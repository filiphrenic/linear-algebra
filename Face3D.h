//
// Created by Filip Hrenic on 17/05/16.
//

#ifndef LAB1_FACE3D_H
#define LAB1_FACE3D_H

#include <vector>
#include <string>
#include <cassert>
#include <cfloat>
#include <cstdio>
#include <sstream>
#include <iostream>


using namespace std;

class Face3D {
    int indexes[3];
public:
    Face3D(int i0, int i1, int i2) {
        indexes[0] = i0;
        indexes[1] = i1;
        indexes[2] = i2;
    }

    static Face3D* fromString(string str) {
        istringstream iss(str);
        int i0, i1, i2;
        iss >> i0 >> i1 >> i2;
        return new Face3D(i0 - 1, i1 - 1, i2 - 1);
    }

    int getVertex(int idx) const {
        assert(0 <= idx && idx < 3);
        return indexes[idx];
    }

    string toString() {
        char buff[256];
        sprintf(buff, "f %d %d %d", indexes[0] + 1, indexes[1] + 1, indexes[2] + 1);
        return string(buff);
    }

};


#endif //LAB1_FACE3D_H
