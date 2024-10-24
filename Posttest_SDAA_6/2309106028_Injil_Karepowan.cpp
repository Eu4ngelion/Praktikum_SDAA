// Program Penjualan Earphone
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <cmath>

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
// Node Earphone
struct node_earphone{
    earphone_data data;
    node_earphone *next;
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
        cout << "1. Login" << endl;
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

// Sort Algoritma
void split(node_earphone* &head, node_earphone* &front, node_earphone* &back){
    node_earphone *fast = head->next;
    node_earphone *slow = head;
    while(fast != nullptr){
        fast = fast->next;
        if(fast != nullptr){
            slow = slow->next;
            fast = fast->next;
        }
    }
    front = head;
    back = slow->next;
    slow->next = nullptr;
}
void merge(node_earphone* &head, node_earphone* &front, node_earphone* &back){
    node_earphone *temp = new node_earphone;
    node_earphone *ptr = temp;
    while(front != nullptr && back != nullptr){
        if(front->data.nama < back->data.nama){
            ptr->next = front;
            front = front->next;
        }else{
            ptr->next = back;
            back = back->next;
        }
        ptr = ptr->next;
    }
    ptr->next = (front == nullptr) ? back : front;
    head = temp->next;
    delete temp;
}
void merge_sort(node_earphone* &head){
    node_earphone *front, *back;
    if(head == nullptr || head->next == nullptr){
        return;
    }
    split(head, front, back);
    merge_sort(front);
    merge_sort(back);
    merge(head, front, back);
}

// Sort Harga
void merge_harga(node_earphone* &head, node_earphone* &front, node_earphone* &back){
    node_earphone *temp = new node_earphone;
    node_earphone *ptr = temp;
    while(front != nullptr && back != nullptr){
        if(front->data.harga < back->data.harga){
            ptr->next = front;
            front = front->next;
        }else{
            ptr->next = back;
            back = back->next;
        }
        ptr = ptr->next;
    }
    ptr->next = (front == nullptr) ? back : front;
    head = temp->next;
    delete temp;
}
void merge_sort_harga(node_earphone* &head){
    node_earphone *front, *back;
    if(head == nullptr || head->next == nullptr){
        return;
    }
    split(head, front, back);
    merge_sort_harga(front);
    merge_sort_harga(back);
    merge_harga(head, front, back);
}

// Sort Stok
void merge_stok(node_earphone* &head, node_earphone* &front, node_earphone* &back){
    node_earphone *temp = new node_earphone;
    node_earphone *ptr = temp;
    while(front != nullptr && back != nullptr){
        if(front->data.stok < back->data.stok){
            ptr->next = front;
            front = front->next;
        }else{
            ptr->next = back;
            back = back->next;
        }
        ptr = ptr->next;
    }
    ptr->next = (front == nullptr) ? back : front;
    head = temp->next;
    delete temp;
}
void merge_sort_stok(node_earphone* &head){
    node_earphone *front, *back;
    if(head == nullptr || head->next == nullptr){
        return;
    }
    split(head, front, back);
    merge_sort_stok(front);
    merge_sort_stok(back);
    merge_stok(head, front, back);
}

// Shell Sort Descending Single Linked List
node_earphone* head_at(int index, node_earphone* head) {
    node_earphone* current = head;
    for (int i = 0; i < index && current != nullptr; i++) {
        current = current->next;
    }
    return current;
}
void shell_sort(node_earphone* &head) {
    int n = 0;
    for (node_earphone* temp = head; temp != nullptr; temp = temp->next) {
        n++;
    }

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            node_earphone* temp = head;
            for (int j = 0; j < i; j++) {
                temp = temp->next;
            }
            earphone_data key = temp->data;
            int j;
            for (j = i; j >= gap && head_at(j - gap, head)->data.nama < key.nama; j -= gap) {
                node_earphone* current = head_at(j, head);
                node_earphone* prev = head_at(j - gap, head);
                current->data = prev->data;
            }
            head_at(j, head)->data = key;
        }
    }
}

// Searching
// Fibonacci Search
int fibonacci_search(node_earphone* &head, string key) {
    // Sort list berdasarkan harga
    


    int n = 0;
    for (node_earphone* temp = head; temp != nullptr; temp = temp->next) {
        n++;
    }

    int fib2 = 0;
    int fib1 = 1;
    int fib = fib1 + fib2;
    while (fib < n) {
        fib2 = fib1;
        fib1 = fib;
        fib = fib1 + fib2;
    }

    int offset = -1;
    while (fib > 1) {
        int i = min(offset + fib2, n - 1);
        node_earphone* temp = head;
        for (int j = 0; j < i; j++) {
            temp = temp->next;
        }
        if (temp->data.nama == key) {
            return i;
        } else if (temp->data.nama < key) {
            fib = fib1;
            fib1 = fib2;
            fib2 = fib - fib1;
            offset = i;
        } else {
            fib = fib2;
            fib1 -= fib2;
            fib2 = fib - fib1;
        }
    }

    node_earphone* temp = head;
    for (int i = 0; i < n; i++) {
        if (temp->data.nama == key) {
            return i;
        }
        temp = temp->next;
    }

    return -1;
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

// Searching
// Fibonacci Search
int fibonacci_search(node_earphone* &head, int  key) {
    // Sort list berdasarkan harga
    merge_sort_harga(head);

    int n = 0;
    for (node_earphone* temp = head; temp != nullptr; temp = temp->next) {
        n++;
    }

    int fib2 = 0;
    int fib1 = 1;
    int fib = fib1 + fib2;
    while (fib < n) {
        fib2 = fib1;
        fib1 = fib;
        fib = fib1 + fib2;
    }

    int offset = -1;
    while (fib > 1) {
        int i = min(offset + fib2, n - 1);
        node_earphone* temp = head;
        for (int j = 0; j < i; j++) {
            temp = temp->next;
        }
        if (temp->data.harga == key) {
            cout << temp->data.nama << endl;
            return 0;
        } else if (temp->data.harga < key) {
            fib = fib1;
            fib1 = fib2;
            fib2 = fib - fib1;
            offset = i;
        } else {
            fib = fib2;
            fib1 -= fib2;
            fib2 = fib - fib1;
        }
    }

    node_earphone* temp = head;
    for (int i = 0; i < n; i++) {
        if (temp->data.harga == key) {
            cout << temp->data.nama << i << endl;
        }
        temp = temp->next;
    }
    return -1;
}

// Jump Search
int jump_search(node_earphone* &head, int key) {
    // Sort list berdasarkan stok
    merge_sort_stok(head);

    int n = 0;
    for (node_earphone* temp = head; temp != nullptr; temp = temp->next) {
        n++;
    }

    int step = sqrt(n);
    int prev = 0;
    while (head_at(min(step, n) - 1, head)->data.stok < key) {
        prev = step;
        step += sqrt(n);
        if (prev >= n) {
            return -1;
        }
        // Jika data langsung ditemukan
        if (head_at(prev, head)->data.stok == key) {
            break;
        }
    }

    // Linear Search
    int found= false;
    for (int i = prev; i < min(step, n); i++) {
        if (head_at(i, head)->data.stok == key) {
            cout << head_at(i, head)->data.nama << endl;
            found = true;
        }
    }

    if (!found) {
        return -1;
    }
    return 0;
}

// Boyer Moore Search
const int NO_OF_CHARS = 256;

void badCharHeuristic(string str, int size, int badChar[NO_OF_CHARS]) {
    for (int i = 0; i < NO_OF_CHARS; i++) {
        badChar[i] = -1;
    }
    for (int i = 0; i < size; i++) {
        badChar[(int)str[i]] = i;
    }
}

int boyer_moore_search(node_earphone* &head, string pat) {
    int m = pat.size();
    node_earphone* temp = head;
    while (temp != nullptr) {
        int n = temp->data.nama.size();
        int badChar[NO_OF_CHARS];
        badCharHeuristic(pat, m, badChar);
        int s = 0;

        while (s <= (n - m)) {
            int j = m - 1;

            while (j >= 0 && pat[j] == temp->data.nama[s + j]) {
                j--;
            }
            if (j < 0) {
                cout << temp->data.nama << endl;
                break;
            }
            else {
                s += max(1, j - badChar[(int)temp->data.nama[s + j]]);
            }
        }
        temp = temp->next;
    }
    return 0;
}

// Menu Admin
int tambah_earphone(node_earphone* &head, int &jumlah_earphone){
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
    // Tambah Data Di Awal List
    node_earphone *new_node = new node_earphone;
    new_node->data = {nama, merk, stoi(harga), stoi(stok)};
    new_node->next = head;
    head = new_node;
    cout << "Earphone Berhasil Ditambahkan" << endl;
    pause();
    clear();
    return 0;
}

int lihat_earphone(node_earphone* &head, int &jumlah_earphone){
    // Sort 
    merge_sort(head);
    cout << "=== LIST EARPHONE ===" << endl;
    int i = 1;
    for(node_earphone *ptr = head; ptr != nullptr; ptr = ptr->next){
        cout << i << ". Nama: " << ptr->data.nama << endl;
        cout << "   Merk: " << ptr->data.merk << endl;
        cout << "   Harga: " << ptr->data.harga << endl;
        cout << "   Stok: " << ptr->data.stok << endl;
        cout << "   Memory Address : " << ptr << endl; 
        cout << "   Next : " << ptr->next << endl << endl;
        i++;
    }
    cout << "=====================" << endl;
    pause();
    clear();
    return 0;
}

int edit_earphone(node_earphone* &head, int &jumlah_earphone){
    string nama, merk, harga, stok;
    string pilihan;
    node_earphone *ptr = head;
    clear();
    cout << "=== EDIT EARPHONE ===" << endl;
    // Tampilkan List Earphone
    lihat_earphone(head, jumlah_earphone);

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
    if(stoi(pilihan) < 1 || stoi(pilihan) > jumlah_earphone){
        cout << "Pilihan tidak tersedia" << endl;
        pause();
        clear();
        return 0;
    }
    // Set Pointer
    for(int i = 0; i < stoi(pilihan)-1; i++){
        ptr = ptr->next;
    }

    // Tampilkan data earphone yang dipilih
    clear();
    cout << "=== EDIT EARPHONE ===" << endl;
    cout << "Nama: " << ptr->data.nama << endl;
    cout << "Merk: " << ptr->data.merk << endl;
    cout << "Harga: " << ptr->data.harga << endl;
    cout << "Stok: " << ptr->data.stok << endl;
    cout << "=====================" << endl;



    // Input Nama Baru
    cout << "Nama Baru: ";
    getline(cin, nama);
    // Error Check
    if(nama.find_first_not_of(" ") == string::npos){
        cout << "Nama tidak boleh kosong" << endl;
        pause();
        clear();
        return 0;
    }
    // Nama tidak boleh sama dengan merk lain
    node_earphone *temp = head;
    for(int i = 0; i < jumlah_earphone; i++){
        if(nama == temp->data.nama){
            cout << "Nama sudah terdaftar" << endl;
            pause();
            clear();
            return 0;
        }
        temp = temp->next;
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
    ptr->data = {nama, merk, stoi(harga), stoi(stok)};
    cout << "Earphone Berhasil Diedit" << endl;
    pause();
    clear();
    return 0;
}

int hapus_earphone(node_earphone* &head, int &jumlah_earphone){
    string nama;
    clear();
    cout << "=== HAPUS EARPHONE ===" << endl;
    // Tampilkan List Earphone
    lihat_earphone(head, jumlah_earphone);

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
    // Cari Nama Earphone
    node_earphone *ptr = head;
    node_earphone *prev = nullptr;
    while(ptr != nullptr){
        if(nama == ptr->data.nama){
            if(prev == nullptr){
                head = ptr->next;
            }else{
                prev->next = ptr->next;
            }
            delete ptr;
            cout << "Earphone Berhasil Dihapus" << endl;
            pause();
            clear();
            return 0;
        }
        prev = ptr;
        ptr = ptr->next;
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





int menu_admin(string &admin_username, string &admin_password, node_user* &head, node_earphone* &earphones, int &jumlah_earphone){
    clear();
    string pilihan, str_key;
    int int_key;
    node_earphone *end;
    while(true){
        clear();
        end = nullptr;
        cout << "=== MENU ADMIN ===" << endl;
        cout << "1. Tambah Earphone" << endl;
        cout << "2. Lihat Earphone" << endl;
        cout << "3. Search Harga (Fibonacci)" << endl;
        cout << "4. Search Stok (Jump Search)" << endl;
        cout << "5. Search Nama (Boyer-Moore)" << endl;
        cout << "6. Edit Earphone" << endl;
        cout << "7. Hapus Earphone" << endl;
        cout << "8. Logout" << endl;
        cout << "PILIH MENU: ";
        getline(cin, pilihan);
        // Error Check
        if(pilihan.find_first_not_of("012345678") != string::npos){
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
                tambah_earphone(earphones, jumlah_earphone);
                break;
            case 2: // Lihat Earphone
                lihat_earphone(earphones, jumlah_earphone);
                break;
            case 3: // Search Harga
                clear();
                if(earphones == nullptr){
                    cout << "Tidak ada earphone" << endl;
                    pause();
                    break;
                }
                // Input Harga
                cout << "=== SEARCH HARGA ===" << endl;
                cout << "Harga: ";
                getline(cin, str_key);
                // Error Check
                if(str_key.find_first_not_of("0123456789") != string::npos){
                    cout << "Harga hanya boleh angka" << endl;
                    pause();
                    clear();
                    break;
                }
                int_key = stoi(str_key);
                cout << "Earphone dengan Harga " << int_key  << ":"<< endl;
                fibonacci_search(earphones, int_key);
                pause();
                clear();
                merge_sort(earphones);
                break;
            case 4: // Search Stok
                clear();
                if(earphones == nullptr){
                    cout << "Tidak ada earphone" << endl;
                    pause();
                    break;
                }
                // Input Stok
                cout << "=== SEARCH STOK ===" << endl;
                cout << "Stok: ";
                getline(cin, str_key);
                // Error Check
                if(str_key.find_first_not_of("0123456789") != string::npos){
                    cout << "Stok hanya boleh angka" << endl;
                    pause();
                    clear();
                }
                int_key = stoi(str_key);
                cout << "Earphone dengan Stok " << int_key << ":" << endl;
                jump_search(earphones, int_key);
                pause();
                clear();
                merge_sort(earphones);
                break;
            case 5: // Search Nama
                clear();
                if(earphones == nullptr){
                    cout << "Tidak ada earphone" << endl;
                    pause();
                    break;
                }

                // Input Nama
                cout << "=== SEARCH NAMA ===" << endl;
                cout << "Nama: ";
                getline(cin, str_key);
                // Error Check
                if(str_key.find_first_not_of(" ") == string::npos){
                    cout << "Nama tidak boleh kosong" << endl;
                    pause();
                    clear();
                    break;
                }
                cout << "Earphone dengan Nama " << str_key << ":" << endl;
                boyer_moore_search(earphones, str_key);
                pause();
                clear();
                break;
            case 6: // Edit Earphone
                edit_earphone(earphones, jumlah_earphone);
                break;
            case 7: // Hapus Earphone
                hapus_earphone(earphones, jumlah_earphone);
                break;
            case 8: // Logout
                return 0;
            default:
                cout << "Pilihan tidak tersedia" << endl;
                pause();
                clear();
                break;
        }
    }
}

// Menu User
int beli_earphone(node_earphone* &earphones, int &jumlah_earphone, string username){
    string nama, jumlah;
    while(true){
        clear();
        cout << "=== BELI EARPHONE ===" << endl;
        // Tampilkan List Earphone
        lihat_earphone(earphones, jumlah_earphone);

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
        // Input Jumlah
        cout << "Jumlah: ";
        getline(cin, jumlah);
        // Error Check
        if(jumlah.find_first_not_of("0123456789") != string::npos){
            cout << "Jumlah hanya boleh angka" << endl;
            pause();
            return 0;
        }
        if(stoi(jumlah) < 1){
            cout << "Jumlah minimal 1" << endl;
            pause();
            return 0;
        }
        // Cari Nama Earphone
        for(node_earphone *ptr = earphones; ptr != nullptr; ptr = ptr->next){
            if(nama == ptr->data.nama){
                if(stoi(jumlah) > ptr->data.stok){
                    cout << "Stok tidak mencukupi" << endl;
                    pause();
                    return 0;
                }else{
                    // Kurangi Stok
                    ptr->data.stok -= stoi(jumlah);
                    // Struk Pembelian
                    cout << "=== STRUK PEMBELIAN ===" << endl;
                    cout << "Nama: " << ptr->data.nama << endl;
                    cout << "Merk: " << ptr->data.merk << endl;
                    cout << "Harga: " << ptr->data.harga << endl;
                    cout << "Jumlah: " << jumlah << endl;
                    cout << "Total: " << stoi(jumlah) * ptr->data.harga << endl;
                    // Tambahkan Pesanan ke Queue
                    Order new_order = {username, nama, stoi(jumlah)};
                    enqueue(new_order);
                    cout << "Pesanan telah ditambahkan ke antrian." << endl;
                    pause();
                    clear();
                    return 0;
                }
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

int menu_user(string &global_username, string &global_password, string admin_username, string admin_password, node_user* &head, node_earphone* &earphones, int &jumlah_earphone){
    string pilihan, str_key;
    int int_key;
    while(true){
        clear();
        cout << "=== MENU USER ===" << endl;
        cout << " User : " << global_username << endl;
        cout << "=================" << endl;
        cout << "1. Lihat Earphone" << endl;
        cout << "2. Beli Earphone (QUEUE)" << endl;
        cout << "3. Search Harga (Fibonacci Search)" << endl;
        cout << "4. Sort Stok (Jump Search)" << endl;
        cout << "5. Search Nama (Boyer-Moore)" << endl;
        cout << "6. Hapus Akun" << endl;
        cout << "7. Logout" << endl;
        cout << "PILIH MENU: ";
        getline(cin, pilihan);
        // Error Check
        if(pilihan.find_first_not_of("1234567") != string::npos || pilihan.length() > 1){
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
                if (earphones == nullptr){
                    cout << "Tidak ada earphone" << endl;
                    pause();
                    clear();
                    break;
                }
                lihat_earphone(earphones, jumlah_earphone);
                break;

            
            case 2: // Beli Earphone
                beli_earphone(earphones, jumlah_earphone, global_username);
                break;

            case 3: // Search Harga
                clear();
                if(earphones == nullptr){
                    cout << "Tidak ada earphone" << endl;
                    pause();
                    break;
                }
                // Input Harga
                cout << "=== SEARCH HARGA ===" << endl;
                cout << "Harga: ";
                getline(cin, str_key);
                // Error Check
                if(str_key.find_first_not_of("0123456789") != string::npos){
                    cout << "Harga hanya boleh angka" << endl;
                    pause();
                    clear();
                    break;
                }
                int_key = stoi(str_key);
                cout << "Earphone dengan Harga " << int_key  << ":"<< endl;
                fibonacci_search(earphones, int_key);
                pause();
                clear();
                merge_sort(earphones);
                break;
            case 4: // Search Stok
                clear();
                if(earphones == nullptr){
                    cout << "Tidak ada earphone" << endl;
                    pause();
                    break;
                }
                // Input Stok
                cout << "=== SEARCH STOK ===" << endl;
                cout << "Stok: ";
                getline(cin, str_key);
                // Error Check
                if(str_key.find_first_not_of("0123456789") != string::npos){
                    cout << "Stok hanya boleh angka" << endl;
                    pause();
                    clear();
                }
                int_key = stoi(str_key);
                cout << "Earphone dengan Stok " << int_key << ":" << endl;
                jump_search(earphones, int_key);
                pause();
                clear();
                merge_sort(earphones);
                break;
            case 5: // Search Nama
                clear();
                if(earphones == nullptr){
                    cout << "Tidak ada earphone" << endl;
                    pause();
                    break;
                }

                // Input Nama
                cout << "=== SEARCH NAMA ===" << endl;
                cout << "Nama: ";
                getline(cin, str_key);
                // Error Check
                if(str_key.find_first_not_of(" ") == string::npos){
                    cout << "Nama tidak boleh kosong" << endl;
                    pause();
                    clear();
                    break;
                }
                cout << "Earphone dengan Nama " << str_key << ":" << endl;
                boyer_moore_search(earphones, str_key);
                pause();
                clear();
                break;
            case 6: 
                edit_user(global_username, global_password, head);
                break;
            case 7: // Logout
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

    node_earphone *head_earphone = nullptr;
    int jumlah_earphone = 0;


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
                menu_admin(admin_username, admin_password, head_user, head_earphone, jumlah_earphone);
                break;
            case 2: // Menu User
                menu_user(global_username, global_password, admin_username, admin_password, head_user, head_earphone, jumlah_earphone);
                break;
        }
    }
}