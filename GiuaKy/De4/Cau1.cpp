#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

long long N = 0;

long long gcd(long long a, long long b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
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

vector<long long> perfectNumbersLessThan(long long M)
{
    vector<long long> list;
    for (long long i = 2; i < M; i++)
        if (isPerfectNumber(i))
            list.push_back(i);
    return list;
}

long long nearestDivisibleBy7(long long K)
{
    if (K % 7 == 0)
        return K;
    long long below = K - (K % 7);
    long long above = below + 7;
    return (K - below) <= (above - K) ? below : above;
}

vector<long long> coprimes(long long K)
{
    vector<long long> list;
    for (long long i = 1; i < K; i++)
        if (gcd(i, K) == 1)
            list.push_back(i);
    return list;
}

long long nearestPrime(long long K)
{
    if (isPrime(K))
        return K;
    for (long long d = 1;; d++)
    {
        if (K - d >= 2 && isPrime(K - d))
            return K - d;
        if (isPrime(K + d))
            return K + d;
    }
}

int main()
{
    do
    {
        cout << "Nhap so nguyen duong N: ";
        cin >> N;
    } while (N <= 0);

    vector<long long> perfects = perfectNumbersLessThan(N);
    long long sum = 0;
    cout << "1. Cac so hoan hao nho hon N = " << N << ":" << endl;
    if (perfects.empty())
    {
        cout << "   Khong co so hoan hao nao" << endl;
    }
    else
    {
        cout << "   So luong: " << perfects.size() << endl;
        cout << "   Danh sach: ";
        for (long long i = 0; i < (long long)perfects.size(); i++)
        {
            cout << perfects[i];
            if (i < (long long)perfects.size() - 1)
                cout << ", ";
            sum += perfects[i];
        }
        cout << endl;
        cout << "   Tong: " << sum << endl;
    }
    cout << endl;

    long long M = perfects.back();
    long long K = nearestDivisibleBy7(M);
    cout << "2. So hoan hao lon nhat: M = " << M << endl;
    cout << "   So K gan M nhat va chia het cho 7: K = " << K << endl;
    cout << endl;

    vector<long long> coprimeList = coprimes(K);
    sum = 0;
    cout << "3. Cac so nguyen duong nho hon K = " << K << " va nguyen to cung nhau voi K:" << endl;
    cout << "   So luong: " << coprimeList.size() << endl;
    cout << "   Danh sach: ";
    for (long long i = 0; i < (long long)coprimeList.size(); i++)
    {
        cout << coprimeList[i];
        if (i < (long long)coprimeList.size() - 1)
            cout << ", ";
        sum += coprimeList[i];
    }
    cout << endl;
    cout << "   Tong: " << sum << endl;
    cout << endl;

    long long P = nearestPrime(K);
    cout << "4. So nguyen to P gan K = " << K << " nhat: P = " << P << endl;
    cout << "   (Khoang cach: |" << K << " - " << P << "| = " << abs(K - P) << ")" << endl;

    return 0;
}