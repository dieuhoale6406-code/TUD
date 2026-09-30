//số dư của a mũ m chia n or số dư của fliibolnaci(m) mũ m chia n
#include<iostream>
using namespace std;
long long Fibonacci(int n){
    if(n == 0) return 0;
    if(n == 1) return 1;

    long long a = 0, b = 1, c;
    for(int i = 2; i <= n; i++){
        c = a + b;
        a = b;
        b = c;
    }
    return b;}
long long LayDu(long long a, long long m, long long n){
    long long kq = 1;
    a = a%n; 
    while(m>0){ 
        if (m%2==1){
            kq = (kq*a)%n; 
        }
        a=(a*a)%n;
        m/=2;} 
    return kq;
}
int main(){
    long long a,m,n;
    cout<<"nhap m";
    cin >> m;
    cout<<"nhap n";
    cin>> n;
    a=Fibonacci(n);
    long long k=Fibonacci(m);
    cout << LayDu(a,k,m) << endl;
    return 0;
}
