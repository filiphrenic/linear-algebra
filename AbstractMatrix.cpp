//
// Created by Filip Hrenic on 12/03/16.
//

#include <cassert>
#include <string>
#include <cmath>

#include "AbstractMatrix.h"
#include "MatrixTransposeView.h"
#include "MatrixSubmatrixView.h"
#include "VectorMatrixView.h"

using namespace std;

IMatrix* AbstractMatrix::nTranspose(bool liveView) {
    IMatrix* matrix = this;
    if (!liveView) matrix = this->copy();
    return new MatrixTransposeView(matrix);
}

IMatrix* AbstractMatrix::add(IMatrix* matrix) {
    return this->linearOperation(matrix, 1, 1);
}

IMatrix* AbstractMatrix::nAdd(IMatrix* matrix) {
    return this->copy()->add(matrix);
}

IMatrix* AbstractMatrix::sub(IMatrix* matrix) {
    return this->linearOperation(matrix, 1, -1);
}

IMatrix* AbstractMatrix::nSub(IMatrix* matrix) {
    return this->copy()->sub(matrix);
}

IMatrix* AbstractMatrix::nMultiply(IMatrix* matrix) {
    assert(this->getColsCount() == matrix->getRowsCount());

    int rows = this->getRowsCount();
    int cols = matrix->getColsCount();
    IMatrix* product = this->newInstance(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            double value = 0;
            for (int k = 0; k < this->getColsCount(); ++k) {
                value += this->get(i, k) * matrix->get(k, j);
            }
            product->set(i, j, value);

        }
    }

    return product;
}

IMatrix* AbstractMatrix::scalarMultiply(double a) {
    return this->linearOperation(this, a, 0);
}

double AbstractMatrix::determinant() {

    int n = this->getRowsCount();
    assert(n == this->getColsCount());
    assert(n > 0);


    switch (n) {

        case 1:
            return this->get(0, 0);

        case 2:
            return this->get(0, 0) * this->get(1, 1) - this->get(0, 1) * this->get(1, 0);

        case 3:
            return get(0, 0) * (get(1, 1) * get(2, 2) - get(1, 2) * get(2, 1))
                   - get(0, 1) * (get(1, 0) * get(2, 2) - get(1, 2) * get(2, 0))
                   + get(0, 2) * (get(1, 0) * get(2, 1) - get(1, 1) * get(2, 0));

        default:
            double result = 0;
            for (int i = 0; i < n; i++) {
                result += this->get(0, i) * (i % 2 == 0 ? 1 : -1)
                          * this->subMatrix(0, i, true)->determinant();
            }
            return result;
    }
}

IMatrix* AbstractMatrix::nInvert() {

    // cramer's rule

    int size = this->getRowsCount();
    assert(size == this->getColsCount());

    double det = this->determinant();
    assert(fabs(det) > EPS); // != 0

    return this->adjugateMatrix()->nTranspose(true)->scalarMultiply(1 / det);
}

IMatrix* AbstractMatrix::adjugateMatrix() {
    int size = this->getRowsCount();
    IMatrix* result = this->newInstance(size, size);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            double value = subMatrix(i, j, true)->determinant()
                           * ((i + j) % 2 == 0 ? 1 : -1);

            result->set(i, j, value);
        }
    }

    return result;
}

IMatrix* AbstractMatrix::subMatrix(int row, int col, bool liveView) {
    IMatrix* matrix = this;
    if (!liveView) matrix = this->copy();
    return new MatrixSubmatrixView(matrix, row, col);
}

double* AbstractMatrix::toArray() {
    double* arr = new double[getRowsCount() * getColsCount()];

    for (int i = 0; i < getRowsCount(); ++i) {
        for (int j = 0; j < getColsCount(); ++j) {
            arr[i * getColsCount() + j] = this->get(i, j);
        }
    }
    return arr;
}

IVector* AbstractMatrix::toVector(bool liveView) {
    assert(this->getRowsCount() == 1 || this->getColsCount() == 1);
    IMatrix* matrix = this;
    if (!liveView) matrix = this->copy();
    return new VectorMatrixView(matrix);
}

string AbstractMatrix::toString() {

    const char* format = "%.3lf";
    char buff[16];

    string str = "[";

    for (int i = 0; i < getRowsCount(); ++i) {
        if (i) str += "]\n[";
        for (int j = 0; j < getColsCount(); ++j) {
            if (j) str += " ";
            sprintf(buff, format, this->get(i, j));
            str += buff;
        }
    }

    str += ']';

    return str;
}

IMatrix* AbstractMatrix::linearOperation(IMatrix* matrix, double a, double b) {
    int rows = this->getRowsCount();
    int cols = this->getColsCount();
    assert(rows == matrix->getRowsCount() && cols == matrix->getColsCount());

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            this->set(r, c, a * this->get(r, c) + b * matrix->get(r, c));
        }
    }

    return this;
}