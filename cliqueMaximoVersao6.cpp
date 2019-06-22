/*
    Feito por:                                  Matrícula:
       Matheus Gonçalves Ferreira   	            15.1.4341
	   Thiago Oliveira de Santana					15.1.4313
    Disciplina: BCC 204 - Teoria dos Grafos
    Prof.: Marco Antonio M. Carvalho

    Algoritmo básico, podendo ser explorado mais futuramente.
    Baseado na ideia de achar o clique Maximal usando o algoritmo Bron-Kerbosch e retorna-se o maior dos cliques maximais!!!
*/
#include <bits/stdc++.h>	//Biblioteca para incluir todas as outras!
using namespace std;
using namespace std::chrono;//Para fazer a contagem do tempo!

/* -- Variáveis Globais, mudar isso -- */
int tam = 0;
vector<int> maior;

/* -- Imprimir o clique máximo encontrado -- */
void printClique(vector<int> clique)
{
	int k, tamanho;
	tamanho = clique.size();

	cout << endl;
	cout << "Tamanho Clique Maximo: " << tam << endl;
	cout << "Vertices Clique Maximo: ";
	for(k = 0; k < tamanho; ++k)
	{
		cout << clique[k] << " ";
	}
	cout << endl;
}

/* -- Verificar com todos os cliques encontrado no grafo, qual é o maior -- */
void maximoClique(vector<int> maximo)
{
	int tamanho;
	tamanho = maximo.size();

	if(tam < tamanho)
	{
		tam = maximo.size();
		maior = maximo;
	}
}

/* Uma funcao para realizar op. de união do primeiro conjunto com um elemento
 * Parametros:
 *		 	Primeiro: vetor de inteiros que representam o conjunto que executará uma
 *               	  operação de união com o segundo parâmetro.
 * 			Segundo:  inteiro que representa o elemento a ser adicionado no primeiro
 *               	  parametro
 *
 * Retorna vector<int> o vetor de inteiros com o segundo parametro adicionado.
 */
vector<int> uni(vector<int> primeiro, int segundo)
{
	primeiro.push_back(segundo);

	return primeiro;
}

/* Uma função para perfurar a operação de interseção com o primeiro conjunto 
 * e os vizinhos do segundo elemento.
 * Parametros:
 *			conf: vetor de inteiros que representa o conjunto que irá executar uma operacao
 *               de intersecao com os vizinhos do segundo parametro
 * 			segundo:  inteiro que representa o elemento que será a conexão para encontrar
 *          		  seus vizinhos
 *
 * Retorna vector<int> o vetor de inteiros com o novo conjunto gerado a partir da interseção
 */
vector<int> intersec(vector<int>* grafo, vector<int> conf, int segundo)
{
	vector<int> novoPrimeiro;
	int k, l, tamanho1, tamanho2;
	tamanho1 = conf.size();

	for(k = 0; k < tamanho1; ++k)
	{
		tamanho2 = grafo[segundo].size();
		for(l = 0; l < tamanho2; ++l)
		{
			if(conf[k] == grafo[segundo][l])
		  	{
		    	novoPrimeiro.push_back(conf[k]);
		  	}
		}
	}
	return novoPrimeiro;
}

/* Uma funcao que calcula todos os cliques maximais do grafo.
 * Parametros:
 *			R vetor de inteiros que representa uma possivel clique
 * 			P vetor de inteiros que representa os vertices adjacentes de cada
 *          		vertice atualmente em R
 *			X vetor de inteiros que representa nós que já estão em alguma clique
 *          		ou processados (para remover cliques duplicados)
 */
void bron(vector<int>* grafo, vector<int> R,vector<int> P,vector<int> X)
{
	vector<int> newr, newp, newx;

	if(P.empty() && X.empty())
	{
		maximoClique(R);
	}
	else
	{
		for(int v : P)
		{
			newr = uni(R, v);
		  	newp = intersec(grafo, P, v);
		  	newx = intersec(grafo, X, v);
		  	bron(grafo, newr, newp , newx);
		  	P.erase(remove(P.begin(), P.end(), v), P.end());
		  	X.push_back(v);
		}
	}
}

int main(int argc, char*argv[])
{
	string nome_arquivo;
	
    if(argc != 2)
    {
        //Analisando erro do formato de entrada do programa!
        cerr << "\nFormato de entrada invalido!" << endl;
        cerr << "Formato esperado: <executavel> <nome_arquivo_instancia>" << endl << endl;
        
        cout << "Por favor, informe o nome do arquivo da instancia a ser tratada: " << endl;
        cout << "Nome: ";
        getline(cin,nome_arquivo);
    }
	else
	{
		nome_arquivo = argv[1];
	}
	
	//Criação variavel para leitura de arquivo
	ifstream entrada;
	string palavra;
	int vertice1, vertice2, vertices, arestas;
	
	//Caso o usuário não forneça a extensão .clq entrára aki para fazer o devido tratamento
	if(nome_arquivo.find(".clq") > nome_arquivo.size())
	{
		nome_arquivo += ".clq";
	}
	entrada.open(nome_arquivo.c_str());
	//Caso o usuário forneça o nome do arquivo errado...
	while(!entrada)
	{
		cout<<"\nERRO NA ABERTURA DO ARQUIVO " << nome_arquivo << " !!!" << endl << endl;
		cout<<"Favor informar um nome valido para o arquivo da instancia" << endl;
		cout << "Nome : ";
        getline(cin,nome_arquivo);
		//Caso o usuário não forneça a extensão .clq entrára aki para fazer o devido tratamento
		if(nome_arquivo.find(".clq") > nome_arquivo.size())
		{
			nome_arquivo += ".clq";
		}
		entrada.open(nome_arquivo.c_str());
	}
	
	//Leitura da primeira linha do arquivo(quantidades de vertices e arestas)
	entrada >> palavra >> palavra;
	entrada >> vertices >> arestas;

	//Formato da estrutura de dados do grafo: vértice, conjunto de todos os vértices que esse vértice se liga (inclusive si mesmo)
	vector<int> R, P, X;
	vector<int> *grafo;
	grafo = new vector<int> [vertices+1];
	
	int i;
	for(i = 0; i < arestas; i++)
	{
		entrada >> palavra >> vertice1 >> vertice2;

		//Lista de adjacencia!
		grafo[vertice1].push_back(vertice2);
		grafo[vertice2].push_back(vertice1);
	}
	entrada.close();

	for(i = 1; i <= vertices; i++)
	{
		P.push_back(i);
	}

	duration<double> time_span;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
	
	//Algoritmo para achar as cliques maximais, e em consequencia o clique máximo!
	bron(grafo, R, P, X);

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
    time_span = duration_cast<duration<double> >(t2-t1);

	printClique(maior);
	cout << "Tempo de execucao: " << time_span.count() << " segundos." << endl;

	delete [] grafo; 
	return 0;
}