//
// Created by Filip Hrenic on 17/05/16.
//

#ifndef LAB6_VERTEX3D_H
#define LAB6_VERTEX3D_H

#include <string>
#include <cassert>
#include <sstream>
#include "IVector.h"
#include "Vector.h"

using namespace std;

class Vertex3D {
    double coord[3];
    IVector* normal;
    int added_normals;
    GLdouble* color;

public:
    Vertex3D(double x, double y, double z) {
        coord[0] = x;
        coord[1] = y;
        coord[2] = z;
        normal = new Vector(3);
        added_normals = 0;
    }

    ~Vertex3D() { delete normal, color; }

    static Vertex3D* fromString(string str) {
        double x, y, z;
        istringstream iss(str);
        iss >> x >> y >> z;
        return new Vertex3D(x, y, z);
    }

    void addToNormal(IVector* n) {
        normal->add(n);
        added_normals++;
    }

    void normalize() {
        normal->scalarMultiply(1.0 / added_normals)->normalize();
    }

    IVector* getNormal() { return normal; }

    double getCoord(int idx) {
        assert(0 <= idx && idx < 3);
        return coord[idx];
    }

    void setCoord(int idx, double v) {
        assert(0 <= idx && idx < 3);
        coord[idx] = v;
    }

    string toString() {
        char buff[256];
        sprintf(buff, "v %lf %lf %lf", coord[0], coord[1], coord[2]);
        return string(buff);
    }

    IVector* toVector() {
        IVector* v = new Vector(3);
        v->set(0, coord[0]);
        v->set(1, coord[1]);
        v->set(2, coord[2]);
        return v;
    }

    void setColor(GLdouble* c) { color = c; }

    GLdouble* getColor() { return color; }

};


#endif //LAB6_VERTEX3D_H
