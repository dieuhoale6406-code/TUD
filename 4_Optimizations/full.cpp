// =====================================================================
// Câu 4 - Tối ưu hóa: 3 phương pháp
//   (1) Gradient Descent   - hàm 2 biến
//   (2) Newton's Method    - hàm 2 biến
//   (3) Golden Section Search - hàm 1 biến (unimodal)
//   + Lagrange Multiplier  - ví dụ tối ưu có ràng buộc
// =====================================================================
#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-8;

// =====================================================================
// HÀM MỤC TIÊU & CÁC DẪN XUẤT
// f(x,y) = x^2 + 2y^2 - 2xy - 4x  (hàm 2 biến, cực tiểu tại (4,2))
// =====================================================================
double f(double x, double y)
{
    return x * x + 2 * y * y - 2 * x * y - 4 * x;
}

// Gradient: ∂f/∂x, ∂f/∂y
pair<double, double> grad(double x, double y)
{
    double gx = 2 * x - 2 * y - 4; // ∂f/∂x
    double gy = 4 * y - 2 * x;     // ∂f/∂y
    return {gx, gy};
}

// Hessian 2x2: [[∂²f/∂x², ∂²f/∂x∂y], [∂²f/∂y∂x, ∂²f/∂y²]]
// H = [[2, -2], [-2, 4]]
void hessian(double &h11, double &h12, double &h21, double &h22)
{
    h11 = 2;
    h12 = -2;
    h21 = -2;
    h22 = 4;
}

// =====================================================================
// PHƯƠNG PHÁP 1: GRADIENT DESCENT (Chap 4, tr. 6-12)
// x_{i+1} = x_i - γ * ∇f(x_i)^T
// =====================================================================
void gradientDescent(double x0, double y0, double gamma = 0.1, int maxIter = 200)
{
    cout << "--- Phuong phap 1: GRADIENT DESCENT (γ=" << gamma << ") ---\n";
    double x = x0, y = y0;
    for (int i = 0; i <= maxIter; i++)
    {
        auto [gx, gy] = grad(x, y);
        double norm = sqrt(gx * gx + gy * gy);
        if (i % 20 == 0 || norm < EPS)
            printf("  Iter %3d: x=%.6f, y=%.6f, f=%.6f, |grad|=%.2e\n",
                   i, x, y, f(x, y), norm);
        if (norm < EPS)
            break;
        x -= gamma * gx;
        y -= gamma * gy;
    }
    printf("  => Ket qua: x*=%.6f, y*=%.6f, f*=%.6f\n\n", x, y, f(x, y));
}

// =====================================================================
// PHƯƠNG PHÁP 2: NEWTON'S METHOD (Chap 4, tr. 130-132)
// Δx = -H^{-1} ∇f
// H = [[h11,h12],[h21,h22]], H^{-1} = 1/det * [[h22,-h12],[-h21,h11]]
// =====================================================================
void newtonMethod(double x0, double y0, int maxIter = 50)
{
    cout << "--- Phuong phap 2: NEWTON'S METHOD ---\n";
    double x = x0, y = y0;
    for (int i = 0; i <= maxIter; i++)
    {
        auto [gx, gy] = grad(x, y);
        double norm = sqrt(gx * gx + gy * gy);
        if (i % 5 == 0 || norm < EPS)
            printf("  Iter %2d: x=%.8f, y=%.8f, f=%.8f, |grad|=%.2e\n",
                   i, x, y, f(x, y), norm);
        if (norm < EPS)
            break;

        double h11, h12, h21, h22;
        hessian(h11, h12, h21, h22);
        double det = h11 * h22 - h12 * h21;
        if (fabs(det) < EPS)
        {
            cout << "  Hessian singular!\n";
            break;
        }

        // Newton step: Δx = -H^{-1} g
        double dx = -(h22 * gx - h12 * gy) / det;
        double dy = -(-h21 * gx + h11 * gy) / det;
        x += dx;
        y += dy;
    }
    printf("  => Ket qua: x*=%.8f, y*=%.8f, f*=%.8f\n\n", x, y, f(x, y));
}

// =====================================================================
// PHƯƠNG PHÁP 3: GOLDEN SECTION SEARCH (Chap 4, tr. 123-128)
// Tìm cực tiểu của hàm unimodal g(t) trên [a, b]
// Tỉ lệ vàng: φ = (√5 - 1) / 2 ≈ 0.618
// =====================================================================
const double PHI = (sqrt(5.0) - 1.0) / 2.0; // ≈ 0.618

// Hàm unimodal 1 biến: g(t) = t^4 - 14t^3 + 60t^2 - 70t
// Cực tiểu tại khoảng t ≈ 0.92 và t ≈ 7.04
double g1var(double t)
{
    return t * t * t * t - 14 * t * t * t + 60 * t * t - 70 * t;
}

double goldenSection(double a, double b, int maxIter = 100, double tol = 1e-8)
{
    cout << "--- Phuong phap 3: GOLDEN SECTION SEARCH ---\n";
    cout << "  Khoang ban dau: [" << a << ", " << b << "]\n";
    double x1 = b - PHI * (b - a);
    double x2 = a + PHI * (b - a);
    double f1 = g1var(x1), f2 = g1var(x2);

    for (int i = 0; i < maxIter; i++)
    {
        if (i % 10 == 0)
            printf("  Iter %3d: [%.6f, %.6f], width=%.2e\n", i, a, b, b - a);
        if (b - a < tol)
            break;

        if (f1 < f2)
        {
            b = x2;
            x2 = x1;
            f2 = f1;
            x1 = b - PHI * (b - a);
            f1 = g1var(x1);
        }
        else
        {
            a = x1;
            x1 = x2;
            f1 = f2;
            x2 = a + PHI * (b - a);
            f2 = g1var(x2);
        }
    }
    double xmin = (a + b) / 2.0;
    printf("  => Cuc tieu tai t*=%.8f, g(t*)=%.8f\n\n", xmin, g1var(xmin));
    return xmin;
}

// =====================================================================
// PHƯƠNG PHÁP BỔ SUNG: Hàm 3 biến với Gradient Descent
// h(x,y,z) = (x-1)^2 + (y-2)^2 + (z-3)^2  => min tại (1,2,3)
// =====================================================================
double h3(double x, double y, double z)
{
    return (x - 1) * (x - 1) + (y - 2) * (y - 2) + (z - 3) * (z - 3);
}
tuple<double, double, double> grad3(double x, double y, double z)
{
    return {2 * (x - 1), 2 * (y - 2), 2 * (z - 3)};
}

void gradDesc3var(double x0, double y0, double z0, double gamma = 0.1)
{
    cout << "--- Gradient Descent - Ham 3 bien ---\n";
    double x = x0, y = y0, z = z0;
    for (int i = 0; i <= 100; i++)
    {
        auto [gx, gy, gz] = grad3(x, y, z);
        double norm = sqrt(gx * gx + gy * gy + gz * gz);
        if (i % 20 == 0 || norm < EPS)
            printf("  Iter %3d: (%.4f,%.4f,%.4f) h=%.6f |g|=%.2e\n",
                   i, x, y, z, h3(x, y, z), norm);
        if (norm < EPS)
            break;
        x -= gamma * gx;
        y -= gamma * gy;
        z -= gamma * gz;
    }
    printf("  => x*=%.6f, y*=%.6f, z*=%.6f, h*=%.8f\n\n", x, y, z, h3(x, y, z));
}

// =====================================================================
// LAGRANGE MULTIPLIER: max f(x1,x2)=2x1+x2+10, st. x1^2+2x2^2=3
// Từ slide Chap 4, trang 143-144
// =====================================================================
void lagrangeExample()
{
    cout << "--- Lagrange Multiplier: max 2x1+x2+10, s.t. x1^2+2x2^2=3 ---\n";
    // Hệ: ∂L/∂x1=0 => 2-2λx1=0 => λ=1/x1
    //     ∂L/∂x2=0 => 1-4λx2=0 => λ=1/(4x2)
    //     g: x1^2+2x2^2=3
    // => x1 = 4x2 => (4x2)^2 + 2x2^2 = 3 => 18x2^2 = 3 => x2 = ±1/√6
    double x2 = 1.0 / sqrt(6.0);
    double x1 = 4 * x2;
    double lam = 1.0 / x1;
    double fval = 2 * x1 + x2 + 10;
    printf("  x1* = %.6f, x2* = %.6f, lambda* = %.6f\n", x1, x2, lam);
    printf("  f* = 2(%.4f) + (%.4f) + 10 = %.6f\n", x1, x2, fval);
    printf("  Constraint check: x1^2 + 2x2^2 = %.6f (should be 3)\n",
           x1 * x1 + 2 * x2 * x2);
}

int main()
{
    cout << "=== CÂU 4: TỐI ƯU HÓA ===\n\n";
    cout << "Bai toan: min f(x,y) = x^2 + 2y^2 - 2xy - 4x\n";
    cout << "(Cuc tieu ly thuyet tai x=4, y=2, f=-8)\n\n";

    // Khởi điểm x0=0, y0=0
    gradientDescent(0.0, 0.0, 0.085, 300);
    newtonMethod(0.0, 0.0, 20);

    cout << "Bai toan 1 bien: min g(t) = t^4 - 14t^3 + 60t^2 - 70t\n";
    goldenSection(0.0, 2.0);

    cout << "Ham 3 bien:\n";
    gradDesc3var(0.0, 0.0, 0.0, 0.1);

    lagrangeExample();
    return 0;
}