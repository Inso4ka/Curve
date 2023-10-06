#include "curve/curve_lib.h"
#include <random>

int main() {
    std::vector<std::unique_ptr<Curve>> curves;

    std::random_device                     rd;
    std::mt19937                           gen(rd());
    std::uniform_real_distribution<double> dis(1.0, 5.0);

    curves.emplace_back(createCircle(dis(gen)));
    curves.emplace_back(createEllipse(dis(gen), dis(gen)));
    curves.emplace_back(createHelix(dis(gen), dis(gen)));

    double t = M_PI / 4.0;
    for (const auto& curve : curves) {
        std::cout << "Coordinates for curve with radius " << curve->radius() << " at t=PI/4:" << std::endl;
        std::cout << "Point: (" << curve->getX(t) << ", " << curve->getY(t) << ", " << curve->getZ(t) << ")" << std::endl;
        std::cout << "Derivative: (" << curve->getDX(t) << ", " << curve->getDY(t) << ", " << curve->getDZ(t) << ")" << std::endl;
        std::cout << std::endl;
    }

    std::vector<Circle*> circlesOnly;
    for (const auto& curve : curves) {
        if (auto circle = dynamic_cast<Circle*>(curve.get())) {
            circlesOnly.push_back(circle);
        }
    }

    std::sort(circlesOnly.begin(), circlesOnly.end(), [](const Circle* c1, const Circle* c2) {
        return c1->radius() < c2->radius();
    });

    double sumOfRadii = 0.0;
    for (const auto& circle : circlesOnly) {
        sumOfRadii += circle->radius();
    }

    std::cout << "Total sum of radii of circles in the second container: " << sumOfRadii << std::endl;

    return 0;
}
