// Program Penjualan Earphone
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

// Struct
// Data User
struct user_data{
    string username;
    string password;
    string telepon;
    string address;
};
// Node User
struct node_user{
    user_data data;
    node_user *next;
};

// Data Earphone
struct earphone_data{
    string nama;
    string merk;
    int harga;
    int stok;
};

// Data Order
struct Order {
    string username;
    string earphone_name;
    int quantity;
};

void clear(){
    system("cls");
}
void pause(){
    system("pause");
}
// STACK
const int MAX_STACK = 100;
string login_stack[MAX_STACK];
int stack_top = -1;

// Push Stack
void push(string value) {
    if (stack_top < MAX_STACK - 1) {
        login_stack[stack_top++] = value;
    } else {
        cout << "Stack overflow!" << endl;
    }
}
bool is_stack_empty() {
    return stack_top == -1;
}
// Pop Stack
string pop() {
    if (stack_top >= 0) {
        return login_stack[stack_top--];
    }
    return "";
}

// Queue
const int MAX_QUEUE_SIZE = 100;
Order order_queue[MAX_QUEUE_SIZE];
int queue_front = 0, queue_rear = -1, queue_count = 0;
void enqueue(Order value) {
    if (queue_count < MAX_QUEUE_SIZE) {
        queue_rear = (queue_rear + 1) % MAX_QUEUE_SIZE;
        order_queue[queue_rear] = value;
        queue_count++;
    } else {
        cout << "Queue is full!" << endl;
    }
}
bool is_queue_empty() {
    return queue_count == 0;
}
Order dequeue() {
    if (!is_queue_empty()) {
        Order value = order_queue[queue_front];
        queue_front = (queue_front + 1) % MAX_QUEUE_SIZE;
        queue_count--;
        return value;
    }
    return {"", "", 0};
}
// Menu Awal
int menu_awal(){
    string pilihan;
    int count = 0;
    while(true){
        count++;
        cout << "=== MENU AWAL ===" << endl;
        cout << "1. Login (STACK)" << endl;
        cout << "2. Register" << endl;
        cout << "3. Exit" << endl;
        cout << "PILIH MENU: ";
        getline(cin, pilihan);
        // Error Check
        if(pilihan.find_first_not_of("123") != string::npos || pilihan.length() > 1){
            cout << "Pilihan tidak tersedia" << endl;
            pause();
            clear();
            continue;
        }
        if(pilihan.find_first_not_of(" ") == string::npos){
            cout << "Pilihan tidak boleh kosong" << endl;
            pause();
            clear();
            continue;
        }
        if(pilihan == "1" || pilihan == "2" || pilihan == "3"){
            return stoi(pilihan);
        }
        if(count > 3){
            cout << "Kesempatan login habis" << endl;
            return 3;
        }
    }
}

int login(string &admin_username, string &admin_password, node_user* &head,
string &global_username, string &global_password, int percobaan = 3){
    string inp_username, inp_pass;

    // Base Case
    if(percobaan == 0){
        cout << "Kesempatan login habis" << endl;
        pause();
        clear();
        return 0; // 0 = Gagal Login
    }
    cout << "=== LOGIN ===" << endl;
    cout << "Username: ";
    getline(cin, inp_username);
    cout << "Password: ";
    getline(cin, inp_pass);
    // Error Check
    if(inp_username.find_first_not_of(" ") == string::npos || inp_pass.find_first_not_of(" ") == string::npos){
        cout << "Password Salah, Silahkan Coba Lagi" << endl;
        cout << "Kesempatan Login: " << percobaan-1 << endl;
        pause();
        clear();
        return login(admin_username, admin_password, head, global_username, global_password, percobaan-1);
    }
    if(inp_username.length() < 5 || inp_pass.length() < 5){
        cout << "Username dan Password minimal 5 karakter" << endl;
        cout << "Kesempatan Login: " << percobaan-1 << endl;
        pause();
        clear();
        return login(admin_username, admin_password, head, global_username, global_password, percobaan-1);
    }

    // Cek Jika Admin
    if(inp_username == admin_username && inp_pass == admin_password){
        cout << "Login Berhasil" << endl;
        global_username = admin_username;
        global_password = admin_password;
        push(admin_username);
        pause();
        clear();
        return 1; // 1 = Admin
    }

    // Cek Jika User
    for(node_user *ptr = head; ptr != nullptr; ptr = ptr->next){
        if(inp_username == ptr->data.username && inp_pass == ptr->data.password){
            cout << "Login Berhasil" << endl;
            global_username = ptr->data.username;
            global_password = ptr->data.password;
            push(ptr->data.username);
            pause();
            clear();
            return 2; // 2 = User
        }
    }
    cout << "Username/Password Salah, Silahkan Coba Lagi" << endl;
    cout << "Kesempatan Login: " << percobaan-1 << endl;
    pause();
    clear();
    return login(admin_username, admin_password, head, global_username, global_password, percobaan-1);
}

int regist(string &admin_username, string &admin_password, node_user* &head){
    string inp_username, inp_pass, inp_telepon, inp_address;
    cout << "=== REGISTER ===" << endl;
    // Input Username & Password
    cout << "Username: ";
    getline(cin, inp_username);
    cout << "Password: ";
    getline(cin, inp_pass);
    // Error & Unique Check
    if(inp_username.find_first_not_of(" ") == string::npos || inp_pass.find_first_not_of(" ") == string::npos){
        cout << "Username dan Password tidak boleh kosong" << endl;
        pause();
        clear();
        return 0;
    }
    if(inp_username.length() < 5 || inp_pass.length() <5){
        cout << "Username dan Password minimal 5 karakter" << endl;
        pause();
        clear();
        return 0;
    }
    for(node_user *ptr = head; ptr != nullptr; ptr = ptr->next){
        if (inp_username == ptr->data.username){
            cout << "Username sudah terdaftar" << endl;
            pause();
            clear();
            return 0;
        }
    }
    if (inp_username == admin_username){
        cout << "Username sudah terdaftar" << endl;
        pause();
        clear();
        return 0;
    }

    // Input Telepon
    cout << "Telepon: ";
    getline(cin, inp_telepon);
    // Error & Unique Check
    if(inp_telepon.find_first_not_of("0123456789") != string::npos){
        cout << "Telepon hanya boleh angka" << endl;
        pause();
        clear();
        return 0;
    }
    if (inp_telepon.length() < 12){
        cout << "Telepon 12-13 Digit" << endl;
        pause();
        clear();
        return 0;
    }
    for(node_user *ptr = head; ptr != nullptr; ptr = ptr->next){
        if (inp_telepon == ptr->data.telepon){
            cout << "Telepon sudah terdaftar" << endl;
            pause();
            clear();
            return 0;
        }
    }

    // Input Alamat
    cout << "Alamat: ";
    getline(cin, inp_address);
    // Error Check
    if(inp_address.find_first_not_of(" ") == string::npos){
        cout << "Alamat tidak boleh kosong" << endl;
        pause();
        clear();
        return 0;
    }
    
    // Tambahkan Data Di Akhir List
    node_user *new_node = new node_user;
    new_node->data = {inp_username, inp_pass, inp_telepon, inp_address};
    new_node->next = nullptr;
    // Jika List Kosong
    if(head == nullptr){
        head = new_node;
    }else{ // Jika List Tidak Kosong
        node_user *ptr = head;
        while(ptr->next != nullptr){
            ptr = ptr->next;
        }
        ptr->next = new_node;
    }
    cout << "Register Berhasil" << endl;
    pause();
    return 0;
}


// Menu Admin
int tambah_earphone(vector<earphone_data>* earphones){
    string nama, merk, harga, stok;
    cout << "=== TAMBAH EARPHONE ===" << endl;
    // Input Nama
    cout << "Nama: ";
    getline(cin, nama);
    // Error & Unique Check
    if(nama.find_first_not_of(" ") == string::npos){
        cout << "Nama tidak boleh kosong" << endl;
        pause();
        clear();
        return 0;
    }
    if( earphones->size() > 0){
        for(int i = 0; i < earphones->size(); i++){
            if(nama == (*earphones)[i].nama){
                cout << "Nama sudah terdaftar" << endl;
                pause();
                clear();
                return 0;
            }
        }
    }
    // Input Merk
    cout << "Merk: ";
    getline(cin, merk);
    // Error Check
    if(merk.find_first_not_of(" ") == string::npos){
        cout << "Merk tidak boleh kosong" << endl;
        pause();
        return 0;
    }
    // Input Harga
    cout << "Harga: ";
    getline(cin, harga);
    // Error Check
    if(harga.find_first_not_of("0123456789") != string::npos){
        cout << "Harga hanya boleh angka" << endl;
        pause();
        return 0;
    }
    // Input Stok
    cout << "Stok: ";
    getline(cin, stok);
    // Error Check
    if(stok.find_first_not_of("0123456789") != string::npos){
        cout << "Stok hanya boleh angka" << endl;
        pause();
        return 0;
    }
    // Push Data
    earphones->push_back({nama, merk, stoi(harga), stoi(stok)});
    cout << "Earphone Berhasil Ditambahkan" << endl;
    pause();
    return 0;
}

int lihat_earphone(vector<earphone_data>* earphones){
    cout << "=== LIST EARPHONE ===" << endl;
    for (int i = 0; i < earphones->size(); i++){
        cout << i+1 << ". " << (*earphones)[i].nama << endl;
    }

    string pilihan;
    cout << "Pilih No. Earphone Untuk Ditampilkan: ";
    getline(cin, pilihan);
    // Error Check
    if(pilihan.find_first_not_of("0123456789") != string::npos){
        cout << "Pilihan hanya boleh angka" << endl;
        pause();
        clear();
        return 0;
    }
    if(stoi(pilihan) > earphones->size()){
        cout << "Earphone tidak ditemukan" << endl;
        pause();
        clear();
        return 0;
    }
    clear();
    cout << "=== DETAIL EARPHONE ===" << endl;
    cout << "Nama: " << (*earphones)[stoi(pilihan)-1].nama << endl;
    cout << "Merk: " << (*earphones)[stoi(pilihan)-1].merk << endl;
    cout << "Harga: " << (*earphones)[stoi(pilihan)-1].harga << endl;
    cout << "Stok: " << (*earphones)[stoi(pilihan)-1].stok << endl;
    pause();
    clear();
    return 0;
}

int edit_earphone(vector<earphone_data> *earphones){
    string nama, merk, harga, stok;
    string pilihan;
    clear();
    cout << "=== EDIT EARPHONE ===" << endl;
    // Tampilkan List Earphone
    for(int i = 0; i < earphones->size(); i++){
        cout << i+1 << ". " << (*earphones)[i].nama << endl;
    }

    // Input Earphone yang dipilih
    cout << "=====================" << endl;
    cout << "Pilih No. Earphone: ";
    getline(cin, pilihan);
    // Error Check
    if(nama.find_first_not_of("0123456789") != string::npos){
        cout << "Pilihan hanya boleh angka" << endl;
        pause();
        clear();
        return 0;
    }
    if(stoi(pilihan) > earphones->size()){
        cout << "Earphone tidak ditemukan" << endl;
        pause();
        clear();
        return 0;
    }
    if (stoi(pilihan) <= 0){
        cout << "Earphone tidak ditemukan" << endl;
        pause();
        clear();
        return 0;
    }

    // Tampilkan data sebelumnya
    clear();
    cout << "=== DATA SEBELUMNYA ===" << endl;
    cout << "Nama: " << (*earphones)[stoi(pilihan)-1].nama << endl;
    cout << "Merk: " << (*earphones)[stoi(pilihan)-1].merk << endl;
    cout << "Harga: " << (*earphones)[stoi(pilihan)-1].harga << endl;
    cout << "Stok: " << (*earphones)[stoi(pilihan)-1].stok << endl;
    cout << "=== DATA BARU ===" << endl;
    
    // Input Nama Baru
    cout << "Nama: ";
    getline(cin, nama);
    // Error Check
    if(nama.find_first_not_of(" ") == string::npos){
        cout << "Nama tidak boleh kosong" << endl;
        pause();
        clear();
        return 0;
    }
    // Nama tidak boleh sama dengan merk lain
    for(int i = 0; i < earphones->size(); i++){
        if(nama == (*earphones)[i].nama && i != stoi(pilihan)-1){
            cout << "Nama sudah terdaftar" << endl;
            pause();
            clear();
            return 0;
        }
    }
    // Input Merk
    cout << "Merk: ";
    getline(cin, merk);
    // Error Check
    if(merk.find_first_not_of(" ") == string::npos){
        cout << "Merk tidak boleh kosong" << endl;
        pause();
        return 0;
    }
    // Input Harga
    cout << "Harga: ";
    getline(cin, harga);
    // Error Check
    if(harga.find_first_not_of("0123456789") != string::npos){
        cout << "Harga hanya boleh angka" << endl;
        pause();
        return 0;
    }
    if(stoi(harga) < 0){
        cout << "Harga harus bernilai positif" << endl;
        pause();
        return 0;
    }
    // Input Stok
    cout << "Stok: ";
    getline(cin, stok);
    // Error Check
    if(stok.find_first_not_of("0123456789") != string::npos){
        cout << "Stok hanya boleh angka" << endl;
        pause();
        return 0;
    }
    if(stoi(stok) < 0){
        cout << "Stok harus bernilai positif" << endl;
        pause();
        return 0;
    }
    // Edit Data Earphone Pada Vektor
    (*earphones)[stoi(pilihan)-1] = {nama, merk, stoi(harga), stoi(stok)};
    cout << "Earphone Berhasil Diubah" << endl;
    pause();
    clear();
    return 0;
}

int hapus_earphone(vector<earphone_data> *earphones){
    string nama;
    clear();
    cout << "=== HAPUS EARPHONE ===" << endl;
    // Tampilkan List Earphone
    for(int i = 0; i < earphones->size(); i++){
        cout << i+1 << ". " << (*earphones)[i].nama << endl;
    }
    // Input Nama
    cout << "Nama Earphone: ";
    getline(cin, nama);
    // Error Check
    if(nama.find_first_not_of(" ") == string::npos){
        cout << "Nama tidak boleh kosong" << endl;
        pause();
        clear();
        return 0;
    }
    for(int i = 0; i < earphones->size(); i++){
        if(nama == (*earphones)[i].nama){
            earphones->erase(earphones->begin() + i);
            cout << "Earphone Berhasil Dihapus" << endl;
            pause();
            clear();
            return 0;
        }
    }
    cout << "Earphone Tidak Ditemukan" << endl;
    pause();
    clear();
    return 0;
}

int edit_admin(string &admin_username, string &admin_password, node_user* &head){
    string inp_username, inp_pass;
    cout << "=== EDIT ADMIN ===" << endl;
    // Input Username & Password
    cout << "Username: ";
    getline(cin, inp_username);
    cout << "Password: ";
    getline(cin, inp_pass);
    // Error & Unique Check
    if(inp_username.find_first_not_of(" ") == string::npos || inp_pass.find_first_not_of(" ") == string::npos){
        cout << "Username dan Password tidak boleh kosong" << endl;
        pause();
        clear();
        return 0;
    }
    if(inp_username.length() < 5 || inp_pass.length() <5){
        cout << "Username dan Password minimal 5 karakter" << endl;
        pause();
        clear();
        return 0;
    }
    // Jika Username/Password admin identik denan salah satu akun user
    for (node_user *ptr = head; ptr != nullptr; ptr = ptr->next){
        if (inp_username == ptr->data.username){
            cout << "Username sudah terdaftar" << endl;
            pause();
            clear();
            return 0;
        }
    }
    // Edit Data
    admin_username = inp_username;
    admin_password = inp_pass;
    cout << "Admin Berhasil Diubah" << endl;
    pause();
    clear();
    return 0;
}

int view_user(node_user* &head){
    cout << "=== LIST USER ===" << endl;
    int i = 1;
    for(node_user *ptr = head; ptr != nullptr; ptr = ptr->next){
        cout << i << ". Username: " << ptr->data.username << endl;
        cout << "   Telepon: " << ptr->data.telepon << endl;
        cout << "   Alamat: " << ptr->data.address << endl ;
        cout << "   Memory Address : " << ptr << endl; 
        cout << "   Next : " << ptr->next << endl << endl;
        i++;
    }
    return 0;
}

int process_orders(){
    if(is_queue_empty()){
        cout << "Tidak ada pesanan dalam antrian." << endl;
        pause();
        return 0;
    }

    cout << "=== PROSES PESANAN ===" << endl;
    while(!is_queue_empty()){
        Order current_order = dequeue();
        cout << "Username: " << current_order.username << endl;
        cout << "Earphone: " << current_order.earphone_name << endl;
        cout << "Jumlah: " << current_order.quantity << endl;
        cout << "-------------------" << endl;
    }
    cout << "Semua pesanan telah diproses." << endl;
    pause();
    return 0;
}

int view_login_history(){
    if(is_stack_empty()){
        cout << "Belum ada riwayat login." << endl;
        pause();
        return 0;
    }

    cout << "=== RIWAYAT LOGIN ===" << endl;
    string temp_stack[MAX_STACK];
    int temp_top = -1;

    while(!is_stack_empty()){
        string username = pop();
        cout << username << endl;
        temp_stack[temp_top++] = username;
    }
    
    // Restore the original stack
    while(temp_top >= 0){
        push(temp_stack[temp_top--]);
    }
    pause();
    return 0;
}

int menu_admin(string &admin_username, string &admin_password, node_user* &head, vector<earphone_data>* earphones){
    clear();
    string pilihan;
    while(true){
        clear();
        cout << "=== MENU ADMIN ===" << endl;
        cout << "1. Tambah Earphone" << endl;
        cout << "2. Lihat Earphone" << endl;
        cout << "3. Edit Earphone" << endl;
        cout << "4. Hapus Earphone" << endl;
        cout << "5. Pengaturan Admin" << endl;
        cout << "6. Lihat User" << endl;
        cout << "7. Proses Pesanan (QUEUE)" << endl;
        cout << "8. Lihat Riwayat Login (STACK)" << endl;
        cout << "9. Logout" << endl;
        cout << "PILIH MENU: ";
        cout << "PILIH MENU: ";
        getline(cin, pilihan);
        // Error Check
        if(pilihan.find_first_not_of("123456789") != string::npos || pilihan.length() > 1){
            cout << "Pilihan tidak tersedia" << endl;
            pause();
            clear();
            continue;
        }
        if(pilihan.find_first_not_of(" ") == string::npos){
            cout << "Pilihan tidak boleh kosong" << endl;
            pause();
            clear();
            continue;
        }
        switch (stoi(pilihan)){
            case 1: // Tambah Earphone
                tambah_earphone(earphones);
                break;
            case 2: // Lihat Earphone
                if (earphones->size() == 0){
                    cout << "Tidak ada earphone untuk dilihat" << endl;
                    pause();
                    clear();
                    break;
                }
                lihat_earphone(earphones);
                break;
            case 3: // Edit Earphone
                if (earphones->size() == 0){
                    cout << "Tidak ada earphone untuk diedit" << endl;
                    pause();
                    clear();
                    break;
                }
                edit_earphone(earphones);
                break;
            case 4: // Hapus Earphone
                if (earphones->size() == 0){
                    cout << "Tidak ada earphone untuk dihapus" << endl;
                    pause();
                    clear();
                    break;
                }
                hapus_earphone(earphones);
                break;
            case 5: // Edit Admin
                edit_admin(admin_username, admin_password, head);
                break;
            case 6: // Lihat User
                clear();
                view_user(head);
                pause();
                break;
            case 7: // Proses Pesanan
                clear();
                process_orders();
                break;
            case 8: // Lihat Riwayat Login
                clear();
                view_login_history();
                break;
            case 9: // Logout
                return 0;
        }
    }
}

// Menu User
int beli_earphone( vector<earphone_data> *earphones, string username){
    string nama, jumlah;
    while(true){
        clear();
        cout << "=== BELI EARPHONE ===" << endl;
        // Tampilkan List Earphone
        for(int i = 0; i < earphones->size(); i++){
            cout << i+1 << ". "<< (*earphones)[i].nama;
            cout << "(Stok : " << (*earphones)[i].stok << ")"<< endl;
        }
        // Input Nama Earphone
        cout << "Nama: ";
        getline(cin, nama);
        // Error Check
        if(nama.find_first_not_of(" ") == string::npos){
            cout << "Nama Earphone tidak boleh kosong" << endl;
            pause();
            clear();
            return 0;
        }
        
        for(int i = 0; i < earphones->size(); i++){
            if(nama == (*earphones)[i].nama){
                // Input Jumlah Pemblian
                cout << "Jumlah: ";
                getline(cin, jumlah);
                // Error Check
                if(jumlah.find_first_not_of("0123456789") != string::npos){
                    cout << "Jumlah hanya boleh angka" << endl;
                    pause();
                    clear();
                    return 0;
                }
                if(stoi(jumlah) > (*earphones)[i].stok){
                    cout << "Stok tidak mencukupi" << endl;
                    pause();
                    clear();
                    return 0;
                }
                if (stoi(jumlah) <= 0){
                    cout << "Jumlah minimal 1" << endl;
                    pause();
                    clear();
                    return 0;
                }
                // Kurangi Stok
                (*earphones)[i].stok -= stoi(jumlah);


                // Struk Pembelian 
                cout << "=== STRUK PEMBELIAN ===" << endl;
                cout << "Nama: " << (*earphones)[i].nama << endl;
                cout << "Merk: " << (*earphones)[i].merk << endl;
                cout << "Harga: " << (*earphones)[i].harga << endl;
                cout << "Jumlah: " << jumlah << endl;
                cout << "Total: " << stoi(jumlah) * (*earphones)[i].harga << endl;

                // Tambahkan Pesanan ke Queue
                Order new_order = {username, nama, stoi(jumlah)};
                enqueue(new_order);

                cout << "Pesanan telah ditambahkan ke antrian." << endl;
                pause();
                clear();
                return 0;
            }
        }
        cout << "Earphone Tidak Ditemukan" << endl;
        pause();
        return 0;
    }
}

int edit_user(string &global_username, string &global_password, node_user* &head){
    string inp_username, inp_pass, inp_telepon, inp_address;
    cout << "=== Edit Akun ===" << endl;
    cout << "Username: " << global_username << endl;
    cout << "=================" << endl;
    // Input Username & Password
    cout << "Username Baru: ";
    getline(cin, inp_username);
    cout << "Password Baru: ";
    getline(cin, inp_pass);
    // Error & Unique Check
    if(inp_username.find_first_not_of(" ") == string::npos || inp_pass.find_first_not_of(" ") == string::npos){
        cout << "Username dan Password tidak boleh kosong" << endl;
        pause();
        clear();
        return 0;
    }
    if(inp_username.length() < 5 || inp_pass.length() <5){
        cout << "Username dan Password minimal 5 karakter" << endl;
        pause();
        clear();
        return 0;
    }
    // Jika Username/Password admin identik denan salah satu akun user
    for (node_user *ptr = head; ptr != nullptr; ptr = ptr->next){
        if (inp_username == ptr->data.username){
            cout << "Username sudah terdaftar" << endl;
            pause();
            clear();
            return 0;
        }
    }
    // Edit Data
    for(node_user *ptr = head; ptr != nullptr; ptr = ptr->next){
        if(global_username == ptr->data.username){
            ptr->data.username = inp_username;
            ptr->data.password = inp_pass;
            cout << "Akun Berhasil Diedit" << endl;
            global_username = inp_username;
            global_password = inp_pass;
            pause();
            clear();
            return 0;
        }
    }
    return 0;
}

int hapus_user(string &global_username, string &global_password, node_user* &head){
    string inp_username, inp_pass;
    cout << "=== Hapus Akun ===" << endl;
    // Input Username & Password
    cout << "Password: ";
    getline(cin, inp_pass);
    // Error & Unique Check
    if(inp_pass.find_first_not_of(" ") == string::npos){
        cout << "Password tidak boleh kosong" << endl;
        pause();
        clear();
        return 1;
    }
    if(inp_pass.length() <5){
        cout << "Password minimal 5 karakter" << endl;
        pause();
        clear();
        return 1;
    }
    // Jika Password Sesuai
    if(inp_pass == global_password){
        // Hapus Data
        node_user *ptr = head;
        node_user *prev = nullptr;
        while(ptr != nullptr){
            if(global_username == ptr->data.username){
                if(prev == nullptr){
                    head = ptr->next;
                }else{
                    prev->next = ptr->next;
                }
                delete ptr;
                cout << "Akun Berhasil Dihapus" << endl;
                pause();
                clear();
                return 0;
            }
            prev = ptr;
            ptr = ptr->next;
        }
    }
    cout << "Password Salah" << endl;
    pause();
    clear();
    return 1;
}

int menu_user(string &global_username, string &global_password, string admin_username, string admin_password, node_user* &head, vector<earphone_data> *earphones){
    string pilihan;
    while(true){
        clear();
        cout << "=== MENU USER ===" << endl;
        cout << " User : " << global_username << endl;
        cout << "=================" << endl;
        cout << "1. Lihat Earphone" << endl;
        cout << "2. Beli Earphone (QUEUE)" << endl;
        cout << "3. Pengaturan Akun" << endl;
        cout << "4. Hapus Akun" << endl;
        cout << "5. Logout" << endl;
        cout << "PILIH MENU: ";
        getline(cin, pilihan);
        // Error Check
        if(pilihan.find_first_not_of("12345") != string::npos || pilihan.length() > 1){
            cout << "Pilihan tidak tersedia" << endl;
            pause();
            clear();
            continue;
        }
        if(pilihan.find_first_not_of(" ") == string::npos){
            cout << "Pilihan tidak boleh kosong" << endl;
            pause();
            clear();
            continue;
        }
        clear();
        switch (stoi(pilihan)){
            case 1: // Lihat Earphone
                lihat_earphone(earphones);
                break;
            case 2: // Beli Earphone
                beli_earphone(earphones, global_username);
                break;
            case 3: 
                edit_user(global_username, global_password, head);
                break;
            case 4:
                if((hapus_user(global_username, global_password, head)) == 0){
                    return 0; // Logout setelah hapus akun
                }
            case 5: // Logout
                return 0;
        }
    }
}


// Main Program
int main() {
    // Database Awal

    node_user *temp = new node_user;
    temp->data = {"user123", "pass123", "081234567890", "Jl. Jalan"};
    temp->next = nullptr;

    node_user *head_user = temp;
    int jumlah_user = 1;

    vector<earphone_data> earphones;
    earphones.push_back({"Earphone 1", "Merk 1", 100000, 10});
    string admin_username = "admin123";
    string admin_password = "admin123";

    // Variabel Awal
    string global_username, global_password;
    int login_status = 0;
    int pilihan;

    // Menu Awal
    while(true){
        clear();
        // Debug Output
        // tampilkan list akun user
        cout << "=== TIPS ===" << endl;
        cout << "Username User : user123" << endl;
        cout << "Password User : pass123" << endl;
        cout << "Username Admin : admin123" << endl;
        cout << "Password Admin : admin123" << endl;

        pilihan = menu_awal();
        switch(pilihan){
            case 1: // Login
                clear();
                // Login
                // 0 = Gagal Login, 1 = Admin, 2 = User
                login_status = login(admin_username, admin_password, head_user, global_username, global_password);
                if (login_status == 0){
                    continue;
                }
                break;
            case 2: // Register
                clear();
                // Register
                regist(admin_username, admin_password, head_user);
                continue;
            case 3: // Exit Program
                return 0;
        }
        switch (login_status){
            case 1: // Menu Admin
                menu_admin(admin_username, admin_password, head_user, &earphones);
                break;
            case 2: // Menu User
                menu_user(global_username, global_password, admin_username, admin_password, head_user, &earphones);
                break;
        }
    }
}