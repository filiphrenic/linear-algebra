//
// Created by Filip Hrenic on 12/03/16.
//

#include <cassert>
#include "MatrixTransposeView.h"

MatrixTransposeView::MatrixTransposeView(IMatrix* matrix) {
    assert(nullptr != matrix);
    this->matrix = matrix;
}

int MatrixTransposeView::getRowsCount() {
    return this->matrix->getColsCount();
}

int MatrixTransposeView::getColsCount() {
    return this->matrix->getRowsCount();
}

double MatrixTransposeView::get(int row, int col) {
    return this->matrix->get(col, row);
}

IMatrix* MatrixTransposeView::set(int row, int col, double value) {
    return this->matrix->set(col, row, value);
}

IMatrix* MatrixTransposeView::copy() {
    return new MatrixTransposeView(this->matrix->copy());
}

IMatrix* MatrixTransposeView::newInstance(int rows, int cols) {
    return new MatrixTransposeView(this->matrix->newInstance(cols, rows));
}
