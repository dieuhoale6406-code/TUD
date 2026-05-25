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

void buildSieve(int n)
{
    fill(sieve, sieve + n + 1, 0);
    for (int x = 2; x <= n; x++)
    {
        if (sieve[x] == 0)
        {
            for (int u = 2 * x; u <= n; u += x)
            {
                if (sieve[u] == 0)
                    sieve[u] = x;
            }
        }
    }
}

bool isPrime(int n)
{
    if (n < 2)
        return false;
    for (int d = 2; (ll)d * d <= n; d++)
        if (n % d == 0)
            return false;
    return true;
}

vector<int> primeFactors(int n)
{
    vector<int> f;
    for (int d = 2; (ll)d * d <= n; d++)
    {
        while (n % d == 0)
        {
            f.push_back(d);
            n /= d;
        }
    }
    if (n > 1)
        f.push_back(n);
    return f;
}

// ---- 2. Thuật toán Euclid ----------------------------------------
ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }

// ---- 3. Euler Totient Function φ(n) --------------------------------
ll eulerTotient(ll n)
{
    ll result = n;
    for (ll p = 2; p * p <= n; p++)
    {
        if (n % p == 0)
        {
            while (n % p == 0)
                n /= p;
            result -= result / p;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}

// ---- 4. Lũy thừa Modular: x^n mod m trong O(log n) ----------------
ll modpow(ll x, ll n, ll m)
{
    ll result = 1;
    x %= m;
    while (n > 0)
    {
        if (n & 1)
            result = result * x % m;
        x = x * x % m;
        n >>= 1;
    }
    return result;
}

// Nghịch đảo modular: x^(-1) mod m (m phải là số nguyên tố)
ll modInverse(ll x, ll m) { return modpow(x, m - 2, m); }

// ---- 5. Extended Euclid - Giải phương trình Diophantine ax+by=gcd -
ll extGcd(ll a, ll b, ll &x, ll &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll g = extGcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// Giải ax + by = c, trả về false nếu vô nghiệm
bool solveDiophantine(ll a, ll b, ll c, ll &x, ll &y)
{
    ll g = extGcd(a, b, x, y);
    if (c % g != 0)
        return false;
    x *= c / g;
    y *= c / g;
    return true;
}

// ---- 6. τ(n): số lượng ước, σ(n): tổng ước, μ(n): tích ước -------
ll countDivisors(ll n)
{
    // Dựa vào phân tích thừa số: τ(n) = Π(αi + 1)
    ll count = 1, tmp = n;
    for (ll p = 2; p * p <= tmp; p++)
    {
        int alpha = 0;
        while (tmp % p == 0)
        {
            alpha++;
            tmp /= p;
        }
        count *= (alpha + 1);
    }
    if (tmp > 1)
        count *= 2; // bậc 1 => α=1 => (1+1)=2
    return count;
}

int main()
{
    cout << "=== CAU 1: LY THUYET SO ===\n\n";

    // 1. Sàng nguyên tố
    buildSieve(MAXN);
    cout << "[Sieve] Cac so nguyen to <= " << MAXN << ":\n";
    for (int i = 2; i <= MAXN; i++)
        if (sieve[i] == 0)
            cout << i << " ";
    cout << "\n\n";

    // 2. Phân tích thừa số
    int n = 360;
    auto factors = primeFactors(n);
    cout << "[PrimeFactors] " << n << " = ";
    for (int i = 0; i < (int)factors.size(); i++)
    {
        cout << factors[i];
        if (i + 1 < (int)factors.size())
            cout << " x ";
    }
    cout << "\n";
    cout << "[τ(360)] So luong uoc = " << countDivisors(360) << "\n\n";

    // 3. GCD / LCM
    ll a = 24, b = 36;
    cout << "[Euclid] gcd(" << a << "," << b << ") = " << gcd(a, b) << "\n";
    cout << "[Euclid] lcm(" << a << "," << b << ") = " << lcm(a, b) << "\n\n";

    // 4. Euler Totient
    ll num = 12;
    cout << "[Totient] phi(" << num << ") = " << eulerTotient(num) << "\n\n";

    // 5. Modular exponentiation
    ll x = 6, exp_n = 15, mod = 17;
    cout << "[ModPow] " << x << "^" << exp_n << " mod " << mod
         << " = " << modpow(x, exp_n, mod) << "\n";
    cout << "[ModInverse] " << x << "^(-1) mod " << mod
         << " = " << modInverse(x, mod) << "\n\n";

    // 6. Phương trình Diophantine: 39x + 15y = 12
    ll px, py;
    ll da = 39, db = 15, dc = 12;
    if (solveDiophantine(da, db, dc, px, py))
    {
        cout << "[Diophantine] " << da << "x + " << db << "y = " << dc << "\n";
        cout << "  Nghiem: x = " << px << ", y = " << py << "\n";
        cout << "  Kiem tra: " << da * px + db * py << " == " << dc << "\n";
    }
    else
    {
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
    ll sol = (3 * X1 * inv1 + 4 * X2 * inv2 + 2 * X3 * inv3) % M;
    cout << "  Nghiem x = " << sol << " (mod " << M << ")\n";
    cout << "  Kiem tra: " << sol << " mod 5 = " << sol % 5
         << ", mod 7 = " << sol % 7
         << ", mod 3 = " << sol % 3 << "\n";

    return 0;
}