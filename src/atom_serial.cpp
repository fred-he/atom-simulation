#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>
#include <getopt.h>

#include "Vec3.h"
#include "Vec2.h"

#define G 9.805  // Gravitational acceleration at latitude 43.47 degree [m/s^2]
#define C 2.9979e8 // Speed of light [m/s]
#define M 2.2069e-25 // Atomic mass of cesium [kg]
#define W0 2.75E-6 // Beam waist [m]
#define WAVELENGTH 9.356e-7 // Wavelength of dipole trap laser [m]
#define YR 2.539365e-05 // pi*WSQUARE/WAVELENGTH // Rayleigh distance [m]
#define kB 1.38065e-23 // Boltzmann constant [m^2 kg s^(-2) K^(-1)]
#define TRAP_DEPTH -0.0003 // Minimum depth the atom has to travel before hitting fiber wall [m]
#define R_FIBER 7.5E-6 // Fiber radius [m]
#define P 0.1 // Laser power [W]

using namespace std;

float laser_intensity (Vec2 pos) {
    float wy_2 = pow(W0, 2) * (1 + pow(pos.y/YR, 2));
    float I0 = 2*P/M_PI/wy_2; // highest intensity at height y
    return I0*exp(-2*pow(pos.r, 2)/wy_2); // conformed to Gaussian distribution
}

Vec2 dipole_potential (Vec2 pos) {
    //float -3/2 * M_PI * pow(C, 2) * laser_intensity(pos);
    return Vec2(-1,-1);
}

Vec2 trajectory(Vec2 pos, Vec2 v0, Vec2 acc, float t) {
    return pos + v0 * t + acc * 1/2 * pow(t, 2);
}

Vec2 acceleration(Vec2 force, float mass) {
    return force/mass;
}

int main(int argc, char* const argv[]) {
    // args:
    // chamber height h
    // chamber diameter r
    // time step t

    float h = 1E-3;
    float r = 20E-6;
    float t = 10E-6;

    int c;
    while ((c = getopt(argc, argv, "h:r:t:")) != -1) {
        switch (c) {
            case 'h':
                h = strtoul(optarg, NULL, 10);
                if (h <= 0) {
                    printf("%s: option requires an argument > 0 -- 'h'\n", argv[0]);
                    return -1;
                }
                break;
            case 'r':
                r = strtoul(optarg, NULL, 10);
                if (r <= 0) {
                    printf("%s: option requires an argument > 0 -- 'r'\n", argv[0]);
                    return -1;
                }
                break;
            case 't':
                t = strtoul(optarg, NULL, 10);
                if (t <= 0) {
                    printf("%s: option requires an argument > 0 -- 't'\n", argv[0]);
                    return -1;
                }
                break;
            default:
                return -1;
        }
    }
    cout << "Starting simulation of atom loading with parameters: h = " << h
         << " r = " << r
         << " t = " << t << endl;


}

