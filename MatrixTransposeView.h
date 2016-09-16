//
// Created by Filip Hrenic on 12/03/16.
//

#ifndef LAB_MATRIXTRANSPOSEVIEW_H
#define LAB_MATRIXTRANSPOSEVIEW_H


#include "IMatrix.h"
#include "AbstractMatrix.h"

class MatrixTransposeView : public AbstractMatrix {

public:

    MatrixTransposeView(IMatrix*);

    int getRowsCount();

    int getColsCount();

    double get(int, int);

    IMatrix* set(int, int, double);

    IMatrix* copy();

    IMatrix* newInstance(int, int);

private:

    IMatrix* matrix;

};


#endif //LAB_MATRIXTRANSPOSEVIEW_H
