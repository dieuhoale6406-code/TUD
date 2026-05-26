
#include <iostream>
using namespace std;

double Fibonacci(int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;

    double a = 0, b = 1, c;
    for (int i = 2; i <= n; i++)
    {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

// Kiểm tra xem x có phải là số nguyên dương chia hết cho 7 hay không
bool sochiahetcho7(long long x)
{
    if (x < 2)
        return false;
    for (long long i = 2; i * i <= x; i++)
    {
        if (x % i == 0)
            return false;
    }
    return true;
}
// Tìm số nguyên dương chia hết cho 7 gần nhất với x (ưu tiên nhỏ hơn nếu hòa)
double sogannhatchiahetcho7(double x)
{
    for (double i = x; i >= 2; i--)
    {
        if (sochiahetcho7(i))
        {
            return i;
        }
    }
    return 0;
}
// Kiểm tra xem n có phải là số nguyên tố hay không
bool isPrime(long long n)
{
    if (n < 2)
        return false;
    for (long long i = 2; i * i <= n; i++)
        if (n % i == 0)
            return false;
    return true;
}
// Tìm số nguyên tố M gần N nhất (ưu tiên nhỏ hơn nếu hòa)
long long nearestPrime(long long n)
{
    if (isPrime(n))
        return n;
    for (long long d = 1;; d++)
    {
        if (isPrime(n - d))
            return n - d;
        if (isPrime(n + d))
            return n + d;
    }
}

// f(n)^n mod m
long long modpow(long long n, long long m)
{
    long long result = 1;
    long long x = Fibonacci(n);
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
int main()
{
    int n;
    int m;
    cout << "Nhap n: ";
    cin >> n;

    double fn = Fibonacci(n);
    cout << "So chia het cho 7 gan nhat voi f(n): ";
    cout << sogannhatchiahetcho7(fn);

    cout << "\nSo nguyen to gan n nhat: " << nearestPrime(n) << endl;
    cout << "Nhap m: ";
    cin >> m;
    cout << "f(n)^n mod m: " << modpow(n, m) << endl;
    return 0;
}
