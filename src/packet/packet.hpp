#pragma once
#include <Salsa20.h>

namespace Packet {
    struct A { // Packet A sent by the game sends the interesting information
    };

    [[nodiscard]]
    std::array<std::uint8_t, 296> decrypt(
        std::span<std::uint8_t, 296> raw_bytes, const std::array<std::uint8_t, 32>& key,
        const std::array<std::uint8_t, 8>& nonce );

    [[nodiscard]]
    std::array<uint8_t, 8> derive_nonce( std::span<std::uint8_t, 296> raw_bytes );
    [[nodiscard]]
    std::array<uint8_t, 32> get_key_bytes( );

    void parse( );
} // namespace Packet
