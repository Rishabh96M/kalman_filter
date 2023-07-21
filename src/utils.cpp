/**
 * @copyright Copyright (c) 2023
 * 
 * @file utils.cpp
 * @author Rishabh Mukund (rishabh.m96@gmail.com)
 * @brief helper fucntion defintions
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

#include "utils.hpp"

#include<string>
#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>


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
vector<double> errorGenerator(double mean, double stddev, int len) {
    random_device rd;
    std::mt19937 generator(rd());
    normal_distribution<double> distribution(mean, stddev);

    vector<double> error(len);

    for(int i = 0; i < len; i++) {
        error[i] = distribution(generator);
    }

    return error;
}


/**
 * @brief Get timestamps and positon data from single sensor
 * @details Data in file should be comma seperated values. (eg time, pos)
 * 
 * @param filename (string) - File path and name to extract data from 
 * @param timestamps (vector<double>&) - reference of vector to push timestamps 
 * @param gt_pos (vector<double>&) - reference of vector to push positions
*/
void getData(string filename, vector<double>& timestamps, vector<double>& gt_pos) {
    ifstream file(filename);
    if(!file.is_open()) {
        throw runtime_error("Failed to open file: " + filename);
    }

    string line;
    while(getline(file, line)) {
        stringstream ss(line);
        string token;

        getline(ss, token, ',');
        timestamps.push_back(stod(token));

        getline(ss, token, ',');
        gt_pos.push_back(stod(token));
    }

    file.close();
}


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
void getData(string filename1, string filename2, vector<double>& timestamps, vector<double>& noise_pos, vector<int>& sensor) {
    ifstream file1(filename1);
    ifstream file2(filename2);

    if(!file1.is_open()) {
        throw runtime_error("Failed to open file: " + filename1);
    }

    if(!file2.is_open()) {
        throw runtime_error("Failed to open file: " + filename1);
    }

    string line1;
    string line2;
    string token;
    double ts1;
    double ts2;
    double pos1;
    double pos2;

    getline(file1, line1);
    stringstream ss1(line1);
    getline(ss1, token, ',');
    ts1 = stod(token);
    getline(ss1, token, ',');
    pos1 = stod(token);


    getline(file2, line2);
    stringstream ss2(line2);
    getline(ss2, token, ',');
    ts2 = stod(token);
    getline(ss2, token, ',');
    pos2 = stod(token);

    // merging data from 2 sensors
    while(true) {
        if(ts1 < ts2) {
            timestamps.push_back(ts1);
            noise_pos.push_back(pos1);
            sensor.push_back(1);

            if(getline(file1, line1)) {
                stringstream ss1(line1);
                getline(ss1, token, ',');
                ts1 = stod(token);
                getline(ss1, token, ',');
                pos1 = stod(token);
            }
            else
                break;
        }
        else if(ts2 < ts1) {
            timestamps.push_back(ts2);
            noise_pos.push_back(pos2);
            sensor.push_back(2);

            if(getline(file2, line2)) {
                stringstream ss2(line2);
                getline(ss2, token, ',');
                ts2 = stod(token);
                getline(ss2, token, ',');
                pos2 = stod(token);
            }
            else
                break;
        }
        else {
            timestamps.push_back(ts2);
            timestamps.push_back(ts2);
            noise_pos.push_back(pos1);
            noise_pos.push_back(pos2);
            sensor.push_back(3);
            sensor.push_back(3);

            if(getline(file1, line1) && getline(file2, line2)) {
                stringstream ss1(line1);
                getline(ss1, token, ',');
                ts1 = stod(token);
                getline(ss1, token, ',');
                pos1 = stod(token);

                stringstream ss2(line2);
                getline(ss2, token, ',');
                ts2 = stod(token);
                getline(ss2, token, ',');
                pos2 = stod(token);
            }
            else
                break;
        }
    }

    file1.close();
    file2.close();
}


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
void writeData(string filename, vector<double>& timestamps, vector<double>& gt_pos, vector<double>& error, vector<double>& est_pos) {
    ofstream file(filename);
    if(!file.is_open()) {
        throw runtime_error("Failed to to open file: " + filename);
    }

    for(int i = 0; i < timestamps.size(); i++) { 
        file << to_string(timestamps[i]) << ',' << gt_pos[i] << ',' << gt_pos[i] + error[i];
        file << ',' << est_pos[i] << ',' << gt_pos[i] - est_pos[i] << "\n"; 
    }

    file.close();
    cout << "File written successfully.\n"; 
}


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
void writeData(string filename, vector<double>& timestamps, vector<double>& gt_pos, vector<double>& est_pos) {
    ofstream file(filename);
    if(!file.is_open()) {
        throw runtime_error("Failed to to open file: " + filename);
    }

    for(int i = 0; i < timestamps.size(); i++) { 
        file << to_string(timestamps[i]) << ',' << gt_pos[i] << ',' << est_pos[i];
        file << ',' << gt_pos[i] - est_pos[i] << "\n"; 
    }

    file.close();
    cout << "File written successfully.\n";  
}