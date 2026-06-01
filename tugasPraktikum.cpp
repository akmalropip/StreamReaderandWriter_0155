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
