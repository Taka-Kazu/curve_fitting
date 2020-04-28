#ifndef __CURVE_FITTING_H
#define __CURVE_FITTING_H

#include <iostream>
#include <vector>
#include <cassert>

#include <Eigen/Dense>
#include <boost/optional.hpp>

namespace curve_fitting
{

/*
 * 2D curve (parabola) fitting
 * This class calculates coefficients of 2D-parabola approximating given points.
 * x^2 + axy + by^2 + cx + dy + e = 0
 * return a, b, c, d, e
 */

class CurveFitting2D
{
public:
    CurveFitting2D(void);

    std::vector<double> calculate(const std::vector<Eigen::Vector2d>&);
    double square(double);
    double cube(double);
    std::vector<double> get_y_from_x(const std::vector<double>&, double);

protected:
};

};

#endif// __CURVE_FITTING_H
