#include <iostream>
#include <fstream>
#include <random>
#include <string>

const int MAX_SIZE = 50;
const int LEVEL1_SIZE = 15;
const int LEVEL2_SIZE = 20;
const int LEVEL3_SIZE = 25;


void readPlayerBoard(const char* filePath, char matrix[][MAX_SIZE], int size)
{
	if (!filePath)
	{
		return;
	}

	std::ifstream ifs(filePath);

	if (!ifs.is_open())
	{
		return;
	}

	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			ifs >> matrix[i][j];
		}
	}

	ifs.close();
}

void printMatrix(char matrix[][MAX_SIZE], int size)
{
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (matrix[i][j] == '0')
			{
				std::cout << " ";
			}
			else
			{
				std::cout << matrix[i][j];
			}


		}
		std::cout << std::endl;
	}
}

unsigned myStrlen(char* str)
{
	if (!str)
	{
		return 0;
	}

	unsigned counter = 0;

	while (*str)
	{
		counter++;
		str++;
	}

	return counter;
}

void myStrcpy(const char* source, char* dest)
{
	if (!source || !dest)
		return;

	while (*source)
	{
		*dest = *source;
		dest++;
		source++;
	}

	*dest = '\0';
}

void myStrcat(char* first, const char* second)
{
	if (!first || !second)
		return;

	size_t firstLen = myStrlen(first);
	first += firstLen;
	myStrcpy(second, first);
}

bool playerFound( char* playersName, char* name)
{
	while (*name != '\0' && *playersName != '\0')
	{
		if (*name != *playersName)
		{
			return false;
		}
		name++;
		playersName++;
	}
	return (*playersName == '\0' && *name == '\0');
}

int returnPlayerLevel(char* playersName)
{
	char name[MAX_SIZE];

	int level = 0;

	std::ifstream inputFile;
	inputFile.open("Names.txt");

	if (inputFile.is_open())
	{
		while (inputFile >> name)
		{
			if (playerFound(playersName, name))
			{
				inputFile >> level;
				inputFile.close();
				return level;
			}
		}
	}
	else
	{
		std::cout << "Coudn't open the file.\n";
	}
	inputFile.close();
	return 0;
}

void addNewPlayer()
{
	char playersName[MAX_SIZE];

	std::cout << "Please enter your name: " << std::endl;
	std::cin >> playersName;

	unsigned lenght = myStrlen(playersName);

	if (lenght > 50)
	{
		std::cout << "Name too long. Please enter valid name.";
		addNewPlayer();
	}
	int level = 0;

	if (level = returnPlayerLevel(playersName))
	{

		std::cout << "Player " << playersName << " was found! Current level: " << level << std::endl;
	}
	else {

		std::ofstream outFile;

		outFile.open("Names.txt", std::ios_base::app);

		outFile << playersName << " 1\n";

		std::cout << "Player " << playersName << " was added.\n";
		outFile.close();

		char fileName[MAX_SIZE]{};

		char txt[] = ".txt\0";

		myStrcat(fileName, playersName);
		myStrcat(fileName, txt);

		std::ofstream player(fileName);
		//int startingLevel = 1;
		//int startingLives = 3;
		//bool keyFound = false;
		//player << "level: " << startingLevel << std::endl;
		//player << "lives: " << startingLives << std::endl;
		//player << "Key: " << keyFound << std::endl;
		player.close();
	}
}

void createPlayerBoard(char matrix[][MAX_SIZE], int toOpen)
{

	switch (toOpen)
	{
	case 10: readPlayerBoard("Level1.1.txt", matrix, LEVEL1_SIZE); break;
	case 11: readPlayerBoard("Level1.2.txt", matrix, LEVEL1_SIZE); break;
	case 20: readPlayerBoard("Level2.1.txt", matrix, LEVEL2_SIZE); break;
	case 21: readPlayerBoard("Level2.2.txt", matrix, LEVEL2_SIZE); break;
	case 30: readPlayerBoard("Level3.1.txt", matrix, LEVEL3_SIZE); break;
	case 31: readPlayerBoard("Level3.2.txt", matrix, LEVEL3_SIZE); break;
	}

}
bool isInTheBoudaries(int size, int row, int col)
{
	return (row >= 0 && row < size) && (col >= 0 && col < size);
}

void movePlayer(char direction, int& startingRow, int& startingCol, int size)
{
	switch (direction)
	{
		//up
	case 'w':
	case 'W':
		if (isInTheBoudaries(size, startingRow - 1, startingCol)) {
			startingRow--;
		}
		else
		{
			std::cout << "You cannot make that move. You are trying to go out of the playing board.";
		}
		
		break;
		//down
	case 's':
	case 'S':
		if (isInTheBoudaries(size, startingRow + 1, startingCol)) {
			startingRow++;
		}
		else
		{
			std::cout << "You cannot make that move. You are trying to go out of the playing board.";
		}
		break;
		//left
	case 'a':
	case 'A':
		if (isInTheBoudaries(size, startingRow, startingCol - 1)) {
			startingCol--;
		}
		else
		{
			std::cout << "You cannot make that move. You are trying to go out of the playing board.";
		}
		break;
		//right
	case 'd':
	case 'D':
		if (isInTheBoudaries(size, startingRow, startingCol + 1)) {
			startingCol++;
		}
		else
		{
			std::cout << "You cannot make that move. You are trying to go out of the playing board.";
		}
		break;
	}
}

bool hasSavedProgress(char* playersName)
{
	std::ifstream inFile;

	inFile.open(playersName);

	int num = 0;
	if (inFile.is_open())
	{
		inFile >> num;
	 }
	return (num != 0); // true - има прогрес, false - няма прогрес
}
void savePlayersProgress(char* playersName, int lives, char matrix[][MAX_SIZE], int size, int coins, bool keyFound)
{
	std::ofstream outFile;

	outFile.open(playersName);

	if (outFile.is_open())
	{
		outFile << lives << " " << coins << " " << keyFound << std::endl;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				outFile << matrix[i][j];
			}
			outFile << std::endl;
		}
	}
	else {
		std::cout << "Cannot open this file!" << std::endl;
	}

	outFile.close();
}

int readPlayersProgress(char* playersName, char matrix[][MAX_SIZE], int size)
{
	int coins;
	int lives;
	bool keyFound;

	std::ifstream inFile;
	inFile.open(playersName);

	if (inFile.is_open())
	{
		inFile >> lives;
		inFile >> coins;
		inFile >> keyFound;

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				inFile >> matrix[i][j];
			}
		}
	}
	else
	{
		std::cout << "Cannot open this file!" << std::endl;
	}
	inFile.close();

	return lives;
}
void startGame(char* playersName, char matrix[][MAX_SIZE], int size)
{
	int level = 1;
	int lives = 3;
	int maxLevel = returnPlayerLevel(playersName);
	char choice;

	if (hasSavedProgress)
	{
		std::cout << "Do you want to continue your saved level or start a new one? Please answer yes[y/Y] or no[n/N]" << std::endl;
		std::cin >> choice;
	}


}

int main()
{
	

	std::cout << "Welcome to Dungeon Escape!" << std::endl;
	addNewPlayer();
	 
	int level = 1;
	

	
	//char matrix[MAX_SIZE][MAX_SIZE]{};

	//createPlayerBoard( matrix, 31);

	//printMatrix(matrix, LEVEL3_SIZE);
	

	return 0;
}