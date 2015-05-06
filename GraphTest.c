//Kara Ekiss
//kekiss
//GraphTest.c
//for Graph.c testing purposes
//Tantalo's GraphClient plus some
//of my own tests

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(int argc, char* argv[]){
   int i, s, d;
   int max, min;
   int n = 35;

   List C = newList();
   List P = newList();
   List E = newList();
   Graph G = NULL;
   Graph G2 = NULL;

   G = newGraph(n);
   for(i = 1; i < n; i++){
      if(i%7 != 0){
         addEdge(G, i, i+1);
      }
      if(i <= 28){
         addEdge(G, i, i+7);
      }
   }

   addEdge(G, 9, 31);
   addEdge(G, 17, 13);
   addEdge(G, 14, 33);

   // Print adjacency list representation of G
   printGraph(stdout, G);

   // Calculate the eccentricity of each vertex 
   for(s=1; s<=n; s++){
      BFS(G, s);
      max = getDist(G, 1);
      for(i=2; i<=n; i++){
         d = getDist(G, i);
         max = ( max<d ? d : max );
      }
      append(E, max);
   }

   // Determine the Radius and Diameter of G, as well as the Central and 
   // Peripheral vertices.
   append(C, 1);
   append(P, 1);
   min = max = front(E);
   moveTo(E,0);
   moveNext(E);
   for(i=2; i<=n; i++){
      d = getElement(E);
      if( d==min ){
         append(C, i);
      }else if( d<min ){
         min = d;
         clear(C);
         append(C, i);
      }
      if( d==max ){
         append(P, i);
      }else if( d>max ){
         max = d;
         clear(P);
         append(P, i);
      }
      moveNext(E);
   }

   //my tests
   addEdge(G2, 1 ,2);
   BFS(G2, 2);
   makeNull(G2);
   addArc(G2, 1, 2);
   getPath(C, G2, d);
   //end my tests

   // Print results 
   printf("\n");
   printf("Radius = %d\n", min);
   printf("Central vert%s: ", length(C)==1?"ex":"ices");
   printList(stdout, C);
   printf("\n");
   printf("Diameter = %d\n", max);
   printf("Peripheral vert%s: ", length(P)==1?"ex":"ices");
   printList(stdout, P);
   printf("\n");

   //my test prints
   printf("\n");
   printf("shortest d%-%d path: ", getSource(G), d);
   printf("\n");
   //end my test prints

   // Free objects 
   freeList(&C);
   freeList(&P);
   freeList(&E);
   freeGraph(&G);
   freeGraph(&G);

   return(0);
}
