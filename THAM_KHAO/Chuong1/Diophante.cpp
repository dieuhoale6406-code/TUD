//phương trình nghiệm nguyên
#include <iostream>
#include<math.h>
using namespace std;
int ExtendedGcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = ExtendedGcd(b, a % b, x1, y1);
    x = y1;
    y = x1-(a/b)*y1;
    return d;
}
void Diophantine(int a, int b, int c) {
    int x, y;
    int d = ExtendedGcd(a, b, x, y);
    if (c % d != 0) {
        cout << "Vo nghiem.\n";
        return;
    }
    x *= c / d;
    y *= c / d;
    cout << "Nghiem rieng: x = " << x << ", y = " << y << endl;
    cout << "Nghiem tong quat:" << endl;
    cout << "x = " << x << " + " << b/d << "*r "<<endl
         << "y = " << y << " - " << a/d << "*r ";
}
int main() {
    int a, b, c;
    cout << "Nhap a, b, c: ";
    cin >> a >> b >> c;
    Diophantine(a, b, c);
    return 0;
}
