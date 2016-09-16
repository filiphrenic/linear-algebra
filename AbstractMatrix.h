//
// Created by Filip Hrenic on 12/03/16.
//

#ifndef LAB_ABSTRACTMATRIX_H
#define LAB_ABSTRACTMATRIX_H

#include <string>

#include "IRG.h"
#include "IMatrix.h"
#include "IVector.h"

class AbstractMatrix : virtual public IMatrix {

public:

    IMatrix* nTranspose(bool);

    IMatrix* add(IMatrix*);

    IMatrix* nAdd(IMatrix*);

    IMatrix* sub(IMatrix*);

    IMatrix* nSub(IMatrix*);

    IMatrix* nMultiply(IMatrix*);

    IMatrix* scalarMultiply(double);

    double determinant();

    IMatrix* nInvert();

    IMatrix* subMatrix(int, int, bool);

    double* toArray();

    IVector* toVector(bool);

    std::string toString();

private:

    IMatrix* linearOperation(IMatrix*, double, double);

    IMatrix* adjugateMatrix();

};


#endif //LAB_ABSTRACTMATRIX_H
