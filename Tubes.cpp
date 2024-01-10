/*
    Nama : Adam Kaze
    NPM  : 4522210094

    "SISTEM INFORMASI PENJUALAN OBAT DI APOTIK"
        materi :
          - Selection
          - Repetation
          - Array
          - Function
          - String
          - File
          - Selection Sort (Ascending)
    
    Matkul : Algoritma Pemrograman - B
    Dosen  : Dra. Sri Rezeki Candra Nursari, Dra., M.Kom
*/



#include <iostream>
#include <fstream>

using namespace std;

string A_pembeli, A_nomorHP;
double A_totalHarga = 0;
char A_konfirmasi;
int i, A_pri = 0 ,A_jumlahObatBeli[15] = {0};
const int A_jumlahObat = 15;
string A_daftarObat[A_jumlahObat] = {
    "Paracetamol ", "Amoxicillin ", "Vitamin C   ", "Betadine    ", "Aspirin     ",
    "Cetirizine  ", "Mefenamic Acid", "Omeprazole  ", "Simvastatin ", "Losartan    ",
    "Dexamethasone", "Metformin   ", "Tramadol    ", "Azithromycin", "Ibuprofen   "
};
double A_hargaObat[A_jumlahObat] = {
    5000, 10000, 8000, 15000, 7000,
    12000, 9000, 13000, 11000, 14000,
    16000, 18000, 20000, 22000, 25000
};

void A_MenuUtama() {
    system("cls");
    cout << "|==============> MENU UTAMA <==============|\n\n";
    cout << "  1. Pembelian Obat\n";
    cout << "  2. History\n";
    cout << "  3. Exit\n";
}

void A_MenuBeli(string A_daftarObat[], double A_hargaObat[], int A_jumlahObat) {
    system("cls");
    cout << "|===============> DAFTAR OBAT <===============|\n\n";
    for (i = 0; i < A_jumlahObat; i++) {
        cout << "  " << i + 1 << ". " << A_daftarObat[i] << "\t-\tRp." << A_hargaObat[i] << endl;
    }
}

void A_Struk(string A_pembeli, string A_nomorHP, int A_jumlahObatBeli[], double A_hargaObat[], double A_totalHarga) {
    cout << "\n|===============> STRUK PEMBELIAN <===============|\n\n";
    cout << " Nama Pembeli   : " << A_pembeli << endl;
    cout << " Nomor HP       : " << A_nomorHP << endl;

    cout << "\n Pembelian Obat : ";
    for (i = 0; i < 15; i++) {
        if (A_jumlahObatBeli[i] > 0) {
            cout << "\n   - " << A_daftarObat[i] << " (" << A_jumlahObatBeli[i] << " pcs)  =>  Rp."
                 << A_hargaObat[i] * A_jumlahObatBeli[i];
        }
    }

    cout << "\n\n Total Harga    : Rp." << A_totalHarga << endl;
}

void SelectionSort(double A_hargaObat[], int A_jumlahObatBeli[]) {  // Mengurutkan Berdasarkan Harga
    for (int i = 0; i < A_jumlahObat - 1; i++) {
        int A_minimum = i;
        for (int j = i + 1; j < A_jumlahObat; j++) {
            if (A_hargaObat[j] < A_hargaObat[A_minimum]) {
                A_minimum = j;
            }
        }
        swap(A_hargaObat[A_minimum], A_hargaObat[i]);
        swap(A_jumlahObatBeli[A_minimum], A_jumlahObatBeli[i]);
    } 
}

void A_Transaksi(string A_daftarObat[], double A_hargaObat[], int A_jumlahObat) {
    char A_lanjutBeli;

    cout << "\n Masukkan nama pembeli  : "; cin.ignore(); getline(cin, A_pembeli);
    cout << "\n Masukkan nomor pembeli : "; getline(cin, A_nomorHP);
    A_MenuBeli(A_daftarObat, A_hargaObat, A_jumlahObat);

    do {
        int A_indeksObat, A_jumlahBeli;

        cout << "\n Masukkan nomor obat yang ingin dibeli  : "; cin >> A_indeksObat;
        while (A_indeksObat <= 0 || A_indeksObat > A_jumlahObat) {
            cout << " nomor obat tidak valid. Masukkan kembali : ";
            cin >> A_indeksObat;
        }

        cout << " Masukkan jumlah obat yang ingin dibeli : "; cin >> A_jumlahBeli;
        A_totalHarga += A_hargaObat[A_indeksObat - 1] * A_jumlahBeli;
        A_jumlahObatBeli[A_indeksObat - 1] += A_jumlahBeli;

        cout << " Apakah Anda ingin membeli obat lain? (y/n) : "; cin >> A_lanjutBeli;
    } while (A_lanjutBeli == 'y' || A_lanjutBeli == 'Y');

    SelectionSort(A_hargaObat, A_jumlahObatBeli);

    system("cls");
    A_Struk(A_pembeli, A_nomorHP, A_jumlahObatBeli, A_hargaObat, A_totalHarga);
    cout << "\nApakah Anda ingin melanjutkan transaksi? (y/n) : "; cin >> A_konfirmasi;

    if (A_konfirmasi == 'y' || A_konfirmasi == 'Y') {
        double A_uangBayar, A_kembalian;
        cout << "\nMasukkan jumlah uang yang dibayarkan : "; cin >> A_uangBayar;

        while (A_uangBayar < A_totalHarga) {
            cout << "Jumlah uang kurang. Masukkan kembali : "; cin >> A_uangBayar;
        }

        A_kembalian = A_uangBayar - A_totalHarga;
        A_pri++;

        system("cls");
        A_Struk(A_pembeli, A_nomorHP, A_jumlahObatBeli, A_hargaObat, A_totalHarga);
        cout << " Uang Bayar     : Rp." << A_uangBayar << endl;
        cout << " Kembalian      : Rp." << A_kembalian << endl;
        cout << "\n|=================================================|\n";
        cout << "\nTekan enter untuk kembali ke menu utama..."; cin.ignore(); cin.get();

        // Menyimpan data transaksi ke dalam file history.txt
        ofstream A_fileHistory("history.txt", ios::app);
        A_fileHistory << "  Transaksi ke   : " << A_pri << endl;
        A_fileHistory << "  Nama Pembeli   : " << A_pembeli << endl;		
        A_fileHistory << "  Nomor HP       : " << A_nomorHP << endl;

        A_fileHistory << "\n  Pembelian Obat : ";
        for (i = 0; i < 15; i++) {
            if (A_jumlahObatBeli[i] > 0) {
                A_fileHistory << "\n   - " << A_daftarObat[i] << " (" << A_jumlahObatBeli[i] << " pcs)  =>  Rp."
                              << A_hargaObat[i] * A_jumlahObatBeli[i];
            }
        }

        A_fileHistory << "\n\n  Total Harga    : Rp." << A_totalHarga << endl;
        A_fileHistory << "  Uang Bayar     : Rp." << A_uangBayar << endl;
        A_fileHistory << "  Kembalian      : Rp." << A_kembalian << endl;
        A_fileHistory << "\n-----------------------------------------------------\n\n";
        A_fileHistory.close();
    }
    A_totalHarga = 0;
    for (i = 0; i < 15; i++) {
        A_jumlahObatBeli[i] = 0;
    }
}

void A_History() {
    system("cls");
    cout << "|===============> HISTORY TRANSAKSI <===============|\n";
    ifstream A_fileHistory("history.txt");

    if (A_fileHistory.is_open()) {
        string A_line;
        while (getline(A_fileHistory, A_line)) {
            cout << A_line << endl;
        }
        A_fileHistory.close();
    } else {
        cout << "\n Belum ada transaksi yang dilakukan.\n";
    }

    cout << "\n Tekan enter untuk kembali ke menu utama..."; cin.ignore(); cin.get();
}

int main() {
    int A_pilihanMenu;

    do {
        A_MenuUtama();
        cout << "\n Pilih menu (1/2/3) : "; cin >> A_pilihanMenu;
        cout << "\n|==========================================|\n";

        if (A_pilihanMenu == 1) {
            A_Transaksi(A_daftarObat, A_hargaObat, A_jumlahObat);
        } else if (A_pilihanMenu == 2) {
            A_History();
        } else if (A_pilihanMenu == 3) {
            cout << " Terima kasih telah menggunakan program ini\n\n";
        }
    } while (A_pilihanMenu != 3);
    return 0;
}