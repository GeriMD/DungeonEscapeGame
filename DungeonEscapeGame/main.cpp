#include <iostream>
#include <fstream>
#include <random>
#include <cstdlib>
#include <windows.h>
#include <sstream>
#include <ctime>

const int MAX_SIZE = 50;
const int LEVEL1_SIZE = 15;
const int LEVEL2_SIZE = 20;
const int LEVEL3_SIZE = 25;
const int LEVELS_COUNT = 3;

int lives;
int coins;
int level;
int levelVersion;
bool key;


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
    system("cls");
    int coins = 0;
    int lives = 3;
    bool key = false;
    std::cout << "Lives: " << lives << std::endl;
    std::cout << "Coins: " << coins << std::endl;
    std::cout << "Key: ";
    if (key)
    {
        std::cout << "not found" << std::endl;
    }
    else
    {
        std::cout << "found" << std::endl;
    }
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

bool playerFound(char* playersName, char* name)
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

    Sleep(100);
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
bool isNotAWall(char matrix[][MAX_SIZE], int row, int col)
{
    return matrix[row][col] != '#';
}
bool isKey(char matrix[][MAX_SIZE], int row, int col)
{
    return matrix[row][col] == '&';
}
bool isCoin(char matrix[][MAX_SIZE], int row, int col)
{
    return matrix[row][col] == 'C';
}
bool isPortal(char matrix[][MAX_SIZE], int row, int col)
{
    return matrix[row][col] == '%';
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

bool isValidLevel(int level)
{
    return (level > 0 && level <= LEVELS_COUNT);
}

void findPlayer(char matrix[][MAX_SIZE], int size, int& startingRow, int& startingCol)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (matrix[i][j] == '@')
            {
                startingRow = i;
                startingCol = j;
            }
        }
    }
}

void start()
{
    int coins;
    int lives;
    bool key;
    char matrix[MAX_SIZE][MAX_SIZE]{};
    char direction;
    createPlayerBoard(matrix, 11);
    printMatrix(matrix, 15);
move:
    std::cout << "Please choose a direction: " << std::endl;

    std::cin >> direction;
    int startingRow = 1;
    int startingCol = 1;
    findPlayer(matrix, 15, startingRow, startingCol);
    matrix[startingRow][startingCol] = ' ';
    movePlayer(direction, startingRow, startingCol, 15);
    matrix[startingRow][startingCol] = '@';
    printMatrix(matrix, 15);
    goto move;

}
bool hasProgress(char* playersName)
{
    char name[MAX_SIZE];

    std::ifstream inputFile;
    inputFile.open("Progress.txt");

    if (inputFile.is_open())
    {
        while (inputFile >> name)
        {
            if (playerFound(playersName, name))
            {

                inputFile.close();
                return true;
            }
        }
    }
    else
    {
        std::cout << "Coudn't open the file.\n";
    }
    inputFile.close();
    return false;
}

void saveProgress(char* playersName)
{
    if (hasProgress(playersName))
    {

    }
    else
    {
        std::ofstream outFile("Progress.txt", std::ios::app);
        if (!outFile.is_open())
        {
            std::cout << "Cannot open the file!";
            return;
        } 

        outFile << playersName << " " << level << " " << lives << " " << coins << " " << key << std::endl;
        outFile.close();

    }
}

int main()
{


    std::cout << "Welcome to Dungeon Escape!" << std::endl;
    std::cout << "Your task in this game is to escape from a maze with maximum coins." << std::endl;
    std::cout << "The game has 3 levels with different difficulty. Good luck!" << std::endl;
   // addNewPlayer();

   // system("cls");
    char name[MAX_SIZE]{};
    std::cin >> name;
    lives = 3;
    coins = 77;
    level = 5;
    key = false;
    saveProgress(name);

    return 0;
}