#include <iostream>
#include <vector>
using namespace std;

//The program isn't dynamic. It's designed exactl for the case when the number of assets is 3

double variance(double w1, double w2, double w3, const vector<vector<double>>& cov) {
    int var = w1*(cov[0][0]*w1+cov[0][1]*w2+cov[0][2]*w3)+w2*(cov[1][0]*w1+cov[1][1]*w2+cov[1][2]*w3)+w3*(cov[2][0]*w1+cov[2][1]*w2+cov[2][2]*w3);
    return var;
}

double expectedPortfolioReturn(double w1, double w2, double w3, const vector<double>& expectedReturns) {
    double ret = w1*expectedReturns[0]+w2*expectedReturns[1]+w3*expectedReturns[2];
    return ret;
}

vector<double> calculateOptimizedWeightsMVO(const vector<double>& expectedReturn, const vector<vector<double>>& covarianceMatrix, double upperBound) {
    size_t numAssets = expectedReturn.size();
    vector<double> weights(numAssets, 0.0);

    double weight1, weight2, weight3, maxExpPortRet, portfolioVariance, portfolioReturn = 0.00;
    for(int i = 0; i < 100; i++) {
        for(int j = 0; j < 100; j++) {
            weight1 = (double)i/100;
            weight2 = (double)j/100;
            weight3 = (double)1 - weight1 - weight2;
            double tempVar = variance(weight1, weight2, weight3, covarianceMatrix);
            double tempRet = expectedPortfolioReturn(weight1,weight2,weight3, expectedReturn);
            bool boolean = weight1>=0 && weight2 >= 0 && weight3 >= 0;
            if(tempRet > maxExpPortRet && tempVar <= upperBound && boolean) {
                maxExpPortRet = tempRet;
                weights[0] = weight1;
                weights[1] = weight2;
                weights[2] = weight3;
                portfolioVariance = tempVar;
                portfolioReturn = tempRet;
            }
        }
    }
    cout << "The expected return of the optimal portfolio: " << portfolioReturn << endl;
    cout << "The variance of the optimal portfolio return: " << portfolioVariance << endl;
    return weights;
}

int main() {
    vector<double> expectedReturn = {0.02, 0.025, 0.03};
    vector<vector<double>> covarianceMatrix = {{1.5, 0.5, 0.3}, {0.5, 1.8, 0.6}, {0.3, 0.6, 1.2}};
    double upperBound = 0.6;

    vector<double> weights = calculateOptimizedWeightsMVO(expectedReturn, covarianceMatrix, upperBound);

    cout << "Optimized Weights:\n";
    for (size_t i = 0; i < expectedReturn.size(); ++i) {
        cout << "Asset " << i + 1 << ": " << weights[i] << "\n";
    }
    return 0;
}
