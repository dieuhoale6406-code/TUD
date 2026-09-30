//ước chung lớn nhất
#include<iostream>
using namespace std;
int Euclid(int n, int m){
    if(m==0) return n;
    else{
        return Euclid(m,n%m); 
    }
}
int main(){
    int n,m;
    cin >> n >> m ;
    cout << Euclid(n,m)<<endl;
    return 0;
}
