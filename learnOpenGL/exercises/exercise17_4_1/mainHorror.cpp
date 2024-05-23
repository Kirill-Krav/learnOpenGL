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
//         coords                      normals               texcoords
    -0.5f, -0.5f, -0.5f,         0.0f,  0.0f, -1.0f,        0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,         0.0f,  0.0f, -1.0f,        1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,         0.0f,  0.0f, -1.0f,        1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,         0.0f,  0.0f, -1.0f,        1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,         0.0f,  0.0f, -1.0f,        0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,         0.0f,  0.0f, -1.0f,        0.0f, 0.0f,
                                        
    -0.5f, -0.5f,  0.5f,         0.0f,  0.0f,  1.0f,        0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,         0.0f,  0.0f,  1.0f,        1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,         0.0f,  0.0f,  1.0f,        1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,         0.0f,  0.0f,  1.0f,        1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,         0.0f,  0.0f,  1.0f,        0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,         0.0f,  0.0f,  1.0f,        0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,        -1.0f,  0.0f,  0.0f,        1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,        -1.0f,  0.0f,  0.0f,        1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,        -1.0f,  0.0f,  0.0f,        0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,        -1.0f,  0.0f,  0.0f,        0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,        -1.0f,  0.0f,  0.0f,        0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,        -1.0f,  0.0f,  0.0f,        1.0f, 0.0f,
                                               
     0.5f,  0.5f,  0.5f,         1.0f,  0.0f,  0.0f,        1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,         1.0f,  0.0f,  0.0f,        1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,         1.0f,  0.0f,  0.0f,        0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,         1.0f,  0.0f,  0.0f,        0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,         1.0f,  0.0f,  0.0f,        0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,         1.0f,  0.0f,  0.0f,        1.0f, 0.0f,
                                               
    -0.5f, -0.5f, -0.5f,         0.0f, -1.0f,  0.0f,        0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,         0.0f, -1.0f,  0.0f,        1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,         0.0f, -1.0f,  0.0f,        1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,         0.0f, -1.0f,  0.0f,        1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,         0.0f, -1.0f,  0.0f,        0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,         0.0f, -1.0f,  0.0f,        0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,         0.0f,  1.0f,  0.0f,        0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,         0.0f,  1.0f,  0.0f,        1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,         0.0f,  1.0f,  0.0f,        1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,         0.0f,  1.0f,  0.0f,        1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,         0.0f,  1.0f,  0.0f,        0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,         0.0f,  1.0f,  0.0f,        0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(2.0f, 5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f, 3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f, 2.0f, -2.5f),
    glm::vec3(1.5f, 0.2f, -1.5f),
    glm::vec3(-1.3f, 1.0f, -1.5f)
};

glm::vec3 pointLightPositions[] = {
    glm::vec3(0.7f, 0.2f, 2.0f),
    glm::vec3(2.3f, -3.3f, -4.0f),
    glm::vec3(-4.0f, 2.0f, -12.0f),
    glm::vec3(0.0f, 0.0f, -3.0f)
};

glm::vec3 pointLightColors[] = {
    glm::vec3(0.1f, 0.1f, 0.1f),
    glm::vec3(0.1f, 0.1f, 0.1f),
    glm::vec3(0.1f, 0.1f, 0.1f),
    glm::vec3(0.3f, 0.1f, 0.1f)
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

unsigned int loadTexture(char const *path) {
    int imgWidth, imgHeight, nrChannels;
    unsigned char* data = stbi_load(path, &imgWidth, &imgHeight, &nrChannels, 0);
    if (!data) {
        std::cerr << "Failed to load texture" << std::endl;
        return -1;
    }

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum format;
    if (nrChannels == 1) {
        format = GL_RED;
    }
    else if (nrChannels == 3) {
        format = GL_RGB;
    }
    else if (nrChannels == 4) {
        format = GL_RGBA;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, format, imgWidth, imgHeight, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    return texture;
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

    unsigned int texture = loadTexture("images/container2.png");
    unsigned int specularMap = loadTexture("images/container2_specular.png");

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    Shader basicShader("shader.vert", "shader.frag");
    Shader lightShader("lightshader.vert", "lightShader.frag");

    basicShader.use();
 
    basicShader.setInt("material.diffuse", 0);
    basicShader.setInt("material.specular", 1);

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);
        
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture); 
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specularMap);

        basicShader.use();
        //dirLight
        basicShader.setVec3("dirLight.ambient", 0.0f, 0.0f, 0.0f);
        basicShader.setVec3("dirLight.diffuse", 0.05f, 0.05f, 0.05);
        basicShader.setVec3("dirLight.specular", 0.2f, 0.2f, 0.2f);
        basicShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);

        //pointLights
        for (int i = 0; i < 4; i++) {
            basicShader.setVec3("pointLights[" + std::to_string(i) + "].ambient", pointLightColors[i] * 0.1f);
            basicShader.setVec3("pointLights[" + std::to_string(i) + "].diffuse", pointLightColors[i]);
            basicShader.setVec3("pointLights[" + std::to_string(i) + "].specular", pointLightColors[i]);
            basicShader.setVec3("pointLights[" + std::to_string(i) + "].position", pointLightPositions[i]);
            basicShader.setFloat("pointLights[" + std::to_string(i) + "].constant", 1.0f);
            basicShader.setFloat("pointLights[" + std::to_string(i) + "].linear", 0.14);
            basicShader.setFloat("pointLights[" + std::to_string(i) + "].quadratic", 0.07);
        }

        //spotLight
        basicShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        basicShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
        basicShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
        basicShader.setVec3("spotLight.position", camera.getPosition());
        basicShader.setVec3("spotLight.direction", camera.getFront());
        basicShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(10.0f)));
        basicShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
        basicShader.setFloat("spotLight.constant", 1.0f);
        basicShader.setFloat("spotLight.linear", 0.09f);
        basicShader.setFloat("spotLight.quadratic", 0.032f);

        basicShader.setVec3("viewPos", camera.getPosition());

        basicShader.setFloat("material.shininess", 64.0f);

        
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.getZoom()), 1.0f * width / height, 0.1f, 100.0f);
        basicShader.setMat4("view", view);
        basicShader.setMat4("projection", projection);
        

        glBindVertexArray(VAO);

        for (int i = 0; i < 10; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            basicShader.setMat4("model", model);
            basicShader.setMat4("inverseModel", glm::inverse(model));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        
        

        lightShader.use();

        lightShader.setMat4("view", view);
        lightShader.setMat4("projection", projection);
        
        glm::mat4 model = glm::mat4(1.0f);
        lightShader.setMat4("model", model);

        

        for (int i = 0; i < 4; i++) {
            lightShader.setVec3("lightColor", pointLightColors[i]);
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f));
            lightShader.setMat4("model", model);

            glBindVertexArray(lightVAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}