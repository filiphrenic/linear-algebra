//
// Created by Filip Hrenic on 18/05/16.
//

#ifndef LAB6_POLY_H
#define LAB6_POLY_H

#include "Face3D.h"
#include "Vertex3D.h"
#include "IVector.h"
#include "Vector.h"

int sign(double x) {
    return (x > 0) - (x < 0);
}

class Poly {

    Face3D* face;
    IVector* normal;
    double d;
    bool visible;
    GLdouble* color;

public:

    Poly(Face3D* face) {
        this->face = face;
        normal = new Vector(3);
        visible = false;
    }

    ~Poly() {
        delete face;
        delete normal;
        delete color;
    }

    void calculateNormal(Vertex3D* v0, Vertex3D* v1, Vertex3D* v2) {

        double v10[3];
        double v20[3];
        for (int i = 0; i < 3; ++i) {
            v10[i] = v1->getCoord(i) - v0->getCoord(i);
            v20[i] = v2->getCoord(i) - v0->getCoord(i);
        }

        double norm[3];
        normal->set(0, v10[1] * v20[2] - v10[2] * v20[1]);
        normal->set(1, v10[2] * v20[0] - v10[0] * v20[2]);
        normal->set(2, v10[0] * v20[1] - v10[1] * v20[0]);

        normal->normalize();

        d = 0;
        for (int i = 0; i < 3; ++i)
            d -= normal->get(i) * v0->getCoord(i);
    }

    void determineVisibility(IVector* eye) {
        visible = eye->scalarProduct(normal) > -d;
    }

    bool isVisible() { return visible; }

    Face3D* getFace() { return face; }

    IVector* getNormal() { return normal; }

    void setColor(GLdouble* c) { color = c; }

    GLdouble* getColor() { return color; }

};


#endif //LAB6_POLY_H
