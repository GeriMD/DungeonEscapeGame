#include <iostream>
#include <fstream>
#include <random>
#include <cstdlib>
#include <windows.h>
#include <sstream>
#include <ctime>
#include <vector>
#include <string>

const int MAX_SIZE = 50;
const int LEVEL1_SIZE = 15;
const int LEVEL2_SIZE = 20;
const int LEVEL3_SIZE = 25;
const int LEVELS_COUNT = 3;

int lives;
int coins;
int level = 3;
int levelVersion;
bool key;
bool wasPortal = false;
char matrix[][MAX_SIZE];
int size;
char* playersName;

int startingRow; 
int startingCol;
int newRow;
int newCol;


void startingMessages()
{
    std::cout << "Welcome to Dungeon Escape!" << std::endl;
    std::cout << "To win the game you will have to escape a maze." << std::endl;
    std::cout << "There are 3 levels. Get through the leves succesfully and with maximum number of coins." << std::endl;
    std::cout << "Good luck!" << std::endl;
    std::cout << std::endl;
}
void explanationsMessages()
{
    std::cout << "@ - user" << std::endl;
    std::cout << "C - coin" << std::endl;
    std::cout << "# - wall [If you hit it, you lose a life. Be carefull!]" << std::endl;
    std::cout << "% - portal [Teleports you to the next portal.]" << std::endl;
    std::cout << "& - key [You need it to finish the level!]" << std::endl;
    std::cout << "X - chest [You open it with the key to win the level.]" << std::endl;
}
void checkBoard();
void readPlayerBoard(const char* filePath) //, char matrix[][MAX_SIZE], int size)
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

void printMatrix()//char matrix[][MAX_SIZE], int size)

{
    system("cls");
    std::cout << "Lives: " << lives << std::endl;
    std::cout << "Coins: " << coins << std::endl;
    std::cout << "Key: ";
    if (!key)
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
//made it const may cause a problem!!!
unsigned myStrlen(const char* str)
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
std::string convertToString(const char* str)
{
    std::string s = "";
    unsigned len = myStrlen(str);
    for (int i = 0; i < len; i++)
    {
        s += str[i];
    }
    return s;
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
void convertFromStringToCharArray(std::string string, char* str)
{
    int len = string.length();

    for (int i = 0; i < len; i++)
    {
        str[i] = string[i];
    }

}

bool playerFound(char* name)//, char* playersName)
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

int returnPlayerLevel()//char* playersName)
{
    char name[MAX_SIZE];

    int level = 0;

    std::ifstream inputFile;
    inputFile.open("Progress.txt");

    if (inputFile.is_open())
    {
        while (inputFile >> name)
        {
            if (playerFound(name)) //playersName))
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
  //  char playersName[MAX_SIZE];

    std::cout << "Please enter your name: " << std::endl;
    std::cin >> playersName;

    unsigned lenght = myStrlen(playersName);

    if (lenght > 50)
    {
        std::cout << "Name too long. Please enter valid name.";
        addNewPlayer();
    }
    int level = 0;

    if (level = returnPlayerLevel())//playersName))
    {

        std::cout << "Player " << playersName << " was found! Current level: " << level << std::endl;
    }
    else {

        std::ofstream outFileNames;
        std::ofstream outFileProgress;

        outFileNames.open("Names.txt", std::ios_base::app);
        outFileProgress.open("Progress.txt", std::ios_base::app);

        outFileNames << playersName << "\n";
        outFileProgress << playersName << " " << 1 << " " << 3 << " " << 74 << " " << false << "\n";
        

        std::cout << "Player " << playersName << " was added.\n";
        outFileNames.close();
        outFileProgress.close();

        char fileName[MAX_SIZE]{};

        char txt[] = ".txt\0";

        myStrcat(fileName, playersName);
        myStrcat(fileName, txt);

        std::ofstream player(fileName);
        player.close();
    }

    Sleep(100);
}
void getSize()
{
    switch (level)
    {
    case 1:
        size = LEVEL1_SIZE;
        break;
    case 2:
        size = LEVEL2_SIZE;
        break;
    case 3:
        size = LEVEL3_SIZE;
        break;
    }
}

void createPlayerBoard( int toOpen) //, char matrix[][MAX_SIZE])
{

    switch (toOpen)
    {
    case 10: readPlayerBoard("Level1.1.txt");//, matrix, LEVEL1_SIZE); 
        break;
    case 11: readPlayerBoard("Level1.2.txt");// , matrix, LEVEL1_SIZE);
        break;
    case 20: readPlayerBoard("Level2.1.txt");// , matrix, LEVEL2_SIZE);
        break;
    case 21: readPlayerBoard("Level2.2.txt");// , matrix, LEVEL2_SIZE);
        break;
    case 30: readPlayerBoard("Level3.1.txt");// , matrix, LEVEL3_SIZE);
        break;
    case 31: readPlayerBoard("Level3.2.txt");//, matrix, LEVEL3_SIZE); 
        break;
    }

}
bool isWall()//char matrix[][MAX_SIZE], int row, int col)
{
    return matrix[newRow][newCol] == '#';
}
bool isKey()//char matrix[][MAX_SIZE], int row, int col)
{
    return matrix[newRow][newCol] == '&';
}
bool isCoin()//char matrix[][MAX_SIZE], int row, int col)
{
    return matrix[newRow][newCol] == 'C';
}
bool isPortal()//char matrix[][MAX_SIZE], int row, int col)
{
    return matrix[newRow][newCol] == '%';
}
bool isChest()//char matrix[][MAX_SIZE], int row, int col)
{
    return matrix[newRow][newCol] == 'X';
}
bool isBlankSpace()
{
    return matrix[newRow][newCol] == '0';
}

//TODO: MAYBE MAKE THEM GLOBAL?
void movePlayer()//char* playersName, int& startingRow, int& startingCol, int size, char matrix[][MAX_SIZE])
{
    std::cout << "Please choose direction to go." << std::endl;
    std::cout << "Up[w/W], down[s/S], left[a/A], right[d/D] or exit[e/E] the game." << std::endl;
   
    newRow = startingRow;
    newCol = startingCol;

    char direction;
    std::cin >> direction;

    switch (direction)
    {
        //up
    case 'w':
    case 'W':  newRow--; break;
        //down
    case 's':
    case 'S': newRow++; break;
        //left
    case 'a':
    case 'A': newCol--; break;
        //right
    case 'd':
    case 'D': newCol++; break;
    case 'e':
    case 'E':
        Sleep(1000);
        saveProgress();//playersName);
            saveMap();// playersName, size, matrix);
            std::cout << "Thank you for playing!" << std::endl;
            Sleep(1000);
            exit(0);
        break;
    }
    checkBoard();
}
void makeMove(int row, int col)
{
    char ch;
    ch = matrix[row][col];
    matrix[row][col] = matrix[startingRow][startingCol];
    matrix[startingRow][startingCol] = ch;
    startingRow = row;
    startingCol = col;
}

void checkBoard()//char matrix[][MAX_SIZE], int row, int col, int size)
{
    if (isWall())//matrix, row, col))
    {
        lives--;
        if (lives == 0)
        {
            gameOver();
        }
    }
    else if (isCoin())//matrix, row, col))
    { 
        coins++;
        matrix[newRow][newCol] = '0';
        
        makeMove(newRow, newCol);
    }
    else if (isKey())//matrix, row, col))
    {
        
        key = true;
        matrix[newRow][newCol] = '0';

        makeMove(newRow, newCol);
    }
    else if (isPortal())//matrix, row, col))
    {
        matrix[newRow][newCol] = '0';

        makeMove(newRow, newCol);
        //TODO: findPortal();
    }
    else if (isChest())//matrix, row, col))
    {
        if (key)
        {
            matrix[newRow][newCol] = '0';

            makeMove(newRow, newCol);
            Sleep(1000);
            winGame();
        }
        else
        {
            std::cout << "You don't have the key to unlock the chest." << std::endl;
            Sleep(1000);
            printMatrix();// matrix, size);
           movePlayer();
        }
    }
    else if (isBlankSpace())
    {
        matrix[newRow][newCol] = '0';

        makeMove(newRow, newCol);
    }
}
bool isValidLevel()//int level)
{
    return (level > 0 && level <= LEVELS_COUNT);
}

void findPlayer()//char matrix[][MAX_SIZE], int size, int& startingRow, int& startingCol)
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
void findPortal()
{
    bool found = false;

    for (int i = startingRow; i < size; i++)
    {
        for (int j = startingCol; j < size; j++)
        {
            if (matrix[i][j] == '%')
            {
                found = true;
              
                matrix[i][j] = matrix[startingRow][startingCol];
                matrix[startingRow][startingCol ] = '%';
                wasPortal = true;
                break;
            }
        }
    }
    if (!found) 
    {
        for (int i = 0; i < size; i++) 
        {
            for (int j = 0; j < size; j++) 
            {
                if (matrix[i][j] == '%') 
                {
                    matrix[i][j] = matrix[startingRow][startingCol];
                    matrix[startingRow][startingCol] = '%';
                    wasPortal = true;
                    break;
                }
            }
        }
    }

}
//TODO
void start()
{
    int coins;
    int lives;
    bool key;
    char matrix[MAX_SIZE][MAX_SIZE]{};
    char direction;
    createPlayerBoard( 11); // matrix);
    printMatrix();// matrix, 15);
move:
    
    int startingRow = 1;
    int startingCol = 1;
    findPlayer();//matrix, 15, startingRow, startingCol);
    matrix[startingRow][startingCol] = ' ';
  //  movePlayer( startingRow, startingCol, 15);
    matrix[newRow][newCol] = '@';
    printMatrix();// matrix, 15);
    goto move;

}
bool hasProgress()//char* playersName)
{
    char name[MAX_SIZE];

    std::ifstream inputFile;
    inputFile.open("Progress.txt");

    if (inputFile.is_open())
    {
        while (inputFile >> name)
        {
            if (playerFound(name)) //playersName)
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
//TODO: MAY CAUSE A PROBLEM!!!
void saveProgress()//char* playersName)
{
    std::string strLives, strCoins, strLevel, strKey, strName;
    strLives = std::to_string(lives);
    strCoins = std::to_string(coins);
    strLevel = std::to_string(level);
    if (key)
    {
        strKey = "true";
    }
    else 
    {
        strKey = "false";
    }
    if (hasProgress())//playersName))
    {
        std::ifstream file("Progress.txt");

        if (!file.is_open())
        {
            std::cout << "Cannot open this file!" << std::endl;
        }
        else
        {
            std::vector<std::string> lines;
            std::string line;

            while (std::getline(file, line))
            {
                std::stringstream StringStream(line);
                std::string name;

                StringStream >> name;
                if (name == playersName)
                {
                    line = name + " " + strLevel + " " + strLives + " " + strCoins + " " + strKey;
                }
                lines.push_back(line);
            }
            file.close();

            std::ofstream outFile("Progress.txt", std::ofstream::trunc);
            if (!outFile)
            {
                std::cerr << "Cannot open this file!" << std::endl;
            }
            else
            {

                for (const auto& updatedLine : lines)
                {
                    outFile << updatedLine << std::endl;
                }
            }
            outFile.close();
        }

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
void replaceProgress(char* playersName)
{

}
void readProgress()//char* playersName)
{
    std::ifstream inputFile("Progress.txt");

    if (!inputFile.is_open())
    {
        std::cout << "Cannot open this file!" << std::endl;

    }

    bool found = false;
    found = hasProgress();//playersName);
    char name[MAX_SIZE];
    if (found)
    {
        while (inputFile >> name)
        {
            if (playerFound(name))//playersName))
            {
                inputFile >> level >> lives >> coins >> key;
                inputFile.close();
               
            }
        }
    }
    else
    {
        lives = 3;
        level = 1;
        coins = 0;
        key = false;
    }
  // std::cout << playersName << " " << level << " " << lives << " " << coins << " " << key << std::endl;
}
void begining()//char* playersName)
{
    readProgress();//playersName);


}
void readPlayersSavedMatrix()//char* playersName, char matrix[][MAX_SIZE], int size)
{
    std::string fileName = convertToString(playersName) + ".txt";
    char fileNameArr[MAX_SIZE]{};
    convertFromStringToCharArray(fileName, fileNameArr);
    readPlayerBoard(fileNameArr);// fileNameArr, matrix, size);
}
void saveMap()//char* playersName, int size, char matrix[50][50])
{
    std::string fileName = convertToString(playersName) + ".txt";

    std::ofstream outFile(fileName);

    if (!outFile.is_open())
    {
        std::cout << "Cannot open this file!" << std::endl;
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                outFile << matrix[i][j];
            }
            outFile << std::endl;
        }
    }
    outFile.close();

}

void chooseStartingMap()//char* playersName, char matrix[][MAX_SIZE], int& size)
{
    again:
    std::cout << "Do you want to continue[c/C] your last saved level, or start a new one[n/N]? " << std::endl;

    char answer;

    std::cin >> answer;

    switch (answer)
    {
    case 'c':
    case 'C':
    {
        
        level = returnPlayerLevel();//playersName);
       switch (level)
       {
       case 1:
           size = LEVEL1_SIZE;
           break;
       case 2:
           size = LEVEL2_SIZE;
           break;
       case 3:
           size = LEVEL3_SIZE;
           break;
       }
       readPlayersSavedMatrix();//playersName, matrix, size);
        lives = 3;
        coins = 0;
        key = false;
        printMatrix();// matrix, size);
    }
       
        break;
    case 'n':
    case 'N':
    {
        go:
        lives = 3;
        coins = 0;
        std::cout << "Please choose a level to play." << std::endl;

        int startingLevel;
        std::cin >> startingLevel;

        if (startingLevel <= level)
        {
            levelVersion = startingLevel * 10 + std::rand() % 2;
            key = false;
            level = startingLevel;
            createPlayerBoard(levelVersion); //matrix);
            printMatrix();//matrix, LEVEL3_SIZE);
        } 
        else
        {
            std::cout << "You cannot play a level you have never played. Your current level is: " << level << " " << std::endl;
            goto go;
        }
    }
        break;
    default:
        goto again;
        break;
    }
}
void winGame()
{
    std::srand(std::time(nullptr));

    if (level == LEVELS_COUNT)
    {
        system("cls");

        std::cout << "You won the game! You passed all the levels." << std::endl;

        Sleep(2000);
        exit(0);
    }
    else
    {
        level++;
        levelVersion = level * 10 + std::rand() % 2;
        key = false;
        saveProgress();

        
        std::cout << "You have passed the level! Do you want to continue with the next one?" << std::endl;
       again:
        std::cout << "Please answer yes[y/Y] or no[n/N]." << std::endl;

        
        char answer;
        std::cin >> answer;

        switch (answer)
        {
        case 'y':
        case 'Y':
            break;
        case 'n':
        case 'N':
            system("cls");

            std::cout << "Thank you for playing!" << std::endl;

            Sleep(100);
            exit(0);
            break;
        default:
            std::cout << "Wrong input!" << std::endl;
            goto again;
            break;
        }
    }
}

void gameOver()
    {
        system("cls");

        std::cout << "You don't have any lives left!" << std::endl;
        std::cout << "Do you want to try again? Please answer yes[y/Y] or no[n/N]." << std::endl;

        char answer;
        wrong:
        std::cin >> answer;

        switch (answer)
        {
        case 'y':
        case 'Y':
            lives = 3;
            coins = 0;
            key = false;

            //insertMatrix();
            //start();
            break;
        case 'n':
        case 'N':
            system("cls");
            std::cout << "Game over! Thank you for playing!" << std::endl;

            Sleep(1000);

            exit(0);
            break;
        default:
            std::cout << "Wrong input! Please try again." << std::endl;
            goto wrong;
        }



    }

int main()
{


  //  std::cout << "Welcome to Dungeon Escape!" << std::endl;
  //  std::cout << "Your task in this game is to escape from a maze with maximum coins." << std::endl;
  //  std::cout << "The game has 3 levels with different difficulty. Good luck!" << std::endl;
  //  addNewPlayer();

   // system("cls");
    char name[MAX_SIZE]{};
   std::cin >> name;

  // saveProgress(name);
  // readProgress(name);
    
    char matrix[50][50]{};
  //  createPlayerBoard(matrix, 21);
   // printMatrix(matrix, LEVEL2_SIZE);
    //std::cout << myStrlen("gerieqka");

   // std::cout << convertToString("gerigeri");
  //  saveMap(name, LEVEL2_SIZE, matrix);
  //  std::string s = "Geri e qka";
  //  convertFromStringToCharArray(s, name);

  //  for (int i = 0; i < 50; i++)
    //    std::cout << name[i] << " ";
   // readPlayersSavedMatrix(name, matrix, LEVEL2_SIZE);
    int size;
    chooseStartingMap();// name, matrix, size);
   
    return 0;
}