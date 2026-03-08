#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// untuk batas menampung data
const int BATAS_USER   = 50;
const int BATAS_BARANG = 100;

// --- nested struct kategori ---
struct Kategori {
    string namaKategori;
    string keteranganKategori;
};

// --- struct barang ---
struct Barang {
    int    kodeBarang;
    string namaBarang;
    double hargaBarang;
    int    stokBarang;
    Kategori kategoriBarang; // nested struct
};

// --- struct akun user ---
struct Akun {
    string namaUser;   // username
    string nimUser;    // password
    bool   isAdmin;    // true = admin, false = user biasa
};

// untuk data keseluruhan
Akun   daftarAkun[BATAS_USER];
int    jumlahAkun  = 0;

Barang dataBarang[BATAS_BARANG];
int    jumlahBarang = 0;
int    kodeOtomatis = 1;

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

            int cobaMaksimal = 3;
            int sisaCoba     = cobaMaksimal;
            bool loginOke    = false;
            int  indexAkun   = -1;

            while (sisaCoba > 0 && !loginOke) {
                string inputNama, inputNim;

                cout << "Tulis username kamu dong  : ";
                getline(cin, inputNama);
                cout << "Password nya juga ya   : ";
                getline(cin, inputNim);

                for (int i = 0; i < jumlahAkun; i++) {
                    if (daftarAkun[i].namaUser == inputNama &&
                        daftarAkun[i].nimUser   == inputNim) {
                        loginOke  = true;
                        indexAkun = i;
                        break;
                    }
                }

                if (loginOke) {
                    cout << "\nLogin berhasil! Selamat datang, " << inputNama << endl;
                    cout << "Tekan Enter untuk lanjut...";
                    cin.ignore();
                } else {
                    sisaCoba--;
                    if (sisaCoba > 0) {
                        cout << "Hmm, username/password nya salah nih. Sisa coba: "
                             << sisaCoba << "\n\n";
                    } else {
                        cout << "\nWaduh sudah 3 kali salah ni. Program ditutup ya.\n";
                        return 0;
                    }
                }
            }

            // ==========================================
            // cek admin atau user biasa
            // ==========================================
            if (daftarAkun[indexAkun].isAdmin) {

                // ======================================
                // MENU ADMIN
                // ======================================
                bool menuAdmin = true;
                while (menuAdmin) {

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

                    // --- lihat barang (admin) ---
                    if (pilihAdmin == 1) {

                        cout << "|=================================================================|" << endl;
                        cout << "|                           DAFTAR BARANG                         |" << endl;
                        cout << "|=================================================================|" << endl;

                        if (jumlahBarang == 0) {
                            cout << "Belum ada barang nih.\n";
                        } else {
                            cout << left
                                 << "+" << setfill('-') << setw(5)  << "-" << "+"
                                                        << setw(22) << "-" << "+"
                                                        << setw(12) << "-" << "+"
                                                        << setw(8)  << "-" << "+"
                                                        << setw(14) << "-" << "+"
                                 << setfill(' ') << endl;
                            cout << "| " << left << setw(3)  << "No"
                                 << " | "        << setw(20) << "Nama Barang"
                                 << " | "        << setw(10) << "Harga (Rp)"
                                 << " | "        << setw(6)  << "Stok"
                                 << " | "        << setw(12) << "Kategori"
                                 << " |" << endl;
                            cout << left
                                 << "+" << setfill('-') << setw(5)  << "-" << "+"
                                                        << setw(22) << "-" << "+"
                                                        << setw(12) << "-" << "+"
                                                        << setw(8)  << "-" << "+"
                                                        << setw(14) << "-" << "+"
                                 << setfill(' ') << endl;
                            for (int i = 0; i < jumlahBarang; i++) {
                                cout << "| " << left  << setw(3)  << i + 1
                                     << " | "         << setw(20) << dataBarang[i].namaBarang
                                     << " | " << right << setw(10) << fixed << setprecision(0)
                                                       << dataBarang[i].hargaBarang
                                     << " | " << right << setw(6)  << dataBarang[i].stokBarang
                                     << " | " << left  << setw(12) << dataBarang[i].kategoriBarang.namaKategori
                                     << " |" << endl;
                            }
                            cout << left
                                 << "+" << setfill('-') << setw(5)  << "-" << "+"
                                                        << setw(22) << "-" << "+"
                                                        << setw(12) << "-" << "+"
                                                        << setw(8)  << "-" << "+"
                                                        << setw(14) << "-" << "+"
                                 << setfill(' ') << endl;
                            cout << "Total: " << jumlahBarang << " barang\n";
                        }
                        cout << "\nTekan Enter untuk kembali...";
                        cin.ignore();

                    // --- tambah barang ---
                    } else if (pilihAdmin == 2) {

                        cout << "|==============================================|" << endl;
                        cout << "|               TAMBAH BARANG BARU             |" << endl;
                        cout << "|==============================================|" << endl;

                        if (jumlahBarang >= BATAS_BARANG) {
                            cout << "Data barang sudah penuh.\n";
                        } else {
                            Barang barangBaru;
                            barangBaru.kodeBarang = kodeOtomatis++;

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


                            dataBarang[jumlahBarang] = barangBaru;
                            jumlahBarang++;

                            cout << "Barang '" << barangBaru.namaBarang
                                 << "' berhasil ditambahkan!\n";
                        }
                        cout << "Tekan Enter untuk kembali...";
                        cin.ignore();

                    // --- update barang ---
                    } else if (pilihAdmin == 3) {

                        cout << "|=================================================================|" << endl;
                        cout << "|                           UPDATE BARANG                         |" << endl;
                        cout << "|=================================================================|" << endl;

                        if (jumlahBarang == 0) {
                            cout << "Belum ada barang.\n";
                        } else {
                            for (int i = 0; i < jumlahBarang; i++) {
                                cout << "| " << left
                                     << setw(2)  << i + 1 << ". "
                                     << setw(18) << dataBarang[i].namaBarang
                                     << " Stok: "     << setw(4) << dataBarang[i].stokBarang
                                     << " Harga: "    << fixed << setprecision(0)
                                     << setw(6)  << dataBarang[i].hargaBarang
                                     << " Kat: " << setw(10) << dataBarang[i].kategoriBarang.namaKategori
                                     << " |" << endl;
                            }
                            cout << "|=================================================================|" << endl;

                            int nomorUpdate;
                            cout << "\nMasukkan nomor barang yang ingin diupdate: ";
                            cin  >> nomorUpdate;
                            cin.ignore();

                            if (nomorUpdate < 1 || nomorUpdate > jumlahBarang) {
                                cout << "Maaf nomor tersebut tidak valid.\n";
                            } else {
                                int indeksUpdate = nomorUpdate - 1;
                                cout << "\n--- Update Barang: " << dataBarang[indeksUpdate].namaBarang << " ---\n";
                                cout << "(Kosongkan / tekan Enter jika tidak ingin mengubah)\n\n";

                                string inputBaru;

                                cout << "Nama baru      [" << dataBarang[indeksUpdate].namaBarang << "]: ";
                                getline(cin, inputBaru);
                                if (!inputBaru.empty()) dataBarang[indeksUpdate].namaBarang = inputBaru;

                                cout << "Stok baru      [" << dataBarang[indeksUpdate].stokBarang << "]: ";
                                getline(cin, inputBaru);
                                if (!inputBaru.empty()) dataBarang[indeksUpdate].stokBarang = stoi(inputBaru);

                                cout << "Harga baru     [" << fixed << setprecision(0)
                                     << dataBarang[indeksUpdate].hargaBarang << "]: ";
                                getline(cin, inputBaru);
                                if (!inputBaru.empty()) dataBarang[indeksUpdate].hargaBarang = stod(inputBaru);

                                cout << "Kategori baru  [" << dataBarang[indeksUpdate].kategoriBarang.namaKategori << "]: ";
                                getline(cin, inputBaru);
                                if (!inputBaru.empty()) dataBarang[indeksUpdate].kategoriBarang.namaKategori = inputBaru;


                                cout << "\nData barang berhasil diperbarui!\n";
                            }
                        }
                        cout << "Tekan Enter untuk kembali...";
                        cin.ignore();

                    // --- hapus barang ---
                    } else if (pilihAdmin == 4) {

                        cout << "|=================================================================|" << endl;
                        cout << "|                           HAPUS BARANG                          |" << endl;
                        cout << "|=================================================================|" << endl;

                        if (jumlahBarang == 0) {
                            cout << "Belum ada barang.\n";
                        } else {
                            for (int i = 0; i < jumlahBarang; i++) {
                                cout << "| " << left
                                     << setw(2)  << i + 1 << ". "
                                     << setw(18) << dataBarang[i].namaBarang
                                     << " Stok: "     << setw(4) << dataBarang[i].stokBarang
                                     << " Harga: "    << fixed << setprecision(0)
                                     << setw(6)  << dataBarang[i].hargaBarang
                                     << " Kat: " << setw(10) << dataBarang[i].kategoriBarang.namaKategori
                                     << " |" << endl;
                            }
                            cout << "|=================================================================|" << endl;

                            int nomorHapus;
                            cout << "\nMasukkan nomor barang yang ingin dihapus: ";
                            cin  >> nomorHapus;
                            cin.ignore();

                            if (nomorHapus < 1 || nomorHapus > jumlahBarang) {
                                cout << "Maaf Nomor tersebut tidak valid.\n";
                            } else {
                                int    indeksHapus = nomorHapus - 1;
                                string namaHapus   = dataBarang[indeksHapus].namaBarang;

                                // geser data ke kiri
                                for (int j = indeksHapus; j < jumlahBarang - 1; j++) {
                                    dataBarang[j] = dataBarang[j + 1];
                                }
                                jumlahBarang--;

                                cout << "Barang '" << namaHapus << "' berhasil dihapus!\n";
                            }
                        }
                        cout << "Tekan Enter untuk kembali...";
                        cin.ignore();

                    // --- logout admin ---
                    } else if (pilihAdmin == 5) {
                        cout << "Logout berhasil!\n";
                        cout << "Tekan Enter untuk kembali ke menu utama...";
                        cin.ignore();
                        menuAdmin = false;

                    } else {
                        cout << "Pilihannya tidak ada, coba lagi.\n";
                    }

                } // end while menu admin

            } else {

                // ======================================
                // MENU PENGGUNA BIASA
                // ======================================
                bool menuUser = true;
                while (menuUser) {

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

                    // --- lihat barang (user biasa) ---
                    if (pilihUser == 1) {

                        cout << "|=================================================================|" << endl;
                        cout << "|                          DAFTAR BARANG                          |" << endl;
                        cout << "|=================================================================|" << endl;

                        if (jumlahBarang == 0) {
                            cout << "Belum ada barang nih.\n";
                        } else {
                            cout << left
                                 << "+" << setfill('-') << setw(5)  << "-" << "+"
                                                        << setw(22) << "-" << "+"
                                                        << setw(12) << "-" << "+"
                                                        << setw(8)  << "-" << "+"
                                                        << setw(14) << "-" << "+"
                                 << setfill(' ') << endl;
                            cout << "| " << left << setw(3)  << "No"
                                 << " | "        << setw(20) << "Nama Barang"
                                 << " | "        << setw(10) << "Harga (Rp)"
                                 << " | "        << setw(6)  << "Stok"
                                 << " | "        << setw(12) << "Kategori"
                                 << " |" << endl;
                            cout << left
                                 << "+" << setfill('-') << setw(5)  << "-" << "+"
                                                        << setw(22) << "-" << "+"
                                                        << setw(12) << "-" << "+"
                                                        << setw(8)  << "-" << "+"
                                                        << setw(14) << "-" << "+"
                                 << setfill(' ') << endl;
                            for (int i = 0; i < jumlahBarang; i++) {
                                cout << "| " << left  << setw(3)  << i + 1
                                     << " | "         << setw(20) << dataBarang[i].namaBarang
                                     << " | " << right << setw(10) << fixed << setprecision(0)
                                                       << dataBarang[i].hargaBarang
                                     << " | " << right << setw(6)  << dataBarang[i].stokBarang
                                     << " | " << left  << setw(12) << dataBarang[i].kategoriBarang.namaKategori
                                     << " |" << endl;
                            }
                            cout << left
                                 << "+" << setfill('-') << setw(5)  << "-" << "+"
                                                        << setw(22) << "-" << "+"
                                                        << setw(12) << "-" << "+"
                                                        << setw(8)  << "-" << "+"
                                                        << setw(14) << "-" << "+"
                                 << setfill(' ') << endl;
                            cout << "Total: " << jumlahBarang << " barang\n";
                        }
                        cout << "\nTekan Enter untuk kembali...";
                        cin.ignore();

                    // --- logout user ---
                    } else if (pilihUser == 2) {
                        cout << "Logout berhasil! Terima kasih sudah mampir\n";
                        cout << "Tekan Enter untuk kembali ke menu utama...";
                        cin.ignore();
                        menuUser = false;

                    } else {
                        cout << "Pilihannya tidak ada, coba lagi.\n";
                    }

                } // end while menu user
            }

        // ==========================================
        // REGISTER
        // ==========================================
        } else if (pilihAwal == 2) {

            cout << "|==============================================|" << endl;
            cout << "|               REGISTER AKUN BARU             |" << endl;
            cout << "|==============================================|" << endl;

            if (jumlahAkun >= BATAS_USER) {
                cout << "Maaf, pendaftaran akun sudah penuh.\n";
            } else {
                Akun akunBaru;
                cout << "Tulis username kamu ya : ";
                getline(cin, akunBaru.namaUser);

                // cek nama udah kepake belum
                bool namaSudahDipakai = false;
                for (int i = 0; i < jumlahAkun; i++) {
                    if (daftarAkun[i].namaUser == akunBaru.namaUser) {
                        namaSudahDipakai = true;
                        break;
                    }
                }

                if (namaSudahDipakai) {
                    cout << "Nama itu sudah dipakai, coba nama lain.\n";
                } else {
                    cout << "Password nya juga ya        : ";
                    getline(cin, akunBaru.nimUser);
                    akunBaru.isAdmin = false; // user biasa

                    daftarAkun[jumlahAkun] = akunBaru;
                    jumlahAkun++;

                    cout << "Akun berhasil dibuat!\n";
                }
            }
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