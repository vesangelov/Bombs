#include <iostream>
#include <vector>
#include <string>

std::vector<std::vector<int>> readInput(const int& matrixSize)
{
    std::vector<std::vector<int>> matrix;

    for (size_t row = 0; row < matrixSize; ++row)
    {
        std::vector<int> rowSide;

        int index = 0;

        for (size_t col = 0; col < matrixSize; ++col)
        {
            std::cin >> index;
            rowSide.push_back(index);
        }

        matrix.push_back(rowSide);
    }

    return matrix;
}

void printMatrix(std::vector<std::vector<int>>& matrix)
{

    for(const auto& currentRow : matrix)
    {
        for(const auto& current : currentRow)
        {
            std::cout << current << " ";
        }

        std::cout << std::endl;
    }
}

std::string readIndexes()
{

    std::string indexes;

    char symbol = '_';

    for (size_t i = 0; i < 3; ++i)
    {
        std::cin >> symbol;
        indexes += symbol;
    }

    return indexes;
}

void findIndexes(std::string& indexes, int& rowIndex, int& colIndex)
{

    std::string current;

    for (size_t i = 0; i < indexes.size(); ++i)
    {

         current = indexes[i];

        if(i == 0)
        {
            rowIndex = std::stoi(current);
        }

        if(i == 2)
        {
            colIndex = std::stoi(current);
        }
    }
}

std::vector<std::pair<int, int>> readBombs()
{

    std::vector<std::pair<int, int>> bombIndexes;

    int rowIndex = 0;
    int colIndex = 0;

    std::string indexes;

    for (size_t i = 0; i < 3; ++i)
    {

        indexes = readIndexes();
        findIndexes(indexes, rowIndex, colIndex);

        bombIndexes.emplace_back(rowIndex, colIndex);

    }

    return bombIndexes;
}

void explosions(std::vector<std::vector<int>>& matrix, const int& bombRowIndex, const int& bombColIndex){

    int bombPower = matrix[bombRowIndex][bombColIndex];

    if(bombRowIndex - 1 >= 0 && matrix[bombRowIndex - 1][bombColIndex] > 0)   //up row
    {
        matrix[bombRowIndex - 1][bombColIndex] -= bombPower;
    }

    if(bombRowIndex + 1 < matrix.size() && matrix[bombRowIndex + 1][bombColIndex] > 0)   //down row
    {
        matrix[bombRowIndex + 1][bombColIndex] -= bombPower;
    }

    if(bombColIndex - 1 >= 0 && matrix[bombRowIndex][bombColIndex - 1] > 0)   //left col
    {
        matrix[bombRowIndex][bombColIndex - 1] -= bombPower;
    }

    if(bombColIndex + 1 < matrix.size() && matrix[bombRowIndex][bombColIndex + 1] > 0)   //right col
    {
        matrix[bombRowIndex][bombColIndex + 1] -= bombPower;
    }

    if(bombRowIndex - 1 >= 0 && bombColIndex - 1 >= 0 && matrix[bombRowIndex - 1][bombColIndex - 1] > 0)   //up row left col
    {
        matrix[bombRowIndex - 1][bombColIndex - 1] -= bombPower;
    }

    if(bombRowIndex + 1 < matrix.size() && bombColIndex - 1 >= 0 && matrix[bombRowIndex + 1][bombColIndex - 1] > 0)   //down row left col
    {
        matrix[bombRowIndex + 1][bombColIndex - 1] -= bombPower;
    }

    if(bombRowIndex - 1 >= 0 && bombColIndex + 1 < matrix.max_size() && matrix[bombRowIndex - 1][bombColIndex + 1] > 0)   //up row right col
    {
        matrix[bombRowIndex - 1][bombColIndex + 1] -= bombPower;
    }

    if(bombRowIndex + 1 < matrix.size() && bombColIndex + 1 < matrix.max_size() && matrix[bombRowIndex + 1][bombColIndex + 1] > 0)   //down row down col
    {
        matrix[bombRowIndex + 1][bombColIndex + 1] -= bombPower;
    }

    matrix[bombRowIndex][bombColIndex] = 0;
}


void takeBombsIndexes(std::vector<std::pair<int, int>>& bombIndexes, std::vector<std::vector<int>>& matrix){

    int bombRowIndex;
    int bombColIndex;

    for(const auto& bomb : bombIndexes)
    {
        bombRowIndex = bomb.first;
        bombColIndex = bomb.second;

        explosions(matrix, bombRowIndex, bombColIndex);
    }
}

void findAndSumAliveCells(std::vector<std::vector<int>>& matrix, int& aliveCells, int& sumFromAliiveCells)
{

    for(const auto& currentRow : matrix)
    {
        for(const auto& current : currentRow)
        {
            if(current > 0){
                aliveCells++;
                sumFromAliiveCells += current;
            }
        }
    }
}

void printResultFromExplosions(std::vector<std::vector<int>>& matrix)
{
    int sumFromAliiveCells = 0;
    int aliveCells = 0;
    findAndSumAliveCells(matrix, aliveCells, sumFromAliiveCells);

    std::cout << "Alive cells: " << aliveCells << std::endl;
    std::cout << "Sum: " << sumFromAliiveCells << std::endl;

    printMatrix(matrix);
}

int main() {

    int matrixSize = 0;

    std::cin >> matrixSize;

    std::vector<std::vector<int>> matrix = readInput(matrixSize);

    std::vector<std::pair<int, int>> bombIndexes = readBombs();

    takeBombsIndexes(bombIndexes, matrix);

    printResultFromExplosions(matrix);

    return 0;
}
