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
float lastMouseX = width / 2, lastMouseY = height / 2;
bool firstMouse = true;

float vertices[] = {
    //coords                      texture
    -0.5f, -0.5f, -0.5f,        0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,        1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,        1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,        1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,        0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,        0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,        0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,        1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,        1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,        1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,        0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,        0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,        1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,        1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,        0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,        0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,        0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,        1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,        1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,        1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,        0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,        0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,        0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,        1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,        0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,        1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,        1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,        1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,        0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,        0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,        0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,        1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,        1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,        1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,        0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,        0.0f, 1.0f
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

void framebufferSizeCallback(GLFWwindow *window, int w, int h) {
    glViewport(0, 0, w, h);
}

float mixValue = 0.2f;
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        mixValue += 0.01f;
        mixValue = std::min(1.0f, mixValue);
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        mixValue -= 0.01f;
        mixValue = std::max(0.0f, mixValue);
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
    




    int imgWidth, imgHeight, nrChannels;
    unsigned char* data = stbi_load("images/container.jpg", &imgWidth, &imgHeight, &nrChannels, 0);
    if (!data) {
        std::cerr << "Failed to load texture" << std::endl;
        return -1;
    }

    unsigned int texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);


    stbi_set_flip_vertically_on_load(true);
    data = stbi_load("images/awesomeface.png", &imgWidth, &imgHeight, &nrChannels, 0);
    if (!data) {
        std::cerr << "Failed to load texture" << std::endl;
        return -1;
    }
    
    unsigned int texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);


    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    Shader ourShader("shader.vert", "shader.frag");

    ourShader.use();

    ourShader.setInt("texture1", 0);

    ourShader.setInt("texture2", 1);

    
    

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        
        processInput(window);
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        ourShader.use();

        glm::mat4 view = glm::mat4(1.0f);
        view = camera.getViewMatrix();
        int viewLocation = glGetUniformLocation(ourShader.getID(), "view");
        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(camera.getZoom()), 1.0f * width / height, 0.1f, 100.0f);
        int projectionLocation = glGetUniformLocation(ourShader.getID(), "projection");
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(VAO);
        for (int i = 0; i < 10; i++) {

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = acosf(-1) / 9.0f * (i + 1);
            model = glm::rotate(model, (float)glfwGetTime() * angle, glm::vec3(1.0f, 0.3f, 0.5f));
            
            int modelLocation = glGetUniformLocation(ourShader.getID(), "model");
            glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

            ourShader.setFloat("mixValue", mixValue);


            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}