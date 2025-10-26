#include "vector.h"
#include "matrix.h"
#include <iostream>
#include <cmath>
using namespace std;

Vector::Vector(const double x, const double y, const double z)
{
    m = Matrix(3, 1, true);
    m.set(0, 0, x);
    m.set(1, 0, y);
    m.set(2, 0, z);
}

Vector::Vector(const Vector& other)
{
    m = other.m;
}

Vector& Vector::operator=(const Vector& other)
{
    if (this != &other)
        m = other.m;
    return *this;
}

Vector Vector::operator*(const double scalar) const
{
    Vector result(*this);
    result.m = result.m * scalar;
    return result;
}

Vector Vector::getDotProduct(const Vector& other, const double theta) const
{
    double magA = getMagnitude();
    double magB = other.getMagnitude();
    double dotValue = magA * magB * cos(theta);
    return Vector(dotValue, 0, 0);
}

Vector Vector::operator*(const Vector other) const
{
    double a1 = getX(), a2 = getY(), a3 = getZ();
    double b1 = other.getX(), b2 = other.getY(), b3 = other.getZ();
    double cx = a2 * b3 - a3 * b2;
    double cy = a3 * b1 - a1 * b3;
    double cz = a1 * b2 - a2 * b1;
    return Vector(cx, cy, cz);
}

double Vector::getX() const { return m.get(0, 0); }
double Vector::getY() const { return m.get(1, 0); }
double Vector::getZ() const { return m.get(2, 0); }

void Vector::setX(const double x) { m.set(0, 0, x); }
void Vector::setY(const double y) { m.set(1, 0, y); }
void Vector::setZ(const double z) { m.set(2, 0, z); }

double Vector::getMagnitude() const
{
    double x = getX(), y = getY(), z = getZ();
    return sqrt(x * x + y * y + z * z);
}

void Vector::print() const
{
    m.print();
}

Vector::~Vector() {}
