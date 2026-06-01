#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <stdexcept>
#include <vector>

using namespace std;

// 1. STRUKTUR KELAS TOKO ELEKTRONIK (OOP)
class TokoElektronik {
private:
    // Atribut Private: Array berkapasitas 3 elemen (Enkapsulasi)
    array<string, 3> etalase;

public:
    // Constructor: Mengisi data awal secara otomatis
    TokoElektronik() {
        etalase[0] = "Laptop HP Victus";
        etalase[1] = "Router MikroTik";
        etalase[2] = "Kabel LAN & RJ45";
    }

    // Method Public: Mengambil produk dengan parameter size_t
    string ambilProduk(size_t nomorRak) {
           // 2. EXCEPTION HANDLING
        try {
            // Menggunakan .at() untuk mengakses indeks
            return etalase.at(nomorRak);
        }
        catch (const out_of_range& e) {
            // Menangkap error bawaan dan melempar (throw) pesan error kustom
            string pesanError = "Gagal Mengambil Barang : Rak nomor " + to_string(nomorRak) + " kosong atau tidak tersedia!";
            throw pesanError; 
        }
    }
};

// 3. FITUR MANAJEMEN GUDANG BERBASIS FILE
const string NAMA_FILE = "gudang.txt";

// Fungsi Bantuan: Menampilkan daftar barang (READ)
void tampilkanGudang() {
    ifstream infile(NAMA_FILE, ios::in);
    string baris;
    int nomor = 1;

    cout << "\n=== DAFTAR BARANG DI GUDANG ===" << endl;
    if (infile.is_open()) {
        while (getline(infile, baris)) {
            cout << nomor << ". " << baris << endl;
            nomor++;
        }
        infile.close();
        if (nomor == 1) {
            cout << "(Gudang masih kosong)" << endl;
        }
    } else {
        cout << "(File gudang.txt belum ada / kosong)" << endl;
    }
    cout << "===============================\n";
}

// Fungsi Bantuan: Menambah barang (CREATE)
void tambahBarang() {
    ofstream outfile(NAMA_FILE, ios::app); // mode append agar data lama tidak tertimpa
    string namaBarang;
    
    cout << "Masukkan nama barang baru: ";
    getline(cin, namaBarang);
    
    if (outfile.is_open()) {
        outfile << namaBarang << endl;
        cout << ">> Berhasil menambahkan '" << namaBarang << "' ke gudang!\n";
        outfile.close();
    } else {
        cout << ">> Gagal membuka file untuk menulis!\n";
    }
}

// Fungsi Bantuan: Membaca isi file ke dalam vector
vector<string> bacaFileKeVector() {
    vector<string> dataBarang;
    ifstream infile(NAMA_FILE, ios::in);
    string baris;
    if (infile.is_open()) {
        while (getline(infile, baris)) {
            dataBarang.push_back(baris);
        }
        infile.close();
    }
    return dataBarang;
}

// Fungsi Bantuan: Menulis vector kembali ke file
void tulisVectorKeFile(const vector<string>& dataBarang) {
    ofstream outfile(NAMA_FILE, ios::out); // mode out untuk menimpa file
    if (outfile.is_open()) {
        for (const string& barang : dataBarang) {
            outfile << barang << endl;
        }
        outfile.close();
    }
}

// Fungsi Bantuan: Mengubah data barang (UPDATE)
void ubahBarang() {
    vector<string> dataBarang = bacaFileKeVector();
    if (dataBarang.empty()) {
        cout << ">> Gudang kosong, tidak ada yang bisa diubah!\n";
        return;
    }

    int indeks;
    cout << "Pilih nomor barang yang ingin diubah: ";
    cin >> indeks;
    cin.ignore(); // Membersihkan sisa enter

    if (indeks > 0 && indeks <= dataBarang.size()) {
        cout << "Masukkan nama barang pengganti: ";
        string namaBaru;
        getline(cin, namaBaru);
        
        dataBarang[indeks - 1] = namaBaru;
        tulisVectorKeFile(dataBarang);
        cout << ">> Barang berhasil diubah!\n";
    } else {
        cout << ">> Nomor barang tidak valid!\n";
    }
}

// Fungsi Bantuan: Menghapus data barang (DELETE)
void hapusBarang() {
    vector<string> dataBarang = bacaFileKeVector();
    if (dataBarang.empty()) {
        cout << ">> Gudang kosong, tidak ada yang bisa dihapus!\n";
        return;
    }

    int indeks;
    cout << "Pilih nomor barang yang ingin dihapus: ";
    cin >> indeks;
    cin.ignore(); 

    if (indeks > 0 && indeks <= dataBarang.size()) {
        cout << ">> Menghapus '" << dataBarang[indeks - 1] << "'...\n";
        dataBarang.erase(dataBarang.begin() + (indeks - 1));
        tulisVectorKeFile(dataBarang);
        cout << ">> Barang berhasil dihapus!\n";
    } else {
        cout << ">> Nomor barang tidak valid!\n";
    }
}
// 4. PENGUJIAN PADA FUNGSI MAIN
int main() {
    TokoElektronik gibranJaya;
    int pilihan;

    // Sistem Menu Utama berjalan dalam looping
    do {
        // READ: Membaca dan menampilkan daftar barang secara otomatis
        tampilkanGudang(); 

        cout << "MENU MANAJEMEN TOKO GIBRAN JAYA" << endl;
        cout << "1. Tambah Barang Baru (Create)" << endl;
        cout << "2. Ubah Data Barang (Update)" << endl;
        cout << "3. Hapus Barang (Delete)" << endl;
        cout << "4. Simulasi Etalase (Test Exception Handling)" << endl;
        cout << "0. Keluar Program" << endl;
        cout << "Pilihan Anda: ";
        cin >> pilihan;
        
        // Membersihkan karakter newline/enter dari buffer input
        cin.ignore(); 

        switch (pilihan) {
            case 1:
                tambahBarang();
                break;
            case 2:
                ubahBarang();
                break;
            case 3:
                hapusBarang();
                break;
            case 4:
                cout << "\n--- Menjalankan Simulasi Etalase ---" << endl;
                
                // Skenario 1: Pengambilan barang di rak indeks ke-1 (Harus Sukses)
                cout << "[Skenario 1] Mengambil barang di Rak 1..." << endl;
                try {
                    string barang1 = gibranJaya.ambilProduk(1);
                    cout << "Sukses: Mendapatkan " << barang1 << endl;
                } catch (const string& e) {
                    cout << "Error: " << e << endl;
                }

                // Skenario 2: Pengambilan barang di rak indeks ke-5 (Harus Gagal & Muncul Error Kustom)
                cout << "\n[Skenario 2] Mengambil barang di Rak 5..." << endl;
                try {
                    string barang2 = gibranJaya.ambilProduk(5);
                    cout << "Sukses: Mendapatkan " << barang2 << endl;
                } catch (const string& e) {
                    cout << "Exception Tertangkap: " << e << endl;
                }
                
                cout << "------------------------------------\n";
                cout << "Tekan Enter untuk melanjutkan...";
                cin.get(); // Pause sejenak agar user bisa membaca output
                break;
            case 0:
                cout << "Keluar dari program. Terima kasih!\n";
                break;
            default:
                cout << "Pilihan tidak valid, silakan coba lagi.\n";
                break;
        }
    } while (pilihan != 0);

    return 0;
}