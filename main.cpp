#include <iostream>
#include "include/GLEW/glew.h"
#include "include/GLFW/glfw3.h"
#include "cmath"
#include "Component/Shader.h"
#include "Component/Camera.h"
#include "Component/Material.h"

#define STB_IMAGE_IMPLEMENTATION

#include "include/stb_image.h"
#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"

using namespace std;

void processInput(GLFWwindow *windows);

unsigned int LoadImage(char *textureName,int activeLayer, int format, int interFormat);

void SetGlVertexAttribPointer(int layer, int needNum, int AllNum);

void mouse_callback(GLFWwindow *window, double xpos, double ypos);

int vertexNextPointer = 0;
float lastTime = 0.0;
float currentTime = 0.0;
float frame = 0.0;
bool firstStart = true;

float lastX = 0;
float lastY = 0;
bool firstMouse = true;


Camera *camera = new Camera(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0, 0);
#pragma region info
float vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,


        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
};
unsigned int indices[] =
        {
                0, 1, 3, // first triangle
                1, 2, 3  // second triangle
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
#pragma endregion
//检测输入函数


int main()
{
    //初始化glfw库  好像是基本的库
    glfwInit();
#pragma region
    //下面三行注释是提示版本号，可以不写
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#pragma  endregion
//创建一个窗口
    GLFWwindow *windows = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);
    glfwMakeContextCurrent(windows);//绑定窗口，让这个窗口变成现在操控的窗口对象
    glViewport(0, 0, 800, 600);//设置图像的位置和像素大小  800 600 上面是窗口
    glfwSetCursorPosCallback(windows, mouse_callback);
    glEnable(GL_DEPTH_TEST);
    glewInit();//glew库初始化，如果失败，请看上面这一行  这个库好像是opengl的颜色库
    glewExperimental = true;//显卡的驱动程序不能正确给出所支持的扩展信息，导致GLEW不能正确获取某些函数的入口地址 所以要先设置true

    Shader *shader = new Shader("ShaderData\\VertexTest.glsl", "ShaderData\\FragmentTest.glsl");

    shader->Use();
    unsigned int VAO;//VAO  Vertex Array Object
    glGenVertexArrays(1, &VAO);//顶点数组  1个 所以是1
    glBindVertexArray(VAO);//绑定顶点

    unsigned int VBO;//Vertex Buffer Object
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
    unsigned int EBO;//Element Buffer Obeject
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    SetGlVertexAttribPointer(0, 3, 8);
    SetGlVertexAttribPointer(1, 3, 8);
    SetGlVertexAttribPointer(2, 2, 8);

    stbi_set_flip_vertically_on_load(true);


    unsigned int modelMatLoc = glGetUniformLocation(shader->ID, "modelMat");
    unsigned int viewMatLoc = glGetUniformLocation(shader->ID, "viewMat");
    unsigned int projMatLoc = glGetUniformLocation(shader->ID, "projMat");
    glUniform3f(glGetUniformLocation(shader->ID, "lightPos"), 0.0f, 1000.0f, 450.0f);
    glUniform3f(glGetUniformLocation(shader->ID, "lightColor"), 0.8f, 0.8f, 0.8f);
    unsigned int texture1, texture2;
    texture1 = LoadImage((char *) "container2.png",0,GL_RGBA,GL_RGBA);
    texture2 = LoadImage((char *) "container2_specular.png",  1, GL_RGBA,GL_RGBA);
    Material *mat = new Material(shader, glm::vec3(0.4, 0.4, 0.4), 0, 1);


    float angle = 0;
    while (!glfwWindowShouldClose(windows))
    {
        glUniform3f(glGetUniformLocation(shader->ID, "camerapos"), camera->position.x, camera->position.y,
                    camera->position.z);
        if (firstStart)
        {
            lastTime = glfwGetTime();
            frame = 0;
            firstStart = false;
        } else
        {
            currentTime = glfwGetTime();
            frame = currentTime - lastTime;
            lastTime = glfwGetTime();
        }

        glViewport(0, 0, 800, 600);

        processInput(windows);//调用输入函数

        glClearColor(0, 0.5, 0.5, 1.0F);//设置背景颜色
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清除颜色

        shader->Use();
        glm::mat4 modelMat, viewMat, projMat;
        modelMat = glm::mat4(1.0f);
        viewMat = glm::mat4(1.0f);
        projMat = glm::mat4(1.0f);
        modelMat = glm::rotate(modelMat, glm::radians(0.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        //viewMat = glm::translate(viewMat, glm::vec3(0.0f, 0.0f, -2.0f));
        projMat = glm::perspective(glm::radians(45.0f), (float) 800.0f / (float) 600.0f, 0.1f, 50.0f);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//绑定EBO里的连线信息 这里有顺序问题，不然贴图加载不出
        viewMat = camera->UpdateCamera();
        for (int i = 0; i < 10; i++)
        {
            angle++;

            modelMat = glm::mat4(1.0f);
            modelMat = glm::translate(modelMat, cubePositions[i]);
            //modelMat = glm::rotate(modelMat, glm::radians(20.0f * ((float) pow(-1, i)) * (float) glfwGetTime()),
            //   glm::vec3(1.0f, 0.3f, 0.5f));
            glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
            glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
            glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, glm::value_ptr(projMat));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(windows);//双重缓存，防止画面撕裂的
        glfwPollEvents();//相应事件
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();//关闭
    delete (shader);
    delete (camera);
    return 0;
}

void processInput(GLFWwindow *windows)
{
    if (glfwGetKey(windows, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(windows, true);
    }
    glm::vec3 moveVec3 = glm::vec3(0.0f);
    if (glfwGetKey(windows, GLFW_KEY_A))
    {
        moveVec3 += -glm::vec3(camera->right.x, 0, camera->right.z);
    }
    if (glfwGetKey(windows, GLFW_KEY_D))
    {
        moveVec3 += glm::vec3(camera->right.x, 0, camera->right.z);
    }
    if (glfwGetKey(windows, GLFW_KEY_W))
    {
        moveVec3 += glm::vec3(camera->forword.x, 0, camera->forword.z);
    }
    if (glfwGetKey(windows, GLFW_KEY_S))
    {
        moveVec3 += -glm::vec3(camera->forword.x, 0, camera->forword.z);
    }
    if (glfwGetKey(windows, GLFW_KEY_Q))
    {
        moveVec3 += camera->up;
    }
    if (glfwGetKey(windows, GLFW_KEY_E))
    {
        moveVec3 += -camera->up;
    }
    //std::cout<<frame<<std::endl;
    camera->Move(moveVec3 * frame);
}

unsigned int LoadImage(char *textureName,int activeLayer, int format, int interFormat)
{
    unsigned int texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0 + activeLayer);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nr;
    unsigned char *data = stbi_load(textureName, &width, &height, &nr, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, interFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

    } else
    {
        ::printf("Load texture fail");
    }
    // glUniform1i(glGetUniformLocation(shader->ID, shaderUniformName), activeLayer);
    stbi_image_free(data);

    return texture;
}

void SetGlVertexAttribPointer(int layer, int needNum, int AllNum)
{
    glVertexAttribPointer(layer, needNum, GL_FLOAT, GL_FALSE, AllNum * sizeof(float),
                          (void *) (vertexNextPointer * sizeof(float)));
    vertexNextPointer += needNum;
    glEnableVertexAttribArray(layer);
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    float currentXpos = xpos;
    float currentYpos = ypos;
    if (firstMouse)
    {
        lastX = currentXpos;
        lastY = currentYpos;
        firstMouse = false;
        return;
    }
    float deltaX = currentXpos - lastX;
    float deltaY = currentYpos - lastY;

    // cout<<deltaY<<endl;


    camera->Rotate(deltaX, deltaY);
    lastX = currentXpos;
    lastY = currentYpos;
}
