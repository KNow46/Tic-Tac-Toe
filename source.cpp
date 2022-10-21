#include <iostream>
#include <conio.h>
#include <windows.h>


using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

class square
{
private: 
	string owner;
public:
	square()
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

class board
{
public:
	string playerTurn;
	square squares[9];
	board() : squares()
	{}
	string iswinner() 
	{
		//winning conditions
		if (squares[0].getOwner() == squares[1].getOwner() && squares[1].getOwner() == squares[2].getOwner())
			return squares[0].getOwner();
		else if (squares[3].getOwner() == squares[4].getOwner() && squares[4].getOwner() == squares[5].getOwner())
			return squares[0].getOwner();
		else if (squares[6].getOwner() == squares[7].getOwner() && squares[7].getOwner() == squares[8].getOwner())
			return squares[0].getOwner();
		else if (squares[0].getOwner() == squares[4].getOwner() && squares[4].getOwner() == squares[8].getOwner())
			return squares[0].getOwner();
		else if (squares[2].getOwner() == squares[4].getOwner() && squares[4].getOwner() == squares[6].getOwner())
			return squares[0].getOwner();
		else
			return "none";
	}
	void printboard()
	{
		system("CLS");
		SetConsoleTextAttribute(hConsole, 3);
		cout << "+---------+\n";
		for (int i = 0; i < 9; i++)
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
	void put
	

};



int main()
{
	board tab;
	tab.printboard();
	return 0;
}