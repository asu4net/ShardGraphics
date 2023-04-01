#include "ImGuiRenderer.h"
#include <imgui.h>
#include <ImGuizmo.h>
#include <glfw/glfw3.h>
#include "Implementation/imgui_impl_glfw.h"
#include "Implementation/imgui_impl_opengl3.h"
#include "Window/Window.h"

namespace Shard::Graphics
{
    ImGuiRenderer::ImGuiRenderer()
        : configFlags(0)
    {
    }

    void ImGuiRenderer::Initialize(const std::shared_ptr<Window>& window)
    {
        m_window = window;
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        io.ConfigFlags |= configFlags;
        GLFWwindow* windowHandler = static_cast<GLFWwindow*>(window->GetHandler());
        ImGui_ImplGlfw_InitForOpenGL(windowHandler, true);
        ImGui_ImplOpenGL3_Init("#version 330");
        ImGui::StyleColorsDark();
    }

    void ImGuiRenderer::Update()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGuizmo::BeginFrame();
        
        for (const auto& widget : m_widgets)
        {
            ImGui::Begin(widget->GetName(), widget->opened, widget->flags);
            widget->OnUpdate();
            ImGui::End();
        }
        
        ImGuiIO& io = ImGui::GetIO();

        if (!m_window.expired())
        {
            const auto window = m_window.lock();
            io.DisplaySize = { window->GetWidth(), window->GetHeight() };
        }

        ImGui::Render();
        
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backupCurrentContext = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backupCurrentContext);
        }
    }

    void ImGuiRenderer::Finalize()
    {
        for (const auto& widget : m_widgets)
        {
            widget->OnDestroy();
        }
        
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
}