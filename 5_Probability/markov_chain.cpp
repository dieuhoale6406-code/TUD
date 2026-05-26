#include <bits/stdc++.h>
#include <vector>

using namespace std;
typedef vector<vector<double>> Matrix;
typedef vector<double> Vec;

// ==== NHÂN MA TRẬN ====
Matrix multiply(const Matrix &A, const Matrix &B)
{
    int n = A.size(), m = B[0].size(), k = B.size();
    Matrix C(n, Vec(m, 0));
    for (int i = 0; i < n; i++)
        for (int l = 0; l < k; l++)
            for (int j = 0; j < m; j++)
                C[i][j] += A[i][l] * B[l][j];
    return C;
}

// ==== LŨY THỪA MA TRẬN P^n — O(n³ log n) ====
Matrix matrixPower(Matrix P, int n)
{
    int sz = P.size();
    Matrix result(sz, Vec(sz, 0));
    for (int i = 0; i < sz; i++)
        result[i][i] = 1; // identity
    while (n > 0)
    {
        if (n & 1)
            result = multiply(result, P);
        P = multiply(P, P);
        n >>= 1;
    }
    return result;
}

// ==== TÍNH XÁC SUẤT SAU n BƯỚC ====
// v0: phân phối ban đầu (v0[i] = 1 nếu bắt đầu ở state i)
// Trả về: phân phối sau n bước
Vec computeAfterNSteps(Vec v0, const Matrix &P, int n)
{
    Matrix Pn = matrixPower(P, n);
    int sz = v0.size();
    Vec result(sz, 0);
    for (int i = 0; i < sz; i++)
        for (int j = 0; j < sz; j++)
            result[j] += v0[i] * Pn[i][j];
    return result;
}

// ==== VẼ ĐỒ THỊ MARKOV (text-based) ====
void printMarkovGraph(const Matrix &P, const vector<string> &names)
{
    int n = P.size();
    cout << "\n=== DO THI MARKOV (chi ve can co P > 0) ===\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (P[i][j] > 1e-9)
                printf("  %s --[%.4f]--> %s\n",
                       names[i].c_str(), P[i][j], names[j].c_str());
    cout << "\n";
}

// ================================================================
// DẠNG 5A — Ma trận P cho trước (Đề 02/03/04)
// ================================================================
void demo_dang5A()
{
    cout << "======= DANG 5A: MA TRAN P CHO TRUOC =======\n";
    // Ma trận ví dụ từ đề (4 trạng thái — thay bằng ma trận đề cho)
    int numStates = 4;
    Matrix P = {
        {0.0, 0.3, 0.7, 0.0},
        {0.1, 0.0, 0.6, 0.3},
        {0.4, 0.0, 0.0, 0.6},
        {0.2, 0.5, 0.3, 0.0}};
    vector<string> names = {"S1", "S2", "S3", "S4"};

    // a) Vẽ đồ thị
    printMarkovGraph(P, names);

    // b) Tính xác suất
    // Ví dụ Đề 02: bắt đầu state 1 (index 0), tính P(state 4) sau 3 và 4 bước
    Vec v0(numStates, 0);
    v0[0] = 1.0; // bắt đầu ở State 1
    for (int steps : {2, 3, 4})
    {
        Vec vn = computeAfterNSteps(v0, P, steps);
        printf("Sau %d buoc (bat dau S1): ", steps);
        for (int i = 0; i < numStates; i++)
            printf("P(S%d)=%.4f  ", i + 1, vn[i]);
        cout << "\n";
    }
}

// ================================================================
// DẠNG 5B — Ước lượng P từ data (Đề 01)
// ================================================================
void demo_dang5B()
{
    cout << "\n======= DANG 5B: UOC LUONG P TU DATA =======\n";
    // Data từ Đề 01
    vector<string> data = {
        "Banh my", "Pho", "Bun", "Pizza", "Banh my", "Pho", "Bun", "Pizza",
        "Pizza", "Banh my", "Banh my", "Pho", "Pho", "Pho", "Bun", "Pho"};
    int n = data.size();

    // Xây dựng tập trạng thái (theo thứ tự xuất hiện)
    map<string, int> stateIdx;
    vector<string> states;
    for (auto &s : data)
        if (!stateIdx.count(s))
        {
            stateIdx[s] = states.size();
            states.push_back(s);
        }
    int m = states.size();

    // Đếm số lần chuyển i → j
    Matrix count(m, Vec(m, 0));
    Vec rowSum(m, 0);
    for (int t = 0; t + 1 < n; t++)
    {
        int i = stateIdx[data[t]], j = stateIdx[data[t + 1]];
        count[i][j]++;
        rowSum[i]++;
    }

    // Xây dựng ma trận P (MLE)
    Matrix P(m, Vec(m, 0));
    for (int i = 0; i < m; i++)
        if (rowSum[i] > 0)
            for (int j = 0; j < m; j++)
                P[i][j] = count[i][j] / rowSum[i];

    // In ma trận P
    cout << "\nMa tran chuyen trang thai P:\n";
    cout << setw(12) << " ";
    for (auto &s : states)
        cout << setw(10) << s;
    cout << "\n";
    for (int i = 0; i < m; i++)
    {
        cout << setw(12) << states[i];
        for (int j = 0; j < m; j++)
            printf("  %7.4f ", P[i][j]);
        cout << "\n";
    }

    // Tính P(Banh my | Pho) = P[idx_Pho][idx_Banh_my]
    string from = "Pho", to = "Banh my";
    if (stateIdx.count(from) && stateIdx.count(to))
    {
        int iFrom = stateIdx[from], iTo = stateIdx[to];
        printf("\nP(%s | %s) = %.4f\n", to.c_str(), from.c_str(), P[iFrom][iTo]);
    }
}

int main()
{
    demo_dang5A();
    demo_dang5B();
    return 0;
}