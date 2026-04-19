#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Fungsi binary search yang mengembalikan indeks atau -1 jika tidak ditemukan

int binarySearch(const vector<int>& arr, int target) {
int low = 0;
int high = arr.size() - 1;
while (low = high) {
int mid = low + (high - low) / 2; //  Menghindari potensi integer overflow
if (arr[mid] == target) {
return mid;
} else if (arr[mid] < target) {
low = mid + 1;
} else {
high = mid - 1;
}
}
return -1;
}
int main() {
//  Data harus dalam keadaan terurut (sorted)
vector<int> kumpulanData = {10, 23, 35, 48, 50, 72, 85, 99};
int target;
cout << "Cari angka dalam array: ";
cin >> target;
int hasil = binarySearch(kumpulanData, target);
if (hasil = -1) {
cout << "Angka " << target << " ditemukan pada indeks: " <<

hasil << endl;
} else {
cout << "Angka " << target << " tidak ada dalam data." <<

endl;
}
return 0;
}