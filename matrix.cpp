#include "matrix.h"
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

Matrix::Matrix()
{
    noOfRows = 0;
    noOfCols = 0;
    arraySize = 0;
    isRowMajorOrderIndexed = true;
    array = NULL;
}

Matrix::Matrix(const int noOfRows, const int noOfCols, const bool isRowMajorOrderIndexed)
{
    this->noOfRows = noOfRows;
    this->noOfCols = noOfCols;
    this->isRowMajorOrderIndexed = isRowMajorOrderIndexed;
    this->arraySize = noOfRows * noOfCols;
    array = new double[arraySize];
    for (int i = 0; i < arraySize; i++)
        array[i] = 0.0;
}

Matrix::Matrix(const Matrix& other)
{
    noOfRows = other.noOfRows;
    noOfCols = other.noOfCols;
    arraySize = other.arraySize;
    isRowMajorOrderIndexed = other.isRowMajorOrderIndexed;
    array = new double[arraySize];
    for (int i = 0; i < arraySize; i++)
        array[i] = other.array[i];
}

Matrix& Matrix::operator=(const Matrix& other)
{
    if (this != &other)
    {
        delete[] array;
        noOfRows = other.noOfRows;
        noOfCols = other.noOfCols;
        arraySize = other.arraySize;
        isRowMajorOrderIndexed = other.isRowMajorOrderIndexed;
        array = new double[arraySize];
        for (int i = 0; i < arraySize; i++)
            array[i] = other.array[i];
    }
    return *this;
}

Matrix::~Matrix()
{
    delete[] array;
    array = NULL;
}

double Matrix::get(const int i) const
{
    if (i < 0 || i >= arraySize)
        return 0;
    return array[i];
}

void Matrix::set(const int i, const double value)
{
    if (i >= 0 && i < arraySize)
        array[i] = value;
}

double Matrix::get(const int i, const int j) const
{
    if (i < 0 || j < 0 || i >= noOfRows || j >= noOfCols)
        return 0;
    int index;
    if (isRowMajorOrderIndexed)
        index = i * noOfCols + j;
    else
        index = j * noOfRows + i;
    return array[index];
}

void Matrix::set(const int i, const int j, const double value)
{
    if (i < 0 || j < 0 || i >= noOfRows || j >= noOfCols)
        return;
    int index;
    if (isRowMajorOrderIndexed)
        index = i * noOfCols + j;
    else
        index = j * noOfRows + i;
    array[index] = value;
}

Matrix Matrix::getTranspose(const Matrix& m) const
{
    Matrix t(m.noOfCols, m.noOfRows, m.isRowMajorOrderIndexed);
    for (int i = 0; i < m.noOfRows; i++)
        for (int j = 0; j < m.noOfCols; j++)
            t.set(j, i, m.get(i, j));
    return t;
}

Matrix Matrix::operator+(const Matrix& other) const
{
    if (noOfRows != other.noOfRows || noOfCols != other.noOfCols)
        return Matrix();
    Matrix r(noOfRows, noOfCols, isRowMajorOrderIndexed);
    for (int i = 0; i < arraySize; i++)
        r.array[i] = array[i] + other.array[i];
    return r;
}

Matrix Matrix::operator-(const Matrix& other) const
{
    if (noOfRows != other.noOfRows || noOfCols != other.noOfCols)
        return Matrix();
    Matrix r(noOfRows, noOfCols, isRowMajorOrderIndexed);
    for (int i = 0; i < arraySize; i++)
        r.array[i] = array[i] - other.array[i];
    return r;
}

Matrix Matrix::operator*(const Matrix& other) const
{
    if (noOfCols != other.noOfRows)
        return Matrix();
    Matrix r(noOfRows, other.noOfCols, isRowMajorOrderIndexed);
    for (int i = 0; i < noOfRows; i++)
    {
        for (int j = 0; j < other.noOfCols; j++)
        {
            double sum = 0;
            for (int k = 0; k < noOfCols; k++)
                sum += get(i, k) * other.get(k, j);
            r.set(i, j, sum);
        }
    }
    return r;
}

Matrix Matrix::operator*(const double scalar) const
{
    Matrix r(noOfRows, noOfCols, isRowMajorOrderIndexed);
    for (int i = 0; i < arraySize; i++)
        r.array[i] = array[i] * scalar;
    return r;
}

double Matrix::getDeterminant() const
{
    if (noOfRows != noOfCols)
        return 0;
    if (noOfRows == 1)
        return array[0];
    if (noOfRows == 2)
        return array[0] * array[3] - array[1] * array[2];

    double det = 0;
    for (int p = 0; p < noOfCols; p++)
    {
        Matrix minor(noOfRows - 1, noOfCols - 1, isRowMajorOrderIndexed);
        for (int i = 1; i < noOfRows; i++)
        {
            int colIndex = 0;
            for (int j = 0; j < noOfCols; j++)
            {
                if (j == p) continue;
                minor.set(i - 1, colIndex, get(i, j));
                colIndex++;
            }
        }
        double sign = (p % 2 == 0) ? 1 : -1;
        det += sign * get(0, p) * minor.getDeterminant();
    }
    return det;
}

void Matrix::print() const
{
    for (int i = 0; i < noOfRows; i++)
    {
        for (int j = 0; j < noOfCols; j++)
            cout << fixed << setprecision(3) << get(i, j) << " ";
        cout << endl;
    }
}

void Matrix::printMatrixSize() const
{
    cout << noOfRows << "x" << noOfCols << endl;
}
