#pragma once
#include <backend/server/server.hpp>
#include <frontend/views/base_view.hpp>

class CHomeView : public CBaseView {
    public:
        CHomeView( CConfig& cfg );
        ~CHomeView( ) override;
        void render( ) override;
        void on_enter( ) override;
        void on_exit( ) override;

    private:
        static int filter_ip_chars( ImGuiInputTextCallbackData* data );
        void handle_connect_click( bool connected );

        std::string m_ps_addr = { };
        bool m_is_connected = false;

        std::thread m_server_thread;
        Packet::A m_packet_a = { };

        CServer m_server;
        SOCKET m_socket;
        CConfig& m_config;
};
