﻿#include "ImGuiRenderer.h"
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

        static bool dockSpaceOpen = true;
        static bool fullscreen = true;
        static bool padding = false;
        static ImGuiDockNodeFlags dockSpaceFlags = ImGuiDockNodeFlags_None;
        
        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoMove;
            windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockSpaceFlags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }
        
        if (dockSpaceFlags & ImGuiDockNodeFlags_PassthruCentralNode)
            windowFlags |= ImGuiWindowFlags_NoBackground;
        
        if (!padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

        for (const auto& widget : m_widgets)
        {
            ImGui::Begin(widget->GetName(), widget->opened, widget->flags);
            widget->OnUpdate();
            ImGui::End();
        }

        //---------------------------------------------------------
        // ImGui Dock Space Begin
        //---------------------------------------------------------
        
        ImGui::Begin("Shard Graphics", &dockSpaceOpen, windowFlags);

        if (!padding)
            ImGui::PopStyleVar();

        if (fullscreen)
            ImGui::PopStyleVar(2);

        // Submit the DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            const ImGuiID dockSpaceId = ImGui::GetID("ShardGraphicsDockSpace");
            ImGui::DockSpace(dockSpaceId, ImVec2(0.0f, 0.0f), dockSpaceFlags);
        }
        else
        {
            printf("Docking disabled");
        }
        
        for (const auto& widget : m_dockSpaceWidgets)
        {
            ImGui::Begin(widget->GetName(), widget->opened, widget->flags);
            widget->OnUpdate();
            ImGui::End();
        }

        ImGui::End();

        //---------------------------------------------------------
        // ImGui Dock Space End
        //---------------------------------------------------------
        
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
            widget->OnDestroy();

        for (const auto& widget : m_dockSpaceWidgets)
            widget->OnDestroy();
        
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
}