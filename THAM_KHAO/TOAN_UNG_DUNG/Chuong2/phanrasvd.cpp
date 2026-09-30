#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <algorithm>
using namespace std;

#define EPS 1e-5
#define MAX_ITER 500

vector<vector<double>> nhanmatran(const vector<vector<double>>& A, const vector<vector<double>>& B) {
    int n = A.size(), m = B[0].size(), p = B.size();
    vector<vector<double>> C(n, vector<double>(m, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (int k = 0; k < p; k++)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}

vector<vector<double>> chuyenvi(const vector<vector<double>>& A) {
    int n = A.size(), m = A[0].size();
    vector<vector<double>> B(m, vector<double>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            B[j][i] = A[i][j];
    return B;
}

void chuanhoa(vector<double>& v) {
    double norm = 0;
    for (double x : v) norm += x * x;
    norm = sqrt(norm);
    if (norm < EPS) return;
    for (double &x : v) x /= norm;
}

pair<double, vector<double>> tririengpoweriteration(const vector<vector<double>>& A) {
    int n = A.size();
    vector<double> v(n, 1.0);
    chuanhoa(v);
    double lambda = 0;
    for (int iter = 0; iter < MAX_ITER; iter++) {
        vector<double> Av(n, 0);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                Av[i] += A[i][j] * v[j];

        double newlambda = 0;
        for (int i = 0; i < n; i++) newlambda += v[i] * Av[i];

        if (fabs(newlambda - lambda) < EPS) break;
        lambda = newlambda;
        v = Av;
        chuanhoa(v);
    }
    return make_pair(lambda, v);
}

void deflation(vector<vector<double>>& A, double lambda, const vector<double>& v) {
    int n = A.size();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            A[i][j] -= lambda * v[i] * v[j];
}

void phanraSVD(const vector<vector<double>>& A) {
    int m = A.size(), n = A[0].size();
    vector<vector<double>> AT = chuyenvi(A);
    vector<vector<double>> ATA = nhanmatran(AT, A);
    vector<pair<double, vector<double>>> eigens;
    vector<vector<double>> B = ATA;
    for (int i = 0; i < n; i++) {
        auto result = tririengpoweriteration(B);
        double lambda = result.first;
        vector<double> v = result.second;
        eigens.push_back({lambda, v});
        deflation(B, lambda, v);
    }

    // Sắp xếp theo trị riêng giảm dần
    sort(eigens.begin(), eigens.end(), [](auto &a, auto &b) {
        return a.first > b.first;
    });

    // V
    vector<vector<double>> V(n, vector<double>(n));
    vector<double> sigma;
    for (int i = 0; i < n; i++) {
        sigma.push_back(sqrt(max(eigens[i].first, 0.0)));
        for (int j = 0; j < n; j++)
            V[j][i] = eigens[i].second[j];
    }
    // U
    vector<vector<double>> U(m, vector<double>(m, 0));
    for (int i = 0; i < n; i++) {
        vector<double> Av(m, 0);
        for (int j = 0; j < m; j++)
            for (int k = 0; k < n; k++)
                Av[j] += A[j][k] * V[k][i];
        if (sigma[i] > EPS) {
            for (int j = 0; j < m; j++)
                U[j][i] = Av[j] / sigma[i];
        }
    }

    // Bổ sung vector trực chuẩn thiếu trong U
    for (int k = n; k < m; k++) {
        vector<double> u(m, 0);
        u[k] = 1.0;
        for (int j = 0; j < k; j++) {
            double dot = 0;
            for (int i = 0; i < m; i++) dot += U[i][j] * u[i];
            for (int i = 0; i < m; i++) u[i] -= dot * U[i][j];
        }
        chuanhoa(u);
        for (int i = 0; i < m; i++) U[i][k] = u[i];
    }
    cout << "\nMa tran U:\n";
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++)
            cout << setw(10) << fixed << setprecision(4) << U[i][j] << " ";
        cout << "\n";
    }
    cout << "\nGia tri ky di (Sigma):\n";
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j && j < sigma.size())
                cout << setw(10) << fixed << setprecision(4) << sigma[j];
            else
                cout << setw(10) << 0.0;
        }
        cout << "\n";
    }

    cout << "\nMa tran V:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << setw(10) << fixed << setprecision(4) << V[i][j] << " ";
        cout << "\n";
    }
}
int main() {
    int m, n;
    cout << "Nhap kich thuoc ma tran m n: ";
    cin >> m >> n;

    vector<vector<double>> A(m, vector<double>(n));
    cout << "Nhap ma tran A:\n";
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            cin >> A[i][j];

    phanraSVD(A);
    return 0;
}
