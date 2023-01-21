#ifndef AP_TASK3_calcDist_HPP
#define AP_TASK3_calcDist_HPP


#include <math.h>
#include "../PointFiles/Point.h"

/**
 * Distance metrics.
 */
double Euclidan(std::vector<double>, std::vector<double>);
double Manhattan(std::vector<double>, std::vector<double>);
double Chebyshev(std::vector<double>, std::vector<double>);
double Canberra(std::vector<double>, std::vector<double>);
double Minkowski(std::vector<double>, std::vector<double>, int);


double calcDistance(std::string, std::vector<double>, Point);
#endif //AP_TASK3_calcDist_HPP