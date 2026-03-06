#include <iostream>
#include <vector>

using namespace std;

long long modpow(long long x, long long n, long long m) { // O(log n)
    if(n == 0)
        return 1 % m;
    long long u = modpow(x, n/2, m);
    u = (u * u) % m;
    if(n % 2 == 1)
        u = (u * x) % m;
    return u;
}

long long eulerPhi(long long n) { // O(√n)
    long long result = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}

vector<long long> modInverse(vector<long long>& x, vector<long long>& m) {
    vector<long long> x_inverse;
    for(int i = 0; i < x.size(); i++) {
        x_inverse.push_back(modpow(x[i], eulerPhi(m[i]) - 1, m[i]));
    }
    return x_inverse;
}

int main() {
    long long n;
    cout << "Nhap so phuong trinh: ";
    cin >> n;
    vector<long long> a;
    vector<long long> m;
    long long num, rem;

    for(long long i = 1; i <= n; i++) {
        cin >> num >> rem;
        a.push_back(num);
        m.push_back(rem);
    }

    vector<long long> X;
    long long product = 1;
    for(int i = 0; i < n; i++)
        product *= m[i];
    for(int i = 0; i < n; i++)
        X.push_back(product / m[i]);

    vector<long long> X_inverse = modInverse(X,m);
    
    long long x = 0;
    for(int i = 0; i < n; i++)
        x += a[i] * X[i] * X_inverse[i];
    cout << "Solution = " << x % product << " + k" << product << endl;
    return 0;
}