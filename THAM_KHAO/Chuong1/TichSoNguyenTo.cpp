#include<iostream>
using namespace std;
#define MAX 100
typedef int VECTOR[MAX];
void PhanTichThuaSoNguyenTo(int n, VECTOR S, int &k ){
    k = 0;
    S[k] = n;
    for(int i=2;i*i<=n;i++){
        while(n % i==0){
            k++;
            S[k]=i;
            n=n/i;
        }
    }
    if (n>1) S[++k] = n;
}
int main(){
    int k;
    int F[MAX];
    int n;
    cin >> n ;
    PhanTichThuaSoNguyenTo(n,F,k);
    for(int i=1; i<=k;i++)
        cout << F[i] <<" ";
    // in ra thừa số lớn nhất
    //cout<<"Thua so nto max: "<<F[k];
    return 0;
}
