/*
#include<iostream>
using namespace std;
#define MAX 1000
typedef int VECTOR[MAX];
bool SoHoanHao(int n){
    if(n<=1) return false;
    int SUM = 1;
     for(int i=2;i*i<=n;i++){
            if(n%i==0){
             SUM += i;
                if(i !=n/i){
                    SUM += n/i;
                }
            }
        }
    return SUM == n;
}
void TimSoHoanHao(int n, VECTOR S, int &k){
    k=0;
    for(int i=1;i<=n;i++){
       if(SoHoanHao(i)){
        S[k]=i;
        k++;
       }
    }
}
int main(){
    int k;
    int F[MAX];
    int n;
    cin >> n;
    TimSoHoanHao(n,F,k);
    for(int i = 0; i < k; i++){
        cout << F[i] << " ";
    }
    //cout<< F[k-1]; in ra số hoàn hảo gần M nhất
    //tính tổng và số lượng
    long sum=0, dem=0;
    for(int i = 0; i < k; i++){
        sum+=F[i];
         dem++;
    }
    cout<<"\n"<<"Tong: "<<sum<<"\n";
    cout<<"Soluong: "<<dem;
    return 0;
}
*/




/*
//số hoàn hảo gần n nhất
#include <iostream>
using namespace std;

#define MAX 1000
typedef int VECTOR[MAX];

bool SoHoanHao(int n){
    if(n <= 1) return false;
    int SUM = 1;
    for(int i = 2; i * i <= n; i++){
        if(n % i == 0){
            SUM += i;
            if(i != n / i) SUM += n / i;
        }
    }
    return SUM == n;
}

void TimSoHoanHao(int n, VECTOR S, int &k){
    k = 0;
    for(int i = 1; i <= n; i++){
        if(SoHoanHao(i)){
            S[k] = i;
            k++;
            if(k >= MAX) break; // tránh tràn mảng nếu n quá lớn
        }
    }
}

int SoHoanHaoGanNhat(int n){
    // prev: hoàn hảo gần nhất phía <= n
    int prev = -1;
    for(int i = n; i >= 2; i--){
        if(SoHoanHao(i)){
            prev = i;
            break;
        }
    }

    // next: hoàn hảo gần nhất phía >= n
    int next = -1;
    for(int i = (n < 2 ? 2 : n); ; i++){
        if(SoHoanHao(i)){
            next = i;
            break;
        }
        // nếu bạn lo chạy quá lâu, có thể đặt giới hạn i ở đây
    }

    if(prev == -1) return next; // n nhỏ quá thì chỉ có phía trên
    int d1 = n - prev;
    int d2 = next - n;

    if(d1 <= d2) return prev;   // bằng nhau thì lấy số nhỏ hơn (prev)
    return next;
}

int main(){
    int n, k;
    int F[MAX];

    cin >> n;

    TimSoHoanHao(n, F, k);

    // In danh sách số hoàn hảo <= n
    for(int i = 0; i < k; i++){
        cout << F[i] << " ";
    }

    // In số hoàn hảo gần n nhất (xét cả trước/sau)
    int ganNhat = SoHoanHaoGanNhat(n);
    cout << "\nSo hoan hao gan n nhat: " << ganNhat;

    return 0;
}
*/


// có tìm số nguyên tố gần M nhất

#include <iostream>
using namespace std;

#define MAX 1000
typedef int VECTOR[MAX];

bool SoHoanHao(int n) {
    if (n <= 1) return false;
    int sum = 1;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            if (i != n / i) sum += n / i;
        }
    }
    return sum == n;
}

void TimSoHoanHao(int N, VECTOR S, int &k) {
    k = 0;
    for (int i = 1; i <= N; i++) {
        if (SoHoanHao(i)) {
            S[k++] = i;
            if (k >= MAX) break;
        }
    }
}

bool SoNguyenTo(int x) {
    if (x < 2) return false;
    if (x == 2 || x == 3) return true;
    if (x % 2 == 0) return false;
    for (int i = 3; 1LL * i * i <= x; i += 2) {
        if (x % i == 0) return false;
    }
    return true;
}

// Tìm số nguyên tố gần M nhất (ưu tiên nhỏ hơn nếu hòa)
int NguyenToGanM(int M, int N) {
    // chỉ xét prime < N
    int left = M, right = M;

    while (true) {
        if (left >= 2) {
            if (SoNguyenTo(left) && left < N) return left;
            left--;
        }

        right++;
        if (right < N && SoNguyenTo(right)) return right;

        // nếu cả 2 phía đều out of range mà chưa thấy prime
        if (left < 2 && right >= N) return -1;
    }
}
/*
// Tìm số nguyên tố gần M nhất theo 1 chiều: NHỎ HƠN M
int NguyenToGanM(int M) {
    for (int x = M - 1; x >= 2; x--) {
        if (SoNguyenTo(x))
            return x;
    }
    return -1; // không có số nguyên tố < M
}
*/
int main() {
    int N;
    cin >> N;

    int k;
    int F[MAX];

    TimSoHoanHao(N, F, k);

    if (k == 0) {
        cout << "Khong co so hoan hao <= N\n";
        return 0;
    }

    // In danh sach so hoan hao
    for (int i = 0; i < k; i++) {
        cout << F[i] << (i + 1 < k ? " " : "");
    }

    int M = F[k - 1];
    cout << "\nM (so hoan hao lon nhat) = " << M << "\n";

    long long sum = 0;
    for (int i = 0; i < k; i++) sum += F[i];
    cout << "Tong: " << sum << "\n";
    cout << "Soluong: " << k << "\n";

    int p = NguyenToGanM(M, N);
    // int p = NguyenToGanM(M);
    if (p == -1) {
        cout << "Khong tim duoc so nguyen to trong khoang [2, N)\n";
    } else {
        cout << "So nguyen to gan M nhat (va < N): " << p << "\n";
        cout << "Khoang cach |p - M| = " << (p > M ? p - M : M - p) << "\n";
    }

    return 0;
}
