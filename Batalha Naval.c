#include <stdio.h>

#define P 11		// Porta-avioes		qtd.1
#define C 11		// Couraçado		qtd.2 	
#define T 7			// Torpedeiros		qtd.3
#define H 8			// Hidroavioes		qtd.4

void  iniciar_matrizes(int campo1[16][16],int campo2 [16][16]);
void Ajuda(void);

int main(void){
	int aux;
	int campo1[16][16],campo2[16][16];

inicio:	
	printf("Bem Vindo a Batalha Naval!\n");		//inicio do programa 
	printf("Precione:\n1-Iniciar \n2-Ajuda\n3-Sair\n");
	scanf("%d",&aux);
	
	switch (aux){
		case 1:
			iniciar_matrizes(campo1,campo2);
			
		break;
		
		case 2:
			Ajuda();
			goto inicio;
		break;
		
		case 3:
			
		break;	
	}
}

void iniciar_matrizes(int campo1[16][16],int campo2[16][16]){
		
		
		
	}
	
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
