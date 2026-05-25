#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Diem
{
    long long x, y;
    int chi_so;

    bool operator<(const Diem &o) const
    {
        return (x < o.x) || (x == o.x && y < o.y);
    }
    bool operator==(const Diem &o) const
    {
        return x == o.x && y == o.y;
    }
};

long long tichCoHuong(const Diem &goc, const Diem &a, const Diem &b)
{
    return 1LL * (a.x - goc.x) * (b.y - goc.y) - 1LL * (a.y - goc.y) * (b.x - goc.x);
}

double tinhDienTich(const vector<Diem> &poly)
{
    if (poly.size() < 3)
        return 0.0;
    long long S = 0;
    int n = (int)poly.size();
    for (int i = 0; i < n; i++)
    {
        int j = (i + 1) % n;
        S += poly[i].x * poly[j].y - poly[j].x * poly[i].y;
    }
    return fabs((double)S) / 2.0;
}

void inDienTich(const vector<Diem> &hull)
{
    double dt = tinhDienTich(hull);
    cout << fixed << setprecision(4);
    cout << "[a] Dien tich bao loi: " << dt << "\n";
}

vector<Diem> andrew(vector<Diem> pts)
{
    int n = (int)pts.size();
    if (n <= 1)
        return pts;
    sort(pts.begin(), pts.end());

    pts.erase(unique(pts.begin(), pts.end()), pts.end());
    n = (int)pts.size();
    if (n <= 1)
        return pts;

    vector<Diem> lower, upper;

    for (int i = 0; i < n; i++)
    {
        while (lower.size() >= 2 &&
               tichCoHuong(lower[lower.size() - 2], lower[lower.size() - 1], pts[i]) <= 0)
            lower.pop_back();
        lower.push_back(pts[i]);
    }
    for (int i = n - 1; i >= 0; i--)
    {
        while (upper.size() >= 2 &&
               tichCoHuong(upper[upper.size() - 2], upper[upper.size() - 1], pts[i]) <= 0)
            upper.pop_back();
        upper.push_back(pts[i]);
    }
    lower.pop_back();
    upper.pop_back();
    lower.insert(lower.end(), upper.begin(), upper.end());
    return lower;
}

int main()
{
    try
    {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);

        int n = 15;
        cout << "Nhap so luong diem (vi du 15): ";
        cin >> n;

        vector<Diem> pts(n);
        cout << "Nhap toa do cac diem (x y):\n";
        for (int i = 0; i < n; i++)
        {
            cin >> pts[i].x >> pts[i].y;
            pts[i].chi_so = i;
        }

        inDienTich(andrew(pts));
    }
    catch (exception &e)
    {
        cerr << "Loi: " << e.what() << endl;
    }
}