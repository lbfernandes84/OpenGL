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
    //How to interpret buffers:  
    //The first thing we must clarify is what a vertex is. For OpenGL, a vertex is a point of the geometry which is going to be presented on the screen
    //This points on the screen can be more than just positions,it could me more than that, for example, textures, normals and etc
    //With that in mind, we need to tell OpenGL how the buffer of memory must be interpretaded telling what parts of buffer represents. 
    //We can do it with the function bellow. This function defines how attributes of vertex are separated.
    //
    //void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer);
    //
    // In order to understand how define the attributes of our vertex, lets simulate a buffer which is an array of floats like drawn below:
    //float vertex[27]:
    //|_|_|_|_|_|_|_|_|_|||_|_|_|_|_|_|_|_|_|||_|_|_|_|_|_|_|_|_||
    //Coords|Text.|Norm.||Coords|Text.|Norm.||Coords|Text.|Norm.||
    //So a vertex are composed by:
    //- Three coordinates (Coords)
    //- Three texture points(Text.)
    //- Three normals points(Norm.)
    //So in the array above we have 3 vertex.
    //Fixing the example lets examinate what parameters we must set to define attributes
    //- GLuint index: The index on the buffer of the attribute, in our case 0
    //- GLint size: Is nothing to do with size of the attribute in bytes, this the count of how many components that attribute has
    //  * The size is a value between 1-4. Example: As we are defining a 2-coordinates attribute, this value is 2
    //  * If we are using an rgba attribute this value would be 4
    //- GlEnum Type: The type of each component of attribute, for our case is float (Check flags in documentation)
    //- GlEnum normalized: A flag if our vertex attribute is normalized (between 0 and 1). For our case GL_FALSE (See flags in documentation)
    //- GlEnum stride: This is the number in bytes of how much data must be read to get next attribute
    //  *In that hipotetic array of floats we have 3 * float coords(12 bytes) + 3 * float texture (12 bytes) + 3 * float normals (12 bytes) = 36 bytes
    //  *In our array we have just the coordinates so, to get the next attribute(positions)we set a stride as 2 floats(8 bytes)
    //- GlEnum pointer: Especifies what position in the buffer the attribute starts
    //  *In the example array, as the first coordinate is the first position on that, the value for that parameter is 0
    //  *If instead coordinates, we are defining the normals as attribute, this value would be 6
    //    + This parameter must be a pointer, so for values different than 0 it must be cast as void(*)

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    
    //For each attribute we must call the function
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