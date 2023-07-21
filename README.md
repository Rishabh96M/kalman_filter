Verified with gcc 9.4.0 on ubuntu 20.04.1 and packages used are Eigen3 and C++ STL

# Kalman Filter
A C++ package for Kalman Filter class and helper methods for sensor fusion. 
Test code provided for "estimating signal by removing noise" and for "sensor fusion to predicit 
positon based on measurements from 2 independent sensors with different sampling rates". 

## Steps to build the package and run the test code
To Build the package:
```
cd <path_to_package>/kalman_filter
mkdir build
cd build
cmake ..
make
```

To run the test code:
```
cd build
./KalmanFilter
```

## To install the dependencies
```
sudo apt update -y
sudo apt install libeigen3-dev
```

## To plot the graphs
```
cd <path_to_package>/kalman_filter
python3 plot.py
```

The ***results*** folder contains the results of the test code.
