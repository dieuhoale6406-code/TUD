#include <iostream>
#include <vector>

using namespace std;

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

vector<int> eulerTotientFunction(int n) { // O(n log n)
    vector<int> p;
    for(int i = 1; i < n; i++)
    if(gcd(i,n) == 1)
        p.push_back(i);
    return p;
}

int eulerPhi(int n) { // O(√n)
    int result = n;
    for(int i = 2; i * i <= n; i++) {
        if(n % i == 0) {
            while(n % i == 0)
                n /= i;
        result -= result / i;
        }
    }
    if(n > 1)
        result -= result / n;
    return result;
}

int main()
{
    int n;
    cout << "Nhap n: ";
    cin >> n;
    vector<int> p = eulerTotientFunction(n);
    cout << "Co " << eulerPhi(n) << " so nguyen to cung nhau voi " << n << ": " << endl;
    for(int i : p)
        cout << i << ' ';
    return 0;
}
