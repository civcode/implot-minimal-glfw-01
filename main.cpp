#include <iostream>
#include <cmath>
#include <vector>

#include "implot.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h> // Include glfw3.h after our OpenGL declarations

using std::cout;
using std::endl;

// float x_data = 0.0f;  // Single x value for current point
// float y_data = 0.0f;  // Single y value for current point

std::vector<float> x_data_all;
std::vector<float> y_data_all;

void RenderPlot(float x, float y)
{
    // x_data_all.push_back(x);
    // y_data_all.push_back(y);

    if (ImPlot::BeginPlot("Iterative Scatter Plot", ImVec2(-1, 0), ImPlotFlags_Equal)) {
        // Set up plot style, grid, etc.
        ImPlot::SetupAxes("X", "Y");

        // Render only the new point
        ImPlot::PlotScatter("New Point", x_data_all.data(), y_data_all.data(), x_data_all.size());  // Plot only the new point
        // Make axis equal


        ImPlot::EndPlot();
    }
    cout << "vector size: " << x_data_all.size() << endl;
}

int main() {
    // Initialize GLFW and OpenGL context
    if (!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(1280, 720, "ImPlot Iterative Example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsLight();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // Setup ImPlot context
    ImPlot::CreateContext();

    // Initialize variables for plotting
    float x_data = 0;
    float y_data = 0;

    // Iteratively add points to the plot
    int i = 0;
    while (!glfwWindowShouldClose(window)) {
        // Poll and handle events
        glfwPollEvents();

        // Start new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Add a new point (for example, square of i)
        for (int j=0; j<100; j++) {
            float a = 0.001f;
            float t = i * 0.01f;
            x_data = a * t * cos(t);
            y_data = a * t * sin(t);
            x_data_all.push_back(x_data);
            y_data_all.push_back(y_data);
        }
        float a = 0.001f;
        float t = i * 0.01f;
        // x_data = static_cast<float>(i) * 0.0001 * cos(static_cast<float>(i) * 0.01);
        // y_data = static_cast<float>(i)*0.01 * static_cast<float>(i)*0.01 * sin(static_cast<float>(i) * 0.01);  // For example, square of x
        x_data = a * t * cos(t);
        y_data = a * t * sin(t);

        // Render the plot with only the new point
        RenderPlot(x_data, y_data);

        // Increment counter
        i++;

        // Render ImGui
        ImGui::Render();
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap buffers
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImPlot::DestroyContext();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}


