/**
 * @copyright Copyright (c) 2023
 * 
 * @file utils.hpp
 * @author Rishabh Mukund (rishabh.m96@gmail.com)
 * @brief Helper methods declaration
 * @version 1.2
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

#include<random>
#include<vector>
#include<map>


using namespace std;

/**
 * @brief Generate points from a normal distribution with given 
 *        mean and standard deviation
 * 
 * @param mean (double) - mean of normal distribution
 * @param stddev (double) - standard deviation of normal distribution
 * @param len (int) - number of points from normal deviation 
 * 
 * @return vector<double> - vector of points from normal distribution 
*/
vector<double> errorGenerator(double mean, double stddev, int len);


/**
 * @brief Get timestamps and positon data from single sensor
 * @details Data in file should be comma seperated values. (eg time, pos)
 * 
 * @param filename (string) - File path and name to extract data from 
 * @param timestamps (vector<double>&) - reference of vector to push timestamps 
 * @param gt_pos (vector<double>&) - reference of vector to push positions
*/
void getData(string filename, vector<double>& timestamps,
    vector<double>& gt_pos);


/**
 * @brief merge timestamps and positon data from two sensor
 * @details Data in file should be comma seperated values. (eg time, pos)
 * 
 * @param filename1 (string) - File path and name to extract data of sensor 1
 * @param filename2 (string) - File path and name to extract data of sensor 2
 * @param timestamps (vector<double>&) - reference of vector to push timestamps 
 * @param noise_pos (vector<double>&) - reference of vector to push positions 
 * @param sensor (vector<int>&) - reference of vector to corresponding sensor
*/
void getData(string filename1, string filename2, vector<double>& timestamps,
    vector<double>& noise_pos, vector<int>& sensor);


/**
 * @brief Write timestamps and corresponding ground truth, estimated and error 
 *        positons to text file
 * @details Data will be stored in file with comma seperated values
 *          (format : timestamps, gt_pos, noise_pos, est_pos, error_in_pos)
 * 
 * @param filename (string) - File path and name to store data
 * @param timestamps (vector<double>&) - reference of vector with timestamps 
 * @param gt_pos (vector<double>&) - reference of vector with GT positions 
 * @param error (vector<double>&) - reference of vector with generated error
 * @param est_pos (vector<double>&) - reference of vector with estimated positions
*/
void writeData(string filename, vector<double>& timestamps,
    vector<double>& gt_pos, vector<double>& error, vector<double>& est_pos);


/**
 * @brief Write timestamps and corresponding ground truth, estimated and error 
 *        positons to text file
 * @details Data will be stored in file with comma seperated values
 *          (format : timestamps, gt_pos, est_pos, error_in_pos)
 * 
 * @param filename (string) - File path and name to store data
 * @param timestamps (vector<double>&) - reference of vector with timestamps 
 * @param gt_pos (vector<double>&) - reference of vector with GT positions 
 * @param est_pos (vector<double>&) - reference of vector with estimated positions
*/
void writeData(string filename, vector<double>& timestamps,
    vector<double>& gt_pos, vector<double>& est_pos);