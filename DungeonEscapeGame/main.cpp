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