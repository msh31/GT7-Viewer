#pragma once
#include <backend/server/server.hpp>
#include <frontend/views/base_view.hpp>

class CHomeView : public CBaseView {
    public:
        ~CHomeView( ) override;
        void render( ) override;
        void on_enter( ) override;
        void on_exit( ) override;

    private:
        static int filter_ip_chars( ImGuiInputTextCallbackData* data );

        std::string m_ps_addr = { };

        CServer m_server;
        SOCKET m_socket;
};
