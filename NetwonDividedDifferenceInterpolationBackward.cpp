#include <iostream>
#include <vector>
#include <chrono>

// Function to calculate divided differences for backward interpolation
std::vector<std::vector<double>> calculateDividedDifferences(const std::vector<double>& x, const std::vector<double>& y) {
    int n = x.size();
    std::vector<std::vector<double>> f(n, std::vector<double>(n, 0.0));

    // Initialize the first column of the divided differences table
    for (int i = 0; i < n; i++) {
        f[i][0] = y[i];
    }

    // Calculate the divided differences for backward interpolation
    for (int j = 1; j < n; j++) {
        for (int i = n - 1; i >= j; i--) {
            f[i][j] = f[i][j - 1] - f[i - 1][j - 1];
        }
    }
    return f;
}

// Function to display the divided differences table
void displayDividedDifferencesTable(const std::vector<std::vector<double>>& f) {
    int n = f.size();

    std::cout << "Divided Differences Table (Backward Interpolation):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            std::cout << f[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

// Function to perform Newton's divided difference backward interpolation
double newtonDividedDifferenceBackwardInterpolation(const std::vector<double>& x, const std::vector<double>& y, double value) {
    int n = x.size();
    std::vector<std::vector<double>> f = calculateDividedDifferences(x, y);

    double result = f[n - 1][0];
    double term = 1.0;

    for (int i = 1; i < n; i++) {
        term *= (value - x[n - 1]) / (x[n - 1 - i] - x[n - 1]);
        result += f[n - 1][i] * term;
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

    // Calculate the interpolated longitude using Newton's divided difference backward interpolation
    double interpolatedLongitude = newtonDividedDifferenceBackwardInterpolation(x, y, latitudeToInterpolate);

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    // Display the divided differences table
    std::vector<std::vector<double>> dividedDifferencesTable = calculateDividedDifferences(x, y);
    displayDividedDifferencesTable(dividedDifferencesTable);

    // Display the interpolated longitude
    std::cout << "Interpolated longitude at latitude " << latitudeToInterpolate << " is: " << interpolatedLongitude << std::endl;

    // Display the total runtime
    std::cout << "Total runtime: " << duration.count() << " microseconds" << std::endl;

    return 0;
}
