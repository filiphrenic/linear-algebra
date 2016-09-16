//
// Created by Filip Hrenic on 13/03/16.
//

#ifndef LAB_MATRIX_H
#define LAB_MATRIX_H


#include "IRG.h"
#include "AbstractMatrix.h"
#include <vector>
#include <string>

class Matrix : public AbstractMatrix {

public:

    Matrix(int, int, std::vector<std::vector<double>>*, bool);

    Matrix(int, int);

    ~Matrix();

    int getRowsCount();

    int getColsCount();

    double get(int, int);

    IMatrix* set(int, int, double);

    IMatrix* copy();

    IMatrix* newInstance(int, int);

    static IMatrix* parseSimple(std::string);

    static IMatrix* translate3d(double, double, double);

    static IMatrix* scale3d(double, double, double);

    static IMatrix* lookAtMatrix(IVector*, IVector*, IVector*);

    static IMatrix* frustumMatrix(double, double, double, double, double, double);

    static IMatrix* rotate3dx(double);

    static IMatrix* rotate3dy(double);

    static IMatrix* rotate3dz(double);

    static IMatrix* rotate3d(double, double, double, double);


private:

    std::vector<std::vector<double>>* data;

    int rows;

    int cols;

};


#endif //LAB_MATRIX_H
