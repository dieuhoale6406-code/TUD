#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int n;
vector<pair<int,int>> factors;

void primeFactors() {
    int temp = n;
    for(int i = 2; i * i <= temp; i++) {
        if(temp % i == 0) {
            int cnt = 0;
            while(temp % i == 0) {
                cnt++;
                temp /= i;
            }
            factors.push_back(make_pair(i,cnt));
        }
    }
    if(temp > 1) factors.peush_back(make_pair(temp,1));
}

int numbersOfFactors() {
    int number_of_factors = 1;
    for(int i = 0; i < factors.size(); i++) {
        number_of_factors *= factors[i].second + 1;
    }
    return number_of_factors;
}

int sumOfAFactor(int p, int a) {
    return (pow(p, a + 1) - 1)/ (p - 1);
}

int sumOfFactors() {
    int sum_of_factors = 1;
    for(int i = 0; i < factors.size(); i++) {
        sum_of_factors *= sumOfAFactor(factors[i].first, factors[i].second);
    }
    return sum_of_factors;
}

long long getProductOfFactors() {
    return pow((double)n, (double)numbersOfFactors() / 2);
}

bool isPerfectNumber() {
    return n == sumOfFactors() - n;
}

int main() {
    cout << "Nhap so can phan tich: ";
    cin >> n;
    primeFactors();
    for(int i = 0; i < factors.size(); i++) {
        cout << factors[i].first << "^" << factors[i].second << " ";
    }
    cout << endl << "So luong uoc so cua " << n << ": " << numbersOfFactors() << endl;
    cout << "Tong tat ca cac uoc so: " << sumOfFactors() << endl;
    cout << "Tich tat ca cac uoc so: " << getProductOfFactors() << endl;
    cout << n << (isPerfectNumber() ? " la " : " khong phai la ") << "so hoan hao" << endl; 
}