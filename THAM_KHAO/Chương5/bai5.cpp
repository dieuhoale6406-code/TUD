#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

using Matrix = vector<vector<double>>;
using Vector = vector<double>;

// Nhân 2 ma trận
Matrix nhanMaTran(const Matrix& A, const Matrix& B) {
    int n = A.size();
    int m = B[0].size();
    int p = B.size();
    Matrix C(n, vector<double>(m, 0));

    for (int i = 0; i < n; i++)
        for (int k = 0; k < p; k++)
            for (int j = 0; j < m; j++)
                C[i][j] += A[i][k] * B[k][j];

    return C;
}

// Lũy thừa ma trận
Matrix luyThuaMaTran(Matrix P, int n) {
    int size = P.size();
    Matrix res(size, vector<double>(size, 0));
    for (int i = 0; i < size; i++)
        res[i][i] = 1;

    while (n > 0) {
        if (n % 2 == 1)
            res = nhanMaTran(res, P);
        P = nhanMaTran(P, P);
        n /= 2;
    }
    return res;
}

// Vector × Ma trận
Vector nhanVectorMaTran(const Vector& v, const Matrix& A) {
    int n = v.size();
    Vector result(n, 0);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[j] += v[i] * A[i][j];

    return result;
}

int main() {
    int S;
    cout << "Nhap so luong trang thai S: ";
    cin >> S;

    Matrix P(S, vector<double>(S));
    cout << "\nNhap ma tran chuyen trang thai P:\n";
    for (int i = 0; i < S; i++)
        for (int j = 0; j < S; j++) {
            cout << "P[" << i+1 << "][" << j+1 << "] = ";
            cin >> P[i][j];
        }

    Vector m(S);
    cout << "\nNhap vector trang thai ban dau m:\n";
    for (int i = 0; i < S; i++) {
        cout << "m[" << i+1 << "] = ";
        cin >> m[i];
    }

    int n, k;
    cout << "\nNhap so buoc thoi gian n: ";
    cin >> n;

    cout << "Nhap trang thai can tinh k: ";
    cin >> k;
    k--; // về chỉ số 0

    Matrix Pn = luyThuaMaTran(P, n);
    Vector ketQua = nhanVectorMaTran(m, Pn);

    cout << fixed << setprecision(6);
    cout << "\nXac suat he thong o trang thai "
         << k + 1 << " sau " << n << " buoc = "
         << ketQua[k] << endl;

    return 0;
}
