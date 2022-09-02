#ifndef HASH4KEY_HPP
#define HASH4KEY_HPP
#include <vector>
#include <iostream>
#include <cstdlib>
using namespace std;

#define hash(v, M) ((v[0]+v[1]+v[2]+v[3]) % M)

typedef struct DataTable DataTable;
typedef struct HashTableFechada HashTableFechada;
typedef struct Block Block;
typedef struct Lista Lista;

struct DataTable{
	vector<int> key;
	vector<vector<int>> matriz;
};

struct HashTableFechada{
	vector<Lista> table;
	int M;
	int col;
};

struct Lista{
	Block *first;
	Block *last;
};

struct Block{
	DataTable valores;
	Block *prox;
};

void InitializeFechada(HashTableFechada *h, int M);
void InsertFechada(HashTableFechada *h, vector<int> key, vector<vector<int>> matriz);
int getValueFechada(HashTableFechada *h, vector<int> key, vector<vector<int>>* matriz);
void ImprimeFechada(HashTableFechada *h);

#endif