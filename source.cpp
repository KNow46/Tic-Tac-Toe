#include <iostream>
#include <conio.h>
#include <windows.h>


using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
const int squaresCount = 9;

class Square
{
private: 
	string owner;
public:
	Square()
	{
		owner = "none";
	}
	void setOwner(string name)
	{
		owner = name;
	}
	string getOwner()
	{
		return owner;
	}
};

class Board
{
private:
	int availablePlaces[squaresCount];
	Square squares[squaresCount];
	string playerTurn;
	bool draw;
public:

	Board() : squares()
	{
		draw = false;
		playerTurn = "X";
		for (int i = 0; i < squaresCount; i++)
		{
			availablePlaces[i] = i;
		}
		
	}
	string iswinner() 
	{
		//winning conditions horrizontaly
		if (squares[0].getOwner() == squares[1].getOwner() && squares[1].getOwner() == squares[2].getOwner())
			return squares[0].getOwner();
		else if (squares[3].getOwner() == squares[4].getOwner() && squares[4].getOwner() == squares[5].getOwner())
			return squares[3].getOwner();
		else if (squares[6].getOwner() == squares[7].getOwner() && squares[7].getOwner() == squares[8].getOwner())
			return squares[6].getOwner();
		//winning conditions perpendicularly
		else if (squares[0].getOwner() == squares[3].getOwner() && squares[3].getOwner() == squares[6].getOwner())
			return squares[0].getOwner();
		else if (squares[1].getOwner() == squares[4].getOwner() && squares[4].getOwner() == squares[7].getOwner())
			return squares[1].getOwner();
		else if (squares[2].getOwner() == squares[5].getOwner() && squares[5].getOwner() == squares[8].getOwner())
			return squares[2].getOwner();
		//winning conditions diagonally
		else if (squares[0].getOwner() == squares[4].getOwner() && squares[4].getOwner() == squares[8].getOwner())
			return squares[0].getOwner();
		else if (squares[2].getOwner() == squares[4].getOwner() && squares[4].getOwner() == squares[6].getOwner())
			return squares[2].getOwner();
		else
			return "none";
	}
	void printboard()
	{
		system("CLS");
		SetConsoleTextAttribute(hConsole, 3);
		cout << "+---------+\n";
		for (int i = 0; i < squaresCount; i++)
		{
			SetConsoleTextAttribute(hConsole, 3);
			if (i == 0 || i == 3 || i == 6)
				cout << "|";
			SetConsoleTextAttribute(hConsole, 7);
			if (squares[i].getOwner() == "none")
				cout << " "<<i<<" ";
			SetConsoleTextAttribute(hConsole, 9);
			if (squares[i].getOwner() == "O")
				cout << " O ";
			SetConsoleTextAttribute(hConsole, 12);
			if (squares[i].getOwner() == "X")
				cout << " X ";
			SetConsoleTextAttribute(hConsole, 3);
			if (i == 2 || i == 5 || i == 8)
				cout << "|\n";
			
		}
		cout << "+---------+\n";
	}
	string putChar()
	{
		int choice;
		bool wrongChoice = true;
		bool isdraw = true;
		for (int i = 0; i < squaresCount; i++)
		{
			if (availablePlaces[i] != -1)
				isdraw = false;
		}
		if (isdraw == true)
		{
			draw = true;
			return "draw";
		}
		do
		{
			printboard();

			cout << "Choose a square(";
			for (int i = 0; i < squaresCount; i++)
			{
				if (availablePlaces[i] != -1 && i != 8)
					cout << i << ", ";
				else if (availablePlaces[i] != -1)
					cout << i;
			}
			cout << "): ";

			while (scanf_s("%d", &choice) != 1 || choice < 0 || choice > 8 || getchar() != '\n')
			{
				cout << "\nWrong choice";
				Sleep(2000);
				while (getchar() != '\n')
					;
				printboard();
				for (int i = 0; i < squaresCount; i++)
				{
					if (availablePlaces[i] != -1 && i != 8)
						cout << i << ", ";
					else if (availablePlaces[i] != -1)
						cout << i;
				}
				cout << "): ";
			}

			for (int i = 0; i < squaresCount; i++)
			{
				if (choice == availablePlaces[i])
					wrongChoice = false;
			}
			if (wrongChoice == true)
			{
				cout << "\nWrong choice";
				Sleep(2000);
			}
			else
			availablePlaces[choice] = -1;
		} while (wrongChoice == true);
		squares[choice].setOwner(playerTurn);
		if (playerTurn == "O")
			playerTurn = "X";
		else
			playerTurn = "O";
		return iswinner();

	}
	string getPlayerTurn()
	{
		return playerTurn;
	}
	bool isDraw()
	{
		return draw;
	}
	void setPlayerTurn(string playerName)
	{
		playerTurn = playerName;
	}

};



int main()
{
	Board tab;
	
	while (tab.putChar() == "none")
	{
		//EMPTY BODY
	}
	tab.printboard();
	if (tab.isDraw() != true)
	{
		if (tab.getPlayerTurn() == "O")
			tab.setPlayerTurn("X");
		else
			tab.setPlayerTurn("O");
		cout << endl << "Player " << tab.getPlayerTurn() << " won the game";
	}
	else
		cout << endl << "DRAW";
	return 0;
}