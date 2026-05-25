#include <iostream>

using namespace std;

bool add(int x, int y, int m) {
    cout << "(" << x << " + " << y << ") mod " << m << " = " << (x + y) % m << endl;
    cout << "(" << x << " mod " << m << " + " << y << " mod " << m << ") mod " << m << " = " << (x % m + y % m) % m << endl;
    return (x + y) % m == (x % m + y % m) % m;
}

bool sub(int x, int y, int m) {
    cout << "(" << x << " - " << y << ") mod " << m << " = " << (x - y) % m << endl;
    cout << "(" << x << " mod " << m << " - " << y << " mod " << m << ") mod " << m << " = " << (x % m - y % m) % m << endl;
    return (x - y) % m == (x % m - y % m) % m;
}

bool mult(int x, int y, int m) {
    cout << "(" << x << " * " << y << ") mod " << m << " = " << (x * y) % m << endl;
    cout << "(" << x << " mod " << m << " * " << y << " mod " << m << ") mod " << m << " = " << (x % m * y % m) % m << endl;
    return (x * y) % m == (x % m * y % m) % m;
}

long long modpow(int x, int n, int m) { // O(log n)
    if(n == 0)
        return 1 % m;
    long long u = modpow(x, n/2, m);
    u = (u * u) % m;
    if(n % 2 == 1)
        u = (u * x) % m;
    return u;
}

bool exp(int x, int n, int m) {
    long long pow = 1;
    for (int i = 0; i < n; i++)
        pow = pow * x;
    pow %= m;
    return pow == modpow(x,n,m);
}

int main() {
    int choice;
    cout << "1. Kiem tra (x + y)mod m = (x mod m + y mod m)mod m\n2. Kiem tra (x - y)mod m = (x mod m - y mod m)mod m\n3. Kiem tra (x * y)mod m = (x mod m * y mod m)mod m\n4. Kiem tra x^n mod m = (x mod m)^ n mod m\n";
    cin >> choice;
    int x, y, m, n;
    switch (choice)
    {
    case 1:
        cout << "Nhap x, y, m: ";
        cin >> x >> y >> m;
        cout << (add(x, y, m) ? "BANG NHAU" : "KHONG BANG NHAU");
        break;
    case 2:
        cout << "Nhap x, y, m: ";
        cin >> x >> y >> m;
        cout << (sub(x, y, m) ? "BANG NHAU" : "KHONG BANG NHAU");
        break;
    case 3:
        cout << "Nhap x, y, m: ";
        cin >> x >> y >> m;
        cout << (mult(x, y, m) ? "BANG NHAU" : "KHONG BANG NHAU");
        break;
    case 4:
        cout << "Nhap x, n, m: ";
        cin >> x >> n >> m;
        cout << (exp(x, n, m) ? "BANG NHAU" : "KHONG BANG NHAU");
        break;

    default:
        break;
    }
    return 0;
}
