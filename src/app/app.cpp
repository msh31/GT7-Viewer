#include "app.hpp"
#include <constants.hpp>

#include <frontend/fonts/font_awesome.hpp>
#include <frontend/fonts/jbm_reg.h>
#include <frontend/icons.hpp>
#include <frontend/theme/theme.hpp>

#include <frontend/views/home/home_view.hpp>
#include <frontend/views/settings/settings_view.hpp>

#include <frontend/dialogs/confirm/confirm_dialog.hpp>
#include <frontend/notification/notification.hpp>

void CApp::init( ) {
    setup_logger( );
    ThemeManager::apply_style( );

    m_ui_manager.add_view( { std::make_unique<CHomeView>( ), ICON_HOME, "Home" } );
    m_ui_manager.set_settings_view( { std::make_unique<CSettingsView>( m_config ), ICON_GEAR, "Settings" } );

    m_statusbar.add_left( { "I am a statusbar", "X" } );
    m_statusbar.add_right( { "Build", APP_VERSION.c_str( ) } );
    m_ui_manager.set_statusbar( std::move( m_statusbar ) );
}

void CApp::render( ) {
    ThemeManager::apply_colors( m_config.settings.dark_mode ? ThemeType::Dark : ThemeType::Light );
    m_ui_manager.render( );
    Notify::render_notifications( );
    ConfirmDialog::render( );
}
