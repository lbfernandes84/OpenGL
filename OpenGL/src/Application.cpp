#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/*
OpenGL is a state machine. This means all iteration with the framework is througth states. This is different from getting an object and, 
for instance, call a function like "DrawTriangle(trObject blablabla)". Basically, OpenGL must be aware of selecting data before and 
iterate with it
*/
int main()
{
  GLFWwindow* window = nullptr;  
  /* Initialize the library */  
  if (!glfwInit())
    return -1;

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  /* 
  Make the window's context current - 
  This is very important once to have the OpenGL functions available
  you must create a valid context. The bellow function is comming from GLFW
  but there are other libraries who also make this available for you
  */  
  glfwMakeContextCurrent(window);
  GLenum errorNumber = glewInit();
  if (errorNumber == GLEW_OK)
  {
    float bufferData[6] = {
      -0.5f, -0.5f,
       0.0f, 0.5f,
       0.5f, 0.5f,
    };

    //--------------------------------------------------------------------------------------------------------------------------
    /*--Generate buffer:
    The way as the GPU process data is throught buffers. You must tell OpenGL you are intend to use them. For that, 
    the function void glGenBuffers(	GLsizei n,GLuint *buffers); is that one who specifies how many buffers you are intend to do.
    The first paremeter is the number of buffers is going to be used
    The second parameter is a pointer of unsigned int(s) with the id's of the buffers that is going to be used 
    */
    unsigned int bufferID;
    glGenBuffers(1, &bufferID);
    /*
    You can update the buffer wherever you want. All iteration with OpenGL is dependent of ID's, buffers, arrays, shaders, etc.
    */
    //--------------------------------------------------------------------------------------------------------------------------
    //--Bind buffer:
    //To select which buffer is going to be used in OpenGL, the function void glBindBuffer(GLenum target,GLuint buffer); is called.
    //The first parameter is an enum option who determines what kind of buffer must be selected. For vertex we use GL_ARRAY_BUFFER
    //The second parameter is the buffer id

    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    //--------------------------------------------------------------------------------------------------------------------------
    //-- Set data for the buffer
    //After tell OpenGL which buffer we should use, its necessary to put data into it. You can pass your data once you know what 
    //is going to be used but also you can pass the data as you process runs.
    //This is our case considering we already have created a triangle in bufferID. Following is the function used to do that
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), bufferData, GL_STATIC_DRAW);
    
    //void glBufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage);
    //Parameters:
    //GLenum target: Same as glBindBuffer
    //GLsizeiptr size: Size of buffer to alocate data in bytes
    //GLenum usage: An enum with one of the following options:
    //  GL_STREAM_DRAW: The data store contents will be modified once and used at most a few times.
    //  GL_STATIC_DRAW: The data store contents will be modified once and used many times. That is most adequate when the data will be static and drawn every frame
    //  GL_DYNAMIC_DRAW: The data store contents will be modified repeatedly and used many times. That is most adequate when the data will be changed and drawn every frame
    //--------------------------------------------------------------------------------------------------------------------------
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
      /* Render here */
      glClear(GL_COLOR_BUFFER_BIT);
      //--Draw buffer
      //This is a simple way of drawing buffers:
      //The first parameter is the type of buffer
      //Second parameter the index in array where it starts
      //Third parameter is the number of elements in the buffer
      glDrawArrays(GL_TRIANGLES, 0, 3);
      /* Swap front and back buffers */
      glfwSwapBuffers(window);

      /* Poll for and process events */
      glfwPollEvents();
    }
  }
  glfwTerminate();
  return 0;
}