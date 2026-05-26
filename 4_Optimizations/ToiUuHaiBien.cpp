#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
using namespace std;

// ============================================================
//  Ham so mau 2 bien:
//      f(x, y) = x^2 + y^2 + 2x - 4y
//
//  Neu muon toi uu ham khac, chi can sua noi dung ham f(x, y).
// ============================================================

const double H = 1e-5;    // buoc sai phan so
const double X0 = 10.0;   // x ban dau
const double Y0 = 1.0;    // y ban dau
const double LR = 0.0001; // learning rate (gamma)
const double ALPHA = 0.4; // he so dong luong
const double EPS = 1e-5;  // sai so dung
const int MAXITER = 25;   // so vong lap toi da

// ---- Ham so va dao ham ----------------------------------------

#include <math.h>

double f(double y, double z)
{
    if (z >= 0)
    {
        return z - z * y + log10(1 + exp(-z));
    }
    else
    {
        return -z * y + log10(exp(z) + 1);
    }
}

// Dao ham rieng theo x (sai phan trung tam)
double gradX(double x, double y)
{
    return (f(x + H, y) - f(x - H, y)) / (2.0 * H);
}

// Dao ham rieng theo y (sai phan trung tam)
double gradY(double x, double y)
{
    return (f(x, y + H) - f(x, y - H)) / (2.0 * H);
}

// Tính độ dài vector gradient
double gradNorm(double gx, double gy)
{
    return sqrt(gx * gx + gy * gy);
}

// Cac dao ham bac 2 de lap ma tran Hessian 2x2
double hessXX(double x, double y)
{
    return (f(x + H, y) - 2.0 * f(x, y) + f(x - H, y)) / (H * H);
}

double hessYY(double x, double y)
{
    return (f(x, y + H) - 2.0 * f(x, y) + f(x, y - H)) / (H * H);
}

double hessXY(double x, double y)
{
    return (f(x + H, y + H) - f(x + H, y - H) - f(x - H, y + H) + f(x - H, y - H)) / (4.0 * H * H);
}

// ---- Ket qua tra ve -------------------------------------------

struct Result
{
    double x;       // nghiem x tim duoc
    double y;       // nghiem y tim duoc
    double fx;      // gia tri ham so tai (x, y)
    int iters;      // so vong lap
    bool converged; // co hoi tu khong
};

// ---- Gradient Descent -----------------------------------------

Result gradientDescent()
{
    double x = X0, y = Y0;
    Result res;
    res.converged = false;

    for (int i = 0; i < MAXITER; i++)
    {
        double gx = gradX(x, y);
        double gy = gradY(x, y);

        if (gradNorm(gx, gy) < EPS)
        {
            res.iters = i + 1;
            res.converged = true;
            break;
        }

        x -= LR * gx;
        y -= LR * gy;

        res.iters = i + 1;
        if (!isfinite(x) || !isfinite(y))
            break;
    }

    res.x = x;
    res.y = y;
    res.fx = f(x, y);
    return res;
}

// ---- Gradient Descent with Momentum ---------------------------

Result gdMomentum()
{
    double x = X0, y = Y0;
    double vx = 0.0, vy = 0.0;
    Result res;
    res.converged = false;

    for (int i = 0; i < MAXITER; i++)
    {
        double gx = gradX(x, y);
        double gy = gradY(x, y);

        if (gradNorm(gx, gy) < EPS)
        {
            res.iters = i + 1;
            res.converged = true;
            break;
        }

        vx = ALPHA * vx + LR * gx;
        vy = ALPHA * vy + LR * gy;
        x -= vx;
        y -= vy;

        res.iters = i + 1;
        if (!isfinite(x) || !isfinite(y))
            break;
    }

    res.x = x;
    res.y = y;
    res.fx = f(x, y);
    return res;
}

// ---- Newton's Method ------------------------------------------

Result newton()
{
    double x = X0, y = Y0;
    Result res;
    res.converged = false;

    for (int i = 0; i < MAXITER; i++)
    {
        double gx = gradX(x, y);
        double gy = gradY(x, y);

        if (gradNorm(gx, gy) < EPS)
        {
            res.iters = i + 1;
            res.converged = true;
            break;
        }
        // H = [ hxx  hxy ]    = hang x
        //     [ hxy  hyy ]    = hang y
        double hxx = hessXX(x, y);
        double hxy = hessXY(x, y);
        double hyy = hessYY(x, y);
        double det = hxx * hyy - hxy * hxy;

        if (abs(det) < 1e-12)
            break; // Hessian = 0 dung lai
        // boi vi neu dinh thuc = 0 thi khong the tinh kha nghich

        // H^(-1) = 1/det * [  hyy  -hxy ]
        //                  [ -hxy   hxx ]

        // [ dx ] = H^(-1) [ gx ]
        // [ dy ]          [ gy ]
        double dx = (hyy * gx - hxy * gy) / det;
        double dy = (-hxy * gx + hxx * gy) / det;

        x -= LR * dx;
        y -= LR * dy;

        res.iters = i + 1;
        if (!isfinite(x) || !isfinite(y))
            break;
    }

    res.x = x;
    res.y = y;
    res.fx = f(x, y);
    return res;
}

// ---- In bang ket qua ------------------------------------------

void printSeparator(int width = 155)
{
    cout << string(width, '-') << "\n";
}

void printResult(const string &name, const Result &r)
{
    cout << left << setw(26) << name
         << right << setw(37) << fixed << setprecision(8) << r.x
         << setw(37) << r.y
         << setw(37) << r.fx
         << setw(8) << r.iters
         << setw(10) << (r.converged ? "Yes" : "No (max)")
         << "\n";
}

// ---- Main -----------------------------------------------------

int main()
{
    cout << "\n";
    cout << "========================================================\n";
    cout << "  TOI UU HAM SO 2 BIEN BANG 3 PHUONG PHAP\n";
    cout << "========================================================\n";
    cout << "  Tham so:\n";
    cout << "    x0 = " << X0 << "   y0 = " << Y0 << "   (diem bat dau)\n";
    cout << "    lr = " << LR << "  (learning rate / gamma)\n";
    cout << "    a  = " << ALPHA << "   (he so dong luong)\n";
    cout << "    eps= " << EPS << "  (sai so dung)\n";
    cout << "    max_iter = " << MAXITER << "\n";
    cout << "========================================================\n\n";

    Result gd = gradientDescent();
    Result gdm = gdMomentum();
    Result nt = newton();

    printSeparator();
    cout << left << setw(26) << "Phuong phap"
         << right << setw(37) << "x*"
         << setw(37) << "y*"
         << setw(37) << "f(x*, y*)"
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
