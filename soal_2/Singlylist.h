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