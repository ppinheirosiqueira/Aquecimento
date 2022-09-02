#include "Matriz.hpp"

void criarArquivo(){
	int tamI, tamJ, Random;
	cout << "Escolha o tamanho da Matriz NxM que você deseja fazer: \n";
	cout << "Digite N:\n";
	cin >> tamI;
	while (tamI <= 0){
		cout << "Escolha um tamanho válido por favor (maior do que 0)\n";
		cin >> tamI;
	}
	cout << "Digite M:\n";
	cin >> tamJ;
	while (tamJ <= 0){
		cout << "Escolha um tamanho válido por favor (maior do que 0)\n";
		cin >> tamJ;
	}
  
    /* initialize random seed: */
	srand (time(NULL));
  
	// Create and open a text file
  	ofstream MyFile("Matriz.txt");

	// Write to the file
  	for (int i=0;i<tamI;i++){
  		for (int j=0;j<tamJ;j++){
  			string aux = "";
  			Random = rand() % 100;
  			if (Random < 10){
  				aux = "0";
  			}
  			aux += to_string(Random);
  			MyFile << aux + " ";
  		}
  		MyFile << "\n";
  	}

	// Close the file
  	MyFile.close();
}

void lerArquivoCoordenadas(HashTableFechada *h){
	string myText;
	ifstream CoordenadasFile;
	vector<int> coordenadas(4,0);
	int iInt, jInt;
	
	CoordenadasFile.open("coordenadas.txt");
	while (getline (CoordenadasFile, myText)){
		if (int(myText.length() < 7)){
			cout << "Arquivo de coordenadas finalizado ou alguma linha com erro de escrita\n";
			CoordenadasFile.close();
			return;
		}
		
		int auxCoor = 0;
		int aux = 0;
		for(int i = 0; i < int(myText.length()); i++){
			if (myText[i] == ','){
				coordenadas[auxCoor] = stoi(myText.substr(aux,i-aux));
				aux = i + 1;
				auxCoor++;
			}
			if (auxCoor == 3){
				coordenadas[3] = stoi(myText.substr(aux,myText.length() - aux));
				break;
			}
		}

		cout << "Coordenadas coletadas: " << coordenadas[0] << "," << coordenadas[1] << "," << coordenadas[2] << "," << coordenadas[3] << "\n";

		aux = coordenadas[1];
		coordenadas[1] = coordenadas[2];
		coordenadas[2] = aux;

		iInt = coordenadas[1] - coordenadas[0] + 1;
		jInt = coordenadas[3] - coordenadas[2] + 1;

		vector<vector<int>> res;
		int auxHash = getValueFechada(h,coordenadas, &res);
		if (auxHash == 1){
			cout << "\nValor encontrado na Hash.\n";
			cout << "Matriz resultante final: \n";
			imprimeMatriz(res, iInt, iInt);
			cout << "\n\n";
		}
		else{
			calcularResultante(iInt, jInt, coordenadas, h);
		}
	}	
}

int lerArquivo(int iIni, int iFin, int jIni, int jFin, vector<vector<int>>* matriz){
	string myText;
	ifstream MatrizFile;
	int AuxLinha = 0;
	int auxI = 0;
	
	MatrizFile.open("Matriz.txt");

	while (getline (MatrizFile, myText)) {
		if (int(myText.length()/3) <= jFin){
			cout << "Coluna final inválida, o maior valor possível é: " << (myText.length()-3)/3 << "\n";
			MatrizFile.close();
			return 0;
		}
		if (AuxLinha >= iIni && AuxLinha <= iFin){
			for(int auxJ = 0; auxJ < (jFin - jIni + 1); auxJ++){
				(*matriz)[auxI][auxJ] = stoi(myText.substr(jIni*3 + auxJ*3,2));
			}
			auxI++;
		}
		AuxLinha++;
	}
	if (iFin >= AuxLinha){
		cout << "\nLinha final inválida, o maior valor possível é: " << AuxLinha-1 << "\n\n";
		MatrizFile.close();
		return 0;
	}
	// Close the file
	MatrizFile.close();

	return 1;
}

void imprimeMatriz(vector<vector<int>> matriz, int iTam, int jTam){
	for (int i = 0; i < iTam; i++){
		for (int j = 0; j < jTam; j++){
			cout << matriz[i][j] << " ";
		}
		cout << "\n";
	}
}

vector<vector<int>> multiplicaMatriz(int tamI, int tamJ, vector<vector<int>> matriz1,  vector<vector<int>> matriz2){

	vector<vector<int>> mul(tamI, vector<int>(tamI,0));

	for(int i=0; i<tamI; i++){    
		for(int j=0; j<tamI; j++){    
			mul[i][j]=0;    
			for(int k=0; k<tamJ; k++){    
				mul[i][j] += matriz1[i][k]*matriz2[k][j];    
			}    
		}    
	}

	return mul;
}

vector<int> lerCoordenadas(){
	vector<int> coordenadas(4,0);
	cout << "Diga a primeira linha da matriz: \n";
	cin >> coordenadas[0];
	while (coordenadas[0] < 0){
		cout << "Escolha um valor válido por favor (maior ou igual a 0)\n";
		cin >> coordenadas[0];
	}
	cout << "Diga a primeira coluna da matriz: \n";
	cin >> coordenadas[2];
	while (coordenadas[2] < 0){
		cout << "Escolha um valor válido por favor (maior ou igual a 0)\n";
		cin >> coordenadas[2];
	}
	cout << "Diga a última linha da matriz: \n";
	cin >> coordenadas[1];
	while (coordenadas[1] < coordenadas[0]){
		cout << "Escolha um valor válido por favor (maior ou igual ao primeiro valor de linha)\n";
		cin >> coordenadas[1];
	}
	cout << "Diga a última coluna da matriz: \n";
	cin >> coordenadas[3];
	while (coordenadas[3] < coordenadas[2]){
		cout << "Escolha um valor válido por favor (maior ou igual ao primeiro valor de coluna)\n";
		cin >> coordenadas[3];
	}
	return coordenadas;
}

void calcularResultante(int iInt, int jInt, vector<int> coordenadas, HashTableFechada *h){
	int auxLeitura;
	cout << "\nInfelizmente, valor ainda não pertencente a Hash.\n";
	cout << "Iniciando procedimentos para o cálculo.\n\n";
	vector<vector<int>> matriz(iInt, vector<int>(jInt,0));
	auxLeitura = lerArquivo(coordenadas[0], coordenadas[1], coordenadas[2], coordenadas[3], &matriz);
	if (auxLeitura == 1){
		cout << "Matriz lida: \n";
		imprimeMatriz(matriz, iInt, jInt);
		cout << "\nMatriz transposta: \n";
		vector<vector<int>> matrizTrans(jInt, vector<int>(iInt,0));
		for (int i = 0; i < jInt; i++){
			for(int j = 0; j < iInt; j++){
				matrizTrans[i][j] = matriz[j][i];
			}
		}
		imprimeMatriz(matrizTrans, jInt, iInt);
		cout << "\nMatriz Resultante: \n";
		vector<vector<int>> res = multiplicaMatriz(iInt, jInt, matriz, matrizTrans);
		imprimeMatriz(res, iInt, iInt);
		InsertFechada(h, coordenadas, res);
		cout << "\nHash Atualizada.\n\n";
	}
	matriz.clear();
}