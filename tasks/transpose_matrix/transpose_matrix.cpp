#include "transpose_matrix.h"

Matrix transpose(const Matrix& matrix)
{
    if(matrix.empty() || matrix[0].empty())
        return Matrix{};

    std::size_t rows = matrix.size();
    std::size_t cols = matrix[0].size();

    Matrix transposedMatrix;
    transposedMatrix.reserve(cols);

    for(std::size_t i = 0; i < cols; i++)
    {
        transposedMatrix.push_back(Row(rows));
        for(std::size_t j = 0; j < rows; j++)
            transposedMatrix[i][j] = matrix[j][i];
    }

    return transposedMatrix;
}
