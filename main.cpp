#include "implot.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h> // Include glfw3.h after our OpenGL declarations

void RenderPlot(float x, float y)
{
    if (ImPlot::BeginPlot("Iterative Scatter Plot")) {
        // Set up plot style, grid, etc.
        ImPlot::SetupAxes("X", "Y");

        // Render only the new point
        ImPlot::PlotScatter("New Point", &x, &y, 1);  // Plot only the new point

        ImPlot::EndPlot();
    }
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
        x_data = static_cast<float>(i) * 0.0001;
        y_data = static_cast<float>(i)*0.01 * static_cast<float>(i)*0.01;  // For example, square of x

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


