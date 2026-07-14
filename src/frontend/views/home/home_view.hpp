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

        std::string m_ps_addr = { };
        bool m_is_connected = false;

        CServer m_server;
        SOCKET m_socket;
        CConfig& m_config;
};
