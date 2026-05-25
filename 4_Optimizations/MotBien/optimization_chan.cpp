/*
 * BAI TAP TOI UU HAM SO - DE CHAN
 * Ham so: f(x) = (e^(2x) + 8x^2 + 4x) / (5 - x)
 *
 * 3 Phuong phap toi uu:
 *   1. Gradient Descent
 *   2. Gradient Descent with Momentum
 *   3. Newton's Method
 *
 * Tham so:
 *   - Diem khoi: x0 = 0
 *   - Learning rate: lr = 0.001
 *   - He so dong luong (Momentum): alpha = 0.1
 *   - So buoc lap: n >= 1000
 *   - Sai so dung: epsilon = 1e-5
 */

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// ============================================================
// Ham so f(x) = (e^(2x) + 8x^2 + 4x) / (5 - x)
// ============================================================
double f(double x) {
    if (abs(5 - x) < 1e-12) {
        // Tranh chia cho 0 tai x = 5
        return 1e18;
    }
    double numerator = exp(2 * x) + 8 * x * x + 4 * x;
    double denominator = 5 - x;
    return numerator / denominator;
}

// ============================================================
// Dao ham bac nhat f'(x)
// Su dung quy tac thuong: f'(x) = (u'v - uv') / v^2
//   u  = e^(2x) + 8x^2 + 4x    => u' = 2e^(2x) + 16x + 4
//   v  = 5 - x                  => v' = -1
//
// f'(x) = [(2e^(2x) + 16x + 4)(5-x) + (e^(2x) + 8x^2 + 4x)] / (5-x)^2
// ============================================================
double df(double x) {
    if (abs(5 - x) < 1e-12) return 1e18;

    double e2x = exp(2 * x);
    double u  = e2x + 8 * x * x + 4 * x;
    double u_prime = 2 * e2x + 16 * x + 4;
    double v  = 5 - x;
    // v' = -1

    // f'(x) = (u'*v - u*v') / v^2 = (u'*v + u) / v^2
    double numerator = u_prime * v + u;
    double denominator = v * v;
    return numerator / denominator;
}

// ============================================================
// Dao ham bac hai f''(x)
// Dat g(x) = f'(x) * (5-x)^2 = (2e^(2x)+16x+4)(5-x) + e^(2x)+8x^2+4x
// Tinh g'(x):
//   g'(x) = (4e^(2x)+16)(5-x) + (2e^(2x)+16x+4)(-1) + 2e^(2x)+16x+4
//          = (4e^(2x)+16)(5-x)
//
// f''(x) = [g'(x)*(5-x)^2 - g(x)*2*(5-x)*(-1)] / (5-x)^4
//         = [g'(x)*(5-x) + 2*g(x)] / (5-x)^3
// ============================================================
double ddf(double x) {
    if (abs(5 - x) < 1e-12) return 1e18;

    double e2x = exp(2 * x);
    double v   = 5 - x;

    // g(x) = numerator cua f'(x) truoc khi chia cho v^2
    double u       = e2x + 8 * x * x + 4 * x;
    double u_prime = 2 * e2x + 16 * x + 4;
    double g       = u_prime * v + u;       // g(x)

    // g'(x) = (4e^(2x) + 16)(5-x)
    double g_prime = (4 * e2x + 16) * v;

    double numerator   = g_prime * v + 2 * g;  // g'(x)*(5-x) + 2*g(x)
    double denominator = v * v * v;             // (5-x)^3
    return numerator / denominator;
}

// ============================================================
// PHUONG PHAP 1: GRADIENT DESCENT
// Cong thuc: x_{i+1} = x_i - lr * f'(x_i)
// Dieu kien dung: |f'(x)| < epsilon hoac n >= max_iter
// ============================================================
void gradientDescent(double x0, double lr, double epsilon, int max_iter) {
    cout << "\n========================================\n";
    cout << "  PHUONG PHAP 1: GRADIENT DESCENT\n";
    cout << "========================================\n";
    cout << fixed << setprecision(8);
    cout << left << setw(8) << "Iter"
         << setw(16) << "x"
         << setw(16) << "f(x)"
         << setw(16) << "f'(x)" << "\n";
    cout << string(56, '-') << "\n";

    double x = x0;
    int iter = 0;

    // In trang thai ban dau
    cout << setw(8) << iter
         << setw(16) << x
         << setw(16) << f(x)
         << setw(16) << df(x) << "\n";

    for (iter = 1; iter <= max_iter; iter++) {
        double grad = df(x);

        // Kiem tra hoi tu
        if (abs(grad) < epsilon) {
            cout << "\n=> Hoi tu tai buoc " << iter
                 << " (|f'(x)| < epsilon)\n";
            break;
        }

        // Cap nhat x
        x = x - lr * grad;

        // In ket qua moi 100 buoc hoac buoc cuoi
        if (iter % 100 == 0 || iter == max_iter) {
            cout << setw(8) << iter
                 << setw(16) << x
                 << setw(16) << f(x)
                 << setw(16) << df(x) << "\n";
        }
    }

    cout << "\n>>> KET QUA GRADIENT DESCENT:\n";
    cout << "    x*    = " << x << "\n";
    cout << "    f(x*) = " << f(x) << "\n";
    cout << "    f'(x*)= " << df(x) << "\n";
    cout << "    So buoc lap: " << min(iter, max_iter) << "\n";
}

// ============================================================
// PHUONG PHAP 2: MOMENTUM (Gradient Descent with Momentum)
// Cong thuc:
//   v_{i+1} = alpha * v_i + lr * f'(x_i)
//   x_{i+1} = x_i - v_{i+1}
// Trong do alpha la he so dong luong (0 < alpha < 1)
// ============================================================
void momentum(double x0, double lr, double alpha, double epsilon, int max_iter) {
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
    double v = 0.0;  // Van toc ban dau = 0
    int iter = 0;

    cout << setw(8) << iter
         << setw(16) << x
         << setw(16) << f(x)
         << setw(16) << df(x)
         << setw(16) << v << "\n";

    for (iter = 1; iter <= max_iter; iter++) {
        double grad = df(x);

        // Kiem tra hoi tu
        if (abs(grad) < epsilon) {
            cout << "\n=> Hoi tu tai buoc " << iter
                 << " (|f'(x)| < epsilon)\n";
            break;
        }

        // Cap nhat van toc va vi tri
        v = alpha * v + lr * grad;
        x = x - v;

        // In moi 100 buoc hoac buoc cuoi
        if (iter % 100 == 0 || iter == max_iter) {
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

// ============================================================
// PHUONG PHAP 3: NEWTON'S METHOD
// Cong thuc: x_{i+1} = x_i - f'(x_i) / f''(x_i)
// Dieu kien dung: |f'(x)| < epsilon hoac |f''(x)| qua nho
// ============================================================
void newtonMethod(double x0, double epsilon, int max_iter) {
    cout << "\n========================================\n";
    cout << "  PHUONG PHAP 3: NEWTON'S METHOD\n";
    cout << "========================================\n";
    cout << fixed << setprecision(8);
    cout << left << setw(8) << "Iter"
         << setw(16) << "x"
         << setw(16) << "f(x)"
         << setw(16) << "f'(x)"
         << setw(16) << "f''(x)" << "\n";
    cout << string(72, '-') << "\n";

    double x = x0;
    int iter = 0;

    cout << setw(8) << iter
         << setw(16) << x
         << setw(16) << f(x)
         << setw(16) << df(x)
         << setw(16) << ddf(x) << "\n";

    for (iter = 1; iter <= max_iter; iter++) {
        double grad  = df(x);
        double grad2 = ddf(x);

        // Kiem tra hoi tu
        if (abs(grad) < epsilon) {
            cout << "\n=> Hoi tu tai buoc " << iter
                 << " (|f'(x)| < epsilon)\n";
            break;
        }

        // Tranh chia cho 0 khi f''(x) qua nho
        if (abs(grad2) < 1e-12) {
            cout << "\n=> Dung: f''(x) gan 0 tai buoc " << iter
                 << " (co the la diem uon)\n";
            break;
        }

        // Cap nhat x theo Newton
        x = x - grad / grad2;

        // In moi buoc (Newton hoi tu nhanh nen in tat ca)
        cout << setw(8) << iter
             << setw(16) << x
             << setw(16) << f(x)
             << setw(16) << df(x)
             << setw(16) << ddf(x) << "\n";

        if (iter == max_iter) {
            cout << "\n=> Dat gioi han so buoc lap " << max_iter << "\n";
        }
    }

    cout << "\n>>> KET QUA NEWTON'S METHOD:\n";
    cout << "    x*    = " << x << "\n";
    cout << "    f(x*) = " << f(x) << "\n";
    cout << "    f'(x*)= " << df(x) << "\n";
    cout << "    So buoc lap: " << iter << "\n";
}

// ============================================================
// MAIN
// ============================================================
int main() {
    // Tham so bai toan
    double x0      = 0.0;     // Diem khoi
    double lr      = 0.001;   // Learning rate
    double alpha   = 0.1;     // He so dong luong
    double epsilon = 1e-5;    // Sai so dung
    int    max_iter = 1000;   // So buoc lap toi da

    cout << "============================================\n";
    cout << "  TOI UU HAM SO - DE CHAN\n";
    cout << "  f(x) = (e^(2x) + 8x^2 + 4x) / (5 - x)\n";
    cout << "============================================\n";
    cout << "Tham so:\n";
    cout << "  - Diem khoi x0    = " << x0      << "\n";
    cout << "  - Learning rate   = " << lr      << "\n";
    cout << "  - Momentum alpha  = " << alpha   << "\n";
    cout << "  - Epsilon         = " << epsilon << "\n";
    cout << "  - Max iterations  = " << max_iter << "\n";
    cout << "\nGia tri ban dau:\n";
    cout << "  f(0)  = " << f(0)   << "\n";
    cout << "  f'(0) = " << df(0)  << "\n";
    cout << "  f''(0)= " << ddf(0) << "\n";

    // Chay 3 phuong phap
    gradientDescent(x0, lr, epsilon, max_iter);
    momentum(x0, lr, alpha, epsilon, max_iter);
    newtonMethod(x0, epsilon, max_iter);

    cout << "\n============================================\n";
    cout << "  TONG KET SO SANH 3 PHUONG PHAP\n";
    cout << "============================================\n";
    cout << "  Gradient Descent : tim cuc tieu, hoi tu cham, on dinh\n";
    cout << "  Momentum         : hoi tu nhanh hon GD nho 'da' van toc\n";
    cout << "  Newton's Method  : hoi tu rat nhanh (bac 2), can f''(x)\n";

    return 0;
}
