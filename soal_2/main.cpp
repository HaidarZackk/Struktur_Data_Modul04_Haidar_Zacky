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