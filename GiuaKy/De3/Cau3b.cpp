#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include "../../../eigen/Eigen/Dense"

using namespace std;

#define EPS 1e-5
using Matrix = vector<vector<double>>;

void printMatrix(const Matrix &A)
{
    for (int i = 0; i < (int)A.size(); i++)
    {
        for (int j = 0; j < (int)A[i].size(); j++)
            cout << fixed << setprecision(6) << setw(12) << A[i][j];
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
                if (fabs(A[j][i]) > EPS)
                {
                    swap(A[i], A[j]);
                    result *= -1;
                    found = true;
                    break;
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

    vector<double> ev(n);
    Matrix P_sorted(n, vector<double>(n));
    for (int j = 0; j < n; j++)
    {
        ev[j] = eigenvalues[idx[j]];
        for (int i = 0; i < n; i++)
            P_sorted[i][j] = P[i][idx[j]];
    }

    Matrix D(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; i++)
        D[i][i] = ev[i];

    Matrix Pinv = transpose(P_sorted);

    if (fabs(det(P_sorted)) < EPS)
    {
        cout << "P khong kha nghich => Ma tran khong cheo hoa duoc!" << endl;
        return;
    }

    cout << "Tri rieng:" << endl;
    for (int i = 0; i < n; i++)
        cout << "  lambda[" << i + 1 << "] = " << fixed << setprecision(6) << ev[i] << endl;
    cout << endl;

    cout << "Vecto rieng:" << endl;
    printMatrix(P_sorted);

    cout << "P:" << endl;
    printMatrix(P_sorted);

    cout << "D:" << endl;
    printMatrix(D);

    cout << "P^T:" << endl;
    printMatrix(Pinv);

    cout << "P * D * P^T^:" << endl;
    printMatrix(multiply(multiply(P_sorted, D), Pinv));
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