#include "curve_fitting/curve_fitting.h"

namespace curve_fitting
{

CurveFitting2D::CurveFitting2D(void)
{
}

std::vector<double> CurveFitting2D::calculate(const std::vector<Eigen::Vector2d>& data_)
{
    if(data_.size() <3){
        std::cout << "data size must be >= 3" << std::endl;
        return std::vector<double>(0);
    }
    // coeff = mat^(-1) * vec
    Eigen::VectorXd coeff = Eigen::VectorXd::Zero(5);
    Eigen::MatrixXd mat = Eigen::MatrixXd::Zero(5, 5);
    Eigen::VectorXd vec = Eigen::VectorXd::Zero(5);
    for(const auto& p : data_){
        double x = p(0);
        double y = p(1);
        double x2 = square(x);
        double y2 = square(y);
        double x3 = cube(x);
        double y3 = cube(y);
        double y4 = y2 * y2;

        mat(0, 0) += x2 * y2;
        mat(0, 1) += x * y3;
        mat(0, 2) += x2 * y;
        mat(0, 3) += x * y2;
        mat(0, 4) += x * y;
        mat(1, 1) += y4;
        mat(1, 3) += y3;
        mat(1, 4) += y2;
        mat(2, 2) += x2;
        mat(2, 4) += x;
        mat(3, 4) += y;
        mat(4, 4) += 1;
        vec(0) += x3 * y;
        vec(1) += x2 * y2;
        vec(2) += x3;
        vec(3) += x2 * y;
        vec(4) += x2;
    }
    mat(1, 0) = mat(0, 1);
    mat(2, 0) = mat(0, 2);
    mat(1, 2) = mat(2, 1) = mat(3, 0) = mat(0, 3);
    mat(3, 1) = mat(1, 3);
    mat(4, 1) = mat(3, 3) = mat(1, 4);
    mat(4, 0) = mat(3, 2) = mat(2, 3) = mat(0, 4);
    mat(4, 2) = mat(2, 4);
    mat(4, 3) = mat(3, 4);
    vec = -vec;

    coeff = mat.inverse() * vec;
    // std::cout << mat << std::endl;
    // std::cout << std::endl;
    // std::cout << mat.inverse() << std::endl;
    // std::cout << std::endl;
    // std::cout << vec << std::endl;
    // std::cout << std::endl;
    if(std::isnan(coeff.norm()) || std::isinf(coeff.norm())){
        return std::vector<double>(0);
    }
    std::vector<double> coeff_(5, 0.0);
    for(unsigned int i=0;i<5;i++){
        coeff_[i] = std::abs(coeff(i)) > 1e-6 ? coeff(i) : 0.0;
    }
    return coeff_;
}

double CurveFitting2D::square(double x)
{
    return x * x;
}

double CurveFitting2D::cube(double x)
{
    return x * x * x;
}

std::vector<double> CurveFitting2D::get_y_from_x(const std::vector<double>& coeff, double x)
{
    if(std::abs(coeff[1]) > 1e-6){
        // |b|>0
        // s = (ax+d)/b
        double s = (coeff[0] * x + coeff[3]) / coeff[1];
        // t = (x^2+cx+e)/b
        double t = (square(x) + coeff[2] * x + coeff[4]) / coeff[1];
        // y^2+sy+t=0
        double u = std::sqrt(s * s - 4 * t);
        auto y_vec = std::vector<double>(2, 0);
        y_vec[0] = -(s + u) / 2.0;
        y_vec[1] = -(s - u) / 2.0;
        return y_vec;
    }else{
        double denominator = coeff[0] * x + coeff[3];
        if(std::abs(denominator) > 1e-6){
            // |ax+d|>0
            return std::vector<double>(1, -(square(x) + coeff[2] * x + coeff[4]) / denominator);
        }
    }
    return std::vector<double>(0);
}

};
