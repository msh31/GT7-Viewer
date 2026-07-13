#include "packet.hpp"

std::array<std::uint8_t, 296> Packet::decrypt(
    std::span<std::uint8_t, 296> raw_bytes, const std::array<std::uint8_t, 32>& key,
    const std::array<std::uint8_t, 8>& nonce ) {

    std::array<std::uint8_t, raw_bytes.extent> decrypted = { };
    ucstk::Salsa20 salsa( key.data( ) );
    salsa.setIv( nonce.data( ) );

    salsa.processBytes( raw_bytes.data( ), decrypted.data( ), 296 );
    return decrypted;
}

std::array<uint8_t, 8> Packet::derive_nonce( std::span<std::uint8_t, 296> raw_bytes ) {
    std::array<uint8_t, 8> nonce;

    uint32_t iv1 = static_cast<uint32_t>( raw_bytes[0x40] );
    iv1 |= static_cast<uint32_t>( raw_bytes[0x41] ) << 8;
    iv1 |= static_cast<uint32_t>( raw_bytes[0x42] ) << 16;
    iv1 |= static_cast<uint32_t>( raw_bytes[0x43] ) << 24;

    uint32_t iv2 = iv1 ^ 0xDEADBEAF; // packet A

    nonce[0] = static_cast<uint8_t>( iv2 & 0xFF );
    nonce[1] = static_cast<uint8_t>( ( iv2 >> 8 ) & 0xFF );
    nonce[2] = static_cast<uint8_t>( ( iv2 >> 16 ) & 0xFF );
    nonce[3] = static_cast<uint8_t>( ( iv2 >> 24 ) & 0xFF );
    nonce[4] = static_cast<uint8_t>( iv1 & 0xFF );
    nonce[5] = static_cast<uint8_t>( ( iv1 >> 8 ) & 0xFF );
    nonce[6] = static_cast<uint8_t>( ( iv1 >> 16 ) & 0xFF );
    nonce[7] = static_cast<uint8_t>( ( iv1 >> 24 ) & 0xFF );

    return nonce;
}

// stolen from -> https://github.com/MacManley/gt7-udp
std::array<uint8_t, 32> Packet::get_key_bytes( ) {
    std::array<uint8_t, 32> bytes = { };
    const std::string key = "Simulator Interface Packet GT7 ver 0.0";

    for ( size_t i = 0; i < key.size( ) && i < bytes.size( ); ++i ) {
        bytes[i] = static_cast<uint8_t>( key[i] );
    }
    return bytes;
}
