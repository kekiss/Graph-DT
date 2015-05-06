// Kara Ekiss
// kekiss
// cs101
// pa2
// List.h

#ifndef __LIST_H__
#define __LIST_H__

#include <stdlib.h>
#include <stdio.h>

typedef struct ListObject* List;

//Constructors
List newList(void);
void freeList(List* pL);

//Access functions
int getIndex(List L);
int front(List L);
int back(List L);
int getElement(List L);
int length(List L);
int equals(List A, List B);

//Manipulation functions
void clear (List L);
void moveTo(List L, int i);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, int data);
void append(List L, int data);
void insertBefore(List L, int data);
void insertAfter(List L, int data);
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);

//Other
void printList (FILE* out, List L);
List copyList(List L);

#endif
