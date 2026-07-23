#include "home_view.hpp"
#include <backend/font_manager/font_manager.hpp>
#include <frontend/notification/notification.hpp>
#include <frontend/ui.hpp>

#include <backend/heartbeat/heartbeat.hpp>

CHomeView::CHomeView( CConfig& cfg ) : m_config( cfg ) {};

void CHomeView::on_enter( ) {
    if ( !m_server.start( ) ) {
        SPDLOG_ERROR( "Failed to start UDP server!" );
    }
    m_socket = m_server.get_socket( );

    auto config_ip = m_config.settings.ip_address;
    if ( !config_ip.empty( ) ) {
        m_ps_addr = config_ip;
    }
}

void CHomeView::render( ) {
    bool connected = m_is_connected;
    if ( connected ) {
        m_packet_a = m_server.get_latest_packet_a( );
    }
    ui::add_font_text(
        "Gran Turismo 7 Metrics Viewer", CFontManager::get( ).get_font( "jbm_reg_xl" ).value_or( nullptr ) ); // sus
    ImGui::Dummy( ImVec2( 0.0f, 10.0f ) );

    ImGui::Text( "Enter your Playstation's IP address: " );
    ImGui::SameLine( );
    ImGui::Dummy( ImVec2( 0.0f, 1.0f ) );
    ImGui::SetNextItemWidth( ImGui::CalcTextSize( "888.888.888.888" ).x + 100.f );
    ImGui::InputText( "##ip_input", &m_ps_addr, ImGuiInputTextFlags_CallbackCharFilter, filter_ip_chars );

    const std::string con_text = connected ? "Stop Recording" : "Start Recording";
    if ( ImGui::Button( con_text.c_str( ) ) ) handle_connect_click( connected );
    ImGui::Separator( );
    ImGui::Dummy( ImVec2( 0.0f, 100.0f ) );

    ImGui::BeginChild( "##main_area", ImVec2( 0, 0 ) );
    ImGui::Text( "%.0f KM/H", m_packet_a.speed * 3.6 ); // game uses m/s
    ImGui::EndChild( );
}

int CHomeView::filter_ip_chars( ImGuiInputTextCallbackData* data ) {
    ImWchar c = data->EventChar;
    if ( std::isdigit( c ) || c == '.' ) return 0; // 0 = accept
    return 1;                                      // 1 = reject
}

void CHomeView::handle_connect_click( bool connected ) {
    if ( connected ) {
        handle_disconnect( );
    } else {
        if ( m_ps_addr.empty( ) ) {
            Notify::show_notification( "Connection Failure", "Empty IP, refusing to connect.", 3000 );
        } else {
            in_addr scratch;
            if ( inet_pton( AF_INET, m_ps_addr.c_str( ), &scratch ) <= 0 ) {
                Notify::show_notification( "Connection Failure", "Invalid IP format.", 3000 );
            } else {
                m_config.settings.ip_address = m_ps_addr;

                CHeartBeat heartbeat( m_ps_addr, 33739 ); // TODO: make this not magic
                if ( !heartbeat.send( m_socket, 'A' ) ) {
                    Notify::show_notification( "Connection Failure", "Failed to send heartbeat!", 1500 );
                } else { // packet A
                    auto n_str = std::format( "Sent heartbeat to: {}:{}", m_ps_addr, 33739 );
                    Notify::show_notification( "Connection Success", n_str, 3000 );
                    m_is_connected = true;
                    m_config.save( );

                    m_server_thread = std::thread( &CServer::listen, &m_server );
                }
            }
        }
    }
}

void CHomeView::on_exit( ) { handle_disconnect( ); }

void CHomeView::handle_disconnect( ) {
    m_is_connected = false;
    if ( m_server_thread.joinable( ) ) {
        Notify::show_notification( "Information", "Waiting for server to stop before disconnecting..", 2000 );
        m_server.stop_flag = true;
        m_server_thread.join( );
    }
}

CHomeView::~CHomeView( ) {}
