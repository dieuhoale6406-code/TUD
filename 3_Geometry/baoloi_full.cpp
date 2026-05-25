/*
=============================================================================
BAO LỒI - CONVEX HULL
Bài 1: Cho n điểm trong không gian
  a) Tính diện tích bao lồi (đa giác lồi lớn nhất tạo từ các điểm đã cho)
  b) Tính khoảng cách ngắn nhất của các điểm nằm bên trong bao lồi
  c) Tính cạnh nhỏ nhất của bao lồi

Thuật toán được cài đặt:
  1. Andrew (Monotone Chain)
  2. Jarvis (Gift Wrapping / March)
  3. Graham Scan
  4. Chan's Algorithm (Shattering / Output-sensitive)
=============================================================================
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
#include <cassert>
#include <iomanip>
using namespace std;

// ============================================================
// CẤU TRÚC ĐIỂM
// ============================================================
struct Diem
{
    long long x, y;
    int chi_so; // chỉ số gốc trong danh sách nhập vào

    bool operator<(const Diem &o) const
    {
        return (x < o.x) || (x == o.x && y < o.y);
    }
    bool operator==(const Diem &o) const
    {
        return x == o.x && y == o.y;
    }
};

// ============================================================
// HÀM TIỆN ÍCH CHUNG
// ============================================================

// Tích có hướng (cross product) của vector (goc->a) và (goc->b)
// > 0: b nằm trái a (ngược chiều kim đồng hồ)
// = 0: thẳng hàng
// < 0: b nằm phải a (cùng chiều kim đồng hồ)
long long tichCoHuong(const Diem &goc, const Diem &a, const Diem &b)
{
    return 1LL * (a.x - goc.x) * (b.y - goc.y) - 1LL * (a.y - goc.y) * (b.x - goc.x);
}

// Khoảng cách bình phương giữa 2 điểm
long long khoangCachBinhPhuong(const Diem &a, const Diem &b)
{
    return 1LL * (a.x - b.x) * (a.x - b.x) + 1LL * (a.y - b.y) * (a.y - b.y);
}

// Khoảng cách Euclid giữa 2 điểm
double khoangCach(const Diem &a, const Diem &b)
{
    return sqrt((double)khoangCachBinhPhuong(a, b));
}

// Tính diện tích bao lồi bằng công thức Shoelace
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

// Tính chu vi bao lồi
double tinhChuVi(const vector<Diem> &poly)
{
    int n = (int)poly.size();
    if (n < 2)
        return 0.0;
    double cv = 0.0;
    for (int i = 0; i < n; i++)
        cv += khoangCach(poly[i], poly[(i + 1) % n]);
    return cv;
}

// Kiểm tra điểm p có nằm trên đoạn [a, b] không
bool namTrenDoan(const Diem &a, const Diem &b, const Diem &p)
{
    if (tichCoHuong(a, b, p) != 0)
        return false;
    return (min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
            min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y));
}

// Kiểm tra điểm p có nằm trong đa giác lồi không
// includeBoundary = true : tính cả điểm trên biên
// includeBoundary = false: chỉ điểm hoàn toàn bên trong
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

// ============================================================
// IN KẾT QUẢ
// ============================================================
void inBaoLoi(const string &ten, const vector<Diem> &hull)
{
    cout << "\n--- " << ten << " ---\n";
    cout << "So dinh bao loi: " << hull.size() << "\n";
    cout << "Cac dinh (theo thu tu):\n";
    for (auto &d : hull)
        cout << "  (" << d.x << ", " << d.y << ")\n";
}

// ============================================================
// BÀI TOÁN a) DIỆN TÍCH
// ============================================================
void inDienTich(const vector<Diem> &hull)
{
    double dt = tinhDienTich(hull);
    cout << fixed << setprecision(4);
    cout << "[a] Dien tich bao loi: " << dt << "\n";
}

// ============================================================
// BÀI TOÁN b) KHOẢNG CÁCH NGẮN NHẤT GIỮA CÁC ĐIỂM BÊN TRONG
// ============================================================
void timKhoangCachNganNhatTrong(const vector<Diem> &hull, const vector<Diem> &tatCaDiem)
{
    // Thu thập điểm hoàn toàn bên trong (không tính biên)
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

// ============================================================
// BÀI TOÁN c) CẠNH NHỎ NHẤT CỦA BAO LỒI
// ============================================================
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

// ============================================================
// THUẬT TOÁN 1: ANDREW (MONOTONE CHAIN)
// Độ phức tạp: O(n log n)
// Ý tưởng:
//   - Sắp xếp điểm theo x (nếu bằng thì theo y)
//   - Xây bao dưới: duyệt từ trái sang phải, loại điểm tạo góc phải
//   - Xây bao trên: duyệt từ phải sang trái, loại điểm tạo góc phải
//   - Ghép bao dưới và bao trên
// ============================================================
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

// ============================================================
// THUẬT TOÁN 2: JARVIS (GIFT WRAPPING / MARCH)
// Độ phức tạp: O(n * h) — h là số đỉnh bao lồi
// Ý tưởng:
//   - Bắt đầu từ điểm có x nhỏ nhất (hoặc y nhỏ nhất nếu bằng)
//   - Mỗi bước, tìm điểm "quay nhiều nhất sang phải" so với điểm hiện tại
//     (tức là điểm mà tất cả điểm khác đều nằm bên trái đường nối)
//   - Lặp đến khi quay về điểm xuất phát
// ============================================================
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

// ============================================================
// THUẬT TOÁN 3: GRAHAM SCAN
// Độ phức tạp: O(n log n)
// Ý tưởng:
//   - Chọn điểm cực (y nhỏ nhất, nếu bằng thì x nhỏ nhất) làm gốc
//   - Sắp xếp các điểm còn lại theo góc cực (polar angle) so với gốc
//   - Quét lần lượt, dùng stack: loại điểm tạo góc phải (tích ≤ 0)
// ============================================================
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

// ============================================================
// THUẬT TOÁN 4: CHAN'S ALGORITHM (SHATTERING / OUTPUT-SENSITIVE)
// Độ phức tạp: O(n log h) — tối ưu nhất, h là số đỉnh hull
// Ý tưởng:
//   - Thử lần lượt m = 2^(2^t) với t = 1, 2, 3, ...
//   - Chia n điểm thành ceil(n/m) nhóm, mỗi nhóm ≤ m điểm
//   - Tính mini-hull cho từng nhóm bằng Graham Scan
//   - Dùng Jarvis march trên các mini-hull: mỗi bước chỉ cần xét
//     1 điểm tốt nhất từ mỗi mini-hull (dùng binary search)
//   - Nếu sau m bước chưa đóng vòng => m quá nhỏ, tăng t
// ============================================================

// Tìm điểm "cực phải" nhất trên mini-hull từ điểm q theo hướng p->q
// Tức là điểm r sao cho tichCoHuong(q, r, điểm_nào_khác) > 0 với mọi điểm khác
// Dùng binary search trên convex polygon
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

// Một vòng Jarvis march với giới hạn m bước, trên tập mini-hulls
// Trả về hull nếu đóng vòng trong m bước, ngược lại trả về rỗng
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

// ============================================================
// MAIN
// ============================================================
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

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

    // ========== CHẠY 4 THUẬT TOÁN ==========
    vector<Diem> hull_andrew = andrew(pts);
    vector<Diem> hull_jarvis = jarvis(pts);
    vector<Diem> hull_graham = graham(pts);
    vector<Diem> hull_chan = chan(pts);

    // In kết quả từng thuật toán
    inBaoLoi("Andrew (Monotone Chain)", hull_andrew);
    inBaoLoi("Jarvis (Gift Wrapping)", hull_jarvis);
    inBaoLoi("Graham Scan", hull_graham);
    inBaoLoi("Chan's Algorithm", hull_chan);

    // ========== BÀI a, b, c dùng hull từ Andrew ==========
    cout << "\n============================================\n";
    cout << "  KET QUA BAI TOAN (su dung bao loi Andrew)\n";
    cout << "============================================\n";

    inDienTich(hull_andrew);
    timKhoangCachNganNhatTrong(hull_andrew, pts);
    timCanhNhoNhat(hull_andrew);

    cout << "\n[Tham khao] Chu vi bao loi: "
         << fixed << setprecision(4) << tinhChuVi(hull_andrew) << "\n";

    cout << "\nNhan Enter de thoat...";
    cin.ignore();
    cin.get();
    return 0;
}

/*
============================================================
HƯỚNG DẪN BIÊN DỊCH VÀ CHẠY
============================================================
  g++ -O2 -o baoloi_full baoloi_full.cpp
  ./baoloi_full

VÍ DỤ INPUT (15 điểm):
  15
  0 0
  1 1
  2 3
  5 0
  5 5
  3 4
  1 4
  4 2
  2 2
  3 1
  0 5
  6 3
  4 5
  6 0
  3 3

============================================================
TÓM TẮT CÁC THUẬT TOÁN
============================================================

1. ANDREW (Monotone Chain) — O(n log n)
   - Sort điểm theo x (rồi y)
   - Xây bao dưới (left→right) và bao trên (right→left)
   - Loại điểm tạo rẽ phải (tích ≤ 0)
   - Ghép lại thành hull CCW

2. JARVIS (Gift Wrapping) — O(n·h)
   - Bắt đầu từ điểm cực trái
   - Mỗi bước: tìm điểm "quay nhiều nhất sang trái"
     (tất cả điểm còn lại nằm bên phải hoặc trên đường thẳng)
   - Dừng khi quay về điểm xuất phát

3. GRAHAM SCAN — O(n log n)
   - Chọn pivot: y nhỏ nhất (rồi x nhỏ nhất)
   - Sắp xếp các điểm còn lại theo góc cực so với pivot
   - Dùng stack: loại điểm tạo rẽ phải (tích ≤ 0)

4. CHAN'S ALGORITHM — O(n log h)
   - Thử từng giá trị m = 2^1, 2^2, 2^3, ...
   - Chia điểm thành ⌈n/m⌉ nhóm, tính mini-hull Graham cho mỗi nhóm
   - Jarvis march: mỗi bước xét 1 ứng viên tốt nhất từ mỗi nhóm
   - Nếu hull đóng vòng trong ≤ m bước → thành công
   - Ngược lại → tăng m và thử lại

============================================================
*/