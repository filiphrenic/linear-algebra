//
// Created by Filip Hrenic on 11/03/16.
//

#include <cassert>
#include <algorithm>
#include <cmath>
#include <string>

#include "AbstractVector.h"
#include "MatrixVectorView.h"
#include "Vector.h"
#include <iostream>

using namespace std;

IVector* AbstractVector::copyPart(int n) {
    IVector* v = this->newInstance(n);
    for (int i = 0; i < min(n, getDimension()); i++) {
        v->set(i, this->get(i));
    }
    return v;
}

IVector* AbstractVector::add(IVector* vector) {
    return this->linearOp(vector, 1, 1);
}

IVector* AbstractVector::nAdd(IVector* vector) {
    return this->copy()->add(vector);
}

IVector* AbstractVector::sub(IVector* vector) {
    return this->linearOp(vector, 1, -1);
}

IVector* AbstractVector::nSub(IVector* vector) {
    return this->copy()->sub(vector);
}

IVector* AbstractVector::scalarMultiply(double d) {
    return this->linearOp(this, d, 0);
}

IVector* AbstractVector::nScalarMultiply(double d) {
    return this->copy()->scalarMultiply(d);
}

IVector* AbstractVector::normalize() {
    double norm = this->norm();
    return this->scalarMultiply(1 / norm);
}

IVector* AbstractVector::nNormalize() {
    return this->copy()->normalize();
}

double AbstractVector::norm() {
    double norm = 0;
    for (int i = 0; i < this->getDimension(); i++) {
        double val = this->get(i);
        norm += val * val;
    }
    //assert(fabs(norm) > EPS);
    return sqrt(norm);
}

double AbstractVector::cosine(IVector* vector) {
    return fabs(this->scalarProduct(vector)) / (this->norm() * vector->norm());
}

double AbstractVector::scalarProduct(IVector* vector) {
    assert(this->getDimension() == vector->getDimension());

    double result = 0;
    for (int i = 0; i < this->getDimension(); i++) {
        result += this->get(i) * vector->get(i);
    }
    return result;
}

IVector* AbstractVector::nVectorProduct(IVector* vector) {
    assert(this->getDimension() == vector->getDimension());

    IVector* a = this;
    IVector* b = vector;
    bool was4 = false;

    if (getDimension() == 4) {
        a = a->nFromHomogeneus();
        b = b->nFromHomogeneus();
        was4 = true;
    } else
        assert(this->getDimension() == 3);

    IVector* product = a->copy();

    product->set(0, a->get(1) * b->get(2) - a->get(2) * b->get(1));
    product->set(1, a->get(2) * b->get(0) - a->get(0) * b->get(2));
    product->set(2, a->get(0) * b->get(1) - a->get(1) * b->get(0));

    if (was4) {
        IVector* four = new Vector(4);
        four->set(0, product->get(0))->set(1, product->get(1))->set(1, product->get(1));
        four->set(3, 1);
        product = four;
    }

    return product;
}

IVector* AbstractVector::nFromHomogeneus() {
    assert(this->getDimension() > 0);

    int newDim = this->getDimension() - 1;
    double last = this->get(newDim);

    assert(fabs(last) > EPS); // last component can't be 0

    return this->copyPart(newDim)->scalarMultiply(1 / last);
}

IMatrix* AbstractVector::toRowMatrix(bool liveView) {
    IVector* vector = this;
    if (!liveView) vector = this->copy();
    return new MatrixVectorView(vector, true);
}

IMatrix* AbstractVector::toColumnMatrix(bool liveView) {
    IVector* vector = this;
    if (!liveView) vector = this->copy();
    return new MatrixVectorView(vector, false);
}

double* AbstractVector::toArray() {
    assert(this->getDimension() > 0);
    double* arr = new double[this->getDimension()];
    for (int i = 0; i < this->getDimension(); i++) {
        arr[i] = this->get(i);
    }
    return arr;
}

string AbstractVector::toString() {

    string str;
    const char* format = "%.3lf";
    char buff[16];

    for (int i = 0; i < this->getDimension(); ++i) {
        if (i) str += " ";
        sprintf(buff, format, this->get(i));
        str += buff;
    }

    return '[' + str + ']';
}

IVector* AbstractVector::linearOp(IVector* vector, double a, double b) {
    assert(this->getDimension() == vector->getDimension());
    for (int i = 0; i < getDimension(); i++) {
        this->set(i, a * this->get(i) + b * vector->get(i));
    }
    return this;
}

IVector* AbstractVector::mMultiply(IMatrix* m, bool live) {
    return this->toRowMatrix(live)->nMultiply(m)->toVector(true);
}

IVector* AbstractVector::mhMultiply(IMatrix* m) {
    return this->nToHomogeneus()->mMultiply(m, true)->nFromHomogeneus();
}