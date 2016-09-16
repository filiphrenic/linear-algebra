//
// Created by Filip Hrenic on 13/03/16.
//

#ifndef LAB_MATRIXVECTORVIEW_H
#define LAB_MATRIXVECTORVIEW_H


#include "IVector.h"
#include "AbstractMatrix.h"

class MatrixVectorView : public AbstractMatrix {

public:

    MatrixVectorView(IVector*, bool);

    int getRowsCount();

    int getColsCount();

    double get(int, int);

    IMatrix* set(int, int, double);

    IMatrix* copy();

    IMatrix* newInstance(int, int);

private:

    IVector* vector;
    bool asRowMatrix;

};


#endif //LAB_MATRIXVECTORVIEW_H
