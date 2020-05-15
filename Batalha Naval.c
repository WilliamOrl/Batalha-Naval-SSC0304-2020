#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define P 11		// Porta-avioes		qtd.1		identificação 1
#define C 10		// Couraçado		qtd.2 		identificação 2
#define T 7			// Torpedeiros		qtd.3		identificação 3
#define H 8			// Hidroavioes		qtd.4		identificação 4
#define ALTO 1	
#define BAIXO 0
#define FLUTUANTE 3

//====================================================================
//		Lista de funções
//====================================================================

int 	Menu_de_Inicio(void);													//start do jogo para o usuario
int		Comandos(char*comando, int* lc);										//Le os comandos digitados		
void 	Ajuda(void);															//Abre o menu de Ajuda
void 	Iniciar_matrizes(int campo1[16][16],int campo2 [16][16]);				//Randomiza os barcos 						
void	Matriz_imagem(int campo[16][16],int jogador, char imgcampo[16][16]);	//Imprime o tabuleiro da batalha naval
void	Escrita_na_matriz(int mat[16][16], int N, int iden);					//Aloca os barcos na matriz
void 	Trans(int campo[16][16],char imgcampo[16][16]);							//Transforma os a matriz numerica em imagem
int 	Tiro(int dados[], int campo[16][16], char imgcampo[16][16]);
//====================================================================
//		Inicio
//====================================================================

int main(void){
	int aux,i,j;
	int campo1[16][16],campo2[16][16];
	char comando[30];
	char imgcampo1[16][16],imgcampo2[16][16];
	int parametros[2];
fim:
	for(i=0;i!=16;i++)
			for(j=0;j!=16;j++){
				imgcampo1[i][j] = ' ';
				imgcampo2[i][j] = ' ';
			}

	aux = Menu_de_Inicio();
ret:	if(aux==1)	return 0;

rest:
	Iniciar_matrizes(campo1,campo2);
	Trans(campo1,imgcampo1);
			
	while(1){
ret1:	Matriz_imagem(campo1,1,imgcampo1);
		aux = Comandos(comando, parametros);
		switch (aux){
			case 0:						//Tiro	
				aux = Tiro(parametros,campo1,imgcampo1);
				
				if(aux == 1)
					goto ret1;	 
				
				if(aux == 2){
					system("cls");
					printf("Parabens Jogador 1!!");
					goto fim;
				}
				break;
				
			case 1:						//Reset
				system("cls");
				printf("Reorganizando os barcos...\n");
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
		case 1:
			system("cls");
			printf("Preparando a Batalha...\n");
			return 0;		
		break;
		
		case 2:
			Ajuda();
			goto inicio;
		break;
		
		case 3:
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

//====================================================================
//		Menu de Comandos
//====================================================================

int Comandos(char*comando, int* lc){
	while(1){
		
		char comandoint[30];
		int i;
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
		
		
		if(comandoint[0] == 'P' && comandoint[1] == 'o' && comandoint[2] == 'w'){
			for(i=4;i!=30;){
				//printf("%c\n",comandoint[i]);
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
			
			//printf("linha = %d\ncoluna = %d",lc[0],lc[1]);
		//	sleep(5);
			if(lc[0]<0 || lc[0]>15 || lc[1]<0 || lc[1]>15)
				goto erro;
			
			return 0;
		}
		else if(comandoint[0] == 'R' && comandoint[1] == 'e' && comandoint[2] == 's' && comandoint[3] == 'e' && comandoint[4] == 't')
			return	1;
		
		else if(comandoint[0] == 'S' && comandoint[1] == 'a' && comandoint[2] == 'i' && comandoint[3] == 'r')
			return	2;
		
		else if(comandoint[0] == 'A' && comandoint[1] == 'j' && comandoint[2] == 'u' && comandoint[3] == 'd' && comandoint[4] == 'a')
			return	3;
		
		else if(comandoint[0] == 'A' && comandoint[1] == 'c' && comandoint[2] == 'a' && comandoint[3] == 's' && comandoint[4] == 'o')
			return	4;
					
		else
erro:		printf("Digite novamente\n");
	}
}

//====================================================================
//		Comando Pow - Tiro
//====================================================================

int	Tiro(int dados[], int campo[16][16], char imgcampo[16][16]){
	int linha,coluna;
	int aux;
	int i,j;
	
	linha = dados[1];
	coluna = dados[0];
		
	aux = campo[coluna][linha];
	
	system("cls");
	
	switch (aux){
		case 0: 
			printf("Tiro n'agua\n");
			imgcampo[coluna][linha] = 'X';			// Desenha tiro n'agua
			campo[coluna][linha] = 5;				
		break;
		
		case 1:
			printf("Tiro no porta-avioes\n");
			imgcampo[coluna][linha] = 'x';			// Desenha porta avião
			campo[coluna][linha] = 5;			
		break; 	
		
		case 2:
			printf("Tiro no Couracado\n");
			imgcampo[coluna][linha] = 'x';			// Desenha couraçado
			campo[coluna][linha] = 5;
		break;
		
		case 3:
			printf("Tiro no Torpedeiro\n");
			imgcampo[coluna][linha] = 'x';			// Desenha torperdeiro		
			campo[coluna][linha] = 5;
		break;
		
		case 4:
			printf("Tiro no hidroaviao\n");
			imgcampo[coluna][linha] = 'x';			// Desenha hidroaviao1
			campo[coluna][linha] = 5;
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
				if(aux == 1 || aux == 2 || aux == 3 || aux == 4)
					return 0;
			}
			
	return 2;
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

		//porta avioes 
		iden = 1;
		Escrita_na_matriz(campo1,P,iden);			
		printf("Porta-avioes zarpados...\n");
		
		//couraçado
		iden = 2;
		for(i=0;i!=2;i++)	
			Escrita_na_matriz(campo1,C,iden); 
		printf("Os Couracados estao em posicao...\n");	
			
		//torpedeiro
		iden = 3;
		for(i=0;i!=3;i++)	
			Escrita_na_matriz(campo1,T,iden); 
		printf("Confirmo a visao de Torpedeiros...\n");	
			
		//hidroaviao
		iden = 4;
		for(i=0;i!=4;i++)	
			Escrita_na_matriz(campo1,H,iden);
		printf("Os hidroavioes ja estao sobrevoando o local...\n");
		
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
		x = rand() %16;
		
		srand(time(NULL));
		y = rand() %16;
		
		srand(time(NULL));
		vert_hor = rand() %2;							//zero:horizontal//   //um:vertical//
		
				
hor:	if(vert_hor == 0){								//horizontal
			
			srand(time(NULL));
			pos_neg = rand() %2;						//zero: direta //     //um:esquerda// 
				
				
direita:			if(pos_neg == 0){					//direita
						for(i=y,j=0;j<N;i++,j++){
							if(mat[x][i] == 0 && i<16){
								if(aux2 != ALTO)
									n_char ++;
								
								if(n_char == N){		//Reiniciando o for
									j=0;
									i=y;
									n_char ++;
									aux2 = ALTO;
								}			
								
								if(n_char>= N){
									mat[x][i] = iden; 
								}		
							}
							
							else{
							
								if(aux == BAIXO){
									if (aux2 == BAIXO && aux == BAIXO)
										goto inicio;
									n_char=0;
									aux = ALTO;
									aux2 = BAIXO;								
									vert_hor = 1;	
									goto vert;
								}	
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
												
								if(n_char == N){		//Reiniciando o for
									j=0;
									i=y;
									n_char ++;
									aux2 = ALTO;
								}			
								
								if(n_char>= N){
									mat[x][i] = iden;
								}
							}
							else{
							
								if(aux == BAIXO){
									if (aux2 == BAIXO && aux == BAIXO)
										goto inicio;
									n_char=0;
									aux = ALTO;		
									aux2 = BAIXO;						
									vert_hor = 1;	
									goto vert;
								}
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
			pos_neg = rand() %2;						//zero: baixo      um:cima 
				
				
baixo:				if(pos_neg == 0){					//baixo
						for(i=x,j=0;j<N;i++,j++){
							if(mat[i][y] == 0 && i<16){
								if(aux2 != ALTO)
									n_char ++;
								
								if(n_char == N){		//Reiniciando o for
									j=0;
									i=x;
									n_char ++;
									aux2 = ALTO;
								}			
								
								if(n_char >= N){
									mat[i][y] = iden; 
								}		
							}
							
							else{
							
								if(aux == BAIXO){
									if (aux2 == BAIXO && aux == BAIXO)
										goto inicio;
									n_char=0;
									aux = ALTO;
									aux2 = BAIXO;								
									vert_hor = 0;	
									goto hor;
								}
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
												
								if(n_char == N){		//Reiniciando o for
									j=0;
									i=x;
									n_char ++;
									aux2 = ALTO;
								}			
								
								if(n_char >= N){
									mat[i][y] = iden;
								}
							}
							else{

								if(aux == BAIXO){
									if (aux2 == BAIXO && aux == BAIXO)
										goto inicio;
									n_char=0;
									aux = ALTO;
									aux2 = BAIXO;								
									vert_hor = 0;	
									goto hor;
								}
								n_char=0;
								aux = BAIXO;
								pos_neg = 0;
								goto baixo;	 
							}	
						}
					}				
		}		
//	return;	
}

//====================================================================
//		Transformando os dados da matriz em imagem 
//====================================================================

void Trans(int campo[16][16],char imgcampo[16][16]){		// Vai ter q mudar dps pq vai presiar do numero e da letra do tiro para revelar só aonde atirar 
	int i,j;
	
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
	
void Matriz_imagem(int campo[16][16], int jogador,char imgcampo[16][16]){			// Adiciona a imagem da matriz 
	int i,j,aux=1;
	int numero = 1;
	char letra = 'A';
	
	system("cls");

	
	printf("Tela do Jogador #%d\n",jogador);
	
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



