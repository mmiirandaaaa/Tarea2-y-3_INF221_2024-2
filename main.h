#ifndef MAIN_H
#define MAIN_H
#include <string>

// Tablas de costos
extern int CostoSub[26][26];
extern int CostoIns[26];
extern int CostoDel[26];
extern int CostoTrans[26][26];

// Función que lee los archivos con los costos y los asigna a las matrices
void setup();

int costo_sub(char a, char b);
int costo_ins(char b);
int costo_del(char a);
int costo_trans(char a, char b);

extern std::string a,b;
extern long long len_A, len_B;

#endif