
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>

#include "editor.hpp"
#include "engine.hpp"
#include "window.hpp"

namespace SquirrelEngine {

Editor::Editor() {}

StartupErrors Editor::initialize( Engine* t_owner ) {
    System::initialize( t_owner );

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    // Setting up ImGui flags
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    // Setting style for ImGui
    ImGui::StyleColorsDark();
    if ( ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable ) {
        ImGui::GetStyle().WindowRounding = 4.f;
        ImGui::GetStyle().ChildRounding = 4.f;
        ImGui::GetStyle().FrameRounding = 4.f;
        ImGui::GetStyle().GrabRounding = 4.f;
        ImGui::GetStyle().Colors[ImGuiCol_WindowBg].w = 1.f;
    }

    // Setting up ImGui
    ImGui_ImplGlfw_InitForOpenGL( owner->getWindowHandle()->getHandle(), true );
    ImGui_ImplOpenGL3_Init( "#version 330" );

    return StartupErrors::SE_Success;
}

void Editor::update( const float ) {
    // ImGui update functions
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    displayDockspace();

    // Display the different windows
    for ( auto& func : m_displayMenuCallbacks ) {
        func();
    }

    ImGui::ShowDemoWindow();
}

void Editor::render() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData() );

    if ( ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable ) {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent( backup_current_context );
    }
}

void Editor::displayDockspace() {
    // Setting up viewport
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos( viewport->Pos );
    ImGui::SetNextWindowSize( viewport->Size );
    ImGui::SetNextWindowViewport( viewport->ID );
    ImGui::SetNextWindowBgAlpha( 0.0f );

    // Setting up window flags
    ImGuiWindowFlags window_flags =
        ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
                    ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |=
        ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    // Setting up window style
    ImGui::PushStyleVar( ImGuiStyleVar_WindowRounding, 0.0f );
    ImGui::PushStyleVar( ImGuiStyleVar_WindowBorderSize, 0.0f );
    ImGui::PushStyleVar( ImGuiStyleVar_WindowPadding, ImVec2( 0.0f, 0.0f ) );

    // Making the window
    ImGui::SetNextWindowBgAlpha( 0.0f );
    ImGui::Begin( "Editor Window", &isOpen, window_flags );
    ImGui::PopStyleVar( 3 );

    // Setting up window settings
    ImGuiID dockspace_id = ImGui::GetID( "Editor" );
    ImGuiDockNodeFlags dockspace_flags =
        ImGuiDockNodeFlags_PassthruCentralNode |
        ImGuiDockNodeFlags_NoDockingInCentralNode;
    ImGui::DockSpace( dockspace_id, ImVec2( 0.0f, 0.0f ), dockspace_flags );
    displayMenuBar();
    ImGui::End();
}

void Editor::displayMenuBar() {
    if ( ImGui::BeginMenuBar() ) {

        ImGui::EndMenuBar();
    }
}

} // namespace SquirrelEngine
