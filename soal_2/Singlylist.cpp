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