#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <cctype>

using namespace std;

using Matrix = vector<vector<double>>;

string trim(const string &s)
{
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == string::npos)
        return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

bool is_number(const string &s)
{
    if (s.empty())
        return false;
    for (char ch : s)
    {
        if (!isdigit(static_cast<unsigned char>(ch)))
            return false;
    }
    return true;
}

int find_food_index(const string &input, const vector<string> &keys)
{
    string t = trim(input);
    if (t.empty())
        return -1;

    if (is_number(t))
    {
        int idx = stoi(t);
        if (idx >= 0 && idx < (int)keys.size())
            return idx;
        return -1;
    }

    for (int i = 0; i < (int)keys.size(); ++i)
    {
        if (keys[i] == t)
            return i;
    }
    return -1;
}

Matrix multiply_matrix(const Matrix &A, const Matrix &B)
{
    int n = (int)A.size();
    int m = (int)B[0].size();
    int k = (int)B.size();
    Matrix C(n, vector<double>(m, 0.0));

    for (int i = 0; i < n; ++i)
    {
        for (int t = 0; t < k; ++t)
        {
            if (A[i][t] == 0.0)
                continue;
            double a = A[i][t];
            for (int j = 0; j < m; ++j)
                C[i][j] += a * B[t][j];
        }
    }
    return C;
}

Matrix identity_matrix(int n)
{
    Matrix I(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; ++i)
        I[i][i] = 1.0;
    return I;
}

Matrix power_matrix(Matrix base, int exp)
{
    int n = (int)base.size();
    Matrix result = identity_matrix(n);
    while (exp > 0)
    {
        if (exp & 1)
            result = multiply_matrix(result, base);
        base = multiply_matrix(base, base);
        exp >>= 1;
    }
    return result;
}

vector<double> multiply_vector_matrix(const vector<double> &v, const Matrix &A)
{
    int n = (int)v.size();
    int m = (int)A[0].size();
    vector<double> out(m, 0.0);
    for (int i = 0; i < n; ++i)
    {
        if (v[i] == 0.0)
            continue;
        for (int j = 0; j < m; ++j)
            out[j] += v[i] * A[i][j];
    }
    return out;
}

int main()
{
    int n = 16;
    // (Optional) Nhap du lieu tu ban phim
    // cout << "Nhap so ngay an: ";
    // if (!(cin >> n)) {
    //     cout << "Nhap n khong hop le.\n";
    //     return 0;
    // }
    // cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (n <= 0)
    {
        cout << "Khong co du lieu.\n";
        return 0;
    }

    vector<string> data = {
        "Banh my", "Pho", "Bun", "Pizza", "Banh my", "Pho", "Bun", "Pizza",
        "Pizza", "Banh my", "Banh my", "Pho", "Pho", "Pho", "Bun", "Pho"};
    data.reserve(n);

    // (Optional) Nhap du lieu tu ban phim
    // cout << "Nhap lan luot cac mon an theo thu tu thoi gian (moi dong 1 mon):\n";
    // for (int i = 0; i < n; ++i)
    // {
    //     string food;
    //     getline(cin, food);
    //     if (food.empty())
    //     {
    //         --i;
    //         continue;
    //     }
    //     data.push_back(food);
    // }

    // Tao tap trang thai Q (cac mon khac nhau) theo thu tu xuat hien
    unordered_map<string, int> key_to_idx;
    vector<string> keys;
    keys.reserve(n);

    for (const auto &f : data)
    {
        if (!key_to_idx.count(f))
        {
            int idx = (int)keys.size();
            key_to_idx[f] = idx;
            keys.push_back(f);
        }
    }

    int m = (int)keys.size();
    cout << "\n================= TRANG THAI Q =================\n";
    cout << "Q = { ";
    for (int i = 0; i < m; ++i)
    {
        cout << keys[i];
        if (i + 1 < m)
            cout << ", ";
    }
    cout << " }\n";

    // Dem so lan xuat hien tung mon + dem so lan chuyen A->B (co self-loop cho ngay cuoi)
    vector<int> food_count(m, 0);
    vector<vector<int>> pair_count(m, vector<int>(m, 0));

    for (int i = 0; i < n; ++i)
    {
        int curr = key_to_idx[data[i]];
        food_count[curr]++;

        if (i == n - 1)
        {
            // self-loop cho ngay cuoi (curr -> curr) de hang cuoi van co chuyen trang thai
            pair_count[curr][curr] += 1;
            break;
        }

        int next = key_to_idx[data[i + 1]];
        pair_count[curr][next] += 1;
    }

    // In so lan xuat hien + % (theo tong n ngay)
    cout << "\n========== SO LAN XUAT HIEN TUNG MON ==========\n";
    cout << fixed << setprecision(2);
    for (int i = 0; i < m; ++i)
    {
        double pct = (double)food_count[i] * 100.0 / (double)n;
        cout << setw(20) << keys[i]
             << " : " << setw(6) << food_count[i]
             << " lan  (" << pct << "%)\n";
    }

    // In so lan chuyen A->B + % (theo tong so lan 'hom nay' = food_count[A])
    cout << "\n==== SO LAN XUAT HIEN CAC CAP (A -> B) ====\n";
    cout << "(% tinh theo: so lan A->B / so lan A lam 'hom nay')\n\n";
    for (int i = 0; i < m; ++i)
    {
        cout << "Neu hom nay an \"" << keys[i] << "\" (so lan: " << food_count[i] << "):\n";
        for (int j = 0; j < m; ++j)
        {
            int c = pair_count[i][j];
            double pct = (food_count[i] == 0) ? 0.0 : (double)c * 100.0 / (double)food_count[i];
            cout << "  -> Ngay mai \"" << keys[j] << "\""
                 << " : " << setw(6) << c << " lan"
                 << "  (" << pct << "%)\n";
        }
        cout << "\n";
    }

    // Tao ma tran P (he so xac suat 0..1): P[i][j] = P(ngay mai = j | hom nay = i)
    vector<vector<double>> P(m, vector<double>(m, 0.0));
    for (int i = 0; i < m; ++i)
    {
        if (food_count[i] == 0)
            continue;
        for (int j = 0; j < m; ++j)
        {
            P[i][j] = (double)pair_count[i][j] / (double)food_count[i];
        }
    }

    // In ma tran P
    cout << "\n=========== MA TRAN CHUYEN TRANG THAI P ===========\n";
    cout << "(don vi: he so xac suat 0..1, vd 10% = 0.10)\n\n";
    cout << fixed << setprecision(4);

    cout << setw(20) << "Hom nay/Ngay mai";
    for (int j = 0; j < m; ++j)
        cout << setw(15) << keys[j];
    cout << "\n";
    cout << string(20 + 15 * m, '-') << "\n";

    for (int i = 0; i < m; ++i)
    {
        cout << setw(20) << keys[i];
        for (int j = 0; j < m; ++j)
            cout << setw(15) << P[i][j];
        cout << "\n";
    }
    cout << "\n";

    //(Optional) Kiem tra tong hang ~= 1.0
    cout << "Tong xac suat tung hang (~1.0):\n";
    for (int i = 0; i < m; ++i)
    {
        double s = 0.0;
        for (int j = 0; j < m; ++j)
            s += P[i][j];
        cout << "  " << setw(20) << keys[i] << " : " << fixed << setprecision(4) << s
             << " (so lan lam 'hom nay': " << food_count[i] << ")\n";
    }
    cout << "\n";

    // Chon mon hien tai va buoc nhay thoi gian k
    cout << "================ CHON THAM SO DU DOAN ================\n";
    cout << "Danh sach mon an (chi so -> ten mon):\n";
    for (int i = 0; i < m; ++i)
        cout << "  " << i << " -> " << keys[i] << "\n";

    string selection;
    int curr_idx = -1;
    while (curr_idx < 0)
    {
        cout << "Nhap ten mon hoac chi so (0-" << (m - 1) << "): ";
        getline(cin, selection);
        curr_idx = find_food_index(selection, keys);
        if (curr_idx < 0)
            cout << "Lua chon khong hop le, vui long nhap lai.\n";
    }

    int steps = 0;
    while (steps <= 0)
    {
        string line;
        cout << "Nhap so buoc thoi gian (k >= 1): ";
        getline(cin, line);
        line = trim(line);
        if (!is_number(line))
        {
            cout << "Gia tri k khong hop le, vui long nhap lai.\n";
            continue;
        }
        steps = stoi(line);
        if (steps <= 0)
            cout << "Gia tri k phai >= 1.\n";
    }

    // P^k va phan phoi sau k buoc
    Matrix Pk = power_matrix(P, steps);
    vector<double> init(m, 0.0);
    init[curr_idx] = 1.0;
    vector<double> dist = multiply_vector_matrix(init, Pk);

    cout << "\n=========== PHAN PHOI SAU " << steps << " BUOC ===========\n";
    cout << fixed << setprecision(4);
    for (int i = 0; i < m; ++i)
    {
        double pct = dist[i] * 100.0;
        cout << setw(20) << keys[i] << " : " << dist[i] << "  (" << fixed << setprecision(2) << pct << "%)\n";
        cout << fixed << setprecision(4);
    }

    int best_idx = (int)(max_element(dist.begin(), dist.end()) - dist.begin());
    double best_p = dist[best_idx];
    double best_pct = best_p * 100.0;

    cout << "================ KET LUAN ================\n";
    cout << "Mon an duoc chon: " << keys[curr_idx] << "\n";
    cout << "Sau " << steps << " buoc, mon an co kha nang cao nhat la \"" << keys[best_idx]
         << "\" voi kha nang xay ra khoang "
         << fixed << setprecision(4) << best_p
         << "  (" << fixed << setprecision(2) << best_pct << "%)\n";

    return 0;
}
