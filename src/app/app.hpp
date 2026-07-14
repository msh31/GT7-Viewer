#pragma once
#include <backend/config/config.hpp>
#include <backend/paths.hpp>
#include <backend/ui_manager/ui_manager.hpp>

#include <frontend/layout/tabbar/tabbar.hpp>

class CApp {
    public:
        void init( );
        void render( );

    private:
        CConfig m_config;
        CUIManager m_ui_manager{ std::make_unique<CTabbarShell>( ) };

        CStatusBar m_statusbar;
};
