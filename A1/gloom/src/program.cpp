// Local headers
#include <vector>

#include "gloom/gloom.hpp"
#include "gloom/shader.hpp"

#include "program.hpp"

GLuint vaoGen(std::vector<float> vertices, std::vector<unsigned int> indices) {
    GLuint array;
    GLuint vbo_buffer;
    GLuint index_buffer;

    // generates one VAO
    glGenVertexArrays(1, &array);
    glBindVertexArray(array);

    // generates one VBO
    glGenBuffers(1, &vbo_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_buffer);

    // load data into VBO
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(int)*vertices.size(),
        vertices.data(),
        GL_STATIC_DRAW
    );

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // generate index array buffer
    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);

    // load data into index array buffer
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(unsigned int)*indices.size(),
        indices.data(),
        GL_STATIC_DRAW
    );

    return array;
}

void runProgram(GLFWwindow* window)
{
    // Enable depth (Z) buffer (accept "closest" fragment)
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Configure miscellaneous OpenGL settings
    glEnable(GL_CULL_FACE);

    // Set default colour after clearing the colour buffer
    glClearColor(0.3f, 0.5f, 0.8f, 1.0f);

    // Set up your scene here (create Vertex Array Objects, etc.)
    std::vector<float> vertices = {
         0.6f, -0.8f, -1.2f,
         0.0f,  0.4f,  0.0f,
        -0.8f, -0.2f,  1.2f,
    };
    std::vector<unsigned int> indices = {0, 1, 2};
    GLuint test_vao = vaoGen(vertices, indices);
    glBindVertexArray(test_vao);

    printGLError();

    Gloom::Shader shader;
    shader.makeBasicShader("../../../gloom/shaders/simple.vert","../../../gloom/shaders/simple.frag");
    shader.activate();

    // Rendering Loop
    while (!glfwWindowShouldClose(window))
    {
        // Clear colour and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Draw your scene here
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

        // Handle other events
        glfwPollEvents();
        handleKeyboardInput(window);

        // Flip buffers
        glfwSwapBuffers(window);

        printGLError();
    }
    shader.deactivate();
    shader.destroy();
}


void handleKeyboardInput(GLFWwindow* window)
{
    // Use escape key for terminating the GLFW window
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}
