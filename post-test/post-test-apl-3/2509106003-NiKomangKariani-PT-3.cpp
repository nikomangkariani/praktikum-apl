#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int BATAS_USER   = 50;
const int BATAS_BARANG = 100;

// untuk nested struct kategori
struct Kategori {
    string namaKategori;
    string keteranganKategori;
};

// untuk struct barang
struct Barang {
    int    kodeBarang;
    string namaBarang;
    double hargaBarang;
    int    stokBarang;
    Kategori kategoriBarang;
};

// untuk struct akun user 
struct Akun {
    string namaUser;
    string nimUser;
    bool   isAdmin;
};

// untuk data keseluruhan
Akun   daftarAkun[BATAS_USER];
int    jumlahAkun  = 0;

Barang dataBarang[BATAS_BARANG];
int    jumlahBarang = 0;
int    kodeOtomatis = 1;


// ==========================================
// prosedur cetak garis tabel
// ==========================================
void cetakGaris() {
    cout << left
         << "+" << setfill('-') << setw(5)  << "-" << "+"
                                << setw(22) << "-" << "+"
                                << setw(12) << "-" << "+"
                                << setw(8)  << "-" << "+"
                                << setw(14) << "-" << "+"
         << setfill(' ') << endl;
}

// ==========================================
// prosedur cetak header tabel
// ==========================================
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

// ==========================================
// fungsi overloading tampilBarang - versi admin
// ==========================================
void tampilBarang(Barang semuaBarang[], int totalBarang, bool tampilKode) {
    cout << "|=================================================================|" << endl;
    cout << "|                           DAFTAR BARANG                         |" << endl;
    cout << "|=================================================================|" << endl;

    if (totalBarang == 0) {
        cout << "Belum ada barang nih.\n";
        return;
    }

    cetakHeader();
    for (int i = 0; i < totalBarang; i++) {
        cout << "| " << left  << setw(3)  << i + 1
             << " | "         << setw(20) << semuaBarang[i].namaBarang
             << " | " << right << setw(10) << fixed << setprecision(0)
                               << semuaBarang[i].hargaBarang
             << " | " << right << setw(6)  << semuaBarang[i].stokBarang
             << " | " << left  << setw(12) << semuaBarang[i].kategoriBarang.namaKategori
             << " |" << endl;
    }
    cetakGaris();
    cout << "Total: " << totalBarang << " barang\n";
}

// ==========================================
// fungsi overloading tampilBarang - versi user biasa
// (parameter beda, tanpa bool tampilKode)
// ==========================================
void tampilBarang(Barang semuaBarang[], int totalBarang) {
    cout << "|=================================================================|" << endl;
    cout << "|                           DAFTAR BARANG                         |" << endl;
    cout << "|=================================================================|" << endl;

    if (totalBarang == 0) {
        cout << "Belum ada barang nih.\n";
        return;
    }

    cetakHeader();
    int adaTersedia = 0;
    for (int i = 0; i < totalBarang; i++) {
        if (semuaBarang[i].stokBarang > 0) {
            cout << "| " << left  << setw(3)  << i + 1
                 << " | "         << setw(20) << semuaBarang[i].namaBarang
                 << " | " << right << setw(10) << fixed << setprecision(0)
                                   << semuaBarang[i].hargaBarang
                 << " | " << right << setw(6)  << semuaBarang[i].stokBarang
                 << " | " << left  << setw(12) << semuaBarang[i].kategoriBarang.namaKategori
                 << " |" << endl;
            adaTersedia++;
        }
    }
    cetakGaris();
    cout << "Tersedia: " << adaTersedia << " jenis barang\n";
}

// ==========================================
// fungsi tambah barang
// ==========================================
void tambahBarang(Barang semuaBarang[], int &totalBarang, int &kodeUrut) {
    cout << "|==============================================|" << endl;
    cout << "|               TAMBAH BARANG BARU             |" << endl;
    cout << "|==============================================|" << endl;

    if (totalBarang >= BATAS_BARANG) {
        cout << "Data barang udah penuh nih.\n";
        return;
    }

    Barang barangBaru;
    barangBaru.kodeBarang = kodeUrut++;

    cout << "Nama barang          : ";
    getline(cin, barangBaru.namaBarang);

    cout << "Stok                 : ";
    cin  >> barangBaru.stokBarang;
    cin.ignore();

    cout << "Harga                : ";
    cin  >> barangBaru.hargaBarang;
    cin.ignore();

    cout << "Kategori             : ";
    getline(cin, barangBaru.kategoriBarang.namaKategori);

    dataBarang[totalBarang] = barangBaru;
    totalBarang++;

    cout << "Barang '" << barangBaru.namaBarang << "' berhasil ditambahkan!\n";
}

// ==========================================
// fungsi update barang
// ==========================================
void updateBarang(Barang semuaBarang[], int totalBarang) {
    cout << "|=================================================================|" << endl;
    cout << "|                           UPDATE BARANG                         |" << endl;
    cout << "|=================================================================|" << endl;

    if (totalBarang == 0) {
        cout << "Belum ada barang.\n";
        return;
    }

    for (int i = 0; i < totalBarang; i++) {
        cout << "| " << left << setw(2) << i + 1 << ". "
             << left << setw(12) << semuaBarang[i].namaBarang
             << " Stok: "  << left << setw(4) << semuaBarang[i].stokBarang
             << " Harga: " << left << setw(7) << fixed << setprecision(0) << semuaBarang[i].hargaBarang
             << " Kat: "   << left << setw(16) << semuaBarang[i].kategoriBarang.namaKategori
             << "|" << endl;
    }
    cout << "|=================================================================|" << endl;

    int nomorUpdate;
    cout << "\nMasukkan nomor barang yang ingin diupdate: ";
    cin  >> nomorUpdate;
    cin.ignore();

    if (nomorUpdate < 1 || nomorUpdate > totalBarang) {
        cout << "Maaf nomor tersebut tidak valid.\n";
        return;
    }

    int indeksUpdate = nomorUpdate - 1;
    cout << "\n--- Update Barang: " << semuaBarang[indeksUpdate].namaBarang << " ---\n";
    cout << "(Kosongkan / tekan Enter jika tidak ingin mengubah)\n\n";

    string inputBaru;

    cout << "Nama baru      [" << semuaBarang[indeksUpdate].namaBarang << "]: ";
    getline(cin, inputBaru);
    if (!inputBaru.empty()) semuaBarang[indeksUpdate].namaBarang = inputBaru;

    cout << "Stok baru      [" << semuaBarang[indeksUpdate].stokBarang << "]: ";
    getline(cin, inputBaru);
    if (!inputBaru.empty()) semuaBarang[indeksUpdate].stokBarang = stoi(inputBaru);

    cout << "Harga baru     [" << fixed << setprecision(0)
         << semuaBarang[indeksUpdate].hargaBarang << "]: ";
    getline(cin, inputBaru);
    if (!inputBaru.empty()) semuaBarang[indeksUpdate].hargaBarang = stod(inputBaru);

    cout << "Kategori baru  [" << semuaBarang[indeksUpdate].kategoriBarang.namaKategori << "]: ";
    getline(cin, inputBaru);
    if (!inputBaru.empty()) semuaBarang[indeksUpdate].kategoriBarang.namaKategori = inputBaru;

    cout << "\nData barang berhasil diperbarui!\n";
}

// ==========================================
// fungsi hapus barang
// ==========================================
void hapusBarang(Barang semuaBarang[], int &totalBarang) {
    cout << "|=================================================================|" << endl;
    cout << "|                           HAPUS BARANG                          |" << endl;
    cout << "|=================================================================|" << endl;

    if (totalBarang == 0) {
        cout << "Belum ada barang.\n";
        return;
    }

    for (int i = 0; i < totalBarang; i++) {
        cout << "| " << left << setw(2) << i + 1 << ". "
             << left << setw(12) << semuaBarang[i].namaBarang
             << " Stok: "  << left << setw(4) << semuaBarang[i].stokBarang
             << " Harga: " << left << setw(7) << fixed << setprecision(0) << semuaBarang[i].hargaBarang
             << " Kat: "   << left << setw(16) << semuaBarang[i].kategoriBarang.namaKategori
             << "|" << endl;
    }
    cout << "|=================================================================|" << endl;

    int nomorHapus;
    cout << "\nMasukkan nomor barang yang ingin dihapus: ";
    cin  >> nomorHapus;
    cin.ignore();

    if (nomorHapus < 1 || nomorHapus > totalBarang) {
        cout << "Maaf Nomor tersebut tidak valid.\n";
        return;
    }

    int    indeksHapus = nomorHapus - 1;
    string namaHapus   = semuaBarang[indeksHapus].namaBarang;

    // geser data ke kiri
    for (int j = indeksHapus; j < totalBarang - 1; j++) {
        semuaBarang[j] = semuaBarang[j + 1];
    }
    totalBarang--;

    cout << "Barang '" << namaHapus << "' berhasil dihapus!\n";
}

// ==========================================
// fungsi cek nama sudah dipakai
// ==========================================
bool cekNamaSudahDipakai(Akun semuaAkun[], int totalAkun, string namaCek) {
    for (int i = 0; i < totalAkun; i++) {
        if (semuaAkun[i].namaUser == namaCek) {
            return true;
        }
    }
    return false;
}

// ==========================================
// fungsi register akun baru
// ==========================================
void registerAkun(Akun semuaAkun[], int &totalAkun) {
    cout << "|==============================================|" << endl;
    cout << "|               REGISTER AKUN BARU             |" << endl;
    cout << "|==============================================|" << endl;

    if (totalAkun >= BATAS_USER) {
        cout << "Maaf, pendaftaran akun sudah penuh.\n";
        return;
    }

    Akun akunBaru;
    cout << "Tulis username kamu ya : ";
    getline(cin, akunBaru.namaUser);

    if (cekNamaSudahDipakai(semuaAkun, totalAkun, akunBaru.namaUser)) {
        cout << "Nama itu sudah dipakai, coba nama lain.\n";
        return;
    }

    cout << "Password nya juga ya        : ";
    getline(cin, akunBaru.nimUser);
    akunBaru.isAdmin = false;

    semuaAkun[totalAkun] = akunBaru;
    totalAkun++;

    cout << "Akun berhasil dibuat!\n";
}

// ==========================================
// fungsi rekursif login
// dipanggil ulang tiap kali gagal login
// ==========================================
int loginRekursif(Akun semuaAkun[], int totalAkun, int sisaCoba) {

    // base case: sisa coba habis
    if (sisaCoba <= 0) {
        cout << "\nWaduh sudah 3 kali salah ni. Program ditutup ya.\n";
        return -2;
    }

    string inputNama, inputNim;
    cout << "Tulis username kamu dong  : ";
    getline(cin, inputNama);
    cout << "Password nya juga ya   : ";
    getline(cin, inputNim);

    for (int i = 0; i < totalAkun; i++) {
        if (semuaAkun[i].namaUser == inputNama &&
            semuaAkun[i].nimUser  == inputNim) {
            cout << "\nLogin berhasil! Selamat datang, " << inputNama << endl;
            cout << "Tekan Enter untuk lanjut...";
            cin.ignore();
            return i;
        }
    }

    // kalau salah, kurangi sisa coba lalu panggil diri sendiri lagi
    int sisaBerikutnya = sisaCoba - 1;
    if (sisaBerikutnya > 0) {
        cout << "Waduh, username/password nya salah nih. Sisa coba: "
             << sisaBerikutnya << "\n\n";
    }
    return loginRekursif(semuaAkun, totalAkun, sisaBerikutnya);
}

// ==========================================
// fungsi menu admin
// ==========================================
void menuAdmin(Barang semuaBarang[], int &totalBarang, int &kodeUrut) {
    bool menuAdminJalan = true;
    while (menuAdminJalan) {

        cout << "|==============================================|" << endl;
        cout << "|                  MENU ADMIN                  |" << endl;
        cout << "|==============================================|" << endl;
        cout << "|1. Lihat Barang                               |" << endl;
        cout << "|2. Tambah Barang                              |" << endl;
        cout << "|3. Update Barang                              |" << endl;
        cout << "|4. Hapus Barang                               |" << endl;
        cout << "|5. Logout                                     |" << endl;
        cout << "|==============================================|" << endl;
        cout << "Pilih menu 1-5 yuk: ";

        int pilihAdmin;
        cin >> pilihAdmin;
        cin.ignore();

        // untuk lihat barang ---
        if (pilihAdmin == 1) {
            tampilBarang(semuaBarang, totalBarang, true);

        // untuk tambah barang
        } else if (pilihAdmin == 2) {
            tambahBarang(semuaBarang, totalBarang, kodeUrut);

        // untuk update barang
        } else if (pilihAdmin == 3) {
            updateBarang(semuaBarang, totalBarang);

        // untuk hapus barang
        } else if (pilihAdmin == 4) {
            hapusBarang(semuaBarang, totalBarang);

        // untuk logout admin
        } else if (pilihAdmin == 5) {
            cout << "Logout berhasil!\n";
            cout << "Tekan Enter untuk kembali ke menu utama...";
            cin.ignore();
            menuAdminJalan = false;

        } else {
            cout << "Pilihannya tidak ada, coba lagi.\n";
        }

        if (pilihAdmin >= 1 && pilihAdmin <= 4) {
            cout << "\nTekan Enter untuk kembali...";
            cin.ignore();
        }

    } // end while menu admin
}

// ==========================================
// fungsi menu user biasa
// ==========================================
void menuUser(Barang semuaBarang[], int totalBarang) {
    bool menuUserJalan = true;
    while (menuUserJalan) {

        cout << "|==============================================|" << endl;
        cout << "|                 MENU PENGGUNA                |" << endl;
        cout << "|==============================================|" << endl;
        cout << "|1. Lihat Barang                               |" << endl;
        cout << "|2. Logout                                     |" << endl;
        cout << "|==============================================|" << endl;
        cout << "Pilih menu 1-2: ";

        int pilihUser;
        cin >> pilihUser;
        cin.ignore();

        // untuk lihat barang
        if (pilihUser == 1) {
            tampilBarang(semuaBarang, totalBarang);
            cout << "\nTekan Enter untuk kembali...";
            cin.ignore();

        // untuk logout user
        } else if (pilihUser == 2) {
            cout << "Logout berhasil! Terima kasih sudah mampir\n";
            cout << "Tekan Enter untuk kembali ke menu utama...";
            cin.ignore();
            menuUserJalan = false;

        } else {
            cout << "Pilihannya tidak ada, coba lagi.\n";
        }

    } // end while menu user
}

int main() {

    // data barang awal
    dataBarang[0] = {kodeOtomatis++, "Buku Tulis",  8000,  100, {"Buku",       "Buku tulis 58 lembar"}};
    dataBarang[1] = {kodeOtomatis++, "Penggaris",   5000,   75, {"Alat Ukur",  "Penggaris 30cm plastik"}};
    dataBarang[2] = {kodeOtomatis++, "Penghapus",   2000,  120, {"Alat Tulis", "Penghapus putih lembut"}};
    dataBarang[3] = {kodeOtomatis++, "Pensil 2B",   3000,   90, {"Alat Tulis", "Pensil untuk menggambar"}};
    dataBarang[4] = {kodeOtomatis++, "Peraut",      2500,   60, {"Alat Tulis", "Peraut pensil putar"}};
    jumlahBarang  = 5;

    // untuk akun admin
    daftarAkun[0] = {"komang", "003", true};
    jumlahAkun    = 1;

    // untuk sambutan awal
    cout << "|==============================================|" << endl;
    cout << "|       SELAMAT DATANG DI TOKO ALAT TULIS      |" << endl;
    cout << "|==============================================|" << endl;
    cout << "Halo! Mau cari alat tulis apa hari ini?" << endl;
    cout << "Kami punya semua yang kamu butuhkan." << endl;
    cout << "\nTekan Enter untuk lanjut ke menu utama..";
    cin.ignore();

    bool appJalan = true;

    while (appJalan) {

        // ==========================================
        // menu utama
        // ==========================================
        cout << "|==============================================|" << endl;
        cout << "|          MENU UTAMA TOKO ALAT TULIS          |" << endl;
        cout << "|==============================================|" << endl;
        cout << "|1. Login                                      |" << endl;
        cout << "|2. Register                                   |" << endl;
        cout << "|3. Keluar                                     |" << endl;
        cout << "|==============================================|" << endl;
        cout << "Pilih 1, 2, atau 3, yuk: ";

        int pilihAwal;
        cin >> pilihAwal;
        cin.ignore();

        // ==========================================
        // LOGIN
        // ==========================================
        if (pilihAwal == 1) {

            cout << "|==============================================|" << endl;
            cout << "|                  LOGIN AKUN                  |" << endl;
            cout << "|==============================================|" << endl;

            // pakai fungsi rekursif, maksimal 3 kali coba
            int indexAkun = loginRekursif(daftarAkun, jumlahAkun, 3);

            if (indexAkun == -2) {
                return 0;
            }

            // cek admin atau user biasa
            if (daftarAkun[indexAkun].isAdmin) {
                menuAdmin(dataBarang, jumlahBarang, kodeOtomatis);
            } else {
                menuUser(dataBarang, jumlahBarang);
            }

        // ==========================================
        // REGISTER
        // ==========================================
        } else if (pilihAwal == 2) {
            registerAkun(daftarAkun, jumlahAkun);
            cout << "Tekan Enter untuk kembali ke menu utama...";
            cin.ignore();

        // ==========================================
        // KELUAR
        // ==========================================
        } else if (pilihAwal == 3) {
            cout << "\nsampai jumpa! Terimakasih sudah mampir ke toko Alat Tulis Kami :)\n";
            appJalan = false;

        } else {
            cout << "Pilihannya tidak ada, coba lagi ya.\n";
        }

    } // end while app

    return 0;
}