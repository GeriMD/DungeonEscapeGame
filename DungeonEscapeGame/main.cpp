#include <iostream>
#include <fstream>

const int MAX_SIZE = 100;

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


int main()
{
	char matrix[MAX_SIZE][MAX_SIZE]{};

	readPlayerBoard("Level1.1.txt", matrix, 15, 15);

	printMatrix(matrix, 15, 15);

	return 0;
}