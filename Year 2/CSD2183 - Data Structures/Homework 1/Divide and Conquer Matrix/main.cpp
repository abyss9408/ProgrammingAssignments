#include <chrono>
#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <numeric> // for std::accumulate
#include <cmath>   // for std::pow

#include "matrix_utilities.h"
#include "matmul_divide_and_conquer.h"
#include "matmul_strassens.h"

using namespace std;

int main() {

    // *** Note: adjust your starting and stoping benchmark sizes using 
    // the variables 'start_size' and 'stop_size' respectively
    int start_size = 8; // multiple of 2
    int stop_size = 256; // mutliple of 2

    // column size to display simple table output.
    int display_width = 16; 

    vector<double> a_sizes;
    vector<double> basic_times;
    vector<double> stras_times;
    vector<double> log_a_sizes;
    vector<double> log_basic_times;
    vector<double> log_stras_times;

    cout << setw(display_width) << "dimension" 
         << setw(display_width) << "log(dimension)" 
         << setw(display_width) << "log(basic_ms)" 
         << setw(display_width) << "log(strassen_ms)" << endl;
    for (int dimension=start_size; dimension<=stop_size; dimension*=2){

        vector<vector<double>> mA, mB, mC1, mC2;
        mA.resize(dimension, std::vector<double>(dimension));
        mB.resize(dimension, std::vector<double>(dimension));

        randomizeMatrix(mA,dimension,-1.0,1.0);
        randomizeMatrix(mB,dimension,-1.0,1.0);

        chrono::time_point<chrono::high_resolution_clock> start1, start2, end1, end2;
        int m;

        start1 = chrono::high_resolution_clock::now();
        int rounds = (int)((stop_size)/dimension);
        for (m = 0; m<rounds; m++) {
            mC1 = divideAndConquerMultiply(mA, mB, dimension);
        }
        end1 = chrono::high_resolution_clock::now();
        start2 = chrono::high_resolution_clock::now();
        for (m = 0; m<rounds; m++) {
            mC2 = strassenMatrixMultiplication(mA, mB, dimension);
          }
        end2 = chrono::high_resolution_clock::now();

        int duration1 = chrono::duration_cast<chrono::microseconds>(end1 - start1).count();
        int duration2 = chrono::duration_cast<chrono::microseconds>(end2 - start2).count();

        double t1 = (duration1 * 0.001)/rounds;
        double t2 = (duration2 * 0.001)/rounds;
        double log_dim = log(dimension);
        double log_t1 = log(t1);
        double log_t2 = log(t2);

        // Display log values
        cout << setw(display_width) << dimension;
        cout << setw(display_width) << log_dim;
        cout << setw(display_width) << log_t1;
        cout << setw(display_width) << log_t2;
        cout << endl;

        a_sizes.push_back(dimension);
        basic_times.push_back(t1);
        stras_times.push_back(t2);
        log_a_sizes.push_back(log(dimension));
        log_basic_times.push_back(log(t1));
        log_stras_times.push_back(log(t2));

        #ifdef __DEBUG__
        // Display the matrices
        cout << "Matrix C1:" << endl;
        printMatrix(mC1);
        cout << "Matrix C2:" << endl;
        printMatrix(mC2);
        if (!isEqualMatrix(mC1, mC2, dimension)) {
            cout << "FAIL" << endl;
            return 1;
        } 
        #endif//__DEBUG__
    }


    // Generate Vega-Lite JSON specification  
    // nlohmann::json spec = generate_vega_lite_spec(
    //     vector<vector<double>>({log_a_sizes, log_a_sizes}),
    //     vector<vector<double>>({log_basic_times, log_stras_times}),
    //     vector<string>({"log(basic)", "log(strassen)"}),
    //     "log(Array Size)",
    //     "log(Running Time/msec)"
    // );

    // // Generate HTML file
    // generate_html(spec, "matmul_plot.html");  
    return 0;
}
