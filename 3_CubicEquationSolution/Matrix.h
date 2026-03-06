// #pragma once
// #include <iostream>
// #include <iomanip>
// #include <math.h>
// #include <vector>
// using namespace std;
// #define EPS 1e-6

// using Matrix = vector<vector<double>>;

// void input(Matrix& A, int n)
// {
//     cout << "Nhap ma tran A (" << n << "x" << n << "):\n";
//     for (int i = 0; i < n; i++)
//         for (int j = 0; j < n; j++)
//         {
//             cout << "A[" << i + 1 << "][" << j + 1 << "]: ";
//             cin >> A[i][j];
//         }
// }

// void print(const Matrix &A)
// {
//     for (auto &r : A) {
//         for (double x : r)
//             cout << setw(8) << fixed << setprecision(3) << x;
//         cout << endl;
//     }
//     cout << endl;
// }

// void ghepmatrandonvi(Matrix& A, int n)
// {
//     for (int i = 0; i < n; i++)
//     {
//         for (int j = n; j < 2 * n; j++)
//         {
//             A[i][j] = (i == j - n) ? 1.0 : 0.0;
//         }
//     }
// }

// int timpivot(Matrix& a, int n, int i)
// {
//     int pivot = i;
//     for (int j = i + 1; j < n; j++)
//     {
//         if (fabs(a[j][i]) > fabs(a[pivot][i]))
//             pivot = j;
//     }
//     return pivot;
// }

// void doihang(Matrix& a, int n, int r1, int r2)
// {
//     swap(a[r1], a[r2]);
// }

// void chuanhoahang(Matrix& a, int n, int i)
// {
//     double div = a[i][i];
//     for (int j = 0; j < 2 * n; j++)
//         a[i][j] /= div;
// }

// void khuhang(Matrix& a, int n, int i)
// {
//     for (int k = 0; k < n; k++)
//     {
//         if (k != i)
//         {
//             double factor = a[k][i];
//             for (int j = 0; j < 2 * n; j++)
//                 a[k][j] -= factor * a[i][j];
//         }
//     }
// }

// bool nghichdao(Matrix& a, int n)
// {
//     for (int i = 0; i < n; i++)
//     {
//         int pivot = timpivot(a, n, i);
//         if (fabs(a[pivot][i]) < EPS)
//             return false;
//         if (pivot != i)
//             doihang(a, n, i, pivot);

//         chuanhoahang(a, n, i);
//         khuhang(a, n, i);
//     }
//     return true;
// }

// void inMaTran(vector<vector<double>> &a, int n)
// {
//     cout << "Ma tran nghich dao:\n";
//     for (int i = 0; i < n; i++)
//     {
//         for (int j = n; j < 2 * n; j++)
//         {
//             cout << fixed << setprecision(2) << a[i][j] << " ";
//         }
//         cout << "\n";
//     }
// }

// // int main()
// // {
// //     int n;
// //     cout << "Nhap cap ma tran: ";
// //     cin >> n;
// //
// //     Matrix a(n, vector<double>(2 * n));
// //     input(a, n);
// //     ghepmatrandonvi(a, n);
// //     if (!nghichdao(a, n))
// //     {
// //         cout << "Ma tran khong kha nghich!\n";
// //         return 0;
// //     }
// //     inketqua(a, n);
// //     return 0;
// // }

// // /* ================= NHẬP / XUẤT ================= */

// // void input(Matrix &A, int n)
// // {
// //     cout << "Nhap ma tran A (" << n << "x" << n << "):\n";
// //     for (int i = 0; i < n; i++)
// //         for (int j = 0; j < n; j++)
// //         {
// //             cout << "A[" << i + 1 << "][" << j + 1 << "] = ";
// //             cin >> A[i][j];
// //         }
// // }

// // void print(const Matrix &A)
// // {
// //     for (auto &r : A)
// //     {
// //         for (double x : r)
// //             cout << setw(10) << fixed << setprecision(4) << x;
// //         cout << "\n";
// //     }
// // }

// // /* ================= NHÂN MA TRẬN ================= */

// // Matrix multiply(const Matrix &A, const Matrix &B)
// // {
// //     int n = A.size();
// //     Matrix C(n, vector<double>(n, 0));
// //     for (int i = 0; i < n; i++)
// //         for (int j = 0; j < n; j++)
// //             for (int k = 0; k < n; k++)
// //                 C[i][j] += A[i][k] * B[k][j];
// //     return C;
// // }

// // /* ================= GAUSS–JORDAN (Y CHANG CODE BẠN) ================= */

// // bool gaussJordan(Matrix &a, int n)
// // {
// //     for (int i = 0; i < n; i++)
// //     {
// //         int pivot = i;
// //         for (int j = i + 1; j < n; j++)
// //             if (fabs(a[j][i]) > fabs(a[pivot][i]))
// //                 pivot = j;

// //         if (fabs(a[pivot][i]) < EPS)
// //             return false;

// //         if (pivot != i)
// //             swap(a[pivot], a[i]);

// //         double div = a[i][i];
// //         for (int j = 0; j < 2 * n; j++)
// //             a[i][j] /= div;

// //         for (int k = 0; k < n; k++)
// //             if (k != i)
// //             {
// //                 double factor = a[k][i];
// //                 for (int j = 0; j < 2 * n; j++)
// //                     a[k][j] -= factor * a[i][j];
// //             }
// //     }
// //     return true;
// // }

// // /* ================= TÍNH NGHỊCH ĐẢO KIỂU BẠN ================= */

// // Matrix inverseFromYourCode(const Matrix &A)
// // {
// //     int n = A.size();
// //     Matrix ext(n, vector<double>(2 * n, 0));

// //     for (int i = 0; i < n; i++)
// //         for (int j = 0; j < n; j++)
// //         {
// //             ext[i][j] = A[i][j];
// //             ext[i][j + n] = (i == j);
// //         }

// //     if (!gaussJordan(ext, n))
// //         throw runtime_error("Ma tran khong kha nghich");

// //     Matrix inv(n, vector<double>(n));
// //     for (int i = 0; i < n; i++)
// //         for (int j = 0; j < n; j++)
// //             inv[i][j] = ext[i][j + n];

// //     return inv;
// // }

// // /* ================= DANILEVSKY CHUẨN ================= */

// // bool danilevsky(Matrix A, Matrix &P)
// // {
// //     int n = A.size();

// //     // P = I
// //     P.assign(n, vector<double>(n, 0));
// //     for (int i = 0; i < n; i++)
// //         P[i][i] = 1;

// //     for (int k = n - 1; k >= 1; k--)
// //     {
// //         if (fabs(A[k][k - 1]) < EPS)
// //             return false;

// //         Matrix M(n, vector<double>(n, 0));
// //         Matrix Minv(n, vector<double>(n, 0));

// //         for (int i = 0; i < n; i++)
// //             M[i][i] = Minv[i][i] = 1;

// //         for (int j = 0; j < n; j++)
// //         {
// //             if (j == k - 1)
// //                 M[k - 1][j] = 1.0 / A[k][k - 1];
// //             else
// //                 M[k - 1][j] = -A[k][j] / A[k][k - 1];

// //             Minv[k - 1][j] = A[k][j];
// //         }

// //         A = multiply(multiply(Minv, A), M);
// //         P = multiply(P, M);
// //     }

// //     return true;
// // }
