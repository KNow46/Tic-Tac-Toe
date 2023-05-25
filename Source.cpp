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
#include "Cell.h"


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

Symbol checkWin(const std::vector<Cell*>& cells)
{
    for (int i = 0; i < 3; ++i)
    {
        if (cells[i * 3]->getSymbol() == cells[i * 3 + 1]->getSymbol() &&
            cells[i * 3]->getSymbol() == cells[i * 3 + 2]->getSymbol() &&
            cells[i * 3]->getSymbol() != Symbol::Empty)
        {
            return cells[i * 3]->getSymbol();
        }
    }

    for (int i = 0; i < 3; ++i)
    {
        if (cells[i]->getSymbol() == cells[i + 3]->getSymbol() &&
            cells[i]->getSymbol() == cells[i + 6]->getSymbol() &&
            cells[i]->getSymbol() != Symbol::Empty)
        {
            return cells[i]->getSymbol();
        }
    }

    if ((cells[0]->getSymbol() == cells[4]->getSymbol() &&
        cells[0]->getSymbol() == cells[8]->getSymbol() &&
        cells[0]->getSymbol() != Symbol::Empty) ||
        (cells[2]->getSymbol() == cells[4]->getSymbol() &&
            cells[2]->getSymbol() == cells[6]->getSymbol() &&
            cells[2]->getSymbol() != Symbol::Empty))
    {
        return cells[4]->getSymbol();
    }

    return Symbol::Empty;
}

struct UserData
{
    std::vector<InterfaceObject*>* allInterfaceObjects;
    std::vector<Cell*>* cells;
    UserData(std::vector<InterfaceObject*>* objects, std::vector<Cell*>* cells) : allInterfaceObjects(objects), cells(cells) {}
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
void generateCells(std::vector<Cell*>& cells, std::vector<InterfaceObject*>& allInterfaceObjects, Symbol& whoseTurn)
{
    for (int i = 0; i < 3; i++)
    {
        cells.push_back(new Cell(i * windowWidth / 3, 0, windowWidth / 3, windowHeight / 3, whoseTurn));
    }
    for (int i = 0; i < 3; i++)
    {
        cells.push_back(new Cell(i * windowWidth / 3, windowHeight / 3, windowWidth / 3, windowHeight / 3, whoseTurn));
    }
    for (int i = 0; i < 3; i++)
    {
        cells.push_back(new Cell(i * windowWidth / 3, windowHeight / 3 * 2, windowWidth / 3, windowHeight / 3, whoseTurn));
    }
    for (int i = 0; i < 9; i++)
    {
        allInterfaceObjects.push_back(cells[i]);
    }
}


int main(void)
{

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(windowWidth, windowHeight, "Tic-Tac-Toe", NULL, NULL);
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

        std::vector<InterfaceObject*> allInterfaceObjects;



        glfwSetMouseButtonCallback(window, mouse_button_callback);

        double xpos, ypos;

        Symbol whoseTurn = Symbol::Cross;

        std::vector<Cell*> cells;

        generateCells(cells, allInterfaceObjects, whoseTurn);

        UserData userData(&allInterfaceObjects, &cells);


        glfwSetWindowUserPointer(window, &userData);
 
        int waitCounter = 0;
        bool isGameOver = false;

        
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            bool areAllCellsBlocked = true;
            for (int i = 0; i < 9; i++)
            {
                if (cells[i]->getSymbol() == Symbol::Empty)
                {
                    areAllCellsBlocked = false;
                }
            }
            if (isGameOver == false)
            {
                if (checkWin(cells) == Symbol::Circle)
                {
                    isGameOver = true;
                    std::cout << "zzz";
                }
                else if (checkWin(cells) == Symbol::Cross)
                {
                    isGameOver = true;
                    std::cout << "aaaa";
                }
                else if (areAllCellsBlocked)
                {
                    isGameOver = true;
                    std::cout << "iii";
                }

                glfwGetCursorPos(window, &xpos, &ypos);

                renderer.Clear();

                rendererScene(allInterfaceObjects, renderer, shader, va, vb, layout, ib, window);

                /* Poll for and process events */
                GLCall(glfwPollEvents());
            }
            else
            {
                waitCounter++;
                if (waitCounter > 300)
                {
                    isGameOver = false;
                    for (int i = 0; i < 9; i++)
                    {
                        cells[i]->setSymbol(Symbol::Empty);
                    }
                    waitCounter = 0;
                }
            }
            /* Swap front and back buffers */
            GLCall(glfwSwapBuffers(window));

        }
    glfwTerminate();
    return 0;
}
