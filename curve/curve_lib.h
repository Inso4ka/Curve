
#ifndef CURVESLIBRARY_H
#define CURVESLIBRARY_H

#ifdef _WIN32
#ifdef CURVESLIBRARY_EXPORTS
#define CURVESLIBRARY_EXPORT __declspec(dllexport)
#else
#define CURVESLIBRARY_EXPORT __declspec(dllimport)
#endif
#else
#define CURVESLIBRARY_EXPORT __attribute__((visibility("default")))
#endif

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

class CURVESLIBRARY_EXPORT Curve
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
};

class CURVESLIBRARY_EXPORT Circle : public Curve
{
  public:
    explicit Circle(double radius);
    double radius() const override;
    double step() const override;
    double getX(double t) const override;
    double getY(double t) const override;
    double getZ(double t) const override;
    double getDX(double t) const override;
    double getDY(double t) const override;
    double getDZ(double t) const override;

  private:
    double m_radius;
};

class CURVESLIBRARY_EXPORT Ellipse : public Curve
{
  public:
    explicit Ellipse(double radiusX, double radiusY);
    double radius() const override;
    double step() const override;
    double getX(double t) const override;
    double getY(double t) const override;
    double getZ(double t) const override;
    double getDX(double t) const override;
    double getDY(double t) const override;
    double getDZ(double t) const override;

  private:
    double m_radiusX;
    double m_radiusY;
};

class CURVESLIBRARY_EXPORT Helix : public Curve
{
  public:
    explicit Helix(double radius, double step);
    double radius() const override;
    double step() const override;
    double getX(double t) const override;
    double getY(double t) const override;
    double getZ(double t) const override;
    double getDX(double t) const override;
    double getDY(double t) const override;
    double getDZ(double t) const override;

  private:
    double m_radius;
    double m_step;
};

extern "C" CURVESLIBRARY_EXPORT Curve* createCircle(double radius);
extern "C" CURVESLIBRARY_EXPORT Curve* createEllipse(double radiusX, double radiusY);
extern "C" CURVESLIBRARY_EXPORT Curve* createHelix(double radius, double step);

#endif
