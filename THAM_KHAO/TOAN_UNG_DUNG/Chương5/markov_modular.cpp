#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <iomanip>
#include <limits>
#include <random>

using namespace std;

struct MarkovModel {
    // Du lieu goc
    vector<string> data;                         // Chuoi mon an theo thoi gian
    // Trang thai
    vector<string> states;                       // Tap trang thai Q (thu tu xuat hien)
    unordered_map<string, int> idx;              // mon an -> chi so trong Q
    // Thong ke
    vector<int> food_count;                      // so lan xuat hien tung trang thai
    vector<vector<int>> pair_count;              // so lan chuyen A->B
    // Ma tran chuyen trang thai
    vector<vector<double>> P;                    // he so xac suat (0..1)
};

//Doc input
static bool readData(vector<string>& data) {
    int n;
    cout << "Nhap so ngay an: ";
    if (!(cin >> n)) {
        cout << "Nhap n khong hop le.\n";
        return false;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (n <= 0) {
        cout << "Khong co du lieu.\n";
        return false;
    }

    data.clear();
    data.reserve(n);

    cout << "Nhap lan luot cac mon an theo thu tu thoi gian (moi dong 1 mon):\n";
    for (int i = 0; i < n; ++i) {
        string food;
        getline(cin, food);
        if (food.empty()) { --i; continue; }
        data.push_back(food);
    }
    return true;
}


// Xay dung tap trang thai Q 
static void buildStates(MarkovModel& model) {
    model.idx.clear();
    model.states.clear();
    model.states.reserve(model.data.size());

    for (const auto& f : model.data) {
        if (!model.idx.count(f)) {
            int id = (int)model.states.size();
            model.idx[f] = id;
            model.states.push_back(f);
        }
    }
}

static void printStatesQ(const MarkovModel& model) {
    cout << "\n================= TRANG THAI Q =================\n";
    cout << "Q = { ";
    for (int i = 0; i < (int)model.states.size(); ++i) {
        cout << model.states[i];
        if (i + 1 < (int)model.states.size()) cout << ", ";
    }
    cout << " }\n";
}

//Dem so lan xuat hien + dem cap A->B 
static void countOccurrences(MarkovModel& model, bool self_loop_last = true) {
    int n = (int)model.data.size();
    int m = (int)model.states.size();

    model.food_count.assign(m, 0);
    model.pair_count.assign(m, vector<int>(m, 0));

    for (int i = 0; i < n; ++i) {
        int curr = model.idx[model.data[i]];
        model.food_count[curr]++;

        if (i == n - 1) {
            if (self_loop_last) {
                model.pair_count[curr][curr] += 1;
            }
            break;
        }

        int next = model.idx[model.data[i + 1]];
        model.pair_count[curr][next] += 1;
    }
}



// Xay dung ma tran P (he so 0..1)
static void buildMatrixP(MarkovModel& model) {
    int m = (int)model.states.size();
    model.P.assign(m, vector<double>(m, 0.0));

    for (int i = 0; i < m; ++i) {
        if (model.food_count[i] == 0) continue;
        for (int j = 0; j < m; ++j) {
            model.P[i][j] = (double)model.pair_count[i][j] / (double)model.food_count[i]; // 10% -> 0.10
        }
    }
}

static void printMatrixP(const MarkovModel& model) {
    int m = (int)model.states.size();

    cout << "\n=========== MA TRAN CHUYEN TRANG THAI P ===========\n";
    cout << "(don vi: he so xac suat 0..1, vd 10% = 0.10)\n\n";
    cout << fixed << setprecision(4);

    cout << setw(20) << "Hom nay/Ngay mai";
    for (int j = 0; j < m; ++j) cout << setw(15) << model.states[j];
    cout << "\n";
    cout << string(20 + 15 * m, '-') << "\n";

    for (int i = 0; i < m; ++i) {
        cout << setw(20) << model.states[i];
        for (int j = 0; j < m; ++j) cout << setw(15) << model.P[i][j];
        cout << "\n";
    }
    cout << "\n";
}



int main() {
    MarkovModel model;

    if (!readData(model.data)) return 0;

    //Xay dung Q + in Q
    buildStates(model);
    printStatesQ(model);
    //Dem so lan xuat hien + cap A->B
    countOccurrences(model, /*self_loop_last=*/true);
    //Xay dung + in ma tran P
    buildMatrixP(model);
    printMatrixP(model);


  

    return 0;
}
