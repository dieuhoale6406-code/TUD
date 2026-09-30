// ma trận nghịch đảo
#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;
#define EPS 1e-6   
void nhapmatran(double a[20][40], int n) {
    cout << "Nhap ma tran A (" << n << "x" << n << "):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout<<"a["<<i+1<<"]["<<j+1<<"]: ";
            cin >> a[i][j];
        }
    }
}
void ghepmatrandonvi(double a[20][40], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = n; j < 2 * n; j++) {
            a[i][j] = (i == j - n) ? 1.0 : 0.0;
        }
    }
}
int timpivot(double a[20][40], int n, int i) {
    int pivot = i;
    for (int j = i + 1; j < n; j++) {
        if (fabs(a[j][i]) > fabs(a[pivot][i]))
            pivot = j;
    }
    return pivot;
}
void doihang(double a[20][40], int n, int r1, int r2) {
    for (int j = 0; j < 2 * n; j++)
        swap(a[r1][j], a[r2][j]);
}
void chuanhoahang(double a[20][40], int n, int i) {
    double div = a[i][i];
    for (int j = 0; j < 2 * n; j++)
        a[i][j] /= div;
}
void khuhang(double a[20][40], int n, int i) {
    for (int k = 0; k < n; k++) {
        if (k != i) {
            double factor = a[k][i];
            for (int j = 0; j < 2 * n; j++) {
                a[k][j] -= factor * a[i][j];
            }
        }
    }
}
bool nghichdao(double a[20][40], int n) {
    for (int i = 0; i < n; i++) {
        int pivot = timpivot(a, n, i);
        if (fabs(a[pivot][i]) < EPS) return false;
        if (pivot != i) doihang(a, n, i, pivot);

        chuanhoahang(a, n, i);
        khuhang(a, n, i);
    }
    return true;
}
void inketqua(double a[20][40], int n) {
    cout << "Ma tran nghich dao:\n";
    for (int i = 0; i < n; i++) {
        for (int j = n; j < 2 * n; j++) {
            cout << fixed << setprecision(2) << a[i][j] << " ";
        }
        cout << "\n";
    }
}
int main() {
    int n;
    cout << "Nhap cap ma tran: ";
    cin >> n;

    double a[20][40]; 
    nhapmatran(a, n);
    ghepmatrandonvi(a, n);
    if (!nghichdao(a, n)) {
        cout << "Ma tran khong kha nghich!\n";
        return 0;
    }
    inketqua(a, n);
    return 0;
}
