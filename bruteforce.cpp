#include "main.h"
#include "bruteforce.h"
#include <algorithm>
#include <climits>
using namespace std;

int distancia(int i, int j){
  //CASOS BASE
  if (i == -1 && j == -1) return 0;
  
  // a está vacío
  if(i == -1){
    // Costo de agregar todo lo que queda en b
    int costo = 0;
    for(int k = j; k >= 0; k--){
      costo += costo_ins(b[k]);
    }
    return costo;
  }

  // b está vacío
  if(j == -1){
    // costo de eliminar todo lo que hay en a
    int costo = 0;
    for(int k = i; k >= 0; k--){
      costo += costo_del(a[k]);
    }
    return costo;
  }

  // RECURSION
  
  // Si los caracteres son iguales pasamos a los siguientes (anteriores)
  if(version && a[i] == b[j]){ // versión optimizada
    return distancia(i-1, j-1);
  }

  // Si se puede hacer trasposición
  int trans;
  if(i > 1 && j > 1 && a[i] == b[j-1] && a[i-1] == b[j]){
    trans = costo_trans(a[i-1], a[i]) + distancia(i-2,j-2);
  }
  else {trans = INT_MAX;} // Si no se puede realizar la transposicion
  
  // Se retorna el mínimo de todos los casos
  return min(
            costo_sub(a[i], b[j]) + distancia(i-1, j-1), // Sustituir
         min(
            costo_ins(b[j]) + distancia(i, j-1), // Insertar
         min(
            costo_del(a[i]) + distancia(i-1, j), //Eliminar
            trans
         )));
}