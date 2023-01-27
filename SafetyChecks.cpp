//
// Created by Daniel Lifshitz on 30/11/2022.
//

#include "SafetyChecks.h"


/**
 * @brief Checks the amount of points given and the amount of points needed for the KNN algorithm is ok.
 *
 * @param k The amount of points of points needed for the KNN algorithm.
 * @param amountOfPoints The amount of points given.
 * @return true The K is ok.
 * @return false The K is not ok.
 */
bool PointsCount(long k, long amountOfPoints){
    if (k > 0 && k < amountOfPoints){
        return true;
    }
    else if (k <= 0){
        // std::cout << "K is too small, please enter a bigger number as K" << std::endl;
    }
    else{
        // std::cout << "K is too big, please enter a smaller number as K" << std::endl;
    }
    return false;
}

/**
 * Checking if all the points in the array points have the same amount of coordinates.
 * @param points The array of points we check on.
 * @return False if not all the points has the same amount of coordinates; True otherwise.
 */
bool IsSameSize(std::vector<Point> points){
    int goodSize = points[0].getAll().size();
    for(int i = 0; i < points.size(); i++){
        if (goodSize != points[i].getAll().size()){
            return false;
        }
    }
    return true;
}

/**
 * Checking if both points have vectors that are the same size.
 * @param uPoint The first point.
 * @param cPoint The second point.
 * @return True if both vectors are the same size; false otherwise.
 */
bool GoodVector(Point uPoint, Point cPoint){
    if(uPoint.getAll().size() == cPoint.getAll().size()){
        return true;
    }
    return false;
}


