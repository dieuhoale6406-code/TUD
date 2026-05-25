#include <iostream>
#include <vector>

using namespace std;

vector<int> sieve(int k, int n) { // O(log n)
    vector<bool> prime(n + 1, true);
    for (int i = 2; i * i <= n; i++) {
        if(prime[i]) {
            for(int j = i * i; j <= n; j += i)
                prime[j] = false;
        }
    }
    vector<int> p;
    for(int i = k; i <= n; i++)
        if(prime[i])
            p.push_back(i);
    return p;
}

int main() {
    int n;
    cout << "Nhap n: ";
    cin >> n;
    for(int i : sieve(2,n))
        cout << i << ' ';
    cout << endl;
    int k;
    cout << "Nhap a va b: ";
    cin >> k >> n;
    for (int i : sieve(k, n))
        cout << i << ' ';
    return 0;
}