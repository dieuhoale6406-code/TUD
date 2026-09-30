// // các số nguyên tố nhỏ hơn n
// #include<iostream>
// using namespace std;
// void Sang(int n){
//     //int sum=0;
//     bool SoNguyenTo[n+1];
//         for(int i =0; i<=n;i++){
//             SoNguyenTo[i] = true;
//         }
//     SoNguyenTo[0]=SoNguyenTo[1]= false;
//     for(int i=2; i*i <=n;i++){
//         if(SoNguyenTo[i]){
//             for(int j=i*i; j<=n;j+=i){
//                 SoNguyenTo[j] = false;
//             }
//         }
//     }
//     for(int i = 2; i<=n ; i++){
//         if(SoNguyenTo[i]){ cout <<i<<" ";
//        // sum+=i;
//         }
//     }
//     //cout<<sum << endl;
// }
// int main(){
//     int n;
//     cin >> n;
//     Sang(n);
//     return 0;
// }




// //các số nguyên tố từu m-n tính tổng và tìm số gần nhất

// #include <iostream>
// using namespace std;

// #define MAX 1000000   // giới hạn tối đa cho sàng

// bool isPrime[MAX + 1];

// void Sang(int N){
//     for(int i = 0; i <= N; i++)
//         isPrime[i] = true;

//     isPrime[0] = isPrime[1] = false;

//     for(int i = 2; i * i <= N; i++){
//         if(isPrime[i]){
//             for(int j = i * i; j <= N; j += i)
//                 isPrime[j] = false;
//         }
//     }
// }

// void InNguyenToTrongDoan(int m, int n){
//    // int sum=0;
//     if(m > n) swap(m, n);
//     if(m < 2) m = 2;

//     for(int i = m; i <= n; i++)
//         if(isPrime[i]){ cout << i << " ";
//       //  sum+=i;
//         }
//     cout << "\n";
//    // cout<< "Tong cac so tu "<<m-1<<" den "<<n<<" la: "<<sum;
//     //cout<< "\n";
// }

// // int NguyenToGanNhat(int k, int maxN){
// //     int prev = -1, next = -1;

// //     // tìm số nguyên tố <= k
// //     for(int i = k; i >= 2; i--){
// //         if(isPrime[i]){
// //             prev = i;
// //             break;
// //         }
// //     }

// //     // tìm số nguyên tố >= k
// //     for(int i = k; i <= maxN; i++){
// //         if(isPrime[i]){
// //             next = i;
// //             break;
// //         }
// //     }

// //     if(prev == -1) return next;
// //     if(next == -1) return prev;

// //     return (k - prev <= next - k) ? prev : next;
// // }

// int main(){
//     int m, n, k;
//     cin >> m >> n >> k;
//     //bỏ k nếu k cần tìm số nguyên tố gần nhất
//     int maxN = n;
//     if(k > maxN) maxN = k;
//     if(maxN < 2) maxN = 2;

//     Sang(maxN);

//     cout << "Cac so nguyen to trong [" << m << ", " << n << "]:\n";
//     InNguyenToTrongDoan(m, n);

//    // cout << "So nguyen to gan " << k << " nhat: ";
//    // cout << NguyenToGanNhat(k, maxN);

//     return 0;
// }








//2 số gần nhất xa nhất
#include <iostream>
using namespace std;

#define MAX 1000000
bool isPrime[MAX + 1];

void Sang(int N) {
    for (int i = 0; i <= N; i++) isPrime[i] = true;
    if (N >= 0) isPrime[0] = false;
    if (N >= 1) isPrime[1] = false;

    for (int i = 2; 1LL * i * i <= N; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= N; j += i)
                isPrime[j] = false;
        }
    }
}

int main() {
    int m, n;
    cin >> m >> n;
    if (m > n) swap(m, n);
    if (n < 2) {
        cout << "Khong co so nguyen to trong doan.\n";
        return 0;
    }

    if (n > MAX) {
        cout << "n vuot qua MAX = " << MAX << ". Hay tang MAX hoac giam n.\n";
        return 0;
    }

    Sang(n);

    int L = max(m, 2);

    cout << "Cac so nguyen to trong [" << m << ", " << n << "]:\n";

    long long sum = 0;
    int prevPrime = -1;

    // luu cặp gần nhất và xa nhất
    int gan_a = -1, gan_b = -1, minGap = 1e9;
    int xa_a  = -1, xa_b  = -1, maxGap = -1;

    int firstPrime = -1, lastPrime = -1;
    int countPrime = 0;

    for (int i = L; i <= n; i++) {
        if (isPrime[i]) {
            cout << i << " ";
            sum += i;
            countPrime++;

            if (firstPrime == -1) firstPrime = i;
            lastPrime = i;

            if (prevPrime != -1) {
                int gap = i - prevPrime;

                if (gap < minGap) {
                    minGap = gap;
                    gan_a = prevPrime;
                    gan_b = i;
                }
            }
            prevPrime = i;
        }
    }
    cout << "\n";

    cout << "Tong cac so nguyen to trong doan = " << sum << "\n";

    if (countPrime < 2) {
        cout << "Khong du 2 so nguyen to de tim cap gan/xa.\n";
        return 0;
    }

    // cặp xa nhất trong đoạn: luôn là số nguyên tố đầu và cuối
    maxGap = lastPrime - firstPrime;
    xa_a = firstPrime;
    xa_b = lastPrime;

    cout << "Cap 2 so nguyen to GAN nhat: (" << gan_a << ", " << gan_b
         << "), khoang cach = " << minGap << "\n";

    cout << "Cap 2 so nguyen to XA nhat: (" << xa_a << ", " << xa_b
         << "), khoang cach = " << maxGap << "\n";

    return 0;
}




