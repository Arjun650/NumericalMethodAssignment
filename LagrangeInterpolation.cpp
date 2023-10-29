#include <iostream>
#include <vector>
#include <chrono>
// Function to calculate the Lagrange basis polynomial for interpolation
double lagrangeBasis(const std::vector<double>& x, int k, double value) {
    double result = 1.0;
    int n = x.size();
    for (int i = 0; i < n; i++) {
        if (i != k) {
            result *= (value - x[i]) / (x[k] - x[i]);
        }
    }
    return result;
}
// Function to perform Lagrange interpolation
double lagrangeInterpolation(const std::vector<double>& x, const std::vector<double>& y, double value) {
    int n = x.size();
    double result = 0.0;
    for (int k = 0; k < n; k++) {
        result += y[k] * lagrangeBasis(x, k, value);
    }
    return result;
}
int main() {
    // Sample navigation data (latitude and longitude)
    std::vector<double> x = {0.0, 1.0, 2.0, 3.0, 4.0}; // Sample latitude values
    std::vector<double> y = {0.0, 1.0, 4.0, 9.0, 16.0}; // Sample longitude values
    double latitudeToInterpolate = 2.5; // Latitude for which we want to interpolate
    // Measure the runtime
    auto start = std::chrono::high_resolution_clock::now();
    // Calculate the interpolated longitude using Lagrange interpolation
    double interpolatedLongitude = lagrangeInterpolation(x, y, latitudeToInterpolate);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    // Display the interpolated longitude
    std::cout << "Interpolated longitude at latitude " << latitudeToInterpolate << " is: " << interpolatedLongitude << std::endl;
    // Display the total runtime
    std::cout << "Total runtime: " << duration.count() << " microseconds" << std::endl;
    return 0;
}
