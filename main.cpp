#include <iostream>
#include <vector>
#include <cmath>

struct Stock {
    std::string symbol;
    double expectedReturn;
    double volatility;
};

std::vector<double> calculateOptimizedWeightsMVO(const std::vector<Stock>& portfolio, double riskFreeRate, double targetReturn) {
    size_t numAssets = portfolio.size();
    std::vector<double> weights(numAssets, 0.0);

    std::vector<std::vector<double>> covarianceMatrix(numAssets, std::vector<double>(numAssets, 0.0));
    for (size_t i = 0; i < numAssets; ++i) {
        for (size_t j = 0; j < numAssets; ++j) {
            double covariance = (i == j) ? portfolio[i].volatility * portfolio[i].volatility : 0.0;
            covarianceMatrix[i][j] = covariance;
        }
    }

    double sumExpectedReturn = 0.0;
    for (const Stock& stock : portfolio) {
        sumExpectedReturn += stock.expectedReturn;
    }

    for (size_t i = 0; i < numAssets; ++i) {
        double partialDerivative = (portfolio[i].expectedReturn - riskFreeRate) / sumExpectedReturn;
        weights[i] = partialDerivative;
    }

    double totalWeight = 0.0;
    for (size_t i = 0; i < numAssets; ++i) {
        totalWeight += weights[i];
    }

    double adjustmentFactor = targetReturn / totalWeight;
    for (size_t i = 0; i < numAssets; ++i) {
        weights[i] *= adjustmentFactor;
    }

    return weights;
}

int main() {
    std::vector<Stock> portfolio = {
            {"AAPL", 0.08, 0.2},
            {"GOOG", 0.12, 0.3},
            {"MSFT", 0.1, 0.25},
            {"AMZN", 0.15, 0.35}
    };

    double riskFreeRate = 0.05;
    double targetReturn = 0.1;

    std::vector<double> weights = calculateOptimizedWeightsMVO(portfolio, riskFreeRate, targetReturn);

    std::cout << "Optimized Weights:\n";
    for (size_t i = 0; i < portfolio.size(); ++i) {
        std::cout << portfolio[i].symbol << ": " << weights[i] << "\n";
    }

    return 0;
}
