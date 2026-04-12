#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int BATAS_USER   = 50;
const int BATAS_BARANG = 100;

// Untuk Struck

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

// Untuk Data Keseluruhan

Akun   daftarAkun[BATAS_USER];
int    jumlahAkun  = 0;

Barang dataBarang[BATAS_BARANG];
int    jumlahBarang = 0;
int    kodeOtomatis = 1;

// Untuk Prosedur Dan Fungsi Menampilkan Tabel

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

// Tampil barang versi admin
void tampilBarang(Barang *semuaBarang, int totalBarang, bool tampilKode) {
    cout << "|=================================================================|" << endl;
    cout << "|                         DAFTAR BARANG                           |" << endl;
    cout << "|=================================================================|" << endl;

    if (totalBarang == 0) {
        cout << "Belum ada barang nih.\n";
        return;
    }

    cetakHeader();
    for (int i = 0; i < totalBarang; i++) {
        Barang *ptrBarang = &semuaBarang[i];
        cout << "| " << left  << setw(3)  << i + 1
             << " | "         << setw(20) << ptrBarang->namaBarang
             << " | " << right << setw(10) << fixed << setprecision(0)
                               << ptrBarang->hargaBarang
             << " | " << right << setw(6)  << ptrBarang->stokBarang
             << " | " << left  << setw(12) << ptrBarang->kategoriBarang.namaKategori
             << " |" << endl;
    }
    cetakGaris();
    cout << "Total: " << totalBarang << " barang\n";
}

// Tampil barang versi user biasa (overloading)
void tampilBarang(Barang *semuaBarang, int totalBarang) {
    cout << "|=================================================================|" << endl;
    cout << "|                         DAFTAR BARANG                           |" << endl;
    cout << "|=================================================================|" << endl;

    if (totalBarang == 0) {
        cout << "Belum ada barang nih.\n";
        return;
    }

    cetakHeader();
    int adaTersedia = 0;
    for (int i = 0; i < totalBarang; i++) {
        Barang *ptrBarang = &semuaBarang[i];
        if (ptrBarang->stokBarang > 0) {
            cout << "| " << left  << setw(3)  << i + 1
                 << " | "         << setw(20) << ptrBarang->namaBarang
                 << " | " << right << setw(10) << fixed << setprecision(0)
                                   << ptrBarang->hargaBarang
                 << " | " << right << setw(6)  << ptrBarang->stokBarang
                 << " | " << left  << setw(12) << ptrBarang->kategoriBarang.namaKategori
                 << " |" << endl;
            adaTersedia++;
        }
    }
    cetakGaris();
    cout << "Tersedia: " << adaTersedia << " jenis barang\n";
}

// Fungsi CRUD Dari Pt Sebelumnya

void tambahBarang(Barang semuaBarang[], int &totalBarang, int &kodeUrut) {
    cout << "|==============================================|" << endl;
    cout << "|              TAMBAH BARANG BARU              |" << endl;
    cout << "|==============================================|" << endl;

    if (totalBarang >= BATAS_BARANG) {
        cout << "Data barang sudah penuh nih.\n";
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

    Barang *ptrSlot = &semuaBarang[totalBarang];
    *ptrSlot = barangBaru;
    totalBarang++;

    cout << "Barang '" << barangBaru.namaBarang << "' berhasil ditambahkan!\n";
}

void updateSatuBarang(Barang *ptrBarangDipilih) {
    cout << "\n Update Barang: " << ptrBarangDipilih->namaBarang << " \n";
    cout << "(Kosongkan atau tekan Enter jika tidak ingin mengubah)\n\n";

    string inputBaru;

    cout << "Nama baru      [" << ptrBarangDipilih->namaBarang << "]: ";
    getline(cin, inputBaru);
    if (!inputBaru.empty()) ptrBarangDipilih->namaBarang = inputBaru;

    cout << "Stok baru      [" << ptrBarangDipilih->stokBarang << "]: ";
    getline(cin, inputBaru);
    if (!inputBaru.empty()) ptrBarangDipilih->stokBarang = stoi(inputBaru);

    cout << "Harga baru     [" << fixed << setprecision(0)
         << ptrBarangDipilih->hargaBarang << "]: ";
    getline(cin, inputBaru);
    if (!inputBaru.empty()) ptrBarangDipilih->hargaBarang = stod(inputBaru);

    cout << "Kategori baru  [" << ptrBarangDipilih->kategoriBarang.namaKategori << "]: ";
    getline(cin, inputBaru);
    if (!inputBaru.empty()) ptrBarangDipilih->kategoriBarang.namaKategori = inputBaru;

    cout << "\nOke! Data barang berhasil diperbarui!\n";
}

void updateBarang(Barang semuaBarang[], int totalBarang) {
    cout << "|=================================================================|" << endl;
    cout << "|                         UPDATE BARANG                           |" << endl;
    cout << "|=================================================================|" << endl;

    if (totalBarang == 0) {
        cout << "Belum ada barang ni.\n";
        return;
    }

    for (int i = 0; i < totalBarang; i++) {
        cout << "| " << left << setw(2) << i + 1 << ". "
             << left << setw(12) << semuaBarang[i].namaBarang
             << " Stok: "  << left << setw(4) << semuaBarang[i].stokBarang
             << " Harga: " << left << setw(7) << fixed << setprecision(0)
                           << semuaBarang[i].hargaBarang
             << " Kat: "   << left << setw(16)
                           << semuaBarang[i].kategoriBarang.namaKategori
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

    Barang *ptrPilihan = &semuaBarang[nomorUpdate - 1];
    updateSatuBarang(ptrPilihan);
}

void hapusBarang(Barang semuaBarang[], int &totalBarang) {
    cout << "|=================================================================|" << endl;
    cout << "|                         HAPUS BARANG                            |" << endl;
    cout << "|=================================================================|" << endl;

    if (totalBarang == 0) {
        cout << "Belum ada barang ni.\n";
        return;
    }

    for (int i = 0; i < totalBarang; i++) {
        cout << "| " << left << setw(2) << i + 1 << ". "
             << left << setw(12) << semuaBarang[i].namaBarang
             << " Stok: "  << left << setw(4) << semuaBarang[i].stokBarang
             << " Harga: " << left << setw(7) << fixed << setprecision(0)
                           << semuaBarang[i].hargaBarang
             << " Kat: "   << left << setw(16)
                           << semuaBarang[i].kategoriBarang.namaKategori
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

    for (int j = indeksHapus; j < totalBarang - 1; j++) {
        Barang *ptrKiri  = &semuaBarang[j];
        Barang *ptrKanan = &semuaBarang[j + 1];
        *ptrKiri = *ptrKanan;
    }
    totalBarang--;

    cout << "Barang '" << namaHapus << "' berhasil dihapus!\n";
}

// Untuk Fungsi Akun

bool cekNamaSudahDipakai(Akun *semuaAkun, int totalAkun, string namaCek) {
    for (int i = 0; i < totalAkun; i++) {
        Akun *ptrAkun = &semuaAkun[i];
        if (ptrAkun->namaUser == namaCek) {
            return true;
        }
    }
    return false;
}

void registerAkun(Akun semuaAkun[], int &totalAkun) {
    cout << "|==============================================|" << endl;
    cout << "|              REGISTER AKUN BARU              |" << endl;
    cout << "|==============================================|" << endl;

    if (totalAkun >= BATAS_USER) {
        cout << "Maaf, pendaftaran akun sudah penuh.\n";
        return;
    }

    Akun akunBaru;
    cout << "Tulis username kamu ya       : ";
    getline(cin, akunBaru.namaUser);

    if (cekNamaSudahDipakai(semuaAkun, totalAkun, akunBaru.namaUser)) {
        cout << "Nama itu sudah dipakai, coba nama lain.\n";
        return;
    }

    cout << "Password nya juga ya         : ";
    getline(cin, akunBaru.nimUser);
    akunBaru.isAdmin = false;

    Akun *ptrSlotAkun = &semuaAkun[totalAkun];
    *ptrSlotAkun = akunBaru;
    totalAkun++;

    cout << "Akun berhasil dibuat!\n";
}

int loginRekursif(Akun *semuaAkun, int totalAkun, int sisaCoba) {
    if (sisaCoba <= 0) {
        cout << "\nWaduh sudah 3 kali salah ni. Program ditutup ya.\n";
        return -2;
    }

    string inputNama, inputNim;
    cout << "Tulis username kamu dong  : ";
    getline(cin, inputNama);
    cout << "Password nya juga ya      : ";
    getline(cin, inputNim);

    for (int i = 0; i < totalAkun; i++) {
        Akun *ptrAkun = &semuaAkun[i];
        if (ptrAkun->namaUser == inputNama &&
            ptrAkun->nimUser  == inputNim) {
            cout << "\nLogin berhasil! Selamat datang, " << inputNama << endl;
            cout << "Tekan Enter untuk lanjut...";
            cin.ignore();
            return i;
        }
    }

    int sisaBerikutnya = sisaCoba - 1;
    if (sisaBerikutnya > 0) {
        cout << "Waduh, username dan password nya salah nih. Sisa coba: "
             << sisaBerikutnya << "\n\n";
    }
    return loginRekursif(semuaAkun, totalAkun, sisaBerikutnya);
}

// Untuk Fungsi Sorting

// 1. SELECTION SORT - Nama Barang Ascending (A ke Z)
//    Mencari elemen terkecil lalu tukar ke posisi paling kiri
void selectionSortNamaAscending(Barang semuaBarang[], int totalBarang) {
    for (int posisiAwal = 0; posisiAwal < totalBarang - 1; posisiAwal++) {
        int indeksNamaTerkecil = posisiAwal;

        // Cari nama terkecil (A-Z) dari posisi kanan
        for (int posisiCek = posisiAwal + 1; posisiCek < totalBarang; posisiCek++) {
            if (semuaBarang[posisiCek].namaBarang < semuaBarang[indeksNamaTerkecil].namaBarang) {
                indeksNamaTerkecil = posisiCek;
            }
        }

        // Untuk Tukar Jika Ditemukan Yang Lebih Kecil
        if (indeksNamaTerkecil != posisiAwal) {
            Barang barangSementara         = semuaBarang[posisiAwal];
            semuaBarang[posisiAwal]        = semuaBarang[indeksNamaTerkecil];
            semuaBarang[indeksNamaTerkecil] = barangSementara;
        }
    }
}

// 2. BUBBLE SORT - Harga Barang Descending (besar ke kecil)
//    Bandingkan dua elemen berdekatan, lalu gelembungkan yang terbesar ke kiri
void bubbleSortHargaDescending(Barang semuaBarang[], int totalBarang) {
    for (int putaranLuar = 0; putaranLuar < totalBarang - 1; putaranLuar++) {
        bool adaPertukaran = false;

        for (int putaranDalam = 0; putaranDalam < totalBarang - 1 - putaranLuar; putaranDalam++) {
            // Descending: kalau kiri lebih kecil dari kanan → tukar
            if (semuaBarang[putaranDalam].hargaBarang < semuaBarang[putaranDalam + 1].hargaBarang) {
                Barang barangSementara          = semuaBarang[putaranDalam];
                semuaBarang[putaranDalam]       = semuaBarang[putaranDalam + 1];
                semuaBarang[putaranDalam + 1]   = barangSementara;
                adaPertukaran = true;
            }
        }

        // Proses: berhenti jika tidak ada pertukaran
        if (!adaPertukaran) break;
    }
}

// 3. INSERTION SORT - Stok Barang Ascending (sedikit ke banyak)
//    Ambil satu elemen, lalu geser elemen yang lebih besar ke kanan, kemudian sisipkan
void insertionSortStokAscending(Barang semuaBarang[], int totalBarang) {
    for (int posisiSisip = 1; posisiSisip < totalBarang; posisiSisip++) {
        Barang barangYangDisisipkan = semuaBarang[posisiSisip];
        int    posisiGeser          = posisiSisip - 1;

        // Geser elemen yang lebih besar ke kanan
        while (posisiGeser >= 0 &&
               semuaBarang[posisiGeser].stokBarang > barangYangDisisipkan.stokBarang) {
            semuaBarang[posisiGeser + 1] = semuaBarang[posisiGeser];
            posisiGeser--;
        }

        // Sisipkan elemen ke posisi yang tepat
        semuaBarang[posisiGeser + 1] = barangYangDisisipkan;
    }
}

// Fungsi salin array barang (agar data asli tidak berubah saat sorting)
void salinDataBarang(Barang sumber[], Barang tujuan[], int totalBarang) {
    for (int i = 0; i < totalBarang; i++) {
        tujuan[i] = sumber[i];
    }
}

// Menu Sorting (dipanggil dari menu admin)
void menuSorting(Barang *semuaBarang, int totalBarang) {
    if (totalBarang == 0) {
        cout << "Belum ada barang untuk diurutkan.\n";
        return;
    }

    // Buat salinan data agar data asli tidak berubah
    Barang dataSortir[BATAS_BARANG];

    bool menuSortingJalan = true;
    while (menuSortingJalan) {

        cout << "|==============================================|" << endl;
        cout << "|               MENU SORTING BARANG            |" << endl;
        cout << "|==============================================|" << endl;
        cout << "|1. Selection Sort - Nama A ke Z (Ascending)   |" << endl;
        cout << "|2. Bubble Sort    - Harga Tertinggi Dulu      |" << endl;
        cout << "|   (Descending)                               |" << endl;
        cout << "|3. Insertion Sort - Stok Terkecil Dulu        |" << endl;
        cout << "|   (Ascending)                                |" << endl;
        cout << "|4. Kembali                                    |" << endl;
        cout << "|==============================================|" << endl;
        cout << "Pilih menu 1-4 yuk: ";

        int pilihSorting;
        cin >> pilihSorting;
        cin.ignore();

        if (pilihSorting == 1) {
            // Salin data asli ke dataSortir
            salinDataBarang(semuaBarang, dataSortir, totalBarang);

            cout << "\nSelection Sort Nama Barang Dari A Ke Z\n";
            selectionSortNamaAscending(dataSortir, totalBarang);
            tampilBarang(dataSortir, totalBarang, true);

        } else if (pilihSorting == 2) {
            salinDataBarang(semuaBarang, dataSortir, totalBarang);

            cout << "\nBubble Sort Harga Tertinggi Ke Terendah\n";
            bubbleSortHargaDescending(dataSortir, totalBarang);
            tampilBarang(dataSortir, totalBarang, true);

        } else if (pilihSorting == 3) {
            salinDataBarang(semuaBarang, dataSortir, totalBarang);

            cout << "\nInsertion Sort Stok Terkecil Ke Terbanyak\n";
            insertionSortStokAscending(dataSortir, totalBarang);
            tampilBarang(dataSortir, totalBarang, true);

        } else if (pilihSorting == 4) {
            menuSortingJalan = false;

        } else {
            cout << "Waduh Pilihan tidak ada, coba lagi.\n";
        }

        if (pilihSorting >= 1 && pilihSorting <= 3) {
            cout << "\nTekan Enter untuk kembali...";
            cin.ignore();
        }

    } // end while menu sorting
}

// Untuk Menu Admin Dan User

void menuAdmin(Barang *semuaBarang, int &totalBarang, int &kodeUrut) {
    bool menuAdminJalan = true;
    while (menuAdminJalan) {

        cout << "|==============================================|" << endl;
        cout << "|                  MENU ADMIN                  |" << endl;
        cout << "|==============================================|" << endl;
        cout << "|1. Lihat Barang                               |" << endl;
        cout << "|2. Tambah Barang                              |" << endl;
        cout << "|3. Update Barang                              |" << endl;
        cout << "|4. Hapus Barang                               |" << endl;
        cout << "|5. Sorting Barang                             |" << endl;
        cout << "|6. Logout                                     |" << endl;
        cout << "|==============================================|" << endl;
        cout << "Pilih menu 1-6 yuk: ";

        int pilihAdmin;
        cin >> pilihAdmin;
        cin.ignore();

        if (pilihAdmin == 1) {
            tampilBarang(semuaBarang, totalBarang, true);

        } else if (pilihAdmin == 2) {
            tambahBarang(semuaBarang, totalBarang, kodeUrut);

        } else if (pilihAdmin == 3) {
            updateBarang(semuaBarang, totalBarang);

        } else if (pilihAdmin == 4) {
            hapusBarang(semuaBarang, totalBarang);

        } else if (pilihAdmin == 5) {
            menuSorting(semuaBarang, totalBarang);

        } else if (pilihAdmin == 6) {
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

void menuUser(Barang *semuaBarang, int totalBarang) {
    bool menuUserJalan = true;
    while (menuUserJalan) {

        cout << "|==============================================|" << endl;
        cout << "|                MENU PENGGUNA                 |" << endl;
        cout << "|==============================================|" << endl;
        cout << "|1. Lihat Barang                               |" << endl;
        cout << "|2. Logout                                     |" << endl;
        cout << "|==============================================|" << endl;
        cout << "Pilih menu 1-2 yuk: ";

        int pilihUser;
        cin >> pilihUser;
        cin.ignore();

        if (pilihUser == 1) {
            tampilBarang(semuaBarang, totalBarang);
            cout << "\nTekan Enter untuk kembali...";
            cin.ignore();

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

// Untuk Fungsi Main 
int main() {

    // Inisialisasi data barang awal
    dataBarang[0] = {kodeOtomatis++, "Buku Tulis", 8000,  100, {"Buku",       "Buku tulis 58 lembar"}};
    dataBarang[1] = {kodeOtomatis++, "Penggaris",  5000,   75, {"Alat Ukur",  "Penggaris 30cm plastik"}};
    dataBarang[2] = {kodeOtomatis++, "Penghapus",  2000,  120, {"Alat Tulis", "Penghapus putih lembut"}};
    dataBarang[3] = {kodeOtomatis++, "Pensil 2B",  3000,   90, {"Alat Tulis", "Pensil untuk menggambar"}};
    dataBarang[4] = {kodeOtomatis++, "Peraut",     2500,   60, {"Alat Tulis", "Peraut pensil putar"}};
    jumlahBarang  = 5;

    // Inisialisasi akun admin
    daftarAkun[0] = {"komang", "003", true};
    jumlahAkun    = 1;

    // Pointer ke array global
    Barang *ptrDataBarang = dataBarang;
    Akun   *ptrDaftarAkun = daftarAkun;

    // Untuk Kata Sambutan
    cout << "|==============================================|" << endl;
    cout << "|      SELAMAT DATANG DI TOKO ALAT TULIS       |" << endl;
    cout << "|==============================================|" << endl;
    cout << "Halo! Mau cari alat tulis apa hari ini?" << endl;
    cout << "Kami punya semua yang kamu butuhkan." << endl;
    cout << "\nTekan Enter untuk lanjut ke menu utama..";
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
        cout << "Pilih Menu 1-3 yuk: ";

        int pilihAwal;
        cin >> pilihAwal;
        cin.ignore();

        if (pilihAwal == 1) {

            cout << "|==============================================|" << endl;
            cout << "|                  LOGIN AKUN                  |" << endl;
            cout << "|==============================================|" << endl;

            int indeksAkun = loginRekursif(ptrDaftarAkun, jumlahAkun, 3);

            if (indeksAkun == -2) {
                return 0;
            }

            Akun *ptrAkunLogin = &daftarAkun[indeksAkun];

            if (ptrAkunLogin->isAdmin) {
                menuAdmin(ptrDataBarang, jumlahBarang, kodeOtomatis);
            } else {
                menuUser(ptrDataBarang, jumlahBarang);
            }

        } else if (pilihAwal == 2) {
            registerAkun(daftarAkun, jumlahAkun);
            cout << "Tekan Enter untuk kembali ke menu utama...";
            cin.ignore();

        } else if (pilihAwal == 3) {
            cout << "\nSampai jumpa! Terimakasih sudah mampir ke toko Alat Tulis Kami :)\n";
            appJalan = false;

        } else {
            cout << "Pilihannya tidak ada, coba lagi ya.\n";
        }

    } // end while app

    return 0;
}