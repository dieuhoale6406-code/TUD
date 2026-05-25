#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>
#include <cmath>
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

long long khoangCachBinhPhuong(const Diem &a, const Diem &b)
{
    return 1LL * (a.x - b.x) * (a.x - b.x) + 1LL * (a.y - b.y) * (a.y - b.y);
}

double khoangCach(const Diem &a, const Diem &b)
{
    return sqrt((double)khoangCachBinhPhuong(a, b));
}

void timCanhNhoNhat(const vector<Diem> &hull)
{
    int n = (int)hull.size();
    if (n < 2)
    {
        cout << "[c] Khong du canh.\n";
        return;
    }

    double minD = numeric_limits<double>::infinity();
    int idx = -1;
    for (int i = 0; i < n; i++)
    {
        double d = khoangCach(hull[i], hull[(i + 1) % n]);
        if (d < minD)
        {
            minD = d;
            idx = i;
        }
    }

    cout << fixed << setprecision(4);
    cout << "[c] Canh nho nhat cua bao loi: " << minD << "\n";
    cout << "    Tu (" << hull[idx].x << "," << hull[idx].y << ") den ("
         << hull[(idx + 1) % n].x << "," << hull[(idx + 1) % n].y << ")\n";
}

vector<Diem> andrew(vector<Diem> pts)
{
    int n = (int)pts.size();
    if (n <= 1)
        return pts;
    sort(pts.begin(), pts.end());
    // Loại trùng
    pts.erase(unique(pts.begin(), pts.end()), pts.end());
    n = (int)pts.size();
    if (n <= 1)
        return pts;

    vector<Diem> lower, upper;

    // Bao dưới (left to right, CCW)
    for (int i = 0; i < n; i++)
    {
        while (lower.size() >= 2 &&
               tichCoHuong(lower[lower.size() - 2], lower[lower.size() - 1], pts[i]) <= 0)
            lower.pop_back();
        lower.push_back(pts[i]);
    }
    // Bao trên (right to left, CCW)
    for (int i = n - 1; i >= 0; i--)
    {
        while (upper.size() >= 2 &&
               tichCoHuong(upper[upper.size() - 2], upper[upper.size() - 1], pts[i]) <= 0)
            upper.pop_back();
        upper.push_back(pts[i]);
    }
    // Xóa điểm trùng ở đầu/cuối
    lower.pop_back();
    upper.pop_back();
    lower.insert(lower.end(), upper.begin(), upper.end());
    return lower;
}

int main()
{
    int n;
    cout << "Nhap so luong diem (vi du 15): ";
    cin >> n;

    vector<Diem> pts(n);
    cout << "Nhap toa do cac diem (x y):\n";
    for (int i = 0; i < n; i++)
    {
        cin >> pts[i].x >> pts[i].y;
        pts[i].chi_so = i;
    }

    timCanhNhoNhat(andrew(pts));
}