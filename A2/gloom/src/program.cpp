// Local headers
#include <vector>

#include <glm/ext.hpp>
#include "program.hpp"

#include "gloom/gloom.hpp"
#include "gloom/shader.hpp"

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

GLuint vaoGenWithColour(std::vector<float> vertices, std::vector<unsigned int> indices, std::vector<float> colours) {
    GLuint array;
    GLuint vbo_buffer;
    GLuint index_buffer;
    GLuint colour_buffer;

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

    // generate colour buffer
    glGenBuffers(1, &colour_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, colour_buffer);

    // load data into colour buffer
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(float)*colours.size(),
        colours.data(),
        GL_STATIC_DRAW
    );

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

    return array;
}

void runProgram(GLFWwindow* window)
{
    // Enable depth (Z) buffer (accept "closest" fragment)
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Configure miscellaneous OpenGL settings
    glEnable(GL_CULL_FACE);

    // Enable colour blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Set default colour after clearing the colour buffer
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // Set up your scene here (create Vertex Array Objects, etc.)
    glm::mat4x4 i = mat4(1.0f);
    glUniformMatrix4fv(7, 1, GL_FALSE, glm::value_ptr(i));

    std::vector<float> vertices = {
        /* a triangle */
        -0.4f,      0.8f,     0.0f,
        -0.5f,      0.6f,     0.0f,
        -0.2636f,   0.5763f,  0.0f,
        /* a triangle */
         0.1653f,   0.4515f,  0.0f,
         0.3487f,   0.4955f,  0.0f,
         0.1377f,   0.2166f,  0.0f,
        /* a triangle */
         0.4368f,  -0.3099f,  0.0f,
         0.3781f,  -0.2109f,  0.0f,
         0.3506f,  -0.2989f,  0.0f,
        /* a triangle */
        -0.5870f,  -0.2127f,  0.0f,
        -0.6237f,  -0.3448f,  0.0f,
        -0.4806f,  -0.2916f,  0.0f,
        /* a triangle */
        -0.1870f,   0.0772f,  0.0f,
        -0.2586f,  -0.1888f,  0.0f,
         0.0698f,  -0.1613f,  0.0f,
    };

    std::vector<float> colours = {
        /* a triangle */
        0.1647f, 0.8314f, 1.0f,    1.0f,
        0.1725f, 0.3529f, 0.6274f, 1.0f,
        0.9921f, 0.9921f, 0.9921f, 1.0f,
        /* a triangle */
        0.1647f, 0.8314f, 1.0f,    0.2f,
        0.1725f, 0.3529f, 0.6274f, 0.5f,
        0.9921f, 0.9921f, 0.9921f, 0.8f,
        /* a triangle */
        0.1647f, 0.8314f, 1.0f,    1.0f,
        0.1725f, 0.3529f, 0.6274f, 1.0f,
        0.9921f, 0.9921f, 0.9921f, 1.0f,
        /* a triangle */
        0.1647f, 0.8314f, 1.0f,    1.0f,
        0.1725f, 0.3529f, 0.6274f, 1.0f,
        0.9921f, 0.9921f, 0.9921f, 1.0f,
        /* a triangle */
        0.1647f, 0.8314f, 1.0f,    1.0f,
        0.1725f, 0.3529f, 0.6274f, 1.0f,
        0.9921f, 0.9921f, 0.9921f, 1.0f,
    };
    
    std::vector<unsigned int> indices = {0, 1, 2, 4, 3, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    GLuint test_vao = vaoGenWithColour(vertices, indices, colours);
    glBindVertexArray(test_vao);

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
