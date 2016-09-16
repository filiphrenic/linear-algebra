//
// Created by Filip Hrenic on 11/03/16.
//

#ifndef LAB_VECTOR_H
#define LAB_VECTOR_H

#include <string>
#include <vector>

#include "IRG.h"
#include "AbstractVector.h"

class Vector : public AbstractVector {

public:

    Vector(std::vector<double>*);

    Vector(int);

    ~Vector();

    Vector(bool, bool, std::vector<double>*);

    double get(int);

    IVector* set(int, double);

    int getDimension();

    IVector* copy();

    IVector* newInstance(int);

    static Vector* parseSimple(std::string);

    IVector* nToHomogeneus();

private:

    std::vector<double>* data;

    int dimension;

    bool readOnly;

};


#endif //LAB_VECTOR_H
