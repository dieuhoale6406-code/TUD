#include <iostream>
#include <vector>
#include <complex>
#include <iomanip>
#include <cmath>
// cd "c:\Users\Acer\Desktop\Thi TUD\Code\De3\" ; if ($?) { g++ -I "D:\download\TaiChuaBiet\eigen-3.4.0\eigen-3.4.0" D3_cau5.cpp -o D3_cau5 } ; if ($?) { .\D3_cau5 }
// Chỉ dùng Eigen để tính trị riêng và vector riêng
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>

using namespace std;

typedef complex<double> SoPhuc;
typedef vector<vector<double>> MaTranThuc;
typedef vector<vector<SoPhuc>> MaTranPhuc;
typedef vector<SoPhuc> VectorPhuc;

const double EPS = 1e-9;

// ===============================
// Tạo ma trận phức toàn số 0
// ===============================
MaTranPhuc taoMaTranPhuc(int soHang, int soCot) {
    return MaTranPhuc(soHang, vector<SoPhuc>(soCot, SoPhuc(0, 0)));
}

// ===============================
// In ma trận phức, chỉ in phần thực
// Vì phần ảo rất nhỏ chỉ là sai số tính toán
// ===============================
void inMaTranPhuc(MaTranPhuc maTran) {
    int soHang = maTran.size();
    int soCot = maTran[0].size();

    for (int i = 0; i < soHang; i++) {
        for (int j = 0; j < soCot; j++) {
            cout << setw(12) << maTran[i][j].real() << " ";
        }
        cout << endl;
    }
}

// ===============================
// In vector phức, chỉ in phần thực
// ===============================
void inVectorPhuc(VectorPhuc vectorKetQua) {
    for (int i = 0; i < vectorKetQua.size(); i++) {
        cout << vectorKetQua[i].real() << " ";
    }
}

// ===============================
// Nhân hai ma trận phức
// ketQua = A * B
// ===============================
MaTranPhuc nhanMaTran(MaTranPhuc A, MaTranPhuc B) {
    int soHangA = A.size();
    int soCotA = A[0].size();
    int soCotB = B[0].size();

    MaTranPhuc ketQua = taoMaTranPhuc(soHangA, soCotB);

    for (int i = 0; i < soHangA; i++) {
        for (int j = 0; j < soCotB; j++) {
            for (int k = 0; k < soCotA; k++) {
                ketQua[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return ketQua;
}

// ===============================
// Nhân vector hàng với ma trận
// ketQua = vectorHang * maTran
// ===============================
VectorPhuc nhanVectorHangVoiMaTran(VectorPhuc vectorHang, MaTranPhuc maTran) {
    int soCot = maTran[0].size();
    int soPhanTu = vectorHang.size();

    VectorPhuc ketQua(soCot, SoPhuc(0, 0));

    for (int j = 0; j < soCot; j++) {
        for (int k = 0; k < soPhanTu; k++) {
            ketQua[j] += vectorHang[k] * maTran[k][j];
        }
    }

    return ketQua;
}

// ===============================
// Tính nghịch đảo ma trận phức
// Dùng Gauss-Jordan
// ===============================
MaTranPhuc nghichDaoMaTran(MaTranPhuc maTran) {
    int n = maTran.size();

    MaTranPhuc moRong = taoMaTranPhuc(n, 2 * n);

    // Tạo ma trận mở rộng [A | I]
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            moRong[i][j] = maTran[i][j];
        }

        for (int j = n; j < 2 * n; j++) {
            if (j - n == i) {
                moRong[i][j] = SoPhuc(1, 0);
            } else {
                moRong[i][j] = SoPhuc(0, 0);
            }
        }
    }

    // Khử Gauss-Jordan
    for (int cot = 0; cot < n; cot++) {
        int dongChon = cot;

        // Chọn dòng có trị tuyệt đối lớn nhất để tránh sai số
        for (int i = cot + 1; i < n; i++) {
            if (abs(moRong[i][cot]) > abs(moRong[dongChon][cot])) {
                dongChon = i;
            }
        }

        if (abs(moRong[dongChon][cot]) < EPS) {
            cout << "Ma tran vector rieng khong kha nghich." << endl;
            cout << "Khong the cheo hoa ma tran P." << endl;
            exit(1);
        }

        swap(moRong[cot], moRong[dongChon]);

        SoPhuc phanTuChot = moRong[cot][cot];

        // Chia cả dòng cho phần tử chốt
        for (int j = 0; j < 2 * n; j++) {
            moRong[cot][j] /= phanTuChot;
        }

        // Khử các dòng khác
        for (int i = 0; i < n; i++) {
            if (i != cot) {
                SoPhuc heSo = moRong[i][cot];

                for (int j = 0; j < 2 * n; j++) {
                    moRong[i][j] -= heSo * moRong[cot][j];
                }
            }
        }
    }

    // Lấy phần bên phải, tức A^-1
    MaTranPhuc nghichDao = taoMaTranPhuc(n, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            nghichDao[i][j] = moRong[i][j + n];
        }
    }

    return nghichDao;
}

// ===============================
// Lấy trị riêng và vector riêng bằng Eigen
// Chỉ dùng Eigen trong hàm này
// ===============================
void layTriRiengVaVectorRieng(
    MaTranThuc maTranChuyen,
    VectorPhuc &triRieng,
    MaTranPhuc &maTranVectorRieng
) {
    int n = maTranChuyen.size();

    Eigen::MatrixXd maTranEigen(n, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            maTranEigen(i, j) = maTranChuyen[i][j];
        }
    }

    Eigen::EigenSolver<Eigen::MatrixXd> boGiai(maTranEigen);

    if (boGiai.info() != Eigen::Success) {
        cout << "Eigen khong tinh duoc tri rieng va vector rieng." << endl;
        exit(1);
    }

    triRieng.resize(n);
    maTranVectorRieng = taoMaTranPhuc(n, n);

    for (int i = 0; i < n; i++) {
        triRieng[i] = boGiai.eigenvalues()(i);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            maTranVectorRieng[i][j] = boGiai.eigenvectors()(i, j);
        }
    }
}

// ===============================
// Tạo ma trận D^n
// D là ma trận đường chéo chứa trị riêng
// D^n là ma trận đường chéo chứa trị riêng mũ n
// ===============================
MaTranPhuc taoMaTranTriRiengMuN(VectorPhuc triRieng, int soBuoc) {
    int n = triRieng.size();

    MaTranPhuc maTranTriRiengMuN = taoMaTranPhuc(n, n);

    for (int i = 0; i < n; i++) {
        maTranTriRiengMuN[i][i] = pow(triRieng[i], soBuoc);
    }

    return maTranTriRiengMuN;
}

// ===============================
// Tính P^n bằng chéo hóa
// P = V * D * V^-1
// P^n = V * D^n * V^-1
// ===============================
MaTranPhuc tinhLuyThuaBangCheoHoa(MaTranThuc maTranChuyen, int soBuoc) {
    VectorPhuc triRieng;
    MaTranPhuc maTranVectorRieng;

    layTriRiengVaVectorRieng(
        maTranChuyen,
        triRieng,
        maTranVectorRieng
    );

    MaTranPhuc maTranTriRiengMuN = taoMaTranTriRiengMuN(
        triRieng,
        soBuoc
    );

    MaTranPhuc maTranVectorRiengNghichDao =
        nghichDaoMaTran(maTranVectorRieng);

    MaTranPhuc ketQua =
        nhanMaTran(
            nhanMaTran(maTranVectorRieng, maTranTriRiengMuN),
            maTranVectorRiengNghichDao
        );

    return ketQua;
}


int main() {
    cout << fixed << setprecision(6);

    // ===============================
    // Ma trận chuyển trạng thái P
    // Hàng i: trạng thái hiện tại
    // Cột j: trạng thái tiếp theo
    // ===============================
    int n;
    cout << "Nhap so trang thai n: ";
    cin >> n;

    if (n <= 0) {
        cout << "So trang thai phai lon hon 0." << endl;
        return 1;
    }

    MaTranThuc maTranChuyen(n, vector<double>(n));

    cout << "Nhap ma tran chuyen trang thai P cap "
         << n << " x " << n << ":" << endl;
    cout << "Moi dong nhap " << n << " so, cach nhau boi dau cach." << endl;

    for (int i = 0; i < n; i++) {
        cout << "Hang " << i + 1 << ": ";
        for (int j = 0; j < n; j++) {
            cin >> maTranChuyen[i][j];
        }
    }
    cout << endl;



    int trangThaiBanDau;
    cout << "Nhap trang thai ban dau (1.." << n << "): ";
    cin >> trangThaiBanDau;

    if (trangThaiBanDau < 1 || trangThaiBanDau > n) {
        cout << "Trang thai ban dau khong hop le." << endl;
        return 1;
    }

    int soBuoc;
    cout << "Nhap so buoc can tinh: ";
    cin >> soBuoc;

    if (soBuoc < 0) {
        cout << "So buoc phai khong am." << endl;
        return 1;
    }

    VectorPhuc vectorBanDau(n, SoPhuc(0, 0));
    vectorBanDau[trangThaiBanDau - 1] = SoPhuc(1, 0);

    cout << "Vector ban dau v0:" << endl;
    cout << "[ ";
    inVectorPhuc(vectorBanDau);
    cout << "]" << endl;

    cout << endl;

    cout << "Ket qua xac suat o trang thai 1 sau 1, 2, 3 buoc:" << endl;


    for (int buoc = 1; buoc <= 3; buoc++) {
        MaTranPhuc maTranChuyenMuN =
            tinhLuyThuaBangCheoHoa(maTranChuyen, buoc);

        VectorPhuc vectorKetQua =
            nhanVectorHangVoiMaTran(vectorBanDau, maTranChuyenMuN);

        cout << "Buoc " << buoc << ": " << endl;
        cout << "[ ";
        inVectorPhuc(vectorKetQua);
        cout << "]" << endl;
    }
    return 0;
}
