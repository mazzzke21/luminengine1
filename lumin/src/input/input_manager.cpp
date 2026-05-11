#include "input/input_manager.h"
#include <cstring>

namespace lumin {

InputManager::InputManager()
    : mousePosition_(0.0f), mouseDelta_(0.0f), lastMousePosition_(0.0f), scrollDelta_(0.0f) {
    std::memset(keyStates_, 0, sizeof(keyStates_));
    std::memset(mouseButtonStates_, 0, sizeof(mouseButtonStates_));
}

InputManager::~InputManager() {
}

void InputManager::update() {
    mouseDelta_ = mousePosition_ - lastMousePosition_;
    lastMousePosition_ = mousePosition_;
    scrollDelta_ = 0.0f;
}

void InputManager::handleEvent(const InputEvent& event) {
    switch (event.type) {
    case InputEventType::KeyPressed:
        keyStates_[static_cast<int>(event.key)] = true;
        break;
    case InputEventType::KeyReleased:
        keyStates_[static_cast<int>(event.key)] = false;
        break;
    case InputEventType::MouseMoved:
        mousePosition_ = event.mousePosition;
        break;
    case InputEventType::MouseButtonPressed:
        mouseButtonStates_[static_cast<int>(event.button)] = true;
        break;
    case InputEventType::MouseButtonReleased:
        mouseButtonStates_[static_cast<int>(event.button)] = false;
        break;
    case InputEventType::MouseScrolled:
        scrollDelta_ = event.scrollDelta;
        break;
    }
}

bool InputManager::isKeyPressed(KeyCode key) const {
    return keyStates_[static_cast<int>(key)];
}

bool InputManager::isKeyReleased(KeyCode key) const {
    return !keyStates_[static_cast<int>(key)];
}

bool InputManager::isKeyDown(KeyCode key) const {
    return keyStates_[static_cast<int>(key)];
}

bool InputManager::isMouseButtonPressed(MouseButton button) const {
    return mouseButtonStates_[static_cast<int>(button)];
}

bool InputManager::isMouseButtonDown(MouseButton button) const {
    return mouseButtonStates_[static_cast<int>(button)];
}

} // namespace lumin
