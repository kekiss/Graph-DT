/* Kara Ekiss
 * cs101
 * pa4
 * Graph.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

#define WHITE 1
#define GRAY 2
#define BLACK 3
#define INF -1
#define NIL 0

//graph struct
typedef struct GraphObject{
   int order, size, source;
   //order is number of verts
   //size is number of edges
   int *color, *parent, *distance;
   List *neighbors;
}GraphObject;

//set up this function
static void orderList(List L, int v);

//returns a Graph pointing to a Graph Object
//with parameter n vertices and 0 edges
Graph newGraph(int n){
   if(n<1){
      printf("Invalid number of vertices.\n");
      exit(1);
   }else{
      Graph new = malloc(sizeof(struct GraphObject));
      new->neighbors = malloc((n+1)*sizeof(List));
      new->color = malloc((n+1)*sizeof(int));
      new->parent = malloc((n+1)*sizeof(int));
      new->distance = malloc((n+1)*sizeof(int));

      new->source = NIL;
      new->order = n; //number of vertices
      new->size = 0; //no edges yet
      new->neighbors[0] = NULL;
      int i;
      for(i = 0; i < n + 1; i++){
         new->neighbors[i] = newList();
         new->color[i] = WHITE;
         new->parent[i] = NIL;
         new->distance[i] = INF; //0 edges means 0 edge length
      }return new;
   }return NULL;
}

//free memory and pointers associated with Graph
void freeGraph(Graph* pG){
   int i;
   for(i = 1; i <= getOrder(*pG); i++){
      freeList(&(*pG)->neighbors[i]);
   }
   free((*pG)->neighbors);
   (*pG)->neighbors = NULL;

   free((*pG)->color);
   (*pG)->color = NULL;

   free((*pG)->parent);
   (*pG)->parent = NULL;

   free((*pG)->distance);   
   (*pG)->distance = NULL;

   free(*pG);
   *pG = NULL;
   return;
}

//get number of edges
int getOrder(Graph G){
   if(G == NULL){
      printf("Graph pointer is NULL in getOrder\n");
      exit(1);
   }else{
      return G->order;
   }
}

//get number of vertices
int getSize(Graph G){
   if(G == NULL){
      printf("Graph pointer is NULL in getSize\n");
      exit(1);
   }else{
      return G->size;
   }
}

//returns source vertex
int getSource(Graph G){
   if(G == NULL){
      printf("Graph pointer is NULL in getSource\n");
      exit(1);
   }else{
      return G->source;
   }
}

//returns parent vertex of u vertex
int getParent(Graph G, int u){
   if(G == NULL){
      printf("Graph pointer is NULL in getParent\n");
      exit(1);
   }else if(u <= 0 || u > getOrder(G)){
      printf("Invalid indices\n");
      exit(1);
   }
   return (G->parent[u]);
}

//returns distance between source and vertex
int getDist(Graph G, int u){
   if(G == NULL){
      printf("Graph pointer is NULL in getDist\n");
      exit(1);
   }else if(u <= 0 || u > getOrder(G)){
      printf("Invalid indices\n");
      exit(1);
   }
   return (G->distance[u]);
}

//calculates the quickest path between the vertex 
//and source, appends that vertice to List L
void getPath(List L, Graph G, int u){
   if(getSource(G) == NIL){
      printf("NIL source\n");
      exit(1);
   }
   if(u < 1 || getOrder(G) < u){
      printf("u parameter is invalid\n");
      exit(1);
   }
   if(G->source == u){
      append(L, u);
   }
   else if(G->parent[u] != NIL){
      getPath(L, G, G->parent[u]);
      append(L, u);
   }
}

//Manipulation procedures//

//clears edges
void makeNull(Graph G){
   if(G == NULL){
      printf("Graph pointer is NULL in makeNull\n");
      exit(1);
   }
   else{ //iteratively clear
      int i;
      for(i = 1; i <= getOrder(G); i++){
         clear(G->neighbors[i]);
      }
      G->size = 0;
   }
}

//creates an edge
void addEdge(Graph G, int u, int v){
   if(G == NULL){
      printf("Graph pointer is NULL in addEdge\n");
      exit(1);
   }
   if(u < 1 || getOrder(G) < u || v < 1 || getOrder(G) < v){
      printf("Invalid vertex numbers");
      exit(1);
   }
   //insert v into U
   List U = G->neighbors[u];
   orderList(U, v);
   //insert u into V
   List V = G->neighbors[v];
   orderList(V, u);
   G->size++; ///to account for new element
}

//adds an arc
void addArc(Graph G, int u, int v){
   if(G == NULL){
      printf("Graph pointer is NULL in addArc\n");
      exit(1);
   }
   if(u < 1 || getOrder(G) < u || v < 1 || getOrder(G) < v){
      printf("Invalid vertex numbers");
      exit(1);
   }
   List U = G->neighbors[u];
   orderList(U, v);
}

//runs BFS algorithm based on textbook's pseudocode
void BFS(Graph G, int s){
   if(G == NULL){
      printf("Graph pointer is NULL in BFS\n");
      exit(1);
   }
   G->source = s;
   int i;
   for(i = 1; i <= getOrder(G); i++){
      G->distance[i] = INF;
      G->parent[i] = NIL;
      G->color[i] = WHITE;
   }
   G->distance[s] = 0;
   G->parent[s] = NIL;
   G->color[s] = GRAY;
   List M = newList();
   prepend(M, s);
   while(length(M) != 0){
      int j = back(M);
      deleteBack(M); 
      List neigh = G->neighbors[j];
      for(moveTo(neigh, 0); getIndex(neigh) != -1; moveNext(neigh)){
         int vertex = getElement(neigh);
         if(G->color[vertex] == WHITE){
            G->color[vertex] = GRAY;
            G->distance[vertex] = G->distance[j] + 1;
            G->parent[vertex] = j;
            prepend(M, vertex);
         }
      }G->color[j] = BLACK;
   }freeList(&M);
}

//prints adjacency list
void printGraph(FILE* out, Graph G){
   if(out == NULL || G == NULL){
      printf("Can't print NULL things");
      exit(1);
   }
   int i;
   for(i = 1; i <= getOrder(G); i++){
      fprintf(out, "%d: ", i);
      printList(out, G->neighbors[i]);
      fprintf(out, "\n");
   }
}

//puts v into List L in sorted order
//function created to make addEdge and addArc shorter
static void orderList(List L, int v){
   if(length(L) == 0){
      append(L, v); //just add v to U
      return;
   }
   for(moveTo(L, 0); getIndex(L) != -1; moveNext(L)){
      if(v < getElement(L)){
         insertBefore(L, v);
         break;
      }
   }
   if(getIndex(L) == -1){ //if index is not in use
      append(L, v);
   }
}
