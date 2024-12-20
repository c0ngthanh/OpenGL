#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <Shader/Shader.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
using namespace std;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float offset = 0.5f;
int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    Shader ourShader = Shader("VertexShader.txt", "FragmentShader.txt"); // you can name your shader files however you like

    // build and compile our shader program
    // ------------------------------------
    
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
    -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f     ,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f     ,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f     ,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f     ,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f     ,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f     ,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f     ,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f     ,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f     ,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f     ,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f     ,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f     ,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f     ,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f     ,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f     ,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f     ,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 0.0f     ,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f     ,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f     ,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f     ,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f     ,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f     ,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 0.0f     ,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f     ,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f     ,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f     ,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f     ,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f     ,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 0.0f     ,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f     ,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f     ,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f     ,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f     ,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f     ,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f     ,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f     ,  0.0f, 1.0f
};
    unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
    }; 

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

   // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    // glBindVertexArray(0);
    //Load texture
    unsigned int texture1,texture2;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // load and generate the texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load("Resource/wall.jpg", &width, &height, &nrChannels, 0);
    // std::cout << stbi_failure_reason();
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    stbi_set_flip_vertically_on_load(true);
    data = stbi_load("Resource/cudamsamset.png", &width, &height, &nrChannels, 0);
    // std::cout << stbi_failure_reason();
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    stbi_image_free(data);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // render loop
    // -----------
    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);
    //Transform
    // glm::mat4 trans = glm::mat4(1.0f);
    // trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
    // trans = glm::scale(trans, glm::vec3(1.3, 1.3, 1.3)); 
    unsigned int modelMatrix = glGetUniformLocation(ourShader.ID, "model");
    unsigned int viewMatrix = glGetUniformLocation(ourShader.ID, "view");
    unsigned int projectionMatrix = glGetUniformLocation(ourShader.ID, "projection");
    // glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
    glEnable(GL_DEPTH_TEST); 
    glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f), 
    glm::vec3( 2.0f,  5.0f, -15.0f), 
    glm::vec3(-1.5f, -2.2f, -2.5f),  
    glm::vec3(-3.8f, -2.0f, -12.3f),  
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-1.7f,  3.0f, -7.5f),  
    glm::vec3( 1.3f, -2.0f, -2.5f),  
    glm::vec3( 1.5f,  2.0f, -2.5f), 
    glm::vec3( 1.5f,  0.2f, -1.5f), 
    glm::vec3(-1.3f,  1.0f, -1.5f)  
    };
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // render the triangle
        ourShader.use();
        // ourShader.setInt("texture1", 0);
        // ourShader.setInt("texture2", 1);
        // glBindVertexArray(VAO);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        ourShader.setFloat("offset",offset);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glBindVertexArray(VAO);
        // glm::mat4 trans = glm::mat4(1.0f);
        // trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
        // trans = glm::scale(trans, glm::vec3(sin(glfwGetTime())+1,sin(glfwGetTime())+1,sin(glfwGetTime())+1));
        // glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glm::mat4 trans2 = glm::mat4(1.0f);
        // trans2 = glm::translate(trans2, glm::vec3(0.5f, -0.5f, 0.0f));
        // trans2 = glm::rotate(trans2, (float)glfwGetTime()*3, glm::vec3(0.0f, 0.0f, 1.0f));
        // glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans2));
        // glm::mat4 model = glm::mat4(1.0f);
        // model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        glm::mat4 view = glm::mat4(1.0f);
        // note that we're translating the scene in the reverse direction of where we want to move
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 
        
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f); 

        // glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionMatrix, 1, GL_FALSE, glm::value_ptr(projection));
        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            if(i%3==0){
                float angle = (20.0f + i*5) * (float)glfwGetTime();
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f+i, 0.3f+i, 0.5f+i));
            }
            glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, glm::value_ptr(model));

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        //DRAW
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_TRIANGLES,0, 36);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if(glfwGetKey(window,GLFW_KEY_UP) == GLFW_PRESS){
        offset += 0.0001f;
        if(offset>=1){
            offset =1;
        }
    }
    if(glfwGetKey(window,GLFW_KEY_DOWN) == GLFW_PRESS){
        offset -= 0.0001f;
        if(offset<=0){
            offset=0;
        }
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}