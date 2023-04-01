#pragma once
#include "ShardCore.h"
#include "Maths.h"

struct GLFWwindow;

namespace Shard::Graphics
{
    DECLARE_EVENT(class WindowEvents, WindowBeginInitializeEvent);
    DECLARE_EVENT(class WindowEvents, WindowEndInitializeEvent);
    DECLARE_EVENT(class WindowEvents, WindowBeginFinalizeEvent);
    DECLARE_EVENT(class WindowEvents, WindowEndFinalizeEvent);
    DECLARE_EVENT_TWO_PARAM(class WindowEvents, WindowResizeEvent, int, width, int, height)
    DECLARE_EVENT(class WindowEvents, WindowCloseEvent);
    DECLARE_EVENT_TWO_PARAM(class WindowEvents, WindowKeyPressedEvent, int, key, bool, repeat)
    DECLARE_EVENT_ONE_PARAM(class WindowEvents, WindowKeyReleasedEvent, int, key)
    DECLARE_EVENT_ONE_PARAM(class WindowEvents, WindowCursorPosEvent, const glm::vec2&, pos)
    DECLARE_EVENT_TWO_PARAM(class WindowEvents, WindowMouseButtonPressedEvent, int, mouseButton, bool, repeat)
    DECLARE_EVENT_ONE_PARAM(class WindowEvents, WindowMouseButtonReleasedEvent, int, mouseButton)
    DECLARE_EVENT_ONE_PARAM(class WindowEvents, WindowScrollEvent, const glm::vec2&, offset)
    
    class WindowEvents
    {
    public:
        WindowEvents() = default;
        ~WindowEvents()
        {
            beginInitializeEvent.RemoveAll();
            beginFinalizeEvent.RemoveAll();
            endFinalizeEvent.RemoveAll();
            resizeEvent.RemoveAll();
            closeEvent.RemoveAll();
            keyPressedEvent.RemoveAll();
            keyReleasedEvent.RemoveAll();
            cursorPosEvent.RemoveAll();
            mouseButtonPressedEvent.RemoveAll();
            mouseButtonReleasedEvent.RemoveAll();
            scrollEvent.RemoveAll();
        }
        
        WindowBeginInitializeEvent beginInitializeEvent;
        WindowEndInitializeEvent endInitializeEvent;
        WindowBeginFinalizeEvent beginFinalizeEvent;
        WindowEndFinalizeEvent endFinalizeEvent;
        WindowResizeEvent resizeEvent;
        WindowCloseEvent closeEvent;
        WindowKeyPressedEvent keyPressedEvent;
        WindowKeyReleasedEvent keyReleasedEvent;
        WindowCursorPosEvent cursorPosEvent;
        WindowMouseButtonPressedEvent mouseButtonPressedEvent;
        WindowMouseButtonReleasedEvent mouseButtonReleasedEvent;
        WindowScrollEvent scrollEvent;
        
    protected:
        void CallBeginInitializeEvent() { beginInitializeEvent.Broadcast(); }
        void CallEndInitializeEvent() { endInitializeEvent.Broadcast(); }
        void CallBeginFinalizeEvent() { beginFinalizeEvent.Broadcast(); }
        void CallEndFinalizeEvent() { endFinalizeEvent.Broadcast(); }
        void CallResizeEvent(const int width, const int height) { resizeEvent.Broadcast(width, height); }
        void CallCloseEvent() { closeEvent.Broadcast(); }
        void CallKeyPressedEvent(const int key, const bool repeat) { keyPressedEvent.Broadcast(key, repeat); }
        void CallKeyReleasedEvent(const int key) { keyReleasedEvent.Broadcast(key); }
        void CallCursorPosEvent(const glm::vec2& pos) { cursorPosEvent.Broadcast(pos); }
        void CallMouseButtonPressedEvent(const int mouseButton, const bool repeat) { mouseButtonPressedEvent.Broadcast(mouseButton, repeat); }
        void CallMouseButtonReleasedEvent(const int mouseButton) { mouseButtonReleasedEvent.Broadcast(mouseButton); }
        void CallScrollEvent(const glm::vec2& offset) { scrollEvent.Broadcast(offset); }

        friend void WindowSizeCallback(GLFWwindow*, int, int);
        friend void WindowCloseCallback(GLFWwindow*);
        friend void WindowKeyPressedCallback(GLFWwindow*, int, bool);
        friend void WindowKeyReleasedCallback(GLFWwindow*, int);
        friend void WindowCursorPosCallback(GLFWwindow*, const glm::vec2&);
        friend void WindowMouseButtonPressedCallback(GLFWwindow*, int, bool);
        friend void WindowMouseButtonReleasedCallback(GLFWwindow*, int);
        friend void WindowScrollCallback(GLFWwindow*, const glm::vec2&);

        friend class Window;
    };
}