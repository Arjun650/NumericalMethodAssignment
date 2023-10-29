#include <iostream>
#include <vector>
#include <chrono>

// Function to calculate Newton's forward interpolation
double newtonForwardInterpolation(const std::vector<double>& x, const std::vector<double>& y, double value) {
    int n = x.size();
    std::vector<std::vector<double>> f(n, std::vector<double>(n, 0.0));
    // Calculate the difference table
    for (int i = 0; i < n; i++) {
        f[i][0] = y[i];
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            f[j][i] = (f[j + 1][i - 1] - f[j][i - 1]) / (x[j + i] - x[j]);
        }
    }
    // Display the difference table
    std::cout << "Difference Table:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            std::cout << f[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    // Initialize the result
    double result = f[0][0];
    double term = 1.0;
    for (int i = 0; i < n - 1; i++) {
        term *= (value - x[i]);
        result += f[i][i + 1] * term;
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
    // Calculate the interpolated longitude
    double interpolatedLongitude = newtonForwardInterpolation(x, y, latitudeToInterpolate);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    // Display the interpolated longitude
    std::cout << "Interpolated longitude at latitude " << latitudeToInterpolate << " is: " << interpolatedLongitude << std::endl;
    // Display the total runtime
    std::cout << "Total runtime: " << duration.count() << " microseconds" << std::endl;
    return 0;
}
