#include <array>
#include <cmath>
#include <iostream>

class IonoModel
{
  public:
    enum class eIonoMode
    {
        iono_L1, // Correction needs to be computed for L1 band
        iono_L2  // Correction needs to be computed for L2 band
    };

    // GPS time – in seconds;
    // latitude, longitude, elevation and azimuth – in radians;
    // ionospheric delay in meters.
    virtual double getIonoDelay(double gpstime, double lat, double lon, double elv, double azm, eIonoMode mode) const = 0;
};

class MyIonoModel : public IonoModel
{
  private:
    static std::array<double, 4> ALPHA;
    static std::array<double, 4> BETA;

  public:
    MyIonoModel() { }

    double getIonoDelay(double gpstime, double lat, double lon, double elv, double azm, eIonoMode mode) const override {
        double ionoDelay = 0.0;
        double psi       = 0.0137 / (elv + 0.11) - 0.022;
        double phi_i     = lat + psi * std::cos(azm);
        if (phi_i > 0.416) {
            phi_i = 0.416;
        } else if (phi_i < -0.416) {
            phi_i = -0.416;
        }

        double lamda_i = lon + psi * std::sin(azm) / std::cos(phi_i);
        double phi_m   = phi_i + 0.064 * std::cos(lamda_i - 1.617);
        double t       = 4.32 * 1.0e+4 * lamda_i + gpstime;
        while (t >= 86400.0) {
            t -= 86400.0;
        }

        while (t < 0) {
            t += 86400.0;
        }

        double F   = 1.0 + 16.0 * std::pow(0.53 - elv, 3.0);
        double PER = 0.0;
        double AMP = 0.0;
        for (int i = 0; i < 4; i++) {
            PER += BETA[i] * std::pow(phi_m, i);
            AMP += ALPHA[i] * std::pow(phi_m, i);
        }

        if (PER < 72000) {
            PER = 72000;
        }

        if (AMP < 0) {
            AMP = 0;
        }

        double x = (2 * M_PI * (t - 50400)) / PER;

        double y      = std::pow(1575.42 / 1227.6, 2);
        double factor = F * (5.0 * 1.0e-9);

        if (std::abs(x) < 1.57) {
            double ionoCorrection = F * AMP * (1 - std::pow(x, 2) / 2 + std::pow(x, 4) / 24);
            ionoDelay             = factor + ionoCorrection;
        } else {
            ionoDelay = factor;
        }

        if (mode == eIonoMode::iono_L2) {
            ionoDelay *= y;
        }

        return ionoDelay;
    }

    static void updateAlphaCoefficients(const std::array<double, 4>& newCoefficients) {
        ALPHA = newCoefficients;
    }

    static void updateBetaCoefficients(const std::array<double, 4>& newCoefficients) {
        BETA = newCoefficients;
    }
};

std::array<double, 4> MyIonoModel::ALPHA = {1.490116119e-08, 2.235174179e-08, -1.192092896e-07, -1.192092896e-07};
std::array<double, 4> MyIonoModel::BETA  = {1.167360000e+05, 1.802240000e+05, -1.310720000e+05, -4.587520000e+05};

int main() {
    MyIonoModel ionoModel;

    double gpstime = 128718.0;
    double lat     = 55.6917 * (M_PI / 180.0);
    double lon     = 37.3478 * (M_PI / 180.0);
    double elv     = 25.0 * (M_PI / 180.0);
    double azm     = 112.0 * (M_PI / 180.0);

    double ionoDelayL1 = ionoModel.getIonoDelay(gpstime, lat, lon, elv, azm, IonoModel::eIonoMode::iono_L1);
    double ionoDelayL2 = ionoModel.getIonoDelay(gpstime, lat, lon, elv, azm, IonoModel::eIonoMode::iono_L2);
    std::cout << ionoDelayL1 << "\n";
    std::cout << ionoDelayL2 << "\n";

    std::array<double, 4> newAlpha = {12.0, 22.0, 31.0, 4.0};
    ionoModel.updateAlphaCoefficients(newAlpha);

    double updatedIonoDelayL1 = ionoModel.getIonoDelay(gpstime, lat, lon, elv, azm, IonoModel::eIonoMode::iono_L1);
    double updatedIonoDelayL2 = ionoModel.getIonoDelay(gpstime, lat, lon, elv, azm, IonoModel::eIonoMode::iono_L2);
    std::cout << updatedIonoDelayL1 << "\n";
    std::cout << updatedIonoDelayL2 << "\n";

    std::array<double, 4> newBeta = {2.167360000e+05, 10.802240000e+05, -10.310720000e+05, -8.587520000e+05};
    MyIonoModel::updateBetaCoefficients(newBeta);

    updatedIonoDelayL1 = ionoModel.getIonoDelay(gpstime, lat, lon, elv, azm, IonoModel::eIonoMode::iono_L1);
    updatedIonoDelayL2 = ionoModel.getIonoDelay(gpstime, lat, lon, elv, azm, IonoModel::eIonoMode::iono_L2);
    std::cout << updatedIonoDelayL1 << "\n";
    std::cout << updatedIonoDelayL2 << "\n";

    return 0;
}
