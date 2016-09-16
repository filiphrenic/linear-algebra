//
// Created by Filip Hrenic on 13/03/16.
//

#include <iostream>

#include "Matrix.h"
#include "Vector.h"
#include <cassert>
#include <cmath>


using namespace std;

Matrix::Matrix(int rows, int cols, vector<vector<double>>* data, bool sharedData) {
    assert(rows > 0 && cols > 0);
    this->rows = rows;
    this->cols = cols;

    if (sharedData) {
        this->data = data;
    } else {
        this->data = new vector<vector<double>>(rows, vector<double>(cols));
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                this->data->at(i).at(j) = data->at(i).at(j);
            }
        }
    }
}

Matrix::Matrix(int rows, int cols) {
    assert(rows > 0 && cols > 0);
    vector<vector<double>>* data = new vector<vector<double>>;
    vector<double> row;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            row.push_back(0.0);
        }
        data->push_back(row);
        row.clear();
    }

    this->data = data;
    this->rows = rows;
    this->cols = cols;

//    Matrix(rows, cols, new vector<vector<double> >(rows, vector<double>(cols)), true);
}

Matrix::~Matrix() {
    delete this->data;
}

int Matrix::getRowsCount() {
    return this->rows;
}

int Matrix::getColsCount() {
    return this->cols;
}

double Matrix::get(int row, int col) {
    assert(0 <= row && row < this->rows);
    assert(0 <= col && col < this->cols);
    return this->data->at(row).at(col);
}

IMatrix* Matrix::set(int row, int col, double value) {
    assert(0 <= row && row < this->rows);
    assert(0 <= col && col < this->cols);
    this->data->at(row).at(col) = value;
    return this;
}

IMatrix* Matrix::copy() {
    return new Matrix(this->rows, this->cols, this->data, false);
}

IMatrix* Matrix::newInstance(int rows, int cols) {
    return new Matrix(rows, cols);
}

IMatrix* Matrix::parseSimple(std::string str) {

    vector<vector<double>>* data = new vector<vector<double>>;
    string number;
    int len = (int) str.length();
    int rows = 0, cols = 0;

    vector<double> row;

    for (int i = 0; i < len + 1; ++i) {

        if (i == len || isspace(str.at(i)) || str.at(i) == '|') {
            if (number.length() > 0) {
                row.push_back(stod(number));
                number = "";
            }
        } else {
            number += str.at(i);
        }

        if (i == len || str.at(i) == '|') {
            rows++;
            cols = max(cols, (int) row.size());
            data->push_back(row);
            row.clear();
        }
    }

    return new Matrix(rows, cols, data, true);
}

IMatrix* Matrix::translate3d(double tx, double ty, double tz) {
    IMatrix* m = new Matrix(4, 4);
    for (int i = 0; i < 4; ++i) {
        m->set(i, i, 1);
    }
    m->set(3, 0, tx);
    m->set(3, 1, ty);
    m->set(3, 2, tz);
    return m;
}

IMatrix* Matrix::scale3d(double sx, double sy, double sz) {
    IMatrix* m = new Matrix(4, 4);
    m->set(0, 0, sx);
    m->set(1, 1, sy);
    m->set(2, 2, sz);
    m->set(3, 3, 1);
    return m;
}

IMatrix* Matrix::lookAtMatrix(IVector* E, IVector* C, IVector* U) {

    IVector* a = E->nSub(C);
    IVector* b = U;

    IVector* w = a->nNormalize();
    IVector* u = b->nVectorProduct(w)->normalize();
    IVector* v = w->nVectorProduct(u);

    IMatrix* m = new Matrix(4, 4);

    m->set(0, 0, u->get(0));
    m->set(1, 0, u->get(1));
    m->set(2, 0, u->get(2));
    m->set(3, 0, -u->scalarProduct(E));

    m->set(0, 1, v->get(0));
    m->set(1, 1, v->get(1));
    m->set(2, 1, v->get(2));
    m->set(3, 1, -v->scalarProduct(E));

    m->set(0, 2, w->get(0));
    m->set(1, 2, w->get(1));
    m->set(2, 2, w->get(2));
    m->set(3, 2, -w->scalarProduct(E));

    m->set(0, 3, 0);
    m->set(1, 3, 0);
    m->set(2, 3, 0);
    m->set(3, 3, 1);

    return m;
}

IMatrix* Matrix::frustumMatrix(double l, double r, double b, double t, double n, double f) {
    IMatrix* m = new Matrix(4, 4);

    m->set(0, 0, 2 * n / (r - l));

    m->set(1, 1, 2 * n / (t - b));

    m->set(2, 0, (r + l) / (r - l));
    m->set(2, 1, (t + b) / (t - b));
    m->set(2, 2, -(f + n) / (f - n));
    m->set(2, 3, -1);

    m->set(3, 2, -2 * f * n / (f - n));

    return m;
}

IMatrix* Matrix::rotate3dx(double angle) {
    IMatrix* m = new Matrix(4, 4);

    m->set(0, 0, 1);
    m->set(1, 1, cos(angle));
    m->set(2, 2, cos(angle));
    m->set(1, 2, sin(angle));
    m->set(2, 1, -sin(angle));
    m->set(3, 3, 1);

    return m;
}

IMatrix* Matrix::rotate3dy(double angle) {
    IMatrix* m = new Matrix(4, 4);

    m->set(1, 1, 1);
    m->set(0, 0, cos(angle));
    m->set(2, 2, cos(angle));
    m->set(0, 2, -sin(angle));
    m->set(2, 0, sin(angle));
    m->set(3, 3, 1);

    return m;
}

IMatrix* Matrix::rotate3dz(double angle) {
    IMatrix* m = new Matrix(4, 4);

    m->set(2, 2, 1);
    m->set(0, 0, cos(angle));
    m->set(1, 1, cos(angle));
    m->set(0, 1, sin(angle));
    m->set(1, 0, -sin(angle));
    m->set(3, 3, 1);

    return m;
}

IMatrix* Matrix::rotate3d(double a, double x, double y, double z) {
    IVector* v = new Vector(3);
    v->set(0, x);
    v->set(1, y);
    v->set(2, z);
    v->normalize();
    x = v->get(0);
    y = v->get(1);
    z = v->get(2);

    IMatrix* m = new Matrix(4, 4);
    double c = cos(a);
    double s = sin(a);

    m->set(0, 0, x * x + (1 - x * x) * c);
    m->set(1, 0, x * y * (1 - c) + z * s);
    m->set(2, 0, x * z * (1 - c) - y * s);
    m->set(3, 0, 0);

    m->set(0, 1, x * y * (1 - c) - z * s);
    m->set(1, 1, y * y + (1 - y * y) * c);
    m->set(2, 1, y * z * (1 - c) + x * s);
    m->set(3, 1, 0);

    m->set(0, 2, x * z * (1 - c) + y * s);
    m->set(1, 2, y * z + (1 - c) - x * s);
    m->set(2, 2, z * z + (1 - z * z) * c);
    m->set(3, 2, 0);

    m->set(0, 3, 0);
    m->set(1, 3, 0);
    m->set(2, 3, 0);
    m->set(3, 3, 0);

    return m;
}
