
// chỉ số trong danh sách các số nguyên tố
// 
//#include <iostream>
//#include <vector>
//#include <cmath>
//using namespace std;
//
//// Hàm kiểm tra số nguyên tố
//bool is_prime(int num) {
//    if (num < 2) return false;
//    for (int i = 2; i <= sqrt(num); i++) {
//        if (num % i == 0) return false;
//    }
//    return true;
//}
//
//// Hàm tìm chỉ số của số gần nhất với target trong một vector
//int find_closest_index(const vector<int>& nums, int target) {
//    int closest_index = 0;
//    int min_diff = abs(nums[0] - target);
//
//    for (int i = 1; i < nums.size(); i++) {
//        int diff = abs(nums[i] - target);
//        if (diff < min_diff) {
//            closest_index = i;
//            min_diff = diff;
//        }
//    }
//    return closest_index;
//}
//
//int main() {
//    const int C = 300; // Giá trị cần tìm số gần nhất
//
//    vector<int> M; // Tập M với các số từ 2 đến 499
//    for (int i = 2; i < 500; i++) {
//        M.push_back(i);
//    }
//
//    vector<int> primes; // Danh sách các số nguyên tố trong tập M
//
//    // Tìm các số nguyên tố trong tập M
//    for (int i = 0; i < M.size(); i++) {
//        if (is_prime(M[i])) {
//            primes.push_back(M[i]);
//        }
//    }
//
//    // In các số nguyên tố tìm được
//    cout << "Cac so nguyen to trong tap M: ";
//    for (int num : primes) {
//        cout << num << " ";
//    }
//    cout << endl;
//
//    // Tìm chỉ số của số nguyên tố gần nhất với C
//    if (!primes.empty()) {
//        int closest_index = find_closest_index(primes, C);
//        cout << "Chi so cua so nguyen to gan nhat voi " << C << " la: " << closest_index << endl;
//        cout << "Gia tri cua no la: " << primes[closest_index] << endl;
//    }
//    else {
//        cout << "Khong co so nguyen to nao trong tap M!" << endl;
//    }
//
//    return 0;
//}


//chỉ số trong tập nguồn M ban đầu 
//#include <iostream>
//#include <vector>
//#include <cmath>
//using namespace std;
//
//// Hàm kiểm tra số nguyên tố
//bool is_prime(int num) {
//    if (num < 2) return false;
//    for (int i = 2; i <= sqrt(num); i++) {
//        if (num % i == 0) return false;
//    }
//    return true;
//}
//
//// Hàm tìm chỉ số thực tế của số nguyên tố gần nhất với target (không tính target)
//int find_closest_prime_index(const vector<int>& primes, const vector<int>& M, int target) {
//    int closest_index_in_primes = -1;
//    int min_diff = INT_MAX;
//
//    // Tìm số nguyên tố gần nhất trong danh sách `primes` (bỏ qua `target`)
//    for (int i = 0; i < primes.size(); i++) {
//        if (primes[i] == target) continue; // Bỏ qua số hiện tại
//        int diff = abs(primes[i] - target);
//        if (diff < min_diff) {
//            closest_index_in_primes = i;
//            min_diff = diff;
//        }
//    }
//
//    // Lấy số nguyên tố gần nhất
//    if (closest_index_in_primes != -1) {
//        int closest_prime = primes[closest_index_in_primes];
//
//        // Tìm chỉ số thực tế của số nguyên tố trong tập M
//        for (int i = 0; i < M.size(); i++) {
//            if (M[i] == closest_prime) {
//                return i + 1; // Thứ tự thực tế (bắt đầu từ 1)
//            }
//        }
//    }
//
//    return -1; // Trường hợp không tìm thấy
//}
//
//int main() {
//    const int C = 397; // Giá trị cần tìm số gần nhất
//
//    vector<int> M; // Tập M với các số từ 1 đến 500
//    for (int i = 1; i <= 500; i++) {
//        M.push_back(i);
//    }
//
//    vector<int> primes; // Danh sách các số nguyên tố trong tập M
//
//    // Tìm các số nguyên tố trong tập M
//    for (int i = 0; i < M.size(); i++) {
//        if (is_prime(M[i])) {
//            primes.push_back(M[i]);
//        }
//    }
//
//    // In các số nguyên tố tìm được
//    cout << "Cac so nguyen to trong tap M: ";
//    for (int num : primes) {
//        cout << num << " ";
//    }
//    cout << endl;
//
//    // Tìm chỉ số của số nguyên tố gần nhất với C (không tính C)
//    if (!primes.empty()) {
//        int closest_index = find_closest_prime_index(primes, M, C);
//        if (closest_index != -1) {
//            cout << "Chi so cua so nguyen to gan nhat voi " << C << " (khong tinh chinh no) la: " << closest_index << endl;
//            cout << "Gia tri cua no la: " << M[closest_index - 1] << endl;
//        }
//        else {
//            cout << "Khong co so nguyen to nao gan voi " << C << "!" << endl;
//        }
//    }
//    else {
//        cout << "Khong co so nguyen to nao trong tap M!" << endl;
//    }
//
//    return 0;
//}

