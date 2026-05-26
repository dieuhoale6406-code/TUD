#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

long long N = 0;

vector<pair<long long, long long>> primeFactors(long long n)
{
    vector<pair<long long, long long>> factors;
    long long temp = n;
    for (long long i = 2; i * i <= temp; i++)
    {
        if (temp % i == 0)
        {
            long long cnt = 0;
            while (temp % i == 0)
            {
                cnt++;
                temp /= i;
            }
            factors.push_back(make_pair(i, cnt));
        }
    }
    if (temp > 1)
        factors.push_back(make_pair(temp, 1));
    return factors;
}
// Ước số nguyên tố lớn nhất M
long long largestPrimeFactor(const vector<pair<long long, long long>> &factors)
{
    if (factors.empty())
        return -1;
    return factors.back().first;
}

bool isPrime(long long n)
{
    if (n < 2)
        return false;
    for (long long i = 2; i * i <= n; i++)
        if (n % i == 0)
            return false;
    return true;
}

// Tìm tất cả số nguyên tố nhỏ hơn M
vector<long long> primesLessThan(long long M)
{
    vector<long long> primes;
    for (long long i = 2; i < M; i++)
        if (isPrime(i))
            primes.push_back(i);
    return primes;
}

bool isPerfectNumber(long long n)
{
    if (n < 2)
        return false;
    long long sum = 1;
    for (long long i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            sum += i;
            if (i != n / i)
                sum += n / i;
        }
    }
    return sum == n;
}

// Tìm tất cả số hoàn hảo nhỏ hơn M
vector<long long> perfectNumbersLessThan(long long M)
{
    vector<long long> perfects;
    for (long long i = 2; i < M; i++)
        if (isPerfectNumber(i))
            perfects.push_back(i);
    return perfects;
}

int main()
{
    do
    {
        cout << "Nhap so nguyen duong N: ";
        cin >> N;
    } while (N <= 0);

    vector<pair<long long, long long>> factors = primeFactors(N);
    cout << "1. Phan tich " << N << " thanh thua so nguyen to: " << N << " = ";
    for (long long i = 0; i < (long long)factors.size(); i++)
    {
        if (i > 0)
            cout << " * ";
        cout << factors[i].first;
        if (factors[i].second > 1)
            cout << "^" << factors[i].second;
    }
    cout << endl;

    long long M = largestPrimeFactor(factors);
    cout << "2. Uoc so nguyen to lon nhat cua " << N << " la M = " << M << endl;

    vector<long long> primes = primesLessThan(M);
    cout << "3. Cac so nguyen to nho hon M = " << M << ": ";
    long long sumPrimes = 0;
    for (long long i = 0; i < (long long)primes.size(); i++)
    {
        cout << primes[i];
        if (i < primes.size() - 1)
            cout << ", ";
        sumPrimes += primes[i];
    }
    cout << endl;
    cout << "   Tong = " << sumPrimes << endl;

    vector<long long> perfects = perfectNumbersLessThan(M);
    if (perfects.empty())
        cout << "4. Khong co so hoan hao nao nho hon M =" << M << endl;
    else
    {
        cout << "4. Cac so hoan hao nho hon M = " << M << ": ";
        long long sumPerfects = 0;
        for (long long i = 0; i < (long long)perfects.size(); i++)
        {
            cout << perfects[i];
            if (i < (long long)perfects.size() - 1)
                cout << ", ";
            sumPerfects += perfects[i];
        }
        cout << endl;
        cout << "Tong = " << sumPerfects << endl;
    }

    return 0;
}