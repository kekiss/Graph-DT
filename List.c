// Kara Ekiss
// kekiss
// cs101
// pa2
// List.c

#include <stdlib.h>
#include <stdio.h>
#include "List.h"

// Structs

// NodeObject
typedef struct NodeObject{
   int data;
   struct NodeObject* prev;
   struct NodeObject* next;
}NodeObject;

//Node    
typedef NodeObject* Node;

//List Object
typedef struct ListObject{
   Node cursor;
   Node first;
   Node last;
   int height;
   int index;
} ListObject;

// Constructors
 
// creates new empty list
List newList(void){ 
   List L = malloc(sizeof(ListObject));
   L->cursor = NULL; 
   L->first = NULL; 
   L->last = NULL; 
   L->height = 0; 
   L->index = -1;
   return L;
}

// creates new node
Node newNode(int data){
   Node N = malloc(sizeof(NodeObject));
   N->next = NULL;
   N->prev = NULL;
   N->data = data;
   return(N);
}

//frees list
void freeList(List* pL){
   if(pL == NULL || *pL == NULL){ 
      return;
   }
   while(length(*pL) != 0){
      deleteFront(*pL);
   }
   free(*pL);
   *pL = NULL;
}

//frees node
void freeNode (Node* pN){
   if(*pN != NULL && pN != NULL){
      free(*pN);
      *pN = NULL;
   } 
}

// Access Functions //////////////////////////////////////////////////////////////////
   
int front(List L){  // returns first element of the list, assuming length() > 0
   if(L == NULL ){
      printf("List Error: front() called on a NULL List\n");
      exit(1);
   }else if (L->height == 0){
      printf("List Error: front() called on a List of length 0\n");
      exit(1);
   }else{
      return L->first->data;
   }
}
   
int back(List L){  // returns last element of the list, assuming length() > 0
   if (L == NULL) {
      printf("List Error: back() called on a NULL List\n");
      exit(1);
   }else if (L->height == 0){
      printf("List Error: back() called on a List of length 0\n");
      exit(1);
   }else{
      return L->last->data;
   }
}

int getIndex(List L){  // returns index of cursor element, returns -1 if cursor is undefined 
   if (L == NULL){
      printf("List Error: getIndex() called on a NULL list\n");
      exit(1);
   }
   return L->index;
}

int getElement(List L){  //returns cursor element
   if(L == NULL){
      printf("List Error: getElement() called on a NULL list\n");
      exit(1);
   }else if (L->cursor == NULL){
      printf("List Error: getElement() called on NULL cursor\n");
      exit(1);
   }else if(L->height > 0 && L->index >= 0){ 
      return L->cursor->data;
   }
   return -1;
}

int length(List L) {  //returns length
   if(L == NULL){
      printf("List Error: length() called on a NULL list\n");
      exit(1);
   }
   return L->height; 
}

int equals(List A, List B){  //compares to lists
   if(A==NULL || B == NULL){
      printf("List Error: length() called on a NULL list\n");
      exit(1);
   }
   Node R = A->first;
   Node L = B->first;
   while(R != NULL && L != NULL){
      if(L->data != R->data){
         return 0;
      }
      R = R->next;
      L = L->next;
   }
   if (R != NULL && R != NULL){
      return 0;
   }
   return 1;
}


// Manipulation Procedures ///////////////////////////////////////////////////////////

void clear(List L){  // resets List to empty
   if(L == NULL){
      printf("List Error: length() called on a NULL list\n");
      exit(1);
   }
   Node first = L->first;
   while(first != NULL){    //move through and free
      Node t = first->next;
      free(first);
      first = t;
   }
   L->first = NULL;
   L->last = NULL;
   L->index = -1;
   L->cursor = NULL;
   L->height = 0;
}

void moveTo(List L, int i){ //moves cursor to i
   if(L == NULL){
      printf("List Error: moveTo called on a NULL list\n");
      exit(1);
   }
   L->cursor = L->first;
   for (L->index = 0; L->index < i; L->index++) { //as index moves to i
	L->cursor = L->cursor->next;  // cursor moves with it
  }
}

void movePrev(List L){ // moves cursor forward
   if(L == NULL){
      printf("List Error: movePrev() called on a NULL List\n");
      exit(1);
   }
   else if(L->index > 0 && L->index <= L->height-1){
      L->cursor = L->cursor->prev;
      L->index--;
   }else{
      L->cursor = NULL;
      L->index = -1;
   }
}

void moveNext(List L){  // moves cursor back
   if(L == NULL){
      printf("List Error: moveNext() called on a NULL List\n");
      exit(1);
   }
   else if(L->index >= 0 && L->index < L->height-1){
      L->cursor = L->cursor->next;
      L->index++;
   }else{
      L->cursor = NULL;
      L->index = -1;
   }
}

void prepend(List L, int data){  //inserts element at front of list
   if(L == NULL){
      printf("List Error: prepend() called on a NULL List\n");
      exit(1);
   }
   else if(L->height == 0){
      Node N = newNode(data);
      L->first = L->last = N;
      L->height++;
   }else{
      Node N = newNode(data);
      N->next = L->first;
      L->first->prev = N;
      L->first = N;
      L->height++;
   }
   if(L->index != -1){
      L->index++;
      L->height++;
   }
//   L->height++;
}

void append(List L, int data){ //insert element at back of list
   if(L == NULL){
      printf("List Error: append() called on a NULL List\n");
      exit(1);
   }
   else if(L->height == 0){
      Node N = newNode(data);
      L->first = L->last = N;
   }else{
      Node N = newNode(data);
      N->prev = L->last;
      L->last->next = N;
      L->last = N;
   }
   L->height++;      
}

void insertBefore(List L, int data){ // inserts element before cursor
   if(L == NULL){
      printf("List Error: insertBefore() called on a NULL List\n");
      exit(1);
   }
   if (L->height == 0){
      printf("List Error: insertBefore() called on empty List\n");
      exit(1);
   }
   if (L->index < 0){
      printf("List Error: insertBefore() called on an index less than zero\n");
      exit(1);
   }   
   L->height++;
   Node N = newNode(data);
   N->prev = L->cursor->prev;
   N->next = L->cursor;
   if(N->prev != NULL){
      L->cursor->prev->next = N;         
   }else{
      L->first = N;
   }
   L->cursor->prev = N;
   L->index++;
}

void insertAfter(List L, int data){ // inserts element after cursor
   if(L == NULL){
      printf("List Error: insertBefore() called on a NULL List\n");
      exit(1);
   }
   if (L->height == 0){
      printf("List Error: insertBefore() called on empty List\n");
      exit(1);
   }
   if (L->index < 0){
      printf("List Error: insertBefore() called on an index less than zero\n");
      exit(1);
   }
   L->height++;
   Node N = newNode(data);
   N->prev = L->cursor;
   N->next = L->cursor->next;
   if (N->next != NULL){
      L->cursor->next->prev = N;
   }else{
      L->last = N;
   }
   L->cursor->next = N;   
}

void deleteFront(List L){ // deletes first element
   if(L == NULL){
      printf("List Error: deleteFront) called on a NULL List\n");
      exit(1);
   }
   if (L->height == 0){
      printf("List Error: deleteFront() called on empty List\n");
      exit(1);
   }
   else if(L->height == 1){
      Node M = L->first;
      L->first = NULL;
      freeNode(&M);
   }else{
      Node M = L->first;
      Node o = L->first->next;
      o->prev = NULL;
      L->first = o;
      if(L->index != -1){
         L->index--;
      }
      if(L->cursor == M){
         moveTo(L, -1);
      }
      freeNode(&M);   
   }
   L->height--;
}

void deleteBack(List L){ // deletes last element
   if(L == NULL){
      printf("List Error: insertBefore() called on a NULL List\n");
      exit(1);
   }
   if (L->height == 0){
      printf("List Error: insertBefore() called on empty List\n");
      exit(1);
   }else if(L->height == 1){
      Node M = L->last;
      L->last = NULL;
      freeNode(&M);
   }else{
      Node M = L->last;
      Node o = L->last->prev;
      o->next = NULL;
      L->last = o;
      if(L->cursor == M){
         moveTo(L, -1);
      }
      freeNode(&M);
   }    
   L->height--;
}

void delete(List L){ // deletes cursor element
   if(L == NULL){
      printf("List Error: delete() called on a NULL List\n");
      exit(1);
   }
   if (L->height == 0){
      printf("List Error: delete() called on empty List\n");
      exit(1);
   }
   if (L->index < 0){
      printf("List Error: delete() called on an index less than zero\n");
      exit(1);
   }
   if(L->cursor == L->first){
      deleteFront(L);
   }else if(L->cursor == L->last){
      deleteBack(L);
   }
   if(L->index >0 && L->height > 0){
      L->height--;
      Node o = L->cursor;
      L->cursor->next->prev = L->cursor->prev;
      L->cursor->prev->next = L->cursor->next;
      L->cursor = NULL;
      L->index = -1;
      free(o);
   }
}


// Other Functions ///////////////////////////////////////////////////////////////////

void printList(FILE* out, List L){  //prints list
   if(L == NULL){
      printf("ListError: printList() called on a NULL List\n");
      exit(1);
   }
   Node N = NULL;
   for(N = L->first; N != NULL; N =N->next){
      fprintf(out, "%d ", N->data);
   }
}

List copyList(List L){  //makes a copy of the list
   if(L == NULL){
      printf("ListError: printList() called on a NULL List\n");
      exit(1);
   }
   List dup = newList();
   Node N;
   for(N = L->first; N != NULL; N = N->next){
      append(dup, N->data);
   }
   return dup;
}

        
