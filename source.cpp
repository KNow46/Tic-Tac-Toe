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
		SetConsoleTextAttribute(hConsole, 112);
		cout << "+---------+\n";
		for (int i = 0; i < 9; i++)
		{
			if (i == 0 || i == 3 || i == 6)
				cout << "|";

			if (squares[i].getOwner() == "none")
				cout << " "<<i<<" ";
			if (squares[i].getOwner() == "O")
				cout << " O ";
			if (squares[i].getOwner() == "X")
				cout << " X ";
			if (i == 2 || i == 5 || i == 8)
				cout << "|\n";
			
		}
		cout << "+---------+\n";
	}
	~board()
	{
		//delete [] squares;
	}

};



int main()
{
	board tab;
	tab.printboard();
	return 0;
}