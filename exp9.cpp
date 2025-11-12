#include <iostream>
#include <vector>
using namespace std;

vector<int> computeLPS(const string &P) {
    int m = P.size();
    vector<int> lps(m, 0);
    int len = 0;
    int i = 1;
    while (i < m) {
        if (P[i] == P[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

vector<int> KMPSearch(const string &S, const string &P) {
    int n = S.size();
    int m = P.size();
    vector<int> lps = computeLPS(P);
    vector<int> occurrences;
    int i = 0, j = 0;
    while (i < n) {
        if (S[i] == P[j]) {
            i++;
            j++;
        }
        if (j == m) {
            occurrences.push_back(i - j);
            j = lps[j - 1];
        } else if (i < n && S[i] != P[j]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
    return occurrences;
}

int main() {
    string S, P;
    cout << "Enter string S: ";
    cin >> S;
    cout << "Enter pattern P: ";
    cin >> P;

    vector<int> result = KMPSearch(S, P);
    if (result.empty())
        cout << "Pattern not found\n";
    else {
        cout << "Pattern found at indices: ";
        for (int idx : result)
            cout << idx << " ";
        cout << endl;
    }

    return 0;
}
