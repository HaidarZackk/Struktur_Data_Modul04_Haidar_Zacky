# <h1 align="center"> Modul 4 SINGLY LINKED LIST (BAGIAN PERTAMA) </h1>
<p align="center">Muhammad Haidar Az Zacky - 109082530035</p>

## Dasar Teori

### A. Linked List dengan Pointer

Linked list (biasa disebut list saja) adalah bentuk struktur data berupa rangkaian elemen data yang saling berkaitan dan bersifat fleksibel karena dapat tumbuh dan mengerut sesuai kebutuhan. Data yang disimpan bisa berupa data tunggal (misalnya satu `string`) maupun data majemuk berupa *record* (misalnya data mahasiswa yang terdiri dari nama dan NIM).

Linked list dapat diimplementasikan dengan array atau pointer. Pada praktikum ini dipakai **pointer** karena array bersifat statis dan lebih cocok untuk data yang jumlah maksimumnya sudah diketahui sejak awal, sedangkan pointer bersifat dinamis sehingga cocok dengan sifat linked list yang fleksibel. Elemen yang ditunjuk pointer diakses dengan operator panah (`->`) atau titik (`.`).

Operasi umum pada ADT linked list meliputi:
1. Penciptaan dan inisialisasi list (*Create List*)
2. Penyisipan elemen (*Insert*)
3. Penghapusan elemen (*Delete*)
4. Penelusuran dan penampilan elemen (*View*)
5. Pencarian elemen (*Searching*)
6. Pengubahan isi elemen (*Update*)

### B. Singly Linked List

Singly linked list adalah model linked list yang hanya memiliki **satu arah pointer**. Setiap elemen terdiri dari dua bagian: *data* (informasi utama) dan *successor* (`next`, penghubung ke elemen berikutnya).

Sifat singly linked list:
1. Hanya memerlukan satu buah pointer pada tiap elemen.
2. Node akhir menunjuk ke `Nil` (kecuali pada list circular).
3. Hanya dapat melakukan pembacaan maju.
4. Pencarian dilakukan secara sekuensial jika data tidak terurut.
5. Penyisipan atau penghapusan di tengah list lebih mudah dibanding array.

Istilah penting: `first/head` (pointer ke elemen pertama), `next` (pointer ke elemen berikutnya), `Nil/NULL` (tidak mengacu ke mana pun), dan `node` (tempat penyimpanan data pada memori).

### C. Komponen dan Operasi Dasar

| Operasi | Keterangan |
|---|---|
| `createList` | Membentuk list kosong dengan mengisi `first = Nil` |
| `alokasi` | Membuat node baru dengan `new` (C++) atau `malloc` (C) |
| `dealokasi` | Mengembalikan memori node ke sistem dengan `delete` (C++) atau `free` (C) |
| `isEmpty` | Mengecek apakah list kosong (`first == Nil`) |
| `insertFirst` | Menyisipkan node di awal list: `P->next = L.first; L.first = P;` |
| `insertLast` | Menyisipkan node di akhir list: telusuri sampai node terakhir `Q`, lalu `Q->next = P;` |
| `insertAfter` | Menyisipkan node setelah node tertentu: `P->next = Q->next; Q->next = P;` |
| `deleteFirst` | Menghapus node pertama: `P = L.first; L.first = L.first->next; P->next = Nil;` |
| `deleteLast` | Menghapus node terakhir: cari node sebelum terakhir `Q`, lalu `Q->next = Nil;` |
| `deleteAfter` | Menghapus node setelah node tertentu: `P->next = Q->next; Q->next = Nil;` |
| `printInfo` / `view` | Menelusuri list dan menampilkan data tiap node |
| `nbList` | Mengembalikan jumlah elemen pada list |
| `delAll` / `deleteList` | Membebaskan seluruh memori node sehingga list menjadi kosong |

Seluruh operasi tersebut disebut primitif dan disimpan dalam ADT: file `.h` untuk tipe data dan prototipe, serta file `.cpp` untuk realisasinya.

## Guided

### 1. Program list.h

```C++
#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <string>
#include <cstddef>
using namespace std;

#define Nil NULL

struct dataMahasiswa {
    string nama;
    string nim;
    int umur;
};

typedef struct node *address;

struct node {
    dataMahasiswa isidata;
    address next;
};

struct LinkedList {
    address first;
};

bool isEmpty(LinkedList List);
void createList(LinkedList &List);
address alokasi(string nama, string nim, int umur);
void dealokasi(address &node);
void insertFirst(LinkedList &List, address nodeBaru);
void insertAfter(LinkedList &List, address nodeBaru, address Prev);
void insertLast(LinkedList &List, address nodeBaru);
void delFirst(LinkedList &List);
void delLast(LinkedList &List);
void delAfter(LinkedList &List, address nodeHapus, address nodePrev);
void printList(LinkedList List);
int nbList(LinkedList List);
void deleteList(LinkedList &List);

#endif
```
**Penjelasan:** Ini adalah *header* yang berisi "kontrak" ADT singly linked list.
- `#ifndef / #define / #endif` adalah header guard agar file tidak terbaca dua kali.
- `#define Nil NULL` memberi nama `Nil` untuk pointer kosong, sesuai istilah pada materi.
- `struct dataMahasiswa` adalah data majemuk (record) berisi `nama`, `nim`, dan `umur` yang disimpan pada tiap node.
- `struct node` adalah elemen list, berisi `isidata` dan pointer `next` ke node berikutnya. `typedef struct node *address` membuat `address` menjadi alias dari pointer ke `node`.
- `struct LinkedList` hanya menyimpan satu pointer `first` yang menunjuk node pertama.
- Baris prototipe di bawahnya adalah primitif: pembuatan list (`createList`), pengecekan (`isEmpty`), manajemen memori (`alokasi`, `dealokasi`), penyisipan (`insertFirst/After/Last`), penghapusan (`delFirst/Last/After`, `deleteList`), serta penelusuran (`printList`, `nbList`).

### 2. Program list.cpp

```C++
#include "list.h"
#include <iostream>
using namespace std;

//I.S = Initial State / kondisi awal
//F.S = Final State / kondisi akhir

//fungsi untuk cek apakah list kosong atau tidak
bool isEmpty(LinkedList List) {
    if(List.first == Nil){
        return true;
    } else {
        return false;
    }
}

//pembuatan linked list kosong
void createList(LinkedList &List) {
    /* I.S. sembarang
       F.S. terbentuk list kosong */
    List.first = Nil;
}

//pembuatan node baru dengan menerapkan manajemen memori
address alokasi(string nama, string nim, int umur) {
    /* I.S. sembarang
       F.S. mengembalikan alamat node baru dengan isidata = sesuai parameter dan next = Nil */
    address nodeBaru = new node;
    nodeBaru->isidata.nama = nama;
    nodeBaru->isidata.nim = nim;
    nodeBaru->isidata.umur = umur;
    nodeBaru->next = Nil;
    return nodeBaru;
}

//penghapusan node dengan menerapkan manajemen memori
void dealokasi(address &node) {
    /* I.S. P terdefinisi
       F.S. memori yang digunakan node dikembalikan ke sistem */
    node->next = Nil;
    delete node;
}

//prosedur-prosedur untuk insert / menambahkan node baru kedalam list
void insertFirst(LinkedList &List, address nodeBaru) {
    /* I.S. sembarang, P sudah dialokasikan
       F.S. menempatkan elemen list (node) pada awal list */
    nodeBaru->next = List.first;
    List.first = nodeBaru;
}

void insertAfter(LinkedList &List, address nodeBaru, address Prev) {
    /* I.S. sembarang, nodeBaru dan Prev alamat salah satu elemen list (node)
       F.S. menempatkan elemen (node) sesudah elemen node Prev */
    if (Prev != Nil) {
        nodeBaru->next = Prev->next;
        Prev->next = nodeBaru;
    } else {
        cout << "Node sebelumnya tidak valid!" << endl;
    }
}

void insertLast(LinkedList &List, address nodeBaru) {
    /* I.S. sembarang, nodeBaru sudah dialokasikan
       F.S. menempatkan elemen nodeBaru pada akhir list */
    if (isEmpty(List)) {
        List.first = nodeBaru;
    } else {
        address nodeBantu = List.first;
        while (nodeBantu->next != Nil) {
            nodeBantu = nodeBantu->next;
        }
        nodeBantu->next = nodeBaru;
    }
}

//prosedur-prosedur untuk delete / menghapus node yang ada didalam list
void delFirst(LinkedList &List){
    /* I.S. list tidak kosong
       F.S. node pertama di list terhapus*/
    address nodeHapus;
    if (isEmpty(List) == false) {
        nodeHapus = List.first;
        List.first = List.first->next;
        nodeHapus->next = Nil;
        dealokasi(nodeHapus);
    } else {
        cout << "List kosong!" << endl;
    }
}

void delLast(LinkedList &List){
    /* I.S. list tidak kosong
       F.S. node terakhir di list terhapus */
    address nodeHapus, nodePrev;
    if(isEmpty(List) == false){
        nodeHapus = List.first;
        if(nodeHapus->next == Nil){
            List.first->next = Nil;
            dealokasi(nodeHapus);
        } else {
            while(nodeHapus->next != Nil){
                nodePrev = nodeHapus;
                nodeHapus = nodeHapus->next;
            }
            nodePrev->next = Nil;
            dealokasi(nodeHapus);
        }
    } else {
        cout << "list kosong" << endl;
    }
}

void delAfter(LinkedList &List, address nodeHapus, address nodePrev){
    /* I.S. list tidak kosng, Prev alamat salah satu elemen list
       F.S. nodeBantu adalah alamat dari Prev->next, menghapus Prev->next dari list */
    if(isEmpty(List) == true){
        cout << "List kosong!" << endl;
    } else { //jika list tidak kosong
        if (nodePrev != Nil && nodePrev->next != Nil) {
            nodeHapus = nodePrev->next;
            nodePrev->next = nodeHapus->next;
            nodeHapus->next = Nil;
            dealokasi(nodeHapus);
        } else {
            cout << "Node sebelumnya (prev) tidak valid!" << endl;
        }
    }
}

//prosedur untuk menampilkan isi list
void printList(LinkedList List) {
    /* I.S. list mungkin kosong
       F.S. jika list tidak kosong menampilkan semua info yang ada pada list */
    if (isEmpty(List)) {
        cout << "List kosong." << endl;
    } else {
        address nodeBantu = List.first;
        while (nodeBantu != Nil) {
            cout << "Nama : " << nodeBantu->isidata.nama << ", NIM : " << nodeBantu->isidata.nim << ", Usia : " << nodeBantu->isidata.umur << endl;
            nodeBantu = nodeBantu->next;
        }
    }
}

//function untuk menampilkan jumlah node didalam list
int nbList(LinkedList List) {
    /* I.S. list sudah ada
       F.S. menampilkan jumlah node didalam list*/
    int count = 0;
    address nodeBantu = List.first;
    while (nodeBantu != Nil) {
        count++;
        nodeBantu = nodeBantu->next;
    }
    return count;
}

//prosedur untuk menghapus list (menghapus semua node didalam list)
void deleteList(LinkedList &List){
    /* I.S. list sudah ada
       F.S. menghapus semua node didalam list*/
    address nodeBantu, nodeHapus;
    nodeBantu = List.first;
    while(nodeBantu != Nil){
        nodeHapus = nodeBantu;
        nodeBantu = nodeBantu->next;
        dealokasi(nodeHapus);
    }
    List.first = Nil;
    cout << "List sudah terhapus!" << endl;
}
```
**Penjelasan:** File ini berisi realisasi seluruh primitif yang dideklarasikan di `list.h`.
- `isEmpty` mengembalikan `true` bila `first == Nil`. `createList` mengisi `first` dengan `Nil` sehingga terbentuk list kosong.
- `alokasi` membuat node baru dengan `new node`, mengisi `nama`, `nim`, `umur`, dan mengatur `next = Nil`. `dealokasi` mengembalikan memori node dengan `delete`.
- `insertFirst`: `next` node baru diarahkan ke `first` lama, lalu `first` menunjuk node baru. `insertAfter`: `next` node baru mengambil `Prev->next`, lalu `Prev->next` diarahkan ke node baru. `insertLast`: jika list kosong node baru menjadi `first`, jika tidak list ditelusuri sampai node terakhir lalu `next`-nya diarahkan ke node baru.
- `delFirst` memindahkan `first` ke node berikutnya lalu mendealokasi node lama. `delLast` menelusuri list sambil mencatat node sebelumnya (`nodePrev`), memutus `nodePrev->next`, lalu mendealokasi node terakhir. `delAfter` melewati node `nodePrev->next` dengan `nodePrev->next = nodeHapus->next`, lalu mendealokasinya.
- `printList` menelusuri list dari `first` hingga `Nil` sambil mencetak data tiap node. `nbList` menghitung jumlah node dengan penelusuran yang sama.
- `deleteList` menelusuri list dan mendealokasi setiap node, lalu mengembalikan `first` menjadi `Nil`.
- Catatan: pada `delLast` untuk kasus list hanya berisi satu node, `first` sebaiknya diset `Nil` setelah node didealokasi agar tidak menjadi *dangling pointer*. Pada `main.cpp` di bawah kasus ini tidak terjadi sehingga program tetap berjalan benar.

### 3. Program main.cpp

```C++
#include "list.h"

#include<iostream>
using namespace std;

int main(){
    LinkedList List;
    address nodeA, nodeB, nodeC, nodeD, nodeE = Nil;
    createList(List);

    dataMahasiswa mhs;

    nodeA = alokasi("Dhimas", "2311102151", 20);
    nodeB = alokasi("Arvin", "2211110014", 21);
    nodeC = alokasi("Rizal", "2311110029", 20);
    nodeD = alokasi("Satrio", "2211102173", 21);
    nodeE = alokasi("Joshua", "2311102133", 21);

    insertFirst(List, nodeA);
    insertLast(List, nodeB);
    insertAfter(List, nodeC, nodeA);
    insertAfter(List, nodeD, nodeC);
    insertLast(List, nodeE);

    cout << "--- ISI LIST SETELAH DILAKUKAN INSERT ---" << endl;
    printList(List);
    cout << "jumlah node : " << nbList(List) << endl;
    cout << endl;

    delFirst(List);
    delLast(List);
    delAfter(List, nodeD, nodeC);

    cout << "--- ISI LIST SETELAH DILAKUKAN DELETE ---" << endl;
    printList(List);
    cout << "jumlah node : " << nbList(List) << endl;
    cout << endl;

    deleteList(List);
    cout << "--- ISI LIST SETELAH DILAKUKAN HAPUS LIST ---" << endl;
    printList(List);
    cout << "jumlah node : " << nbList(List) << endl;
    cout << endl;

    return 0;
}
```
**Penjelasan:** Ini adalah *driver* yang memakai ADT. Program membuat list kosong, mengalokasikan lima node (Dhimas, Arvin, Rizal, Satrio, Joshua), lalu menyisipkannya secara bertahap:
- `insertFirst(A)` menghasilkan **A**; `insertLast(B)` menghasilkan **A, B**; `insertAfter(C, A)` menghasilkan **A, C, B**; `insertAfter(D, C)` menghasilkan **A, C, D, B**; `insertLast(E)` menghasilkan **A, C, D, B, E**. Jadi urutan tampil: Dhimas, Rizal, Satrio, Arvin, Joshua dengan jumlah node 5.
- `delFirst` menghapus Dhimas, `delLast` menghapus Joshua, lalu `delAfter(C)` menghapus Satrio (node setelah Rizal). Sisa list: Rizal, Arvin dengan jumlah node 2.
- `deleteList` menghapus seluruh node sehingga `printList` menampilkan "List kosong." dan jumlah node 0.
- Kompilasi harus menyertakan kedua file `.cpp`: `g++ main.cpp list.cpp -o program`.

## Unguided

### 1. Membuat ADT Singly Linked List dan menyisipkan data dengan insertFirst

```C++
/* file : Singlylist.h */
#ifndef SINGLYLIST_H_INCLUDED
#define SINGLYLIST_H_INCLUDED

#include <iostream>
#include <cstddef>
using namespace std;

#define Nil NULL

typedef int infotype;
typedef struct ElmList *address;

struct ElmList {
    infotype info;
    address next;
};

struct List {
    address first;
};

void createList(List &L);

address alokasi(infotype x);

void dealokasi(address &P);

void printInfo(List L);

void insertFirst(List &L, address P);

#endif
```
```C++
/* file : Singlylist.cpp */
#include "Singlylist.h"

void createList(List &L) {
    L.first = Nil;
}

address alokasi(infotype x) {
    address P = new ElmList;
    P->info = x;
    P->next = Nil;
    return P;
}

void dealokasi(address &P) {
    delete P;
    P = Nil;
}

void printInfo(List L) {
    address P = L.first;
    while (P != Nil) {
        cout << P->info << " ";
        P = P->next;
    }
    cout << endl;
}

void insertFirst(List &L, address P) {
    P->next = L.first;
    L.first = P;
}
```
```C++
/* file : main.cpp */
#include "Singlylist.h"

int main(){
    List L;
    address P1, P2, P3, P4, P5 = Nil;
    createList(L);

    P1 = alokasi(2);
    insertFirst(L,P1);

    P2 = alokasi(0);
    insertFirst(L,P2);

    P3 = alokasi(8);
    insertFirst(L,P3);

    P4 = alokasi(12);
    insertFirst(L,P4);

    P5 = alokasi(9);
    insertFirst(L,P5);

    printInfo(L);
    return 0;
}
```
### Output Unguided 1 :

##### Output 1
![Output 1](https://github.com/HaidarZackk/Struktur_Data_Modul04_Haidar_Zacky/blob/main/soal_1/Output-Unguided1.png)

**Penjelasan:**
- `Singlylist.h` ditulis mengikuti spesifikasi pada soal: `infotype` bertipe `int`, `address` berupa pointer ke `ElmList`, `ElmList` berisi `info` dan `next`, serta `List` berisi `first`. Prosedur dan fungsinya persis lima buah seperti di soal, yaitu `createList`, `alokasi`, `dealokasi`, `printInfo`, dan `insertFirst`. Gaya komentar I.S./F.S. mengikuti contoh `list.h` pada modul.
- Pada spesifikasi, `dealokasi` bersifat *input/output* sehingga `P` dikirim by reference (`address &P`), sedangkan pada `insertFirst` hanya `L` yang *input/output* dan `P` berstatus *input* sehingga `P` dikirim by value (`address P`).
- Spesifikasi di soal menulis `CreateList`, sedangkan `main.cpp` di soal memanggil `createList`. Karena C++ membedakan huruf besar dan kecil, nama yang dipakai adalah `createList` agar sesuai dengan `main.cpp` soal.
- `main.cpp` sama dengan program utama di soal (hanya ditambah titik koma pada `printInfo(L);`). Karena `insertFirst` selalu menyisipkan di depan, data yang dimasukkan berurutan 2, 0, 8, 12, 9 terbaca terbalik menjadi **9 12 8 0 2**, sesuai gambar list pada soal.
- Kompilasi: `g++ main.cpp Singlylist.cpp -o singlylist`.

### 2. Dari soal Latihan pertama, lakukan penghapusan node 9 menggunakan deleteFirst(), node 2 menggunakan deleteLast(), dan node 8 menggunakan deleteAfter(). Kemudian tampilkan jumlah node yang tersimpan menggunakan nbList() dan lakukan penghapusan seluruh node menggunakan deleteList(). 

```C++
/* file : Singlylist.h */
#ifndef SINGLYLIST_H_INCLUDED
#define SINGLYLIST_H_INCLUDED

#include <iostream>
#include <cstddef>
using namespace std;

#define Nil NULL

typedef int infotype;
typedef struct ElmList *address;

struct ElmList {
    infotype info;
    address next;
};

struct List {
    address first;
};

void createList(List &L);

address alokasi(infotype x);

void dealokasi(address &P);

void insertFirst(List &L, address P);

void deleteFirst(List &L, address &P);

void deleteLast(List &L, address &P);

void deleteAfter(address Prec, address &P);

void printInfo(List L);

int nbList(List L);

void deleteList(List &L);

#endif
```
```C++
/* file : Singlylist.cpp */
#include "Singlylist.h"

void createList(List &L) {
    L.first = Nil;
}

address alokasi(infotype x) {
    address P = new ElmList;
    P->info = x;
    P->next = Nil;
    return P;
}

void dealokasi(address &P) {
    delete P;
    P = Nil;
}

void insertFirst(List &L, address P) {
    P->next = L.first;
    L.first = P;
}

void deleteFirst(List &L, address &P) {
    if (L.first == Nil) {
        P = Nil;
        return;
    }
    P = L.first;
    L.first = L.first->next;
    P->next = Nil;
    dealokasi(P);
}

void deleteLast(List &L, address &P) {
    if (L.first == Nil) {
        P = Nil;
        return;
    }
    if (L.first->next == Nil) {
        P = L.first;
        L.first = Nil;
    } else {
        address Q = L.first;
        while (Q->next->next != Nil) {
            Q = Q->next;
        }
        P = Q->next;
        Q->next = Nil;
    }
    dealokasi(P);
}

void deleteAfter(address Prec, address &P) {
    if (Prec == Nil || Prec->next == Nil) {
        P = Nil;
        return;
    }
    P = Prec->next;
    Prec->next = P->next;
    P->next = Nil;
    dealokasi(P);
}

void printInfo(List L) {
    address P = L.first;
    while (P != Nil) {
        cout << P->info << " ";
        P = P->next;
    }
    cout << endl;
}

int nbList(List L) {
    int jumlah = 0;
    address P = L.first;
    while (P != Nil) {
        jumlah++;
        P = P->next;
    }
    return jumlah;
}

void deleteList(List &L) {
    address P;
    while (L.first != Nil) {
        deleteFirst(L, P);
    }
}
```
```C++
/* file : main.cpp */
#include "Singlylist.h"

int main(){
    List L;
    address P1, P2, P3, P4, P5 = Nil;
    address hapus = Nil;
    createList(L);

    P1 = alokasi(2);
    insertFirst(L,P1);

    P2 = alokasi(0);
    insertFirst(L,P2);

    P3 = alokasi(8);
    insertFirst(L,P3);

    P4 = alokasi(12);
    insertFirst(L,P4);

    P5 = alokasi(9);
    insertFirst(L,P5);

    deleteFirst(L, hapus);      // hapus node 9
    deleteLast(L, hapus);       // hapus node 2
    deleteAfter(P4, hapus);     // hapus node 8 (setelah node 12)

    printInfo(L);
    cout << "Jumlah node : " << nbList(L) << endl;
    cout << endl;

    deleteList(L);
    cout << "- List Berhasil Terhapus -" << endl;
    cout << "Jumlah node : " << nbList(L) << endl;
    return 0;
}
```
### Output Unguided 2 :

##### Output 2
![Output 2](https://github.com/HaidarZackk/Struktur_Data_Modul04_Haidar_Zacky/blob/main/soal_2/Output-Unguided2.png)

**Penjelasan:**
- Bagian atas `main.cpp` sama dengan Latihan 1, sehingga list awal adalah 9 -> 12 → 8 -> 0 -> 2.
- `deleteFirst` memindahkan `first` ke node 12 lalu mendealokasi node 9. List menjadi 12 -> 8 -> 0 -> 2.
- `deleteLast` mencari node sebelum terakhir (`Q->next->next == Nil`), memutus `Q->next`, lalu mendealokasi node 2. List menjadi 12 -> 8 -> 0. Bila list hanya berisi satu node, `first` dikembalikan menjadi `Nil`.
- `deleteAfter(P4, hapus)` dengan `P4` menunjuk node 12 menghapus node setelahnya, yaitu 8, dengan cara `Prec->next = P->next`. List menjadi 12 -> 0.
- `nbList` menghitung node dengan penelusuran sehingga menghasilkan 2. `deleteList` memanggil `deleteFirst` berulang sampai `first` bernilai `Nil`, sehingga seluruh memori dibebaskan dan `nbList` menghasilkan 0.
- Output program: `12 0`, `Jumlah node : 2`, baris kosong, `- List Berhasil Terhapus -`, `Jumlah node : 0`, sama dengan output yang diharapkan pada soal.

## Kesimpulan

**Kesimpulan modul.** Modul ini memperkenalkan singly linked list, yaitu struktur data berupa rangkaian node yang dihubungkan oleh pointer `next` dalam satu arah dan diakses melalui pointer `first`. Berbeda dengan array yang ukurannya tetap, linked list dialokasikan secara dinamis dengan `new` dan dibebaskan dengan `delete`, sehingga dapat bertambah dan berkurang sesuai kebutuhan. Operasi dasarnya (create, alokasi/dealokasi, insert, delete, view, dan hitung jumlah node) disusun sebagai primitif dalam ADT yang dipisah menjadi header (`.h`), implementasi (`.cpp`), dan driver (`main.cpp`), melanjutkan pola ADT dari modul sebelumnya.

**Kesimpulan Guided.** Pada bagian Guided, ADT linked list dipraktikkan dengan data majemuk mahasiswa (nama, NIM, umur). Program memperlihatkan seluruh operasi penyisipan (`insertFirst`, `insertAfter`, `insertLast`), penghapusan (`delFirst`, `delLast`, `delAfter`), penelusuran (`printList`, `nbList`), dan penghapusan seluruh list (`deleteList`). Dari alur `main.cpp` terlihat bahwa urutan list berubah sesuai posisi penyisipan, dan bahwa setiap penghapusan harus memutus dan menyambung ulang pointer `next` dengan benar agar list tidak terputus serta memori dikembalikan ke sistem. Selain itu, kasus khusus seperti list kosong dan list satu node perlu diperhatikan agar tidak terjadi kesalahan pointer.

**Kesimpulan Unguided.** Pada bagian Unguided, Latihan 1 membangun ADT singly linked list dengan data bertipe `int` dan membuktikan bahwa `insertFirst` menyusun data dalam urutan terbalik dari urutan pemasukan, sehingga memasukkan 2, 0, 8, 12, 9 menghasilkan list 9 12 8 0 2. Latihan 2 menambahkan `deleteFirst`, `deleteLast`, `deleteAfter`, `nbList`, dan `deleteList`; hasilnya list menyisakan 12 dan 0 dengan jumlah node 2, lalu menjadi kosong dengan jumlah node 0 setelah `deleteList`. Kedua latihan menunjukkan bahwa kunci operasi linked list ada pada pengaturan pointer yang tepat dan pengelolaan memori yang disiplin.

**Kesimpulan keseluruhan.** Secara keseluruhan, modul ini menunjukkan bahwa singly linked list adalah struktur data dinamis yang efisien untuk penyisipan dan penghapusan, terutama di awal list, dan menjadi dasar bagi struktur lanjutan seperti doubly linked list, circular linked list, stack, dan queue. Penguasaan pointer, alokasi dan dealokasi memori, serta pemisahan ADT ke dalam header, implementasi, dan driver sangat penting agar program terstruktur dan bebas kebocoran memori. Perlu diingat pula bahwa akses elemen pada linked list bersifat sekuensial, sehingga pada praktiknya pilihan antara linked list dan array perlu disesuaikan dengan jenis operasi yang paling sering dilakukan.

## Referensi

[1] Weiss, M. A. (2014). *Data Structures and Algorithm Analysis in C++* (4th ed.). Boston: Pearson. (Bab 3: Lists, Stacks, and Queues, termasuk Abstract Data Types dan Simple Linked Lists).
<br>[2] Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2022). *Introduction to Algorithms* (4th ed.). Cambridge, MA: MIT Press.
<br>[3] Stroustrup, B. (2022). *A Tour of C++* (3rd ed.). Boston: Addison-Wesley.
<br>[4] Sonntag, B., & Colnet, D. (2023). *RIP Linked List: Empirical Study to Discourage You from Using Linked Lists Any Further*. arXiv:2306.06942. https://arxiv.org/abs/2306.06942
