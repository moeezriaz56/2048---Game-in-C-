#include<iostream>			

#include<string>			

#include<conio.h>			
							
#include<fstream>			

#include<stdlib.h>			
							
#include<ctime>

using namespace std;

const int m = 4;
const int n = 4;
int Array[m][n];
int score = 0, maxscore, moves = 0, rem_moves = 0;
bool lost = 0;

void initialization();
void board();
void up();
void moveup();
void down();
void movedown();
void left();
void moveleft();
void right();
void moveright();
bool winner();
void UpdateHighestScore();
bool up_down_check();
bool left_right_check();
void generate_random();
void display();

int main()
{
	system("color E4");			
	
	int n, j;
	char option = ' ';
	char input;					
	int start = 0;

	while (true)
	{
		system("cls");
		display();			
		
		if (start == 0)		
		{
			while (option != 'n')			
			{
				option = _getch();			
				
				initialization();			
				
				score = 0;							
				moves = 0;
				
				for (int a = 0; a <= 1; a++)		
				{
					n = rand() % 4;					
					j = rand() % 4;
					Array[n][j] = 2;
				}
				start++;
			}
		}
		
		UpdateHighestScore();
		board();

		input = _getch();

		if (input == 72)
		{
			up();
		}
		else if (input == 80)
		{
			down();
		}
		else if (input == 75)
		{
			left();
		}
		else if(input == 77)
		{
			right();
		}
		else if(input ==  's')
		{
			while (input != 'r')
			{
				system("cls");
				cout << "Game Paused!!" << endl;
				cout << "Press r To Resume Game" << endl;

				input = _getch();

				if (input == 'r')
				{
					break;
				}
			}
		}
		else if(input == 'q')
		{
			break;
		}
		else if (score >= 15000)
		{
			system("cls"); 
			cout << endl << endl << endl;
			cout << "\t\t\t\tYou Reach Maximum Score Limit!!!" << endl;
			break;
		}
		else if (moves == 1500)
		{
			system("cls");
			cout << endl << endl << endl;
			cout << "\t\t\t\tYou Reach Maximum Move Limit!!!" << endl;
			break;
		}
		else if (winner())
		{
			system("cls");
			cout << endl << endl << endl << endl << endl;
			cout << "\t\t\t\t\t " << " +===========================+ " << endl;
			cout << "\t\t\t\t\t " << " |      CONGRATULATIONS      | " << endl;
			cout << "\t\t\t\t\t " << " |      YOU WON THE GAME     | " << endl;
			cout << "\t\t\t\t\t " << " +===========================+   " << endl;
			cout << endl << endl << endl;
			break;
		}
		else if (up_down_check())
		{
			system("cls");
			cout << endl << endl << endl << endl << endl;
			cout << "\t\t\t\t\t " << " +===========================+ " << endl;
			cout << "\t\t\t\t\t " << " |           ALAS!           | " << endl;
			cout << "\t\t\t\t\t " << " |      YOU LOSE THE GAME    | " << endl;
			cout << "\t\t\t\t\t " << " +===========================+   " << endl;
			cout << endl << endl << endl;
			break;
		}
	}
}
		

void UpdateHighestScore(){
	{
		if (score > maxscore)
		{
			maxscore = score;
			ofstream out;
			out.open("maxscore.txt");
			out << maxscore;
			out.close();
		}
		ifstream in;
		in.open("maxscore.txt");
		in >> maxscore;
		in.close();

	}
}


void display()
{
	cout << "\t\t\t\t\t\t" << "+===============+" << endl;
	cout << "\t\t\t\t\t\t" << "| THE 2048 GAME |" << endl;
	cout << "\t\t\t\t\t\t" << "+===============+" << endl;
	cout << endl;
	cout << "\t\t\t\t\t" << "+===============================+" << endl;
	cout << "\t\t\t\t\t\t" << "   SCORE: " << score << endl;
	cout << "\t\t\t\t\t\t" << "   MOVES: " << moves << endl;
	cout << "\t\t\t\t\t" << "     REMAINING MOVES: " << (1500 - moves) << endl;
	cout << "\t\t\t\t\t" << "     HIGHEST SCORE: " << maxscore << endl;
	cout << "\t\t\t\t\t" << "+===============================+" << endl;
	cout << endl;
	cout << "\t\t\t\t\t\t" << " [ INSTRUCTIONS ]" << endl;
	cout << endl;
	cout << "\t\t\t\t" << "--MOVE AND JOIN THE NUMBERS TO GET TO THE 2048 TILE !" << endl;
	cout << "\t\t\t\t" << "--USE ARROW KEYS FOR THE MOVEMENT OF THE NUMBERS THROUGH TILES !" << endl << endl << endl;
	cout << "\t\t\t\t" << "--PRESS  (n)  TO START  THE NEW GAME !" << endl;
	cout << "\t\t\t\t" << "--PRESS  (s)  TO PAUSE  THE GAME !" << endl;
	cout << "\t\t\t\t" << "--PRESS  (r)  TO RESUME THE PAUSED GAME !" << endl;
	cout << "\t\t\t\t" << "--PRESS  (q)  TO QUIT   THE GAME !" << endl;
	cout << endl << endl;
}


void initialization()
{
	for (int i = 0; i <= 3; i++)
	{
		for (int j = 0; j <= 3; j++)
		{
			Array[i][j] = 0;
		}
	}
}


void moveup()
{
	for (int col = 0; col <= 3; col++)
	{
		for (int count = 0; count <= 3; count++)
		{
			if (Array[0][col] == 0)
			{
				Array[0][col] = Array[1][col];
				Array[1][col] = 0;
			}
			if (Array[1][col] == 0)
			{
				Array[1][col] = Array[2][col];
				Array[2][col] = 0;
			}
			if (Array[2][col] == 0)
			{
				Array[2][col] = Array[3][col];
				Array[3][col] = 0;
			}
		}
	}
}

void up()
{
	moveup();

	for (int col = 0; col <= 3; col++)
	{
		if (Array[0][col] == Array[1][col])
		{
			Array[0][col] = Array[1][col] + Array[0][col];
			Array[1][col] = 0;
			score += Array[0][col];
		}
		if (Array[1][col] == Array[2][col])
		{
			Array[1][col] = Array[1][col] + Array[2][col];
			Array[2][col] = 0;
			score += Array[1][col];
		}
		if (Array[2][col] == Array[3][col])
		{ 
			Array[2][col] = Array[3][col] + Array[2][col];
			Array[3][col] = 0;
			score += Array[2][col];
		}
	}

	moveup();
	moves++;
	generate_random();
	board();
}

void movedown()
{

	for (int col = 0; col <= 3; col++)
	{
		for (int count = 0; count <= 3; count++)
		{
			if (Array[3][col] == 0)
			{
				Array[3][col] = Array[2][col];
				Array[2][col] = 0;
			}
			if (Array[2][col] == 0)
			{
				Array[2][col] = Array[1][col];
				Array[1][col] = 0;
			}
			if (Array[1][col] == 0)
			{
				Array[1][col] = Array[0][col];
				Array[0][col] = 0;
			}
		}
	}

}

void down()
{
	movedown();

	for (int col = 0; col <= 3; col++)
	{
		if (Array[3][col] == Array[2][col])
		{
			Array[3][col] = Array[2][col] + Array[3][col];
			Array[2][col] = 0;
			score += Array[3][col];
		}
		if (Array[2][col] == Array[1][col])
		{
			Array[2][col] = Array[2][col] + Array[1][col];
			Array[1][col] = 0;
			score += Array[2][col];
		}
		if (Array[1][col] == Array[0][col])
		{
			Array[1][col] = Array[1][col] + Array[0][col];
			Array[0][col] = 0;
			score += Array[1][col];
		}
	
	}

	movedown();
	moves++;
	generate_random();
	board();
}

void moveleft()
{

	for (int row = 0; row <= 3; row++)
	{
		for (int count = 0; count <= 3; count++)
		{
			if (Array[row][0] == 0)
			{
				Array[row][0] = Array[row][1];
				Array[row][1] = 0;
			}
			if (Array[row][1] == 0)
			{
				Array[row][1] = Array[row][2];
				Array[row][2] = 0;
			}
			if (Array[row][2] == 0)
			{
				Array[row][2] = Array[row][3];
				Array[row][3] = 0;
			}
		}
	}

}

void left()
{
	moveleft();
	for (int row = 0; row <= 3; row++)
	{

		if (Array[row][0] == Array[row][1])
		{
			Array[row][0] += Array[row][1];
			Array[row][1] = 0;
			score = score + Array[row][0];
		}
		if (Array[row][1] == Array[row][2])
		{
			Array[row][1] += Array[row][2];
			Array[row][2] = 0;
			score += Array[row][1];
		}
		if (Array[row][2] == Array[row][3])
		{
			Array[row][2] += Array[row][3];
			Array[row][3] = 0;
			score = score + Array[row][2];
		}
	}

	moveleft();
	moves++;
	generate_random();
	board();
}

void moveright()
{
	for (int row = 0; row <= 3; row++)
	{

		for (int count = 0; count <= 3; count++)
		{
			if (Array[row][3] == 0)
			{
				Array[row][3] = Array[row][2];
				Array[row][2] = 0;
			}
			if (Array[row][2] == 0)
			{
				Array[row][2] = Array[row][1];
				Array[row][1] = 0;
			}
			if (Array[row][1] == 0)
			{
				Array[row][1] = Array[row][0];
				Array[row][0] = 0;
			}
		}
	}

}

void right()
{
	moveright();
	for (int col = 3; col >= 3; col--)
	{
		for (int row = 0; row <= 3; row++)
		{
			if (Array[row][3] == Array[row][2])
			{
				Array[row][3] += Array[row][2];
				Array[row][2] = 0;
				score = score + Array[row][3];
			}
			if (Array[row][2] == Array[row][1])
			{
				Array[row][2] += Array[row][1];
				Array[row][1] = 0;
				score += Array[row][2];
			}
			if (Array[row][1] == Array[row][0])
			{
				Array[row][1] += Array[row][0];
				Array[row][0] = 0;
				score = score + Array[row][1];
			}
		}
	}
	moveright();
	moves++;
	generate_random();
	board();
}
void generate_random()
{
	int p = 0, y = 0, twofour;
	if (moves < 1500)
	{
		for (int i = 0; i < 16; i++)
		{
			p = rand() % 4;
			y = rand() % 4;
			twofour = rand() % 4;
			if (twofour >= 2)
			{
				if (Array[p][y] == 0)
				{
					Array[p][y] = 2;
					i = 16;
				}
			}
			else
			{
				if (Array[p][y] == 0)
				{
					Array[p][y] = 4;
					i = 16;
				}
			}
		}
	}
	else
	{
		lost = 1;
	}
}


void board()
{

	system("cls");
	display();
	for (int row = 0; row <= 3; row++)
	{
		cout << "\t\t\t\t\t";
		for (int col = 0; col <= 3; col++)
		{
			if (Array[row][col] == 0)
			{
				cout << "|       |";
			}
			else
			{
				if (Array[row][col] < 10)
				{
					cout << "|   " << Array[row][col] << "   |";
				}
				else if (Array[row][col] < 100)
				{
					cout << "|  " << Array[row][col] << "   |";
				}
				else if (Array[row][col] < 1000)
				{
					cout << "|  " << Array[row][col] << "  |";
				}
				else if (Array[row][col] < 10000)
				{
					cout << "| " << Array[row][col] << "  |";
				}
				else
				{
					cout << "| " << Array[row][col] << " |";
				}
			}
		}
		cout << endl;
	}
}


bool winner()
{
	bool win = false;
	for (int row = 0; row <= 3; row++)
	{
		for (int col = 0; col <= 3; col++)
		{
			if (Array[row][col] >= 2048)
			{
				win = true;
				return win;
			}
			else
			{
				win = false;
			}
		}
	}
	return win;
}

bool up_down_check()
{
	int a = 0, b = 0, c = 0;
	bool ans;
	for (int row = 0; row <= 3; row++)
	{
		for (int col = 0; col <= 3; col++)
		{
			if (Array[row][col] != 0)
			{
				a++;
			}
		}
	}
	if (a == 16)
	{

		for (int col = 0; col <= 3; col++)
		{
			if (Array[0][col] != Array[1][col])
			{
				b++;
			}
			if (Array[1][col] != Array[2][col])
			{
				b++;
			}
			if (Array[2][col] != Array[3][col])
			{
				b++;
			}
		}

	}



	if (b == 12)
	{
		bool ans= true;
		bool ans2 = left_right_check();
		if (ans = ans2)
		{
			return ans;
		}
	}

	else
	{
		ans = false;
		return ans;
	}
}

bool left_right_check()
{
	int a = 0, b = 0;
	bool ans3;

	for (int row = 0; row <= 3; row++)
	{
		if (Array[row][3] != Array[row][2])
		{
			a++;
		}
		if (Array[row][2] != Array[row][1])
		{
			a++;
		}
		if (Array[row][1] != Array[row][0])
		{
			a++;
		}
	}

	if (a == 12)
	{
		ans3 = true;
		return ans3;
	}
	else
	{
		ans3 = false;
		return ans3;
	}
}