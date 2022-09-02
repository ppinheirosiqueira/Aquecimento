#include "Matriz.hpp"

int main() {
	string auxMenu;
	HashTableFechada hF;
	int M = 11;
	InitializeFechada(&hF, M);

	do{
		cout << "Escolha entre as opções abaixo: \n\n";
		cout << "1 - Criar um novo arquivo para ser lido.\n";
		cout << "2 - Ler o arquivo de coordenadas.\n";
		cout << "3 - Escolher coordenadas específicas para serem multiplicadas\n";
		cout << "4 - Imprimir Hash Atual\n";
		cout << "5 - Reiniciar Hash\n";
		cout << "Qualquer outra coisa - Sair do programa\n\nSua entrada: ";
		cin >> auxMenu;
		cout << "\n";

		if (auxMenu == "1"){
			criarArquivo();
			cout << "\nMatriz criada com sucesso no arquivo!\n";
			InitializeFechada(&hF, M);
			cout << "Hash reiniciada.\n\n";
		}
		
		else if(auxMenu == "2"){
			lerArquivoCoordenadas(&hF);
		}

		else if (auxMenu == "3"){
			int iInt, jInt;
			vector<int> coordenadas = lerCoordenadas();
			iInt = coordenadas[1] - coordenadas[0] + 1; // Intervalo de I
			jInt = coordenadas[3] - coordenadas[2] + 1; // Intervalo de J
			
			vector<vector<int>> res;
			int auxHash = getValueFechada(&hF,coordenadas, &res);

			if (auxHash == 1){
				cout << "Valor encontrado na Hash.\n";
				cout << "Matriz resultante final: \n";
				imprimeMatriz(res, iInt, iInt);
				cout << "\n\n";
			}
			else{
				calcularResultante(iInt, jInt, coordenadas, &hF);
			}
		}
		
		else if (auxMenu == "4"){
			ImprimeFechada(&hF);
		}

		else if(auxMenu == "5"){
			InitializeFechada(&hF, M);
			cout << "Hash reiniciada.\n\n";
		}
	}while(auxMenu == "1" || auxMenu == "2" || auxMenu == "3" || auxMenu == "4" || auxMenu == "5");
	
	cout << "Obrigado por usar o programa\n";
}