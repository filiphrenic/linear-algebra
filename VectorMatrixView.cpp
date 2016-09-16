//
// Created by Filip Hrenic on 13/03/16.
//

#include "VectorMatrixView.h"
#include <cassert>


VectorMatrixView::VectorMatrixView(IMatrix* matrix) {
    if (matrix->getRowsCount() == 1) {
        this->wasRowMatrix = true;
    } else if (matrix->getColsCount() == 1) {
        this->wasRowMatrix = false;
    } else {
        assert(false);
    }
    this->matrix = matrix;
}

double VectorMatrixView::get(int i) {
    assert(0 <= i && i < this->getDimension());
    int row = i, col = i;
    if (wasRowMatrix) row = 0; else col = 0;
    return this->matrix->get(row, col);
}

IVector* VectorMatrixView::set(int i, double value) {
    assert(0 <= i && i < this->getDimension());
    int row = i, col = i;
    if (wasRowMatrix) row = 0; else col = 0;
    this->matrix->set(row, col, value);
    return this;
}

int VectorMatrixView::getDimension() {
    if (wasRowMatrix)
        return this->matrix->getColsCount();
    else
        return this->matrix->getRowsCount();
}

IVector* VectorMatrixView::copy() {
    return new VectorMatrixView(this->matrix->copy());
}

IVector* VectorMatrixView::newInstance(int cols) {
    return new VectorMatrixView(this->matrix->newInstance(1, cols));
}

IVector* VectorMatrixView::nToHomogeneus() {
    assert(false);
}
