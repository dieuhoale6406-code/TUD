//#include <iostream>
//#include <cmath>
//using namespace std;
//
//bool is_prime(int n) {
//    if (n < 2) return false;
//    for (int i = 2; i <= sqrt(n); ++i) {
//        if (n % i == 0) return false;
//    }
//    return true;
//}
//
//int euler_phi(int n) {
//    int result = n;
//    for (int p = 2; p <= sqrt(n); ++p) {
//        if (n % p == 0) {
//            while (n % p == 0) n /= p;
//            result -= result / p;
//        }
//    }
//    if (n > 1) result -= result / n;
//    return result;
//}
//
//int power_mod(int a, int b, int m) {
//    int res = 1;
//    a %= m;
//    while (b) {
//        if (b & 1) res = (res * a) % m;
//        b >>= 1;
//        a = (a * a) % m;
//    }
//    return res;
//}
//
//int mod_inverse(int a, int m) {
//    return power_mod(a, euler_phi(m) - 1, m);
//}
//
//int gcd(int a, int b) {
//    return b ? gcd(b, a % b) : a;
//}
//
//int main() {
//    int a, m;
//    cin >> a >> m;
//    if (gcd(a, m) != 1) {
//        cout << "No modular inverse for " << a << " mod " << m << endl;
//    }
//    else {
//        cout << "Modular inverse of " << a << " mod " << m << " is " << mod_inverse(a, m) << endl;
//    }
//    return 0;
//}
