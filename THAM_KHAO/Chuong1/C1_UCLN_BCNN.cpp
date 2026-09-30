#include <iostream>
using namespace std;

int gcd(int a, int b) {
   return b == 0 ? a : gcd(b, a % b);
}

int lcm(int a, int b) {
   return (a * b) / gcd(a, b);
}

bool is_coprime(int a, int b) {
   return gcd(a, b) == 1;
}

int main() {
   int a, b;
   cin >> a >> b;

   cout << (is_coprime(a, b) ? "Nguyen to cung nhau" : "Khong la nguyen to cung nhau") << endl;
   cout << "Gcd: " << gcd(a, b) << "\nLcm: " << lcm(a, b) << endl;

   return 0;
}
