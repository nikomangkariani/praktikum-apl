#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>   // Shortcut buat manipulasi data (kayak sortir atau ubah huruf)
#include <stdexcept>   // Buat nanganin error biar program gak gampang mati
#include <limits>
using namespace std;

// Di sini tempat kita membuat aturan: kalau ada kejadian aneh 
// (seperti input minus atau data kosong), program akan tahu.

class TokoException : public exception {
protected:
    string pesan;
public:
    explicit TokoException(const string &msg) : pesan(msg) {}
    const char *what() const noexcept override { return pesan.c_str(); }
};

class InvalidInputException : public TokoException {
public:
    explicit InvalidInputException(const string &detail)
        : TokoException(detail) {}
};

class OutOfRangeException : public TokoException {
public:
    explicit OutOfRangeException(const string &detail)
        : TokoException(detail) {}
};

class NotFoundException : public TokoException {
public:
    explicit NotFoundException(const string &detail)
        : TokoException(detail) {}
};

class KapasitasPenuhException : public TokoException {
public:
    explicit KapasitasPenuhException(const string &detail)
        : TokoException(detail) {}
};

class AuthException : public TokoException {
public:
    explicit AuthException(const string &detail)
        : TokoException(detail) {}
};

class DuplikatException : public TokoException {
public:
    explicit DuplikatException(const string &detail)
        : TokoException(detail) {}
};

// Di sini tempat naruh fungsi 'asisten' yang tugasnya 
// beresin hal-hal kecil supaya program utama makin rapi.

void validasiStringTidakKosong(const string &nilai, const string &namaField) {
    if (nilai.empty())
        throw InvalidInputException(namaField + " tidak boleh kosong!");
}

void validasiPositif(double nilai, const string &namaField) {
    if (nilai <= 0)
        throw InvalidInputException(namaField + " harus bernilai positif (> 0)! "
                                    "Kamu memasukkan: " + to_string((int)nilai));
}

void validasiStokTidakNegatif(int nilai) {
    if (nilai < 0)
        throw InvalidInputException("Stok tidak boleh negatif! Kamu memasukkan: "
                                    + to_string(nilai));
}

void validasiRentang(int nilai, int bawah, int atas, const string &konteks) {
    if (nilai < bawah || nilai > atas)
        throw OutOfRangeException("Pilihan tersebut tidak ada di menu, coba lagi.");
}

int bacaInt(const string &prompt) {
    cout << prompt;
    int nilai;
    if (!(cin >> nilai)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw InvalidInputException("Input harus berupa angka bulat!");
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return nilai;
}

double bacaDouble(const string &prompt) {
    cout << prompt;
    double nilai;
    if (!(cin >> nilai)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw InvalidInputException("Input harga harus berupa angka!");
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return nilai;
}

void tampilError(const string &pesan) {
    cout << "\nERROR: " << pesan << "\n";
}

void tampilSukses(const string &pesan) {
    cout << "\n" << pesan << "\n";
}

void tekanEnter() {
    cout << "\nTekan Enter untuk lanjut...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Untuk Konstanta
const int BATAS_USER   = 50;
const int BATAS_BARANG = 100;

// Struct
struct Kategori {
    string namaKategori;
    string keteranganKategori;
};

struct Barang {
    int      kodeBarang;
    string   namaBarang;
    double   hargaBarang;
    int      stokBarang;
    Kategori kategoriBarang;
};

struct Akun {
    string namaUser;
    string nimUser;
    bool   isAdmin;
};

// Data keseluruhan 
Akun   daftarAkun[BATAS_USER];
int    jumlahAkun   = 0;

Barang dataBarang[BATAS_BARANG];
int    jumlahBarang = 0;
int    kodeOtomatis = 1;

// Fungsi tampilan pada tabel
void cetakGaris() {
    cout << left
         << "+" << setfill('-') << setw(5)  << "-" << "+"
                                << setw(22) << "-" << "+"
                                << setw(12) << "-" << "+"
                                << setw(8)  << "-" << "+"
                                << setw(14) << "-" << "+"
         << setfill(' ') << endl;
}

void cetakHeader() {
    cetakGaris();
    cout << "| " << left << setw(3)  << "No"
         << " | "        << setw(20) << "Nama Barang"
         << " | "        << setw(10) << "Harga (Rp)"
         << " | "        << setw(6)  << "Stok"
         << " | "        << setw(12) << "Kategori"
         << " |" << endl;
    cetakGaris();
}

void tampilBarang(Barang *semuaBarang, int totalBarang, bool tampilKode) {
    cout << "|=================================================================|" << endl;
    cout << "|                         DAFTAR BARANG                           |" << endl;
    cout << "|=================================================================|" << endl;

    if (totalBarang == 0)
        throw NotFoundException("Belum ada barang di toko.");

    cetakHeader();
    for (int i = 0; i < totalBarang; i++) {
        Barang *p = &semuaBarang[i];
        cout << "| " << left   << setw(3)  << i + 1
             << " | "          << setw(20) << p->namaBarang
             << " | " << right << setw(10) << fixed << setprecision(0) << p->hargaBarang
             << " | " << right << setw(6)  << p->stokBarang
             << " | " << left  << setw(12) << p->kategoriBarang.namaKategori
             << " |" << endl;
    }
    cetakGaris();
    cout << "Total: " << totalBarang << " barang\n";
}

void tampilBarang(Barang *semuaBarang, int totalBarang) {
    cout << "|=================================================================|" << endl;
    cout << "|                         DAFTAR BARANG                           |" << endl;
    cout << "|=================================================================|" << endl;

    if (totalBarang == 0)
        throw NotFoundException("Belum ada barang di toko.");

    cetakHeader();
    int adaTersedia = 0;
    for (int i = 0; i < totalBarang; i++) {
        Barang *p = &semuaBarang[i];
        if (p->stokBarang > 0) {
            cout << "| " << left   << setw(3)  << i + 1
                 << " | "          << setw(20) << p->namaBarang
                 << " | " << right << setw(10) << fixed << setprecision(0) << p->hargaBarang
                 << " | " << right << setw(6)  << p->stokBarang
                 << " | " << left  << setw(12) << p->kategoriBarang.namaKategori
                 << " |" << endl;
            adaTersedia++;
        }
    }
    cetakGaris();
    if (adaTersedia == 0)
        throw NotFoundException("Semua barang sedang kosong stoknya.");
    cout << "Tersedia: " << adaTersedia << " jenis barang\n";
}

void tampilSatuBarang(Barang *p, int nomorUrut) {
    cetakGaris();
    cout << "| " << left   << setw(3)  << nomorUrut
         << " | "          << setw(20) << p->namaBarang
         << " | " << right << setw(10) << fixed << setprecision(0) << p->hargaBarang
         << " | " << right << setw(6)  << p->stokBarang
         << " | " << left  << setw(12) << p->kategoriBarang.namaKategori
         << " |" << endl;
    cetakGaris();
    cout << "Kode Barang  : " << p->kodeBarang << endl;
    cout << "Keterangan   : " << p->kategoriBarang.keteranganKategori << endl;
}

// Disini tempat Fungsi CRUD nya

void tambahBarang(Barang semuaBarang[], int &totalBarang, int &kodeUrut) {
    cout << "|==============================================|" << endl;
    cout << "|              TAMBAH BARANG BARU              |" << endl;
    cout << "|==============================================|" << endl;

    if (totalBarang >= BATAS_BARANG)
        throw KapasitasPenuhException("Data barang sudah mencapai batas maksimum ("
                                      + to_string(BATAS_BARANG) + " barang).");

    Barang barangBaru;
    barangBaru.kodeBarang = kodeUrut++;

    cout << "Nama barang          : ";
    getline(cin, barangBaru.namaBarang);
    validasiStringTidakKosong(barangBaru.namaBarang, "Nama barang");

    barangBaru.stokBarang = bacaInt("Stok                 : ");
    validasiStokTidakNegatif(barangBaru.stokBarang);

    barangBaru.hargaBarang = bacaDouble("Harga                : ");
    validasiPositif(barangBaru.hargaBarang, "Harga");

    cout << "Kategori             : ";
    getline(cin, barangBaru.kategoriBarang.namaKategori);
    validasiStringTidakKosong(barangBaru.kategoriBarang.namaKategori, "Kategori");

    semuaBarang[totalBarang++] = barangBaru;
    tampilSukses("Barang '" + barangBaru.namaBarang + "' berhasil ditambahkan! "
                 "(Kode: " + to_string(barangBaru.kodeBarang) + ")");
}

void updateSatuBarang(Barang *p) {
    cout << "\nUpdate Barang: " << p->namaBarang << "\n";
    cout << "(Kosongkan atau tekan Enter jika tidak ingin mengubah)\n\n";

    string inputBaru;

    cout << "Nama baru      [" << p->namaBarang << "]: ";
    getline(cin, inputBaru);
    if (!inputBaru.empty()) p->namaBarang = inputBaru;

    cout << "Stok baru      [" << p->stokBarang << "]: ";
    getline(cin, inputBaru);
    if (!inputBaru.empty()) {
        int stokBaru;
        try { stokBaru = stoi(inputBaru); }
        catch (...) { throw InvalidInputException("Stok harus berupa angka bulat!"); }
        validasiStokTidakNegatif(stokBaru);
        p->stokBarang = stokBaru;
    }

    cout << "Harga baru     [" << fixed << setprecision(0) << p->hargaBarang << "]: ";
    getline(cin, inputBaru);
    if (!inputBaru.empty()) {
        double hargaBaru;
        try { hargaBaru = stod(inputBaru); }
        catch (...) { throw InvalidInputException("Harga harus berupa angka!"); }
        validasiPositif(hargaBaru, "Harga");
        p->hargaBarang = hargaBaru;
    }

    cout << "Kategori baru  [" << p->kategoriBarang.namaKategori << "]: ";
    getline(cin, inputBaru);
    if (!inputBaru.empty()) p->kategoriBarang.namaKategori = inputBaru;

    tampilSukses("Data barang berhasil diperbarui!");
}

void updateBarang(Barang semuaBarang[], int totalBarang) {
    cout << "|===================================================================|" << endl;
    cout << "|                           UPDATE BARANG                           |" << endl;
    cout << "|===================================================================|" << endl;

    if (totalBarang == 0)
        throw NotFoundException("Belum ada barang untuk diupdate.");

    for (int i = 0; i < totalBarang; i++) {
        cout << "| " << left << setw(2) << i + 1 << ". "
             << left << setw(15) << semuaBarang[i].namaBarang
             << " Stok: "  << left << setw(4) << semuaBarang[i].stokBarang
             << " Harga: " << left << setw(8) << fixed << setprecision(0) << semuaBarang[i].hargaBarang
             << " Kat: "   << left << setw(14) << semuaBarang[i].kategoriBarang.namaKategori
             << "|" << endl;
    }
    cout << "|===================================================================|" << endl;

    int nomorUpdate = bacaInt("\nMasukkan nomor barang yang ingin diupdate: ");
    validasiRentang(nomorUpdate, 1, totalBarang, "Nomor barang");

    updateSatuBarang(&semuaBarang[nomorUpdate - 1]);
}

void hapusBarang(Barang semuaBarang[], int &totalBarang) {
    cout << "|===================================================================|" << endl;
    cout << "|                           HAPUS BARANG                            |" << endl;
    cout << "|===================================================================|" << endl;

    if (totalBarang == 0)
        throw NotFoundException("Belum ada barang untuk dihapus.");

    for (int i = 0; i < totalBarang; i++) {
        cout << "| " << left << setw(2) << i + 1 << ". "
             << left << setw(15) << semuaBarang[i].namaBarang
             << " Stok: "  << left << setw(4)  << semuaBarang[i].stokBarang
             << " Harga: " << left << setw(8)  << fixed << setprecision(0) << semuaBarang[i].hargaBarang
             << " Kat: "   << left << setw(14) << semuaBarang[i].kategoriBarang.namaKategori
             << "|" << endl;
    }
    cout << "|===================================================================|" << endl;

    int nomorHapus = bacaInt("\nMasukkan nomor barang yang ingin dihapus: ");
    validasiRentang(nomorHapus, 1, totalBarang, "Nomor barang");

    int    indeks     = nomorHapus - 1;
    string namaDihapus = semuaBarang[indeks].namaBarang;

    for (int j = indeks; j < totalBarang - 1; j++)
        semuaBarang[j] = semuaBarang[j + 1];
    totalBarang--;

    tampilSukses("Barang '" + namaDihapus + "' berhasil dihapus!");
}

// Isinya fungsi buat ngecek siapa yang masuk ke program

bool cekNamaSudahDipakai(Akun *semuaAkun, int totalAkun, const string &namaCek) {
    for (int i = 0; i < totalAkun; i++)
        if (semuaAkun[i].namaUser == namaCek) return true;
    return false;
}

void registerAkun(Akun semuaAkun[], int &totalAkun) {
    cout << "|==============================================|" << endl;
    cout << "|              REGISTER AKUN BARU              |" << endl;
    cout << "|==============================================|" << endl;

    if (totalAkun >= BATAS_USER)
        throw KapasitasPenuhException("Pendaftaran akun sudah mencapai batas maksimum.");

    Akun akunBaru;

    cout << "Tulis username kamu ya       : ";
    getline(cin, akunBaru.namaUser);
    validasiStringTidakKosong(akunBaru.namaUser, "Username");

    if (cekNamaSudahDipakai(semuaAkun, totalAkun, akunBaru.namaUser))
        throw DuplikatException("Username '" + akunBaru.namaUser + "' sudah dipakai. Coba nama lain.");

    cout << "Password nya juga ya         : ";
    getline(cin, akunBaru.nimUser);
    validasiStringTidakKosong(akunBaru.nimUser, "Password");

    if (akunBaru.nimUser.length() < 3)
        throw InvalidInputException("Password minimal 3 karakter!");

    akunBaru.isAdmin = false;
    semuaAkun[totalAkun++] = akunBaru;

    tampilSukses("Akun '" + akunBaru.namaUser + "' berhasil dibuat!");
}

int loginRekursif(Akun *semuaAkun, int totalAkun, int sisaCoba) {
    if (sisaCoba <= 0)
        throw AuthException("Sudah 3 kali salah memasukkan username/password. Akses ditolak.");

    string inputNama, inputNim;
    cout << "Tulis username kamu dong  : ";
    getline(cin, inputNama);
    cout << "Password nya juga ya      : ";
    getline(cin, inputNim);

    for (int i = 0; i < totalAkun; i++) {
        if (semuaAkun[i].namaUser == inputNama && semuaAkun[i].nimUser == inputNim) {
            cout << "\nLogin berhasil! Selamat datang, " << inputNama << "\n";
            cout << "Tekan Enter untuk lanjut...";
            cin.ignore();
            return i;
        }
    }

    int sisa = sisaCoba - 1;
    if (sisa > 0)
        cout << "Waduh, username/password salah. Sisa coba: " << sisa << "\n\n";
    return loginRekursif(semuaAkun, totalAkun, sisa);
}

// Fungsi Sorting

void selectionSortNamaAscending(Barang arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j].namaBarang < arr[minIdx].namaBarang) minIdx = j;
        if (minIdx != i) swap(arr[i], arr[minIdx]);
    }
}

void bubbleSortHargaDescending(Barang arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool ada = false;
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j].hargaBarang < arr[j + 1].hargaBarang) {
                swap(arr[j], arr[j + 1]);
                ada = true;
            }
        }
        if (!ada) break;
    }
}

void insertionSortStokAscending(Barang arr[], int n) {
    for (int i = 1; i < n; i++) {
        Barang kunci = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].stokBarang > kunci.stokBarang) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = kunci;
    }
}

void salinDataBarang(Barang src[], Barang dst[], int n) {
    for (int i = 0; i < n; i++) dst[i] = src[i];
}

void menuSorting(Barang *semuaBarang, int totalBarang) {
    if (totalBarang == 0)
        throw NotFoundException("Belum ada barang untuk diurutkan.");

    Barang dataSortir[BATAS_BARANG];
    bool   jalan = true;

    while (jalan) {
        cout << "|==============================================|" << endl;
        cout << "|               MENU SORTING BARANG            |" << endl;
        cout << "|==============================================|" << endl;
        cout << "|1. Selection Sort - Nama A ke Z (Ascending)   |" << endl;
        cout << "|2. Bubble Sort    - Harga Tertinggi (Desc)    |" << endl;
        cout << "|3. Insertion Sort - Stok Terkecil (Ascending) |" << endl;
        cout << "|4. Kembali                                    |" << endl;
        cout << "|==============================================|" << endl;

        try {
            int p = bacaInt("Pilih menu 1-4 yuk: ");
            validasiRentang(p, 1, 4, "Pilihan sorting");

            if (p == 4) { jalan = false; continue; }

            salinDataBarang(semuaBarang, dataSortir, totalBarang);
            if      (p == 1) { cout << "\nSelection Sort: Nama A ke Z\n";           selectionSortNamaAscending(dataSortir, totalBarang); }
            else if (p == 2) { cout << "\nBubble Sort: Harga Tertinggi ke Terendah\n"; bubbleSortHargaDescending(dataSortir, totalBarang); }
            else if (p == 3) { cout << "\nInsertion Sort: Stok Terkecil ke Terbanyak\n"; insertionSortStokAscending(dataSortir, totalBarang); }
            tampilBarang(dataSortir, totalBarang, true);
            tekanEnter();

        } catch (const TokoException &e) {
            tampilError(e.what());
            tekanEnter();
        }
    }
}

// Fungsi Searching

int binarySearchKodeBarang(Barang *arr, int n, int kode) {
    int kiri = 0, kanan = n - 1;
    while (kiri <= kanan) {
        int tengah = (kiri + kanan) / 2;
        int k = (arr + tengah)->kodeBarang;
        if (k == kode)  return tengah;
        else if (k < kode) kiri  = tengah + 1;
        else               kanan = tengah - 1;
    }
    return -1;
}

int sequentialSearchNamaBarang(Barang *arr, int n, const string &nama) {
    string kunci = nama;
    transform(kunci.begin(), kunci.end(), kunci.begin(), ::tolower);
    for (int i = 0; i < n; i++) {
        string namaKecil = (arr + i)->namaBarang;
        transform(namaKecil.begin(), namaKecil.end(), namaKecil.begin(), ::tolower);
        if (namaKecil.find(kunci) != string::npos) return i;
    }
    return -1;
}

void sortKodeAscendingUntukSearch(Barang arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j].kodeBarang < arr[minIdx].kodeBarang) minIdx = j;
        if (minIdx != i) swap(arr[i], arr[minIdx]);
    }
}

void menuSearching(Barang *semuaBarang, int totalBarang) {
    if (totalBarang == 0)
        throw NotFoundException("Belum ada barang untuk dicari.");

    bool jalan = true;
    while (jalan) {
        cout << "|==============================================|" << endl;
        cout << "|              MENU PENCARIAN BARANG           |" << endl;
        cout << "|==============================================|" << endl;
        cout << "|1. Cari Kode Barang  (Binary Search)          |" << endl;
        cout << "|2. Cari Nama Barang  (Sequential Search)      |" << endl;
        cout << "|3. Kembali                                    |" << endl;
        cout << "|==============================================|" << endl;

        try {
            int p = bacaInt("Pilih menu 1-3 yuk: ");
            validasiRentang(p, 1, 3, "Pilihan pencarian");

            if (p == 3) { jalan = false; continue; }

            if (p == 1) {
                int kode = bacaInt("\nMasukkan kode barang yang dicari: ");
                if (kode <= 0) throw InvalidInputException("Kode barang harus positif!");

                Barang dataCari[BATAS_BARANG];
                salinDataBarang(semuaBarang, dataCari, totalBarang);
                sortKodeAscendingUntukSearch(dataCari, totalBarang);

                cout << "\nProses Binary Search untuk Kode " << kode << ":\n";
                int kiri = 0, kanan = totalBarang - 1, langkah = 1;
                while (kiri <= kanan) {
                    int t = (kiri + kanan) / 2;
                    cout << "  Langkah " << langkah << ": periksa kode " << dataCari[t].kodeBarang
                         << " ('" << dataCari[t].namaBarang << "')";
                    if (dataCari[t].kodeBarang == kode) { cout << " -> Ditemukan!\n"; break; }
                    else if (dataCari[t].kodeBarang < kode) { cout << " -> cari kanan\n"; kiri = t + 1; }
                    else { cout << " -> cari kiri\n"; kanan = t - 1; }
                    langkah++;
                    if (kiri > kanan) cout << "  Tidak ditemukan.\n";
                }

                int idx = binarySearchKodeBarang(dataCari, totalBarang, kode);
                cout << "\nHasil Pencarian:\n";
                cetakHeader();
                if (idx == -1) {
                    cetakGaris();
                    throw NotFoundException("Barang dengan kode " + to_string(kode) + " tidak ditemukan.");
                }
                tampilSatuBarang(dataCari + idx, idx + 1);

            } else {
                string nama;
                cout << "\nMasukkan nama barang yang dicari: ";
                getline(cin, nama);
                validasiStringTidakKosong(nama, "Kata kunci pencarian");

                string kunci = nama;
                transform(kunci.begin(), kunci.end(), kunci.begin(), ::tolower);
                cout << "\nProses Sequential Search untuk \"" << nama << "\":\n";
                for (int i = 0; i < totalBarang; i++) {
                    string namaKecil = (semuaBarang + i)->namaBarang;
                    transform(namaKecil.begin(), namaKecil.end(), namaKecil.begin(), ::tolower);
                    cout << "  Periksa [" << i << "] '" << (semuaBarang + i)->namaBarang << "'";
                    if (namaKecil.find(kunci) != string::npos) { cout << " -> Cocok!\n"; break; }
                    else cout << " -> tidak cocok\n";
                }

                int idx = sequentialSearchNamaBarang(semuaBarang, totalBarang, nama);
                cout << "\nHasil Pencarian:\n";
                cetakHeader();
                if (idx == -1) {
                    cetakGaris();
                    throw NotFoundException("Barang dengan nama \"" + nama + "\" tidak ditemukan.");
                }
                tampilSatuBarang(semuaBarang + idx, idx + 1);
            }
            tekanEnter();

        } catch (const TokoException &e) {
            tampilError(e.what());
            tekanEnter();
        }
    }
}

// Menu Admin
void menuAdmin(Barang *semuaBarang, int &totalBarang, int &kodeUrut) {
    bool jalan = true;
    while (jalan) {
        cout << "|==============================================|" << endl;
        cout << "|                  MENU ADMIN                  |" << endl;
        cout << "|==============================================|" << endl;
        cout << "|1. Lihat Barang                               |" << endl;
        cout << "|2. Tambah Barang                              |" << endl;
        cout << "|3. Update Barang                              |" << endl;
        cout << "|4. Hapus Barang                               |" << endl;
        cout << "|5. Sorting Barang                             |" << endl;
        cout << "|6. Cari Barang                                |" << endl;
        cout << "|7. Logout                                     |" << endl;
        cout << "|==============================================|" << endl;

        try {
            int p = bacaInt("Pilih menu 1-7 yuk: ");
            validasiRentang(p, 1, 7, "Pilihan menu admin");

            if      (p == 1) { tampilBarang(semuaBarang, totalBarang, true); tekanEnter(); }
            else if (p == 2) { tambahBarang(semuaBarang, totalBarang, kodeUrut); tekanEnter(); }
            else if (p == 3) { updateBarang(semuaBarang, totalBarang); tekanEnter(); }
            else if (p == 4) { hapusBarang(semuaBarang, totalBarang); tekanEnter(); }
            else if (p == 5) { menuSorting(semuaBarang, totalBarang); }
            else if (p == 6) { menuSearching(semuaBarang, totalBarang); }
            else {
                tampilSukses("Logout berhasil!");
                tekanEnter();
                jalan = false;
            }

        } catch (const TokoException &e) {
            tampilError(e.what());
            tekanEnter();
        } catch (const exception &e) {
            tampilError(string("Unexpected error: ") + e.what());
            tekanEnter();
        }
    }
}

// Menu User
void menuUser(Barang *semuaBarang, int totalBarang) {
    bool jalan = true;
    while (jalan) {
        cout << "|==============================================|" << endl;
        cout << "|                MENU PENGGUNA                 |" << endl;
        cout << "|==============================================|" << endl;
        cout << "|1. Lihat Barang                               |" << endl;
        cout << "|2. Cari Barang (Searching)                    |" << endl;
        cout << "|3. Logout                                     |" << endl;
        cout << "|==============================================|" << endl;

        try {
            int p = bacaInt("Pilih menu 1-3 yuk: ");
            validasiRentang(p, 1, 3, "Pilihan menu user");

            if (p == 1) { tampilBarang(semuaBarang, totalBarang); tekanEnter(); }
            else if (p == 2) { menuSearching(semuaBarang, totalBarang); }
            else {
                tampilSukses("Logout berhasil! Terima kasih sudah mampir :)");
                tekanEnter();
                jalan = false;
            }

        } catch (const TokoException &e) {
            tampilError(e.what());
            tekanEnter();
        } catch (const exception &e) {
            tampilError(string("Unexpected error: ") + e.what());
            tekanEnter();
        }
    }
}

// Fungsi Main

int main() {

    // Inisialisasi data barang awal
    dataBarang[0] = {kodeOtomatis++, "Buku Tulis",  8000, 100, {"Buku",       "Buku tulis 58 lembar"}};
    dataBarang[1] = {kodeOtomatis++, "Penggaris",   5000,  75, {"Alat Ukur",  "Penggaris 30cm plastik"}};
    dataBarang[2] = {kodeOtomatis++, "Penghapus",   2000, 120, {"Alat Tulis", "Penghapus putih lembut"}};
    dataBarang[3] = {kodeOtomatis++, "Pensil 2B",   3000,  90, {"Alat Tulis", "Pensil untuk menggambar"}};
    dataBarang[4] = {kodeOtomatis++, "Peraut",      2500,  60, {"Alat Tulis", "Peraut pensil putar"}};
    jumlahBarang  = 5;

    // Inisialisasi akun admin
    daftarAkun[0] = {"komang", "003", true};
    jumlahAkun    = 1;

    Barang *ptrDataBarang = dataBarang;
    Akun   *ptrDaftarAkun = daftarAkun;

    cout << "|==============================================|" << endl;
    cout << "|      SELAMAT DATANG DI TOKO ALAT TULIS       |" << endl;
    cout << "|==============================================|" << endl;
    cout << "Halo! Mau cari alat tulis apa hari ini?\n";
    cout << "Kami punya semua yang kamu butuhkan.\n\n";
    cout << "Tekan Enter untuk lanjut ke menu utama..";
    cin.ignore();

    bool appJalan = true;

    while (appJalan) {
        cout << "|==============================================|" << endl;
        cout << "|        MENU UTAMA TOKO ALAT TULIS            |" << endl;
        cout << "|==============================================|" << endl;
        cout << "|1. Login                                      |" << endl;
        cout << "|2. Register                                   |" << endl;
        cout << "|3. Keluar                                     |" << endl;
        cout << "|==============================================|" << endl;

        try {
            int pilih = bacaInt("Pilih Menu 1-3 yuk: ");
            validasiRentang(pilih, 1, 3, "Pilihan menu utama");

            if (pilih == 1) {
                cout << "|==============================================|" << endl;
                cout << "|                  LOGIN AKUN                  |" << endl;
                cout << "|==============================================|" << endl;

                int idx = loginRekursif(ptrDaftarAkun, jumlahAkun, 3);

                if (daftarAkun[idx].isAdmin)
                    menuAdmin(ptrDataBarang, jumlahBarang, kodeOtomatis);
                else
                    menuUser(ptrDataBarang, jumlahBarang);

            } else if (pilih == 2) {
                registerAkun(daftarAkun, jumlahAkun);
                tekanEnter();

            } else {
                cout << "\nSampai jumpa! Terima kasih sudah mampir ke Toko Alat Tulis :)\n";
                appJalan = false;
            }

        } catch (const AuthException &e) {
            tampilError(e.what());
            cout << "Program ditutup karena percobaan login melebihi batas.\n";
            return 1;

        } catch (const TokoException &e) {
            tampilError(e.what());
            tekanEnter();

        } catch (const exception &e) {
            tampilError(string("System error: ") + e.what());
            tekanEnter();
        }
    }

    return 0;
}
