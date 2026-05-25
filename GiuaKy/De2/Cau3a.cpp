#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

#define EPS 1e-5
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

Matrix transpose(const Matrix &A)
{
    int m = A.size(), n = A[0].size();
    Matrix T(n, vector<double>(m));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            T[j][i] = A[i][j];
    return T;
}

bool isSquare(const Matrix &A)
{
    return (int)A.size() == (int)A[0].size();
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

void ldlt(const Matrix &A)
{
    int n = A.size();

    Matrix L(n, vector<double>(n, 0.0));
    vector<double> d(n, 0.0);
    for (int i = 0; i < n; i++)
        L[i][i] = 1.0;

    for (int j = 0; j < n; j++)
    {
        double sum_d = 0.0;
        for (int k = 0; k < j; k++)
            sum_d += L[j][k] * L[j][k] * d[k];
        d[j] = A[j][j] - sum_d;

        if (fabs(d[j]) < EPS)
        {
            cout << "  d[" << j << "] = 0, "
                 << "ma tran suy bien, khong the phan ra LDL^T" << endl;
            return;
        }

        for (int i = j + 1; i < n; i++)
        {
            double sum_l = 0.0;
            for (int k = 0; k < j; k++)
                sum_l += L[i][k] * L[j][k] * d[k];
            L[i][j] = (A[i][j] - sum_l) / d[j];
        }
    }

    Matrix D(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; i++)
        D[i][i] = d[i];

    Matrix LT = transpose(L);
    Matrix check = multiply(multiply(L, D), LT);

    cout << "Ma tran L:" << endl;
    printMatrix(L);

    cout << "Ma tran D:" << endl;
    printMatrix(D);

    cout << "Ma tran LT:" << endl;
    printMatrix(LT);

    cout << "Ket qua L * D * LT:" << endl;
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

    cout << "Ma tran A:" << endl;
    printMatrix(A);

    if (!isSquare(A))
    {
        cout << "Ma tran khong phai ma tran vuong!" << endl;
        return 1;
    }
    if (!isSymmetric(A))
    {
        cout << "Ma tran khong doi xung -> khong the phan ra LDL^T!" << endl;
        return 1;
    }

    ldlt(A);

    return 0;
}