cmake_minimum_required(VERSION 3.12)
project(ImPlotIterativeExample)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Set up paths to your libraries (make sure they exist on your system)
set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/libs/imgui")
set(IMPLT_DIR "${CMAKE_SOURCE_DIR}/libs/implot")
set(GLFW_DIR "${CMAKE_SOURCE_DIR}/libs/glfw")

# Add source files for ImGui and ImPlot
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# Include only the existing ImPlot source files
set(IMPLT_SOURCES
    ${IMPLT_DIR}/implot.cpp  # Main ImPlot source file
    ${IMPLT_DIR}/implot_items.cpp  # ImPlot items file
)

# Include directories for the libraries
include_directories(
    ${IMGUI_DIR}
    ${IMPLT_DIR}
    ${GLFW_DIR}
    ${OPENGL_INCLUDE_DIR}
)

# Add source files for your project
set(SOURCES
    main.cpp
    ${IMGUI_SOURCES}
    ${IMPLT_SOURCES}
)

# Create executable
add_executable(ImPlotIterativeExample ${SOURCES})

# Link the necessary libraries
target_link_libraries(ImPlotIterativeExample
    glfw
    OpenGL
)

# Optionally link static or precompiled libraries if you are not using add_subdirectory.
# You may need to specify paths manually if required.

