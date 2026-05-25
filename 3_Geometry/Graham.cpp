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

vector<Diem> graham(vector<Diem> pts)
{
    int n = (int)pts.size();
    if (n <= 1)
        return pts;

    // Bước 1: Tìm điểm cực (pivot) - y nhỏ nhất, nếu bằng thì x nhỏ nhất
    int pivot = 0;
    for (int i = 1; i < n; i++)
    {
        if (pts[i].y < pts[pivot].y ||
            (pts[i].y == pts[pivot].y && pts[i].x < pts[pivot].x))
            pivot = i;
    }
    swap(pts[0], pts[pivot]);
    Diem p0 = pts[0];

    // Bước 2: Sắp xếp theo góc cực tương đối so với p0
    sort(pts.begin() + 1, pts.end(), [&](const Diem &a, const Diem &b)
         {
        long long cross = tichCoHuong(p0, a, b);
        if (cross != 0) return cross > 0; // a trước b nếu a "trái hơn"
        // Cùng góc: lấy điểm gần hơn trước (hoặc xa hơn — tuỳ convention)
        return khoangCachBinhPhuong(p0, a) < khoangCachBinhPhuong(p0, b); });

    // Bước 3: Xử lý điểm collinear ở cuối — giữ điểm xa nhất
    // (để hull không bỏ sót đỉnh thật)
    int m = n - 1;
    while (m > 0 && tichCoHuong(p0, pts[m], pts[n - 1]) == 0)
        m--;
    reverse(pts.begin() + m + 1, pts.end());

    // Bước 4: Graham Scan — dùng stack
    if (n < 3)
        return pts;
    vector<Diem> stk;
    stk.push_back(pts[0]);
    stk.push_back(pts[1]);
    for (int i = 2; i < n; i++)
    {
        while (stk.size() > 1 &&
               tichCoHuong(stk[stk.size() - 2], stk[stk.size() - 1], pts[i]) <= 0)
            stk.pop_back();
        stk.push_back(pts[i]);
    }
    return stk;
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

    inBaoLoi("Graham Scan", graham(pts));
    cout << "Danh sach diem ben trong bao loi:\n";
    for (const Diem &d : diemNamTrongBaoLoi(graham(pts), pts))
        cout << "   (" << d.x << ", " << d.y << ")\n";
}