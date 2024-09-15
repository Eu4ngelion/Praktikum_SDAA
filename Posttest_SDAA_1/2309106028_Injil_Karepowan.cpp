#include <iostream>
using namespace std;

int pascal(int i, int j) {
    // Base Case
    if (j == 0 || i == j) {
        return 1;
    } 
    // tambahkan angka di atas & di atas kiri
    else {
        return pascal(i-1, j-1) + pascal(i-1, j);
    }
}
int main() {
    system ("cls");
    // Header
    cout << "=============================" << endl;
    cout << "   Program Segitiga Pascal" << endl;
    cout << "-----------------------------" << endl;
    cout << "Nama : Injil Karepowan" << endl;
    cout << "NIM : 2309106028" << endl;
    cout << "=============================" << endl;
    int tinggi = 3;
    // Perulangan untuk tiap elemen (baris, kolom)
    for (int i = 0; i < tinggi; i++) {
        for (int j = 0; j <= i; j++) {
            cout << pascal(i, j);
            cout << " ";
        }
        cout << endl;
    }
    return 0;
}