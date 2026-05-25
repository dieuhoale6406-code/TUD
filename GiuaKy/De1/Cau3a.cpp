#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

#define EPS 1e-5
using Matrix = vector<vector<double>>;

void printMatrix(const Matrix &A)
{
    for (const auto &row : A)
    {
        for (double val : row)
            cout << fixed << setprecision(6) << setw(10) << val << " ";
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

Matrix transpose(const Matrix &A)
{
    int n = A.size();
    Matrix T(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            T[j][i] = A[i][j];
    return T;
}

bool isSquare(const Matrix &A)
{
    return A.size() == A[0].size();
}

bool isSymmetric(const Matrix &A)
{
    int n = A.size();
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (fabs(A[i][j] - A[j][i]) > EPS)
                return false;
    return true;
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

bool isPositiveDefinite(const Matrix &A)
{
    int n = A.size();
    for (int k = 1; k <= n; k++)
    {
        Matrix sub(k, vector<double>(k));
        for (int i = 0; i < k; i++)
            for (int j = 0; j < k; j++)
                sub[i][j] = A[i][j];
        if (det(sub) <= EPS)
            return false;
    }
    return true;
}

void choleskyLDLT(const Matrix &A)
{
    int n = A.size();

    Matrix L(n, vector<double>(n, 0.0));
    Matrix D(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; i++)
        L[i][i] = 1.0;

    for (int j = 0; j < n; j++)
    {
        double sum = 0.0;
        for (int k = 0; k < j; k++)
            sum += L[j][k] * L[j][k] * D[k][k];
        D[j][j] = A[j][j] - sum;

        for (int i = j + 1; i < n; i++)
        {
            double s = 0.0;
            for (int k = 0; k < j; k++)
                s += L[i][k] * L[j][k] * D[k][k];
            L[i][j] = (A[i][j] - s) / D[j][j];
        }
    }

    Matrix LT = transpose(L);
    Matrix check = multiply(multiply(L, D), LT);

    cout << "Ma tran L:" << endl;
    printMatrix(L);
    cout << "Ma tran D:" << endl;
    printMatrix(D);
    cout << "Ma tran L^T:" << endl;
    printMatrix(LT);
    cout << "Ket qua L * D * L^T:" << endl;
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

    if (!isSquare(A))
    {
        cout << "Ma tran khong phai ma tran vuong!" << endl;
        return 1;
    }
    if (!isSymmetric(A))
    {
        cout << "Ma tran khong doi xung -> khong the phan ra Cholesky!" << endl;
        return 1;
    }
    choleskyLDLT(A);
    return 0;
}