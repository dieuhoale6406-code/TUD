#include <iostream>
#include "Eigen/Dense"
#include <iomanip>
#include <cmath>

using namespace std;
using namespace Eigen;

int count = 0;

void swap(double& a, double& b); // Hàm hoán đổi giá trị hai số thực
void display(double A[][10], int row, int col); // Hàm in ma trận ra màn hình với định dạng cột
void transpose(double A[][10], double At[][10], int rows, int cols); // Hàm tính ma trận chuyển vị
void multiplyMatrices(MatrixXd& S, double A[][10], double B[][10], int row1, int col1, int col2); // Hàm nhân hai ma trận
void getEigenValuesAndVectors(MatrixXd S, MatrixXd& lambda, MatrixXd& vector); // Hàm tìm trị riêng và vector riêng
void calculateMatrixS(MatrixXd lambda, double sigma[][10], int rows, int cols); // Hàm tạo ma trận Sigma (giá trị kỳ dị)
void calculateMatrixU(MatrixXd lambda, MatrixXd vector, double U[][10], double A[][10], int rows, int cols); // Hàm tính ma trận U
void calculateMatrixV(MatrixXd vector, double V[][10]); // Hàm tính ma trận V
void gramSchmidt(double U[][10], int rows, int cols); // Hàm trực giao hóa Gram-Schmidt để bổ sung vector cho U
void rref(MatrixXd& U_matrix); // Hàm đưa ma trận về dạng bậc thang rút gọn

int main()
{
   int rows, cols;
   double A[10][10], At[10][10];

   // Nhập kích thước ma trận từ bàn phím
   cout << "Nhap kich thuoc ma tran:" << endl;
   cout << "Hang: ";
   cin >> rows;
   cout << "Cot: ";
   cin >> cols;

   // Nhập các phần tử của ma trận A
   cout << "Nhap cac phan tu cua ma tran:" << endl;
   for (int i = 0; i < rows; i++)
   {
       for (int j = 0; j < cols; j++)
       {
           cout << "A[" << i + 1 << "][" << j + 1 << "] = ";
           cin >> A[i][j];
       }
   }

   // Khởi tạo các ma trận hỗ trợ của Eigen
   MatrixXd S(cols, cols), lambda(cols, 1), vector(cols, cols);
   // Bước 1: Tính ma trận chuyển vị A^T
   transpose(A, At, rows, cols);
   // Bước 2: Tính S = A^T * A để tìm giá trị riêng/vector riêng
   multiplyMatrices(S, At, A, cols, rows, cols);
   MatrixXd S_copy = S;
   rref(S_copy); // Thử nghiệm đưa S về dạng RREF
   //Tìm GTR (lambda) và Vector riêng (vector) của S
   getEigenValuesAndVectors(S, lambda, vector);
   double sigma[10][10], U[10][10], V[10][10];
   //Tính toán ma trận U, Sigma và V
   calculateMatrixU(lambda, vector, U, A, rows, cols);
   MatrixXd null_space(cols, 1);
   for (int i = 0; i < cols; i++)
   {
       null_space(i, 0) = S_copy(i, cols - 1);
   }
   
   // Hiển thị kết quả ma trận U
   cout << "Ma Tran U:" << endl;
   display(U, rows, rows);

   // Hiển thị kết quả ma trận Sigma
   calculateMatrixS(lambda, sigma, rows, cols);
   cout << "Ma Tran Sigma(Gia tri ki di):" << endl;
   display(sigma, rows, cols);
   // Hiển thị kết quả ma trận V^T
   calculateMatrixV(vector, V);
   cout << "Ma Tran V^T:" << endl;
   double VT[10][10];
   transpose(V, VT, cols, cols);
   display(VT, cols, cols);
   // Bước 5: Kiểm tra lại bằng cách nhân U * Sigma * V^T
   MatrixXd U_matrix(rows, rows), V_matrix(cols, cols), S_matrix(rows, cols);
   for (int i = 0; i < rows; i++)
       for (int j = 0; j < rows; j++)
           U_matrix(i, j) = U[i][j];

   for (int i = 0; i < cols; i++)
       for (int j = 0; j < cols; j++)
           V_matrix(i, j) = V[i][j];

   for (int i = 0; i < rows; i++)
       for (int j = 0; j < cols; j++)
           S_matrix(i, j) = sigma[i][j];
   MatrixXd A_matrix = U_matrix * S_matrix * V_matrix;
   cout << "Ma Tran A duoc tai tao lai(check):" << endl;
   display(A, rows, cols);
   return 0;
}

// Hàm đưa ma trận về dạng bậc thang rút gọn (Reduced Row Echelon Form)
void rref(MatrixXd& U_matrix)
{
   int rows = U_matrix.rows();
   int cols = U_matrix.cols();
   int lead = 0;

   for (int r = 0; r < rows; ++r)
   {
       if (lead >= cols)
           return;
       int i = r;
       while (U_matrix(i, lead) == 0)
       {
           ++i;
           if (i == rows)
           {
               i = r;
               ++lead;
               if (lead == cols)
                   return;
           }
       }

       U_matrix.row(i).swap(U_matrix.row(r));
       U_matrix.row(r) /= U_matrix(r, lead);
       for (int i = 0; i < rows; ++i)
       {
           if (i != r)
           {
               U_matrix.row(i) -= U_matrix.row(r) * U_matrix(i, lead);
           }
       }
       ++lead;
   }
}

// Hàm hoán đổi giá trị hai biến
void swap(double& a, double& b)
{
   double temp = a;
   a = b;
   b = temp;
}

// Hàm hiển thị ma trận với định đinh dang đẹp
void display(double A[][10], int row, int col)
{
   for (int i = 0; i < row; i++)
   {
       for (int j = 0; j < col; j++)
           cout << setw(12) << setprecision(4) << A[i][j];
       cout << endl;
   }
}

// Hàm thực hiện chuyển vị ma trận
void transpose(double A[][10], double At[][10], int rows, int cols)
{
   for (int i = 0; i < rows; i++)
       for (int j = 0; j < cols; j++)
           At[j][i] = A[i][j];
}

// Hàm nhân ma trận thủ công
void multiplyMatrices(MatrixXd& S, double A[][10], double B[][10], int row1, int col1, int col2)
{
   for (int i = 0; i < row1; i++)
   {
       for (int j = 0; j < col2; j++)
       {
           S(i, j) = 0;
           for (int k = 0; k < col1; k++)
           {
               S(i, j) += A[i][k] * B[k][j];
           }
       }
   }
}

// Hàm giải tìm trị riêng/vector riêng và sắp xếp chúng theo thứ tự giảm dần
void getEigenValuesAndVectors(MatrixXd S, MatrixXd& lambda, MatrixXd& vector)
{
   SelfAdjointEigenSolver<Eigen::MatrixXd> eigensolver(S);
   vector = eigensolver.eigenvectors();
   lambda = eigensolver.eigenvalues();
   int k = lambda.rows();
   int l = vector.rows();

   // Xử lý các trị riêng cực nhỏ
   for (int i = 0; i < k; i++)
   {
       if (lambda(i, 0) < 0.000001)
       {
           lambda(i, 0) = 0;
           ::count++;
       }
   }
   // Thuật toán sắp xếp nổi bọt để đưa trị riêng lớn nhất lên đầu
   for (int i = 0; i < k; i++)
   {
       for (int j = i + 1; j < k; j++)
       {
           if (lambda(j, 0) > lambda(i, 0))
           {
               swap(lambda(j, 0), lambda(i, 0));
               for (int h = 0; h < l; h++)
                   swap(vector(h, i), vector(h, j));
           }
       }
   }
}

// Hàm tính ma trận U
void calculateMatrixU(MatrixXd lambda, MatrixXd vector, double U[][10], double A[][10], int rows, int cols)
{
   MatrixXd ui(rows, 1);
   double Vi[10][10];

   for (int i = 0; i < cols; i++)
   {
       for (int j = 0; j < cols; j++)
       {
           Vi[j][0] = vector(j, i);
       }
       multiplyMatrices(ui, A, Vi, rows, cols, 1);

       for (int k = 0; k < rows; k++)
       {
           if (lambda(i, 0) != 0)
           {
               // U_i = (1 / giá trị kỳ dị) * A * V_i
               U[k][i] = (1 / sqrt(lambda(i, 0))) * ui(k, 0);
           }
           else
           {
               U[k][i] = 0;
           }
       }
   }
}

// Quy trình Gram-Schmidt để tạo các vector trực chuẩn bổ sung cho ma trận U
void gramSchmidt(double U[][10], int rows, int cols)
{
   for (int i = cols; i < rows; i++)
   {
       for (int j = 0; j < rows; j++)
       {
           U[j][i] = (i == j) ? 1 : 0;
       }
       for (int k = 0; k < i; k++)
       {
           double dot_product = 0;
           for (int j = 0; j < rows; j++)
           {
               dot_product += U[j][i] * U[j][k];
           }
           for (int j = 0; j < rows; j++)
           {
               U[j][i] -= dot_product * U[j][k];
           }
       }
       double norm = 0;
       for (int j = 0; j < rows; j++)
       {
           norm += U[j][i] * U[j][i];
       }
       norm = sqrt(norm);
       for (int j = 0; j < rows; j++)
       {
           U[j][i] /= norm;
       }
   }
}

// Hàm gán kết quả vector riêng vào mảng tĩnh V
void calculateMatrixV(MatrixXd vector, double V[][10])
{
   int row = vector.rows(), col = vector.cols();
   for (int i = 0; i < row; i++)
   {
       for (int j = 0; j < col; j++)
       {
           V[i][j] = vector(i, j);
       }
   }
}

// Hàm tạo ma trận Sigma chứa các giá trị kỳ dị (căn bậc hai của trị riêng)
void calculateMatrixS(MatrixXd lambda, double sigma[][10], int rows, int cols)
{
   int k = 0;
   for (int i = 0; i < rows; i++)
   {
       for (int j = 0; j < cols; j++)
       {
           if (i == j && lambda(k, 0) != 0)
           {
               sigma[i][j] = sqrt(lambda(k, 0));
               k++;
           }
           else
           {
               sigma[i][j] = 0;
           }
       }
   }
}