
#ifndef CURVESLIBRARY_H
#define CURVESLIBRARY_H

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#define M_PI 3.14159265358979323846264338327950288

class Curve
{
  public:
    virtual ~Curve() { }

    virtual double radius() const = 0;
    virtual double step() const   = 0;

    virtual double getX(double t) const = 0;
    virtual double getY(double t) const = 0;
    virtual double getZ(double t) const = 0;

    virtual double getDX(double t) const = 0;
    virtual double getDY(double t) const = 0;
    virtual double getDZ(double t) const = 0;

    virtual const std::string& info() const = 0;
};

class Circle : public Curve
{
  public:
    explicit Circle(double radius);
    double             radius() const override;
    double             step() const override;
    double             getX(double t) const override;
    double             getY(double t) const override;
    double             getZ(double t) const override;
    double             getDX(double t) const override;
    double             getDY(double t) const override;
    double             getDZ(double t) const override;
    const std::string& info() const override;

  private:
    double m_radius;
};

class Ellipse : public Curve
{
  public:
    explicit Ellipse(double radiusX, double radiusY);
    double             radius() const override;
    double             step() const override;
    double             getX(double t) const override;
    double             getY(double t) const override;
    double             getZ(double t) const override;
    double             getDX(double t) const override;
    double             getDY(double t) const override;
    double             getDZ(double t) const override;
    const std::string& info() const override;

  private:
    double m_radiusX;
    double m_radiusY;
};

class Helix : public Curve
{
  public:
    explicit Helix(double radius, double step);
    double             radius() const override;
    double             step() const override;
    double             getX(double t) const override;
    double             getY(double t) const override;
    double             getZ(double t) const override;
    double             getDX(double t) const override;
    double             getDY(double t) const override;
    double             getDZ(double t) const override;
    const std::string& info() const override;

  private:
    double m_radius;
    double m_step;
};

Curve* createCircle(double radius);
Curve* createEllipse(double radiusX, double radiusY);
Curve* createHelix(double radius, double step);

#endif
