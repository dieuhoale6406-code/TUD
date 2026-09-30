//định thức
#include <iostream>
#include <vector>
#include <iomanip>
#include <math.h>
using namespace std;
double dinhthuc(vector<vector<double>> a) {
    int n = a.size();
    double det = 1; 
    for (int i = 0; i < n; i++) {
        int p = i;
        for (int j = i + 1; j < n; j++)
            if (fabs(a[j][i]) > fabs(a[p][i])) p = j;
        if (fabs(a[p][i]) < 1e-12) return 0; 
        if (p != i) { 
            swap(a[p], a[i]); 
            det =-det; 
        }
        det *= a[i][i];
        for (int j = i + 1; j < n; j++) {
            double h = a[j][i] / a[i][i];
            for (int k = i; k < n; k++)
                a[j][k] -= h * a[i][k];
        }
    }
    return det;
}
int main() {
    int n;
    cout << "Nhap cap ma tran: ";
    cin >> n;
    vector<vector<double>> a(n, vector<double>(n));
    cout << "Nhap ma tran:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++){
            cout<<"A["<<i+1<<"]["<<j+1<<"]: ";
            cin >> a[i][j];}
    cout << fixed << setprecision(2);
    cout << "Det = " << dinhthuc(a) << "\n";
    return 0;
}
