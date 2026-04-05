#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int BATAS_USER   = 50;
const int BATAS_BARANG = 100;

// Ini untuk Nested struct kategori barang
struct Kategori {
    string namaKategori;
    string keteranganKategori;
};

// Ini untuk Struct barang
// Point+: pointer pada struct digunakan di seluruh program
struct Barang {
    int      kodeBarang;
    string   namaBarang;
    double   hargaBarang;
    int      stokBarang;
    Kategori kategoriBarang;
};

// Ini untuk Struct akun user
struct Akun {
    string namaUser;
    string nimUser;   // Ini dipakai sebagai password (sesuai pada PT-3)
    bool   isAdmin;
};

// Untuk data keseluruhan
Akun   daftarAkun[BATAS_USER];
int    jumlahAkun  = 0;

Barang dataBarang[BATAS_BARANG];
int    jumlahBarang = 0;
int    kodeOtomatis = 1;

// Untuk prosedur cetak garis tabel
void cetakGaris() {
    cout << left
         << "+" << setfill('-') << setw(5)  << "-" << "+"
                                << setw(22) << "-" << "+"
                                << setw(12) << "-" << "+"
                                << setw(8)  << "-" << "+"
                                << setw(14) << "-" << "+"
         << setfill(' ') << endl;
}

// Ini untuk prosedur cetak header tabel
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

// Untuk Overloading tampilBarang versi admin
// Dengan menggunakan pointer pada struct Barang
// Parameter: Barang* (pointer ke array struct)

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
        // Menggunakan pointer untuk akses tiap elemen struct Barang
        Barang *ptrBarang = &semuaBarang[i];  // Address-of operator (&)
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

// Untuk Overloading tampilBarang versi USER BIASA
// (tanpa bool tampilKode — beda parameter = overloading)
// Menggunakan pointer pada struct Barang

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
        // Pointer ke tiap elemen struct Barang
        Barang *ptrBarang = &semuaBarang[i];  // Address-of operator (&)
        if (ptrBarang->stokBarang > 0) {       // Dereference via ->
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

// Fungsi tambah barang
// Wajib: &totalBarang dan &kodeUrut = Address-of operator
// Sebagai parameter fungsi (pass by reference)
// Point+: *ptrSlot = dereference untuk simpan data via pointer

void tambahBarang(Barang semuaBarang[], int &totalBarang, int &kodeUrut) {
    cout << "|==============================================|" << endl;
    cout << "|              TAMBAH BARANG BARU              |" << endl;
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

    // Menggunakan pointer untuk menyimpan data ke slot array
    Barang *ptrSlot = &semuaBarang[totalBarang];  // Address-of operator (&)
    *ptrSlot = barangBaru;                        // Dereference operator (*) untuk isi data
    totalBarang++;                                // &totalBarang memastikan perubahan terasa di main

    cout << "Barang '" << barangBaru.namaBarang << "' berhasil ditambahkan!\n";
}

// Untuk fungsi updateSatuBarang
// Wajib: parameter Barang *ptrBarangDipilih
// = Dereference operator (*) sebagai parameter fungsi
// Perubahan langsung ke data asli lewat pointer

void updateSatuBarang(Barang *ptrBarangDipilih) {
    cout << "\n--- Update Barang: " << ptrBarangDipilih->namaBarang << " ---\n";
    cout << "(Kosongkan / tekan Enter jika tidak ingin mengubah)\n\n";

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

    cout << "\nData barang berhasil diperbarui!\n";
}

// Untuk Fungsi update barang (pembungkus)
// Untuk Mengirim pointer ke fungsi updateSatuBarang
// Address-of (&) dipakai untuk ambil alamat elemen yang dipilih

void updateBarang(Barang semuaBarang[], int totalBarang) {
    cout << "|=================================================================|" << endl;
    cout << "|                         UPDATE BARANG                           |" << endl;
    cout << "|=================================================================|" << endl;

    if (totalBarang == 0) {
        cout << "Belum ada barang.\n";
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

    // Address-of operator (&): ambil alamat elemen yang dipilih
    // lalu kirim ke updateSatuBarang sebagai pointer (Dereference * ada di dalam fungsi)
    Barang *ptrPilihan = &semuaBarang[nomorUpdate - 1];
    updateSatuBarang(ptrPilihan);
}

// Untuk Fungsi hapus barang
// Wajib: &totalBarang = Address-of operator sebagai parameter
// *ptrKiri = *ptrKanan untuk geser data via pointer

void hapusBarang(Barang semuaBarang[], int &totalBarang) {
    cout << "|=================================================================|" << endl;
    cout << "|                         HAPUS BARANG                            |" << endl;
    cout << "|=================================================================|" << endl;

    if (totalBarang == 0) {
        cout << "Belum ada barang.\n";
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

    // Geser data menggunakan pointer (dereference * untuk salin isi struct)
    for (int j = indeksHapus; j < totalBarang - 1; j++) {
        Barang *ptrKiri  = &semuaBarang[j];      // Address-of (&) elemen kiri
        Barang *ptrKanan = &semuaBarang[j + 1];  // Address-of (&) elemen kanan
        *ptrKiri = *ptrKanan;                    // Dereference (*) untuk salin struct
    }
    totalBarang--;  // &totalBarang memastikan perubahan terasa di pemanggil

    cout << "Barang '" << namaHapus << "' berhasil dihapus!\n";
}

// Untuk Fungsi cek nama sudah dipakai
// Pointer Akun* untuk iterasi array struct Akun
// Wajib: Dereference (->) untuk baca namaUser lewat pointer

bool cekNamaSudahDipakai(Akun *semuaAkun, int totalAkun, string namaCek) {
    for (int i = 0; i < totalAkun; i++) {
        Akun *ptrAkun = &semuaAkun[i];       // Address-of operator (&)
        if (ptrAkun->namaUser == namaCek) {   // Dereference via ->
            return true;
        }
    }
    return false;
}

// Untuk fungsi register akun baru
// Wajib: &totalAkun = Address-of operator sebagai parameter
// *ptrSlotAkun = dereference untuk simpan akun baru

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

    // Simpan akun baru ke slot array via pointer
    Akun *ptrSlotAkun = &semuaAkun[totalAkun];  // Address-of operator (&)
    *ptrSlotAkun = akunBaru;                    // Dereference operator (*) untuk isi data
    totalAkun++;

    cout << "Akun berhasil dibuat!\n";
}

// Untuk fungsi rekursif login
// Wajib: parameter Akun *semuaAkun
// = pointer (Dereference *) sebagai parameter fungsi
// Wajib: &semuaAkun[i] = Address-of operator di dalam fungsi

int loginRekursif(Akun *semuaAkun, int totalAkun, int sisaCoba) {

    // base case: sisa coba habis
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
        // Akses struct Akun lewat pointer
        Akun *ptrAkun = &semuaAkun[i];         // Address-of operator (&)
        if (ptrAkun->namaUser == inputNama &&  // Dereference via ->
            ptrAkun->nimUser  == inputNim) {
            cout << "\nLogin berhasil! Selamat datang, " << inputNama << endl;
            cout << "Tekan Enter untuk lanjut...";
            cin.ignore();
            return i;
        }
    }

    // Kalau salah: kurangi sisa coba, panggil diri sendiri (rekursif)
    int sisaBerikutnya = sisaCoba - 1;
    if (sisaBerikutnya > 0) {
        cout << "Waduh, username/password nya salah nih. Sisa coba: "
             << sisaBerikutnya << "\n\n";
    }
    return loginRekursif(semuaAkun, totalAkun, sisaBerikutnya);
}

// Untuk fungsi menu admin
// Wajib: &totalBarang dan &kodeUrut = Address-of sebagai parameter

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
        cout << "|5. Logout                                     |" << endl;
        cout << "|==============================================|" << endl;
        cout << "Pilih menu 1-5 yuk: ";

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

// Untuk fungsi menu user biasa

void menuUser(Barang *semuaBarang, int totalBarang) {
    bool menuUserJalan = true;
    while (menuUserJalan) {

        cout << "|==============================================|" << endl;
        cout << "|                MENU PENGGUNA                 |" << endl;
        cout << "|==============================================|" << endl;
        cout << "|1. Lihat Barang                               |" << endl;
        cout << "|2. Logout                                     |" << endl;
        cout << "|==============================================|" << endl;
        cout << "Pilih menu 1-2: ";

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

// MAIN
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

    // Pointer ke array global, diteruskan ke semua fungsi
    Barang *ptrDataBarang = dataBarang;   // pointer ke array struct Barang
    Akun   *ptrDaftarAkun = daftarAkun;  // pointer ke array struct Akun

    // Sambutan awal
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
        cout << "Pilih 1, 2, atau 3, yuk: ";

        int pilihAwal;
        cin >> pilihAwal;
        cin.ignore();

        // LOGIN
        if (pilihAwal == 1) {

            cout << "|==============================================|" << endl;
            cout << "|                  LOGIN AKUN                  |" << endl;
            cout << "|==============================================|" << endl;

            // ptrDaftarAkun adalah pointer Akun* (Dereference * sebagai parameter fungsi)
            int indeksAkun = loginRekursif(ptrDaftarAkun, jumlahAkun, 3);

            if (indeksAkun == -2) {
                return 0;
            }

            // Address-of (&): ambil alamat akun yang berhasil login
            Akun *ptrAkunLogin = &daftarAkun[indeksAkun];

            // Dereference (->): cek status admin lewat pointer
            if (ptrAkunLogin->isAdmin) {
                menuAdmin(ptrDataBarang, jumlahBarang, kodeOtomatis);
            } else {
                menuUser(ptrDataBarang, jumlahBarang);
            }

        // REGISTER
        } else if (pilihAwal == 2) {
            registerAkun(daftarAkun, jumlahAkun);
            cout << "Tekan Enter untuk kembali ke menu utama...";
            cin.ignore();

        // KELUAR
        } else if (pilihAwal == 3) {
            cout << "\nSampai jumpa! Terimakasih sudah mampir ke toko Alat Tulis Kami :)\n";
            appJalan = false;

        } else {
            cout << "Pilihannya tidak ada, coba lagi ya.\n";
        }

    } // end while app

    return 0;
}
