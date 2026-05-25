#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

void nhapmatran(vector<vector<double>> &A, int n) {
    cout << "Nhap ma tran A (" << n << "x" << n << "):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout<<"a["<<i+1<<"]["<<j+1<<"]: ";
            cin >> A[i][j];
        }
    }
}
bool doixung(const vector<vector<double>> &A, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((A[i][j] != A[j][i])) {
                return false;
            }
        }
    }
    return true;
}
bool xacdinhduong(const vector<vector<double>> &A, int n) {
    vector<vector<double>> L(n, vector<double>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            double sum = 0;
            for (int k = 0; k < j; k++) {
                sum += L[i][k] * L[j][k];
            }

            if (i == j) {
                double val = A[i][i] - sum;
                if (val <= 0) return false;
                L[i][j] = sqrt(val);
            } else {
                if (fabs(L[j][j]) < 1e-12) return false; // né chia 0
                L[i][j] = (A[i][j] - sum) / L[j][j];
            }
        }
    }
    return true;
}

bool cholesky(const vector<vector<double>> &A, vector<vector<double>> &L, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            double sum = 0;
            for (int k = 0; k < j; k++) {
                sum += L[i][k] * L[j][k];
            }
            if (i == j) {
                double val = A[i][i] - sum;
                if (val <= 0) return false; 
                L[i][j] = sqrt(val);
            } else {
                if (fabs(L[j][j]) < 1e-12) return false;
                L[i][j] = (A[i][j] - sum) / L[j][j];
            }
        }
    }
    return true;
}

int main() {
    int n;
    cout << "Nhap cap ma tran: ";
    cin >> n;

    vector<vector<double>> A(n, vector<double>(n));
    nhapmatran(A, n);
    if (!doixung(A, n)) {
        cout << "Ma tran khong doi xung!\n";
        return 0;
    }
    if (!xacdinhduong(A, n)) {
        cout << "Ma tran khong xac dinh duong!\n";
        return 0;
    }
    vector<vector<double>> L(n, vector<double>(n, 0));
    if (cholesky(A, L, n)) {
        cout << "\nMa tran L (tam giac duoi):\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << setw(10) << fixed << setprecision(2) << L[i][j] << " ";
            }
            cout << "\n";
        }
    } else {
        cout << "Khong the phan ra Cholesky!\n";
    }
    return 0;
}
