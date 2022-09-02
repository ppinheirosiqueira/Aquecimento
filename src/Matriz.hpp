#ifndef MATRIZ_HPP
#define MATRIZ_HPP
#include <time.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Hash4key.hpp"
using namespace std;

void criarArquivo();
void lerArquivoCoordenadas(HashTableFechada *h);
int lerArquivo(int iIni, int iFin, int jIni, int jFin, vector<vector<int>>* matriz);
void imprimeMatriz(vector<vector<int>> matriz, int iTam, int jTam);
vector<vector<int>> multiplicaMatriz(int tamI, int tamJ, vector<vector<int>> matriz1,  vector<vector<int>> matriz2);
vector<int> lerCoordenadas();
void calcularResultante(int iInt, int jInt, vector<int> coordenadas, HashTableFechada *h);

#endif