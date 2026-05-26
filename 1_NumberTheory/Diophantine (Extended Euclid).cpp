#include <iostream>

using namespace std;

long long extGcd(long long a, long long b, long long &x, long long &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long g = extGcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// Giải ax + by = c, trả về false nếu vô nghiệm
bool solveDiophantine(long long a, long long b, long long c, long long &x, long long &y)
{
    long long g = extGcd(a, b, x, y);
    if (c % g != 0)
        return false;
    x *= c / g;
    y *= c / g;
    return true;
}

int main()
{
    long long px, py, da, db, dc;
    cout << "Phương trình Diophantine: ax + by = c" << endl;
    cout << "Nhap a, b, c: ";
    cin >> da >> db >> dc;
    if (solveDiophantine(da, db, dc, px, py))
    {
        cout << "[Diophantine] " << da << "x + " << db << "y = " << dc << "\n";
        cout << "  Nghiem: x = " << px << ", y = " << py << "\n";
        cout << "  Kiem tra: " << da * px + db * py << " == " << dc << "\n";
    }
    else
    {
        cout << "[Diophantine] Phuong trinh vo nghiem!\n";
    }
}