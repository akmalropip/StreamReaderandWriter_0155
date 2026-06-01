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