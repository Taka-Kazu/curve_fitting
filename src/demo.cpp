#include "curve_fitting/curve_fitting.h"

int main(int argc, char** argv)
{
    {
        curve_fitting::CurveFitting2D cf;
        auto f = [](double x){return 1/1000.*(x-1)*(x-1)+3;};
        std::vector<Eigen::Vector2d> points;
        for(double x=-10.0;x<10.0;x+=1){
            points.emplace_back(Eigen::Vector2d(x, f(x)));
            // std::cout << points.back().transpose() << std::endl;
        }
        auto coeff = cf.calculate(points);
        if(coeff.size() > 0){
            std::cout << "x^2" << " + " << coeff[0] << "xy" << " + " << coeff[1] << "y^2" << " + " << coeff[2] << "x" << " + " << coeff[3] << "y" << " + " << coeff[4] << std::endl;
            for(unsigned int i=0;i<points.size();i++){
                auto y = cf.get_y_from_x(coeff, points[i](0));
                if(y.size() == 1){
                    std::cout << points[i].transpose() << ", " << y[0] << std::endl;
                }else if(y.size() == 2){
                    std::cout << points[i].transpose() << ", " << y[0] << ", " << y[1] << std::endl;
                }
            }
        }else{
            std::cout << "failed" << std::endl;
        }
    }
    {
        curve_fitting::CurveFitting2D cf;
        std::vector<Eigen::Vector2d> points;
        points.push_back(Eigen::Vector2d(0, 0));
        points.push_back(Eigen::Vector2d(1, 1));
        points.push_back(Eigen::Vector2d(2, 3));
        points.push_back(Eigen::Vector2d(3, 4));
        auto coeff = cf.calculate(points);
        if(coeff.size() > 0){
            std::cout << "x^2" << " + " << coeff[0] << "xy" << " + " << coeff[1] << "y^2" << " + " << coeff[2] << "x" << " + " << coeff[3] << "y" << " + " << coeff[4] << std::endl;
        }else{
            std::cout << "failed" << std::endl;
        }
    }

    return 0;
}
