#include <iostream>
#include <fstream>
#include <chrono>

#include "main.h"
#include "dp.h"
#include "bruteforce.h"
using namespace std;

int CostoSub[26][26];
int CostoIns[26];
int CostoDel[26];
int CostoTrans[26][26];

// Función que lee los archivos con los costos y los asigna a las matrices
void setup(){
	ifstream arch_ins ("costo_ins.txt"), arch_del ("costo_del.txt"), arch_sub ("costo_sub.txt"), arch_trans ("costo_trans.txt");

    bool first = true;

    for (int i=0; i<26; i++){
        for (int j=0; j<26; j++){
            if (first){                 // Llena los vectores fila
                arch_ins >> CostoIns[j];
                arch_del >> CostoDel[j];
            }
            arch_sub >> CostoSub[i][j];    // Llena las matrices
            arch_trans >> CostoTrans[i][j];
        }
        first = false;
    }
    arch_del.close();arch_ins.close();arch_sub.close();arch_trans.close();
}

// Recibe los titulos de los archivos que contienen los strings (S1.txt, S2.txt) y recibe un título para ponerle al csv que genera
// Itera sobre los largos pasandole como indice final cada valor de largo en cada una de las iteraciones
// Ejecuta los códigos de bruteforce y bruteforce optimizado tomando los tiempos y los escribe en un csv de nombre "titulo"
void analizar_bf(string S1_txt, string S2_txt, string titulo){

  ifstream S1(S1_txt), S2(S2_txt);
  S1 >> a; S2 >> b;
  S1.close();S2.close();

  ofstream resultados(titulo);
  resultados << "TIEMPO_BF,TIEMPO_BF_OP,LEN_S1,LEN_S2\n";

  for(len_A = 0; len_A < 16; len_A++){
    for(len_B = len_A; len_B < 16; len_B++){

      chrono::time_point<chrono::high_resolution_clock> start, end;
      chrono::duration<long long, micro> delta;
      
      // BRUTEFORCE NO OPTIMIZADO
      version = false;
      start = chrono::high_resolution_clock::now();

      distancia(len_A-1, len_B-1);

      end = chrono::high_resolution_clock::now();
      delta = chrono::duration_cast<chrono::microseconds>(end-start);
      resultados << delta.count() << ",";

      // BRUTEFORCE OPTIMIZADO
      version = true;
      start = chrono::high_resolution_clock::now();

      distancia(len_A-1, len_B-1);

      end = chrono::high_resolution_clock::now();
      delta = chrono::duration_cast<chrono::microseconds>(end-start);
      resultados << delta.count() << ",";

      resultados << len_A << "," << len_B << "\n";
      
    }
  }
  resultados.close();
}

// Recibe los titulos de los archivos que contienen los strings (S1.txt, S2.txt) y recibe un título para ponerle al csv que genera
// Itera sobre los largos pasandole como indice final cada valor de largo en cada una de las iteraciones pero lo hace en pasos de potencias de 10 para disminuir la cantidad de casos que debe computar
// Ejecuta los códigos de bruteforce y bruteforce optimizado tomando los tiempos y los escribe en un csv de nombre "titulo"
void analizar_dp(string S1_txt, string S2_txt, string titulo){
   
  ifstream S1(S1_txt), S2(S2_txt);
  S1 >> a; S2 >> b;
  S1.close();S2.close();

  ofstream resultados(titulo);
  resultados << "TIEMPO_DP,LEN_S1,LEN_S2\n";

  for(len_A = 1; len_A < a.length(); len_A = len_A*10){
    for(len_B = len_A; len_B < b.length(); len_B = len_B*10){
      chrono::time_point<chrono::high_resolution_clock> start, end;
      chrono::duration<long long, micro> delta;
      
      start = chrono::high_resolution_clock::now();

      dp();

      end = chrono::high_resolution_clock::now();
      delta = chrono::duration_cast<chrono::microseconds>(end-start);
      resultados << delta.count() << ",";

      resultados << len_A << "," << len_B << "\n";
    }
  }
  resultados.close();
}


// Recibe los titulos de los archivos que contienen los strings (S1.txt, S2.txt) y recibe un título para ponerle al csv que genera
// Itera sobre los largos pasandole como indice final cada valor de largo en cada una de las iteraciones. Como el anterior lo hacía en pasos de potencias, se salta los casos pequeños. Esta función arregla eso y calclula los casos pequeños de uno en uno hasta 15
// Ejecuta los códigos de bruteforce y bruteforce optimizado tomando los tiempos y los escribe en un csv de nombre "titulo"
void analizar_dp_hasta_15(string S1_txt, string S2_txt, string titulo){
  ifstream S1(S1_txt), S2(S2_txt);
  S1 >> a; S2 >> b;
  S1.close();S2.close();

  ofstream resultados(titulo);
  resultados << "TIEMPO_DP,LEN_S1,LEN_S2\n";

  for(len_A = 0; len_A < 16; len_A++){
    for(len_B = len_A; len_B < 16; len_B++){

      chrono::time_point<chrono::high_resolution_clock> start, end;
      chrono::duration<long long, micro> delta;
      
      start = chrono::high_resolution_clock::now();

      dp();

      end = chrono::high_resolution_clock::now();
      delta = chrono::duration_cast<chrono::microseconds>(end-start);
      resultados << delta.count() << ",";

      resultados << len_A << "," << len_B << "\n";
    }
  }
  resultados.close();
}


int costo_sub(char a, char b){
  if(a==b) return 0;
  return CostoSub[a-97][b-97];
}

int costo_ins(char b){
  return CostoIns[b-97];
}

int costo_del(char a){
  return CostoDel[a-97];
}

int costo_trans(char a, char b){
  return CostoTrans[a-97][b-97];
}

string a,b;
long long len_A,len_B;
bool version;


int main(){

  setup();

  analizar_bf("S1.txt","S2.txt","bf_distintos.csv");
  analizar_bf("S1.txt","S1.txt","bf_iguales.csv");
  analizar_bf("S3.txt","S3.txt","bf_transposiciones.csv");
  analizar_bf("S1.txt","VACIA.txt","bf_vacia.csv");
  
  analizar_dp("S1.txt","S2.txt","dp_distintos.csv");
  analizar_dp("S1.txt","S2.txt","dp_iguales.csv");
  analizar_dp("S3.txt","S3.txt","dp_transposiciones.csv");
  analizar_dp("S1.txt","VACIA.txt","dp_vacia.csv");
    
  analizar_dp_hasta_15("S1.txt","S2.txt","dp_hasta15_distintos.csv");
  analizar_dp_hasta_15("S1.txt","S2.txt","dp_hasta15_iguales.csv");
  analizar_dp_hasta_15("S3.txt","S3.txt","dp_hasta15_transposiciones.csv");
  analizar_dp_hasta_15("S1.txt","VACIA.txt","dp_hasta15_vacia.csv");

	return 0;
}
