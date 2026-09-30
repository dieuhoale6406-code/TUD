#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

using Vec = vector<double>;
using Mat = vector<Vec>;

const double EPS = 1e-9;

// In bảng
void printTable(const Mat& table) {
    for (const auto& row : table) {
        for (double v : row)
            cout << setw(10) << v << " ";
        cout << "\n";
    }
}

// Tạo bảng ban đầu [b | A], hàng cuối để trống (sẽ tính sau)
void buildInitialTable(const Mat& A, const Vec& b, Mat& table) {
    int m = A.size();
    int n = A[0].size();
    table.assign(m + 1, Vec(n + 1, 0.0));

    for (int i = 0; i < m; ++i) {
        table[i][0] = b[i];          // cột b
        for (int j = 0; j < n; ++j)  // các cột biến
            table[i][j + 1] = A[i][j];
    }
    // hàng cuối (delta) sẽ được tính sau
}

// Tính lại hàng ∆ (delta) theo: ∆_j = c_B^T * a_j - c_j
// basis[k] = chỉ số biến cơ bản ở hàng k (0..N-1)
void recomputeDelta(const Vec& c, const vector<int>& basis, Mat& table) {
    int m = (int)table.size() - 1;
    int nTotal = (int)table[0].size() - 1;

    Vec cB(m, 0.0);
    for (int i = 0; i < m; ++i) {
        int idx = basis[i];
        if (idx >= 0 && idx < (int)c.size())
            cB[i] = c[idx];
        else
            cB[i] = 0.0; // biến giả hoặc biến không có trong hàm mục tiêu
    }

    // delta[0] = c_B^T * b
    double d0 = 0.0;
    for (int i = 0; i < m; ++i)
        d0 += cB[i] * table[i][0];
    table[m][0] = d0;

    // delta[j] = c_B^T * col_j - c_j
    for (int j = 1; j <= nTotal; ++j) {
        double colVal = 0.0;
        for (int i = 0; i < m; ++i)
            colVal += cB[i] * table[i][j];

        double cj = 0.0;
        int varIndex = j - 1; // cột 1 tương ứng biến 0
        if (varIndex >= 0 && varIndex < (int)c.size())
            cj = c[varIndex];

        table[m][j] = colVal - cj;
    }
}

// Giải một pha đơn hình với:
// - basis: tập biến cơ bản (chỉ số biến 0..N-1)
// - table: bảng đơn hình (m+1 x (N+1))
// - nUse: chỉ cho phép các cột từ 1..nUse được vào cơ sở (các biến được phép chọn)
// Trả về: x0 (chỉ cho nUse biến đầu), fmin (giá trị hàm mục tiêu)
bool simplexPhase(vector<int>& basis, Mat& table, int nUse, Vec& x0, double& fmin,
                  const string& phaseName = "") {
    int m = (int)table.size() - 1;
    int nTotal = (int)table[0].size() - 1;

    int step = 0;
    cout << "\n===== " << phaseName << " - Step " << step << " =====\n";
    cout << "Bien co ban (chi so + 1): ";
    for (int i = 0; i < m; ++i) cout << basis[i] + 1 << " ";
    cout << "\n";
    printTable(table);

    bool unbounded = false;

    while (true) {
        // 1. Chọn cột vào cơ sở (chỉ trong 1..nUse)
        double mx = -1e18;
        int idCol = -1;
        for (int j = 1; j <= nUse; ++j) {
            if (table[m][j] > EPS && table[m][j] > mx) {
                mx = table[m][j];
                idCol = j;
            }
        }
        // Nếu không còn hệ số dương -> tối ưu
        if (idCol == -1) break;

        // 2. Chọn hàng rời cơ sở (tỉ số nhỏ nhất b_i / a_ij)
        double mn = 1e18;
        int idRow = -1;
        for (int i = 0; i < m; ++i) {
            double aij = table[i][idCol];
            if (aij > EPS) {
                double tmp = table[i][0] / aij;
                if (tmp < mn - EPS) {
                    mn = tmp;
                    idRow = i;
                }
            }
        }
        if (idRow == -1) {
            unbounded = true;
            break;
        }

        // 3. Pivot
        basis[idRow] = idCol - 1;  // biến mới vào cơ sở
        double pivot = table[idRow][idCol];

        // Gauss-Jordan quanh phần tử trụ
        for (int r = 0; r <= m; ++r) {
            for (int c = 0; c <= nTotal; ++c) {
                if (r != idRow && c != idCol) {
                    table[r][c] -= table[idRow][c] * table[r][idCol] / pivot;
                }
            }
        }
        // Làm 0 cột trụ
        for (int r = 0; r <= m; ++r) {
            if (r != idRow)
                table[r][idCol] = 0.0;
        }
        // Chuẩn hóa hàng trụ
        for (int c = 0; c <= nTotal; ++c) {
            if (c != idCol)
                table[idRow][c] /= pivot;
        }
        table[idRow][idCol] = 1.0;

        // In lại bảng
        step++;
        cout << "\n===== " << phaseName << " - Step " << step << " =====\n";
        cout << "Tam quay (row, col) = (" << idRow + 1 << ", " << idCol + 1 << ")\n";
        cout << "Bien co ban (chi so + 1): ";
        for (int i = 0; i < m; ++i) cout << basis[i] + 1 << " ";
        cout << "\n";
        printTable(table);
    }

    if (unbounded) {
        cout << "\nBai toan khong bi chan tren (unbounded) trong " << phaseName << ".\n";
        return false;
    }

    // Lấy nghiệm x0 (chỉ cho nUse biến đầu)
    x0.assign(nUse, 0.0);
    for (int i = 0; i < m; ++i) {
        int idx = basis[i];
        if (idx >= 0 && idx < nUse)
            x0[idx] = table[i][0];
    }
    fmin = table[m][0];
    return true;
}

int main() {
    cout << fixed << setprecision(4);

    int m, n;
    cout << "Nhap so rang buoc m: ";
    cin >> m;
    cout << "Nhap so bien goc n: ";
    cin >> n;

    Vec c(n);
    cout << "Nhap vector he so c (" << n << " phan tu) cho bai toan Min Z = c^T x:\n";
    for (int i = 0; i < n; ++i) cin >> c[i];

    Mat A(m, Vec(n));
    cout << "Nhap ma tran A (" << m << "x" << n << "):\n";
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            cin >> A[i][j];

    Vec b(m);
    cout << "Nhap vector b (" << m << " phan tu):\n";
    for (int i = 0; i < m; ++i) cin >> b[i];

    // Nếu có b[i] < 0, đổi dấu cả hàng cho gọn (áp dụng cho rang buoc "=")
    for (int i = 0; i < m; ++i) {
        if (b[i] < -EPS) {
            b[i] *= -1;
            for (int j = 0; j < n; ++j)
                A[i][j] *= -1;
        }
    }

    // =========================
    //       PHASE 1
    // =========================
    int artCount = m;              // mỗi ràng buộc một biến giả
    int nTotal1 = n + artCount;    // tổng số biến (gốc + giả)

    // Tạo A1: A mở rộng thêm cột biến giả (ma trận đơn vị)
    Mat A1(m, Vec(nTotal1, 0.0));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j)
            A1[i][j] = A[i][j];
        // biến giả thứ i: cột n + i
        A1[i][n + i] = 1.0;
    }

    // Vector hệ số pha 1: w = sum artificial vars
    Vec c1(nTotal1, 0.0);
    for (int j = n; j < nTotal1; ++j)
        c1[j] = 1.0;

    // Basis ban đầu: tất cả là biến giả
    vector<int> basis(m);
    for (int i = 0; i < m; ++i)
        basis[i] = n + i;   // artificial vars

    Mat table1;
    buildInitialTable(A1, b, table1);
    recomputeDelta(c1, basis, table1);

    Vec xPhase1;
    double wmin;
    bool ok1 = simplexPhase(basis, table1, nTotal1, xPhase1, wmin, "Phase 1");

    if (!ok1 || wmin > EPS) {
        cout << "\nKet luan: Bai toan VO NGHIEM (khong ton tai nghiem khong am thoa man Ax = b).\n";
        return 0;
    }

    cout << "\nPhase 1 ket thuc: w_min = " << wmin << " (gan 0) -> Co nghiem kha thi.\n";

    // =========================
    //       PHASE 2
    // =========================
    // Dung lai table1, basis sau phase 1
    // Tinh lai hang delta theo ham muc tieu goc c (chi n bien dau)
    recomputeDelta(c, basis, table1);

    Vec xFinal;
    double fmin;
    // Chi cho phep cac bien goc (0..n-1) duoc vao co so -> nUse = n
    bool ok2 = simplexPhase(basis, table1, n, xFinal, fmin, "Phase 2");

    if (!ok2) {
        cout << "\nBai toan khong bi chan tren trong phase 2.\n";
        return 0;
    }

    cout << "\n===== KET QUA CUOI CUNG (Phase 2) =====\n";
    cout << "Nghiem toi uu x* = ";
    for (int i = 0; i < n; ++i)
        cout << "x" << i + 1 << " = " << xFinal[i] << "  ";
    cout << "\nGia tri nho nhat Min Z = " << fmin << "\n";

    return 0;
}
