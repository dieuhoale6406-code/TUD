#include <iostream>
#include <cmath>
using namespace std;


double func(double z, double y) {
    if(z>=y)
        return abs(z-z*y+(log(1+exp(-(z*z)))/log(10)));
    else
    return abs(-z*y+(log(exp(z*z +1))));
    }


double grad1(double x1, double x2, double h) {
    return (func(x1 + h, x2) - func(x1, x2)) / h;
}
double grad2(double x1, double x2, double h) {
    return (func(x1, x2 + h) - func(x1, x2)) / h;
}
void GDWithMomentum2D(double x1, double x2,
                      double gamma, double alpha,
                      double eps, int loop)
{
    double v1 = 0, v2 = 0;      // vận tốc (momentum) cho x1 và x2
    double x1_new, x2_new;

    for (int i = 1; i <= loop; i++) {
        // cập nhật vận tốc
        v1 = alpha * v1 + gamma * grad1(x1,x2,eps);
        v2 = alpha * v2 + gamma * grad2(x1,x2,eps);

        // cập nhật nghiệm
        x1_new = x1 - v1;
        x2_new = x2 - v2;

        cout << "Buoc " << i
             << ": x1 = " << x1_new
             << ", x2 = " << x2_new
             << ", f = " << func(x1_new, x2_new) << endl;
        // điều kiện hội tụ: cả 2 biến thay đổi rất nhỏ
        if (abs(x1_new - x1) < eps && abs(x2_new - x2) < eps)
            break;

        x1 = x1_new;
        x2 = x2_new;
    }

    cout << "\nHam so dat nho nhat tai  = " << x1 << ", x2 = " << x2;
    cout << "\nMin = " << func(x1, x2) << endl;
}

int main() {
    double x1 = 1, x2 = 5;   
    double gamma = 0.0001;      
    double alpha = 0.4;      
    double eps = 0.00001;     
    int loop = 5000;          

    GDWithMomentum2D(x1, x2, gamma, alpha, eps, loop);
    return 0;
}
