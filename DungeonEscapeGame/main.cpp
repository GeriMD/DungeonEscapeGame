#include <iostream>
#include <fstream>
#include <random>

const int MAX_SIZE = 50;
const int LEVEL1_SIZE = 15;
const int LEVEL2_SIZE = 20;
const int LEVEL3_SIZE = 25;


void readPlayerBoard(const char* filePath, char matrix[][MAX_SIZE], int rows, int cols)
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

	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			ifs >> matrix[i][j];
		}
	}

	ifs.close();
}

void printMatrix(char matrix[][MAX_SIZE], int rows, int cols)
{
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
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

void addNewPlayer(char* playersName)
{
	unsigned lenght = myStrlen(playersName);

	if (lenght > 50)
	{
		std::cout << "Please enter valid name.";
			return;
	}

	std::ofstream outFile;

	outFile.open("Names.txt", std::ios_base::app);

	outFile << playersName << "1\n";

	std::cout << "Player " << playersName << " was added.\n";
	outFile.close();

	char fileName[MAX_SIZE]{};

	char txt[] = ".txt\0";

	myStrcat(fileName, playersName);
	myStrcat(fileName, txt);

	std::ofstream player(fileName);
	player.close();
}

bool playerFound(const char* playersName, const char* name)
{
	while (!name && !playersName)
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

int main()
{

	char playersName[MAX_SIZE] = "";

	std::cout << "Welcome to Dungeon Escape! Enter players name: ";

	std::cin >> playersName;

	int level = 1;
	
	/*
	char matrix[MAX_SIZE][MAX_SIZE]{};

	readPlayerBoard("Level1.1.txt", matrix, 15, 15);

	printMatrix(matrix, 15, 15);
	*/

	return 0;
}