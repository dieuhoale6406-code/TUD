# 📐 TOÁN ỨNG DỤNG (APPLIED MATHEMATICS) - DUT

## 📌 Giới thiệu tổng quan

Kho lưu trữ chứa toàn bộ tài liệu học tập, mã nguồn thuật toán C++, bài tập thực hành, đề thi và hướng dẫn giải chi tiết cho 5 chuyên đề môn học **Toán Ứng Dụng**:

1. **Chương 1 — Lý thuyết số & Số học rời rạc**: Sàng Eratosthenes, phân tích thừa số nguyên tố, số hoàn hảo, thuật toán Euclid & Euclid mở rộng (giải phương trình Diophantine $ax+by=c$), số học modular, nghịch đảo modular, định lý phần dư Trung Hoa (CRT), hàm Euler Totient $\phi(n)$, dãy số Fibonacci.
2. **Chương 2 — Đại số tuyến tính tính toán**: Tính định thức, ma trận nghịch đảo, trực chuẩn hóa Gram-Schmidt, phương pháp lặp Jacobi, phân rã Cholesky ($A=LL^T$), phân rã trị riêng & vector riêng, phân rã giá trị suy biến SVD ($A = U\Sigma V^T$).
3. **Chương 3 — Hình học tính toán & Độ đo tương đồng**: Thuật toán tìm bao lồi 2D (Convex Hull: Andrew Monotone Chain, Graham Scan, Jarvis March, Chan's Algorithm), tính diện tích bao lồi (công thức Shoelace), chu vi bao lồi, khoảng cách ngắn nhất / dài nhất, kiểm tra điểm nằm trong bao lồi, độ tương đồng Cosine (Cosine Similarity).
4. **Chương 4 — Tối ưu hóa**: Tối ưu hóa không ràng buộc 1 biến và nhiều biến, phương pháp Gradient Descent (GD), Gradient Descent có quán tính (Momentum - GDM/GDWM), phương pháp Newton-Raphson, tối ưu hóa có ràng buộc (Lagrange Multipliers), thuật toán đơn hình Simplex 1 pha và 2 pha cho quy hoạch tuyến tính.
5. **Chương 5 — Xác suất & Chuỗi Markov**: Các phân phối xác suất quan trọng (Binomial, Normal, Geometric), xấp xỉ CLT, mô hình chuỗi Markov (Markov Chain): ma trận chuyển trạng thái $P$, xác suất chuyển sau $k$ bước ($\pi_k = \pi_0 P^k$), phân phối dừng / trạng thái cân bằng ($\pi P = \pi$), mô phỏng và xuất dữ liệu CSV vẽ đồ thị.

---

## 🗺️ Cấu trúc thư mục

```text
.
├── README.md                      # [File này] Hướng dẫn sử dụng & tổng quan repository
├── .gitignore                     # Cấu hình loại trừ file binary .exe, thư viện ngoài & file tạm
├── CuoiKy.md                      # Cẩm nang tổng ôn cuối kỳ (2200+ dòng code C++ chuẩn & lý thuyết)
├── 1_NumberTheory/                # Thuật toán Lý thuyết số C++ & file docx mã giả/mô tả
├── 2_LinearAlgebra/               # Thuật toán Đại số tuyến tính (Gram-Schmidt, Jacobi, Cholesky, SVD...)
├── 3_Geometry/                    # Thuật toán Bao lồi (Andrew, Graham, Jarvis, Chan) & Cosine
├── 4_Optimizations/               # Tối ưu hóa: GD, GDM, Newton, Đơn hình 1 pha & 2 pha
├── 5_Probability/                 # Xác suất thống kê & Chuỗi Markov, ma trận chuyển trạng thái
├── GiuaKy/                        # Kho tài liệu & đề thi giữa kỳ (De1 -> De4 kèm bài giải mẫu)
├── CuoiKy/                        # Đề thi & tài liệu ôn thi cuối kỳ
├── THAM_KHAO/                     # Mã nguồn và bài tập tham khảo mở rộng từ các khóa trước
└── ToanUD_src-and-tools/          # Bộ công cụ thi tự chứa (Exam_CPP, Checker_Python, Diagrams, Latex)
```

---

## 🎯 Bản đồ 5 dạng câu hỏi đề thi cuối kỳ

|    Câu    | Chuyên đề              | Thuật toán & Trọng tâm kiến thức                                                                                | File mã nguồn học tập                                             | File làm bài thi nhanh (`ToanUD_src-and-tools/Exam_CPP/`) |
| :-------: | :--------------------- | :-------------------------------------------------------------------------------------------------------------- | :---------------------------------------------------------------- | :-------------------------------------------------------- |
| **Câu 1** | **Lý thuyết số**       | Sàng Eratosthenes, Diophantine $ax+by=c$, Modular Pow, Modular Inverse, CRT, Euler $\phi(n)$, Fibonacci.        | `1_NumberTheory/full.cpp`<br>`1_NumberTheory/fibonaci.cpp`        | `Cau1_NumberTheory_Fibonacci.cpp`                         |
| **Câu 2** | **Đại số tuyến tính**  | Eigenvalues / Eigenvectors, Phân rã Cholesky, Phân rã SVD ($U, \Sigma, V^T$), Gram-Schmidt.                     | `2_LinearAlgebra/SVD.cpp`<br>`2_LinearAlgebra/phanracholesky.cpp` | `Cau2_SVD.cpp`                                            |
| **Câu 3** | **Hình học tính toán** | Andrew Monotone Chain, Graham Scan, Jarvis March, Diện tích Shoelace, Chu vi, Cosine Similarity.                | `3_Geometry/Andrew(Monotone Chain).cpp`<br>`3_Geometry/cos.cpp`   | `Cau3_ConvexHull.cpp`<br>`Cau3_CosineSimilarity.cpp`      |
| **Câu 4** | **Tối ưu hóa**         | Gradient Descent (GD), GD with Momentum (GDM), Phương pháp Newton, Đơn hình Simplex 1 & 2 pha.                  | `4_Optimizations/full.cpp`<br>`4_Optimizations/MotBien/`          | `Cau4_GDM.cpp`                                            |
| **Câu 5** | **Xác suất & Markov**  | Ma trận chuyển trạng thái $P$, vector xác suất $\pi_k = \pi_0 P^k$, phân phối dừng, phân phối Binomial, Normal. | `5_Probability/markov_modular.cpp`<br>`5_Probability/bai5.cpp`    | `Cau5_Markov.cpp`                                         |

---

## 🚀 Hướng dẫn biên dịch & chạy thử nghiệm

### 1. Yêu cầu môi trường

- Trình biên dịch C++ hỗ trợ **C++17** (`g++` / MinGW-w64).
- Python 3.8+ (tùy chọn: dùng kiểm tra kết quả chéo qua `Checker_Python`).

### 2. Biên dịch thủ công qua dòng lệnh

```bash
# Câu 1: Lý thuyết số
g++ -std=c++17 1_NumberTheory/full.cpp -o full_c1.exe
./full_c1.exe

# Câu 2: Phân rã SVD
g++ -std=c++17 2_LinearAlgebra/SVD.cpp -o svd.exe
./svd.exe

# Câu 3: Bao lồi Andrew
g++ -std=c++17 "3_Geometry/Andrew(Monotone Chain).cpp" -o andrew.exe
./andrew.exe

# Câu 4: Tối ưu hóa
g++ -std=c++17 4_Optimizations/full.cpp -o opt.exe
./opt.exe

# Câu 5: Chuỗi Markov
g++ -std=c++17 5_Probability/markov_modular.cpp -o markov.exe
./markov.exe
```

### 3. Quy trình làm bài thi thực hành siêu tốc

1. Mở file cẩm nang [CuoiKy.md](CuoiKy.md) để tra cứu công thức và lý thuyết nhanh.
2. Mở thư mục `ToanUD_src-and-tools/Exam_CPP/`.
3. Sửa thông số đề bài tại khối `// TODO: INPUT` trong file tương ứng (`Cau1` -> `Cau5`).
4. Chạy file để nhận ngay kết quả từng bước và chép vào bài làm.
5. (Tùy chọn) Chạy script tương ứng trong `ToanUD_src-and-tools/Checker_Python/` để double-check tính chính xác.

---

## ⚠️ Lưu ý kỹ thuật quan trọng

- **Kiểu dữ liệu số lớn**: Các bài toán lý thuyết số và lũy thừa modular phải sử dụng kiểu `long long` (64-bit) để tránh tràn số.
- **Độ chính xác số thực**: Khi so sánh số thực trong SVD, Gradient Descent và Markov, luôn sử dụng ngưỡng sai số `EPS = 1e-9`.
- **Thư viện ngoài**: Bài thi và bài tập yêu cầu triển khai giải thuật thủ công, không dùng thư viện ngoài (như Eigen hay thư viện tối ưu hóa có sẵn) nhằm đảm bảo mục tiêu học tập và đánh giá.
