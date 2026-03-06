#include <iostream>

using namespace std;

int gcd(int a, int b) {
    if(b == 0) return a;
    return gcd(b, a % b);
}

int lcm(int a, int b) {
    return a * b / gcd(a, b);
}

int main()
{
    int a, b;
    cout << "Nhap a va b: ";
    cin >> a >> b;
    cout << "Uoc chung lon nhat: " << gcd(a,b) << ", boi chung nho nhat: " << lcm(a, b);
    return 0;
}
