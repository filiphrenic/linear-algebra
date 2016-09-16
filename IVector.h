//
// Created by Filip Hrenic on 11/03/16.
//

#ifndef IVector_h
#define IVector_h

#include <string>

#include "IRG.h"
#include "IMatrix.h"

/**
 * Interface that represents a vector model.
 *
 * @author fhrenic
 */
class IVector {

public:

    // Returns one component.
    virtual double get(int) = 0;

    // Sets one component.
    virtual IVector* set(int, double) = 0;

    // Returns vector's dimesnion.
    virtual int getDimension() = 0;

    // Creates a new vector copy that has same elements.
    virtual IVector* copy() = 0;

    // Copies a part of the vector and fills the rest with zeros.
    virtual IVector* copyPart(int) = 0;

    // Creates a new vector with given dimension.
    virtual IVector* newInstance(int) = 0;

    // Adds the IVector other to this vector.
    virtual IVector* add(IVector*) = 0;

    // Adds the IVector other to this vector, but creates a new vector as the result.
    virtual IVector* nAdd(IVector*) = 0;

    // Subtracts the IVector other from this vector.
    virtual IVector* sub(IVector*) = 0;

    // Subtracts the {@link IVector} other from this vector.
    virtual IVector* nSub(IVector*) = 0;

    // Multiplies every component of the vector by the parameter.
    virtual IVector* scalarMultiply(double) = 0;

    // Multiplies every component of the vector by the parameter and returns a new vector.
    virtual IVector* nScalarMultiply(double) = 0;

    // Normalizes this vector by dividing all of its components with this vectors norm.
    virtual IVector* normalize() = 0;

    // Returns a new IVector that is the normalized form of this vector.
    virtual IVector* nNormalize() = 0;

    // Calculates the norm
    virtual double norm() = 0;

    // Calculates the cosine of the angle theta between the two vectors.
    virtual double cosine(IVector*) = 0;

    // Returns a scalar product of this and other IVector
    virtual double scalarProduct(IVector*) = 0;

    //Returns a vector product of this and other IVector.
    // Vector's must have same dimensions and that dimension must be 3.
    virtual IVector* nVectorProduct(IVector*) = 0;

    // Returns a vector that is calculated from the first one.
    // If you want to know how, see this link: http://en.wikipedia.org/wiki/Homogeneous_coordinates
    virtual IVector* nFromHomogeneus() = 0;

    virtual IVector* nToHomogeneus() = 0;

    // Returns this vector as a row matrix.
    virtual IMatrix* toRowMatrix(bool) = 0;

    // Returns this vector as a column matrix.
    virtual IMatrix* toColumnMatrix(bool) = 0;

    // Returns vector components in an array.
    virtual double* toArray() = 0;

    // Returns this vector as string
    virtual std::string toString() = 0;

    virtual IVector* mMultiply(IMatrix*, bool live = false) = 0;

    virtual IVector* mhMultiply(IMatrix*) = 0;

};

#endif /* IVector_h */
