
#include <iostream>
using namespace std;

double Fibonacci(int n){
    if(n == 0) return 0;
    if(n == 1) return 1;

    double a = 0, b = 1, c;
    for(int i = 2; i <= n; i++){
        c = a + b;
        a = b;
        b = c;
    }
    return b;}
bool sochiahetcho7(long long x){
    if(x < 2) return false;
    for(long long i = 2; i * i <= x; i++){
        if(x % i == 0) return false;
    }
    return true;
}

double sogannhatchiahetcho7(double x){
    for(double i = x; i >= 2; i--){
        if(sochiahetcho7(i)){
            return i;
        }
    }
    return 0;
}

int main(){
    int n;
    cin >> n;

    double fn = Fibonacci(n);
    cout << "So chia het cho 7 gan nhat voi f(n): ";
    cout << sogannhatchiahetcho7(fn);

    return 0;
}
