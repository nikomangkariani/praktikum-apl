#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>   // Untuk mengganti huruf besar ke kecil secara otomatis
using namespace std;

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

// Fungsi tampilan tabel (dari pt 5, tidak di ubah) 

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

// Tampil barang versi admin (dengan kode)
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
        cout << "| " << left   << setw(3)  << i + 1
             << " | "          << setw(20) << ptrBarang->namaBarang
             << " | " << right << setw(10) << fixed << setprecision(0)
                               << ptrBarang->hargaBarang
             << " | " << right << setw(6)  << ptrBarang->stokBarang
             << " | " << left  << setw(12) << ptrBarang->kategoriBarang.namaKategori
             << " |" << endl;
    }
    cetakGaris();
    cout << "Total: " << totalBarang << " barang\n";
}

// Fungsi khusus user: Hanya menampilkan barang yang stoknya yang di atas 0
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
            cout << "| " << left   << setw(3)  << i + 1
                 << " | "          << setw(20) << ptrBarang->namaBarang
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

// Untuk menampilkan satu barang (hasil pencarian)
void tampilSatuBarang(Barang *ptrBarangDitemukan, int nomorUrut) {
    cetakGaris();
    cout << "| " << left   << setw(3)  << nomorUrut
         << " | "          << setw(20) << ptrBarangDitemukan->namaBarang
         << " | " << right << setw(10) << fixed << setprecision(0)
                           << ptrBarangDitemukan->hargaBarang
         << " | " << right << setw(6)  << ptrBarangDitemukan->stokBarang
         << " | " << left  << setw(12) << ptrBarangDitemukan->kategoriBarang.namaKategori
         << " |" << endl;
    cetakGaris();
    cout << "Kode Barang  : " << ptrBarangDitemukan->kodeBarang   << endl;
    cout << "Keterangan   : " << ptrBarangDitemukan->kategoriBarang.keteranganKategori << endl;
}

// Fungsi CRUD (dari pt 5, tidak di ubah) 

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

    cout << "Barang '" << barangBaru.namaBarang << "' berhasil ditambahkan! "
         << "(Kode: " << barangBaru.kodeBarang << ")\n";
}

void updateSatuBarang(Barang *ptrBarangDipilih) {
    cout << "\nUpdate Barang: " << ptrBarangDipilih->namaBarang << "\n";
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

// Fungsi akun (dari pt 5, tidak di ubah)

bool cekNamaSudahDipakai(Akun *semuaAkun, int totalAkun, string namaCek) {
    for (int i = 0; i < totalAkun; i++) {
        Akun *ptrAkun = &semuaAkun[i];
        if (ptrAkun->namaUser == namaCek) return true;
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

// Fungsi sorting (dari pt 5, tidak di ubah) 

void selectionSortNamaAscending(Barang semuaBarang[], int totalBarang) {
    for (int posisiAwal = 0; posisiAwal < totalBarang - 1; posisiAwal++) {
        int indeksNamaTerkecil = posisiAwal;
        for (int posisiCek = posisiAwal + 1; posisiCek < totalBarang; posisiCek++) {
            if (semuaBarang[posisiCek].namaBarang < semuaBarang[indeksNamaTerkecil].namaBarang) {
                indeksNamaTerkecil = posisiCek;
            }
        }
        if (indeksNamaTerkecil != posisiAwal) {
            Barang barangSementara          = semuaBarang[posisiAwal];
            semuaBarang[posisiAwal]         = semuaBarang[indeksNamaTerkecil];
            semuaBarang[indeksNamaTerkecil] = barangSementara;
        }
    }
}

void bubbleSortHargaDescending(Barang semuaBarang[], int totalBarang) {
    for (int putaranLuar = 0; putaranLuar < totalBarang - 1; putaranLuar++) {
        bool adaPertukaran = false;
        for (int putaranDalam = 0; putaranDalam < totalBarang - 1 - putaranLuar; putaranDalam++) {
            if (semuaBarang[putaranDalam].hargaBarang < semuaBarang[putaranDalam + 1].hargaBarang) {
                Barang barangSementara        = semuaBarang[putaranDalam];
                semuaBarang[putaranDalam]     = semuaBarang[putaranDalam + 1];
                semuaBarang[putaranDalam + 1] = barangSementara;
                adaPertukaran = true;
            }
        }
        if (!adaPertukaran) break;
    }
}

void insertionSortStokAscending(Barang semuaBarang[], int totalBarang) {
    for (int posisiSisip = 1; posisiSisip < totalBarang; posisiSisip++) {
        Barang barangYangDisisipkan = semuaBarang[posisiSisip];
        int    posisiGeser          = posisiSisip - 1;
        while (posisiGeser >= 0 &&
               semuaBarang[posisiGeser].stokBarang > barangYangDisisipkan.stokBarang) {
            semuaBarang[posisiGeser + 1] = semuaBarang[posisiGeser];
            posisiGeser--;
        }
        semuaBarang[posisiGeser + 1] = barangYangDisisipkan;
    }
}

void salinDataBarang(Barang sumber[], Barang tujuan[], int totalBarang) {
    for (int i = 0; i < totalBarang; i++) {
        tujuan[i] = sumber[i];
    }
}

void menuSorting(Barang *semuaBarang, int totalBarang) {
    if (totalBarang == 0) {
        cout << "Belum ada barang untuk diurutkan.\n";
        return;
    }

    Barang dataSortir[BATAS_BARANG];
    bool   menuSortingJalan = true;

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
        cin  >> pilihSorting;
        cin.ignore();

        if (pilihSorting == 1) {
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
    }
}

// Fungsi Searching baru

// METODE 1: BINARY SEARCH
 
int binarySearchKodeBarang(Barang *semuaBarang, int totalBarang, int kodeYangDicari) {
    int batasKiri  = 0;
    int batasKanan = totalBarang - 1;

    while (batasKiri <= batasKanan) {
        int indeksTengah = (batasKiri + batasKanan) / 2;

        // Akses elemen via pointer arithmetic
        int kodeTengah = (semuaBarang + indeksTengah)->kodeBarang;

        if (kodeTengah == kodeYangDicari) {
            return indeksTengah;         // Ditemukan
        } else if (kodeTengah < kodeYangDicari) {
            batasKiri = indeksTengah + 1; // Cari di bagian kanan
        } else {
            batasKanan = indeksTengah - 1; // Cari di bagian kiri
        }
    }
    return -1; // Tidak ditemukan
}


// METODE 2: SEQUENTIAL SEARCH

int sequentialSearchNamaBarang(Barang *semuaBarang, int totalBarang, string namaYangDicari) {
    // Ubah kata kunci ke huruf kecil agar pencarian lebih mudah
    string kataKunciKecil = namaYangDicari;
    transform(kataKunciKecil.begin(), kataKunciKecil.end(),
              kataKunciKecil.begin(), ::tolower);

    for (int indeks = 0; indeks < totalBarang; indeks++) {
        // Ambil nama barang satu per satu dan ubah ke huruf kecil
        string namaDataKecil = (semuaBarang + indeks)->namaBarang;
        transform(namaDataKecil.begin(), namaDataKecil.end(),
                  namaDataKecil.begin(), ::tolower);

        // Cek apakah kata kunci ada di dalam nama barang
        if (namaDataKecil.find(kataKunciKecil) != string::npos) {
            return indeks; // Ditemukan
        }
    }
    return -1; // Tidak ditemukan
}

// Rapikan urutan barang (berdasarkan kode) di daftar cadangan, 
// supaya pencarian Binary Search bisa jalan dengan benar.
void sortKodeAscendingUntukSearch(Barang semuaBarang[], int totalBarang) {
    for (int posisiAwal = 0; posisiAwal < totalBarang - 1; posisiAwal++) {
        int indeksKodeTerkecil = posisiAwal;
        for (int posisiCek = posisiAwal + 1; posisiCek < totalBarang; posisiCek++) {
            if (semuaBarang[posisiCek].kodeBarang < semuaBarang[indeksKodeTerkecil].kodeBarang) {
                indeksKodeTerkecil = posisiCek;
            }
        }
        if (indeksKodeTerkecil != posisiAwal) {
            Barang barangSementara            = semuaBarang[posisiAwal];
            semuaBarang[posisiAwal]           = semuaBarang[indeksKodeTerkecil];
            semuaBarang[indeksKodeTerkecil]   = barangSementara;
        }
    }
}

// Menu Cari Barang: Bisa cari pakai kode atau pakai nama.
// Fitur ini bisa dipakai untuk Admin maupun User.
void menuSearching(Barang *semuaBarang, int totalBarang) {
    if (totalBarang == 0) {
        cout << "Belum ada barang untuk dicari.\n";
        return;
    }

    bool menuSearchJalan = true;
    while (menuSearchJalan) {

        cout << "|==============================================|" << endl;
        cout << "|              MENU PENCARIAN BARANG           |" << endl;
        cout << "|==============================================|" << endl;
        cout << "|1. Cari Kode Barang  (Binary Search)          |" << endl;
        cout << "|2. Cari Nama Barang  (Sequential Search)      |" << endl;
        cout << "|3. Kembali                                    |" << endl;
        cout << "|==============================================|" << endl;
        cout << "Pilih menu 1-3 yuk: ";

        int pilihCari;
        cin  >> pilihCari;
        cin.ignore();

        // Pilihan 1: BINARY SEARCH berdasarkan Kode

        if (pilihCari == 1) {
            int kodeYangDicari;
            cout << "\nCari Barang: Binary Search (Kode Barang)\n";
            cout << "Masukkan kode barang yang ingin dicari: ";
            cin  >> kodeYangDicari;
            cin.ignore();

            // Salin data agar data asli tidak berubah
            Barang dataCari[BATAS_BARANG];
            salinDataBarang(semuaBarang, dataCari, totalBarang);

            // Binary Search memerlukan data terurut berdasarkan kode barang
            sortKodeAscendingUntukSearch(dataCari, totalBarang);

            cout << "\nProses Binary Search untuk Kode " << kodeYangDicari << ":\n";

            // Tampilkan langkah-langkah binary search
            int batasKiri  = 0;
            int batasKanan = totalBarang - 1;
            int langkah    = 1;
            while (batasKiri <= batasKanan) {
                int tengah    = (batasKiri + batasKanan) / 2;
                int kodeTengah = dataCari[tengah].kodeBarang;
                cout << "  Langkah " << langkah << ": periksa kode " << kodeTengah
                     << " ('" << dataCari[tengah].namaBarang << "')";
                if (kodeTengah == kodeYangDicari) {
                    cout << " -> Ditemukan!\n";
                    break;
                } else if (kodeTengah < kodeYangDicari) {
                    cout << " -> cari ke kanan\n";
                    batasKiri = tengah + 1;
                } else {
                    cout << " -> cari ke kiri\n";
                    batasKanan = tengah - 1;
                }
                langkah++;
                if (batasKiri > batasKanan) cout << "  Tidak ditemukan.\n";
            }

            // Panggil fungsi Binary Search dengan POINTER sebagai parameter
            int indeksHasil = binarySearchKodeBarang(dataCari, totalBarang, kodeYangDicari);

            cout << "\nHasil Pencarian:\n";
            cetakHeader();
            if (indeksHasil != -1) {
                // Gunakan pointer ke elemen hasil
                Barang *ptrHasil = dataCari + indeksHasil;
                tampilSatuBarang(ptrHasil, indeksHasil + 1);
            } else {
                cetakGaris();
                cout << "Barang dengan kode " << kodeYangDicari << " tidak ditemukan.\n";
            }

        // Pilihan 2: SEQUENTIAL SEARCH berdasarkan Nama

        } else if (pilihCari == 2) {
            string namaYangDicari;
            cout << "\nCari Barang: Sequential Search (Nama Barang)\n";
            cout << "Masukkan nama barang yang di cari: ";
            getline(cin, namaYangDicari);

            cout << "\nProses Sequential Search untuk \"" << namaYangDicari << "\":\n";

            // Tampilkan langkah-langkah sequential search

            string kataKunciKecil = namaYangDicari;
            transform(kataKunciKecil.begin(), kataKunciKecil.end(),
                      kataKunciKecil.begin(), ::tolower);
            for (int i = 0; i < totalBarang; i++) {
                string namaKecil = (semuaBarang + i)->namaBarang;
                transform(namaKecil.begin(), namaKecil.end(), namaKecil.begin(), ::tolower);
                cout << "  Periksa [" << i << "] '" << (semuaBarang + i)->namaBarang << "'";
                if (namaKecil.find(kataKunciKecil) != string::npos) {
                    cout << " -> Cocok!\n";
                    break;
                } else {
                    cout << " -> tidak cocok\n";
                }
            }

            // Panggil fungsi Sequential Search dengan Pointer sebagai parameter
            int indeksHasil = sequentialSearchNamaBarang(semuaBarang, totalBarang, namaYangDicari);

            cout << "\nHasil Pencarian:\n";
            cetakHeader();
            if (indeksHasil != -1) {
                // Gunakan pointer ke elemen hasil
                Barang *ptrHasil = semuaBarang + indeksHasil;
                tampilSatuBarang(ptrHasil, indeksHasil + 1);
            } else {
                cetakGaris();
                cout << "Barang dengan nama \"" << namaYangDicari << "\" tidak ditemukan.\n";
            }

        } else if (pilihCari == 3) {
            menuSearchJalan = false;

        } else {
            cout << "Pilihan tidak ada, coba lagi ya.\n";
        }

        if (pilihCari >= 1 && pilihCari <= 2) {
            cout << "\nTekan Enter untuk kembali...";
            cin.ignore();
        }

    } // end while menu searching
}

// Menu Admin dan User 

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
        cout << "|6. Cari Barang                                |" << endl;
        cout << "|7. Logout                                     |" << endl;
        cout << "|==============================================|" << endl;
        cout << "Pilih menu 1-7 yuk: ";

        int pilihAdmin;
        cin  >> pilihAdmin;
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
            menuSearching(semuaBarang, totalBarang);   // <-- FITUR BARU

        } else if (pilihAdmin == 7) {
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
        cout << "|2. Cari Barang (Searching)                    |" << endl;
        cout << "|3. Logout                                     |" << endl;
        cout << "|==============================================|" << endl;
        cout << "Pilih menu 1-3 yuk: ";

        int pilihUser;
        cin  >> pilihUser;
        cin.ignore();

        if (pilihUser == 1) {
            tampilBarang(semuaBarang, totalBarang);
            cout << "\nTekan Enter untuk kembali...";
            cin.ignore();

        } else if (pilihUser == 2) {
            menuSearching(semuaBarang, totalBarang);   // <-- FITUR BARU

        } else if (pilihUser == 3) {
            cout << "Logout berhasil! Terima kasih sudah mampir\n";
            cout << "Tekan Enter untuk kembali ke menu utama...";
            cin.ignore();
            menuUserJalan = false;

        } else {
            cout << "Pilihannya tidak ada, coba lagi.\n";
        }

    } // end while menu user
}

// Fungsi MAIN

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

    // Pointer ke array 
    Barang *ptrDataBarang = dataBarang;
    Akun   *ptrDaftarAkun = daftarAkun;

    // Kata sambutan dan sapaan 
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
        cin  >> pilihAwal;
        cin.ignore();

        if (pilihAwal == 1) {

            cout << "|==============================================|" << endl;
            cout << "|                  LOGIN AKUN                  |" << endl;
            cout << "|==============================================|" << endl;

            int indeksAkun = loginRekursif(ptrDaftarAkun, jumlahAkun, 3);

            if (indeksAkun == -2) return 0;

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