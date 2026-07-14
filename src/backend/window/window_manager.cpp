#include "window_manager.hpp"
#include <constants.hpp>

#include <frontend/fonts/font_awesome.hpp>
#include <frontend/fonts/jbm_reg.h>

bool CWindowManager::should_continue( ) {
    bool window_open = glfwWindowShouldClose( m_window ) == 0;
#ifndef NDEBUG
    bool q_pressed = glfwGetKey( m_window, GLFW_KEY_Q ) == GLFW_PRESS;
    return window_open && !q_pressed;
#else
    return window_open;
#endif
}

void CWindowManager::run( std::function<void( )> fun ) {
    do {
        glClear( GL_COLOR_BUFFER_BIT );

        ImGui_ImplOpenGL3_NewFrame( );
        ImGui_ImplGlfw_NewFrame( );
        ImGui::NewFrame( );

        ImGuiViewport* viewport = ImGui::GetMainViewport( );
        ImGui::SetNextWindowPos( viewport->Pos );
        ImGui::SetNextWindowSize( viewport->Size );
        // ImGui::SetNextWindowViewport(viewport->ID);

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                                        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
                                        ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus |
                                        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;

        ImGui::Begin( "Main Window", nullptr, window_flags );
        fun( );
        ImGui::End( );
        ImGui::Render( );

        ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData( ) );
        glfwSwapBuffers( m_window );
        glfwWaitEventsTimeout( 1.0 / 60.0 );
    } while ( should_continue( ) );
}

static void error_callback( int error, const char* description ) {
    auto str = std::format( "A fatal error occured: {}", description );
    throw std::runtime_error( str.c_str( ) );
}

void CWindowManager::setup_opengl( ) {
    glfwSetErrorCallback( error_callback );
    if ( !glfwInit( ) ) {
        throw std::runtime_error( "Failed to initialize GLFW" );
    }

    // glfwWindowHint( GLFW_SAMPLES, 4 ); // 4x antialiasing (MSAA)
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE ); // no old OpenGL

    m_window = glfwCreateWindow( DEF_RES_W, DEF_RES_H, APP_NAME.c_str( ), nullptr, nullptr );
    if ( m_window == nullptr ) {
        glfwTerminate( );
    }

    glfwSetWindowSizeLimits( m_window, MIN_RES_W, MIN_RES_H, MAX_RES_W, MAX_RES_H );
    glfwMakeContextCurrent( m_window );
    glfwSwapInterval( 1 );
    if ( !gladLoadGL( glfwGetProcAddress ) ) {
        throw std::runtime_error( "Failed to initialize GLAD!" );
    }

    // glEnable( GL_MULTISAMPLE ); // enable MSAA...
}

void CWindowManager::setup_imgui( ) {
    ImGui::CreateContext( );

    ImGuiIO& io = ImGui::GetIO( );
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.IniFilename = nullptr; // no imgui.ini
    io.LogFilename = nullptr; // no imgui log pls

    CFontManager::get( ).load_from_memory( { "jbm_reg", 16.0f, false, true }, (void*)jbm_reg, jbm_reg_len );
    CFontManager::get( ).load_from_memory(
        { "font_awesome", 16.0f, true, false }, (void*)font_awesome, font_awesome_len );

    CFontManager::get( ).load_from_memory( { "jbm_reg_xl", 18.0f, false, false }, (void*)jbm_reg, jbm_reg_len );

    if ( !ImGui_ImplGlfw_InitForOpenGL( m_window, true ) ) {
        throw std::runtime_error( "Failed to initialize ImGui for OpenGL" );
    }
    if ( !ImGui_ImplOpenGL3_Init( ) ) {
        throw std::runtime_error( "Failed to initialize ImGui" );
    }
}
