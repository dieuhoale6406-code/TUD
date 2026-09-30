#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
using namespace std;
#define eps 1e-6
#define laptoida 100
void nhapmatran(vector<vector<double>> &a, int n){
    cout << "Nhap ma tran A:\n";
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++){
            cout<<"a["<<i+1<<"]["<<j+1<<"]: ";
            cin >> a[i][j];
        }
}
bool ktradoixung(vector<vector<double>> &a,int n){
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(a[i][j]!=a[j][i]) return false;
    return true;
}
void kqphanra(vector<vector<double>> &d, vector<vector<double>> &v, int n){
    cout << "\nMa tran gia tri rieng (duong cheo):\n";
    for(int i=0;i<n;i++) cout << d[i][i] << " ";
    cout << "\nMa tran vector rieng (cot):\n";
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            cout << setw(10) << v[i][j] << " ";
        cout << "\n";
    }
}
void phanra(vector<vector<double>> a,int n){
    vector<vector<double>> v(n,vector<double>(n,0));
    vector<vector<double>> d=a; 
    for(int i=0;i<n;i++) v[i][i]=1;
    for(int lap=0;lap<laptoida;lap++){
        int p=0,q=1;
        double max=0;
        for(int i=0;i<n;i++)
            for(int j=i+1;j<n;j++)
                if(fabs(d[i][j])>max){
                    max=fabs(d[i][j]);
                    p=i;q=j;
                }
        if(max<eps) break;
        double theta=0.5*atan2(2*d[p][q],d[q][q]-d[p][p]);
        double c=cos(theta),s=sin(theta);
        //xoay cột và hàng
        for(int i=0;i<n;i++){
            double dip=d[p][i],diq=d[q][i];
            d[p][i]=c*dip - s*diq;
            d[q][i]=s*dip + c*diq;
        }
        for(int i=0;i<n;i++){
            double dip=d[i][p],diq=d[i][q];
            d[i][p]=c*dip - s*diq;
            d[i][q]=s*dip + c*diq;
        }
        d[p][q]=d[q][p]=0;
        //cập nhật vector riêng
        for(int i=0;i<n;i++){
            double vip=v[i][p],viq=v[i][q];
            v[i][p]=c*vip - s*viq;
            v[i][q]=s*vip + c*viq;
        }
    }
    kqphanra(d,v,n);
}
int main(){
    int n;
    cout << "Nhap cap ma tran: ";
    cin >> n;
    vector<vector<double>> a(n,vector<double>(n));
    nhapmatran(a,n);
    if(ktradoixung(a,n)) phanra(a,n);
    else cout << "Ma tran khong doi xung, phan ra theo gia tri rieng khong duoc.\n";
    return 0;
}
