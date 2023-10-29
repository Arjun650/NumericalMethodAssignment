#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
// Function to calculate the Lagrange basis polynomial for inverse interpolation
double lagrangeBasisInverse(const std::vector<double>& x, int k, double value) {
    double result = 1.0;
    int n = x.size();
    for (int i = 0; i < n; i++) {
        if (i != k) {
            result *= (value - x[i]) / (x[k] - x[i]);
        }
    }
    return result;
}
// Function to perform Lagrange inverse interpolation
double lagrangeInverseInterpolation(const std::vector<double>& x, const std::vector<double>& y, double value) {
    int n = x.size();
    double result = 0.0;
    for (int k = 0; k < n; k++) {
        result += y[k] * lagrangeBasisInverse(x, k, value);
    }
    return result;
}
int main() {
    // Sample navigation data (latitude and longitude)
    std::vector<double> x = {0.0, 1.0, 2.0, 3.0, 4.0}; // Sample latitude values
    std::vector<double> y = {0.0, 1.0, 4.0, 9.0, 16.0}; // Sample longitude values
    double longitudeToInterpolate = 7.0; // Longitude for which we want to perform inverse interpolation
    // Measure the runtime
    auto start = std::chrono::high_resolution_clock::now();
    // Calculate the interpolated latitude using Lagrange inverse interpolation
    double interpolatedLatitude = lagrangeInverseInterpolation(y, x, longitudeToInterpolate);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    // Display the interpolated latitude
    std::cout << "Interpolated latitude at longitude " << longitudeToInterpolate << " is: " << interpolatedLatitude << std::endl;
    // Display the total runtime
    std::cout << "Total runtime: " << duration.count() << " microseconds" << std::endl; 
    return 0;
}
