#include <iostream>
#include <GLFW/glfw3.h>

int main()
{
  GLFWwindow* window;

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
  but there are other libraries who make this available for you
  */
  glfwMakeContextCurrent(window);

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window))
  {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    glVertex2f(-1, -1);
    glVertex2f(0, 1);
    glVertex2f(1, -1);
    glEnd();
    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }
}