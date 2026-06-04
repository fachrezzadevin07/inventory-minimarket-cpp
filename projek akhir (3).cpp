#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

struct Barang {
    int id;
    string nama;
    string kategori;
    int harga;
    int stok;
};

Barang barang[100];
int jumlahBarang = 0;

void saveFile() {
    ofstream file("barang.txt");

    for(int i = 0; i < jumlahBarang; i++) {
        file << barang[i].id << endl;
        file << barang[i].nama << endl;
        file << barang[i].kategori << endl;
        file << barang[i].harga << endl;
        file << barang[i].stok << endl;
    }

    file.close();

    cout << "\nData berhasil disimpan ke file.\n";
}

void bacaFile() {
    ifstream file("barang.txt");

    while(file >> barang[jumlahBarang].id) {

        file.ignore();

        getline(file, barang[jumlahBarang].nama);
        getline(file, barang[jumlahBarang].kategori);

        file >> barang[jumlahBarang].harga;
        file >> barang[jumlahBarang].stok;

        jumlahBarang++;
    }

    file.close();
}

void inputBarang() {
    int jumlahInput;

    cout << "\n============ INPUT BARANG ===============\n";
    cout << "Mau input berapa barang? : ";
    cin >> jumlahInput;

    for(int i = 0; i < jumlahInput; i++) {
        cout << "\nBarang ke-" << i + 1 << endl;
        cout << "ID Barang       : ";
        cin >> barang[jumlahBarang].id;
        cin.ignore();
        cout << "Nama Barang     : ";
        getline(cin, barang[jumlahBarang].nama);
        cout << "Kategori Barang : ";
        getline(cin, barang[jumlahBarang].kategori);
        cout << "Harga Barang    : ";
        cin >> barang[jumlahBarang].harga;
        
        if(barang[jumlahBarang].harga < 0) {
            cout << "\nHarga tidak boleh negatif!\n";
            return;
        }

        cout << "Stok Barang     : ";
        cin >> barang[jumlahBarang].stok;

        if(barang[jumlahBarang].stok < 0) {

            cout << "\nStok tidak boleh negatif!\n";
            return;
        }

        jumlahBarang++;

        cout << "\nBarang berhasil ditambahkan.\n";
    }
}

void tampilBarang() {

    if(jumlahBarang == 0) {

        cout << "\nData barang masih kosong.\n";
        return;
    }

    cout << "\n===================================================================\n";
    cout << "                      DATA BARANG MINIMARKET\n";
    cout << "===================================================================\n";

    cout << left
         << setw(10) << "ID"
         << setw(20) << "Nama"
         << setw(15) << "Kategori"
         << setw(12) << "Harga"
         << setw(10) << "Stok" << endl;

    cout << "-------------------------------------------------------------------\n";

    for(int i = 0; i < jumlahBarang; i++) {

        // POINTER
        Barang *ptr = &barang[i];

        cout << left
             << setw(10) << ptr->id
             << setw(20) << ptr->nama
             << setw(15) << ptr->kategori
             << setw(12) << ptr->harga
             << setw(10) << ptr->stok << endl;
    }
}

void cariBarang() {
    int pilihCari;
    bool ketemu = false;

    cout << "\n=============== CARI BARANG ===============\n";
    cout << "1. Cari berdasarkan ID\n";
    cout << "2. Cari berdasarkan Nama\n";
    cout << "Pilih : ";
    cin >> pilihCari;

    if(pilihCari == 1) {

        int cariID;

        cout << "Masukkan ID barang : ";
        cin >> cariID;

        for(int i = 0; i < jumlahBarang; i++) {

            if(barang[i].id == cariID) {
                cout << "\nBarang ditemukan!\n";
                cout << "ID       : " << barang[i].id << endl;
                cout << "Nama     : " << barang[i].nama << endl;
                cout << "Kategori : " << barang[i].kategori << endl;
                cout << "Harga    : " << barang[i].harga << endl;
                cout << "Stok     : " << barang[i].stok << endl;
                ketemu = true;
                break;
            }
        }
    }

    else if(pilihCari == 2) {
        string cariNama;
        cin.ignore();

        cout << "Masukkan nama barang : ";
        getline(cin, cariNama);
        for(int i = 0; i < jumlahBarang; i++) {
            if(barang[i].nama == cariNama) {

                cout << "\nBarang ditemukan!\n";
                cout << "ID       : " << barang[i].id << endl;
                cout << "Nama     : " << barang[i].nama << endl;
                cout << "Kategori : " << barang[i].kategori << endl;
                cout << "Harga    : " << barang[i].harga << endl;
                cout << "Stok     : " << barang[i].stok << endl;

                ketemu = true;
                break;
            }
        }
    }

    else {
        cout << "\nPilihan tidak tersedia.\n";
        return;
    }

    if(!ketemu) {
        cout << "\nBarang tidak ditemukan.\n";
    }
}

void sortingBarang() {
    int pilihSort;
    Barang sementara;

    cout << "\n=============== SORTING BARANG ===============\n";
    cout << "1. Harga Termurah (ASC)\n";
    cout << "2. Harga Termahal (DESC)\n";
    cout << "Pilih : ";
    cin >> pilihSort;

    for(int i = 0; i < jumlahBarang - 1; i++) {

        for(int j = 0; j < jumlahBarang - i - 1; j++) {

            if(pilihSort == 1) {

                if(barang[j].harga > barang[j + 1].harga) {

                    sementara = barang[j];
                    barang[j] = barang[j + 1];
                    barang[j + 1] = sementara;
                }
            }

            else if(pilihSort == 2) {

                if(barang[j].harga < barang[j + 1].harga) {

                    sementara = barang[j];
                    barang[j] = barang[j + 1];
                    barang[j + 1] = sementara;
                }
            }
        }
    }

    cout << "\nData berhasil diurutkan.\n";

    tampilBarang();
}

void hapusBarang() {
    int idHapus;
    bool ketemu = false;

    cout << "\n========================== HAPUS BARANG ==========================\n";

    tampilBarang();

    cout << "\nMasukkan ID barang yang ingin dihapus : ";
    cin >> idHapus;

    for(int i = 0; i < jumlahBarang; i++) {

        if(barang[i].id == idHapus) {

            ketemu = true;

            for(int j = i; j < jumlahBarang - 1; j++) {

                barang[j] = barang[j + 1];
            }

            jumlahBarang--;

            cout << "\nData barang berhasil dihapus.\n";

            saveFile();

            break;
        }
    }

    if(!ketemu) {

        cout << "\nID barang tidak ditemukan.\n";
    }
}

void transaksi() {
    int idCari, jumlahBeli, subtotal, bayar, kembalian;
    int total = 0;
    bool ketemu;
    char lagi;
    string namaNota[100];
    int qtyNota[100];
    int hargaNota[100];
    int subtotalNota[100];
    int jumlahNota = 0;

 cout << "\n===================================================================\n";
    cout << "                TRANSAKSI PENJUALAN\n";

    do {

        ketemu = false;

        tampilBarang();

        cout << "\nMasukkan ID barang : ";
        cin >> idCari;

        for(int i = 0; i < jumlahBarang; i++) {

            if(barang[i].id == idCari) {

                ketemu = true;

                cout << "\nNama Barang : " << barang[i].nama << endl;
                cout << "Harga       : " << barang[i].harga << endl;
                cout << "Stok        : " << barang[i].stok << endl;

                cout << "Jumlah beli : ";
                cin >> jumlahBeli;

                if(jumlahBeli <= barang[i].stok) {

                    subtotal = jumlahBeli * barang[i].harga;

                    barang[i].stok -= jumlahBeli;

                    total += subtotal;

                    namaNota[jumlahNota] = barang[i].nama;
                    qtyNota[jumlahNota] = jumlahBeli;
                    hargaNota[jumlahNota] = barang[i].harga;
                    subtotalNota[jumlahNota] = subtotal;

                    jumlahNota++;

                    cout << "\nBarang berhasil ditambahkan ke transaksi.\n";
                }

                else {

                    cout << "\nStok tidak mencukupi!\n";
                }

                break;
            }
        }

        if(!ketemu) {

            cout << "\nID barang tidak ditemukan.\n";
        }

        cout << "\nTambah barang lagi? (y/n) : ";
        cin >> lagi;

    } while(lagi == 'y' || lagi == 'Y');

    cout << "\n\n===========================================================\n";
    cout << "                    NOTA BELANJA\n";
    cout << "===========================================================\n";

    cout << left
         << setw(5) << "No"
         << setw(20) << "Nama Barang"
         << setw(10) << "Qty"
         << setw(12) << "Harga"
         << setw(12) << "Subtotal" << endl;

    cout << "-----------------------------------------------------------\n";

    for(int i = 0; i < jumlahNota; i++) {

        cout << left
             << setw(5) << i + 1
             << setw(20) << namaNota[i]
             << setw(10) << qtyNota[i]
             << setw(12) << hargaNota[i]
             << setw(12) << subtotalNota[i] << endl;
    }

    cout << "-----------------------------------------------------------\n";

    cout << right << setw(45)
         << "Total Bayar : Rp "
         << total << endl;

    cout << "\nMasukkan uang bayar : Rp ";
    cin >> bayar;

    kembalian = bayar - total;

    cout << setw(25)
         << "Kembalian : Rp "
         << kembalian << endl;

    cout << "====================================================\n";
    cout << "          TERIMA KASIH SUDAH BERBELANJA\n";
    cout << "====================================================\n";

    saveFile();
}

int main() {
    int menu;
    bacaFile();
    do {
        cout << "\n\n====================================================\n";
        cout << "           PROGRAM INVENTORY MINIMARKET\n";
        cout << "====================================================\n";
        cout << "1. Input Data Barang\n";
        cout << "2. Tampilkan Data Barang\n";
        cout << "3. Cari Barang\n";
        cout << "4. Urutkan Data Barang\n";
        cout << "5. Hapus Data Barang\n";
        cout << "6. Transaksi Penjualan\n";
        cout << "7. Save File\n";
        cout << "8. Keluar\n";
        cout << "Pilih menu : ";
        cin >> menu;

        switch(menu) {

            case 1:
                inputBarang();
                break;

            case 2:
                tampilBarang();
                break;

            case 3:
                cariBarang();
                break;

            case 4:
                sortingBarang();
                break;

            case 5:
                hapusBarang();
                break;

            case 6:
                transaksi();
                break;

            case 7:
                saveFile();
                break;

            case 0:
                cout << "\nProgram selesai...\n";
                break;

            default:
                cout << "\nMenu tidak tersedia.\n";
        }

    } while(menu != 8);

    return 0;
}
