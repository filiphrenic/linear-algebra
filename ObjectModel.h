//
// Created by Filip Hrenic on 17/05/16.
//

#ifndef LAB1_OBJECTMODEL_H
#define LAB1_OBJECTMODEL_H

#include "Face3D.h"

#include <fstream>
#include <vector>
#include "Poly.h"
#include "Vector.h"

using namespace std;

class ObjectModel {
    vector<Vertex3D*> vertexes;
    vector<Poly*> polys;
    pair<double, double> minmax[3];

    void calcNormal(Poly* p) {
        Face3D* f = p->getFace();
        p->calculateNormal(
                vertexes[f->getVertex(0)],
                vertexes[f->getVertex(1)],
                vertexes[f->getVertex(2)]
        );
    }

    void normalizeVertexes() {
        for (Poly* p : polys) {
            Face3D* f = p->getFace();
            IVector* n = p->getNormal();
            for (int i = 0; i < 3; ++i)
                vertexes[f->getVertex(i)]->addToNormal(n);
        }
        for (Vertex3D* v : vertexes)
            v->normalize();
    }

public:

    ObjectModel(string filename) : ObjectModel() {

        ifstream file(filename, fstream::in);
        string str, values;

        while (getline(file, str)) {
            if (str.empty()) continue;
            values = str.substr(1);
            if (str[0] == 'v') addVertex(Vertex3D::fromString(values));
            else if (str[0] == 'f') addFace(Face3D::fromString(values));
        }

    }

    ObjectModel() {
        for (int i = 0; i < 3; ++i) {
            minmax[i].first = INT_MAX; // min
            minmax[i].second = INT_MIN; // max
        }
    }

    ~ObjectModel() {
        for (Vertex3D* v : vertexes) delete v;
        for (Poly* p : polys) delete p;
    }

    void normalize() {
        double center[3], M = DBL_MIN;
        for (int i = 0; i < 3; ++i) {
            center[i] = (minmax[i].first + minmax[i].second) / 2;
            M = max(M, minmax[i].second - minmax[i].first);
        }
        for (auto it = vertexes.begin(); it != vertexes.end(); ++it) {
            for (int i = 0; i < 3; ++i) {
                double coord = (*it)->getCoord(i);
                coord = (coord - center[i]) * 2 / M;
                (*it)->setCoord(i, coord);
            }
        }

        for (Poly* p : polys) calcNormal(p);

        normalizeVertexes();
    }

    void addVertex(Vertex3D* v) {
        for (int i = 0; i < 3; ++i) {
            minmax[i].first = min(minmax[i].first, v->getCoord(i));
            minmax[i].second = max(minmax[i].second, v->getCoord(i));
        }
        vertexes.push_back(v);
    }

    void addFace(Face3D* f) {
        long n = vertexes.size();
        for (int i = 0; i < 3; ++i) assert(0 <= f->getVertex(i) && f->getVertex(i) < n);
        Poly* p = new Poly(f);
        calcNormal(p);
        polys.push_back(p);
    }

    vector<Poly*> getPolys() {
        return this->polys;
    }

    Vertex3D* getVertex(int idx) {
        return vertexes[idx];
    }

    void determineFaceVisibilities(IVector* eye) {
        for (Poly* p : polys) p->determineVisibility(eye);
    }

    IVector* getCenter(Poly* poly) {
        IVector* v = new Vector(3);
        for (int i = 0; i < 3; ++i)
            v->add(vertexes[poly->getFace()->getVertex(i)]->toVector());
        v->scalarMultiply(1.0 / 3);
        return v;
    }

};


#endif //LAB1_OBJECTMODEL_H
