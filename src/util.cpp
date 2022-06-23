#include <sstream>
#include "trekscii.h"


size_t GetManhattanDist(size_t x1, size_t y1, size_t x2, size_t y2) {
    return (abs(x1 - x2) + abs(y1 - y2));
}


std::vector<std::vector<char>> LiteralToMat(std::string literal)
{
    std::stringstream ss(literal);
    std::string line;

    std::vector<std::vector<char>> mat;

    while (std::getline(ss, line, '\n'))
        mat.push_back(std::vector<char>(line.begin(), line.end()));

    return mat;
}


/**
 * Convert jagged matrix to square, get horiz dimension of mat
 */
size_t Squarify(std::vector<std::vector<char>>& mat)
{
    int maxLength = 0;

    for (std::vector<char> row : mat)
        if (row.size() > maxLength) maxLength = row.size();

    for (int i = 0; i < mat.size(); i++)
        while (mat[i].size() < maxLength)
            mat[i].push_back(' ');

    return maxLength;
}


// Reverse a 2d matrix & swap resversible chars
void Reverse(std::vector<std::vector<char>>& mat)
{
    for (int i = 0; i < mat.size(); i++)
        std::reverse(mat[i].begin(), mat[i].end());
    

    // eww
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[i].size(); j++) {
            switch (mat[i][j]) {
                case '/': {
                    mat[i][j] = '\\';
                    break;
                }
                case '\\': {
                    mat[i][j] = '/';
                    break;
                }
                case '(': {
                    mat[i][j] = ')';
                    break;
                }
                case ')': {
                    mat[i][j] = '(';
                    break;
                }
                case '[': {
                    mat[i][j] = ']';
                    break;
                }
                case ']': {
                    mat[i][j] = '[';
                    break;
                }
                case '{': {
                    mat[i][j] = '}';
                    break;
                }
                case '}': {
                    mat[i][j] = '{';
                    break;
                }
            }
        }
    }
}


// Overlay one matrix onto another
void Overlay(std::vector<std::vector<std::string>>& base, const std::vector<std::vector<char>>& overlay, int x, int y, std::string color)
{
    for (int i = 0; i < overlay.size(); i++)
    {
        for (int j = 0; j < overlay[i].size(); j++)
        {
            if (overlay[i][j] == 'a') base[y + i][x + j] = ' ';
            else if (overlay[i][j] != ' ') base[y + i][x + j] = color +"\x1b[1m" + std::string(1, overlay[i][j]) + "\x1b[0m";
        }
    }
}
