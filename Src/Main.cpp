#include <iostream>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

void FramebufferSizeCallback(GLFWwindow *window, int width, int height);
void ProcessInputs(GLFWwindow *window);

// Retangle
// float vertices[] = {
//     0.5f, 0.5f, 0.0f,   // top right
//     0.5f, -0.5f, 0.0f,  // bottom right
//     -0.5f, -0.5f, 0.0f, // bottom left
//     -0.5f, 0.5f, 0.0f   // top left
// };
// unsigned int indices[] = {
//     3, 2, 1, // first triangle
//     1, 0, 3  // second triangle
// };

// Triangle (equilateral)
// float vertices[] = {
//     -0.5f, -0.5f, 0.0f, // bottom left
//     0.5f, -0.5f, 0.0f,  // bottom right
//     0.0f, 0.5f, 0.0f    // top
// };
// unsigned int indices[] = {
//     0, 1, 2};

// Triangle (equilateral) (colored)
float vertices[] = {
    // positions         // colors
    0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
    0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f    // top
};
unsigned int indices[] = {
    1, 0, 2};

int main()
{
    // Init GLFW and errorcheck
    if (!glfwInit())
    {
        std::cerr << "[ERROR] Failed to init GLFW\n";
        return -1;
    }

    // Set up OpenGL versins, profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window (and make it the current context) and errorcheck
    GLFWwindow *window = glfwCreateWindow(800, 600, "VoxelGame", NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "[ERROR] Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Load GLAD and errorcheck
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "[ERROR] Failed to init GLAD\n";
        glfwTerminate();
        return -1;
    }

    // Set veiwport size and set up resizing
    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

    // Shader program setup
    Shader ourShader("./Resources/Shaders/Basic/Basic.vert", "./Resources/Shaders/Basic/Basic.frag");

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    // Render loop setup
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glPolygonMode(GL_FRONT, GL_FILL);
    glEnable(GL_CULL_FACE);

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        ProcessInputs(window);

        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.Use();

        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}

/**
 * Sets the viewport of the OpenGL rendering context to match the size of the specified window.
 *
 * @param window A pointer to the GLFWwindow whose size will be used for the viewport.
 * @param width The width of the window.
 * @param height The height of the window.
 */
void FramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

/**
 * Processes inputs.
 *
 * @param window A pointer to the GLFW window to operate on.
 */
void ProcessInputs(GLFWwindow *window)
{
    // Set WindowShouldClose to ture
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    // Press space to see in wireframe mode
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        glDisable(GL_CULL_FACE);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
    {
        glEnable(GL_CULL_FACE);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}
