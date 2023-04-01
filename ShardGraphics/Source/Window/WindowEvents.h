#pragma once
#include "Delegates/MulticastDelegate.h"
#include "Maths.h"

struct GLFWwindow;

namespace Shard::Graphics
{
    DECLARE_EVENT(class WindowEvents, WindowBeginCreateEvent);
    DECLARE_EVENT(class WindowEvents, WindowEndCreateEvent);
    DECLARE_EVENT(class WindowEvents, WindowBeginDestroyEvent);
    DECLARE_EVENT(class WindowEvents, WindowEndDestroyEvent);
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
            beginCreateEvent.RemoveAll();
            beginDestroyEvent.RemoveAll();
            endDestroyEvent.RemoveAll();
            resizeEvent.RemoveAll();
            closeEvent.RemoveAll();
            keyPressedEvent.RemoveAll();
            keyReleasedEvent.RemoveAll();
            cursorPosEvent.RemoveAll();
            mouseButtonPressedEvent.RemoveAll();
            mouseButtonReleasedEvent.RemoveAll();
            scrollEvent.RemoveAll();
        }
        
        WindowBeginCreateEvent beginCreateEvent;
        WindowEndCreateEvent endCreateEvent;
        WindowBeginDestroyEvent beginDestroyEvent;
        WindowEndDestroyEvent endDestroyEvent;
        WindowResizeEvent resizeEvent;
        WindowCloseEvent closeEvent;
        WindowKeyPressedEvent keyPressedEvent;
        WindowKeyReleasedEvent keyReleasedEvent;
        WindowCursorPosEvent cursorPosEvent;
        WindowMouseButtonPressedEvent mouseButtonPressedEvent;
        WindowMouseButtonReleasedEvent mouseButtonReleasedEvent;
        WindowScrollEvent scrollEvent;
        
    protected:
        void CallBeginCreateEvent() { beginCreateEvent.Broadcast(); }
        void CallEndCreateEvent() { endCreateEvent.Broadcast(); }
        void CallBeginDestroyEvent() { beginDestroyEvent.Broadcast(); }
        void CallEndDestroyEvent() { endDestroyEvent.Broadcast(); }
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