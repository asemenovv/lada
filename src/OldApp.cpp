#include <filesystem>
#include <iostream>

#include "GL/glew.h"
#include <GLFW/glfw3.h>

#include "DemoApp.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 960

// int main() {
//     if (!glfwInit())
//         return -1;
//
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//     // #ifdef __APPLE__
//     glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//     // #endif
//
//     GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,
//                                           "Hello World", nullptr, nullptr);
//     if (!window) {
//         glfwTerminate();
//         return -1;
//     }
//
//     glfwMakeContextCurrent(window);
//     glfwSwapInterval(1);
//
//     if (glewInit() != GLEW_OK) {
//         std::cerr << "GLEW could not be initialized" << std::endl;
//         return -1;
//     }
//
//     constexpr float positions[] = {
//         -0.5f, -0.5f, 0.0f, 0.0f,
//         0.5f, -0.5f, 1.0f, 0.0f,
//         0.5f, 0.5f, 1.0f, 1.0f,
//         -0.5f, 0.5f, 0.0f, 1.0f,
//     };
//
//     const unsigned int indices[] = {
//         0, 1, 2,
//         2, 3, 0
//     };
//
//     GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
//     GL_CALL(glEnable(GL_BLEND));
//
//     VertexArray va;
//     const VertexBuffer vb(positions, 4 * 4 * sizeof(float));
//
//     VertexBufferLayout layout;
//     layout.Push<float>(2);
//     layout.Push<float>(2);
//     va.AddBuffer(vb, layout);
//
//     const IndexBuffer ib(indices, 6);
//
//     Shader shader("./res/shaders/Basic.glsl");
//     shader.Bind();
//
//     const Texture texture("./res/textures/aquarium.png");
//     texture.Bind();
//     shader.SetUniform1i("u_Texture", 0);
//
//     Renderer renderer;
//
//     ImGui::CreateContext();
//     ImGuiIO& io = ImGui::GetIO(); (void)io;
//     ImGui_ImplGlfw_InitForOpenGL(window, true);
//     ImGui::StyleColorsDark();
//     ImGui_ImplOpenGL3_Init("#version 330");
//
//     float r = 0.0f;
//     float increment = 0.01f;
//
//     while (!glfwWindowShouldClose(window)) {
//         const glm::mat4 proj = glm::ortho(-2.0f, 2.0f,-1.5f, 1.5f,-1.0f, 1.0f);
//         const glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-0.0f, 0.0f, 0.0f));
//         const glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f * r), glm::vec3(0.0f, 1.0f, 0.0f));
//         glm::mat4 mvp = proj * view * model;
//         shader.SetUniformMat4f("u_MVP", mvp);
//
//         renderer.Clear();
//
//         ImGui_ImplOpenGL3_NewFrame();
//         ImGui_ImplGlfw_NewFrame();
//         ImGui::NewFrame();
//
//         shader.Bind();
//         shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
//         renderer.Draw(va, ib, shader);
//
//         if (r > 1.0f || r < 0.0f) {
//             increment = -increment;
//         }
//         r += increment;
//
//         {
//             ImGui::Begin("Lada::Debug");
//             ImGui::SliderFloat("Rotation", &r, 0.0f, 1.0f);
//             ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
//             ImGui::End();
//         }
//
//         ImGui::Render();
//         ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//
//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }
//
//     ImGui_ImplOpenGL3_Shutdown();
//     ImGui_ImplGlfw_Shutdown();
//     ImGui::DestroyContext();
//
//     glfwTerminate();
//     return 0;
// }