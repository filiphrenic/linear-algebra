//
// Created by Filip Hrenic on 11/03/16.
//

#include <vector>
#include <cassert>
#include <string>

#include "IRG.h"
#include "Vector.h"
#include <stdarg.h>

using namespace std;

Vector::~Vector() { delete this->data; }

Vector::Vector(vector<double>* data) {
    Vector::Vector(false, false, data);
}

Vector::Vector(int size) {
    assert(size > 0);
    vector<double>* data = new vector<double>(size);
    for (int i = 0; i < size; ++i) {
        data->at(i) = 0;
    }
    this->readOnly = false;
    this->dimension = size;
    this->data = data;
}

Vector::Vector(bool readOnly, bool sharedData, vector<double>* data) {

    this->readOnly = readOnly;
    this->dimension = (int) data->size();

    if (sharedData) {
        this->data = data;
    } else {
        this->data = new vector<double>();
        for (int i = 0; i < this->dimension; ++i) {
            this->data->push_back(data->at(i));
        }
    }
}

double Vector::get(int i) {
    assert(0 <= i && i < this->dimension);
    return this->data->at(i);
}

IVector* Vector::set(int i, double d) {
    assert(!this->readOnly);
    assert(0 <= i && i < this->dimension);
    this->data->at(i) = d;
    return this;
}

int Vector::getDimension() {
    return this->dimension;
}

IVector* Vector::copy() {
    return new Vector(this->readOnly, false, this->data);
}

IVector* Vector::newInstance(int n) {
    return new Vector(n);
}

Vector* Vector::parseSimple(string str) {
    vector<double>* data = new vector<double>;
    string number;
    int len = (int) str.length();

    for (int i = 0; i < len + 1; ++i) {
        if (i == len || isspace(str.at(i))) {
            if (number.length() > 0) {
                data->push_back(stod(number));
                number = "";
            }
        } else {
            number += str.at(i);
        }
    }

    return new Vector(false, true, data);
}

IVector* Vector::nToHomogeneus() {
    Vector* v = new Vector(this->readOnly, false, this->data);
    v->data->push_back(1);
    v->dimension++;
    return v;
}

