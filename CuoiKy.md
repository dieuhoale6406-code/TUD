Tôi đã đọc toàn bộ 5 file PDF. Bây giờ tôi bắt đầu viết code và tổng quan ôn tập.

---

# 🧮 PHẦN 1: SOURCE CODE C++

---

## Câu 1 — Lý thuyết Số (Number Theory)

```cpp
// =====================================================================
// Câu 1 - Lý thuyết Số (Number Theory)
// Bao gồm: Sàng Eratosthenes, GCD/LCM, Euler's Totient,
//          Lũy thừa Modular, Phương trình Diophantine (Extended GCD)
// =====================================================================
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// ---- 1. Sàng Eratosthenes ----------------------------------------
// sieve[k]=0 => k là số nguyên tố, sieve[k]!=0 => ước nguyên tố nhỏ nhất
const int MAXN = 100;
int sieve[MAXN + 1];

void buildSieve(int n) {
    fill(sieve, sieve + n + 1, 0);
    for (int x = 2; x <= n; x++) {
        if (sieve[x] == 0) {
            for (int u = 2 * x; u <= n; u += x) {
                if (sieve[u] == 0) sieve[u] = x;
            }
        }
    }
}

bool isPrime(int n) {
    if (n < 2) return false;
    for (int d = 2; (ll)d * d <= n; d++)
        if (n % d == 0) return false;
    return true;
}

vector<int> primeFactors(int n) {
    vector<int> f;
    for (int d = 2; (ll)d * d <= n; d++) {
        while (n % d == 0) { f.push_back(d); n /= d; }
    }
    if (n > 1) f.push_back(n);
    return f;
}

// ---- 2. Thuật toán Euclid ----------------------------------------
ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }

// ---- 3. Euler Totient Function φ(n) --------------------------------
ll eulerTotient(ll n) {
    ll result = n;
    for (ll p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0) n /= p;
            result -= result / p;
        }
    }
    if (n > 1) result -= result / n;
    return result;
}

// ---- 4. Lũy thừa Modular: x^n mod m trong O(log n) ----------------
ll modpow(ll x, ll n, ll m) {
    ll result = 1;
    x %= m;
    while (n > 0) {
        if (n & 1) result = result * x % m;
        x = x * x % m;
        n >>= 1;
    }
    return result;
}

// Nghịch đảo modular: x^(-1) mod m (m phải là số nguyên tố)
ll modInverse(ll x, ll m) { return modpow(x, m - 2, m); }

// ---- 5. Extended Euclid - Giải phương trình Diophantine ax+by=gcd -
ll extGcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    ll x1, y1;
    ll g = extGcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// Giải ax + by = c, trả về false nếu vô nghiệm
bool solveDiophantine(ll a, ll b, ll c, ll &x, ll &y) {
    ll g = extGcd(a, b, x, y);
    if (c % g != 0) return false;
    x *= c / g;
    y *= c / g;
    return true;
}

// ---- 6. τ(n): số lượng ước, σ(n): tổng ước, μ(n): tích ước -------
ll countDivisors(ll n) {
    // Dựa vào phân tích thừa số: τ(n) = Π(αi + 1)
    ll count = 1, tmp = n;
    for (ll p = 2; p * p <= tmp; p++) {
        int alpha = 0;
        while (tmp % p == 0) { alpha++; tmp /= p; }
        count *= (alpha + 1);
    }
    if (tmp > 1) count *= 2; // bậc 1 => α=1 => (1+1)=2
    return count;
}

int main() {
    cout << "=== CÂU 1: LÝ THUYẾT SỐ ===\n\n";

    // 1. Sàng nguyên tố
    buildSieve(MAXN);
    cout << "[Sieve] Các số nguyên tố <= " << MAXN << ":\n";
    for (int i = 2; i <= MAXN; i++)
        if (sieve[i] == 0) cout << i << " ";
    cout << "\n\n";

    // 2. Phân tích thừa số
    int n = 360;
    auto factors = primeFactors(n);
    cout << "[PrimeFactors] " << n << " = ";
    for (int i = 0; i < (int)factors.size(); i++) {
        cout << factors[i];
        if (i + 1 < (int)factors.size()) cout << " x ";
    }
    cout << "\n";
    cout << "[τ(360)] Số lượng ước = " << countDivisors(360) << "\n\n";

    // 3. GCD / LCM
    ll a = 24, b = 36;
    cout << "[Euclid] gcd(" << a << "," << b << ") = " << gcd(a,b) << "\n";
    cout << "[Euclid] lcm(" << a << "," << b << ") = " << lcm(a,b) << "\n\n";

    // 4. Euler Totient
    ll num = 12;
    cout << "[Totient] φ(" << num << ") = " << eulerTotient(num) << "\n\n";

    // 5. Modular exponentiation
    ll x = 6, exp_n = 15, mod = 17;
    cout << "[ModPow] " << x << "^" << exp_n << " mod " << mod
         << " = " << modpow(x, exp_n, mod) << "\n";
    cout << "[ModInverse] " << x << "^(-1) mod " << mod
         << " = " << modInverse(x, mod) << "\n\n";

    // 6. Phương trình Diophantine: 39x + 15y = 12
    ll px, py;
    ll da = 39, db = 15, dc = 12;
    if (solveDiophantine(da, db, dc, px, py)) {
        cout << "[Diophantine] " << da << "x + " << db << "y = " << dc << "\n";
        cout << "  Nghiem: x = " << px << ", y = " << py << "\n";
        cout << "  Kiem tra: " << da*px + db*py << " == " << dc << "\n";
    } else {
        cout << "[Diophantine] Phuong trinh vo nghiem!\n";
    }

    // 7. Chinese Remainder Theorem minh họa
    // x ≡ 3 (mod 5), x ≡ 4 (mod 7), x ≡ 2 (mod 3)
    cout << "\n[CRT] x=3 mod 5, x=4 mod 7, x=2 mod 3\n";
    ll M = 5 * 7 * 3;
    ll X1 = 21, X2 = 15, X3 = 35;
    ll inv1 = modInverse(X1 % 5, 5);
    ll inv2 = modInverse(X2 % 7, 7);
    ll inv3 = modInverse(X3 % 3, 3);
    ll sol = (3*X1*inv1 + 4*X2*inv2 + 2*X3*inv3) % M;
    cout << "  Nghiem x = " << sol << " (mod " << M << ")\n";
    cout << "  Kiem tra: " << sol << " mod 5 = " << sol%5
         << ", mod 7 = " << sol%7
         << ", mod 3 = " << sol%3 << "\n";

    return 0;
}
```

**Giải thích:** Code triển khai đầy đủ 6 thuật toán của Chương 1: (1) Sàng Eratosthenes O(n log log n) đánh dấu số nguyên tố; (2) Phân tích thừa số nguyên tố O(√n); (3) Euclid O(log n) tính GCD/LCM; (4) Hàm Euler φ(n); (5) Lũy thừa modular O(log n) + nghịch đảo modular qua Fermat; (6) Extended Euclid giải phương trình Diophantine ax+by=c và Chinese Remainder Theorem.

---

## Câu 2 — Trị riêng / Vector riêng (Eigenvalues/Eigenvectors)

```cpp
// =====================================================================
// Câu 2 - Lambda: Trị riêng & Vector riêng (Eigenvalues/Eigenvectors)
// Ma trận 2x2 và 3x3, giải đặc trưng, tìm eigenvectors
// =====================================================================
#include <bits/stdc++.h>
using namespace std;
typedef vector<vector<double>> Mat;

const double EPS = 1e-9;

void printMatrix(const Mat& A, const string& name) {
    cout << name << ":\n";
    for (auto& row : A) {
        cout << "  [";
        for (int j = 0; j < (int)row.size(); j++)
            cout << setw(8) << fixed << setprecision(4) << row[j]
                 << (j+1<(int)row.size() ? "," : "");
        cout << " ]\n";
    }
}

// ---- Ma trận 2x2: Tính eigenvalues bằng đa thức đặc trưng ----------
// det(A - λI) = λ² - (a+d)λ + (ad-bc) = 0
// Trace = a+d, Det = ad-bc
// Δ = Trace² - 4*Det
// λ = (Trace ± √Δ) / 2
pair<double,double> eigen2x2(Mat A) {
    double trace = A[0][0] + A[1][1];
    double det   = A[0][0]*A[1][1] - A[0][1]*A[1][0];
    double disc  = trace*trace - 4*det;
    if (disc < 0) {
        cout << "  [WARNING] Eigenvalues phức (discriminant < 0)\n";
        return {NAN, NAN};
    }
    double lam1 = (trace + sqrt(disc)) / 2.0;
    double lam2 = (trace - sqrt(disc)) / 2.0;
    return {lam1, lam2};
}

// Tìm eigenvector ứng với eigenvalue λ cho ma trận 2x2
// Giải (A - λI)x = 0
vector<double> eigenvec2x2(Mat A, double lam) {
    double a = A[0][0] - lam, b = A[0][1];
    double c = A[1][0],       d = A[1][1] - lam;
    vector<double> v(2);
    if (fabs(b) > EPS || fabs(a) > EPS) {
        if (fabs(a) > EPS) { v[0] = -b; v[1] = a; }
        else               { v[0] =  d; v[1] = -c; }
    } else {
        v[0] = 1; v[1] = 0;
    }
    // Chuẩn hóa
    double norm = sqrt(v[0]*v[0] + v[1]*v[1]);
    if (norm > EPS) { v[0] /= norm; v[1] /= norm; }
    return v;
}

// ---- Ma trận 3x3: Tính eigenvalues bằng đa thức đặc trưng bậc 3 ---
// det(A - λI) = -λ³ + (trA)λ² - (sum of 2x2 minors)λ + det(A) = 0
double det3x3(Mat A) {
    return A[0][0]*(A[1][1]*A[2][2] - A[1][2]*A[2][1])
          -A[0][1]*(A[1][0]*A[2][2] - A[1][2]*A[2][0])
          +A[0][2]*(A[1][0]*A[2][1] - A[1][1]*A[2][0]);
}

double characteristicPoly3(Mat A, double lam) {
    Mat B = A;
    B[0][0] -= lam; B[1][1] -= lam; B[2][2] -= lam;
    return det3x3(B);
}

// Tìm nghiệm đa thức đặc trưng bậc 3 bằng phương pháp bisection + tìm khoảng
vector<double> eigenvalues3x3(Mat A) {
    vector<double> roots;
    double lo = -100.0, hi = 100.0;
    int steps = 10000;
    double step = (hi - lo) / steps;
    double prev = characteristicPoly3(A, lo);
    for (int i = 1; i <= steps; i++) {
        double x = lo + i * step;
        double curr = characteristicPoly3(A, x);
        if (prev * curr < 0) {
            // Tìm nghiệm bằng bisection
            double L = x - step, R = x;
            for (int j = 0; j < 100; j++) {
                double mid = (L + R) / 2.0;
                if (characteristicPoly3(A, L) * characteristicPoly3(A, mid) < 0)
                    R = mid;
                else
                    L = mid;
            }
            double root = (L + R) / 2.0;
            // Tránh trùng lặp
            bool dup = false;
            for (double r : roots) if (fabs(r - root) < 1e-4) { dup = true; break; }
            if (!dup) roots.push_back(root);
        }
        prev = curr;
    }
    sort(roots.begin(), roots.end(), greater<double>());
    return roots;
}

// Gaussian elimination để tìm null space (eigenvector) của (A - λI)
vector<double> eigenvec3x3(Mat A, double lam) {
    Mat M = A;
    for (int i = 0; i < 3; i++) M[i][i] -= lam;
    // Augmented matrix [M | 0], row reduce
    for (int col = 0, row = 0; col < 3 && row < 3; col++) {
        int pivot = -1;
        for (int i = row; i < 3; i++)
            if (fabs(M[i][col]) > EPS) { pivot = i; break; }
        if (pivot == -1) continue;
        swap(M[row], M[pivot]);
        double div = M[row][col];
        for (int j = 0; j < 3; j++) M[row][j] /= div;
        for (int i = 0; i < 3; i++) {
            if (i != row) {
                double f = M[i][col];
                for (int j = 0; j < 3; j++) M[i][j] -= f * M[row][j];
            }
        }
        row++;
    }
    // Trích vector từ null space (free variable = 1)
    vector<double> v(3, 0);
    // Heuristic: tìm free variable
    bool found[3] = {false,false,false};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (fabs(M[i][j]) > EPS) { found[j] = true; break; }
        }
    }
    int freeVar = -1;
    for (int j = 0; j < 3; j++) if (!found[j]) { freeVar = j; break; }
    if (freeVar == -1) freeVar = 2;
    v[freeVar] = 1.0;
    for (int i = 2; i >= 0; i--) {
        int pivCol = -1;
        for (int j = 0; j < 3; j++) {
            if (fabs(M[i][j]) > EPS && j != freeVar) { pivCol = j; break; }
        }
        if (pivCol == -1) continue;
        double sum = 0;
        for (int j = 0; j < 3; j++)
            if (j != pivCol) sum += M[i][j] * v[j];
        v[pivCol] = -sum / M[i][pivCol];
    }
    // Chuẩn hóa
    double norm = sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
    if (norm > EPS) for (auto& x : v) x /= norm;
    return v;
}

// Xác minh: Ax = λx
void verify(Mat A, double lam, vector<double> v, int n) {
    cout << "  Verify Ax = λx: ";
    for (int i = 0; i < n; i++) {
        double ax = 0;
        for (int j = 0; j < n; j++) ax += A[i][j] * v[j];
        double lv = lam * v[i];
        cout << "(" << fixed << setprecision(4) << ax
             << " vs " << lv << ") ";
    }
    cout << "\n";
}

int main() {
    cout << "=== CÂU 2: TRỊ RIÊNG & VECTOR RIÊNG ===\n\n";

    // ---- Ví dụ 1: Ma trận 2x2 từ slide Chap 2 ----------------------
    // A = [[-3, -1], [0, 2]]  => eigenvalues: -3, 2
    cout << "--- Ma trận 2x2 ---\n";
    Mat A2 = {{-3, -1}, {0, 2}};
    printMatrix(A2, "A");
    auto [l1, l2] = eigen2x2(A2);
    cout << "  λ1 = " << l1 << ",  λ2 = " << l2 << "\n";
    auto v1 = eigenvec2x2(A2, l1);
    auto v2 = eigenvec2x2(A2, l2);
    cout << "  Eigenvec(λ1=" << l1 << "): ["
         << v1[0] << ", " << v1[1] << "]\n";
    cout << "  Eigenvec(λ2=" << l2 << "): ["
         << v2[0] << ", " << v2[1] << "]\n";
    verify(A2, l1, v1, 2);
    verify(A2, l2, v2, 2);

    // ---- Ví dụ 2: Ma trận 3x3 ---------------------------------------
    // A = [[4, -2, 1], [2, 0, 1], [2, -2, 3]]
    cout << "\n--- Ma trận 3x3 ---\n";
    Mat A3 = {{4, -2, 1}, {2, 0, 1}, {2, -2, 3}};
    printMatrix(A3, "A");
    auto eigs = eigenvalues3x3(A3);
    cout << "  Eigenvalues: ";
    for (double e : eigs) cout << fixed << setprecision(4) << e << "  ";
    cout << "\n";
    for (double lam : eigs) {
        auto ev = eigenvec3x3(A3, lam);
        cout << "  Eigenvec(λ=" << fixed << setprecision(4) << lam << "): ["
             << ev[0] << ", " << ev[1] << ", " << ev[2] << "]\n";
        verify(A3, lam, ev, 3);
    }

    // ---- Ví dụ 3: Eigendecomposition A = PDP^{-1} cho 2x2 ----------
    cout << "\n--- Eigendecomposition A = P D P^(-1) ---\n";
    Mat B2 = {{2, 1}, {1, 2}};
    printMatrix(B2, "B");
    auto [b1, b2] = eigen2x2(B2);
    cout << "  D = diag(" << b1 << ", " << b2 << ")\n";
    auto bv1 = eigenvec2x2(B2, b1);
    auto bv2 = eigenvec2x2(B2, b2);
    cout << "  P = [[" << bv1[0] << "," << bv2[0] << "],\n"
         << "       [" << bv1[1] << "," << bv2[1] << "]]\n";
    cout << "  det(A) = λ1*λ2 = " << b1*b2 << " (direct: " << det3x3({{B2[0][0],B2[0][1],0},{B2[1][0],B2[1][1],0},{0,0,1}}) << ")\n";

    return 0;
}
```

**Giải thích:** Code tính eigenvalues/eigenvectors cho ma trận 2x2 và 3x3. Với 2x2: giải trực tiếp từ phương trình bậc 2 `λ² - trace·λ + det = 0`. Với 3x3: dùng phương pháp bisection tìm nghiệm của đa thức đặc trưng, sau đó Gaussian elimination để tìm null space `(A - λI)x = 0`. Xác minh `Ax = λx`.

---

## Câu 3 — Bao lồi (Andrew's Convex Hull)

```cpp
// =====================================================================
// Câu 3 - Bao lồi: Thuật toán Andrew's Monotone Chain O(n log n)
// =====================================================================
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;

// Cross product của vector OA và OB
// Dương => B quay trái so với A (từ gốc O)
// Âm   => B quay phải
// 0    => thẳng hàng
ll cross(P O, P A, P B) {
    return (A.first - O.first) * (B.second - O.second)
         - (A.second - O.second) * (B.first - O.first);
}

// Andrew's Monotone Chain Algorithm
// Trả về các điểm trên bao lồi theo thứ tự ngược chiều kim đồng hồ
vector<P> convexHull(vector<P> pts) {
    int n = pts.size();
    if (n < 3) return pts;

    // Bước 1: Sắp xếp theo x, sau đó theo y
    sort(pts.begin(), pts.end());

    vector<P> hull;

    // Bước 2: Xây lower hull
    // Đi từ trái sang phải
    // Đảm bảo hull không quay trái (cross <= 0)
    for (int i = 0; i < n; i++) {
        while (hull.size() >= 2 &&
               cross(hull[hull.size()-2], hull[hull.size()-1], pts[i]) <= 0)
            hull.pop_back();
        hull.push_back(pts[i]);
    }

    // Bước 3: Xây upper hull
    // Đi từ phải sang trái
    int lower_size = hull.size() + 1; // +1 để skip điểm đầu
    for (int i = n - 2; i >= 0; i--) {
        while ((int)hull.size() >= lower_size &&
               cross(hull[hull.size()-2], hull[hull.size()-1], pts[i]) <= 0)
            hull.pop_back();
        hull.push_back(pts[i]);
    }

    // Bỏ điểm cuối (trùng điểm đầu)
    hull.pop_back();
    return hull;
}

// Tính diện tích bao lồi bằng công thức Shoelace
double hullArea(const vector<P>& hull) {
    double area = 0;
    int n = hull.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += (double)hull[i].first * hull[j].second;
        area -= (double)hull[j].first * hull[i].second;
    }
    return fabs(area) / 2.0;
}

// Kiểm tra điểm có trong bao lồi không (bằng góc quay)
bool pointInHull(const vector<P>& hull, P p) {
    int n = hull.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        if (cross(hull[i], hull[j], p) < 0) return false;
    }
    return true;
}

int main() {
    cout << "=== CÂU 3: BAO LỒI (ANDREW'S ALGORITHM) ===\n\n";

    // Test case 1: Bộ điểm cơ bản
    vector<P> pts1 = {
        {1,1},{2,3},{3,1},{4,2},{5,5},
        {6,1},{7,3},{3,4},{2,1},{4,4}
    };
    cout << "[Test 1] Tập điểm:\n  ";
    for (auto [x,y] : pts1) cout << "(" << x << "," << y << ") ";
    cout << "\n";

    auto hull1 = convexHull(pts1);
    cout << "  Bao loi (" << hull1.size() << " dinh, CCW order):\n  ";
    for (auto [x,y] : hull1) cout << "(" << x << "," << y << ") ";
    cout << "\n";
    cout << "  Dien tich bao loi = " << fixed << setprecision(2) << hullArea(hull1) << "\n\n";

    // Test case 2: Điểm trên đường tròn
    cout << "[Test 2] 8 diem tren hinh tron ban kinh 5:\n  ";
    vector<P> pts2;
    for (int i = 0; i < 8; i++) {
        double angle = 2 * M_PI * i / 8;
        pts2.push_back({(ll)round(5*cos(angle)), (ll)round(5*sin(angle))});
        cout << "(" << pts2.back().first << "," << pts2.back().second << ") ";
    }
    // Thêm điểm bên trong
    pts2.push_back({0, 0});
    pts2.push_back({1, 1});
    cout << "\n";
    auto hull2 = convexHull(pts2);
    cout << "  Bao loi (" << hull2.size() << " dinh):\n  ";
    for (auto [x,y] : hull2) cout << "(" << x << "," << y << ") ";
    cout << "\n\n";

    // Test case 3: Kiểm tra điểm trong/ngoài bao lồi
    cout << "[Test 3] Kiem tra diem trong bao loi:\n";
    P inside = {3, 3}, outside = {10, 10};
    // Đảm bảo hull1 theo CCW
    vector<P> hullCCW = hull1;
    // cross check yêu cầu hull theo CCW
    cout << "  Diem (" << inside.first  << "," << inside.second  << "): "
         << (pointInHull(hullCCW, inside)  ? "BEN TRONG" : "BEN NGOAI") << "\n";
    cout << "  Diem (" << outside.first << "," << outside.second << "): "
         << (pointInHull(hullCCW, outside) ? "BEN TRONG" : "BEN NGOAI") << "\n\n";

    // Test case 4: Trình bày từng bước Andrew (minh họa giáo khoa)
    cout << "[Test 4] Minh hoa tung buoc:\n";
    vector<P> pts4 = {{0,0},{1,1},{2,0},{1,-1},{3,1},{2,2},{0,2}};
    sort(pts4.begin(), pts4.end());
    cout << "  Sau khi sort: ";
    for (auto [x,y] : pts4) cout << "(" << x << "," << y << ") ";
    cout << "\n";

    // Lower hull
    vector<P> lower;
    for (auto p : pts4) {
        while (lower.size() >= 2 &&
               cross(lower[lower.size()-2], lower[lower.size()-1], p) <= 0)
            lower.pop_back();
        lower.push_back(p);
    }
    cout << "  Lower hull: ";
    for (auto [x,y] : lower) cout << "(" << x << "," << y << ") ";
    cout << "\n";

    // Upper hull
    vector<P> upper;
    for (int i = (int)pts4.size()-1; i >= 0; i--) {
        while (upper.size() >= 2 &&
               cross(upper[upper.size()-2], upper[upper.size()-1], pts4[i]) <= 0)
            upper.pop_back();
        upper.push_back(pts4[i]);
    }
    upper.pop_back();
    cout << "  Upper hull: ";
    for (auto [x,y] : upper) cout << "(" << x << "," << y << ") ";
    cout << "\n";

    auto hull4 = convexHull(pts4);
    cout << "  Ket qua cuoi: ";
    for (auto [x,y] : hull4) cout << "(" << x << "," << y << ") ";
    cout << "\n  Dien tich = " << hullArea(hull4) << "\n";

    return 0;
}
```

**Giải thích:** Thuật toán Andrew's Monotone Chain: (1) Sắp xếp điểm theo tọa độ x rồi y; (2) Xây **lower hull** từ trái qua phải — loại bỏ điểm nếu cross product ≤ 0 (quay trái); (3) Xây **upper hull** từ phải qua trái — logic tương tự. Kết quả là bao lồi hoàn chỉnh theo thứ tự CCW. Độ phức tạp O(n log n).

---

## Câu 4 — Tối ưu hóa (3 phương pháp: Gradient Descent, Newton, Golden Section)

```cpp
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
double f(double x, double y) {
    return x*x + 2*y*y - 2*x*y - 4*x;
}

// Gradient: ∂f/∂x, ∂f/∂y
pair<double,double> grad(double x, double y) {
    double gx = 2*x - 2*y - 4;   // ∂f/∂x
    double gy = 4*y - 2*x;        // ∂f/∂y
    return {gx, gy};
}

// Hessian 2x2: [[∂²f/∂x², ∂²f/∂x∂y], [∂²f/∂y∂x, ∂²f/∂y²]]
// H = [[2, -2], [-2, 4]]
void hessian(double& h11, double& h12, double& h21, double& h22) {
    h11 = 2; h12 = -2; h21 = -2; h22 = 4;
}

// =====================================================================
// PHƯƠNG PHÁP 1: GRADIENT DESCENT (Chap 4, tr. 6-12)
// x_{i+1} = x_i - γ * ∇f(x_i)^T
// =====================================================================
void gradientDescent(double x0, double y0, double gamma = 0.1, int maxIter = 200) {
    cout << "--- Phuong phap 1: GRADIENT DESCENT (γ=" << gamma << ") ---\n";
    double x = x0, y = y0;
    for (int i = 0; i <= maxIter; i++) {
        auto [gx, gy] = grad(x, y);
        double norm = sqrt(gx*gx + gy*gy);
        if (i % 20 == 0 || norm < EPS)
            printf("  Iter %3d: x=%.6f, y=%.6f, f=%.6f, |grad|=%.2e\n",
                   i, x, y, f(x,y), norm);
        if (norm < EPS) break;
        x -= gamma * gx;
        y -= gamma * gy;
    }
    printf("  => Ket qua: x*=%.6f, y*=%.6f, f*=%.6f\n\n", x, y, f(x,y));
}

// =====================================================================
// PHƯƠNG PHÁP 2: NEWTON'S METHOD (Chap 4, tr. 130-132)
// Δx = -H^{-1} ∇f
// H = [[h11,h12],[h21,h22]], H^{-1} = 1/det * [[h22,-h12],[-h21,h11]]
// =====================================================================
void newtonMethod(double x0, double y0, int maxIter = 50) {
    cout << "--- Phuong phap 2: NEWTON'S METHOD ---\n";
    double x = x0, y = y0;
    for (int i = 0; i <= maxIter; i++) {
        auto [gx, gy] = grad(x, y);
        double norm = sqrt(gx*gx + gy*gy);
        if (i % 5 == 0 || norm < EPS)
            printf("  Iter %2d: x=%.8f, y=%.8f, f=%.8f, |grad|=%.2e\n",
                   i, x, y, f(x,y), norm);
        if (norm < EPS) break;

        double h11, h12, h21, h22;
        hessian(h11, h12, h21, h22);
        double det = h11*h22 - h12*h21;
        if (fabs(det) < EPS) { cout << "  Hessian singular!\n"; break; }

        // Newton step: Δx = -H^{-1} g
        double dx = -(h22*gx - h12*gy) / det;
        double dy = -(-h21*gx + h11*gy) / det;
        x += dx; y += dy;
    }
    printf("  => Ket qua: x*=%.8f, y*=%.8f, f*=%.8f\n\n", x, y, f(x,y));
}

// =====================================================================
// PHƯƠNG PHÁP 3: GOLDEN SECTION SEARCH (Chap 4, tr. 123-128)
// Tìm cực tiểu của hàm unimodal g(t) trên [a, b]
// Tỉ lệ vàng: φ = (√5 - 1) / 2 ≈ 0.618
// =====================================================================
const double PHI = (sqrt(5.0) - 1.0) / 2.0;  // ≈ 0.618

// Hàm unimodal 1 biến: g(t) = t^4 - 14t^3 + 60t^2 - 70t
// Cực tiểu tại khoảng t ≈ 0.92 và t ≈ 7.04
double g1var(double t) {
    return t*t*t*t - 14*t*t*t + 60*t*t - 70*t;
}

double goldenSection(double a, double b, int maxIter = 100, double tol = 1e-8) {
    cout << "--- Phuong phap 3: GOLDEN SECTION SEARCH ---\n";
    cout << "  Khoang ban dau: [" << a << ", " << b << "]\n";
    double x1 = b - PHI*(b - a);
    double x2 = a + PHI*(b - a);
    double f1 = g1var(x1), f2 = g1var(x2);

    for (int i = 0; i < maxIter; i++) {
        if (i % 10 == 0)
            printf("  Iter %3d: [%.6f, %.6f], width=%.2e\n", i, a, b, b-a);
        if (b - a < tol) break;

        if (f1 < f2) {
            b = x2; x2 = x1; f2 = f1;
            x1 = b - PHI*(b - a);
            f1 = g1var(x1);
        } else {
            a = x1; x1 = x2; f1 = f2;
            x2 = a + PHI*(b - a);
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
double h3(double x, double y, double z) {
    return (x-1)*(x-1) + (y-2)*(y-2) + (z-3)*(z-3);
}
tuple<double,double,double> grad3(double x, double y, double z) {
    return {2*(x-1), 2*(y-2), 2*(z-3)};
}

void gradDesc3var(double x0, double y0, double z0, double gamma = 0.1) {
    cout << "--- Gradient Descent - Ham 3 bien ---\n";
    double x = x0, y = y0, z = z0;
    for (int i = 0; i <= 100; i++) {
        auto [gx,gy,gz] = grad3(x,y,z);
        double norm = sqrt(gx*gx+gy*gy+gz*gz);
        if (i % 20 == 0 || norm < EPS)
            printf("  Iter %3d: (%.4f,%.4f,%.4f) h=%.6f |g|=%.2e\n",
                   i, x, y, z, h3(x,y,z), norm);
        if (norm < EPS) break;
        x -= gamma*gx; y -= gamma*gy; z -= gamma*gz;
    }
    printf("  => x*=%.6f, y*=%.6f, z*=%.6f, h*=%.8f\n\n", x, y, z, h3(x,y,z));
}

// =====================================================================
// LAGRANGE MULTIPLIER: max f(x1,x2)=2x1+x2+10, st. x1^2+2x2^2=3
// Từ slide Chap 4, trang 143-144
// =====================================================================
void lagrangeExample() {
    cout << "--- Lagrange Multiplier: max 2x1+x2+10, s.t. x1^2+2x2^2=3 ---\n";
    // Hệ: ∂L/∂x1=0 => 2-2λx1=0 => λ=1/x1
    //     ∂L/∂x2=0 => 1-4λx2=0 => λ=1/(4x2)
    //     g: x1^2+2x2^2=3
    // => x1 = 4x2 => (4x2)^2 + 2x2^2 = 3 => 18x2^2 = 3 => x2 = ±1/√6
    double x2 = 1.0 / sqrt(6.0);
    double x1 = 4 * x2;
    double lam = 1.0 / x1;
    double fval = 2*x1 + x2 + 10;
    printf("  x1* = %.6f, x2* = %.6f, lambda* = %.6f\n", x1, x2, lam);
    printf("  f* = 2(%.4f) + (%.4f) + 10 = %.6f\n", x1, x2, fval);
    printf("  Constraint check: x1^2 + 2x2^2 = %.6f (should be 3)\n",
           x1*x1 + 2*x2*x2);
}

int main() {
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
```

**Giải thích:** Ba phương pháp từ Chương 4: (1) **Gradient Descent** cập nhật `x = x - γ∇f` — cần chọn learning rate γ phù hợp; (2) **Newton's Method** dùng Hessian `Δx = -H⁻¹∇f` — hội tụ siêu tuyến tính, chỉ cần vài bước; (3) **Golden Section Search** thu hẹp khoảng tìm kiếm theo tỉ lệ vàng φ≈0.618 cho hàm unimodal. Phần Lagrange Multiplier minh họa tối ưu có ràng buộc.

---

## Câu 5 — Xác suất & Thống kê (Probability + CSV cho đồ thị)

```cpp
// =====================================================================
// Câu 5 - Xác suất Thống kê
// In kết quả tính toán + xuất CSV để vẽ đồ thị
// Bao gồm: Binomial, Normal (CLT), Geometric, Markov Chains
// =====================================================================
#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);

// ---- Hàm hỗ trợ ------------------------------------------------
double factorial(int n) {
    double r = 1; for (int i = 2; i <= n; i++) r *= i; return r;
}
double C(int n, int k) {
    if (k < 0 || k > n) return 0;
    return factorial(n) / (factorial(k) * factorial(n-k));
}

// =====================================================================
// 1. PHÂN PHỐI NHỊ THỨC: X ~ Bin(n, p)
// P(X=k) = C(n,k) * p^k * (1-p)^(n-k)
// E[X] = np, Var[X] = np(1-p)
// =====================================================================
void binomialDistribution(int n, double p) {
    cout << "\n=== PHAN PHOI NHI THUC Bin(" << n << ", " << p << ") ===\n";
    printf("%-5s %-12s %-12s\n", "k", "P(X=k)", "P(X<=k)");
    double cdf = 0, mean = n * p;
    double var = n * p * (1 - p);
    for (int k = 0; k <= n; k++) {
        double pmf = C(n, k) * pow(p, k) * pow(1-p, n-k);
        cdf += pmf;
        printf("%-5d %-12.6f %-12.6f\n", k, pmf, cdf);
    }
    printf("E[X] = %.4f, Var[X] = %.4f, SD = %.4f\n", mean, var, sqrt(var));
}

// =====================================================================
// 2. PHÂN PHỐI CHUẨN: N(μ, σ²)
// pdf(x) = 1/(σ√2π) * exp(-(x-μ)²/(2σ²))
// Xấp xỉ bằng CLT: Bin(n,p) ≈ N(np, np(1-p))
// =====================================================================
double normalPDF(double x, double mu, double sigma) {
    return exp(-0.5*pow((x-mu)/sigma, 2)) / (sigma * sqrt(2*PI));
}
// CDF chuẩn N(0,1) dùng xấp xỉ
double normalCDF(double z) {
    return 0.5 * erfc(-z / sqrt(2.0));
}

void normalDistribution(double mu, double sigma, double a, double b) {
    cout << "\n=== PHAN PHOI CHUAN N(" << mu << ", " << sigma << "^2) ===\n";
    printf("P(%.2f < X < %.2f) = %.6f\n", a, b,
           normalCDF((b-mu)/sigma) - normalCDF((a-mu)/sigma));
    printf("P(X < %.2f) = %.6f\n", mu + sigma,
           normalCDF(1.0));
    printf("P(X < %.2f) = %.6f\n", mu + 2*sigma,
           normalCDF(2.0));
    printf("Quy tac 68-95-99.7:\n");
    printf("  P(mu-s < X < mu+s)   = %.4f (ky vong ~0.6827)\n",
           normalCDF(1.0) - normalCDF(-1.0));
    printf("  P(mu-2s < X < mu+2s) = %.4f (ky vong ~0.9545)\n",
           normalCDF(2.0) - normalCDF(-2.0));
    printf("  P(mu-3s < X < mu+3s) = %.4f (ky vong ~0.9973)\n",
           normalCDF(3.0) - normalCDF(-3.0));
}

// =====================================================================
// 3. PHÂN PHỐI HÌNH HỌC: P(X=k) = (1-p)^(k-1) * p
// Thành công lần đầu ở lần k
// E[X] = 1/p
// =====================================================================
void geometricDistribution(double p, int kMax = 15) {
    cout << "\n=== PHAN PHOI HINH HOC (p=" << p << ") ===\n";
    printf("%-5s %-12s %-12s\n", "k", "P(X=k)", "P(X<=k)");
    double cdf = 0;
    for (int k = 1; k <= kMax; k++) {
        double pmf = pow(1-p, k-1) * p;
        cdf += pmf;
        printf("%-5d %-12.6f %-12.6f\n", k, pmf, cdf);
    }
    printf("E[X] = %.4f (ly thuyet 1/p = %.4f)\n",
           1.0/p, 1.0/p);
}

// =====================================================================
// 4. CHUỖI MARKOV (Markov Chain) - Ví dụ thời tiết từ slide tr. 81-85
// States: 0=Nice, 1=Rainy, 2=Snowy
// =====================================================================
void markovChain() {
    cout << "\n=== CHUOI MARKOV - Vi du thoi tiet ===\n";
    // Ma trận chuyển P[i][j] = P(state j | state i)
    // Từ slide: Nice->Rainy=0.75, Nice->Snowy=0.25
    //           Rainy->Nice=0.25, Rainy->Rainy=0.25, Rainy->Snowy=0.50
    //           Snowy->Nice=0.25, Snowy->Rainy=0.50, Snowy->Snowy=0.25
    double P[3][3] = {
        {0.00, 0.75, 0.25},   // từ Nice
        {0.25, 0.25, 0.50},   // từ Rainy
        {0.25, 0.50, 0.25}    // từ Snowy
    };
    vector<string> states = {"Nice", "Rainy", "Snowy"};
    cout << "Ma tran chuyen P:\n";
    cout << setw(10) << " ";
    for (auto& s : states) cout << setw(8) << s;
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << setw(10) << states[i];
        for (int j = 0; j < 3; j++)
            printf("  %6.3f", P[i][j]);
        cout << "\n";
    }

    // Phân phối ban đầu: bắt đầu từ Nice
    double dist[3] = {1.0, 0.0, 0.0};
    cout << "\nPhan phoi xac suat qua cac buoc:\n";
    printf("%-5s %-8s %-8s %-8s\n", "Step", "Nice", "Rainy", "Snowy");
    for (int step = 0; step <= 20; step++) {
        printf("%-5d %-8.4f %-8.4f %-8.4f\n",
               step, dist[0], dist[1], dist[2]);
        // Cập nhật: new_dist[j] = Σ_i dist[i] * P[i][j]
        double newdist[3] = {0, 0, 0};
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                newdist[j] += dist[i] * P[i][j];
        for (int i = 0; i < 3; i++) dist[i] = newdist[i];
    }
    cout << "(Phan phoi dung: khoang [0.2, 0.44, 0.36])\n";
}

// =====================================================================
// 5. XUẤT DỮ LIỆU CSV ĐỂ VẼ ĐỒ THỊ
//    File: binomial_dist.csv, normal_dist.csv, geometric_dist.csv
// =====================================================================
void exportCSV() {
    // a) Binomial distribution Bin(20, 0.3)
    {
        ofstream f("binomial_dist.csv");
        f << "k,pmf,cdf\n";
        int n = 20; double p = 0.3;
        double cdf = 0;
        for (int k = 0; k <= n; k++) {
            double pmf = C(n,k) * pow(p,k) * pow(1-p,n-k);
            cdf += pmf;
            f << k << "," << pmf << "," << cdf << "\n";
        }
        cout << "\n[CSV] Da xuat: binomial_dist.csv (Bin(20,0.3))\n";
        cout << "  Ve do thi: Bar chart cho PMF, Line chart cho CDF\n";
        cout << "  Python: import pandas as pd, matplotlib.pyplot as plt\n";
        cout << "          df = pd.read_csv('binomial_dist.csv')\n";
        cout << "          df.plot(x='k', y='pmf', kind='bar')\n";
    }

    // b) Normal distribution N(5, 4) pdf
    {
        ofstream f("normal_dist.csv");
        f << "x,pdf_mu5_s2,pdf_mu5_s1,pdf_mu3_s1\n";
        for (int i = -20; i <= 200; i++) {
            double x = i * 0.05;
            f << x << ","
              << normalPDF(x, 5, 2) << ","
              << normalPDF(x, 5, 1) << ","
              << normalPDF(x, 3, 1) << "\n";
        }
        cout << "[CSV] Da xuat: normal_dist.csv (so sanh N(5,2), N(5,1), N(3,1))\n";
        cout << "  Ve do thi: Line chart, x=[-1,10], 3 duong khac nhau\n";
    }

    // c) Geometric distribution
    {
        ofstream f("geometric_dist.csv");
        f << "k,pmf_p02,pmf_p05,pmf_p08\n";
        for (int k = 1; k <= 20; k++) {
            f << k << ","
              << pow(0.8,k-1)*0.2 << ","
              << pow(0.5,k-1)*0.5 << ","
              << pow(0.2,k-1)*0.8 << "\n";
        }
        cout << "[CSV] Da xuat: geometric_dist.csv (so sanh p=0.2,0.5,0.8)\n";
        cout << "  Ve do thi: Line chart, x=[1,20], 3 duong cho 3 gia tri p\n";
    }

    // d) Markov chain stationary distribution (hội tụ theo bước)
    {
        ofstream f("markov_chain.csv");
        f << "step,P_Nice,P_Rainy,P_Snowy\n";
        double P[3][3] = {
            {0.00,0.75,0.25}, {0.25,0.25,0.50}, {0.25,0.50,0.25}
        };
        double dist[3] = {1.0, 0.0, 0.0};
        for (int step = 0; step <= 30; step++) {
            f << step << "," << dist[0] << "," << dist[1] << "," << dist[2] << "\n";
            double nd[3] = {0,0,0};
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    nd[j] += dist[i]*P[i][j];
            for (int i = 0; i < 3; i++) dist[i] = nd[i];
        }
        cout << "[CSV] Da xuat: markov_chain.csv (hoi tu phan phoi dung)\n";
        cout << "  Ve do thi: Line chart 3 duong, truc x=buoc, truc y=xac suat\n";
    }
}

// =====================================================================
// 6. BÀI TOÁN KẾT HỢP - Ném xúc xắc, xác suất theo tài liệu Chap 5
// =====================================================================
void diceProblems() {
    cout << "\n=== CAC BAI TOAN XAC SUAT TU SLIDE ===\n";

    // P(sum=10 | 2 dice)
    int count10 = 0;
    for (int i = 1; i <= 6; i++)
        for (int j = 1; j <= 6; j++)
            if (i+j == 10) count10++;
    printf("P(tong 2 xuc xac = 10) = %d/36 = %.4f\n", count10, (double)count10/36);

    // P(it nhat 1 lan ra 6 trong 10 lan nem)
    double p_no6 = pow(5.0/6.0, 10);
    printf("P(it nhat 1 lan ra 6 trong 10 lan) = 1-(5/6)^10 = %.6f\n", 1-p_no6);

    // 3 la bai co cung gia tri: P = 13*C(4,3) / C(52,3)
    double desired = 13 * C(4,3);
    double total = C(52,3);
    printf("P(3 bai cung gia tri) = %.0f/%.0f = 1/%.0f = %.6f\n",
           desired, total, total/desired, desired/total);

    // E[so hop trong] khi bo n bong vao n hop
    int n = 10;
    double prob_empty = pow((double)(n-1)/n, n);
    double expected_empty = n * prob_empty;
    printf("E[hop trong] khi bo %d bong vao %d hop = %.4f\n",
           n, n, expected_empty);
}

int main() {
    cout << "=== CÂU 5: XÁC SUẤT THỐNG KÊ ===\n";

    binomialDistribution(10, 0.4);
    normalDistribution(5.0, 2.0, 3.0, 7.0);
    geometricDistribution(0.3, 12);
    markovChain();
    diceProblems();
    exportCSV();

    cout << "\n=== HUONG DAN VE DO THI (Python) ===\n";
    cout << "import pandas as pd\nimport matplotlib.pyplot as plt\n\n";
    cout << "# 1. Binomial\ndf = pd.read_csv('binomial_dist.csv')\n";
    cout << "fig, (ax1,ax2) = plt.subplots(1,2)\n";
    cout << "ax1.bar(df.k, df.pmf); ax1.set_title('PMF Bin(20,0.3)')\n";
    cout << "ax2.plot(df.k, df.cdf); ax2.set_title('CDF Bin(20,0.3)')\n\n";
    cout << "# 2. Normal\ndf2 = pd.read_csv('normal_dist.csv')\n";
    cout << "df2.plot(x='x', y=['pdf_mu5_s2','pdf_mu5_s1','pdf_mu3_s1'])\n\n";
    cout << "# 3. Markov\ndf3 = pd.read_csv('markov_chain.csv')\n";
    cout << "df3.plot(x='step', y=['P_Nice','P_Rainy','P_Snowy'])\n";
    cout << "plt.show()\n";

    return 0;
}
```

**Giải thích:** Code tính toán 4 phân phối xác suất chính từ Chương 5: Binomial (PMF, CDF, E[X], Var[X]), Normal (PDF, CDF, quy tắc 68-95-99.7), Geometric, và Markov Chain (ma trận chuyển + hội tụ về phân phối dừng). Xuất 4 file CSV để vẽ đồ thị bằng Python/matplotlib.

---

---

# 📖 PHẦN 2: TỔNG QUAN LÝ THUYẾT & TRỌNG TÂM ÔN TẬP

---

## 📌 Câu 1 — Lý thuyết Số (Chap 1, 49 trang)

**Công thức cốt lõi:**

- **Số nguyên tố:** n là nguyên tố nếu chỉ chia hết cho 1 và n; kiểm tra trong O(√n)
- **Phân tích thừa số:** n = p₁^α₁ · p₂^α₂ · ... · pₖ^αₖ → τ(n)=∏(αᵢ+1), σ(n)=∏(pᵢ^(αᵢ+1)-1)/(pᵢ-1)
- **Sàng Eratosthenes:** O(n log log n), đánh dấu bội của mỗi số nguyên tố
- **GCD Euclid:** gcd(a,b) = gcd(b, a mod b), O(log n)
- **LCM:** lcm(a,b) = a·b / gcd(a,b)
- **Euler φ(n):** φ(n) = n · ∏(1 - 1/pᵢ) cho các nguyên tố pᵢ | n
- **Lũy thừa modular:** x^n mod m trong O(log n) bằng fast exponentiation
- **Nghịch đảo modular:** x⁻¹ = x^(m-2) mod m (m nguyên tố, dùng Fermat)
- **Diophantine ax+by=c:** giải được ⟺ gcd(a,b) | c, dùng Extended Euclid
- **CRT:** hệ x≡aᵢ (mod mᵢ) có nghiệm duy nhất mod M=m₁m₂...mₙ khi các mᵢ đôi một nguyên tố cùng nhau

**Tập trung vào:** Slides trang 17–28 (Algorithms), trang 31–38 (Modular), trang 41–45 (Equations)

---

## 📌 Câu 2 — Trị riêng / Vector riêng (Chap 2, 82 trang)

**Công thức cốt lõi:**

- **Định nghĩa:** Ax = λx, x ≠ 0 → λ là eigenvalue, x là eigenvector
- **Bước 1:** Đa thức đặc trưng: det(A - λI) = 0
- **Bước 2:** Giải đa thức để tìm λ₁, λ₂, ..., λₙ
- **Bước 3:** Với mỗi λᵢ, giải (A - λᵢI)x = 0 → tìm eigenspace Eλ
- **Eigendecomposition:** A = PDP⁻¹, P gồm các eigenvectors, D=diag(λ₁,...,λₙ)
- **Cholesky:** A = LL^T với A đối xứng xác định dương; det(A) = ∏lᵢᵢ²
- **SVD:** A = UΣV^T; singular values σᵢ = √(eigenvalues của A^TA)
- **Tính chất:** det(A) = ∏λᵢ, trace(A) = ∑λᵢ, A^k = PD^kP⁻¹

**Tập trung vào:** Slides trang 27–35 (Eigenvalues/Eigenvectors), trang 51–59 (Eigendecomposition)

---

## 📌 Câu 3 — Bao lồi (Chap 3, 45 trang)

**Công thức cốt lõi:**

- **Cross product:** (a-c)×(b-c) = (a.x-c.x)(b.y-c.y) - (a.y-c.y)(b.x-c.x)
  - > 0: b quay trái (CCW), < 0: quay phải (CW), = 0: thẳng hàng
- **Andrew's Algorithm (O(n log n)):**
  1. Sort điểm theo (x, y)
  2. Xây lower hull: đi trái→phải, loại điểm nếu cross ≤ 0
  3. Xây upper hull: đi phải→trái, logic tương tự
- **Shoelace formula:** Area = ½|∑(xᵢyᵢ₊₁ - xᵢ₊₁yᵢ)|
- **Pick's theorem:** Area = a + b/2 - 1 (a: điểm nguyên trong, b: trên biên)
- **Khoảng cách điểm-đường thẳng:** d = |(s₁-p)×(s₂-p)| / |s₂-s₁|

**Tập trung vào:** Slides trang 40–45 (Convex Hull Problem), trang 8–10 (Cross Product)

---

## 📌 Câu 4 — Tối ưu hóa (Chap 4, 209 trang)

**Công thức cốt lõi:**

**Phương pháp 1 — Gradient Descent:**

- x\_{i+1} = xᵢ - γ · ∇f(xᵢ)^T; điều kiện hội tụ: f(x₁) ≥ f(x₂) ≥ ...
- Chọn γ (learning rate) quan trọng: nhỏ → chậm, lớn → diverge

**Phương pháp 2 — Newton's Method:**

- Δx = -H⁻¹∇f; H là ma trận Hessian (∂²f/∂xᵢ∂xⱼ)
- Hội tụ bậc 2; tại cực tiểu: H > 0; tại cực đại: H < 0; saddle point: H không xác định dấu

**Phương pháp 3 — Golden Section Search (hàm unimodal):**

- φ = (√5-1)/2 ≈ 0.618; thu hẹp khoảng [a,b] theo tỉ lệ vàng
- Nếu f(x₁) < f(x₂) → max nằm trong [xmin, x₂]; ngược lại trong [x₁, xmax]

**Lagrange Multiplier (tối ưu có ràng buộc):**

- L(x,λ) = f(x) + λ(b - g(x)); đặt ∂L/∂xᵢ = 0 và ∂L/∂λⱼ = 0

**Điều kiện cực trị (hàm nhiều biến):**

- Cần: ∇f = 0 (stationary point)
- Đủ: H > 0 → cực tiểu; H < 0 → cực đại

**Tập trung vào:** Slides trang 6–12 (Gradient Descent), trang 112–122 (NLP, Hessian), trang 123–128 (Golden Section), trang 139–144 (Lagrange)

---

## 📌 Câu 5 — Xác suất Thống kê (Chap 5, 93 trang)

**Công thức cốt lõi:**

- **Quy tắc cơ bản:** P(Ā)=1-P(A); P(A∪B)=P(A)+P(B)-P(A∩B); P(A|B)=P(A∩B)/P(B)
- **Binomial X~Bin(n,p):** P(X=k)=C(n,k)pᵏ(1-p)ⁿ⁻ᵏ; E=np; Var=np(1-p)
- **Geometric X~Geo(p):** P(X=k)=(1-p)^(k-1)p; E=1/p
- **Normal N(μ,σ²):** pdf = 1/(σ√2π) · exp(-(x-μ)²/2σ²); CLT: Bin(n,p) → N(np, np(1-p))
- **Markov Chain:** phân phối tại bước t+1: dist\_{t+1} = dist_t · P; phân phối dừng: π = πP
- **Expected value:** E[X]=∑xP(X=x); Linearity: E[X₁+...+Xₙ]=E[X₁]+...+E[Xₙ]
- **Vẽ đồ thị:** dùng CSV output + Python/matplotlib (bar chart PMF, line chart CDF/pdf)

**Tập trung vào:** Slides trang 4–8 (Calculation), trang 21–27 (Random Variables), trang 41–43 (Binomial), trang 65–76 (Markov Chains)

---

---

Tôi đã hoàn tất việc cung cấp Source Code và Tổng quan lý thuyết. **Bạn muốn đi sâu vào chi tiết ôn tập hay giải tay thử bài toán của câu nào tiếp theo?**

Đã đọc xong toàn bộ 28 file `.cpp`. Bắt đầu thực hiện tuần tự 4 bước.

---

# 🔍 BƯỚC 1: PHÂN TÍCH & AUDIT CODE

## 1.1 — Kiểm kê File & % Coverage

| Chương     | File(s) hiện có                                                                                                                                                      | Chức năng                                                                             | % Coverage đề thi |
| ---------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------- | :---------------: |
| **Chap 1** | `SangEratosthenes.cpp`, `Euclid.cpp`, `C1_UCLN_BCNN.cpp`, `amummodn.cpp`, `Diophante.cpp`, `ThangDuTrungHoa.cpp`, `TichSoNguyenTo.cpp`, `SoHoanHaoKhongVuotQuaN.cpp` | Sàng, GCD/LCM, ModPow, Extended Euclid, CRT (brute-force), Phân tích TSN, Số hoàn hảo |     **~65%**      |
| **Chap 2** | `bai1.cpp`, `bai2.cpp`, `bai3.cpp`, `bai4.cpp`, `phanracholesky.cpp`, `SVD.cpp`                                                                                      | Định thức, Ma trận nghịch đảo, Eigen (Jacobi+Power), Cholesky, SVD (dùng Eigen lib)   |     **~70%**      |
| **Chap 3** | `baoloi.cpp`, `cos.cpp`                                                                                                                                              | Convex Hull (Andrew), Cosine Similarity + KD-tree                                     |     **~55%**      |
| **Chap 4** | `C4_GD.cpp`, `C4_GDnhieubien.cpp`, `C4_GDvsMomentum.cpp`, `C4_GDvsMomentum_nhieubien.cpp`, `donhinh1pha.cpp`, `donhinh2pha.cpp`                                      | GD 1/nhiều biến, GD+Momentum, Simplex 1/2 pha                                         |     **~50%**      |
| **Chap 5** | `bai5.cpp`, `markov_final_order.cpp`, `markov_modular.cpp`                                                                                                           | Markov chain matrix power, Ước lượng P từ dữ liệu                                     |     **~55%**      |

---

## 1.2 — Bảng Mapping: Tên Tiếng Việt → Tiếng Anh

### 📁 Chuong1/

| Tên cũ (tiếng Việt)        | Tên mới (tiếng Anh)            | File                         |
| -------------------------- | ------------------------------ | ---------------------------- |
| `Sang()`                   | `sieve()`                      | `SangEratosthenes.cpp`       |
| `SoNguyenTo[]`             | `isPrime[]`                    | `SangEratosthenes.cpp`       |
| `InNguyenToTrongDoan()`    | `printPrimesInRange()`         | (commented)                  |
| `gan_a, gan_b`             | `nearest_a, nearest_b`         | `SangEratosthenes.cpp`       |
| `xa_a, xa_b`               | `farthest_a, farthest_b`       | `SangEratosthenes.cpp`       |
| `LayDu()`                  | `modPow()`                     | `amummodn.cpp`               |
| `kq`                       | `result`                       | `amummodn.cpp`               |
| `ThangDuTrungHoa()`        | `chineseRemainderBruteForce()` | `ThangDuTrungHoa.cpp`        |
| `PhanTichThuaSoNguyenTo()` | `primeFactorize()`             | `TichSoNguyenTo.cpp`         |
| `SoHoanHao()`              | `isPerfectNumber()`            | `SoHoanHaoKhongVuotQuaN.cpp` |
| `TimSoHoanHao()`           | `findPerfectNumbers()`         | `SoHoanHaoKhongVuotQuaN.cpp` |
| `SoNguyenTo()`             | `checkPrime()`                 | `SoHoanHaoKhongVuotQuaN.cpp` |
| `NguyenToGanM()`           | `nearestPrime()`               | `SoHoanHaoKhongVuotQuaN.cpp` |

### 📁 Chuong2/

| Tên cũ              | Tên mới                | File                                 |
| ------------------- | ---------------------- | ------------------------------------ |
| `dinhthuc()`        | `determinant()`        | `bai1.cpp`                           |
| `nhapmatran()`      | `readMatrix()`         | `bai2,3,4.cpp`, `phanracholesky.cpp` |
| `nghichdao()`       | `computeInverse()`     | `bai2.cpp`                           |
| `ghepmatrandonvi()` | `appendIdentity()`     | `bai2.cpp`                           |
| `timpivot()`        | `findPivotRow()`       | `bai2.cpp`                           |
| `doihang()`         | `swapRows()`           | `bai2.cpp`                           |
| `chuanhoahang()`    | `normalizeRow()`       | `bai2.cpp`                           |
| `khuhang()`         | `eliminateRow()`       | `bai2.cpp`                           |
| `inketqua()`        | `printResult()`        | `bai2.cpp`                           |
| `ktradoixung()`     | `isSymmetric()`        | `bai3.cpp`, `bai4.cpp`               |
| `ketquajacobi()`    | `printJacobiResult()`  | `bai3.cpp`                           |
| `luythua()`         | `powerIteration()`     | `bai3.cpp`                           |
| `lamdamoi`          | `newLambda`            | `bai3.cpp`                           |
| `chuan`             | `vecNorm`              | `bai3.cpp`                           |
| `so_lap_toi_da`     | `MAX_ITER`             | `bai3.cpp`                           |
| `kqphanra()`        | `printDecomposition()` | `bai4.cpp`                           |
| `phanra()`          | `eigenDecompose()`     | `bai4.cpp`                           |
| `doixung()`         | `isSymmetric()`        | `phanracholesky.cpp`                 |
| `xacdinhduong()`    | `isPositiveDefinite()` | `phanracholesky.cpp`                 |

### 📁 Chuong3/

| Tên cũ                  | Tên mới                     | File         |
| ----------------------- | --------------------------- | ------------ |
| `struct Diem`           | `struct Point`              | `baoloi.cpp` |
| `tichcohuong()`         | `crossProduct()`            | `baoloi.cpp` |
| `timbaoloi()`           | `computeConvexHull()`       | `baoloi.cpp` |
| `in()`                  | `printHull()`               | `baoloi.cpp` |
| `tinhDienTich()`        | `computeArea()`             | `baoloi.cpp` |
| `khoangCach()`          | `euclidDistance()`          | `baoloi.cpp` |
| `timDiemGanNhat()`      | `findClosestPair()`         | `baoloi.cpp` |
| `namTrenDoan()`         | `isOnSegment()`             | `baoloi.cpp` |
| `namTrongDaGiacLoi()`   | `isInsideConvexPolygon()`   | `baoloi.cpp` |
| `tinhChuVi()`           | `computePerimeter()`        | `baoloi.cpp` |
| `bao_duoi` / `bao_tren` | `lower_hull` / `upper_hull` | `baoloi.cpp` |
| `tap_diem`              | `points`                    | `baoloi.cpp` |
| `diem_goc`              | `original_pts`              | `baoloi.cpp` |

### 📁 Chuong4/

| Tên cũ        | Tên mới               | File              |
| ------------- | --------------------- | ----------------- |
| `anCoBan()`   | `getBasicVariables()` | `donhinh1pha.cpp` |
| `initTable()` | `initSimplexTable()`  | `donhinh1pha.cpp` |
| `voNghiem`    | `is_unbounded`        | `donhinh1pha.cpp` |
| `idAnCoBan`   | `basis_indices`       | `donhinh1pha.cpp` |

### 📁 Chuong5/

| Tên cũ               | Tên mới                  | File       |
| -------------------- | ------------------------ | ---------- |
| `nhanMaTran()`       | `multiplyMatrix()`       | `bai5.cpp` |
| `luyThuaMaTran()`    | `matrixPower()`          | `bai5.cpp` |
| `nhanVectorMaTran()` | `multiplyVectorMatrix()` | `bai5.cpp` |
| `ketQua`             | `result`                 | `bai5.cpp` |

---

# 🔬 BƯỚC 2: PHÂN TÍCH LỖ HỔNG (GAP ANALYSIS)

## 2.1 — Chap 1 (Number Theory) — **thiếu ~35%**

| Kiến thức trong Slide             | Trạng thái trong Code                                                                         |
| --------------------------------- | --------------------------------------------------------------------------------------------- |
| Sieve of Eratosthenes             | ✅ Có, nhưng phần active bị lẫn logic "cặp gần/xa nhất"                                       |
| GCD/LCM (Euclid)                  | ✅ Đủ                                                                                         |
| Extended Euclid + Diophantine     | ✅ Đủ                                                                                         |
| **Euler's Totient Function φ(n)** | ❌ **HOÀN TOÀN THIẾU** _(Slide 29)_                                                           |
| Modular Exponentiation            | ✅ Có (`LayDu`) nhưng trộn lẫn Fibonacci vô nghĩa                                             |
| Modular Inverse (Fermat)          | ❌ **THIẾU** _(Slide 37)_                                                                     |
| **CRT đúng thuật toán**           | ❌ Code hiện tại là **brute-force** vét cạn x=1,2,3... — **SAI** so với slide _(Slide 44-45)_ |
| Wilson's Theorem                  | ❌ Thiếu (slide 49)                                                                           |

**Lỗi logic nghiêm trọng:** `ThangDuTrungHoa.cpp` dùng vòng lặp `while(true) x++` — **O(∞)** với input lớn. Slide dạy thuật toán O(n·log m) chính xác.

## 2.2 — Chap 2 (Linear Algebra) — **thiếu ~30%**

| Kiến thức trong Slide                          | Trạng thái trong Code                                                                                     |
| ---------------------------------------------- | --------------------------------------------------------------------------------------------------------- |
| Eigenvalue (Jacobi - ma trận đối xứng)         | ✅ `bai3.cpp`, `bai4.cpp`                                                                                 |
| Eigenvalue (Power Iteration - không đối xứng)  | ✅ `bai3.cpp`                                                                                             |
| Cholesky A = LL^T                              | ✅ `phanracholesky.cpp`                                                                                   |
| **SVD không dùng thư viện ngoài**              | ❌ `SVD.cpp` **phụ thuộc `#include "Eigen/Dense"`** — không compile được trên máy thi nếu không cài Eigen |
| **Eigendecomposition A = PDP^{-1} in kết quả** | ⚠️ Có nhưng chỉ cho ma trận **đối xứng**                                                                  |

## 2.3 — Chap 3 (Geometry/Convex Hull) — **thiếu ~45%**

| Kiến thức trong Slide               | Trạng thái trong Code                                                                                                                                                |
| ----------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Andrew's Algorithm (monotone chain) | ✅ Đúng logic                                                                                                                                                        |
| Shoelace (diện tích)                | ✅ Có                                                                                                                                                                |
| **Dùng `<complex>` như slide dạy**  | ❌ **HOÀN TOÀN THIẾU** — Slide trang 4-9 dạy dùng `complex<double>` để biểu diễn điểm và tính cross product bằng `conj()`. Code hiện tại dùng `struct Diem` thủ công |
| Cross product bằng `conj()`         | ❌ Thiếu _(Chap 3, Slide 8-9)_                                                                                                                                       |
| Point in Polygon (ray casting)      | ❌ Code dùng cross product, không dùng ray casting như slide _(Slide 16-17)_                                                                                         |
| Distance point-to-line              | ❌ Thiếu _(Slide 14-15)_                                                                                                                                             |

## 2.4 — Chap 4 (Optimization) — **thiếu ~50%**

| Kiến thức trong Slide              | Trạng thái trong Code                            |
| ---------------------------------- | ------------------------------------------------ |
| Gradient Descent (1 biến)          | ✅ `C4_GD.cpp`                                   |
| GD + Momentum (1 biến, nhiều biến) | ✅ Đủ                                            |
| Simplex 1/2 pha                    | ✅ Đủ                                            |
| **Golden Section Search**          | ❌ **HOÀN TOÀN THIẾU** _(Chap 4, Slide 123-128)_ |
| **Newton's Method**                | ❌ **HOÀN TOÀN THIẾU** _(Chap 4, Slide 130)_     |
| **Lagrange Multipliers**           | ❌ **THIẾU** _(Chap 4, Slide 139-144)_           |
| Nonlinear conjugate gradient       | ❌ Thiếu _(Slide 131)_                           |

**Đề thi yêu cầu "3 phương pháp"** → Hiện tại chỉ có: (1) GD, (2) GD+Momentum → **Thiếu Golden Section Search và Newton's Method.**

## 2.5 — Chap 5 (Probability/Markov) — **thiếu ~45%**

| Kiến thức trong Slide                            | Trạng thái trong Code                          |
| ------------------------------------------------ | ---------------------------------------------- |
| Markov Chain matrix P                            | ✅ Đủ                                          |
| Matrix power P^n                                 | ✅ `bai5.cpp`                                  |
| Ước lượng P từ chuỗi dữ liệu                     | ✅ `markov_final_order.cpp`                    |
| **Laplace smoothing (Bayesian estimate)**        | ❌ **HOÀN TOÀN THIẾU** _(Chap 5, Slide 90-92)_ |
| **Phân phối dừng (stationary distribution)**     | ❌ **THIẾU** _(Slide 85)_                      |
| Phân phối xác suất (Binomial, Normal, Geometric) | ❌ Thiếu _(Slide 41-50)_                       |
| Expected value                                   | ❌ Thiếu _(Slide 22-26)_                       |

---

# 🛠️ BƯỚC 3: MÃ NGUỒN BỔ SUNG (CHỈ BÙ LỖ HỔNG)

---

### 📄 File 1/4: `number_theory_extras.cpp`

> **Chỉ dẫn:** Tạo file mới tên `Chuong1/number_theory_extras.cpp`. Đây là chương trình độc lập bổ sung **Euler's Totient, Modular Inverse, CRT đúng thuật toán** — thay thế hoàn toàn `ThangDuTrungHoa.cpp`.

```cpp
// number_theory_extras.cpp
// Bổ sung: Euler Totient, Modular Inverse, Chinese Remainder Theorem (đúng thuật toán)
// Nguồn lý thuyết: Chap 1, Slide 29 (Totient), 37 (Inverse), 44-45 (CRT)
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// ================================================================
// 1. EULER'S TOTIENT FUNCTION φ(n)
//    φ(n) = n * Π(1 - 1/p) với p là ước nguyên tố của n
//    Nguồn: Chap 1, Slide 29
// ================================================================
ll eulerTotient(ll n) {
    ll result = n;
    for (ll p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0) n /= p;
            result -= result / p;  // result *= (1 - 1/p)
        }
    }
    if (n > 1) result -= result / n;
    return result;
}

// ================================================================
// 2. FAST MODULAR EXPONENTIATION: x^n mod m trong O(log n)
//    Nguồn: Chap 1, Slide 33-34
// ================================================================
ll modPow(ll x, ll n, ll m) {
    ll result = 1;
    x %= m;
    while (n > 0) {
        if (n & 1) result = result * x % m;
        x = x * x % m;
        n >>= 1;
    }
    return result;
}

// ================================================================
// 3. MODULAR INVERSE: x^(-1) mod m
//    Dùng Fermat: x^(-1) = x^(m-2) mod m  (m phải là số nguyên tố)
//    Nguồn: Chap 1, Slide 37 — "x^(-1) = x^(m-2)"
// ================================================================
ll modInverse(ll x, ll m) {
    // Yêu cầu: gcd(x, m) = 1 và m là số nguyên tố
    return modPow(x, m - 2, m);
}

// ================================================================
// 4. EXTENDED EUCLID (dùng nội bộ cho CRT)
//    Tìm x, y sao cho a*x + b*y = gcd(a, b)
//    Nguồn: Chap 1, Slide 27-28, 41-42
// ================================================================
ll extGcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    ll x1, y1;
    ll g = extGcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// ================================================================
// 5. CHINESE REMAINDER THEOREM (CRT) — ĐÚNG THUẬT TOÁN
//    Giải hệ: x ≡ a[i] (mod m[i])  với các m[i] đôi một nguyên tố cùng nhau
//    Công thức: x = Σ (a_k * X_k * X_k^{-1}_{m_k}) mod M
//    Nguồn: Chap 1, Slide 44-45
//    LƯU Ý: Đây là thuật toán O(n·log m) — thay thế brute-force O(∞) trong ThangDuTrungHoa.cpp
// ================================================================
// Tính nghịch đảo của a mod m bằng Extended Euclid (m không cần nguyên tố)
ll modInverseGeneral(ll a, ll m) {
    ll x, y;
    ll g = extGcd(a, m, x, y);
    if (g != 1) return -1; // không tồn tại nghịch đảo
    return (x % m + m) % m;
}

// Trả về nghiệm x (mod M) với M = m[0]*m[1]*...*m[k-1]
// a[i]: số dư, m[i]: modulus (đôi một nguyên tố cùng nhau)
ll chineseRemainderTheorem(vector<ll> a, vector<ll> m) {
    int k = a.size();
    ll M = 1;
    for (ll mi : m) M *= mi;

    ll x = 0;
    for (int i = 0; i < k; i++) {
        ll Xi = M / m[i];                      // X_k = M / m_k
        ll inv = modInverseGeneral(Xi, m[i]);   // X_k^{-1} mod m_k
        x = (x + a[i] % M * Xi % M * inv % M) % M;
    }
    return (x + M) % M;
}

// ================================================================
// MAIN — Demo tất cả
// ================================================================
int main() {
    cout << "=== Euler Totient ===\n";
    // φ(12) = 4 vì {1,5,7,11} coprime với 12  (Slide 29)
    cout << "phi(12) = " << eulerTotient(12) << "  (expected: 4)\n";
    // φ(p) = p-1 nếu p nguyên tố
    cout << "phi(17) = " << eulerTotient(17) << "  (expected: 16)\n\n";

    cout << "=== Modular Exponentiation ===\n";
    // 2^10 mod 1000 = 24  (Slide 33)
    cout << "2^10 mod 1000 = " << modPow(2, 10, 1000) << "  (expected: 24... wait: 1024%1000=24 ✓)\n\n";

    cout << "=== Modular Inverse ===\n";
    // 6^(-1) mod 17 = 3  vì 6*3 mod 17 = 1  (Slide 36-37)
    ll inv = modInverse(6, 17);
    cout << "6^(-1) mod 17 = " << inv << "  (expected: 3)\n";
    cout << "Verify: 6 * " << inv << " mod 17 = " << (6 * inv % 17) << "  (must be 1)\n\n";

    cout << "=== Chinese Remainder Theorem ===\n";
    // Ví dụ từ Slide 45:
    // x ≡ 3 (mod 5), x ≡ 4 (mod 7), x ≡ 2 (mod 3)
    // Expected: x = 263  (mod 105)
    vector<ll> a = {3, 4, 2};
    vector<ll> m = {5, 7, 3};
    ll x = chineseRemainderTheorem(a, m);
    cout << "x = 3 (mod 5), x = 4 (mod 7), x = 2 (mod 3)\n";
    cout << "x = " << x << "  (expected: 263 mod 105 = " << 263 % 105 << ")\n";
    cout << "Verify: " << x << " mod 5=" << x%5
         << ", mod 7=" << x%7 << ", mod 3=" << x%3 << "\n\n";

    // Input từ bàn phím
    cout << "=== Nhap he phuong trinh dong du ===\n";
    int k;
    cout << "So phuong trinh k = ";
    cin >> k;
    vector<ll> av(k), mv(k);
    for (int i = 0; i < k; i++) {
        cout << "a[" << i+1 << "] (so du), m[" << i+1 << "] (modulus): ";
        cin >> av[i] >> mv[i];
    }
    cout << "Nghiem x = " << chineseRemainderTheorem(av, mv) << "\n";
    return 0;
}
```

---

### 📄 File 2/4: `convex_hull.cpp`

> **Chỉ dẫn:** Tạo file mới `Chuong3/convex_hull.cpp`. **File này THAY THẾ `baoloi.cpp`** — dùng đúng `<complex>` như slide dạy (Chap 3, Slide 4-9). Rename `baoloi.cpp` thành `baoloi_old.cpp` để lưu lại.

```cpp
// convex_hull.cpp
// Andrew's Monotone Chain sử dụng <complex> như Chap 3 Slide 4-9 dạy
// Nguồn: Chap 3, Slide 40-45 (Andrew), Slide 4-9 (complex), Slide 19-21 (Shoelace)
#include <bits/stdc++.h>
using namespace std;

// ================================================================
// DÙNG <complex> ĐỂ BIỂU DIỄN ĐIỂM/VECTOR — đúng như Slide 4-5
// typedef: C là kiểu tọa độ, P là kiểu điểm
// ================================================================
typedef long long   C;
typedef complex<C>  P;   // P = (x, y) biểu diễn bằng số phức

// Macro truy cập tọa độ (Slide 5)
#define X real()
#define Y imag()

// ================================================================
// CROSS PRODUCT dùng conj() — ĐÚNG THEO SLIDE
//    cross(a, b) = imag(conj(a) * b) = a.x*b.y - a.y*b.x
//    Nguồn: Chap 3, Slide 8-9
// ================================================================
C crossProduct(P a, P b) {
    return (a.X * b.Y) - (a.Y * b.X);
}

// Cross product của vector OA và OB từ gốc O
C cross(P O, P A, P B) {
    return crossProduct(A - O, B - O);
}

// ================================================================
// ANDREW'S MONOTONE CHAIN — O(n log n)
//    Nguồn: Chap 3, Slide 43-45
//    Bước 1: Sort theo x, rồi y
//    Bước 2: Xây lower hull (trái → phải, loại khi cross <= 0)
//    Bước 3: Xây upper hull (phải → trái, loại khi cross <= 0)
// ================================================================
vector<P> computeConvexHull(vector<P> pts) {
    int n = pts.size();
    if (n < 2) return pts;

    // Bước 1: Sort (Slide 44)
    sort(pts.begin(), pts.end(), [](const P& a, const P& b) {
        return a.X < b.X || (a.X == b.X && a.Y < b.Y);
    });

    vector<P> hull;

    // Bước 2: Lower hull — đi trái → phải (Slide 44)
    for (int i = 0; i < n; i++) {
        while (hull.size() >= 2 &&
               cross(hull[hull.size()-2], hull[hull.size()-1], pts[i]) <= 0)
            hull.pop_back();
        hull.push_back(pts[i]);
    }

    // Bước 3: Upper hull — đi phải → trái (Slide 44)
    int lower_size = hull.size() + 1;
    for (int i = n - 2; i >= 0; i--) {
        while ((int)hull.size() >= lower_size &&
               cross(hull[hull.size()-2], hull[hull.size()-1], pts[i]) <= 0)
            hull.pop_back();
        hull.push_back(pts[i]);
    }

    hull.pop_back(); // Bỏ điểm cuối (trùng điểm đầu)
    return hull;     // Thứ tự CCW (ngược chiều kim đồng hồ)
}

// ================================================================
// SHOELACE FORMULA — Diện tích đa giác
//    Area = (1/2) |Σ p_i × p_{i+1}|
//    Nguồn: Chap 3, Slide 19-21
// ================================================================
double computeArea(const vector<P>& hull) {
    double area = 0;
    int n = hull.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += (double)hull[i].X * hull[j].Y;
        area -= (double)hull[j].X * hull[i].Y;
    }
    return fabs(area) / 2.0;
}

// ================================================================
// CHU VI BAO LỒI
// ================================================================
double computePerimeter(const vector<P>& hull) {
    double perim = 0;
    int n = hull.size();
    for (int i = 0; i < n; i++) {
        P d = hull[(i+1)%n] - hull[i];
        perim += sqrt((double)(d.X*d.X + d.Y*d.Y));
    }
    return perim;
}

// ================================================================
// KHOẢNG CÁCH ĐIỂM ĐẾN ĐƯỜNG THẲNG
//    d = |(s1 - p) × (s2 - p)| / |s2 - s1|
//    Nguồn: Chap 3, Slide 14-15
// ================================================================
double pointToLineDistance(P s1, P s2, P p) {
    C cp = crossProduct(s1 - p, s2 - p);
    P diff = s2 - s1;
    double len = sqrt((double)(diff.X*diff.X + diff.Y*diff.Y));
    return fabs((double)cp) / len;
}

// ================================================================
// KIỂM TRA ĐIỂM TRONG ĐA GIÁC LỒI (dùng cross product)
//    Nguồn: Chap 3, Slide 16-17 (ray casting concept)
// ================================================================
bool isInsideConvexPolygon(const vector<P>& hull, P p) {
    int n = hull.size();
    for (int i = 0; i < n; i++) {
        if (cross(hull[i], hull[(i+1)%n], p) < 0) return false;
    }
    return true;
}

// ================================================================
// TÌM CẶP ĐIỂM GẦN NHẤT / XA NHẤT TRÊN BAO LỒI
// ================================================================
pair<int,int> findClosestPair(const vector<P>& hull) {
    int n = hull.size();
    pair<int,int> result = {0, 1};
    double minDist = 1e18;
    for (int i = 0; i < n; i++)
        for (int j = i+1; j < n; j++) {
            P d = hull[j] - hull[i];
            double dist = sqrt((double)(d.X*d.X + d.Y*d.Y));
            if (dist < minDist) { minDist = dist; result = {i, j}; }
        }
    return result;
}

pair<int,int> findFarthestPair(const vector<P>& hull) {
    int n = hull.size();
    pair<int,int> result = {0, 1};
    double maxDist = -1;
    for (int i = 0; i < n; i++)
        for (int j = i+1; j < n; j++) {
            P d = hull[j] - hull[i];
            double dist = sqrt((double)(d.X*d.X + d.Y*d.Y));
            if (dist > maxDist) { maxDist = dist; result = {i, j}; }
        }
    return result;
}

// ================================================================
// MAIN
// ================================================================
int main() {
    int n;
    cout << "Nhap so luong diem: ";
    cin >> n;

    vector<P> points(n);
    cout << "Nhap toa do cac diem (x y):\n";
    for (int i = 0; i < n; i++) {
        C x, y; cin >> x >> y;
        points[i] = P(x, y);
    }

    // Lưu điểm gốc để kiểm tra "trong bao lồi"
    vector<P> original_pts = points;

    // Tính bao lồi (Andrew's algorithm)
    vector<P> hull = computeConvexHull(points);

    cout << "\nCac dinh bao loi (thu tu CCW, " << hull.size() << " dinh):\n";
    for (auto& p : hull)
        cout << "  (" << p.X << ", " << p.Y << ")\n";

    cout << fixed << setprecision(4);
    cout << "\nDien tich = " << computeArea(hull) << "\n";
    cout << "Chu vi    = " << computePerimeter(hull) << "\n";

    // Cặp gần nhất / xa nhất
    if (hull.size() >= 2) {
        auto [ci, cj] = findClosestPair(hull);
        P dc = hull[cj] - hull[ci];
        cout << "\nCap gan nhat: (" << hull[ci].X << "," << hull[ci].Y << ") - ("
             << hull[cj].X << "," << hull[cj].Y << ")"
             << "  dist=" << sqrt((double)(dc.X*dc.X+dc.Y*dc.Y)) << "\n";

        auto [fi, fj] = findFarthestPair(hull);
        P df = hull[fj] - hull[fi];
        cout << "Cap xa nhat:  (" << hull[fi].X << "," << hull[fi].Y << ") - ("
             << hull[fj].X << "," << hull[fj].Y << ")"
             << "  dist=" << sqrt((double)(df.X*df.X+df.Y*df.Y)) << "\n";
    }

    // Kiểm tra các điểm gốc nằm trong/ngoài bao lồi
    cout << "\nKiem tra diem trong/ngoai bao loi:\n";
    for (auto& p : original_pts) {
        bool inside = isInsideConvexPolygon(hull, p);
        cout << "  (" << p.X << "," << p.Y << ") -> "
             << (inside ? "BEN TRONG" : "BEN NGOAI") << "\n";
    }

    return 0;
}
```

---

### 📄 File 3/4: `optimization_methods.cpp`

> **Chỉ dẫn:** Tạo file mới `Chuong4/optimization_methods.cpp`. Đây là file **bổ sung 2 phương pháp còn thiếu**: Golden Section Search và Newton's Method (cả 1 biến lẫn nhiều biến). \__Chèn vào cùng thư mục với các file C4_GD_.cpp.\_\*

```cpp
// optimization_methods.cpp
// Bổ sung phương pháp 2 và 3 còn thiếu:
//   (2) Golden Section Search   — Nguồn: Chap 4, Slide 123-128
//   (3) Newton's Method         — Nguồn: Chap 4, Slide 130-132
// + Lagrange Multiplier minh họa — Nguồn: Chap 4, Slide 139-144
#include <bits/stdc++.h>
using namespace std;

// ================================================================
// PHƯƠNG PHÁP 2: GOLDEN SECTION SEARCH
//    Tìm cực tiểu của hàm unimodal f trên [a, b]
//    Nguồn: Chap 4, Slide 123-128
//    Tỉ lệ vàng: φ = (√5 - 1) / 2 ≈ 0.618
//    Mỗi bước thu hẹp khoảng theo tỉ lệ φ, không cần đạo hàm
// ================================================================
const double GOLDEN_RATIO = (sqrt(5.0) - 1.0) / 2.0;  // ≈ 0.618

// f: hàm unimodal cần tìm cực tiểu (truyền bằng function pointer/lambda)
// [lo, hi]: khoảng tìm kiếm
// tol: độ chính xác mong muốn
double goldenSectionSearch(function<double(double)> f,
                           double lo, double hi,
                           double tol = 1e-8, int maxIter = 200) {
    // x1, x2 là 2 điểm kiểm tra bên trong [lo, hi]
    double x1 = hi - GOLDEN_RATIO * (hi - lo);
    double x2 = lo + GOLDEN_RATIO * (hi - lo);
    double f1 = f(x1), f2 = f(x2);

    printf("  [GoldenSection] Initial: [%.6f, %.6f]\n", lo, hi);

    for (int iter = 0; iter < maxIter && (hi - lo) > tol; iter++) {
        // Thu hẹp khoảng: giữ lại phía chứa cực tiểu
        if (f1 < f2) {
            // Cực tiểu nằm trong [lo, x2]
            hi = x2;
            x2 = x1; f2 = f1;
            x1 = hi - GOLDEN_RATIO * (hi - lo);
            f1 = f(x1);
        } else {
            // Cực tiểu nằm trong [x1, hi]
            lo = x1;
            x1 = x2; f1 = f2;
            x2 = lo + GOLDEN_RATIO * (hi - lo);
            f2 = f(x2);
        }
        if (iter % 20 == 0)
            printf("  Iter %3d: [%.8f, %.8f]  width=%.2e\n", iter, lo, hi, hi-lo);
    }
    double xmin = (lo + hi) / 2.0;
    printf("  => x* = %.8f,  f(x*) = %.8f\n\n", xmin, f(xmin));
    return xmin;
}

// ================================================================
// PHƯƠNG PHÁP 3: NEWTON'S METHOD — 1 BIẾN
//    x_{n+1} = x_n - f'(x_n) / f''(x_n)
//    Hội tụ bậc 2 (rất nhanh)
//    Nguồn: Chap 4, Slide 130
// ================================================================
// Đạo hàm xấp xỉ bậc 1 (sai phân tiến)
double numericalDeriv1(function<double(double)> f, double x, double h = 1e-6) {
    return (f(x + h) - f(x)) / h;
}
// Đạo hàm xấp xỉ bậc 2
double numericalDeriv2(function<double(double)> f, double x, double h = 1e-5) {
    return (f(x + h) - 2*f(x) + f(x - h)) / (h * h);
}

double newtonMethod1D(function<double(double)> f,
                      double x0, double tol = 1e-8, int maxIter = 100) {
    double x = x0;
    printf("  [Newton 1D] x0 = %.6f\n", x0);
    for (int i = 0; i < maxIter; i++) {
        double g  = numericalDeriv1(f, x);   // f'(x)
        double g2 = numericalDeriv2(f, x);   // f''(x)
        if (fabs(g2) < 1e-14) { printf("  f''=0, Newton diverges!\n"); break; }
        double dx = g / g2;                   // Newton step
        x -= dx;
        if (i % 10 == 0)
            printf("  Iter %3d: x=%.8f  f=%.8f  |f'|=%.2e\n", i, x, f(x), fabs(g));
        if (fabs(g) < tol) break;
    }
    printf("  => x* = %.8f,  f(x*) = %.8f\n\n", x, f(x));
    return x;
}

// ================================================================
// PHƯƠNG PHÁP 3: NEWTON'S METHOD — 2 BIẾN (dùng Hessian)
//    [x_{n+1}] = [x_n] - H^{-1} * ∇f
//    H = [[f_xx, f_xy], [f_yx, f_yy]]  (ma trận Hessian)
//    Nguồn: Chap 4, Slide 130 + Slide 112-122 (Hessian)
// ================================================================
double numericalPartial(function<double(double,double)> f,
                        double x, double y, int var, double h = 1e-5) {
    if (var == 0) return (f(x+h, y) - f(x-h, y)) / (2*h);
    else          return (f(x, y+h) - f(x, y-h)) / (2*h);
}
double numericalPartial2(function<double(double,double)> f,
                         double x, double y, int i, int j, double h = 1e-4) {
    // ∂²f/∂xi∂xj bằng sai phân hỗn hợp
    double dx = (i == 0 ? h : 0), dy = (i == 1 ? h : 0);
    double ex = (j == 0 ? h : 0), ey = (j == 1 ? h : 0);
    return (f(x+dx+ex, y+dy+ey) - f(x+dx-ex, y+dy-ey)
           -f(x-dx+ex, y-dy+ey) + f(x-dx-ex, y-dy-ey)) / (4*h*h);
}

void newtonMethod2D(function<double(double,double)> f,
                    double x0, double y0,
                    double tol = 1e-8, int maxIter = 100) {
    double x = x0, y = y0;
    printf("  [Newton 2D] (x0,y0) = (%.4f, %.4f)\n", x0, y0);
    for (int i = 0; i < maxIter; i++) {
        double gx = numericalPartial(f, x, y, 0);  // ∂f/∂x
        double gy = numericalPartial(f, x, y, 1);  // ∂f/∂y
        double norm = sqrt(gx*gx + gy*gy);
        if (i % 5 == 0)
            printf("  Iter %3d: (%.6f,%.6f) f=%.6f |grad|=%.2e\n",
                   i, x, y, f(x,y), norm);
        if (norm < tol) break;

        // Hessian 2x2
        double h11 = numericalPartial2(f, x, y, 0, 0); // f_xx
        double h12 = numericalPartial2(f, x, y, 0, 1); // f_xy
        double h21 = h12;                                // f_yx = f_xy
        double h22 = numericalPartial2(f, x, y, 1, 1); // f_yy
        double det = h11*h22 - h12*h21;
        if (fabs(det) < 1e-14) { printf("  Hessian singular!\n"); break; }

        // H^{-1} * g = (1/det) * [[h22,-h12],[-h21,h11]] * [gx,gy]
        double dx = -(h22*gx - h12*gy) / det;
        double dy = -(-h21*gx + h11*gy) / det;
        x += dx; y += dy;
    }
    printf("  => x*=(%.8f, %.8f)  f*=%.8f\n\n", x, y, f(x,y));
}

// ================================================================
// PHƯƠNG PHÁP 3: NEWTON — 3 BIẾN
//    Mở rộng tương tự cho hàm f(x, y, z)
//    Nguồn: Chap 4, Slide 119-122
// ================================================================
void newtonMethod3D(function<double(double,double,double)> f,
                    double x0, double y0, double z0,
                    double tol = 1e-8, int maxIter = 100) {
    double x = x0, y = y0, z = z0;
    double h = 1e-5;
    printf("  [Newton 3D] (x0,y0,z0) = (%.4f,%.4f,%.4f)\n", x0, y0, z0);
    for (int iter = 0; iter < maxIter; iter++) {
        // Gradient (xấp xỉ sai phân)
        double gx = (f(x+h,y,z) - f(x-h,y,z)) / (2*h);
        double gy = (f(x,y+h,z) - f(x,y-h,z)) / (2*h);
        double gz = (f(x,y,z+h) - f(x,y,z-h)) / (2*h);
        double norm = sqrt(gx*gx + gy*gy + gz*gz);

        if (iter % 10 == 0)
            printf("  Iter %3d: (%.5f,%.5f,%.5f) f=%.6f |g|=%.2e\n",
                   iter, x, y, z, f(x,y,z), norm);
        if (norm < tol) break;

        // Hessian 3x3 (xấp xỉ đường chéo chính để đơn giản hóa — Quasi-Newton)
        double hxx = (f(x+h,y,z)-2*f(x,y,z)+f(x-h,y,z))/(h*h);
        double hyy = (f(x,y+h,z)-2*f(x,y,z)+f(x,y-h,z))/(h*h);
        double hzz = (f(x,y,z+h)-2*f(x,y,z)+f(x,y,z-h))/(h*h);

        // Chỉ dùng đường chéo Hessian (diagonal Newton step)
        if (fabs(hxx) > 1e-14) x -= gx / hxx;
        if (fabs(hyy) > 1e-14) y -= gy / hyy;
        if (fabs(hzz) > 1e-14) z -= gz / hzz;
    }
    printf("  => (x*,y*,z*)=(%.8f,%.8f,%.8f)  f*=%.8f\n\n",
           x, y, z, f(x,y,z));
}

// ================================================================
// LAGRANGE MULTIPLIER — Ví dụ từ slide
//    max f(x1,x2) = 2x1 + x2 + 10
//    s.t. g(x1,x2) = x1^2 + 2x2^2 = 3
//    Nguồn: Chap 4, Slide 143-144
// ================================================================
void lagrangeExample() {
    cout << "=== Lagrange Multiplier (Slide 143-144) ===\n";
    cout << "max f = 2x1 + x2 + 10,  s.t. x1^2 + 2x2^2 = 3\n";
    // Từ dL/dx1=0: 2 - 2λx1 = 0 => x1 = 1/λ
    // Từ dL/dx2=0: 1 - 4λx2 = 0 => x2 = 1/(4λ)
    // Ràng buộc: x1^2 + 2x2^2 = 3 => 1/λ^2 + 2/(16λ^2) = 3 => 18/(16λ^2) = 3
    // => λ^2 = 18/48 = 3/8 => λ = sqrt(3/8)
    // => x1 = sqrt(8/3), x2 = sqrt(8/3)/4 = sqrt(1/6)
    double lam = sqrt(3.0/8.0);
    double x1  = 1.0 / lam;
    double x2  = 1.0 / (4.0 * lam);
    double fval = 2*x1 + x2 + 10;
    printf("  lambda* = %.6f\n", lam);
    printf("  x1* = %.6f,  x2* = %.6f\n", x1, x2);
    printf("  f*  = %.6f\n", fval);
    printf("  Kiem tra rang buoc: x1^2 + 2x2^2 = %.6f (should be 3)\n\n",
           x1*x1 + 2*x2*x2);
}

// ================================================================
// MAIN — Demo tất cả
// ================================================================
int main() {
    cout << "============================================================\n";
    cout << " OPTIMIZATION METHODS — Chap 4 Demo\n";
    cout << "============================================================\n\n";

    // ---- Hàm 1 biến: g(t) = t^4 - 14t^3 + 60t^2 - 70t
    //      Cực tiểu tại t ≈ 0.92 trong [0, 2]
    auto g1 = [](double t) {
        return t*t*t*t - 14*t*t*t + 60*t*t - 70*t;
    };

    cout << "--- Ham 1 bien: g(t) = t^4 - 14t^3 + 60t^2 - 70t ---\n\n";

    cout << "[Phuong phap 2] Golden Section Search  (Slide 123-128):\n";
    goldenSectionSearch(g1, 0.0, 2.0);

    cout << "[Phuong phap 3] Newton's Method 1D  (Slide 130):\n";
    newtonMethod1D(g1, 0.5);

    // ---- Hàm 2 biến: f(x,y) = (x-2)^2 + 2*(y-3)^2 + x*y
    //      Cực tiểu gần (x≈1.6, y≈2.6)
    cout << "--- Ham 2 bien: f(x,y) = (x-2)^2 + 2*(y-3)^2 + x*y ---\n\n";
    auto f2 = [](double x, double y) {
        return (x-2)*(x-2) + 2*(y-3)*(y-3) + x*y;
    };

    cout << "[Phuong phap 3] Newton's Method 2D  (Slide 130, 112-122):\n";
    newtonMethod2D(f2, 0.0, 0.0);

    // ---- Hàm 3 biến: h(x,y,z) = (x-1)^2 + (y-2)^2 + (z-3)^2
    //      Cực tiểu tại (1, 2, 3)
    cout << "--- Ham 3 bien: h(x,y,z) = (x-1)^2 + (y-2)^2 + (z-3)^2 ---\n\n";
    auto f3 = [](double x, double y, double z) {
        return (x-1)*(x-1) + (y-2)*(y-2) + (z-3)*(z-3);
    };

    cout << "[Phuong phap 3] Newton's Method 3D  (Slide 119-122):\n";
    newtonMethod3D(f3, 0.0, 0.0, 0.0);

    // ---- Lagrange
    lagrangeExample();

    return 0;
}
```

---

### 📄 File 4/4: `markov_laplace.cpp`

> **Chỉ dẫn:** Tạo file mới `Chuong5/markov_laplace.cpp`. **Bổ sung** phần Laplace smoothing và tính phân phối dừng còn thiếu trong `markov_modular.cpp`.

```cpp
// markov_laplace.cpp
// Bổ sung 2 phần thiếu trong markov_modular.cpp:
//   (1) Laplace Smoothing (Bayesian estimate)  — Nguồn: Chap 5, Slide 90-92
//   (2) Stationary Distribution                — Nguồn: Chap 5, Slide 85
#include <bits/stdc++.h>
using namespace std;
typedef vector<vector<double>> Matrix;
typedef vector<double> Vec;

// ================================================================
// 1. XÂY DỰNG MA TRẬN MARKOV VỚI LAPLACE SMOOTHING
//    Thay vì P[i][j] = count(i->j) / count(i)  (MLE thuần túy)
//    Dùng:  P[i][j] = (count(i->j) + alpha) / (count(i) + alpha*m)
//    alpha = 1: Laplace estimate (add-one smoothing)
//    Tránh chia cho 0 và xác suất bằng 0 khi không đủ dữ liệu
//    Nguồn: Chap 5, Slide 90-92 (Bayesian Approach)
// ================================================================
Matrix buildMarkovWithLaplace(const vector<int>& sequence, int numStates,
                              double alpha = 1.0) {
    int m = numStates;
    // Đếm số lần chuyển i -> j
    Matrix count(m, Vec(m, 0.0));
    Vec rowSum(m, 0.0);

    for (int t = 0; t + 1 < (int)sequence.size(); t++) {
        int i = sequence[t], j = sequence[t+1];
        count[i][j]++;
        rowSum[i]++;
    }

    // Laplace smoothing: P[i][j] = (count[i][j] + alpha) / (rowSum[i] + alpha*m)
    Matrix P(m, Vec(m, 0.0));
    for (int i = 0; i < m; i++) {
        double denom = rowSum[i] + alpha * m;
        for (int j = 0; j < m; j++)
            P[i][j] = (count[i][j] + alpha) / denom;
    }
    return P;
}

// ================================================================
// 2. STATIONARY DISTRIBUTION (Phân phối dừng)
//    π = lim_{n→∞} v₀ · P^n
//    Cách tính: lặp π_new = π_old · P cho đến hội tụ
//    Thỏa mãn: π = π · P và Σπ_i = 1
//    Nguồn: Chap 5, Slide 85 — "[0.2, 0.44, 0.36] is called the stationary distribution"
// ================================================================
Vec computeStationaryDistribution(const Matrix& P, int maxIter = 10000,
                                  double tol = 1e-10) {
    int m = P.size();
    // Khởi tạo phân phối đều
    Vec pi(m, 1.0 / m);

    for (int iter = 0; iter < maxIter; iter++) {
        Vec pi_new(m, 0.0);
        // π_new[j] = Σ_i π[i] * P[i][j]
        for (int i = 0; i < m; i++)
            for (int j = 0; j < m; j++)
                pi_new[j] += pi[i] * P[i][j];

        // Kiểm tra hội tụ
        double diff = 0.0;
        for (int i = 0; i < m; i++) diff += fabs(pi_new[i] - pi[i]);
        pi = pi_new;
        if (diff < tol) {
            printf("  [Stationary] Converged after %d iterations (diff=%.2e)\n\n", iter, diff);
            break;
        }
    }
    return pi;
}

// ================================================================
// 3. TÍNH XÁC SUẤT SAU n BƯỚC: v(t+n) = v(t) · P^n
//    Nguồn: Chap 5, Slide 70-76
// ================================================================
Matrix matrixMultiply(const Matrix& A, const Matrix& B) {
    int n = A.size(), m = B[0].size(), k = B.size();
    Matrix C(n, Vec(m, 0.0));
    for (int i = 0; i < n; i++)
        for (int l = 0; l < k; l++)
            for (int j = 0; j < m; j++)
                C[i][j] += A[i][l] * B[l][j];
    return C;
}

Matrix matrixPower(Matrix P, int n) {
    int m = P.size();
    Matrix result(m, Vec(m, 0.0));
    for (int i = 0; i < m; i++) result[i][i] = 1.0; // Identity
    while (n > 0) {
        if (n & 1) result = matrixMultiply(result, P);
        P = matrixMultiply(P, P);
        n >>= 1;
    }
    return result;
}

Vec multiplyVecMatrix(const Vec& v, const Matrix& P) {
    int m = P.size();
    Vec result(m, 0.0);
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++)
            result[j] += v[i] * P[i][j];
    return result;
}

// ================================================================
// MAIN — Demo với ví dụ thời tiết từ Slide 81-85
// ================================================================
int main() {
    cout << fixed << setprecision(4);
    cout << "=== MARKOV CHAIN + LAPLACE SMOOTHING (Chap 5) ===\n\n";

    // --- Ví dụ 1: Ma trận thời tiết từ Slide 81-85
    //    States: 0=Nice, 1=Rainy, 2=Snowy
    int m = 3;
    vector<string> states = {"Nice", "Rainy", "Snowy"};
    // Dữ liệu chuỗi quan sát: [0,1,2,1,0,0,1,2,2,1,0,...]
    vector<int> seq = {0,1,2,1,0,0,1,2,2,1,0,1,2,0,1,1,2,0};

    // --- Phần 1: Ước lượng MLE thông thường
    cout << "--- MLE Thong thuong (alpha=0) ---\n";
    Matrix P_mle = buildMarkovWithLaplace(seq, m, 0.0);
    for (int i = 0; i < m; i++) {
        cout << "  " << states[i] << ": ";
        for (int j = 0; j < m; j++)
            printf("P(%s|%s)=%.4f  ", states[j].c_str(), states[i].c_str(), P_mle[i][j]);
        cout << "\n";
    }

    // --- Phần 2: Ước lượng Laplace (alpha=1)
    //    Nguồn: Slide 90 — "Laplace estimates: na+1 / Σni+1"
    cout << "\n--- Laplace Smoothing (alpha=1.0) (Slide 90-92) ---\n";
    Matrix P_lap = buildMarkovWithLaplace(seq, m, 1.0);
    cout << setw(8) << " ";
    for (int j = 0; j < m; j++) cout << setw(8) << states[j];
    cout << "\n";
    for (int i = 0; i < m; i++) {
        cout << setw(8) << states[i];
        for (int j = 0; j < m; j++) printf("  %.4f", P_lap[i][j]);
        cout << "\n";
    }

    // --- Phần 3: Stationary distribution
    //    Nguồn: Slide 85 — "The row [0.2 0.44 0.36] is called the stationary distribution"
    cout << "\n--- Stationary Distribution (Slide 85) ---\n";
    // Dùng ma trận slide gốc để so sánh
    Matrix P_slide = {
        {0.00, 0.75, 0.25},   // Nice -> Rainy 75%, Snowy 25%
        {0.25, 0.25, 0.50},   // Rainy
        {0.25, 0.50, 0.25}    // Snowy
    };
    Vec pi = computeStationaryDistribution(P_slide);
    cout << "  Phan phoi dung: ";
    for (int i = 0; i < m; i++)
        printf("%s=%.4f  ", states[i].c_str(), pi[i]);
    cout << "\n  (Slide ghi: [0.2, 0.44, 0.36])\n";

    // Xác minh: π = π · P
    Vec check = multiplyVecMatrix(pi, P_slide);
    cout << "  Verify pi*P: ";
    for (int i = 0; i < m; i++) printf("%.4f  ", check[i]);
    cout << "\n\n";

    // --- Phần 4: Xác suất sau n bước
    cout << "--- Xac suat sau n buoc (Slide 70-76) ---\n";
    Vec v0 = {1.0, 0.0, 0.0}; // Bắt đầu từ Nice
    int n_steps = 20;
    Matrix Pn = matrixPower(P_slide, n_steps);
    Vec vn = multiplyVecMatrix(v0, Pn);
    printf("  Sau %d buoc (bat dau Nice): ", n_steps);
    for (int i = 0; i < m; i++) printf("%s=%.4f  ", states[i].c_str(), vn[i]);
    cout << "\n  (Ket qua rat gan voi phan phoi dung)\n\n";

    // --- Phần 5: Input từ bàn phím (dùng Laplace)
    cout << "=== INPUT BANG PHIM (Laplace Smoothing) ===\n";
    int numStates;
    cout << "Nhap so trang thai: "; cin >> numStates;
    int seqLen;
    cout << "Nhap do dai chuoi quan sat: "; cin >> seqLen;
    vector<int> userSeq(seqLen);
    cout << "Nhap chuoi (trang thai 0.." << numStates-1 << "): ";
    for (int& s : userSeq) cin >> s;
    double alpha;
    cout << "Nhap he so Laplace alpha (1.0 = standard Laplace): "; cin >> alpha;

    Matrix P_user = buildMarkovWithLaplace(userSeq, numStates, alpha);
    cout << "\nMa tran P (Laplace alpha=" << alpha << "):\n";
    for (int i = 0; i < numStates; i++) {
        printf("  State %d: ", i);
        for (int j = 0; j < numStates; j++) printf("%.4f  ", P_user[i][j]);
        cout << "\n";
    }

    Vec pi_user = computeStationaryDistribution(P_user);
    cout << "Phan phoi dung: ";
    for (int i = 0; i < numStates; i++) printf("%.4f  ", pi_user[i]);
    cout << "\n";

    return 0;
}
```

---

# 📚 BƯỚC 4: TỔNG HỢP NỘI DUNG ÔN TẬP (CÓ TRÍCH DẪN SLIDE)

---

## 📌 Câu 1 — Lý thuyết Số

- **Số nguyên tố & phân tích thừa số:** n = p₁^α₁·…·pₖ^αₖ → τ(n)=∏(αᵢ+1), σ(n)=∏(pᵢ^(αᵢ+1)-1)/(pᵢ-1) — _Nguồn: Chap 1, Slide 9-12_
- **Sàng Eratosthenes** O(n log log n): Đánh dấu bội của mỗi số nguyên tố — _Nguồn: Chap 1, Slide 21-23_
- **Euclid GCD** O(log n): `gcd(a,b) = gcd(b, a%b)` — _Nguồn: Chap 1, Slide 26-28_
- **LCM:** `lcm(a,b) = a*b/gcd(a,b)` — _Nguồn: Chap 1, Slide 26_
- **Euler's Totient φ(n):** `φ(n) = n·∏(1 - 1/pᵢ)`, φ(p) = p-1 — _Nguồn: Chap 1, Slide 29_
- **Modular Exponentiation** O(log n): chia đôi số mũ — _Nguồn: Chap 1, Slide 33-34_
- **Modular Inverse:** x⁻¹ = x^(m-2) mod m (Fermat, m nguyên tố) — _Nguồn: Chap 1, Slide 36-37_
- **Extended Euclid + Diophantine ax+by=c:** Giải được ⟺ gcd(a,b)|c — _Nguồn: Chap 1, Slide 41-43_
- **CRT:** x ≡ aᵢ (mod mᵢ) → x = Σ aₖ·Xₖ·(Xₖ⁻¹ mod mₖ) với M = ∏mᵢ — _Nguồn: Chap 1, Slide 44-45_
- **Wilson's Theorem:** n nguyên tố ⟺ (n-1)! mod n = n-1 — _Nguồn: Chap 1, Slide 49_

---

## 📌 Câu 2 — Trị riêng / Vector riêng

- **Định nghĩa:** Ax = λx (x ≠ 0) — _Nguồn: Chap 2, Slide 27_
- **3 bước tính:** (1) Đa thức đặc trưng det(A-λI)=0, (2) Giải ra λ, (3) Giải (A-λI)x=0 — _Nguồn: Chap 2, Slide 28_
- **Eigenspace Eλ:** Tập nghiệm của (A-λI)x=0 — _Nguồn: Chap 2, Slide 29_
- **Jacobi Method** (ma trận đối xứng): xoay Q^T·A·Q lặp đến ma trận chéo — _Nguồn: Chap 2, Slide 35 (code bai3.cpp)_
- **Eigendecomposition:** A = PDP⁻¹, P là ma trận eigenvectors, D = diag(λᵢ) — _Nguồn: Chap 2, Slide 55-58_
- **Công thức nhanh:** det(A) = ∏λᵢ, trace(A) = ∑λᵢ, A^k = PD^kP⁻¹ — _Nguồn: Chap 2, Slide 58_
- **Cholesky A = LL^T:** Chỉ khi A đối xứng xác định dương — _Nguồn: Chap 2, Slide 37-49_
- **SVD A = UΣV^T:** σᵢ = √(eigenvalues của A^TA), luôn tồn tại cho mọi A — _Nguồn: Chap 2, Slide 61-74_

---

## 📌 Câu 3 — Bao lồi (Convex Hull)

- **`<complex>` biểu diễn điểm:** `typedef complex<double> P`, dùng `real()`, `imag()` — _Nguồn: Chap 3, Slide 4-6_
- **Cross product bằng conj():** `imag(conj(a)*b)` = a.x·b.y - a.y·b.x — _Nguồn: Chap 3, Slide 8-9_
- **Andrew's Algorithm O(n log n):** Sort → Lower hull → Upper hull. Loại điểm khi cross ≤ 0 — _Nguồn: Chap 3, Slide 43-45_
- **Shoelace formula:** Area = ½|Σ(xᵢyᵢ₊₁ - xᵢ₊₁yᵢ)| — _Nguồn: Chap 3, Slide 19-21_
- **Pick's Theorem:** Area = a + b/2 - 1 (a: điểm nguyên trong, b: trên biên) — _Nguồn: Chap 3, Slide 22_
- **Khoảng cách điểm-đường:** d = |(s₁-p)×(s₂-p)| / |s₂-s₁| — _Nguồn: Chap 3, Slide 14-15_
- **Điểm trong đa giác:** Ray casting (đếm số lần tia giao biên) — _Nguồn: Chap 3, Slide 16-17_

---

## 📌 Câu 4 — Tối ưu hóa (3 Phương pháp)

- **Phương pháp 1 — Gradient Descent:** xᵢ₊₁ = xᵢ - γ·∇f(xᵢ)^T — _Nguồn: Chap 4, Slide 6-9_
- **GD + Momentum:** Δxᵢ = α·Δxᵢ₋₁ + γ·∇f(xᵢ), α∈[0,1] — _Nguồn: Chap 4, Slide 13-14_
- **Phương pháp 2 — Golden Section Search:** φ=(√5-1)/2 ≈ 0.618, thu hẹp khoảng theo tỉ lệ vàng, chỉ dùng cho hàm unimodal — _Nguồn: Chap 4, Slide 123-128_
- **Phương pháp 3 — Newton's Method:** Δx = -H⁻¹∇f (H là Hessian), hội tụ bậc 2 — _Nguồn: Chap 4, Slide 130_
- **Hessian & điều kiện đủ:** H > 0 → cực tiểu; H < 0 → cực đại; mixed sign → saddle point — _Nguồn: Chap 4, Slide 112-122_
- **Lagrange Multiplier:** L(x,λ) = f(x) + Σλᵢ(bᵢ - gᵢ(x)), đặt ∂L/∂xᵢ=0 và ∂L/∂λⱼ=0 — _Nguồn: Chap 4, Slide 139-144_
- **Simplex Method (1 pha & 2 pha):** Tableau + Pivot — _Nguồn: Chap 4, Slide 36-53_

---

## 📌 Câu 5 — Xác suất & Markov

- **Xác suất cơ bản:** P(Ā)=1-P(A), P(A∪B)=P(A)+P(B)-P(A∩B), P(A|B)=P(A∩B)/P(B) — _Nguồn: Chap 5, Slide 12-18_
- **E[X] = Σx·P(X=x)**, Linearity: E[X+Y]=E[X]+E[Y] — _Nguồn: Chap 5, Slide 22-26_
- **Binomial Bin(n,p):** P(X=k)=C(n,k)pᵏ(1-p)^(n-k), E=np, Var=np(1-p) — _Nguồn: Chap 5, Slide 41-43_
- **Geometric:** P(X=k)=(1-p)^(k-1)p, E=1/p — _Nguồn: Chap 5, Slide 49-50_
- **Normal N(μ,σ²) & CLT:** Bin(n,p)→N(np,np(1-p)) khi n lớn — _Nguồn: Chap 5, Slide 28-31_
- **Markov Chain:** Transition matrix P[i][j], π*{t+1} = π_t·P, matrix power P^n — \_Nguồn: Chap 5, Slide 65-76*
- **Stationary distribution π:** π = π·P, Σπᵢ=1 (lặp đến hội tụ) — _Nguồn: Chap 5, Slide 85_
- **MLE ước lượng P:** P[i][j] = count(i→j) / count(i) — _Nguồn: Chap 5, Slide 88-89_
- **Laplace Smoothing:** P[i][j] = (count(i→j)+α) / (count(i)+α·m) — _Nguồn: Chap 5, Slide 90-92_
