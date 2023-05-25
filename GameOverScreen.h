#pragma once
#include "InterfaceObject.h"
#include "StartButton.h"
#include "HighscoresButton.h"
#include <vector>
#include <fstream>

class GameOverScreen : public InterfaceObject
{
public:
	GameOverScreen(int x, int y, int width, int height, std::string texturePath, std::string textureHoveredPath,StartButton* startButton, HighscoresButton* highscoresButton, std::vector<InterfaceObject*>& allInterfaceObjects, bool& isGameLost, int &points)
		:InterfaceObject(x, y, width, height, texturePath, textureHoveredPath), isGameLost(isGameLost), allInterfaceObjects(allInterfaceObjects), startButton(startButton), highscoresButton(highscoresButton)
	{
		std::ifstream file("HighScores.txt");
		std::string line;
	
		if (file.is_open())
		{
			int i = 0;
			while (std::getline(file, line)) 
			{
				highscores[i] = std::stoi(line);
				i++;
			}
		}

		allInterfaceObjects.push_back(new Text(windowWidth / 2-25, windowHeight * 0.48, 300, 100, std::to_string(points), 13, Text::none));
		
		int whereChangeHighScore = 0;
		for (int i = 0; i < 5; i++)
		{ 
			if (points > highscores[i])
			{
				break;
			}
			whereChangeHighScore++;
		}

		int lastValue = highscores[whereChangeHighScore];
		for (int i = whereChangeHighScore +1; i < 5; i++)
		{
			int lastValue2 = highscores[i];
			highscores[i] = lastValue;
			lastValue = lastValue2;
		}

		if (whereChangeHighScore < 5)
			highscores[whereChangeHighScore] = points;

		
		std::ofstream outputFile("HighScores.txt");

		if (outputFile.is_open()) 
		{ 
			for (int i = 0; i < 5; i++)
			{
				outputFile <<  std::to_string(highscores[i])<< std::endl;
			}
			outputFile.close(); 
			
		}
		else 
		{
			std::cout << "Can't open a file" << std::endl;
		}
		points = 0;
	}

	void onClick()
	{
		while (!allInterfaceObjects.empty())
		{
			if (allInterfaceObjects.back() != this)
			{
				delete allInterfaceObjects.back();
			}
			allInterfaceObjects.pop_back();
		}

		isGameLost = false;
		startButton->setIsGameStarted(false);
		allInterfaceObjects.push_back(startButton);
		allInterfaceObjects.push_back(highscoresButton);

		delete this;
	}


private:
	StartButton* startButton;;
	HighscoresButton* highscoresButton;
	bool& isGameLost;
	std::vector<InterfaceObject*>& allInterfaceObjects;
	int highscores[5];
};