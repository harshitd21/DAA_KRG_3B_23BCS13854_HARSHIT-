#include <iostream>
#include <vector>
using namespace std;

int knapsackDP(const vector<int> &weights, const vector<int> &values, int n, int W) {
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= W; w++) {
            if (weights[i - 1] <= w)
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    return dp[n][W];
}

int main() {
    int n, W;
    cout << "Enter number of items: ";
    cin >> n;
    vector<int> weights(n), values(n);
    cout << "Enter weights of items: ";
    for (int i = 0; i < n; i++) cin >> weights[i];
    cout << "Enter values of items: ";
    for (int i = 0; i < n; i++) cin >> values[i];
    cout << "Enter capacity of knapsack: ";
    cin >> W;

    int maxValue = knapsackDP(weights, values, n, W);
    cout << "Maximum value in Knapsack: " << maxValue << endl;

    return 0;
}
