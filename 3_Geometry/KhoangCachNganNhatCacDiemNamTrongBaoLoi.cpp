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

bool namTrenDoan(const Diem &a, const Diem &b, const Diem &p)
{
    if (tichCoHuong(a, b, p) != 0)
        return false;
    return (min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
            min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y));
}

bool namTrongDaGiacLoi(const vector<Diem> &poly, const Diem &p, bool includeBoundary = false)
{
    int n = (int)poly.size();
    if (n < 3)
        return false;
    bool coDuong = false, coAm = false;
    for (int i = 0; i < n; i++)
    {
        Diem a = poly[i];
        Diem b = poly[(i + 1) % n];
        long long c = tichCoHuong(a, b, p);
        if (c == 0)
        {
            if (namTrenDoan(a, b, p))
                return includeBoundary;
            return false;
        }
        if (c > 0)
            coDuong = true;
        else
            coAm = true;
        if (coDuong && coAm)
            return false;
    }
    return true;
}

void timKhoangCachNganNhatTrong(const vector<Diem> &hull, const vector<Diem> &tatCaDiem)
{
    vector<Diem> diemTrong;
    for (auto &p : tatCaDiem)
    {
        if (namTrongDaGiacLoi(hull, p, false))
            diemTrong.push_back(p);
    }

    cout << "[b] So diem hoan toan ben trong bao loi: " << diemTrong.size() << "\n";
    if (diemTrong.size() < 2)
    {
        cout << "    Khong du 2 diem ben trong de tinh khoang cach.\n";
        return;
    }
    cout << "Danh sach diem ben trong:\n";
    for (auto &d : diemTrong)
        cout << "  (" << d.x << ", " << d.y << ")\n";

    double minD = numeric_limits<double>::infinity();
    Diem pa, pb;
    int n = (int)diemTrong.size();
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
        {
            double d = khoangCach(diemTrong[i], diemTrong[j]);
            if (d < minD)
            {
                minD = d;
                pa = diemTrong[i];
                pb = diemTrong[j];
            }
        }

    cout << fixed << setprecision(4);
    cout << "    Khoang cach ngan nhat giua cac diem ben trong: " << minD << "\n";
    cout << "    Giua diem (" << pa.x << "," << pa.y << ") va ("
         << pb.x << "," << pb.y << ")\n";
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
    timKhoangCachNganNhatTrong(andrew(pts), pts);
}