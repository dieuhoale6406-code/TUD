#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

// ============================================================
//  Ham so: f(x) = (e^(2x) + 3x^2 + 8x) / (35 - x)
// ============================================================

const double H = 1e-7;    // buoc sai phan so
const double X0 = -1.0;   // diem bat dau
const double LR = 0.001;  // learning rate (gamma)
const double ALPHA = 0.5; // he so dong luong
const double EPS = 1e-5;  // sai so dung
const int MAXITER = 1000; // so vong lap toi da

// ---- Ham so va dao ham ----------------------------------------

double f(double x)
{
    // double denom = 35.0 - x;
    // if (abs(denom) < 1e-12) return 1e18;
    // return (exp(2.0 * x) + 3.0 * x * x + 8.0 * x) / denom;
    return log(pow(2 * x * x + 1, 2.0)) + 9 * x + 3 * exp(x * x) - 5;
}

// Dao ham bac 1 (sai phan trung tam)
double grad(double x)
{
    return (f(x + H) - f(x - H)) / (2.0 * H);
    // f'(x) = (f(x + h) - f(x - h)) / (2h)
}

// Dao ham bac 2 (Hessian)
double hess(double x)
{
    return (f(x + H) - 2.0 * f(x) + f(x - H)) / (H * H);
    // f''(x) ≈ [f(x + H) - 2f(x) + f(x - H)] / H^2
}

// ---- Ket qua tra ve -------------------------------------------

struct Result
{
    double x;       // nghiem tim duoc
    double fx;      // gia tri ham so
    int iters;      // so vong lap
    bool converged; // co hoi tu khong
};

// ---- Gradient Descent -----------------------------------------

Result gradientDescent()
{
    double x = X0;
    Result res;
    res.converged = false;
    for (int i = 0; i < MAXITER; i++)
    {
        double g = grad(x);
        if (abs(g) < EPS)
        {
            res.iters = i + 1;
            res.converged = true;
            break;
        }
        x -= LR * g;
        res.iters = i + 1;
        if (!isfinite(x))
        {
            printf("Error: x = %f\n", x);

            break;
        }
    }
    res.x = x;
    res.fx = f(x);
    return res;
}

// ---- Gradient Descent with Momentum ---------------------------

Result gdMomentum()
{
    double x = X0, v = 0.0;
    Result res;
    res.converged = false;
    for (int i = 0; i < MAXITER; i++)
    {
        double g = grad(x);
        if (abs(g) < EPS)
        {
            res.iters = i + 1;
            res.converged = true;
            break;
        }
        v = ALPHA * v + LR * g;
        x -= v;
        res.iters = i + 1;
        if (!isfinite(x))
            break;
    }
    res.x = x;
    res.fx = f(x);
    return res;
}

// ---- Newton's Method ------------------------------------------

Result newton()
{
    double x = X0;
    Result res;
    res.converged = false;
    for (int i = 0; i < MAXITER; i++)
    {
        double g = grad(x);
        if (abs(g) < EPS)
        {
            res.iters = i + 1;
            res.converged = true;
            break;
        }
        double H2 = hess(x);
        if (abs(H2) < 1e-12)
            break; // Hessian = 0 dung lai
        x -= g / H2;
        res.iters = i + 1;
        if (!isfinite(x))
            break;
    }
    res.x = x;
    res.fx = f(x);
    return res;
}

// ---- In bang ket qua ------------------------------------------

void printSeparator(int width = 72)
{
    cout << string(width, '-') << "\n";
}

void printResult(const string &name, const Result &r)
{
    cout << left << setw(26) << name
         << right << setw(14) << fixed << setprecision(8) << r.x
         << setw(14) << r.fx
         << setw(8) << r.iters
         << setw(10) << (r.converged ? "Yes" : "No (max)")
         << "\n";
}

// ---- Main -----------------------------------------------------

int main()
{
    cout << "\n";
    cout << "========================================================\n";
    cout << "  Tham so:\n";
    cout << "    x0 = " << X0 << "   (diem khoi)\n";
    cout << "    lr = " << LR << "  (learning rate / gamma)\n";
    cout << "    a  = " << ALPHA << "   (he so dong luong)\n";
    cout << "    eps= " << EPS << "  (sai so dung)\n";
    cout << "    max_iter = " << MAXITER << "\n";
    cout << "========================================================\n\n";

    Result gd = gradientDescent();
    Result gdm = gdMomentum();
    Result nt = newton();

    // Bang ket qua
    printSeparator();
    cout << left << setw(26) << "Phuong phap"
         << right << setw(14) << "x*"
         << setw(14) << "f(x*)"
         << setw(8) << "Iters"
         << setw(10) << "Hoi tu?"
         << "\n";
    printSeparator();
    printResult("Gradient Descent", gd);
    printResult("GD + Momentum", gdm);
    printResult("Newton's Method", nt);
    printSeparator();

    cout << "\nKet thuc chuong trinh.\n\n";
    return 0;
}
