//
// Created by Filip Hrenic on 13/03/16.
//

#ifndef LAB_VECTORMATRIXVIEW_H
#define LAB_VECTORMATRIXVIEW_H


#include "AbstractVector.h"

class VectorMatrixView : public AbstractVector {

public:

    VectorMatrixView(IMatrix*);

    double get(int);

    IVector* set(int, double);

    int getDimension();

    IVector* copy();

    IVector* newInstance(int);

    IVector* nToHomogeneus();

private:

    IMatrix* matrix;
    bool wasRowMatrix;

};


#endif //LAB_VECTORMATRIXVIEW_H
