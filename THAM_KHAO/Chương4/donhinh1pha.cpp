#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

using Vec = vector<double>;
using Mat = vector<Vec>;

vector<int> anCoBan(const Mat& A) {
    int m = A.size(), n = A[0].size();
    vector<int> res(m, -1);
    for (int col = 0; col < n; ++col) {
        int cnt0 = 0, cnt1 = 0, idRow = -1;
        for (int row = 0; row < m; ++row) {
            if (A[row][col] == 0.0) cnt0++;
            else if (A[row][col] == 1.0) {
                cnt1++;
                idRow = row;
            }
        }
        if (cnt0 == m - 1 && cnt1 == 1 && idRow != -1)
            res[idRow] = col;
    }
    return res;
}

void initTable(const Vec& c, const Mat& A, const Vec& b,
               vector<int>& idAnCoBan, Mat& table) {
    int m = A.size(), n = A[0].size();
    idAnCoBan = anCoBan(A);
    table.assign(m + 1, Vec(n + 1, 0.0));

    for (int i = 0; i < m; ++i) {
        table[i][0] = b[i];
        for (int j = 0; j < n; ++j)
            table[i][j + 1] = A[i][j];
    }

    Vec delta(n + 1, 0.0);
    double s0 = 0.0;
    for (int i = 0; i < m; ++i) {
        int col = idAnCoBan[i];
        if (col >= 0) s0 += c[col] * b[i];
    }
    delta[0] = s0;
    for (int j = 0; j < n; ++j) {
        double s = 0.0;
        for (int i = 0; i < m; ++i) {
            int col = idAnCoBan[i];
            if (col >= 0) s += c[col] * A[i][j];
        }
        delta[j + 1] = s - c[j];
    }
    table[m] = delta;
}

void printTable(const Mat& table) {
    for (const auto& row : table) {
        for (double v : row)
            cout << setw(8) << v << " ";
        cout << "\n";
    }
}

bool solve(vector<int>& idAn, Mat& table, Vec& x0, double& fmin) {
    int m = (int)table.size() - 1;
    int n = (int)table[0].size() - 1;
    int step = 0;

    cout << "\n=== Step " << step << " ===\n";
    cout << "Nghiem co ban: ";
    for (int i = 0; i < m; ++i) cout << idAn[i] + 1 << " ";
    cout << "\n";
    printTable(table);

    bool voNghiem = false;
    while (true) {
        double mx = -1.0;
        int idCol = -1;
        for (int j = 1; j <= n; ++j) {
            if (table[m][j] > 0.0 && table[m][j] > mx) {
                mx = table[m][j];
                idCol = j;
            }
        }
        if (mx == -1.0) break;

        double mn = 1e18;
        int idRow = -1;
        for (int i = 0; i < m; ++i) {
            if (table[i][idCol] <= 0.0) continue;
            double tmp = table[i][0] / table[i][idCol];
            if (tmp < mn) {
                mn = tmp;
                idRow = i;
            }
        }
        if (idRow == -1) {
            voNghiem = true;
            break;
        }

        idAn[idRow] = idCol - 1;
        double pivot = table[idRow][idCol];

        for (int r = 0; r <= m; ++r) {
            for (int c = 0; c <= n; ++c) {
                if (r != idRow && c != idCol)
                    table[r][c] -= table[idRow][c] * table[r][idCol] / pivot;
            }
        }
        for (int r = 0; r <= m; ++r)
            if (r != idRow) table[r][idCol] = 0.0;
        for (int c = 0; c <= n; ++c)
            if (c != idCol) table[idRow][c] /= pivot;
        table[idRow][idCol] = 1.0;

        step++;
        cout << "\n=== Step " << step << " ===\n";
        cout << "Tam quay: " << idRow + 1 << "," << idCol + 1 << "\n";
        cout << "Nghiem co ban: ";
        for (int i = 0; i < m; ++i) cout << idAn[i] + 1 << " ";
        cout << "\n";
        printTable(table);
    }

    if (voNghiem) return false;
    x0.assign(n, 0.0);
    for (int i = 0; i < m; ++i)
        if (idAn[i] >= 0) x0[idAn[i]] = table[i][0];
    fmin = table[m][0];
    return true;
}

int main() {
    cout << fixed << setprecision(2);

    int m, n;
    cout << "Nhap so rang buoc m: ";
    cin >> m;
    cout << "Nhap so bien n: ";
    cin >> n;

    Vec c(n);
    cout << "Nhap vector he so c (" << n << " phan tu):\n";
    for (int i = 0; i < n; ++i) cin >> c[i];

    Mat A(m, Vec(n));
    cout << "Nhap ma tran A (" << m << "x" << n << "):\n";
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            cin >> A[i][j];

    Vec b(m);
    cout << "Nhap vector b (" << m << " phan tu):\n";
    for (int i = 0; i < m; ++i) cin >> b[i];

    vector<int> idAn;
    Mat table;
    initTable(c, A, b, idAn, table);

    Vec x0;
    double fmin;
    bool ok = solve(idAn, table, x0, fmin);

    if (!ok)
        cout << "\nBai toan khong bi chan tren (vo nghiem trong y nghia toi uu hoa).\n";
    else {
        cout << "\nNghiem x0 = ";
        for (double v : x0) cout << v << " ";
        cout << "\nMin = " << fmin << "\n";
    }

    return 0;
}
