#include <iostream>
#include <windows.h>
#include <string>
#include <locale.h>

using namespace std;

struct Player
{ // Struct Respons�vel por guardar informa��es do jogador.
	string nome;
	float score;
};

struct NoArvore
{								  // Struct Respons�vel pela cria��o e parte do processe de manipual��o da �rvore construida no programa.
	char dado;					  // Vari�vel cujo valor ser� armazenado na �rvore.
	NoArvore *esquerda, *direita; // Ponteiros para apontar na dire��o dos n�s da �rvore.
};

Player jogador;
// Inicializamos os ponteiros como NULL e criamos um ponteiro para copiar a �rvore sem alterar o seu valor.
NoArvore *novo = NULL;
NoArvore *raiz = NULL;
NoArvore *aux = raiz;

NoArvore *inserir(NoArvore *, char); // Fun��o Para inserir valores na �rvore.
void inserirArvore(NoArvore *);		 // Fun��o respons�vel por inserir os elementos na �rvore (Poderia ser inserida junto com a fun��o "inserir", mas criamos separada apenas por motivos de organiza��o).

// As duas fun��es a seguir n�o ser�o utilizada e est�o no programa apenas a n�vel de conhecimento.
// Pois n�o h� necessidades de se usar visto que n�o apresenta serventia ao c�digo.
int imprimir_arvore(NoArvore *); // Fun��o para imprimir valores da �rvore em pr� ordem (tamb�m � poss�vel imprimir em ordem sim�trica ou p�s ordem).
NoArvore *remover(NoArvore *, char);

// Fun��es de hist�ria: Cont�m o menu do jogo, suas escolhas e desenvolvimentos.
void intro(string);			   // Fun��o de texto para introduzir o jogo .
void home(string, bool &);	   // Fun��o que funciona como um menu principal, respons�vel por iniciar o jogo e coletar alguns dados do jogador.
void historia(string, bool &); // Fun��o com os eventos e acontecimentos do jogo, � aqui que o programa compara a variavel percorrida pela arvore com o evento que ir� acontecer.

// Fun��es est�ticas: Servem para maior harmoniza��o entre o usu�rio e o programa.
void centralizar(string); // Fun��o est�tica para centralizar o texto no terminal do console.
void view(string);		  // Fun��o est�tica que reproduz letra por letra na exibi��o dos textos do jogo.
void limpar(string);	  // Fun��o para exibir o texto corretamente e limpar a tela (contruida com outras fun��es).

int main()
{

	int escolha = 0;
	bool fim = false;
	string f; // Variavel auxliar. Serve apenas para armazenar os textos que ser�o exibidos na tela.

	inserirArvore(aux);	 // Aqui n�s inicializamos a �rvore e executamos a fun��o para preencher com os valores.
	jogador.score = 0.0; // Aqui inicializamos a pontua��o do jogador e definimos como 0.

	intro(f);	  // Chamamos a fun��o de introdu��o do jogo.
	home(f, fim); // Exibimos o menu "Home".
	while (fim != true)
	{										// Essa parte do c�digo garantir� que o programa s� enquanto o usu�rio n�o tiver chegado ao fim da aventura, e pare ao fim.
		system("cls");						// Limpando o console
		historia(f, fim);					// Come�amos a introduzir a hist�ria, o usu�rio j� come�a em um ponto de partida fixo e suas escolhas e decis�es o levar�o ao resultado do seu jogo.
		jogador.score = jogador.score + 50; // Cada vez que o usu�rio passa por aqui, quer dizer que ele n�o morreu ainda e ganha + 50 pontos por isso. Receba B�nus por sobreviver at� o final!

		if (fim == true)
		{ // Aqui verificamos se o jogo acabou nesta �ltima rodada, se sim, � exibido uma mensagem de fim de jogo e a pontua��o do usu�rio.
			Sleep(1000);
			system("cls");
			cout << "Fim de jogo!" << endl;
			cout << "Voc� fez " << jogador.score << " pontos!" << endl;

			break;
		}
		// Caso n�o seja o fim do jogo ainda, o jogador poder� escolher qual caminho seguir� em sua jornada.
		cout << "                                                     ";
		cin >> escolha;
		if (escolha == 1)
		{ // Se ele escolhe o caminho da esquerda, ent�o a �rvore � percorrida, seguindo o caminho da esquerda.
			aux = aux->esquerda;
		}
		else if (escolha == 2)
		{ // Se ele escolhe o caminho da direita, ent�o a �rvore � percorrida, seguindo o caminho da direita.
			aux = aux->direita;
		}
		else
		{
			jogador.score = jogador.score - 50; // Aqui retiramos os pontos ganhos se o jogador n�o inserir um valor v�lido, para evitar burlas no sistema de pontua��es.
			f = "N�o aceito, tente novamente!"; // Armazena a frase na vari�vel para ser enviada � fun��o e impressa corretamente.
			system("cls");						// Limpa o terminal.
			limpar(f);							// Exibe a informa��o que a informa��o inserida n�o � aceita.
		}
	}
}

NoArvore *inserir(NoArvore *aux, char info)
{ // Insere elementos na arvore ja fazendo o balanciamento.

	if (aux == NULL)
	{														   // Verifica se tem algo na raiz, sen�o tiver ele j� pode inserir direto
		NoArvore *novo = (NoArvore *)malloc(sizeof(NoArvore)); // Aloca espa�o na mem�ria para um novo n� na �rvore
		novo->dado = info;									   // Recebe uma c�pia da vari�vel como elemento d� �rvore
		// Informa a mem�ria que seus dois filhos (quais ele aponta) tem o valor NULL
		novo->esquerda = NULL;
		novo->direita = NULL;
		return novo;
	}
	else // Sen�o vazio, ele percorre a �rvore para inserir em algum lugar livre
	{
		if (info < aux->dado)
		{ // Se for menor que o valor atual, vai para a direita
			aux->esquerda = inserir(aux->esquerda, info);
		}
		if (info > aux->dado)
		{ // Se for maior que o valor atual, vai para a direita
			aux->direita = inserir(aux->direita, info);
		}
		return aux;
	}
}

void inserirArvore(NoArvore *)
{ // Constr�i uma �rvore predeterminada com os valores informados
	aux = inserir(aux, 'H');
	aux = inserir(aux, 'D');
	aux = inserir(aux, 'J');
	aux = inserir(aux, 'B');
	aux = inserir(aux, 'F');
	aux = inserir(aux, 'I');
	aux = inserir(aux, 'K');
	aux = inserir(aux, 'A');
	aux = inserir(aux, 'C');
	aux = inserir(aux, 'E');
	aux = inserir(aux, 'G');
	// A ordem de inser��o em uma �rvore geralmente n�o interfere no seu funcionamento, mas para o modelo proposto no programa (que ser� apresentado em sala)
	// � indispensavel essa ordena��o para melhor desenvolvimento e seguimento dos eventos de maneira cronol�gica.
}

int imprimir_arvore(NoArvore *aux)
{ // Fun��o para imprimir os elemento da �rvore em pr� ordem
	if (aux)
	{									// Aqui ele verifica se a arvore est� vazia (ja que a condi��o vazia verifica se � diferente de null)
		imprimir_arvore(aux->esquerda); // Aqui percorre os elementos da esquerda de forma recursiva
		cout << aux->dado << " ";		// Imprime o elemento
		imprimir_arvore(aux->direita);	// E percorre os elementos da direita
		// Com isso ele imprime os elementos em ordem crescente (No c�digo atual ele imprimiria A B C D E F G H I J K)
	}
}

NoArvore *removerNo(NoArvore *aux, char dado)
{ // Fun��o para remover um elemento espec�fico da �rvore

	char caractere; // Variavel para receber o elemento a ser removido

	cout << "Insira o caracter que voc� deseja remover." << endl;
	cin >> caractere;

	if (aux == NULL)
	{
		cout << "O valor informado n�o est� inserido na �rvore." << endl;
		return NULL;
	}
	else
	{
		if (aux->dado == caractere)
		{ // Aqui ele verifica se o n� tem algum filho, se n�o tiver ele � um n� folha e pode apenas ser removido facilmente.
			if (aux->esquerda == NULL && aux->direita == NULL)
			{
				free(aux);
				return NULL;
			}
			else
			{ // Caso ele n�o seja um n� folha, como � uma arvore bin�ria (que s� pode conter 0, 1 ou 2 filhos e j� sabemos que n�o tem 0) vamos verificar se tem um filho ou dois
				if (aux->esquerda != NULL && aux->direita != NULL)
				{									 // Se os ponteiros que apontam para esquerda e para direita s�o diferentes de NULL, temos 2 filhos, ent�o vamos mudar a ordem criando uma c�pia do elemento para realizar a troca e depois devolvendo ao lugar certo
					NoArvore *copia = aux->esquerda; // Aqui criamos uma c�pia da vari�vel
					while (copia->direita != NULL)
					{ // O la�o de repeti��o serve para percorrer at� o final da arv�re
						copia = copia->direita;
					}
					aux->dado = copia->dado;						// Atibuimos o valor da variavel a copia
					copia->dado = caractere;						// Substituimos
					aux->esquerda = removerNo(aux->esquerda, dado); // Devolvemos o valor e removemos
					return aux;										// E liberamos o espa�o na mem�ria
				}
				else
				{					 // Quando s� temos um filho � f�cil remover porque s� temos que criar uma c�pia do valor para posteriormente ser substituido.
					NoArvore *copia; // Aqui criamos uma c�pia da vari�vel
					if (aux->esquerda != NULL)
					{ // Se a esquerda estiver livre, vamos inserir o valor guardado para que n�o seja perdido quando removermos o elemento
						copia = aux->esquerda;
					}
					else
					{ // Se a esquerda n�o estiver livre, vamos inserir � direita.
						copia = aux->direita;
					}
					free(aux); // Depois que seu filho foi reposicionado, podemos liberar o espa�o da mem�ria que ele ocupava
					return copia;
				}
			}
		}
		else
		{ // Se tiver o elemento e ele for menor que o percorrido ele � realocado para a esquerda
			if (dado < raiz->dado)
			{
				aux->esquerda = removerNo(raiz->esquerda, dado);
			}
			else
			{
				aux->direita = removerNo(raiz->direita, dado);
			}
			return aux;
		}
	}
}

void intro(string frase)
{
	setlocale(LC_ALL, "Portuguese");	  // Fun��o para aplica��o de acentua��o
	system("mode con:cols=120 lines=30"); // Fun��o que define o tamanho da janela a ser exibida o jogo
	system("Color f4");					  // Fun��o que define a cor de fundo e a cor do texto
	// system("Color 02"); //Caso a visualiza��o esteja ruim, esse layout mudar� as cores do terminal para preto e verde para melhor visualiza��o

	frase = "Voc� � uma pessoa importante que est� embarcando em uma viagem de f�rias com 5 amigos em um avi�o particular.";
	limpar(frase);

	frase = "A viagem segue tranquila, ent�o, voc� avista uma ilha tenebrosa, mas...";
	limpar(frase);

	frase = "(Piloto) Estamos passando por uma turbul�ncia, apertem os cintos senhoras e senhores!";
	limpar(frase);

	frase = "(Piloto) SEGUREM-SE!";
	limpar(frase);

	frase = "(GRITOS)";
	limpar(frase);

	frase = "O avi�o cai na ilha.";
	limpar(frase);

	frase = "...";
	limpar(frase);
	system("pause");
}

void home(string frase, bool &fim)
{						 // Fun��o de menu
	char controle = 'a'; // Variavel de controle que recebe a op��o do jogador de iniciar o jogo ou sair (inicializada com um valor aleatorio para atendimento dos requisitos das estruturas condicionais a seguir)

	while (controle != 'x' && controle != 'X' && controle != 'o' && controle != 'O')
	{ // Aqui garante que o menu ser� exibido enquanto o jogador n�o inserir um valor v�lido (iniciar ou fechar o jogo).
		// As pr�ximas 12 linhas de c�digo s�o apenas para enfeitar a exibi��o do programa
		system("cls");
		frase = "< Choice Islands: The game! >";
		centralizar(frase);
		view(frase);
		Sleep(200);
		cout << endl
			 << endl;
		cout << "                                         ";
		frase = "Aperte [O] para iniciar ou [X] para sair\n";
		view(frase);
		for (int i = 0; i < 60; i++)
		{
			cout << " ";
		}

		cin >> controle; // Recebe a op��o do jogador
		cout << endl
			 << endl
			 << endl
			 << endl;
		cout << "                                                            ";
		system("cls");
		if (controle != 'x' && controle != 'X' && controle != 'o' && controle != 'O')
		{
			frase = "Valor inv�lido!\n";
			limpar(frase);
		}
	}

	if (controle == 'x' or controle == 'X')
	{
		fim = true;
		frase = "Voc� decidiu abandonar o jogo, uma pena!\n";
		limpar(frase);
	}

	else if (controle == 'o' or controle == 'O')
	{ // Recebe o nome do jogador e armazena
		frase = "Diga-me o seu nome...";
		centralizar(frase);
		view(frase);
		cout << endl
			 << endl
			 << endl;
		cout << "                                                     ";
		cin.ignore();
		getline(cin, jogador.nome);
		system("cls");
	}
}

void historia(string frase, bool &fim)
{
	char copiaAux = aux->dado; // Cria uma c�pia d� vari�vel atual que est� sendo percorrida na �rvore
	switch (copiaAux)
	{ // Estrutura de sele��o que exibe o evento que acontecer� de acordo com as decis�es do jogador percorrendo a �rvore. Cada letra (elemento da �rvore) corresponde a um evento de forma sequencial e cronol�gica.
	case 'H':
	{

		frase = "Voc�, " + jogador.nome + ", acordou ap�s horas desmaiado, em meio a uma floresta na ilha.";
		limpar(frase);

		frase = "Voc� est� PERDIDO!";
		limpar(frase);

		frase = "... e, por incr�vel que pare�a... sem ferimentos s�rios.";
		limpar(frase);

		frase = "Ap�s andar pela floresta, voc� se depara com uma trilha e decide seguir por ela at� que...";
		limpar(frase);

		frase = "Voc� encontra uma bifurca��o na estrada!";
		limpar(frase);

		frase = "O caminho � esquerda � aberto, com galhos quebrados pela estrada, e uma vegeta��o rasteira.";
		limpar(frase);

		frase = "O caminho � direita � fechado, com uma neblina estranha, e uma mata alta.";
		limpar(frase);

		frase = "Por qual caminho voc� quer seguir? ";
		centralizar(frase);
		view(frase);
		cout << endl;

		frase = "Aperte [1] para seguir pela esquerda ou [2] para seguir pela direita ";
		centralizar(frase);
		view(frase);
		cout << endl;
		break;
	}
	case 'D':
	{
		system("cls");
		frase = "Voc� seguiu pela estrada esquerda, andou por 4km e encontrou uma �rea aberta, pr�xima ao mar.";
		limpar(frase);

		frase = "Ao analisar o ambiente, voc�  percebe que h� uma cabana acima de um pequeno morro.";
		limpar(frase);

		frase = "Voc� tamb�m, percebe que h� um bote perto no mar.";
		limpar(frase);

		frase = "Aperte [1] para vasculhar a cabana ou [2] para ir at� o bote ";
		centralizar(frase);
		view(frase);
		cout << endl;
		break;
	}
	case 'B':
	{
		system("cls");
		frase = "Voc� subiu o morro, entrou na cabana e estava sem ningu�m...";
		limpar(frase);

		frase = "Ao entrar, voc� se depara com um banquete, e ouve seu est�mago grunir.";
		limpar(frase);

		frase = "Voc�, " + jogador.nome + ", tamb�m avistou um r�dio perto da mesa de centro.";
		limpar(frase);

		frase = "Qual ser� a sua escolha?";
		limpar(frase);

		frase = "Aperte [1] para comer o banquete ou [2] para usar o r�dio ";
		centralizar(frase);
		view(frase);
		cout << endl;
		break;
	}
	case 'F':
	{
		system("cls");
		frase = "Voc� ignorou a cabana e foi direto para perto do bote.";
		limpar(frase);

		frase = "Nesta parte da praia, v� que pr�ximo ao bote, existem alguns instrumentos de sobreviv�ncia.";
		limpar(frase);

		frase = "Mas tamb�m, voc� percebe h� remos por perto perto.";
		limpar(frase);

		frase = "O que voc� vai fazer?";
		limpar(frase);

		frase = "Aperte [1] para tentar sobreviver na ilha ou [2] para usar o bote para fugir da ilha ";
		centralizar(frase);
		view(frase);
		cout << endl;
		break;
	}
	case 'I':
	{
		system("cls");
		frase = "Voc�, " + jogador.nome + ", numa atitude corajosa foi desbravar a vila.";
		limpar(frase);

		frase = "Dentro da vila voc� escuta gritos, correntes batendo, e uma luz forte vindo em sua dire��o pela rua.";
		limpar(frase);

		frase = "Voc� corre, mas a luz fica cada vez mais forte e...";
		limpar(frase);

		frase = "(GRITOS)";
		limpar(frase);

		frase = "Voc� acordou em seguran�a, no seu quarto, ap�s um pesadelo!";
		centralizar(frase);
		view(frase);
		jogador.score = jogador.score + 150;
		aux = NULL;
		fim = true;
		break;
	}

	case 'K':
	{
		system("cls");
		frase = "Voc�, " + jogador.nome + ", foge para longe da vila e entra novamente na floresta.";
		limpar(frase);

		frase = "Voc� n�o reconhece mais as �rvores das quais tinha passado.";
		limpar(frase);

		frase = "A escurid�o toma conta de vez da floresta e voc� n�o consegue se guiar pela mata.";
		limpar(frase);

		frase = "Voc� est� perdido!";
		limpar(frase);

		frase = "Ap�s dias tentando achar a sa�da daquela mata, seu corpo n�o resiste com a fome.";
		limpar(frase);

		frase = "e ap�s longos e exaustivos dias de busca, voc� morre.";
		limpar(frase);
		aux = NULL;
		fim = true;
		break;
	}
	case 'A':
	{
		system("cls");
		frase = "Voc� est� se deliciando com o banquete na cabana, quando de repente...";
		limpar(frase);

		frase = "Um calafrio percorre toda sua espinha, e ao olhar para baixo, voc� percebe que est� sangando muito.";
		limpar(frase);

		frase = "O propriet�rio da casa havia chegado enquanto voc� comia e lhe apunhalou pelas costas, com uma pistola de silenciador.";
		limpar(frase);

		frase = "E voc� sangra lament�velmente at� a morte.";
		limpar(frase);
		aux = NULL;
		fim = true;
		break;
	}
	case 'J':
	{
		system("cls");
		frase = "Voc� seguiu pela estrada direita mata a dentro, ap�s 15 minutos andando, voc� encontra uma estrada.";
		limpar(frase);

		frase = "Essa estrada te levou a uma vila abandonada, sua intui��o te diz para ir embora.";
		limpar(frase);

		frase = "Mas a sua curiosidade � t�o forte quanto, ent�o o que voc� escolhe?";
		limpar(frase);

		frase = "Aperte [1] para desbravar a vila ou [2] para fugir da vila ";
		centralizar(frase);
		view(frase);
		cout << endl;
		break;
	}
	case 'C':
	{
		system("cls");
		frase = "Voc� escolheu usar o r�dio e chamar ajuda...";
		limpar(frase);

		frase = "Voc� escuta passos por perto e foge da cabana.";
		limpar(frase);

		frase = "N�o demorou muito tempo at� que voc� recebesse ajuda, um helic�ptero foi em sua busca.";
		limpar(frase);

		frase = "Voc� � o �nico sobrevivente da trag�dia da ilha! ";
		limpar(frase);
		jogador.score = jogador.score + 150;
		aux = NULL;
		fim = true;
		break;
	}
	case 'E':
	{
		system("cls");
		frase = "Voc�, " + jogador.nome + ", recolhe os itens de sobreviv�ncia e tenta permanecer na ilha at� a ajuda chegar.";
		limpar(frase);

		frase = "Mas o tempo passa e nenhuma ajuda chega... Voc� resiste � ilha por um bom tempo.";
		limpar(frase);

		frase = "Mas a ilha te consome a cada dia. At� que...";
		limpar(frase);

		frase = "Voc� morre por desnutri��o.";
		limpar(frase);
		aux = NULL;
		fim = true;
		break;
	}
	case 'G':
	{
		system("cls");
		frase = "Voc�, " + jogador.nome + ", escolhe remar para fugir da ilha";
		limpar(frase);

		frase = "Mas a mar� estava cheia e a correnteza estava forte.";
		limpar(frase);

		frase = "Ap�s algumas horas, exausto e remando, uma enorme onda vem de encontro a sua dire��o, e te engole.";
		limpar(frase);

		frase = "E voc� morre.";
		limpar(frase);
		aux = NULL;
		fim = true;
		break;
	}
	}
}

void centralizar(string f)
{ // Fun��o apenas est�tica para centralizar o texto no meio da tela, pode ignorar.
	int tam = 120;
	int i;
	tam = tam - f.length();
	i = tam / 2;
	cout << endl
		 << endl
		 << endl
		 << endl
		 << endl
		 << endl
		 << endl
		 << endl
		 << endl
		 << endl
		 << endl
		 << endl;
	while (i != 0)
	{
		cout << " ";
		i--;
	}
}

void view(string frase)
{ // Fun��o apenas est�tica para exibir o texto de maneira sequencial, pode ignorar.
	int tam = frase.length();
	for (int i = 0; i <= tam; i++)
	{
		cout << frase[i];
		Sleep(20);
	}
}

void limpar(string frase)
{ // Fun��o apenas est�tica para limpar o terminal, pode ignorar.
	centralizar(frase);
	view(frase);
	Sleep(2500);
	system("cls");
}
