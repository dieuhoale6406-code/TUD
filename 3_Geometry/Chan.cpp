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

Diem tangent(const vector<Diem> &hull, const Diem &q)
{
    int n = (int)hull.size();
    if (n == 1)
        return hull[0];

    int lo = 0, hi = n;
    // Cross product của cạnh i: tichCoHuong(q, hull[i], hull[(i+1)%n])
    auto cross_at = [&](int i)
    {
        return tichCoHuong(q, hull[i % n], hull[(i + 1) % n]);
    };
    auto up_at = [&](int i)
    {
        return tichCoHuong(q, hull[0], hull[i % n]) > 0;
    };

    while (lo < hi)
    {
        int mid = (lo + hi) / 2;
        bool left_turn = cross_at(mid) > 0;
        bool on_left = up_at(mid);
        bool start_left_turn = cross_at(0) > 0;
        bool start_on_left = tichCoHuong(q, hull[0], hull[1]) > 0;

        if (left_turn && (!on_left || start_left_turn))
            lo = mid + 1;
        else if (!left_turn && (on_left || !start_left_turn))
            hi = mid;
        else
            break;
    }
    // Fallback O(n) nếu binary search phức tạp edge case
    int best = 0;
    for (int i = 1; i < n; i++)
    {
        long long c = tichCoHuong(q, hull[best], hull[i]);
        if (c > 0 || (c == 0 &&
                      khoangCachBinhPhuong(q, hull[i]) > khoangCachBinhPhuong(q, hull[best])))
            best = i;
    }
    return hull[best];
}

vector<Diem> chanOneTry(const vector<Diem> &pts, int m)
{
    int n = (int)pts.size();
    // Chia nhóm và tính mini-hull
    int numGroups = (n + m - 1) / m;
    vector<vector<Diem>> groups(numGroups);
    for (int i = 0; i < numGroups; i++)
    {
        int lo = i * m, hi = min(n, lo + m);
        vector<Diem> sub(pts.begin() + lo, pts.begin() + hi);
        groups[i] = graham(sub); // mini-hull bằng Graham
    }

    // Tìm điểm bắt đầu: y nhỏ nhất (rồi x nhỏ nhất)
    Diem p0 = pts[0];
    for (auto &p : pts)
        if (p.y < p0.y || (p.y == p0.y && p.x < p0.x))
            p0 = p;

    // Jarvis trên mini-hulls
    vector<Diem> hull;
    Diem cur = p0;
    for (int step = 0; step < m; step++)
    {
        hull.push_back(cur);
        // Điểm nằm "cực trái" nhất so với cur
        Diem next = cur; // placeholder
        bool first = true;
        for (auto &g : groups)
        {
            Diem candidate = tangent(g, cur);
            if (first)
            {
                next = candidate;
                first = false;
                continue;
            }
            long long cross = tichCoHuong(cur, next, candidate);
            if (cross > 0 ||
                (cross == 0 &&
                 khoangCachBinhPhuong(cur, candidate) > khoangCachBinhPhuong(cur, next)))
                next = candidate;
        }
        if (next == p0)
            return hull; // đóng vòng
        cur = next;
    }
    return {}; // chưa đóng vòng — m quá nhỏ
}

vector<Diem> chan(vector<Diem> pts)
{
    int n = (int)pts.size();
    if (n <= 1)
        return pts;
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());
    n = (int)pts.size();
    if (n <= 3)
        return graham(pts);

    for (int t = 1; t <= 30; t++)
    {
        // m = min(2^(2^t), n) — tránh overflow
        long long m = 1LL << min(t, 30); // 2^t đủ dùng cho mục đích thực tế
        if (m > n)
            m = n;
        auto hull = chanOneTry(pts, (int)m);
        if (!hull.empty())
            return hull;
    }
    // Fallback
    return graham(pts);
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

    inBaoLoi("Chan Algorithm", chan(pts));
    cout << "Danh sach diem ben trong bao loi:\n";
    for (const Diem &d : diemNamTrongBaoLoi(chan(pts), pts))
        cout << "   (" << d.x << ", " << d.y << ")\n";
}