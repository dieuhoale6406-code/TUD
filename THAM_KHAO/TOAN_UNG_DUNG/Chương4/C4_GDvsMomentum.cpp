#include <iostream>
#include <cmath>

using namespace std;

double func(double x) {
    return ((exp(2 * x) + 8 * x * x + 4 * x) / (5 - x)) - 10 * x;
}

double grad(double x, double gra) {
    return (func(x + gra) - func(x)) / gra;
}

double GDWithMomentum(double x0, double gamma, double alpha,
                      double eps, int loop)
{
    double x = x0;   // nghiệm hiện tại
    double v = 0;    // vận tốc (momentum)
    double x_new;

    for (int i = 1; i <= loop; i++) {
        // Cập nhật vận tốc (momentum)
        v = alpha * v + gamma * grad(x,eps);

        // Cập nhật nghiệm
        x_new = x - v;
        cout << "Buoc lap " << i
             << ": x = " << x_new
             << ", y = " << func(x_new)
             << ", v = " << v << endl;

        // Điều kiện hội tụ
        if (abs(x_new - x) < eps)
            break;

        x = x_new;
    }
    return x;
}

int main() {
    double x0 = 0;        // điểm khởi tạo
    double gamma = 0.001; // hệ số học
    double alpha = 0.1;   // hệ số động lượng
    double eps = 0.00001; // sai số hội tụ
    int loop = 1000;      // số vòng lặp tối đa
    double x_min = GDWithMomentum(x0, gamma, alpha, eps, loop);
    double y_min = func(x_min);
    cout << "X_min = " << x_min << endl;
    cout << "Y_min = " << y_min << endl;

    return 0;
}
