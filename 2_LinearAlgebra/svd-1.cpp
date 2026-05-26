#include <bits/stdc++.h>
using namespace std;
typedef vector<vector<double>> Mat;
typedef vector<double> Vec;
const double EPS = 1e-10;

// ---- Ma trận cơ bản ----
Mat zeros(int r, int c) { return Mat(r, Vec(c, 0)); }
Mat identity(int n)
{
    Mat I = zeros(n, n);
    for (int i = 0; i < n; i++)
        I[i][i] = 1;
    return I;
}
Mat transpose(const Mat &A)
{
    int r = A.size(), c = A[0].size();
    Mat T = zeros(c, r);
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            T[j][i] = A[i][j];
    return T;
}
Mat multiply(const Mat &A, const Mat &B)
{
    int r = A.size(), m = A[0].size(), c = B[0].size();
    Mat C = zeros(r, c);
    for (int i = 0; i < r; i++)
        for (int k = 0; k < m; k++)
            for (int j = 0; j < c; j++)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}
void printMat(const Mat &A, const string &name)
{
    cout << name << ":\n";
    for (auto &row : A)
    {
        for (double v : row)
            printf("%9.4f ", v);
        cout << "\n";
    }
}

// ---- Jacobi Eigenvalue Algorithm (cho ma trận đối xứng S = A^T*A) ----
// Trả về eigenvalues (đường chéo D) và eigenvectors (cột của V)
pair<Vec, Mat> jacobiEigen(Mat S, int maxIter = 1000)
{
    int n = S.size();
    Mat V = identity(n);
    for (int iter = 0; iter < maxIter; iter++)
    {
        // Tìm phần tử ngoài đường chéo lớn nhất
        int p = 0, q = 1;
        double maxVal = fabs(S[0][1]);
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (fabs(S[i][j]) > maxVal)
                {
                    maxVal = fabs(S[i][j]);
                    p = i;
                    q = j;
                }
        if (maxVal < EPS)
            break;
        // Tính góc xoay
        double theta = 0.5 * atan2(2 * S[p][q], S[q][q] - S[p][p]);
        double c = cos(theta), s = sin(theta);
        // Xoay hàng
        for (int i = 0; i < n; i++)
        {
            double sp = c * S[p][i] - s * S[q][i];
            double sq = s * S[p][i] + c * S[q][i];
            S[p][i] = sp;
            S[q][i] = sq;
        }
        // Xoay cột
        for (int i = 0; i < n; i++)
        {
            double sp = c * S[i][p] - s * S[i][q];
            double sq = s * S[i][p] + c * S[i][q];
            S[i][p] = sp;
            S[i][q] = sq;
        }
        S[p][q] = S[q][p] = 0;
        // Cập nhật eigenvectors
        for (int i = 0; i < n; i++)
        {
            double vp = c * V[i][p] - s * V[i][q];
            double vq = s * V[i][p] + c * V[i][q];
            V[i][p] = vp;
            V[i][q] = vq;
        }
    }
    Vec evals(n);
    for (int i = 0; i < n; i++)
        evals[i] = S[i][i];
    return {evals, V};
}

// ---- Gram-Schmidt bổ sung cột cho U (khi rows > cols) ----
void gramSchmidtExtend(Mat &U, int existCols)
{
    int rows = U.size(), totalCols = U[0].size();
    for (int col = existCols; col < totalCols; col++)
    {
        // Khởi tạo cột chuẩn tắc (0,...,1,...,0)
        for (int i = 0; i < rows; i++)
            U[i][col] = (i == col) ? 1.0 : 0.0;
        // Trừ đi các hình chiếu lên các cột trước
        for (int k = 0; k < col; k++)
        {
            double dot = 0;
            for (int i = 0; i < rows; i++)
                dot += U[i][col] * U[i][k];
            for (int i = 0; i < rows; i++)
                U[i][col] -= dot * U[i][k];
        }
        // Chuẩn hóa
        double norm = 0;
        for (int i = 0; i < rows; i++)
            norm += U[i][col] * U[i][col];
        norm = sqrt(norm);
        if (norm > EPS)
            for (int i = 0; i < rows; i++)
                U[i][col] /= norm;
    }
}

// ---- SVD CHÍNH: A = U * Sigma * V^T ----
struct SVDResult
{
    Mat U, Sigma, Vt;
};

SVDResult computeSVD(const Mat &A)
{
    int rows = A.size(), cols = A[0].size();
    // Bước 1: S = A^T * A  (cols x cols)
    Mat At = transpose(A);
    Mat S = multiply(At, A);
    // Bước 2: Eigendecomposition của S → eigenvalues λ, eigenvectors V
    auto [evals, V] = jacobiEigen(S);
    // Sắp xếp eigenvalues giảm dần (kéo theo cột V)
    vector<int> idx(cols);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int a, int b)
         { return evals[a] > evals[b]; });
    Vec sortedEvals(cols);
    Mat sortedV = zeros(cols, cols);
    for (int j = 0; j < cols; j++)
    {
        sortedEvals[j] = evals[idx[j]];
        for (int i = 0; i < cols; i++)
            sortedV[i][j] = V[i][idx[j]];
    }
    // Bước 3: σ_i = sqrt(λ_i) → Sigma (rows x cols)
    int rank = 0;
    for (double ev : sortedEvals)
        if (ev > EPS)
            rank++;
    Mat Sigma = zeros(rows, cols);
    Vec sigma(rank);
    for (int i = 0; i < rank; i++)
    {
        sigma[i] = sqrt(sortedEvals[i]);
        Sigma[i][i] = sigma[i];
    }
    // Bước 4: u_i = (1/σ_i) * A * v_i → U (rows x rows)
    Mat U(rows, Vec(rows, 0));
    for (int k = 0; k < rank; k++)
    {
        Vec v(cols);
        for (int i = 0; i < cols; i++)
            v[i] = sortedV[i][k];
        // u_k = A * v_k / sigma_k
        for (int i = 0; i < rows; i++)
        {
            double val = 0;
            for (int j = 0; j < cols; j++)
                val += A[i][j] * v[j];
            U[i][k] = val / sigma[k];
        }
    }
    // Bước 5: Gram-Schmidt bổ sung nếu rows > rank
    if (rank < rows)
        gramSchmidtExtend(U, rank);
    return {U, Sigma, transpose(sortedV)};
}

// ---- Xác minh: tái tạo A = U * Sigma * V^T ----
void verifySVD(const Mat &A, const SVDResult &svd)
{
    Mat reconstructed = multiply(multiply(svd.U, svd.Sigma), svd.Vt);
    double err = 0;
    for (int i = 0; i < (int)A.size(); i++)
        for (int j = 0; j < (int)A[0].size(); j++)
            err += fabs(A[i][j] - reconstructed[i][j]);
    printf("Sai so tai tao ||A - U*Sigma*VT||_1 = %.2e %s\n",
           err, err < 1e-6 ? "(OK)" : "(FAIL)");
}

int main()
{
    cout << "Nhap kich thuoc ma tran (rows cols): ";
    int rows, cols;
    cin >> rows >> cols;
    Mat A(rows, Vec(cols));
    cout << "Nhap ma tran A:\n";
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            cin >> A[i][j];
    printMat(A, "A");
    auto svd = computeSVD(A);
    printMat(svd.U, "\nU (left singular vectors)");
    printMat(svd.Sigma, "Sigma (singular values)");
    printMat(svd.Vt, "V^T (right singular vectors)");
    verifySVD(A, svd);
    return 0;
}