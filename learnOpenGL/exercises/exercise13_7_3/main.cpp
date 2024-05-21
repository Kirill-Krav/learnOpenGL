#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "Shader.h"
#include "Camera.h"

float deltaTime = 0.0f;
float lastFrame = 0.0f;

const int width = 800;
const int height = 600;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastMouseX = width / 2;
float lastMouseY = height / 2;
bool firstMouse = true;

float vertices[] = {
//         coords                      normals
    -0.5f, -0.5f, -0.5f,         0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,         0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,         0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,         0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,         0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,         0.0f,  0.0f, -1.0f,
                                        
    -0.5f, -0.5f,  0.5f,         0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,         0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,         0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,         0.0f,  0.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,         0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,         0.0f,  0.0f,  1.0f,

    -0.5f,  0.5f,  0.5f,        -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,        -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,        -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,        -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,        -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,        -1.0f,  0.0f,  0.0f,
                                               
     0.5f,  0.5f,  0.5f,         1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,         1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,         1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,         1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,         1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,         1.0f,  0.0f,  0.0f,
                                               
    -0.5f, -0.5f, -0.5f,         0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,         0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,         0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,         0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,         0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,         0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,         0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,         0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,         0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,         0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,         0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,         0.0f,  1.0f,  0.0f,
};

void framebufferSizeCallback(GLFWwindow *window, int w, int h) {
    glViewport(0, 0, w, h);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.processKeyBoard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.processKeyBoard(BACKWORD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.processKeyBoard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.processKeyBoard(RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse)
    {
        lastMouseX = xpos;
        lastMouseY = ypos;
        firstMouse = false;
    }
    
    float xoffset = xpos - lastMouseX;
    float yoffset = lastMouseY - ypos; 
    lastMouseX = xpos;
    lastMouseY = ypos;
    
    camera.processMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.processMouseScroll(yoffset);
}

bool wireframeMode = false;
void onKeyDown(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS && key == GLFW_KEY_SPACE) {
        if (!wireframeMode) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            wireframeMode = true;
        }
        else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            wireframeMode = false;
        }
    }
}

int main(void)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initiaize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetKeyCallback(window, onKeyDown);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glEnable(GL_DEPTH_TEST);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    Shader basicShader("shader.vert", "shader.frag");
    Shader lightShader("lightshader.vert", "lightShader.frag");

    basicShader.use();
 
    

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);
        
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);

        basicShader.use();
        basicShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        basicShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        basicShader.setVec3("lightPos", lightPos);
        basicShader.setVec3("viewPos", camera.getPosition());

        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.getZoom()), 1.0f * width / height, 0.1f, 100.0f);
        glm::mat4 model = glm::mat4(1.0f);

        basicShader.setMat4("view", view);
        basicShader.setMat4("projection", projection);
        basicShader.setMat4("model", model);
        basicShader.setMat4("inverseModel", glm::inverse(view * model));

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        lightShader.use();

        lightShader.setMat4("view", view);
        lightShader.setMat4("projection", projection);
        lightShader.setMat4("model", model);

        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f));
        lightShader.setMat4("model", model);

        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}