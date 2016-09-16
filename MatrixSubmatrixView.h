//
// Created by Filip Hrenic on 12/03/16.
//

#ifndef LAB_MATRIXSUBMATRIXVIEW_H
#define LAB_MATRIXSUBMATRIXVIEW_H


#include "AbstractMatrix.h"

class MatrixSubmatrixView : public AbstractMatrix {

public:

    MatrixSubmatrixView(IMatrix*, int, int);

    int getRowsCount();

    int getColsCount();

    double get(int, int);

    IMatrix* set(int, int, double);

    IMatrix* copy();

    IMatrix* newInstance(int, int);

private:

    IMatrix* matrix;
    int row;
    int col;

};


#endif //LAB_MATRIXSUBMATRIXVIEW_H
