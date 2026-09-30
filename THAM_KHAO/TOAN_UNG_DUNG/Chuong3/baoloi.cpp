/*#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
using namespace std;

struct Diem {
    int x, y;

    bool operator<(const Diem& diem_khac) const {
        return (x < diem_khac.x) || (x == diem_khac.x && y < diem_khac.y);
    }
};

// Tích có hướng
int tichcohuong(const Diem& goc, const Diem& a, const Diem& b) {
    return (a.x - goc.x) * (b.y - goc.y) - (a.y - goc.y) * (b.x - goc.x);
}

// Bao lồi (Monotone chain)
vector<Diem> timbaoloi(vector<Diem>& tap_diem) {
    int n = tap_diem.size();
    if (n <= 1) return tap_diem;
    sort(tap_diem.begin(), tap_diem.end());
    vector<Diem> bao_duoi, bao_tren;
    // Bao dưới
    for (const auto& diem : tap_diem) {
        while (bao_duoi.size() >= 2 && tichcohuong(bao_duoi[bao_duoi.size()-2], bao_duoi[bao_duoi.size()-1], diem) <= 0) {
            bao_duoi.pop_back();
        }
        bao_duoi.push_back(diem);
    }
    // Bao trên
    for (int i = n - 1; i >= 0; i--) {
        const Diem& diem = tap_diem[i];
        while (bao_tren.size() >= 2 && tichcohuong(bao_tren[bao_tren.size()-2], bao_tren[bao_tren.size()-1], diem) <= 0) {
            bao_tren.pop_back();
        }
        bao_tren.push_back(diem);
    }
    // Xóa điểm trùng
    bao_duoi.pop_back();
    bao_tren.pop_back();
    // Ghép 2 bao
    bao_duoi.insert(bao_duoi.end(), bao_tren.begin(), bao_tren.end());
    return bao_duoi;
}

// In các điểm
void in(const vector<Diem>& bao_loi) {
    cout << "\nCac diem thuoc bao loi theo thu tu:\n";
    for (const auto& diem : bao_loi) {
        cout << diem.x << " " << diem.y << "\n";
    }
}

// Tính diện tích bao lồi (công thức Shoelace)
double tinhDienTich(const vector<Diem>& bao_loi) {
    double S = 0;
    int n = bao_loi.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        S += (bao_loi[i].x * bao_loi[j].y - bao_loi[j].x * bao_loi[i].y);
    }
    return fabs(S) / 2.0;
}

// Tính khoảng cách giữa 2 điểm
double khoangCach(const Diem& a, const Diem& b) {
    return sqrt((a.x - b.x) * 1.0 * (a.x - b.x) + (a.y - b.y) * 1.0 * (a.y - b.y));
}

// Tìm 2 điểm gần nhất trên bao lồi
pair<Diem, Diem> timDiemGanNhat(const vector<Diem>& bao_loi) {
    double minDist = numeric_limits<double>::infinity();
    pair<Diem, Diem> ketqua;
    int n = bao_loi.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double d = khoangCach(bao_loi[i], bao_loi[j]);
            if (d < minDist) {
                minDist = d;
                ketqua = {bao_loi[i], bao_loi[j]};
            }
        }
    }
    return ketqua;
}

int main() {
    int n;
    cout << "Nhap so luong diem: ";
    cin >> n;
    vector<Diem> tap_diem(n);
    cout << "Nhap toa do cac diem (x y):\n";
    for (int i = 0; i < n; ++i) {
        cin >> tap_diem[i].x >> tap_diem[i].y;
    }

    vector<Diem> bao_loi = timbaoloi(tap_diem);
    in(bao_loi);

    // Tính diện tích bao lồi
    double dientich = tinhDienTich(bao_loi);
    cout << "\nDien tich bao loi: " << dientich << endl;

    // Tìm 2 điểm gần nhất
    auto capGanNhat = timDiemGanNhat(bao_loi);
    cout << "Hai diem gan nhat tren bao loi: ("
         << capGanNhat.first.x << "," << capGanNhat.first.y << ") va ("
         << capGanNhat.second.x << "," << capGanNhat.second.y << ")\n";
    cout << "Khoang cach = " << khoangCach(capGanNhat.first, capGanNhat.second) << endl;

    return 0;
}
*/







#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
using namespace std;

struct Diem {
    int x, y;

    bool operator<(const Diem& diem_khac) const {
        return (x < diem_khac.x) || (x == diem_khac.x && y < diem_khac.y);
    }
};

// Tích có hướng
long long tichcohuong(const Diem& goc, const Diem& a, const Diem& b) {
    return 1LL * (a.x - goc.x) * (b.y - goc.y) - 1LL * (a.y - goc.y) * (b.x - goc.x);
}

// Bao lồi
vector<Diem> timbaoloi(vector<Diem>& tap_diem) {
    int n = (int)tap_diem.size();
    if (n <= 1) return tap_diem;
    sort(tap_diem.begin(), tap_diem.end());
    vector<Diem> bao_duoi, bao_tren;

    // Bao dưới
    for (const auto& diem : tap_diem) {
        while (bao_duoi.size() >= 2 &&
               tichcohuong(bao_duoi[bao_duoi.size()-2], bao_duoi[bao_duoi.size()-1], diem) <= 0) {
            bao_duoi.pop_back();
        }
        bao_duoi.push_back(diem);
    }

    // Bao trên
    for (int i = n - 1; i >= 0; i--) {
        const Diem& diem = tap_diem[i];
        while (bao_tren.size() >= 2 &&
               tichcohuong(bao_tren[bao_tren.size()-2], bao_tren[bao_tren.size()-1], diem) <= 0) {
            bao_tren.pop_back();
        }
        bao_tren.push_back(diem);
    }
    // xóa trùng
    bao_duoi.pop_back();
    bao_tren.pop_back();
    //ghép 2 bao lại
    bao_duoi.insert(bao_duoi.end(), bao_tren.begin(), bao_tren.end());
    return bao_duoi; // CCW
}

// In các điểm
void in(const vector<Diem>& bao_loi) {
    cout << "\nCac diem thuoc bao loi theo thu tu:\n";
    for (const auto& diem : bao_loi) {
        cout << diem.x << " " << diem.y << "\n";
    }
}

// Tính diện tích bao lồi (Shoelace)
double tinhDienTich(const vector<Diem>& bao_loi) {
    if (bao_loi.size() < 3) return 0.0;
    double S = 0;
    int n = (int)bao_loi.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        S += (1.0 * bao_loi[i].x * bao_loi[j].y - 1.0 * bao_loi[j].x * bao_loi[i].y);
    }
    return fabs(S) / 2.0;
}

// Tính khoảng cách giữa 2 điểm
double khoangCach(const Diem& a, const Diem& b) {
    return sqrt((a.x - b.x) * 1.0 * (a.x - b.x) + (a.y - b.y) * 1.0 * (a.y - b.y));
}

// Tìm 2 điểm gần nhất trên bao lồi
pair<Diem, Diem> timDiemGanNhat(const vector<Diem>& bao_loi) {
    double minDist = numeric_limits<double>::infinity(); //nếu max thì khởi tạo bằng -numeric(thêm dấu trừ) 
    pair<Diem, Diem> ketqua;
    int n = (int)bao_loi.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double d = khoangCach(bao_loi[i], bao_loi[j]);
            if (d < minDist) {      //đổi dấu
                minDist = d;        //max=d
                ketqua = {bao_loi[i], bao_loi[j]};
            }
        }
    }
    return ketqua;
}


//Điểm phía trong bao lồi
// Kiểm tra điểm p có nằm trên đoạn ab không
bool namTrenDoan(const Diem& a, const Diem& b, const Diem& p) {
    if (tichcohuong(a, b, p) != 0) return false; // không thẳng hàng
    return (min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
            min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y));
}

// Kiểm tra p nằm trong đa giác lồi
// includeBoundary = true  => tính cả điểm nằm trên biên là "trong"
// includeBoundary = false => chỉ tính điểm nằm hẳn bên trong (không trên biên)
bool namTrongDaGiacLoi(const vector<Diem>& poly, const Diem& p, bool includeBoundary) {
    int n = (int)poly.size();
    if (n < 3) return false;
    bool coDuong = false, coAm = false;
    for (int i = 0; i < n; i++) {
        Diem a = poly[i];
        Diem b = poly[(i + 1) % n];
        long long c = tichcohuong(a, b, p);
        if (c == 0) {
            if (namTrenDoan(a, b, p)) return includeBoundary;
            // thẳng hàng nhưng ngoài đoạn => chắc chắn ngoài
            return false;
        }
        if (c > 0) coDuong = true;
        else coAm = true;

        if (coDuong && coAm) return false; // khác dấu => ngoài
    }
    return true; // cùng dấu hết => trong
}

// Tính chu vi bao lồi
double tinhChuVi(const vector<Diem>& bao_loi) {
    int n = (int)bao_loi.size();
    if (n < 2) return 0.0;

    double chuvi = 0.0;
    for (int i = 0; i < n; i++) {
        chuvi += khoangCach(bao_loi[i], bao_loi[(i + 1) % n]);
    }
    return chuvi;
}



int main() {
    int n;
    cout << "Nhap so luong diem: ";
    cin >> n;
    vector<Diem> tap_diem(n);
    cout << "Nhap toa do cac diem (x y):\n";
    for (int i = 0; i < n; ++i) {
        cin >> tap_diem[i].x >> tap_diem[i].y;
    }
    // Lưu lại danh sách điểm gốc để xét "điểm trong"
    vector<Diem> diem_goc = tap_diem;
    vector<Diem> bao_loi = timbaoloi(tap_diem);
    in(bao_loi);
    //diện tích
    double dientich = tinhDienTich(bao_loi);
    cout << "\nDien tich bao loi: " << dientich << endl;
    // Tìm 2 điểm gần nhất
    auto capGanNhat = timDiemGanNhat(bao_loi);       //nếu tìm xa nhất chỉ đổi tên hàm và tên các biến capGanNhat
    cout << "Hai diem gan nhat tren bao loi: ("
         << capGanNhat.first.x << "," << capGanNhat.first.y << ") va ("
         << capGanNhat.second.x << "," << capGanNhat.second.y << ")\n";
    cout << "Khoang cach = " << khoangCach(capGanNhat.first, capGanNhat.second) << endl;
    //đếm & liệt kê điểm nằm TRONG bao lồi
    bool tinhCaDiemTrenBien = false; // đổi thành true nếu muốn tính cả điểm trên biên
    vector<Diem> diem_trong;
    for (const auto& p : diem_goc) {
        if (namTrongDaGiacLoi(bao_loi, p, tinhCaDiemTrenBien)) {
            // nếu tinhCaDiemTrenBien=false thì điểm trên biên sẽ không được tính
            diem_trong.push_back(p);
        }
    }
    cout << "\nSo luong diem nam " << (tinhCaDiemTrenBien ? "trong hoac tren bien" : "hoan toan ben trong")
         << " bao loi: " << diem_trong.size() << "\n";
    cout << "Danh sach cac diem do:\n";
    for (auto &p : diem_trong) {
        cout << p.x << " " << p.y << "\n";
    }

    //chuvi
    double chuvi = tinhChuVi(bao_loi);
cout << "Chu vi bao loi: " << chuvi << endl;


    return 0;
}










/*
.**Sắpxếp điểm**:Sắp xếpcácđiểmtheotọađộ\(x\)tăngdần(nếu\(x \)bằngnhauthìtheo\(y\)).
2.**Xâybaodưới**:-Duyệttừđiểm tráinhất,thêmđiểmmớinếu tạo"rẽtrái"(tíchcó hướng>0).-Nếutạo "rẽphải"hoặc thẳnghàng(tích≤0),loạibỏđiểmcuốivàkiểm tralại.
3.**Xâybaotrên**:-Duyệtngượctừđiểm phảinhất,thêmđiểm mớinếutạo "rẽtrái"(tíchcóhướng>0).-Nếutạo "rẽphải"hoặc thẳnghàng(tích≤0),loạibỏđiểmcuốivàkiểm tralại.
4.**Kếthợp**: Nốibaodướivàbaotrên,xóahaiđiểmtrùngở đầu/cuối.
5.**Kếtquả**: Danhsáchđỉnhbaolồi theothứ tự ngược chiều kimđồnghồ.*/