#include <iostream>
#include <cmath>

using namespace std;

double func(double x) {          
    return x * x + 5 * sin(x);     // hàm cần tối ưu
}
// Đạo hàm xấp xỉ bằng sai phân tiến
double grad(double x, double h) {
    return (func(x + h) - func(x)) / h;
}

double gradientDescent(double x, double alpha, double eps, int loop) {
    for (int i = 1; i <= loop; i++) {

        // Cập nhật nghiệm theo hướng âm của gradient
        x = x - alpha * grad(x, eps);

        // In thông tin từng bước lặp
        cout << "Buoc lap " << i
             << ": x = " << x
             << ", y = " << func(x) << endl;

        // Điều kiện hội tụ
        if (abs(grad(x, eps)) < eps)
            break;
    }
    return x;
}

int main() {
    double x0, alpha, eps;
    int loop;

    x0 = 0;           // điểm khởi tạo
    alpha = 0.1;      // hệ số học
    eps = 0.00001;    // sai số ε
    loop = 1000;      // số vòng lặp tối đa

    double x_min = gradientDescent(x0, alpha, eps, loop);
    double y_min = func(x_min);

    // In kết quả cuối cùng (dùng cout)
    cout << "Diem khoi tao: x0 = " << x0
         << ", y0 = " << func(x0) << endl;

    cout << "Ham so dat nho nhat tai x = " << x_min
         << ", y = " << y_min << endl;

    return 0;
}
