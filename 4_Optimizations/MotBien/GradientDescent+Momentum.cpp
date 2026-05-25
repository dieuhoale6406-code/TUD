#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double f(double x)
{
    if (abs(5 - x) < 1e-12)
    {
        return 1e18;
    }
    double numerator = exp(2 * x) + 8 * x * x + 4 * x;
    double denominator = 5 - x;
    return numerator / denominator;
}

double df(double x)
{
    if (abs(5 - x) < 1e-12)
        return 1e18;

    double e2x = exp(2 * x);
    double u = e2x + 8 * x * x + 4 * x;
    double u_prime = 2 * e2x + 16 * x + 4;
    double v = 5 - x;
    double numerator = u_prime * v + u;
    double denominator = v * v;
    return numerator / denominator;
}

void momentum(double x0, double lr, double alpha, double epsilon, int max_iter)
{
    cout << "\n========================================\n";
    cout << "  PHUONG PHAP 2: MOMENTUM\n";
    cout << "========================================\n";
    cout << "  alpha (he so dong luong) = " << alpha << "\n\n";
    cout << fixed << setprecision(8);
    cout << left << setw(8) << "Iter"
         << setw(16) << "x"
         << setw(16) << "f(x)"
         << setw(16) << "f'(x)"
         << setw(16) << "v (velocity)" << "\n";
    cout << string(72, '-') << "\n";

    double x = x0;
    double v = 0.0;
    int iter = 0;

    cout << setw(8) << iter
         << setw(16) << x
         << setw(16) << f(x)
         << setw(16) << df(x)
         << setw(16) << v << "\n";

    for (iter = 1; iter <= max_iter; iter++)
    {
        double grad = df(x);

        if (abs(grad) < epsilon)
        {
            cout << "\n=> Hoi tu tai buoc " << iter
                 << " (|f'(x)| < epsilon)\n";
            break;
        }

        v = alpha * v + lr * grad;
        x = x - v;

        if (iter % 100 == 0 || iter == max_iter)
        {
            cout << setw(8) << iter
                 << setw(16) << x
                 << setw(16) << f(x)
                 << setw(16) << df(x)
                 << setw(16) << v << "\n";
        }
    }

    cout << "\n>>> KET QUA MOMENTUM:\n";
    cout << "    x*    = " << x << "\n";
    cout << "    f(x*) = " << f(x) << "\n";
    cout << "    f'(x*)= " << df(x) << "\n";
    cout << "    So buoc lap: " << min(iter, max_iter) << "\n";
}

int main()
{
    // Tham so bai toan
    double x0 = 0.0;       // Diem khoi
    double lr = 0.001;     // Learning rate
    double alpha = 0.1;    // He so dong luong
    double epsilon = 1e-5; // Sai so dung
    int max_iter = 1000;   // So buoc lap toi da

    cout << "  f(x) = (e^(2x) + 8x^2 + 4x) / (5 - x)\n";
    cout << "Tham so:\n";
    cout << "  - Diem khoi x0    = " << x0 << "\n";
    cout << "  - Learning rate   = " << lr << "\n";
    cout << "  - Momentum alpha  = " << alpha << "\n";
    cout << "  - Epsilon         = " << epsilon << "\n";
    cout << "  - Max iterations  = " << max_iter << "\n";
    cout << "\nGia tri ban dau:\n";
    cout << "  f(0)  = " << f(0) << "\n";
    cout << "  f'(0) = " << df(0) << "\n";

    momentum(x0, lr, alpha, epsilon, max_iter);

    return 0;
}