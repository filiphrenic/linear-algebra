//
// Created by Filip Hrenic on 12/03/16.
//

#include <cassert>
#include "MatrixSubmatrixView.h"

MatrixSubmatrixView::MatrixSubmatrixView(IMatrix* matrix, int row, int col) {
    assert(nullptr != matrix);
    assert(0 <= row && row < matrix->getRowsCount());
    assert(0 <= col && col < matrix->getColsCount());
    this->matrix = matrix;
    this->row = row;
    this->col = col;
}

int MatrixSubmatrixView::getRowsCount() {
    return this->matrix->getRowsCount() - 1;
}

int MatrixSubmatrixView::getColsCount() {
    return this->matrix->getColsCount() - 1;
}

double MatrixSubmatrixView::get(int row, int col) {
    if (row >= this->row) row++;
    if (col >= this->col) col++;
    return this->matrix->get(row, col);
}

IMatrix* MatrixSubmatrixView::set(int row, int col, double value) {
    if (row >= this->row) row++;
    if (col >= this->col) col++;
    return this->matrix->set(row, col, value);
}

IMatrix* MatrixSubmatrixView::copy() {
    return new MatrixSubmatrixView(
            this->matrix->copy(),
            this->row,
            this->col
    );
}

IMatrix* MatrixSubmatrixView::newInstance(int rows, int cols) {
    return new MatrixSubmatrixView(
            this->matrix->newInstance(rows, cols),
            this->row,
            this->col
    );
}
