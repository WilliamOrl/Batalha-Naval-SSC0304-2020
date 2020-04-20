#include <stdio.h>

#define P 11		// Porta-avioes		qtd.1
#define C 11		// Couraçado		qtd.2 	
#define T 7			// Torpedeiros		qtd.3
#define H 8			// Hidroavioes		qtd.4

int 	Menu_de_Inicio(void);
void	Comandos(void);
void 	Iniciar_matrizes(int campo1[16][16],int campo2 [16][16]);
void 	Ajuda(void);
void	Matriz_imagem(int campo[16][16],int jogador);


int main(void){
	int aux;
	int campo1[16][16],campo2[16][16];
	
	aux = Menu_de_Inicio();
		if(aux==1)	return 0;
		
	while(1){
		Matriz_imagem(campo1,1);
		Comandos();
	}
}

//====================================================================
//		Menu de Inicio
//====================================================================

int	Menu_de_Inicio(void){
	int aux;	

inicio:	
	printf("Bem Vindo a Batalha Naval!\n");		//inicio do programa 
	printf("Precione:\n1-Iniciar \n2-Ajuda\n3-Sair\n");
	scanf("%d",&aux);
	
	switch (aux){
		case 1:
			//iniciar_matrizes(campo1,campo2);
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

void Comandos(void){
	char comando [10];
	printf("\nInsira o Comando:");
	scanf("%s",&comando);
	return;
}

//====================================================================
//		Inicializaca das matrizes
//====================================================================

void Iniciar_matrizes(int campo1[16][16],int campo2[16][16]){
			
	}	

//====================================================================
//		Desenhando as o campo de batalha 
//====================================================================
	
void Matriz_imagem(int campo[16][16], int jogador){			// Adiciona a imagem da matriz 
	int i,j,aux=1;
	int numero = 1;
	char letra = 'A';
	char imagem_campo[16][16];
	
	system("cls");
	/*	
	for(i=0;i!=16;i++)
		for (j=0;i!=16;j++)
	 		imagem_campo[i][j] = '0';
	*/
	
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
				printf(" |   |  "/*,imagem_campo[i][j]*/);		//add o %c dentro das chaves
			
		}else if(numero<=10){
			for (j=0;j!=16;j++)
				printf("  |   | "/*,imagem_campo[i][j]*/);		//add o %c dentro das chaves
		}
		
		printf("\n");
		
		for (j=0;j!=16;j++)
			printf("   +---+");
		
		printf("\n");
	}
}



