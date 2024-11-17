#include "main.h"
#include "dp.h"
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int dp(){
	// Creamos la tabla para el DP
	vector<vector<int>> dp(len_A + 1, vector<int>(len_B + 1, 0));

	// Hacemos los casos base
	dp[0][0] = 0;
	for(int i=1; i < len_A + 1; i++){
		dp[i][0] = dp[i-1][0] + costo_del(a[i-1]); // El string b es vacío --> hay que eliminar en a
	}
	for(int j=1; j < len_B + 1; j++){
		dp[0][j] = dp[0][j-1] + costo_ins(b[j-1]); // El string a es vacío --> hay que insertar en a
	}

	// Llenamos la tabla
	for(int i=1; i < len_A + 1; i++){
		for(int j=1; j < len_B + 1; j++){
			dp[i][j] = min(
					   	dp[i-1][j-1] + costo_sub(a[i-1],b[j-1]), // Substitución
					   min(
					   	dp[i][j-1] + costo_ins(b[j-1]), // Inserción
						dp[i-1][j] + costo_del(a[i-1]) // Eliminación
					   ));
			if(i>1 && j>1 && a[i-1] == b[j-2] && a[i-2] == b[j-1]){ // Se puede transponer
				dp[i][j] = min(
							dp[i][j], // Lo que ya habíamos calculado (min(sub,ins,del))
							dp[i-2][j-2] + costo_trans(a[i-1], a[i-2]) // Transposición
						  );
			}
		}
	}

	return dp[len_A][len_B];
}