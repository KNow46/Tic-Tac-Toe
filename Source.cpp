#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "Global.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "GameObject.h"
#include "Image.h"
#include "InterfaceObject.h"


//transforms to range (-1,1)
//if transforming point set length to 0
//(isX == 1) if you are transforming x coordinate
float transformToOpenGl(const float &position, const float &length, const bool &isX)
{
    float result = 0.0f;
    if (isX == false)
    {
        result = -((position + length / 2.0) / windowHeight * 2.0 - 1.0);
    }
    else
    {
        result = (position + length / 2.0) / windowWidth * 2.0 - 1.0;
    }
    return result;
}

void rendererScene(std::vector<InterfaceObject*>sceneObjects, Renderer& renderer, Shader& shader, VertexArray& va, VertexBuffer& vb, VertexBufferLayout& layout, IndexBuffer& ib, GLFWwindow* window)
{
    for (int i = 0; i < sceneObjects.size(); i++)
    {
        if (sceneObjects[i]->getIsDestroyed() == false)
        {
            float positionsTransformed[] = {
            transformToOpenGl(sceneObjects[i]->getX(), 0, 1),  transformToOpenGl(sceneObjects[i]->getY() + sceneObjects[i]->getHeight(),0,0), 0.0f, 0.0f,
            transformToOpenGl(sceneObjects[i]->getX() + sceneObjects[i]->getWidth(), 0, 1) , transformToOpenGl(sceneObjects[i]->getY() + sceneObjects[i]->getHeight(),0,0), 1.0f, 0.0f,
            transformToOpenGl(sceneObjects[i]->getX() + sceneObjects[i]->getWidth(), 0, 1) , transformToOpenGl(sceneObjects[i]->getY(), 0, 0) , 1.0f, 1.0f,
             transformToOpenGl(sceneObjects[i]->getX(), 0, 1), transformToOpenGl(sceneObjects[i]->getY(), 0, 0), 0.0f, 1.0f
            };

           vb.changeData(positionsTransformed, 4 * 4 * sizeof(float));
;           
            sceneObjects[i]->getTexture()->Bind(1);

            renderer.Draw(va, ib, shader);

        }
    }	
}


void clearDestroyed(std::vector <GameObject*>& allSceneObjects)
{
    std::vector<GameObject*> newAllSceneObjects;

    for(int i = allSceneObjects.size(); i > 0; i--)
    {
        if (allSceneObjects[i-1]->getIsDestroyed() == false)
        {
            newAllSceneObjects.push_back(allSceneObjects[i-1]);
        }
    }
    for (int i = allSceneObjects.size(); i > 0; i--)
    {
        allSceneObjects.pop_back();
    }
    for (int i = newAllSceneObjects.size(); i > 0; i--)
    {
        allSceneObjects.push_back(newAllSceneObjects[i-1]);
    }
  
}


struct UserData
{
    std::vector<InterfaceObject*>* allInterfaceObjects;

    UserData(std::vector<InterfaceObject*>* objects) : allInterfaceObjects(objects) {}
};

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        void* userPointer = glfwGetWindowUserPointer(window);
        if (UserData* userData = static_cast<UserData*>(userPointer))
        {
            
            for (int i = 0; i < userData->allInterfaceObjects->size(); i++)
            {
 
                if (xpos > (*userData->allInterfaceObjects)[i]->getX() && xpos < (*userData->allInterfaceObjects)[i]->getX() + (*userData->allInterfaceObjects)[i]->getWidth())
                {
                    if (ypos > (*userData->allInterfaceObjects)[i]->getY() && ypos < (*userData->allInterfaceObjects)[i]->getY() + (*userData->allInterfaceObjects)[i]->getHeight())
                    {
                        (*userData->allInterfaceObjects)[i]->onClick();
                        break;
                    }
                }
                
            }
            
        }
       
    }
}


void hoverInterfaceObjects(int x, int y, std::vector<InterfaceObject*>& allInterfaceObjects)
{
    
    for (int i = 0; i < allInterfaceObjects.size(); i++)
    {
        if (x > allInterfaceObjects[i]->getX() && x < allInterfaceObjects[i]->getX() + allInterfaceObjects[i]->getWidth() && y > allInterfaceObjects[i]->getY() && y < allInterfaceObjects[i]->getY() + allInterfaceObjects[i]->getHeight())
        {
            allInterfaceObjects[i]->setIsHovered(true);
        }
        else
        {
            allInterfaceObjects[i]->setIsHovered(false);
        }
    }
}
int main(void)
{

    std::vector<InterfaceObject*> allInterfaceObjects;

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(windowWidth, windowHeight, "Arkanoid", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "glew error";
    else
        std::cout << "glew initialized properly\n";

    std::cout << glGetString(GL_VERSION);

	
        float positions[] = {
            -1.0f, -1.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 0.0f, 1.0f
        };
        unsigned int indicies[] = {
            0,1,2,
            2,3,0
        };

        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glEnable(GL_BLEND));

        VertexArray va;
        VertexBuffer vb(positions, 4 * 4  * sizeof(float));

        VertexBufferLayout layout;

        layout.Push<float>(2);
        layout.Push<float>(2);

        va.AddBuffer(vb, layout);
        IndexBuffer ib(indicies, 6);
        Shader shader("res/shaders/Basic.shader");
        Renderer renderer;

		shader.Bind();
		shader.SetUniform1i("u_Texture", 1);


        UserData userData(&allInterfaceObjects);
        

        glfwSetWindowUserPointer(window, &userData);


        glfwSetMouseButtonCallback(window, mouse_button_callback);

        double xpos, ypos;


 
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {

                glfwGetCursorPos(window, &xpos, &ypos);
   
                
                hoverInterfaceObjects(xpos, ypos, allInterfaceObjects);
               
                renderer.Clear();
              
   
                rendererScene(allInterfaceObjects, renderer, shader, va, vb, layout, ib, window);



                /* Swap front and back buffers */
                GLCall(glfwSwapBuffers(window));
            


            /* Poll for and process events */
            GLCall(glfwPollEvents());
        }
    glfwTerminate();
    return 0;
}
