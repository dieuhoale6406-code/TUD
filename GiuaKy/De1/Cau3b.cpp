#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include "../../../eigen/Eigen/Dense"

using namespace std;

#define EPS 1e-9
using Matrix = vector<vector<double>>;

void printMatrix(const Matrix &A)
{
    for (int i = 0; i < (int)A.size(); i++)
    {
        for (int j = 0; j < (int)A[i].size(); j++)
            cout << fixed << setprecision(6) << setw(10) << A[i][j];
        cout << endl;
    }
    cout << endl;
}

Matrix multiply(const Matrix &A, const Matrix &B)
{
    int m = A.size(), n = B[0].size(), p = B.size();
    Matrix C(m, vector<double>(n, 0.0));
    for (int i = 0; i < m; i++)
        for (int k = 0; k < p; k++)
            for (int j = 0; j < n; j++)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}

double det(Matrix A)
{
    int n = A.size();
    double result = 1.0;
    for (int i = 0; i < n; i++)
    {
        if (fabs(A[i][i]) < EPS)
        {
            bool found = false;
            for (int j = i + 1; j < n; j++)
            {
                if (fabs(A[j][i]) > EPS)
                {
                    swap(A[i], A[j]);
                    result *= -1;
                    found = true;
                    break;
                }
            }
            if (!found)
                return 0.0;
        }
        result *= A[i][i];
        for (int j = i + 1; j < n; j++)
        {
            double ratio = A[j][i] / A[i][i];
            for (int k = i; k < n; k++)
                A[j][k] -= ratio * A[i][k];
        }
    }
    return result;
}

Matrix inverse(const Matrix &A)
{
    int n = A.size();
    Matrix aug(n, vector<double>(2 * n, 0.0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            aug[i][j] = A[i][j];
        aug[i][i + n] = 1.0;
    }
    for (int col = 0; col < n; col++)
    {
        int pivot = col;
        for (int row = col + 1; row < n; row++)
            if (fabs(aug[row][col]) > fabs(aug[pivot][col]))
                pivot = row;
        swap(aug[col], aug[pivot]);
        double div = aug[col][col];
        for (int j = 0; j < 2 * n; j++)
            aug[col][j] /= div;
        for (int row = 0; row < n; row++)
        {
            if (row == col)
                continue;
            double factor = aug[row][col];
            for (int j = 0; j < 2 * n; j++)
                aug[row][j] -= factor * aug[col][j];
        }
    }
    Matrix inv(n, vector<double>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            inv[i][j] = aug[i][j + n];
    return inv;
}
void computeEigen(const Matrix &A, vector<double> &eigenvalues, Matrix &eigenvectors)
{
    int n = A.size();

    Eigen::MatrixXd Aeig(n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            Aeig(i, j) = A[i][j];

    Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> solver(Aeig);

    eigenvalues.resize(n);
    eigenvectors.assign(n, vector<double>(n));
    for (int i = 0; i < n; i++)
    {
        eigenvalues[i] = solver.eigenvalues()(i);
        for (int j = 0; j < n; j++)
            eigenvectors[j][i] = solver.eigenvectors()(j, i);
    }
}
// Phân rã Eigen Decomposition
void eigenDecomposition(const Matrix &A)
{
    int n = A.size();
    vector<double> eigenvalues;
    Matrix P;
    computeEigen(A, eigenvalues, P);

    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int a, int b)
         { return eigenvalues[a] > eigenvalues[b]; });

    vector<double> ev_sorted(n);
    Matrix P_sorted(n, vector<double>(n));
    for (int j = 0; j < n; j++)
    {
        ev_sorted[j] = eigenvalues[idx[j]];
        for (int i = 0; i < n; i++)
            P_sorted[i][j] = P[i][idx[j]];
    }

    Matrix D(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; i++)
        D[i][i] = ev_sorted[i];

    Matrix Pinv = inverse(P_sorted);

    if (fabs(det(P_sorted)) < EPS)
    {
        cout << "P khong kha nghich => Ma tran khong cheo hoa duoc!" << endl;
        return;
    }

    Matrix check = multiply(multiply(P_sorted, D), Pinv);

    cout << "Tri rieng (Diagonal matrix D):" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            double val = (i == j) ? ev_sorted[i] : 0.0;
            cout << fixed << setprecision(6) << setw(14) << val;
        }
        cout << endl;
    }
    cout << endl;

    cout << "Vecto rieng (cot thu i la v[i]):" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << fixed << setprecision(6) << setw(14) << P_sorted[i][j];
        cout << endl;
    }
    cout << endl;

    cout << "P:" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << setw(12) << fixed << setprecision(6) << P_sorted[i][j];
        cout << endl;
    }

    cout << "D:" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << setw(12) << fixed << setprecision(6) << D[i][j];
        cout << endl;
    }

    cout << "PInv:" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << setw(12) << fixed << setprecision(6) << Pinv[i][j];
        cout << endl;
    }

    cout << "P * D * PInv:" << endl;
    printMatrix(check);
}

int main()
{
    int n;
    cout << "Nhap kich thuoc ma tran: ";
    cin >> n;

    Matrix A(n, vector<double>(n));
    cout << "Nhap ma tran A:" << endl;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> A[i][j];

    cout << "\nMa tran A:" << endl;
    printMatrix(A);

    eigenDecomposition(A);

    return 0;
}