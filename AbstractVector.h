//
// Created by Filip Hrenic on 11/03/16.
//

#ifndef LAB_ABSTRACTVECTOR_H
#define LAB_ABSTRACTVECTOR_H

#include <string>

#include "IRG.h"
#include "IVector.h"
#include "IMatrix.h"

class AbstractVector : virtual public IVector {

public:

    IVector* copyPart(int);

    IVector* add(IVector*);

    IVector* nAdd(IVector*);

    IVector* sub(IVector*);

    IVector* nSub(IVector*);

    IVector* scalarMultiply(double);

    IVector* nScalarMultiply(double);

    IVector* normalize();

    IVector* nNormalize();

    double norm();

    double cosine(IVector*);

    double scalarProduct(IVector*);

    IVector* nVectorProduct(IVector*);

    IVector* nFromHomogeneus();

    IMatrix* toRowMatrix(bool);

    IMatrix* toColumnMatrix(bool);

    double* toArray();

    std::string toString();

    IVector* mMultiply(IMatrix*, bool live = false);

    IVector* mhMultiply(IMatrix*);

private:

    // return a * this + b * other
    IVector* linearOp(IVector*, double, double);

};

#endif //LAB_ABSTRACTVECTOR_H
