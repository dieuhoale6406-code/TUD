/*
 * Cheo hoa ma tran vuong cap n bat ky
 * Su dung thu vien Eigen (EigenSolver cho ma tran tong quat)
 *
 * Bien dich:
 *   g++ -std=c++17 -I<duong_dan_den_thu_muc_chua_eigen> main.cpp -o main
 * Vi du (trong workspace nay):
 *   g++ -std=c++17 -I ..\..\eigen main.cpp -o main
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <numeric>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>

using namespace std;
using namespace Eigen;

/* ========== IN MA TRAN EIGEN ========== */

void printEigen(const MatrixXd &M, const string &name)
{
    cout << name << ":\n";
    for (int i = 0; i < M.rows(); i++)
    {
        for (int j = 0; j < M.cols(); j++)
            cout << fixed << setprecision(4) << setw(11) << M(i, j);
        cout << "\n";
    }
    cout << "\n";
}

/* ========== MAIN ========== */

int main()
{
    int n;
    cout << "Nhap cap ma tran n: ";
    cin >> n;

    MatrixXd A(n, n);
    cout << "Nhap ma tran A (" << n << "x" << n << "):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            cout << "  A[" << i + 1 << "][" << j + 1 << "]: ";
            cin >> A(i, j);
        }

    cout << "\n";
    printEigen(A, "Ma tran A");

    // ---- Tinh tri rieng va vec-to rieng bang Eigen::EigenSolver ----
    EigenSolver<MatrixXd> es(A);

    // Lay phan thuc cua tri rieng (phuc) va kiem tra xem co thuc khong
    VectorXcd eigvals_c = es.eigenvalues();
    MatrixXcd eigvecs_c = es.eigenvectors();

    const double tol_imag = 1e-6;
    bool allReal = true;
    for (int i = 0; i < n; i++)
        if (fabs(eigvals_c[i].imag()) > tol_imag)
        {
            allReal = false;
            break;
        }

    if (!allReal)
    {
        cout << "Ma tran co tri rieng phuc => khong cheo hoa duoc tren R.\n\n";
        cout << "Tri rieng (co the phuc):\n";
        for (int i = 0; i < n; i++)
            cout << "  lambda[" << i + 1 << "] = "
                 << fixed << setprecision(4) << eigvals_c[i].real()
                 << (eigvals_c[i].imag() >= 0 ? " + " : " - ")
                 << fabs(eigvals_c[i].imag()) << "i\n";
        cout << "\n";
        return 0;
    }

    // Toan bo tri rieng la thuc
    VectorXd eigvals = eigvals_c.real();
    MatrixXd P = eigvecs_c.real(); // cac cot la vec-to rieng

    // Sap xep theo chieu giam dan cua tri rieng
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int a, int b)
         { return eigvals[a] > eigvals[b]; });

    VectorXd eigvals_sorted(n);
    MatrixXd P_sorted(n, n);
    for (int j = 0; j < n; j++)
    {
        eigvals_sorted[j] = eigvals[idx[j]];
        P_sorted.col(j) = P.col(idx[j]);
    }

    // Chuan hoa: phan tu khac 0 dau tien cua moi cot bang 1
    for (int j = 0; j < n; j++)
    {
        double scale = 0;
        for (int i = 0; i < n; i++)
            if (fabs(P_sorted(i, j)) > 1e-9)
            {
                scale = P_sorted(i, j);
                break;
            }
        if (fabs(scale) > 1e-15)
            P_sorted.col(j) /= scale;
    }

    cout << "Tri rieng (eigenvalues): ";
    for (int i = 0; i < n; i++)
        cout << fixed << setprecision(4) << eigvals_sorted[i] << "  ";
    cout << "\n\n";

    // Kiem tra P kha nghich
    double detP = P_sorted.determinant();
    if (fabs(detP) < 1e-10)
    {
        cout << "P khong kha nghich => cac vec-to rieng khong doc lap tuyen tinh.\n";
        cout << "Ma tran khong cheo hoa duoc.\n";
        return 0;
    }

    MatrixXd Pinv = P_sorted.inverse();
    MatrixXd D = Pinv * A * P_sorted;

    // Lam sach nhieu so ra ngoai duong cheo
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i != j && fabs(D(i, j)) < 1e-6)
                D(i, j) = 0.0;

    printEigen(P_sorted, "Ma tran P  (cot la vec-to rieng)");
    printEigen(Pinv, "Ma tran P nghich dao");
    printEigen(D, "Ma tran D = P^{-1} * A * P  (duong cheo la tri rieng)");

    return 0;
}