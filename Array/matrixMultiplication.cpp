#include <bits/stdc++.h>
using namespace std;

void matrixMultiply(vector<vector<int>> &A,
                    vector<vector<int>> &B,
                    vector<vector<int>> &C) {
    int n = A.size();
    int m = B[0].size();
    int p = B.size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            C[i][j] = 0;
            for (int k = 0; k < p; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    vector<vector<int>> A = {{1, 2}, {3, 4}};
    vector<vector<int>> B = {{5, 6}, {7, 8}};
    vector<vector<int>> C(2, vector<int>(2));

    matrixMultiply(A, B, C);

    for (auto &row : C) {
        for (int x : row) cout << x << " ";
        cout << endl;
    }
    return 0;
}
