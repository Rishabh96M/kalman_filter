/**
 * @copyright Copyright (c) 2023
 * 
 * @file kalman_filter.hpp
 * @author Rishabh Mukund (rishabh.m96@gmail.com)
 * @brief Kalman Filter class declaration
 * @version 2.2
 * @date 14/07/2023
 * 
 * 
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
*/

#pragma once

#include <Eigen/Dense>


using namespace Eigen;

class KalmanFilter {
private:
    int num_states_;        // Number of state parameters
    int num_measurements_;  // Number of independent measurements

    MatrixXd H_;   // Observation Model Matrix
    MatrixXd Q_;   // Process Noise Covariance Matrix
    MatrixXd Pp_;  // Process Covariance Matrix (Predicited)
    MatrixXd Pe_;  // Process Covariance Matrix (Estimated)
    MatrixXd K_;   // Kalman Gain Matrix
    MatrixXd I_;   // Identity Matrix

    VectorXd xp_;  // state vector (Predicited)
    VectorXd xe_;  // state vector (Estimated)


public:
    /**
     * @brief Constructor for KalmanFilter class
     * 
     * @param num_states (int) - Number of state parameters
     * @param num_states (int) - Number of independent measurements 
    */
    KalmanFilter(int num_states, int num_measurements);


    /**
     * @brief set obervation matrix (H) of system
     * 
     * @param H (MatrixXd) - Obervation matrix 
    */    
    void setObervationMatrix(const MatrixXd& H);
    

    /**
     * @brief set initial state of the system
     * 
     * @param xi (VectorXd) - Initial state vector
     * @param Pi (MatrixXd) - Initial Process Covariance Matrix
    */
    void setInitState(const VectorXd& xi, const MatrixXd& Pi);
    
    
    /**
     * @brief set noise covariance matrix (Q) of system
     * 
     * @param Q (MatrixXd) - Obervation matrix  
    */
    void setNoiseCovariance(const MatrixXd& Q);
    
    
    /**
     * @brief run predicit step of Kalman Filter
     * 
     * @param A (MatrixXd) - State transition matrix
     * @param B (MatrixXd) - Control input matrix
     * @param u (VectorXd) - Control vector
    */
    void predict(const MatrixXd& A, const MatrixXd& B, const VectorXd& u);
    
    
    /**
     * @brief run update step of Kalman Filter
     * 
     * @param y (VectorXd) - Measured state variables
     * @param R (MatrixXd) - Observation noise covariance matrix  
    */
    void update(const VectorXd& y, const MatrixXd& R);
    

    /**
     * @brief get Estimated state vector
     * 
     * @return (VectorXd) - Estimated state vector 
    */
    VectorXd getStateEstimate() const;
    
    
    /**
     * @brief get Predicited state vector
     * 
     * @return (VectorXd) - Predicited state vector 
    */
    VectorXd getStatePredicited() const;
};