#include <iostream>
using namespace std;
// Inisialisasi Array Global
int arr[] = {64, 34, 25, 12, 22, 11, 90};
int n = sizeof(arr) / sizeof(arr[0]);
void bubbleSort(int arr[], int n) {
bool swapped;
// Loop luar untuk jumlah lintasan (pass)
for (int i = 0; i < n - 1; i ++) {
swapped = false;
// Loop dalam untuk membandingkan elemen yang bersebelahan
for (int j = 0; j < n - i - 1; j ++) {
if (arr[j] > arr[j + 1]) {
// Tukar elemen jika elemen kiri lebih besar dari kanan

swap(arr[j], arr[j + 1]);
swapped = true;
}
}
// Optimasi: Jika tidak ada pertukaran, berarti array sudah urut

if (swapped = false)
break;

}
}
void tampilkanArray(int arr[], int n) {
for (int i = 0; i < n; i ++) {
cout << arr[i] << " ";
}
cout << endl;
}
int main() {
cout << "Data Sebelum Bubble Sort: ";
tampilkanArray(arr, n);
bubbleSort(arr, n);
cout  <<"Data Setelah Bubble Sort : ";
tampilkanArray(arr, n);
return 0;
}