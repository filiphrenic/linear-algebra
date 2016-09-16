//
// Created by Filip Hrenic on 13/03/16.
//

#include <cassert>
#include <algorithm>
#include "MatrixVectorView.h"

MatrixVectorView::MatrixVectorView(IVector* vector, bool asRowMatrix) {
    assert(vector != nullptr);
    this->vector = vector;
    this->asRowMatrix = asRowMatrix;
}

int MatrixVectorView::getRowsCount() {
    return this->asRowMatrix ? 1 : this->vector->getDimension();
}

int MatrixVectorView::getColsCount() {
    return this->asRowMatrix ? this->vector->getDimension() : 1;
}

double MatrixVectorView::get(int row, int col) {
    assert(0 <= row && row <= this->getRowsCount());
    assert(0 <= col && col <= this->getColsCount());
    return this->vector->get(row > col ? row : col);
}

IMatrix* MatrixVectorView::set(int row, int col, double value) {
    assert(0 <= row && row <= this->getRowsCount());
    assert(0 <= col && col <= this->getColsCount());
    this->vector->set(row > col ? row : col, value);
    return this;
}

IMatrix* MatrixVectorView::copy() {
    return new MatrixVectorView(this->vector->copy(), this->asRowMatrix);
}

IMatrix* MatrixVectorView::newInstance(int rows, int cols) {
    assert(std::min(rows, cols) == 1);
    IVector* vector = this->vector->newInstance(std::max(rows, cols));
    return new MatrixVectorView(vector, rows == 1);
}
