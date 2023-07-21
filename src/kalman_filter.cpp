/**
 * @copyright Copyright (c) 2023
 * 
 * @file kalman_filter.cpp
 * @author Rishabh Mukund (rishabh.m96@gmail.com)
 * @brief Kalman Filter class definitions
 * @version 2.3
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

#include "kalman_filter.hpp"

#include<iostream>

using namespace Eigen;
using namespace std;


/**
 * @brief Constructor for KalmanFilter class
 * 
 * @param num_states (int) - Number of state parameters
 * @param num_states (int) - Number of independent measurements 
*/
KalmanFilter::KalmanFilter(int num_states, int num_measurements) 
    : num_states_(num_states),
      num_measurements_(num_measurements),
      H_(num_measurements, num_states),
      Q_(num_states, num_states)
    {
        I_ = MatrixXd::Identity(num_states, num_states);
    }


/**
 * @brief set obervation matrix (H) of system
 * 
 * @param H (MatrixXd) - Obervation matrix 
*/   
void KalmanFilter::setObervationMatrix(const MatrixXd& H) {
    if(H.rows() != num_measurements_ || H.cols() != num_states_) {
        throw runtime_error("Invalid dimension for obeservation matrix.");
    }
    H_ = H;
}


/**
 * @brief set initial state of the system
 * 
 * @param xi (VectorXd) - Initial state vector
 * @param Pi (MatrixXd) - Initial Process Covariance Matrix
*/
void KalmanFilter::setInitState(const VectorXd& xi, const MatrixXd& Pi) {
    if(xi.size() != num_states_ || Pi.rows() != num_states_ ||
       Pi.cols() != num_states_ ) {
        throw runtime_error("Invalid dimensions for system state.");
    }
    xe_ = xi;
    Pe_ = Pi;
}


/**
 * @brief set noise covariance matrix (Q) of system
 * 
 * @param Q (MatrixXd) - Obervation matrix  
*/
void KalmanFilter::setNoiseCovariance(const MatrixXd& Q) {
    if(Q.rows() != num_states_ || Q.cols() != num_states_) {
        throw runtime_error("Invalid dimension for noise covariance matrix.");
    }
    Q_ = Q;
}


/**
 * @brief run predicit step of Kalman Filter
 * 
 * @param A (MatrixXd) - State transition matrix
 * @param B (MatrixXd) - Control input matrix
 * @param u (VectorXd) - Control vector
*/
void KalmanFilter::predict(const MatrixXd& A, const MatrixXd& B, const VectorXd& u) {
    if(A.rows() != num_states_ || A.cols() != num_states_ ||
       B.rows() != num_states_ || B.cols() != 1 || u.size() != 1) {
        throw runtime_error("Invalid dimensions for state matrices.");
       }
    
    xp_ = (A * xe_) + (B * u);
    Pp_ = (A * Pe_ * A.transpose()) + Q_; 
}


/**
 * @brief run update step of Kalman Filter
 * 
 * @param y (VectorXd) - Measured state variables
 * @param R (MatrixXd) - Observation noise covariance matrix  
*/
void KalmanFilter::update(const VectorXd& y, const MatrixXd& R) {
    if(R.rows() != num_measurements_ || R.cols() != num_measurements_ ||
       y.size() != num_measurements_) {
        throw runtime_error("Invalid dimension for Observation noise covariance matrix.");
       }
    K_ = Pp_ * H_.transpose() * ((H_ * Pp_ * H_.transpose()) + R).inverse();
    xe_ = xp_ + K_ * (y - (H_ * xp_));
    Pe_ = (I_ - (K_ * H_)) * Pp_;
}


/**
 * @brief get Estimated state vector
 * 
 * @return (VectorXd) - Estimated state vector 
*/
VectorXd KalmanFilter::getStateEstimate() const {
    return xe_;
}


/**
 * @brief get Predicited state vector
 * 
 * @return (VectorXd) - Predicited state vector 
*/
VectorXd KalmanFilter::getStatePredicited() const {
    return xp_;
}