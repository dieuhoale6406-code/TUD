// tìm vector riêng giá trị riêng
#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
using namespace std;

#define eps 1e-10
#define so_lap_toi_da 100

void nhapmatran(vector<vector<double>> &a, int n){
    cout << "Nhap ma tran A:\n";
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++){
            cout<<"a["<<i+1<<"]["<<j+1<<"]: ";
            cin >> a[i][j];}
}
bool ktradoixung(vector<vector<double>> &a,int n){
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(a[i][j]!=a[j][i]) return false;
    return true;
}
void ketquajacobi(vector<vector<double>> &a, vector<vector<double>> &v, int n){
    cout << "\nChi so rieng (doi xung):\n";
    for(int i=0;i<n;i++) cout << a[i][i] << " ";
    cout << "\nVector rieng (cot):\n";
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            cout << setw(10) << v[i][j] << " ";
        cout << "\n";
    }
}
void jacobi(vector<vector<double>> a,int n){
    vector<vector<double>> v(n,vector<double>(n,0));
    for(int i=0;i<n;i++) v[i][i]=1;

    for(int lap=0;lap<so_lap_toi_da;lap++){
        int p=0,q=1;
        double max=fabs(a[p][q]);
        for(int i=0;i<n;i++)
            for(int j=i+1;j<n;j++)
                if(fabs(a[i][j])>max){
                    max=fabs(a[i][j]);
                    p=i;q=j;
                }
        if(max<eps) break;
        double theta=0.5*atan2(2*a[p][q],a[q][q]-a[p][p]);
        double c=cos(theta),s=sin(theta);
        for(int i=0;i<n;i++){
            double api=a[p][i],aqi=a[q][i];
            a[p][i]=c*api - s*aqi;
            a[q][i]=s*api + c*aqi;
        }
        for(int i=0;i<n;i++){
            double aip=a[i][p],aiq=a[i][q];
            a[i][p]=c*aip - s*aiq;
            a[i][q]=s*aip + c*aiq;
        }
        a[p][q]=a[q][p]=0;
        for(int i=0;i<n;i++){
            double vip=v[i][p],viq=v[i][q];
            v[i][p]=c*vip - s*viq;
            v[i][q]=s*vip + c*viq;
        }
    }
    ketquajacobi(a,v,n);
}

void luythua(vector<vector<double>> a,int n){
    vector<double> v(n,1.0);
    double lamda=0;
    for(int lap=0;lap<1000;lap++){
        vector<double> vmoi(n,0);
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                vmoi[i]+=a[i][j]*v[j];
        double chuan=0;
        for(int i=0;i<n;i++) chuan+=vmoi[i]*vmoi[i];
        chuan=sqrt(chuan);
        for(int i=0;i<n;i++) vmoi[i]/=chuan;
        double lamdamoi=0;
        for(int i=0;i<n;i++){
            double tong=0;
            for(int j=0;j<n;j++) tong+=a[i][j]*vmoi[j];
            lamdamoi+=vmoi[i]*tong;
        }

        if(fabs(lamdamoi-lamda)<eps){
            lamda=lamdamoi;
            v=vmoi;
            break;
        }
        lamda=lamdamoi;
        v=vmoi;
    }

    cout << "\nChi so rieng (gan dung - ko doi xung): " << lamda << "\n";
    cout << "Vector rieng tuong ung:\n";
    for(int i=0;i<n;i++) cout << v[i] << " ";
    cout << "\n";
}
int main(){
    int n;
    cout << "Nhap cap ma tran: ";
    cin >> n;
    vector<vector<double>> a(n,vector<double>(n));
    nhapmatran(a,n);
    if(ktradoixung(a,n)) jacobi(a,n);
    else luythua(a,n);
    return 0;
}
