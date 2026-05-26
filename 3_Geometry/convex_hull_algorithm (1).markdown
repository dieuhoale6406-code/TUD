# Thuật Toán Tìm Bao Lồi (Graham's Scan)

## Mục Tiêu
Tìm đa giác lồi nhỏ nhất bao quanh tất cả các điểm trong một tập hợp, đảm bảo mọi đoạn nối hai điểm trong bao lồi nằm bên trong.

## Ý Tưởng Chính
- Sử dụng tích có hướng để kiểm tra hướng rẽ khi thêm điểm.
- Chia bao lồi thành **bao dưới** (lower hull) và **bao trên** (upper hull), sau đó kết hợp.

## Các Bước Thực Hiện
1. **Sắp xếp điểm**: Sắp xếp các điểm theo tọa độ \( x \) tăng dần (nếu \( x \) bằng nhau thì theo \( y \)).
2. **Xây bao dưới**:
   - Duyệt từ điểm trái nhất, thêm điểm mới nếu tạo "rẽ trái" (tích có hướng > 0).
   - Nếu tạo "rẽ phải" hoặc thẳng hàng (tích ≤ 0), loại bỏ điểm cuối và kiểm tra lại.
3. **Xây bao trên**:
   - Duyệt từ điểm phải nhất, thêm điểm mới nếu tạo "rẽ trái" (tích có hướng > 0).
   - Nếu tạo "rẽ phải" hoặc thẳng hàng (tích ≤ 0), loại bỏ điểm cuối và kiểm tra lại.
4. **Kết hợp**: Nối bao dưới và bao trên, bỏ hai điểm trùng ở đầu/cuối.
5. **Kết quả**: Danh sách đỉnh bao lồi theo thứ tự ngược chiều kim đồng hồ.

## Tích Có Hướng
- Với ba điểm \( P, Q, R \):  
  \( D = (Q_x - P_x)(R_y - P_y) - (Q_y - P_y)(R_x - P_x) \)  
  - \( D > 0 \): Rẽ trái (giữ).  
  - \( D < 0 \): Rẽ phải (loại).  
  - \( D = 0 \): Thẳng hàng (loại).

## Độ Phức Tạp
- Thời gian: \( O(n \log n) \) (do sắp xếp).  
- Không gian: \( O(n) \).

## Minh Họa
- Từ tập điểm rải rác, thuật toán tạo ra đa giác lồi bao quanh (như hình minh họa trong slide).
- Ví dụ: Với điểm \( P1(0, 0), P2(1, 1), P4(1, 3), P5(0, 2) \), bao lồi có 4 đỉnh.

