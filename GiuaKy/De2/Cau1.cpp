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

vector<long long> coprimes()
{
    vector<long long> list;
    for (long long i = 1; i < N; i++)
    {
        if (gcd(i, N) == 1)
        {
            list.push_back(i);
        }
    }
    return list;
}

long long nearestPrime()
{
    if (isPrime(N))
        return N;
    for (long long d = 1;; d++)
    {
        if (isPrime(N - d))
            return N - d;
        if (isPrime(N + d))
            return N + d;
    }
}

vector<long long> perfectNumbersLessThan(long long M)
{
    vector<long long> list;
    for (long long i = 2; i < M; i++)
    {
        if (isPerfectNumber(i))
        {
            list.push_back(i);
        }
    }
    return list;
}

long long nearestDivisibleBy3()
{
    if (N % 3 == 0)
        return N;
    long long below = N - (N % 3);
    long long above = below + 3;
    return (N - below) <= (above - N) ? below : above;
}

int main()
{
    do
    {
        cout << "Nhap so nguyen duong N: ";
        cin >> N;
    } while (N <= 0);
    long long sum = 0;
    vector<long long> list = coprimes();
    cout << "1. Cac so nguyen to cung nhau voi N = " << N << ":" << endl;
    cout << "   So luong: " << list.size() << endl;
    cout << "   Danh sach: ";
    for (long long i = 0; i < (long long)list.size(); i++)
    {
        cout << list[i];
        if (i < (long long)list.size() - 1)
            cout << ", ";
        sum += list[i];
    }
    cout << "   Tong    : " << sum << endl;

    cout << endl;

    long long M = nearestPrime();
    cout << "2. So nguyen to gan N = " << N << " nhat: M = " << M << endl;
    cout << "   (Khoang cach: |" << N << " - " << M << "| = " << abs(N - M) << ")" << endl;
    cout << endl;

    vector<long long> perfectNumbers = perfectNumbersLessThan(M);
    sum = 0;
    cout << "3. Cac so hoan hao nho hon M = " << M << ":" << endl;
    if (perfectNumbers.empty())
    {
        cout << "   Khong co so hoan hao nao." << endl;
    }
    else
    {
        cout << "   Danh sach: ";
        for (long long i = 0; i < (long long)perfectNumbers.size(); i++)
        {
            cout << perfectNumbers[i];
            if (i < (long long)perfectNumbers.size() - 1)
                cout << ", ";
            sum += perfectNumbers[i];
        }
        cout << endl;
        cout << "   Tong: " << sum << endl;
    }
    cout << endl;

    long long nearest3 = nearestDivisibleBy3();
    cout << "4. So gan N = " << N << " nhat va chia het cho 3: " << nearest3 << endl;
    cout << "   (Kiem tra: " << nearest3 << " % 3 = " << nearest3 % 3 << ")" << endl;

    return 0;
}