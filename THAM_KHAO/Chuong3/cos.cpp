#include <bits/stdc++.h>
using namespace std;

static const int D = 10;

struct Point {
    array<double, D> x{};
    int id = -1; 
};

double dotP(const Point& a, const Point& b) {
    double s = 0.0;
    for (int i = 0; i < D; ++i) s += a.x[i] * b.x[i];
    return s;
}

double norm2(const Point& p) {
    double s = 0.0;
    for (double v : p.x) s += v * v;
    return s;
}

double dist2(const Point& a, const Point& b) {
    double s = 0.0;
    for (int i = 0; i < D; ++i) {
        double d = a.x[i] - b.x[i];
        s += d * d;
    }
    return s;
}

// Cosine chuẩn (chưa chuẩn hoá)
double cosineSimilarity_raw(const Point& a, const Point& b) {
    double d = dotP(a, b);
    double na = sqrt(norm2(a));
    double nb = sqrt(norm2(b));
    if (na == 0.0 || nb == 0.0) return 0.0;
    return d / (na * nb);
}

// Chuẩn hoá về vector đơn vị
Point normalizePoint(const Point& p) {
    Point u = p;
    double n = sqrt(norm2(p));
    if (n == 0.0) return u;
    for (int i = 0; i < D; ++i) u.x[i] /= n;
    return u;
}

struct KDNode {
    Point p;
    int axis;
    KDNode *l = nullptr, *r = nullptr;
    KDNode(const Point& _p, int _axis) : p(_p), axis(_axis) {}
};

KDNode* buildKD(vector<Point>& pts, int l, int r, int depth) {
    if (l > r) return nullptr;
    int axis = depth % D;
    int m = (l + r) / 2;

    nth_element(pts.begin() + l, pts.begin() + m, pts.begin() + r + 1,
        [&](const Point& a, const Point& b) { return a.x[axis] < b.x[axis]; });

    KDNode* node = new KDNode(pts[m], axis);
    node->l = buildKD(pts, l, m - 1, depth + 1);
    node->r = buildKD(pts, m + 1, r, depth + 1);
    return node;
}

void nearestSearch(KDNode* node, const Point& target, int forbidId,
                   Point& bestP, double& bestD2) {
    if (!node) return;

    double d2 = dist2(node->p, target);
    if (node->p.id != forbidId && d2 < bestD2) {
        bestD2 = d2;
        bestP = node->p;
    }

    int ax = node->axis;
    double diff = target.x[ax] - node->p.x[ax];

    KDNode* first  = (diff < 0 ? node->l : node->r);
    KDNode* second = (diff < 0 ? node->r : node->l);

    nearestSearch(first, target, forbidId, bestP, bestD2);
    if (diff * diff < bestD2) {
        nearestSearch(second, target, forbidId, bestP, bestD2);
    }
}

vector<Point> readCSV_10D(const string& filename) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "Khong mo duoc file: " << filename << "\n";
        return {};
    }

    vector<Point> pts;
    string line;
    int id = 0;

    while (getline(fin, line)) {
        if (line.empty()) continue;

        // thay ',' -> ' '
        for (char& c : line) if (c == ',') c = ' ';
        stringstream ss(line);

        // thử đọc 10 số; nếu fail (vd header x1 x2...) thì bỏ qua
        array<double, D> a{};
        bool ok = true;
        for (int i = 0; i < D; ++i) {
            if (!(ss >> a[i])) { ok = false; break; }
        }
        if (!ok) continue; // bỏ header / dòng lỗi

        Point p;
        p.id = id++;
        p.x = a;
        pts.push_back(p);
    }
    return pts;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string filename = "B.scv";
    vector<Point> raw = readCSV_10D(filename);

    if ((int)raw.size() == 0) {
        cout << "Khong doc duoc du lieu tu B.csv!\n";
        return 0;
    }

    // Chuẩn hoá
    vector<Point> unit = raw;
    for (auto& p : unit) p = normalizePoint(p);

    // Build KD-tree (copy vì build dùng nth_element)
    vector<Point> buildPts = unit;
    KDNode* root = buildKD(buildPts, 0, (int)buildPts.size() - 1, 0);

    // Tìm cặp có cosine lớn nhất:
    // vì đã chuẩn hoá => cosine = dot
    double bestCos = -1e300;
    pair<int,int> bestPair = {-1, -1};

    for (const auto& u : unit) {
        Point bestN; bestN.id = -1;
        double bestD2 = 1e300;

        nearestSearch(root, u, u.id, bestN, bestD2);
        if (bestN.id == -1) continue;

        double cosv = dotP(u, bestN); // cosine vì unit vectors
        if (cosv > bestCos) {
            bestCos = cosv;
            bestPair = {u.id, bestN.id};
        }
    }

    cout.setf(std::ios::fixed);
    cout << setprecision(6);

    cout << "So diem doc duoc: " << raw.size() << " (10 chieu)\n";
    cout << "Cap diem co Cosine lon nhat (1-based): "
         << bestPair.first + 1 << " va " << bestPair.second + 1 << "\n";
    cout << "Cosine max = " << bestCos << "\n\n";

    auto printPoint = [&](int idx) {
        cout << "Diem " << (idx + 1) << ": ";
        for (int j = 0; j < D; ++j) {
            cout << raw[idx].x[j] << (j + 1 < D ? ", " : "");
        }
        cout << "\n";
    };

    if (bestPair.first != -1) {
        printPoint(bestPair.first);
        printPoint(bestPair.second);
    }

    return 0;
}





// // độ đo 2 đối tượng
// #include <iostream>
// #include <vector>
// #include <cmath>
// #include <iomanip>
// using namespace std;

// /* Tích vô hướng */
// double dotProduct(const vector<double>& A, const vector<double>& B) {
//     double s = 0;
//     for (int i = 0; i < A.size(); i++)
//         s += A[i] * B[i];
//     return s;
// }

// /* Chuẩn (độ dài vector) */
// double norm(const vector<double>& A) {
//     double s = 0;
//     for (double x : A)
//         s += x * x;
//     return sqrt(s);
// }

// /* Khoảng cách Euclid */
// double euclidDistance(const vector<double>& A, const vector<double>& B) {
//     double s = 0;
//     for (int i = 0; i < A.size(); i++) {
//         double d = A[i] - B[i];
//         s += d * d;
//     }
//     return sqrt(s);
// }

// /* Cosine similarity */
// double cosineSimilarity(const vector<double>& A, const vector<double>& B) {
//     double na = norm(A);
//     double nb = norm(B);
//     if (na == 0 || nb == 0) return 0;
//     return dotProduct(A, B) / (na * nb);
// }

// int main() {
//     int n;
//     cout << "Nhap so chieu n = ";
//     cin >> n;

//     vector<double> A(n), B(n);

//     cout << "Nhap doi tuong A:\n";
//     for (int i = 0; i < n; i++)
//         cin >> A[i];

//     cout << "Nhap doi tuong B:\n";
//     for (int i = 0; i < n; i++)
//         cin >> B[i];

//     cout << fixed << setprecision(6);

//     cout << "\nKhoang cach Euclid = "
//          << euclidDistance(A, B) << "\n";

//     cout << "Cosine similarity = "
//          << cosineSimilarity(A, B) << "\n";

//     return 0;
// }
