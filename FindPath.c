//Kara Ekiss
//kekiss
//FindPath.c


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Graph.h"

#define MAX_LEN 160

typedef char *string;

int main(int argc, char* argv[]){
   int verts, x, y, source, destination;
   //check usage
   if(argc != 3){
      printf("Must type three arguments\n");
      exit(1);
   }
   //open and check input file
   FILE *in = fopen(argv[1], "r");
   if(in == NULL){
      printf("Cannot open input file\n");
      exit(1);
   }
   //open and check output file
   FILE *out = fopen(argv[2], "w");
   if(out == NULL){
      printf("Cannot open output file\n");
      exit(1);
   }
   //create graph, fill it
   fscanf(in, "%d", &verts);
   Graph G = newGraph(verts);
   while(fscanf(in, "%d %d", &x, &y) == 2){
      if(x == 0 && y == 0){
         break;
      }
      addEdge(G, x, y);
   }
   //print graph
   printGraph(out, G);
   
   //print all paths
   List L = newList();
   while (fscanf(in, "%d %d", &source, &destination)){
      if(destination == 0 && source == 0){
         break;
      }
      BFS(G, source);
      getPath(L, G, destination);
      fprintf(out, "\nThe distance from %d to %d is ", source, destination);
      if(length(L) != 0){
         fprintf(out, "%d\n", getDist(G, destination));
         fprintf(out, "A shortest %d-%d path is: ", source, destination);
         printList(out, L);
         fprintf(out, "\n");
      }else{
         fprintf(out, "No %d-%d path exists\n", source, destination);
      }
      clear(L);
   } 
   fclose(in);
   fclose(out);

   freeList(&L);
   freeGraph(&G);
}
