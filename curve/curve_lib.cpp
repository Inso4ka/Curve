#include "curve_lib.h"
#include <stdexcept>

Circle::Circle(double radius) : m_radius(radius) {
    if (radius <= 0) {
        throw std::invalid_argument("Radius must be positive");
    }
}
double Circle::radius() const {
    return m_radius;
}
double Circle::step() const {
    return 0;
}
double Circle::getX(double t) const {
    return m_radius * cos(t);
}
double Circle::getY(double t) const {
    return m_radius * sin(t);
}
double Circle::getZ(double t) const {
    return 0;
}
double Circle::getDX(double t) const {
    return -m_radius * sin(t);
}
double Circle::getDY(double t) const {
    return m_radius * cos(t);
}
double Circle::getDZ(double t) const {
    return 0;
}

Ellipse::Ellipse(double radiusX, double radiusY) : m_radiusX(radiusX), m_radiusY(radiusY) {
    if (radiusX <= 0 || radiusY <= 0) {
        throw std::invalid_argument("Radius must be positive");
    }
}
double Ellipse::radius() const {
    return std::max(m_radiusX, m_radiusY);
}
double Ellipse::step() const {
    return 0;
}
double Ellipse::getX(double t) const {
    return m_radiusX * cos(t);
}
double Ellipse::getY(double t) const {
    return m_radiusY * sin(t);
}
double Ellipse::getZ(double t) const {
    return 0;
}
double Ellipse::getDX(double t) const {
    return -m_radiusX * sin(t);
}
double Ellipse::getDY(double t) const {
    return m_radiusY * cos(t);
}
double Ellipse::getDZ(double t) const {
    return 0;
}

Helix::Helix(double radius, double step) : m_radius(radius), m_step(step) {
    if (radius <= 0 || step <= 0) {
        throw std::invalid_argument("Radius and step must be positive");
    }
}
double Helix::radius() const {
    return m_radius;
}
double Helix::step() const {
    return m_step;
}
double Helix::getX(double t) const {
    return m_radius * cos(t);
}
double Helix::getY(double t) const {
    return m_radius * sin(t);
}
double Helix::getZ(double t) const {
    return m_step * t / (2 * M_PI);
}
double Helix::getDX(double t) const {
    return -m_radius * sin(t);
}
double Helix::getDY(double t) const {
    return m_radius * cos(t);
}
double Helix::getDZ(double t) const {
    return m_step / (2 * M_PI);
}

Curve* createCircle(double radius) {
    return new Circle(radius);
}
Curve* createEllipse(double radiusX, double radiusY) {
    return new Ellipse(radiusX, radiusY);
}
Curve* createHelix(double radius, double step) {
    return new Helix(radius, step);
}
