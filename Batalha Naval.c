#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define P 11						// Porta-avioes		qtd.1		identificação 1
#define C 10						// Couraçado		qtd.2 		identificação 2
#define T 7							// Torpedeiros		qtd.3		identificação 3
#define H 8							// Hidroavioes		qtd.4		identificação 4					 
#define ALTO 1						// Representa um sinal logico alto, ou seja verdadeiro para o programa
#define BAIXO 0						// Representa um sinal logico baixo, ou seja falso ao programa
#define FLUTUANTE 3					// Representa um sinal logico que não esta em alto nem baixo, ou seja indefinido
//====================================================================
//		Struct das quantidades de peças 
//====================================================================

typedef struct{
	int pa;
	int co;
	int to;
	int hi;
}Barco;


//====================================================================
//		Lista de funções
//====================================================================

int 	Menu_de_Inicio(void);																																						//start do jogo para o usuario
int		Comandos(char* gravar, int* lc);																																			//Le os comandos digitados		
void 	Ajuda(void);																																								//Abre o menu de Ajuda
void 	Iniciar_matrizes(int campo1[16][16],int campo2 [16][16]);																													//Randomiza os barcos 						
void	Matriz_imagem(int campo[16][16],int jogador, char imgcampo[16][16], int pontos, double tempo);																				//Imprime o tabuleiro da batalha naval
void	Escrita_na_matriz(int mat[16][16], int N, int iden);																														//Aloca os barcos na matriz
void 	Trans(int campo[16][16],char imgcampo[16][16]);																																//Transforma os a matriz numerica em imagem
int 	Tiro(int dados[], int campo[16][16], char imgcampo[16][16], int *pontos, Barco* qa, int* pt);																				//Exerce o tiro e abre as informações na tela
void	Gravar(char* gravar, int* pontos1, int* pontos2, double* tempo, int* aux, int campo1[16][16], int campo2[16][16],  char imgcampo1[16][16], char imgcampo2[16][16]);			//Grava as informações do campo
void	Carrega(char* gravar, int* pontos1, int* pontos2, double* tempo, int* aux, int campo1[16][16], int campo2[16][16],  char imgcampo1[16][16], char imgcampo2[16][16]);		//Carrega as informações do campo

//====================================================================
//		Inicio
//====================================================================

int main(void){
	
	int aux,i,j;
	
	int campo1[16][16],campo2[16][16];
	char imgcampo1[16][16],imgcampo2[16][16];
	
	char gravar[30];
	int parametros[2];
	
	int pontos1,pontos2;
	
	double tempo;
	clock_t start_t, end_t;

	
fim:
	aux = Menu_de_Inicio();
ret:	if(aux==1)	return 0;

/*
	O programa funciona basicamente apartir de duas matrizes:
	
	campo: que apresenta todas as possiçoes dos barcos e não é acessivel ao jogador
	
	imgcampo: que apresenta tudo aquilo que o jogador consegue ver, sendo que a matriz campo
	ao decorrer do jogo passará as informações para o complemento da imgcampo
*/

rest:			//Reinicia os campos o tempo e os pontos
	start_t = clock();
	pontos1 = 0;
	pontos2 = 0;
	
acaso:			// Reinicia apenas os campos
	Iniciar_matrizes(campo1,campo2);
	
	
	for(i=0;i!=16;i++)
		for(j=0;j!=16;j++){
			imgcampo1[i][j] = ' ';
				imgcampo2[i][j] = ' ';
		}
	
	int pt1 = 84,pt2 = 84;
	Barco qa1, qa2;						//Quantidade de peças de barcos							
	
	/*
		qa é a quantidade de cada barco peça de barco no tabuleiro
	*/
	
	qa1.pa = 11;
	qa1.co = 20;
	qa1.to = 21;
	qa1.hi = 32;
	
	qa2.pa = 11;
	qa2.co = 20;
	qa2.to = 21;
	qa2.hi = 32;
			
		
	while(1){		//Inicio do Jogo 
ret1:	
		end_t = clock(); 				//Calcula o tempo passado desde o inicio do jogo
		tempo = end_t - start_t;
		tempo = tempo/CLOCKS_PER_SEC;
		

		Matriz_imagem(campo1,1,imgcampo1,pontos1,tempo);
		aux = Comandos(gravar, parametros);
		
		switch (aux){
			case 0:						//Tiro	
				aux = Tiro(parametros,campo1,imgcampo1,&pontos1,&qa1,&pt1);
				
				if(aux == 1)
					goto ret1;	 
				
				if(aux == 2){			//Com o aux sendo igual a dois todos os barcos inimicos foram abatidos
					system("cls");
					printf("Parabens Jogador 1!!!\n");\
					sleep(2);
					goto rest;
				}
				break;
				
			case 1:						//Reset
				system("cls");
				printf("Reorganizando os barcos...\n");
				printf("Zerando os pontos...\n");
				goto rest;
				break;
				
			case 2:						//Sair
				aux = 1;
				goto ret;
				break;
				
			case 3:						//Ajuda
				Ajuda();
				goto ret1;
				break;
				
			case 4:						//Acaso
				system("cls");
				printf("Reorganizando os barcos...\n");
				goto acaso;
				break;
			
			case 5:						//Gravar
				end_t = clock(); 		//Há uma contagem do tempo no instante antes de salvar o campo
				tempo = end_t - start_t;
				tempo = tempo/CLOCKS_PER_SEC;
				aux = 1;				//Seleciona a vez do jogador anteriormente a ser salvo
				Gravar(gravar, &pontos1, &pontos2, &tempo, &aux, campo1, campo2, imgcampo1, imgcampo2);
				goto ret1;
				break;
			
			case 6:						//Carregar
				Carrega(gravar, &pontos1, &pontos2, &tempo, &aux, campo1, campo2, imgcampo1, imgcampo2);
				
				if(aux == 2){
					goto ret2;
				}
										
				goto ret1;
				break;	
			
			case 7:						//Mode 123
				/*
					Acesso restito apenas para dessenvolvedores que sabem o codigo de acesso
				*/
				Trans(campo1,imgcampo1);
				Trans(campo2,imgcampo2);
				goto ret1;
				break;
		}

	
ret2:	
		end_t = clock(); 				//Calcula o tempo passado desde o inicio do jogo
		tempo = end_t - start_t;
		tempo = tempo/CLOCKS_PER_SEC;
		
		Matriz_imagem(campo2,2,imgcampo2,pontos2,tempo);
		aux = Comandos(gravar, parametros);
		
		switch (aux){
			case 0:						//Tiro	
				aux = Tiro(parametros,campo2,imgcampo2,&pontos2,&qa2,&pt2);
				
				if(aux == 1)
					goto ret2;	 
				
				if(aux == 2){			//Com o aux sendo igual a dois todos os barcos inimicos foram abatidos
					system("cls");
					printf("Parabens Jogador 2!!!\n");
					sleep(2);
					goto rest;
				}
				break;
				
			case 1:						//Reset
				system("cls");
				printf("Reorganizando os barcos...\n");
				printf("Zerando os pontos...\n");
				goto rest;
				break;
				
			case 2:						//Sair
				aux = 1;
				goto ret;
				break;
				
			case 3:						//Ajuda
				Ajuda();
				goto ret2;
				break;
				
			case 4:						//Acaso
				system("cls");
				printf("Reorganizando os barcos...\n");
				goto acaso;
				break;
			
			case 5:						//Gravar
				end_t = clock(); 		//Há uma contagem do tempo no instante antes de salvar o campo
				tempo = end_t - start_t;
				tempo = tempo/CLOCKS_PER_SEC;
				aux = 2;				//Seleciona a vez do jogador anteriormente a ser salvo
				Gravar(gravar, &pontos1, &pontos2, &tempo, &aux, campo1, campo2, imgcampo1, imgcampo2);
				goto ret2;
				break;
			
			case 6:						//Carregar
				Carrega(gravar, &pontos1, &pontos2, &tempo, &aux, campo1, campo2, imgcampo1, imgcampo2);
				
				if(aux == 1){
					goto ret1;
				}
			
				goto ret2;	
				break;
			
			case 7:						//Mode 123
				/*
					Acesso restito apenas para dessenvolvedores que sabem o codigo de acesso
				*/
				Trans(campo1,imgcampo1);
				Trans(campo2,imgcampo2);
				goto ret2;
				break;
		}
	}

	return 0;
}

//====================================================================
//		Menu de Inicio
//====================================================================

int	Menu_de_Inicio(void){
	int aux;	

inicio:	
	system("cls");
	printf("Bem Vindo a Batalha Naval!\n");		
	printf("Precione:\n1-Iniciar \n2-Ajuda\n3-Sair\nSelecione: ");
	scanf("%d",&aux);
	
	switch (aux){
		case 1:				//Iniciar
			system("cls");
			printf("Preparando a Batalha...\n");
			return 0;		
		break;
		
		case 2:				//Ajuda
			Ajuda();
			goto inicio;
		break;
		
		case 3:				//Sair
			return 1;
		break;	

	}	
}

//====================================================================
//		Menu de Ajuda
//====================================================================

void Ajuda(void){		
	char c;
	
	system("cls");
	
	printf("Pow (coluna)(linha) - Seleciona um lugar para atirar\n");
	printf("Reset - Nova partida\n");
	printf("Sair - Abandonar o Jogo\n");
	printf("Ajuda-Retona a este Menu\n");
	printf("Acaso - Inicia um novo tabuleiro mantendo os pontos\n");
	printf("Gravar (nome do arquivo) - Salva o jogo\n");
	printf("Carregar (nome do arquivo) - Carrega o jogo\n");
	printf("Pressecione qualquer tecla para sair:");
	
	while(1){
		c =	getchar();
		if(c!='\n'){
			system("cls");
			return;
		}
	}
}

//====================================================================er
//		Menu de Comandos
//====================================================================

int Comandos(char*gravar, int* lc){
	while(1){
		
		char comandoint[30];
		int i,j;
		int aux;
		
		for(i=0;i!=30;i++){
			comandoint[i] = ' ';  
		}
	
		lc[0] = 0;
		lc[1] = 0;
		
		setbuf(stdin, NULL);
		
		printf("\nInsira o Comando: ");
		scanf("%[^\n]s",&comandoint);
		
		setbuf(stdin, NULL);
		
		
		if(comandoint[0] == 'P' && comandoint[1] == 'o' && comandoint[2] == 'w'){		//Comando Pow
		
			/*
			Nesta parte, o programa transforma o valor ditado no tipo char para o tipo int
			facilitando assim, o envio para a proxima função 
			*/
			
				for(i=4;i!=30;){
				
				if(comandoint[i]>=48 && comandoint[i]<=57){					//48 e 57 são os estremos de 0 a 9 na tabala ASCII
					
					aux = comandoint[i] - 48;								
					lc[0] = lc[0]*10;	
					lc[0] = lc[0] + aux;
					i++;
				}
				
				else if(comandoint[i]>=65 && comandoint[i]<=80){				//65 e 80 são os estremos de A a P na tabala ASCII
					aux = comandoint[i] - 65;
					lc[1] = aux;
					i++;
				}
				
				else
				i++;
			
			}
			
			lc[0]--;
			
			
			if(lc[0]<0 || lc[0]>15 || lc[1]<0 || lc[1]>15)
				goto erro;
			
			return 0;
		}
		else if(comandoint[0] == 'R' && comandoint[1] == 'e' && comandoint[2] == 's' && comandoint[3] == 'e' && comandoint[4] == 't') //Reset
			return	1;
		
		else if(comandoint[0] == 'S' && comandoint[1] == 'a' && comandoint[2] == 'i' && comandoint[3] == 'r') //Sair
			return	2;
		
		else if(comandoint[0] == 'A' && comandoint[1] == 'j' && comandoint[2] == 'u' && comandoint[3] == 'd' && comandoint[4] == 'a') //Ajuda
			return	3;
		
		else if(comandoint[0] == 'A' && comandoint[1] == 'c' && comandoint[2] == 'a' && comandoint[3] == 's' && comandoint[4] == 'o')	//Acaso
			return	4;
			
		else if(comandoint[0] == 'G' && comandoint[1] == 'r' && comandoint[2] == 'a' && comandoint[3] == 'v' && comandoint[4] == 'a' && comandoint[5] == 'r'){ //Gravar
		
			/*
				O programa aqui salva o nome do arquivo em uma nova sting
				que será enviada para fora do programa para ser usada de nome
				do arquivo salvo 
			*/
			
			for(i=7, j=0;i!=30;i++,j++){
					gravar[j] = comandoint[i];	
				}
			return	5;		
		}
			
				
		else if(comandoint[0] == 'C' && comandoint[1] == 'a' && comandoint[2] == 'r' && comandoint[3] == 'r' && comandoint[4] == 'e' && comandoint[5] == 'g' && comandoint[6] == 'a' && comandoint[7] == 'r'){ //Carregar
		
			/*
				O programa aqui salva o nome do arquivo em uma nova sting
				que será enviada para fora do programa para ser usada de nome
				do arquivo para o carregamento 
			*/
			
			for(i=9, j=0;i!=30;i++,j++){
					gravar[j] = comandoint[i];	
				}
			return	6;
		}
		
		else if	(comandoint[0] == 'M' && comandoint[1] == 'o' && comandoint[2] == 'd' && comandoint[3] == 'e' && comandoint[4] == ' ' && comandoint[5] == '1' && comandoint[6] == '2' && comandoint[7] == '3'){
			/*
				Rotina para desenvolvedores onde, todos os barcos ficam visiveis, 
				facilitando assim a localização de algum erro
			*/
			return 7;
		}
			
						
		else
erro:		printf("Digite novamente\n");
	}
}

//====================================================================
//		Comando Pow - Tiro
//====================================================================

int	Tiro(int dados[], int campo[16][16], char imgcampo[16][16], int* pontos, Barco* qa, int* pt){
	int linha,coluna;
	int aux;
	int i,j;
	int N=256;		// Numero total de casas do jogo
	int erro = 0;
	
	linha = dados[1];
	coluna = dados[0];
		
	aux = campo[coluna][linha];
	
	system("cls");
	
	/*
		Sempre que um lugar é selecionado o seu valor de indentificação é mudado
		para 5 para assim poder analizar a vitoria do jogo e, evitar que um jogador
		selecione o mesmo lugar duas vezes desperciando sua jogada.
	*/
	
	switch (aux){
		case 0: 
			printf("Tiro n'agua\n");
			imgcampo[coluna][linha] = 'X';			// Desenha tiro n'agua
			campo[coluna][linha] = 5;
			if(*pontos != 0){
				erro = (((N - *pt)*5)/N);
			}
			else 
				*pontos = *pontos - erro;
		break;
		
		case 1:
			printf("Belo disparo capitao\nTiro no porta-avioes\n");
			imgcampo[coluna][linha] = 'P';			// Desenha porta avião
			campo[coluna][linha] = 5;		
			*pontos = *pontos + (qa->pa*11*1000/N);
			qa->pa--;
			*pt--;	
		break; 	
		
		case 2:
			printf("Belo disparo capitao\nTiro no Couracado\n");
			imgcampo[coluna][linha] = 'C';			// Desenha couraçado
			campo[coluna][linha] = 5;
			*pontos = *pontos + (qa->co*10*1000/N);
			qa->co--;
			*pt--;
		break;
		
		case 3:
			printf("Belo disparo capitao\nTiro no Torpedeiro\n");
			imgcampo[coluna][linha] = 'T';			// Desenha torperdeiro		
			campo[coluna][linha] = 5;
			*pontos = *pontos + (qa->to*7*1000/N);
			qa->to--;
			*pt--;
		break;
		
		case 4:
			printf("Belo disparo capitao\nTiro no hidroaviao\n");
			imgcampo[coluna][linha] = 'H';			// Desenha hidroaviao1
			campo[coluna][linha] = 5;
			*pontos = *pontos + (qa->hi*8*1000/N);
			qa->hi--;
			*pt--;
		break;
		
		case 5:
			printf("Local ja Selecionado\n");
			sleep (2);
			return 1; 
		break;
	}
	
	sleep (2);
	
	
	for(i=0;i!=16;i++)
			for(j=0;j!=16;j++){
				aux = campo[i][j];
				if(aux == 1 || aux == 2 || aux == 3 || aux == 4)		//Verifica se ainda existe algum barco de pé
					return 0;
			}
			
	return 2;
}

//====================================================================
//		Gravar
//====================================================================

void Gravar(char* gravar, int* pontos1, int* pontos2, double* tempo, int* aux, int campo1[16][16], int campo2[16][16],  char imgcampo1[16][16], char imgcampo2[16][16]){
	
	int i,j;
	strcat(gravar, ".dat");
	FILE *arquivo = fopen(gravar,"wb");		//Cria o arquivo com o nome selecionado dentro da função Comandos
	
	if(arquivo == NULL){		//Verifica se o arquivo foi inicializado com sucesso	
		printf("ERRO!\n");
		return;
	}
	
	system("cls");
	printf("Gravando o Jogo...\n");
	
	/*
		Grava os valores requisitados no arquivo:
		Pontos 1 
		Pontos 2 
		Tempo 
		Vez do jogador
		Matriz de identificação do jogador 1
		Matriz de identificação do jogador 2
		Matriz de imagem do jogador 1
		Matriz de imagem do jogador 2
	*/
	
	fwrite(pontos1,sizeof(int),1,arquivo);
	fwrite(pontos2,sizeof(int),1,arquivo);
	fwrite(tempo,sizeof(double),1,arquivo);
	fwrite(aux,sizeof(int),1,arquivo);
	
	for(i=0;i!=16;i++)
		for(j=0;j!=16;j++){
			fwrite(&campo1[i][j],sizeof(int),1,arquivo);
	}
	
	for(i=0;i!=16;i++)
		for(j=0;j!=16;j++){
			fwrite(&campo2[i][j],sizeof(int),1,arquivo);
	}
	
	
	for(i=0;i!=16;i++){
		for(j=0;j!=16;j++){
			fprintf(arquivo,"%c",imgcampo1[i][j]);	
		}
	}
	
	
	for(i=0;i!=16;i++){
		for(j=0;j!=16;j++){
			fprintf(arquivo,"%c",imgcampo2[i][j]);	
		}
	}
	
	fclose(arquivo);
	
	printf("Salvo com Sucesso!\n");
	sleep(3);
	
	return;
}

//====================================================================
//		Carregar
//====================================================================

void	Carrega(char* gravar, int* pontos1, int* pontos2, double* tempo, int* aux, int campo1[16][16], int campo2[16][16],  char imgcampo1[16][16], char imgcampo2[16][16]){
	
	int i,j;
	strcat(gravar, ".dat");
	FILE *arquivo = fopen(gravar,"rb");		//Carregar o arquivo com o nome selecionado dentro da função Comandos
	
	if(arquivo == NULL){		//Verifica se o arquivo foi inicializado com sucesso
		printf("ERRO!\n");
		return;
	}
	
	system("cls");
	printf("Carregando o Jogo...\n");
	
	/*
		Carrega os valores salvos do arquivo:
		Pontos 1 
		Pontos 2 
		Tempo 
		Vez do jogador
		Matriz de identificação do jogador 1
		Matriz de identificação do jogador 2
		Matriz de imagem do jogador 1
		Matriz de imagem do jogador 2
	*/
	
	
	fread(pontos1,sizeof(int),1,arquivo);
	fread(pontos2,sizeof(int),1,arquivo);
	fread(tempo,sizeof(double),1,arquivo);
	fread(aux,sizeof(int),1,arquivo);
	
	for(i=0;i!=16;i++)
		for(j=0;j!=16;j++){
			fread(&campo1[i][j],sizeof(int),1,arquivo);
	}
	
	for(i=0;i!=16;i++)
		for(j=0;j!=16;j++){
			fread(&campo2[i][j],sizeof(int),1,arquivo);
	}
	
	for(i=0;i!=16;i++)
		for(j=0;j!=16;j++){
			imgcampo1[i][j] = fgetc(arquivo);
	}
	
	for(i=0;i!=16;i++)
		for(j=0;j!=16;j++){
			imgcampo2[i][j] = fgetc(arquivo);
	}
	
	fclose(arquivo);
	printf("Carregado com Sucesso!\n");
	sleep(3);
	
	return;

}

//====================================================================
//		Inicialização das matrizes
//====================================================================

void Iniciar_matrizes(int campo1[16][16],int campo2[16][16]){
		int i,j,iden;	
		
		for(i=0;i!=16;i++)
			for(j=0;j!=16;j++){
				campo1[i][j] = 0;
				campo2[i][j] = 0;
			}
		
		/*
			O programa adribui a cada barco uma identificação
			Cada identificação esta escrita no inicio do programa
		
		*/
		
		//porta avioes 
		iden = 1;
		Escrita_na_matriz(campo1,P,iden);			
		printf("Os Barcos estao saindo cais...\n");
		
		//couraçado
		iden = 2;
		for(i=0;i!=2;i++){
			Escrita_na_matriz(campo1,C,iden);
		}	
		printf("Os Couracados estao em posicao...\n");	
			
		//torpedeiro
		iden = 3;
		for(i=0;i!=3;i++){
			Escrita_na_matriz(campo1,T,iden);
		}	
		printf("Netuno esta do nosso lado...\n");	
			
		//hidroaviao
		iden = 4;
		for(i=0;i!=4;i++){
			Escrita_na_matriz(campo1,H,iden);
		}	
		printf("Os hidroavioes ja estao sobrevoando o local...\n");
		
		/*
			
			Teve que haver uma separação entre os dois barcos, pois como o selecionamento dos
			barcos é feito por um srand(time(NULL)) deixar os dois em seguida cria campos iguais
		
		*/
		
		//porta avioes 2 
		iden = 1;			
		Escrita_na_matriz(campo2,P,iden);
		printf("Porta-avioes zarpados...\n");
		
		//couraçado 2
		iden = 2;
		for(i=0;i!=2;i++){
			Escrita_na_matriz(campo2,C,iden);
		}	
		printf("Enimigo a vista...\n");	
			
		//torpedeiro 2
		iden = 3;
		for(i=0;i!=3;i++){
			Escrita_na_matriz(campo2,T,iden);
		}	
		printf("Confirmo a visao de Torpedeiros...\n");	
			
		//hidroaviao 2
		iden = 4;
		for(i=0;i!=4;i++){
			Escrita_na_matriz(campo2,H,iden);
		}	
		printf("A mare esta para peixe hoje...\n");
		
		sleep (2);
	}	



//====================================================================
//		Escrevendo na Matriz 
//====================================================================



void Escrita_na_matriz(int mat[16][16], int N, int iden){
	unsigned int x,y,vert_hor,pos_neg;
	int i,j,aux,aux2,n_char;

	
inicio:		
		n_char=0;
		aux = ALTO;
		aux2 = FLUTUANTE;
			
		srand(time(NULL));
		x = rand() %16;			//Seleciona um lugar aleatorio em X na matriz
		
		srand(time(NULL));
		y = rand() %16;			//Seleciona um lugar aleatorio em Y na matriz
		
		srand(time(NULL));
		vert_hor = rand() %2;	// Seleciona se a matriz sera escrita na vertical ou horizontal
	
		/*
			0 = horizontal  
			1 = vertical
		*/
				
hor:	if(vert_hor == 0){								//horizontal
			
			srand(time(NULL));
			pos_neg = rand() %2;	// Seleciona se a matriz sera escrita na direita ou esquerda					
		
			/*
				0 = direita    
				1 = esquerda 
			*/	
				
direita:			if(pos_neg == 0){					//direita
						for(i=y,j=0;j<N;i++,j++){
							if(mat[x][i] == 0 && i<16){
								if(aux2 != ALTO)
									n_char ++;
								
								/*
									Verifica inicioalmente se todos os lugares 
									na matriz estão disponiveis para a escrita do barco
								*/
								
								if(n_char == N){		//Reiniciando o for caso seja verdade
									j=0;
									i=y;
									n_char ++;
									aux2 = ALTO;
								}			
								
								if(n_char>= N){			//Escreve o barco
									mat[x][i] = iden; 
								}		
							}
							
							else{		//Caso o barco não consiga ocupar o espaço
							
								if(aux == BAIXO){
									if (aux2 == BAIXO && aux == BAIXO)
										/*
											Isso so sera verdadeiro caso
											o barco ja tenha tentado ir para esquerda, 
											direita, cima e baixo e em nenhum desas opções
											tenha dado certo para encaixar o barco
											Portanto sera selecionado um novo lugar na matriz
											para testes
										*/
										goto inicio;
									
									/*
										Inverte o sentido de horizontal para vertical
									*/	
									n_char=0;
									aux = ALTO;
									aux2 = BAIXO;								
									vert_hor = 1;	
									goto vert;
								}
								
								/*
									Inverte o sentido da direita para a esqueda
								*/	
								n_char=0;
								aux = BAIXO;
								pos_neg = 1;
								goto esquerda;
							}
						}	
					}
					
esquerda:			if(pos_neg == 1){					//esquerda
						for(i=y,j=0;j<N;i--,j++){
							if(mat[x][i] == 0 && i>=0){
								if(aux2 != ALTO)
									n_char ++;
									
								/*
									Verifica inicioalmente se todos os lugares 
									na matriz estão disponiveis para a escrita do barco
								*/	
												
								if(n_char == N){		//Reiniciando o for caso seja verdade
									j=0;
									i=y;
									n_char ++;
									aux2 = ALTO;
								}			
								
								if(n_char>= N){		
									mat[x][i] = iden;	//Escreve o barco
								}
							}
							else{		//Caso o barco não consiga ocupar o espaço
							
								if(aux == BAIXO){
									if (aux2 == BAIXO && aux == BAIXO)
										/*
											Isso so sera verdadeiro caso
											o barco ja tenha tentado ir para esquerda, 
											direita, cima e baixo e em nenhum desas opções
											tenha dado certo para encaixar o barco
											Portanto sera selecionado um novo lugar na matriz
											para testes
										*/									
										goto inicio;
										
									/*
										Inverte o sentido de horizontal para vertical
									*/		
									n_char=0;
									aux = ALTO;		
									aux2 = BAIXO;						
									vert_hor = 1;	
									goto vert;
								}
								
								/*
									Inverte o sentido da esqueda para a direita
								*/	
								n_char=0;
								aux = BAIXO;
								pos_neg = 0;
								goto direita; 
							}
						}	
					}				
		}
		
		
vert:	if(vert_hor == 1){								//vertical
			
			srand(time(NULL));
			pos_neg = rand() %2;						// Seleciona se a matriz sera escrita na cima ou baixo
			 
			/*
				0 = bbaixo    
				1 = cima 
			*/		
				
baixo:				if(pos_neg == 0){					//baixo
						for(i=x,j=0;j<N;i++,j++){
							if(mat[i][y] == 0 && i<16){
								if(aux2 != ALTO)
									n_char ++;
								
								/*
									Verifica inicioalmente se todos os lugares 
									na matriz estão disponiveis para a escrita do barco
								*/
								
								if(n_char == N){		//Reiniciando o for caso seja verdade
									j=0;
									i=x;
									n_char ++;
									aux2 = ALTO;
								}			
								
								if(n_char >= N){
									mat[i][y] = iden; 	//Escreve o barco
								}		
							}
							
							else{			//Caso o barco não consiga ocupar o espaço
							
								if(aux == BAIXO){
									if (aux2 == BAIXO && aux == BAIXO)
										/*
											Isso so sera verdadeiro caso
											o barco ja tenha tentado ir para esquerda, 
											direita, cima e baixo e em nenhum desas opções
											tenha dado certo para encaixar o barco
											Portanto sera selecionado um novo lugar na matriz
											para testes
										*/											
										goto inicio;
										
									/*
										Inverte o sentido de vertical para horizontal
									*/		
									n_char=0;
									aux = ALTO;
									aux2 = BAIXO;								
									vert_hor = 0;	
									goto hor;
								}
								
								/*
									Inverte o sentido de baixo para cima
								*/	
								n_char=0;
								aux = BAIXO;
								pos_neg = 1;
								goto cima; 
							}
						}	
					}
					
					
cima:				if(pos_neg == 1){					//cima
						for(i=x,j=0;j<N;i--,j++){
							if(mat[i][y] == 0 && i>=0){
								if(aux2 != ALTO)
									n_char ++;
							
								/*
									Verifica inicioalmente se todos os lugares 
									na matriz estão disponiveis para a escrita do barco
								*/
													
								if(n_char == N){		//Reiniciando o for caso seja verdade
									j=0;
									i=x;
									n_char ++;
									aux2 = ALTO;
								}			
								
								if(n_char >= N){
									mat[i][y] = iden;	//Escreve o barco
								}
							}
							else{		//Caso o barco não consiga ocupar o espaço

								if(aux == BAIXO){
									if (aux2 == BAIXO && aux == BAIXO)
										/*
											Isso so sera verdadeiro caso
											o barco ja tenha tentado ir para esquerda, 
											direita, cima e baixo e em nenhum desas opções
											tenha dado certo para encaixar o barco
											Portanto sera selecionado um novo lugar na matriz
											para testes
										*/	
										goto inicio;
									
									/*
										Inverte o sentido de vertical para horizontal
									*/	
									n_char=0;
									aux = ALTO;
									aux2 = BAIXO;								
									vert_hor = 0;	
									goto hor;
								}
								
								/*
									Inverte o sentido de cima para baixo
								*/	
								n_char=0;
								aux = BAIXO;
								pos_neg = 0;
								goto baixo;	 
							}	
						}
					}				
		}		
}

//====================================================================
//		Transformando os dados da matriz em imagem 
//====================================================================

void Trans(int campo[16][16],char imgcampo[16][16]){		// Função apenas para testes 
	int i,j;
	
	/*
		Função apenas para desenvolvedores.
		Com o acionamento desta todos os barcos 
		podem ser visiveis. 
		O comando para seu acionamento é Mode 123
	*/
	
	for(i=0;i!=16;i++)
		for(j=0;j!=16;j++)
		{
			if(campo[i][j] == 0)								// Desenha tiro n'agua	
				imgcampo[i][j] = ' ';
			
			if(campo[i][j] == 1)
				imgcampo[i][j] = 'P';							// Desenha porta avião
			
			if(campo[i][j] == 2)								
				imgcampo[i][j] = 'C';							// Desenha couraçado
				
			if(campo[i][j] == 3)								
				imgcampo[i][j] = 'T';							// Desenha torperdeiro
			
			if(campo[i][j] == 4)								
				imgcampo[i][j] = 'H';							// Desenha hidroaviao1
				
	}
		
	return;
}

//====================================================================
//		Desenhando o campo de batalha 
//====================================================================
	
void Matriz_imagem(int campo[16][16], int jogador,char imgcampo[16][16], int pontos, double tempo){			// Adiciona a imagem da matriz 
	int i,j,aux=1;
	int numero = 1;
	char letra = 'A';
	
	/*
		Apresenta a função de desenhar todo o campo de batalha 
		Usando para isso o campo de imagem, cujo mostra apenas 
		os lugares selecionados pelos jogadores.
	*/
	system("cls");

	
	printf("Tela do Jogador #%d  Pontos:%d  Time:%f\n",jogador,pontos,tempo);
	
	for(i=0;i!=16;i++){
		for (j=0;j!=16;j++)
			if(aux==1){
				printf("     %c  ",letra);
				letra++;	
			}
			
		aux=0;	
		printf("\n");
		
		for (j=0;j!=16;j++)
			printf("   +---+");
		
		
		printf("\n");
		
		printf("%d",numero);
		numero++;
		
		if(numero>10){
			for (j=0;j!=16;j++)
				printf(" | %c |  ",imgcampo[i][j]);		
			
		}else if(numero<=10){
			for (j=0;j!=16;j++)
				printf("  | %c | ",imgcampo[i][j]);		
		}
		
		printf("\n");
		
		for (j=0;j!=16;j++)
			printf("   +---+");
		
		printf("\n");
	}
}



