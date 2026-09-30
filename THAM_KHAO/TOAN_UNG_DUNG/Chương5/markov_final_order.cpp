#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <iomanip>
#include <limits>
#include <random>

using namespace std;

int main() {
    int n;
    cout << "Nhap so ngay an: ";
    if (!(cin >> n)) {
        cout << "Nhap n khong hop le.\n";
        return 0;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (n <= 0) {
        cout << "Khong co du lieu.\n";
        return 0;
    }

    vector<string> data;
    data.reserve(n);

    cout << "Nhap lan luot cac mon an theo thu tu thoi gian (moi dong 1 mon):\n";
    for (int i = 0; i < n; ++i) {
        string food;
        getline(cin, food);
        if (food.empty()) { --i; continue; }
        data.push_back(food);
    }


    //Tao tap trang thai Q (cac mon khac nhau) theo thu tu xuat hien
    unordered_map<string, int> key_to_idx;
    vector<string> keys;
    keys.reserve(n);

    for (const auto &f : data) {
        if (!key_to_idx.count(f)) {
            int idx = (int)keys.size();
            key_to_idx[f] = idx;
            keys.push_back(f);
        }
    }

    int m = (int)keys.size();
    cout << "\n================= TRANG THAI Q =================\n";
    cout << "Q = { ";
    for (int i = 0; i < m; ++i) {
        cout << keys[i];
        if (i + 1 < m) cout << ", ";
    }
    cout << " }\n";

    //Dem so lan xuat hien tung mon + dem so lan chuyen A->B (co self-loop cho ngay cuoi)
    vector<int> food_count(m, 0);
    vector<vector<int>> pair_count(m, vector<int>(m, 0));

    for (int i = 0; i < n; ++i) {
        int curr = key_to_idx[data[i]];
        food_count[curr]++;

        if (i == n - 1) {
            // self-loop cho ngay cuoi (curr -> curr) de hang cuoi van co chuyen trang thai
            pair_count[curr][curr] += 1;
            break;
        }

        int next = key_to_idx[data[i + 1]];
        pair_count[curr][next] += 1;
    }

    //In so lan xuat hien + % (theo tong n ngay)
    cout << "\n========== SO LAN XUAT HIEN TUNG MON ==========\n";
    cout << fixed << setprecision(2);
    for (int i = 0; i < m; ++i) {
        double pct = (double)food_count[i] * 100.0 / (double)n;
        cout << setw(20) << keys[i]
             << " : " << setw(6) << food_count[i]
             << " lan  (" << pct << "%)\n";
    }

    //In so lan chuyen A->B + % (theo tong so lan 'hom nay' = food_count[A])
    cout << "\n==== SO LAN XUAT HIEN CAC CAP (A -> B) ====\n";
    cout << "(% tinh theo: so lan A->B / so lan A lam 'hom nay')\n\n";
    for (int i = 0; i < m; ++i) {
        cout << "Neu hom nay an \"" << keys[i] << "\" (so lan: " << food_count[i] << "):\n";
        for (int j = 0; j < m; ++j) {
            int c = pair_count[i][j];
            double pct = (food_count[i] == 0) ? 0.0 : (double)c * 100.0 / (double)food_count[i];
            cout << "  -> Ngay mai \"" << keys[j] << "\""
                 << " : " << setw(6) << c << " lan"
                 << "  (" << pct << "%)\n";
        }
        cout << "\n";
    }

    //Tao ma tran P (he so xac suat 0..1): P[i][j] = P(ngay mai = j | hom nay = i)
    vector<vector<double>> P(m, vector<double>(m, 0.0));
    for (int i = 0; i < m; ++i) {
        if (food_count[i] == 0) continue;
        for (int j = 0; j < m; ++j) {
            P[i][j] = (double)pair_count[i][j] / (double)food_count[i];
        }
    }

    //In ma tran P
    cout << "\n=========== MA TRAN CHUYEN TRANG THAI P ===========\n";
    cout << "(don vi: he so xac suat 0..1, vd 10% = 0.10)\n\n";
    cout << fixed << setprecision(4);

    cout << setw(20) << "Hom nay/Ngay mai";
    for (int j = 0; j < m; ++j) cout << setw(15) << keys[j];
    cout << "\n";
    cout << string(20 + 15 * m, '-') << "\n";

    for (int i = 0; i < m; ++i) {
        cout << setw(20) << keys[i];
        for (int j = 0; j < m; ++j) cout << setw(15) << P[i][j];
        cout << "\n";
    }
    cout << "\n";

    //(Optional) Kiem tra tong hang ~= 1.0
    cout << "Tong xac suat tung hang (~1.0):\n";
    for (int i = 0; i < m; ++i) {
        double s = 0.0;
        for (int j = 0; j < m; ++j) s += P[i][j];
        cout << "  " << setw(20) << keys[i] << " : " << fixed << setprecision(4) << s
             << " (so lan lam 'hom nay': " << food_count[i] << ")\n";
    }
    cout << "\n";

    //Ket luan: du doan mon ngay mai dua tren mon cuoi (np.random.choice tuong duong)
    string curr_food = data.back();
    int curr_idx = key_to_idx[curr_food];

    double sum_row = 0.0;
    for (double v : P[curr_idx]) sum_row += v;
    if (sum_row <= 0.0) {
        cout << "================ KET LUAN ================\n";
        cout << "Mon an hom truoc: " << curr_food << "\n";
        cout << "Khong du du lieu de du doan mon ngay mai.\n";
        return 0;
    }

    random_device rd;
    mt19937 gen(rd());
    discrete_distribution<int> dist(P[curr_idx].begin(), P[curr_idx].end());

    int predicted_idx = dist(gen);
    string predicted_food = keys[predicted_idx];
    double predicted_p = P[curr_idx][predicted_idx];
    double predicted_percent = predicted_p * 100.0;

    cout << "================ KET LUAN ================\n";
    cout << "Mon an chung ta an hom truoc: " << curr_food << "\n";
    cout << "Mon an nen an vao hom nay la \"" << predicted_food
         << "\" voi kha nang xay ra khoang "
         << fixed << setprecision(4) << predicted_p
         << "  (" << fixed << setprecision(2) << predicted_percent << "%)\n";

    return 0;
}
