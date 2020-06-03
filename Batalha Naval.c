#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define P 11						// Porta-avioes		qtd.1		identificação 1
#define C 10						// Couraçado		qtd.2 		identificação 2
#define T 7							// Torpedeiros		qtd.3		identificação 3
#define H 8							// Hidroavioes		qtd.4		identificação 4					 
#define ALTO 1	
#define BAIXO 0
#define FLUTUANTE 3
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

int 	Menu_de_Inicio(void);																																//start do jogo para o usuario
int		Comandos(char* gravar, int* lc);																													//Le os comandos digitados		
void 	Ajuda(void);																																		//Abre o menu de Ajuda
void 	Iniciar_matrizes(int campo1[16][16],int campo2 [16][16]);																							//Randomiza os barcos 						
void	Matriz_imagem(int campo[16][16],int jogador, char imgcampo[16][16], int pontos, double tempo);														//Imprime o tabuleiro da batalha naval
void	Escrita_na_matriz(int mat[16][16], int N, int iden);																								//Aloca os barcos na matriz
void 	Trans(int campo[16][16],char imgcampo[16][16]);																										//Transforma os a matriz numerica em imagem
void	Snart(int campo[16][16],char imgcampo[16][16]);																										//Transforma os a matriz imagem em numerica
int 	Tiro(int dados[], int campo[16][16], char imgcampo[16][16], int *pontos, Barco* qa, int* pt);														//Exerce o tiro e abre as informações na tela
void	Gravar(char* gravar, int* pontos1, int* pontos2, int campo1[16][16], int campo2[16][16],  char imgcampo1[16][16], char imgcampo2[16][16]);			//Grava as informações do campo
void	Carrega(char* gravar, int* pontos1, int* pontos2, int campo1[16][16], int campo2[16][16], char imgcampo1[16][16], char imgcampo2[16][16]);			//Carrega as informações do campo

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

	
system("start music.mp3");
	
fim:
	aux = Menu_de_Inicio();
ret:	if(aux==1)	return 0;



rest:
	start_t = clock();
	pontos1 = 0;
	pontos2 = 0;
	
acaso:	
	Iniciar_matrizes(campo1,campo2);
	
	
	for(i=0;i!=16;i++)
		for(j=0;j!=16;j++){
			imgcampo1[i][j] = ' ';
				imgcampo2[i][j] = ' ';
		}
	
			
//	Trans(campo1,imgcampo1);
//	Trans(campo2,imgcampo2);
	
	int pt1 = 84,pt2 = 84;
	Barco qa1, qa2;						//Quantidade de peças de barcos							
	
	qa1.pa = 11;
	qa1.co = 20;
	qa1.to = 21;
	qa1.hi = 32;
	
	qa2.pa = 11;
	qa2.co = 20;
	qa2.to = 21;
	qa2.hi = 32;
		


		
		
		
	while(1){
ret1:	
		end_t = clock(); 
		tempo = end_t - start_t;
		tempo = tempo/CLOCKS_PER_SEC;
		

		Matriz_imagem(campo1,1,imgcampo1,pontos1,tempo);
		aux = Comandos(gravar, parametros);
		
		switch (aux){
			case 0:						//Tiro	
				aux = Tiro(parametros,campo1,imgcampo1,&pontos1,&qa1,&pt1);
				
				if(aux == 1)
					goto ret1;	 
				
				if(aux == 2){
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
				Gravar(gravar, &pontos1, &pontos2, campo1, campo2, imgcampo1, imgcampo2);
				goto ret1;
				break;
			
			case 6:						//Carregar
				Carrega(gravar, &pontos1, &pontos2, campo1, campo2, imgcampo1, imgcampo2);
				
				/*
				for (i=0;i!=16;i++){
					for (j=0;j!=16;j++){
						printf("%d",campo1[i][j]);
					}
					printf("\n");
				}
				sleep(10);
				*/
				
							
				goto ret1;
				break;	
		}

	
ret2:	
		end_t = clock(); 
		tempo = end_t - start_t;
		tempo = tempo/CLOCKS_PER_SEC;
		
		Matriz_imagem(campo2,2,imgcampo2,pontos2,tempo);
		aux = Comandos(gravar, parametros);
		
		switch (aux){
			case 0:						//Tiro	
				aux = Tiro(parametros,campo2,imgcampo2,&pontos2,&qa2,&pt2);
				
				if(aux == 1)
					goto ret2;	 
				
				if(aux == 2){
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
				Gravar(gravar, &pontos1, &pontos2, campo1, campo2, imgcampo1, imgcampo2);
				goto ret2;
				break;
			
			case 6:						//Carregar
				Carrega(gravar, &pontos1, &pontos2, campo1, campo2, imgcampo1, imgcampo2);
				
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
		
		
		if(comandoint[0] == 'P' && comandoint[1] == 'o' && comandoint[2] == 'w'){
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
		else if(comandoint[0] == 'R' && comandoint[1] == 'e' && comandoint[2] == 's' && comandoint[3] == 'e' && comandoint[4] == 't')
			return	1;
		
		else if(comandoint[0] == 'S' && comandoint[1] == 'a' && comandoint[2] == 'i' && comandoint[3] == 'r')
			return	2;
		
		else if(comandoint[0] == 'A' && comandoint[1] == 'j' && comandoint[2] == 'u' && comandoint[3] == 'd' && comandoint[4] == 'a')
			return	3;
		
		else if(comandoint[0] == 'A' && comandoint[1] == 'c' && comandoint[2] == 'a' && comandoint[3] == 's' && comandoint[4] == 'o')
			return	4;
			
		else if(comandoint[0] == 'G' && comandoint[1] == 'r' && comandoint[2] == 'a' && comandoint[3] == 'v' && comandoint[4] == 'a' && comandoint[5] == 'r'){
			for(i=7, j=0;i!=30;i++,j++){
					gravar[j] = comandoint[i];	
				}
			return	5;		
		}
			
				
		else if(comandoint[0] == 'C' && comandoint[1] == 'a' && comandoint[2] == 'r' && comandoint[3] == 'r' && comandoint[4] == 'e' && comandoint[5] == 'g' && comandoint[6] == 'a' && comandoint[7] == 'r'){
			for(i=9, j=0;i!=30;i++,j++){
					gravar[j] = comandoint[i];	
				}
			return	6;
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
				if(aux == 1 || aux == 2 || aux == 3 || aux == 4)		//Verigeica se ainda existe algum barco de pé
					return 0;
			}
			
	return 2;
}

//====================================================================
//		Gravar
//====================================================================

void Gravar(char* gravar, int* pontos1, int* pontos2, int campo1[16][16], int campo2[16][16],  char imgcampo1[16][16], char imgcampo2[16][16]){
	
	int i,j;
	strcat(gravar, ".dat");
	FILE *arquivo = fopen(gravar,"wb");
	
	if(arquivo == NULL){
		printf("ERRO!\n");
		return;
	}
	
	system("cls");
	printf("Gravando o Jogo...\n");
	
	fwrite(pontos1,sizeof(int),1,arquivo);
	fwrite(pontos2,sizeof(int),1,arquivo);
	
	
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
	//	fprintf(arquivo,"\n");
	}
	
	
	for(i=0;i!=16;i++){
		for(j=0;j!=16;j++){
			fprintf(arquivo,"%c",imgcampo2[i][j]);	
		}
	//	fprintf(arquivo,"\n");
	}
	
	fclose(arquivo);
	
	printf("Salvo com Sucesso!\n");
	sleep(3);
	
	return;
}

//====================================================================
//		Carregar
//====================================================================

void	Carrega(char* gravar, int* pontos1, int* pontos2, int campo1[16][16], int campo2[16][16],  char imgcampo1[16][16], char imgcampo2[16][16]){
	
	int i,j,aux;
	strcat(gravar, ".dat");
	FILE *arquivo = fopen(gravar,"rb");
	
	if(arquivo == NULL){
		printf("ERRO!\n");
		return;
	}
	
	system("cls");
	printf("Carregando o Jogo...\n");
	
	
	fread(pontos1,sizeof(int),1,arquivo);
	fread(pontos2,sizeof(int),1,arquivo);
	
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

void Trans(int campo[16][16],char imgcampo[16][16]){		// Função apenas para testes 
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
	
void Matriz_imagem(int campo[16][16], int jogador,char imgcampo[16][16], int pontos, double tempo){			// Adiciona a imagem da matriz 
	int i,j,aux=1;
	int numero = 1;
	char letra = 'A';
	
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



