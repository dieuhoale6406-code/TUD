#include <iostream>
#include <vector>
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

void inBaoLoi(const string &ten, const vector<Diem> &hull)
{
    cout << "\n--- " << ten << " ---\n";
    cout << "So dinh bao loi: " << hull.size() << "\n";
    cout << "Cac dinh (theo thu tu):\n";
    for (auto &d : hull)
        cout << "  (" << d.x << ", " << d.y << ")\n";
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

vector<Diem> diemNamTrongBaoLoi(const vector<Diem> &hull, const vector<Diem> &tatCaDiem)
{
    // Thu thập điểm hoàn toàn bên trong (không tính biên)
    vector<Diem> diemTrong;
    for (auto &p : tatCaDiem)
        if (namTrongDaGiacLoi(hull, p, false))
            diemTrong.push_back(p);
    return diemTrong;
}

vector<Diem> jarvis(vector<Diem> pts)
{
    int n = (int)pts.size();
    if (n <= 1)
        return pts;

    // Tìm điểm bắt đầu: x nhỏ nhất, nếu bằng thì y nhỏ nhất
    int start = 0;
    for (int i = 1; i < n; i++)
        if (pts[i] < pts[start])
            start = i;

    vector<Diem> hull;
    int cur = start;
    do
    {
        hull.push_back(pts[cur]);
        int next = (cur + 1) % n;
        for (int i = 0; i < n; i++)
        {
            long long cross = tichCoHuong(pts[cur], pts[next], pts[i]);
            if (cross > 0)
            {
                // pts[i] nằm bên trái pts[next] => chọn pts[i]
                next = i;
            }
            else if (cross == 0)
            {
                // Thẳng hàng: chọn điểm xa hơn để tránh collinear trong hull
                if (khoangCachBinhPhuong(pts[cur], pts[i]) >
                    khoangCachBinhPhuong(pts[cur], pts[next]))
                    next = i;
            }
        }
        cur = next;
    } while (cur != start);

    return hull;
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

    inBaoLoi("Jarvis March", jarvis(pts));
    cout << "Danh sach diem ben trong bao loi:\n";
    for (const Diem &d : diemNamTrongBaoLoi(jarvis(pts), pts))
        cout << "   (" << d.x << ", " << d.y << ")\n";
}