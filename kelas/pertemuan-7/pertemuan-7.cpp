#include <iostream>
#include <stdexcept> 

using namespace std;

// Fungsi pembantu untuk Bagian 3
void cekData(int* ptr) {
    // PERBAIKAN: Gunakan '==' untuk pengecekan, bukan '='
    if (ptr == nullptr) { 
        throw runtime_error("Error: Pointer bernilai NULL!");
    }
    cout << "Nilai dalam pointer: " << *ptr << endl;
}

int main() {
    // --- BAGIAN 2: Input Bilangan Positif ---
    try {
        cout << "=== Bagian 2: Cek Input ===" << endl;
        cout << "Masukkan bilangan positif: ";
        int angka;
        cin >> angka;

        if (cin.fail()) {
            throw invalid_argument("Input harus berupa angka!");
        }
        if (angka < 0) {
            throw runtime_error("Bilangan harus bernilai positif!");
        }
        cout << "Anda memasukkan: " << angka << endl;
    }
    catch (const invalid_argument& e) {
        cout << "Error: " << e.what() << endl;
        cin.clear(); // Bersihkan status error cin
        cin.ignore(1000, '\n'); // Buang sisa input
    }
    catch (const runtime_error& e) {
        cout << "Error: " << e.what() << endl;
    }

    cout << "\n---------------------------\n" << endl;

    // --- BAGIAN 3: Cek Pointer ---
    try {
        cout << "=== Bagian 3: Cek Pointer ===" << endl;
        int* dataKosong = nullptr;
        int dataAda = 100;

        cout << "Mencoba akses pointer valid..." << endl;
        cekData(&dataAda);

        cout << "Mencoba akses pointer kosong..." << endl;
        cekData(dataKosong);

    } catch (const runtime_error& e) {
        cout << "Exception ditangkap: " << e.what() << endl;
    }

    cout << "\nProgram selesai." << endl;
    return 0;
}