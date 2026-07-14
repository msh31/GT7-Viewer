#include "home_view.hpp"
#include <frontend/notification/notification.hpp>

void CHomeView::on_enter( ) {
    if ( !m_server.start( ) ) {
        SPDLOG_ERROR( "Failed to start UDP server!" );
    }
    m_socket = m_server.get_socket( );
}

void CHomeView::render( ) {
    ImGui::InputText( "...", &m_ps_addr, ImGuiInputTextFlags_CallbackCharFilter, filter_ip_chars );
    ImGui::Text( "Your IP: %s", m_ps_addr.data( ) );
    // TODO
}

int CHomeView::filter_ip_chars( ImGuiInputTextCallbackData* data ) {
    ImWchar c = data->EventChar;
    if ( std::isdigit( c ) || c == '.' ) return 0; // 0 = accept
    return 1;                                      // 1 = reject
}

void CHomeView::on_exit( ) {
    // TODO
}

CHomeView::~CHomeView( ) {}
