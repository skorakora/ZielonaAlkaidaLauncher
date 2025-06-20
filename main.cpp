#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

GLuint LoadTextureFromFile(const char* filename, int& width, int& height) {
    unsigned char* image_data = stbi_load(filename, &width, &height, NULL, 4);
    if (image_data == NULL) {
        std::cerr << "Failed to load image: " << filename << std::endl;
        return 0;
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    stbi_image_free(image_data);

    return texture;
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Minecraft Launcher", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

    // Dodajemy czcionki
    io.Fonts->AddFontDefault(); // domyślna mała czcionka

    ImFont* bigFont = io.Fonts->AddFontFromFileTTF("arialbd.ttf", 150.0f); // bardzo duża czcionka
    if (!bigFont) {
        std::cerr << "Nie udało się załadować czcionki arialbd.ttf\n";
    }

    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 10.0f;
    style.Colors[ImGuiCol_WindowBg].w = 0.6f;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    int bg_width, bg_height;
    GLuint bg_texture = LoadTextureFromFile("backround.jpg", bg_width, bg_height);
    if (bg_texture == 0) return -1;

    char nickname[64] = "";

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        int win_width, win_height;
        glfwGetFramebufferSize(window, &win_width, &win_height);

        // Tło
        ImGui::GetBackgroundDrawList()->AddImage(
            (void*)(intptr_t)bg_texture,
            ImVec2(0, 0),
            ImVec2((float)win_width, (float)win_height),
            ImVec2(0, 0), ImVec2(1, 1)
        );

        // Gradient
        ImGui::GetBackgroundDrawList()->AddRectFilledMultiColor(
            ImVec2(0, 0),
            ImVec2((float)win_width, (float)win_height),
            IM_COL32(0, 0, 0, 180),
            IM_COL32(0, 0, 0, 180),
            IM_COL32(0, 0, 0, 220),
            IM_COL32(0, 0, 0, 220)
        );

        // Nagłówek — tylko on ma dużą czcionkę
        {
            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::SetNextWindowSize(ImVec2((float)win_width, win_height * 0.5f));
            ImGui::Begin("Header", nullptr,
                ImGuiWindowFlags_NoTitleBar |
                ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoMove |
                ImGuiWindowFlags_NoCollapse |
                ImGuiWindowFlags_NoBackground);

            if (bigFont) ImGui::PushFont(bigFont);
            ImVec2 textSize = ImGui::CalcTextSize("Zielona Alkaida");
            ImGui::SetCursorPos(ImVec2((win_width - textSize.x) / 2.0f, (win_height * 0.5f - textSize.y) / 2.0f));
            ImGui::TextColored(ImVec4(0.2f, 1.0f, 0.2f, 1.0f), "Zielona Alkaida");
            if (bigFont) ImGui::PopFont();

            ImGui::End();
        }

        // Pole na nick — domyślna czcionka
        {
            ImGui::SetNextWindowPos(ImVec2(20, win_height - 120));
            ImGui::SetNextWindowSize(ImVec2(300, 100));
            ImGui::Begin("NicknamePanel", nullptr,
                ImGuiWindowFlags_NoTitleBar |
                ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoMove |
                ImGuiWindowFlags_NoCollapse |
                ImGuiWindowFlags_NoBackground);

            ImGui::Text("Wpisz nick:");
            ImGui::InputText("##nick", nickname, IM_ARRAYSIZE(nickname));
            ImGui::End();
        }

        // Przyciski — domyślna czcionka
        {
            ImGui::SetNextWindowPos(ImVec2(win_width - 320, win_height - 160));
            ImGui::SetNextWindowSize(ImVec2(300, 140));
            ImGui::Begin("ButtonsPanel", nullptr,
                ImGuiWindowFlags_NoTitleBar |
                ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoMove |
                ImGuiWindowFlags_NoCollapse |
                ImGuiWindowFlags_NoBackground);

            if (ImGui::Button("Zielona alkaida clasic", ImVec2(280, 50))) {
                std::cout << "Start: Zielona alkaida clasic | Nick: " << nickname << "\n";
            }
            if (ImGui::Button("Zielona alkaida edycja 2", ImVec2(280, 50))) {
                std::cout << "Start: Zielona alkaida edycja 2 | Nick: " << nickname << "\n";
            }

            ImGui::End();
        }

        // Stopka — domyślna czcionka
        {
            ImGui::SetNextWindowPos(ImVec2(10, win_height - 30));
            ImGui::SetNextWindowSize(ImVec2((float)win_width - 20, 20));
            ImGui::Begin("Footer", nullptr,
                ImGuiWindowFlags_NoTitleBar |
                ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoMove |
                ImGuiWindowFlags_NoCollapse |
                ImGuiWindowFlags_NoBackground);

            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.7f, 0.7f, 0.7f, 0.8f));
            ImGui::Text("Created by: Daniel Skorski     Copyright: Danzo Systems");
            ImGui::PopStyleColor();

            ImGui::End();
        }

        // Renderowanie
        ImGui::Render();
        glViewport(0, 0, win_width, win_height);
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
