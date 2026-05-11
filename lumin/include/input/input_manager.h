#pragma once

#include "ecs/entity.h"
#include <glm/glm.hpp>

namespace lumin {

/**
 * Input codes and event types
 */
enum class KeyCode {
    // Alphabet
    A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
    // Numbers
    Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
    // Special
    Space, Return, Escape, Backspace, Tab, LeftShift, RightShift, LeftCtrl, RightCtrl,
    Left, Right, Up, Down,
    // Function keys
    F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12
};

enum class MouseButton {
    Left,
    Right,
    Middle,
    Button4,
    Button5
};

enum class InputEventType {
    KeyPressed,
    KeyReleased,
    MouseMoved,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseScrolled
};

struct InputEvent {
    InputEventType type;
    KeyCode key;
    MouseButton button;
    glm::vec2 mousePosition;
    glm::vec2 mouseDelta;
    float scrollDelta;
};

/**
 * Input Manager - handles keyboard, mouse, and gamepad input
 */
class InputManager {
public:
    InputManager();
    ~InputManager();

    void update();
    void handleEvent(const InputEvent& event);

    // Keyboard input
    bool isKeyPressed(KeyCode key) const;
    bool isKeyReleased(KeyCode key) const;
    bool isKeyDown(KeyCode key) const;

    // Mouse input
    glm::vec2 getMousePosition() const { return mousePosition_; }
    glm::vec2 getMouseDelta() const { return mouseDelta_; }
    bool isMouseButtonPressed(MouseButton button) const;
    bool isMouseButtonDown(MouseButton button) const;
    float getScrollDelta() const { return scrollDelta_; }

private:
    bool keyStates_[256];
    bool mouseButtonStates_[8];
    glm::vec2 mousePosition_;
    glm::vec2 mouseDelta_;
    glm::vec2 lastMousePosition_;
    float scrollDelta_;
};

} // namespace lumin
