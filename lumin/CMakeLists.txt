cmake_minimum_required(VERSION 3.20)
project(LuminEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Main engine library
add_library(lumin_engine
    src/engine.cpp
    src/ecs/entity_manager.cpp
    src/ecs/component_manager.cpp
    src/graphics/renderer.cpp
    src/graphics/shader.cpp
    src/physics/physics_engine.cpp
    src/audio/audio_engine.cpp
    src/input/input_manager.cpp
    src/scene/scene_manager.cpp
    src/core/transform.cpp
)

target_include_directories(lumin_engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link external libraries (adjust paths as needed)
# For Windows: vcpkg or manual setup
# target_link_libraries(lumin_engine PRIVATE
#     opengl32
#     glfw3
#     glew32
#     bullet3
#     SDL2_mixer
# )

# Example executable
add_executable(lumin_example
    examples/main.cpp
)
target_link_libraries(lumin_example PRIVATE lumin_engine)

# Optional: Tests
enable_testing()
