#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 25

int pontuacao=0;

struct var{

	int i, j, aux;
	char mapa[TAM][TAM];

};

void desenhar_mapa(char mapa[TAM][TAM]){
	int i, j;

	for(i=0; i<30; i++) printf("\n");	
	
	printf("Pontuaçao: %d\n", pontuacao);	
	for(i=0; i<TAM; i++){
		for(j=0; j<TAM; j++){
			printf("%c ", mapa[i][j]);
		}
		printf("\n");
	}
}

#include "progresso.c"
#include "criar_mapa.c"
#include "movimento.c"

int main(){
	
	int jogar=1;
	struct var variaveis;
	while(jogar){
				
		int posx, posy;
		char tecla;
		posx=posy=1;

		srand(time(NULL));// numero aleatorio

		/* preparar matriz */
		for(variaveis.i=0; variaveis.i<TAM; variaveis.i++){
			for(variaveis.j=0; variaveis.j<TAM; variaveis.j++){
				if((variaveis.i%2==0)||(variaveis.j%2==0)){
					variaveis.mapa[variaveis.i][variaveis.j]='w';
				}else{
					variaveis.mapa[variaveis.i][variaveis.j]='0';
				}
			}
		}

		if((TAM/2)%2==0)
			variaveis.i = variaveis.j = (TAM/2)-1;
		else
			variaveis.i = variaveis.j = TAM/2;
		
		criar_mapa(&variaveis);

		variaveis.mapa[1][1] = '#';
		variaveis.mapa[TAM-1][TAM-2] = '+';
		desenhar_mapa(variaveis.mapa);
		do{
			scanf("%c", &tecla);
			movimento(variaveis.mapa, tecla, &posx, &posy);
			desenhar_mapa(variaveis.mapa);
		}while((posx!=TAM-1)||(posy!=TAM-2));

		pontuacao++;
		puts("1-Novo Jogo\n0-Sair");
		getchar();
		do{
			scanf("%d", &jogar);
		}while((jogar<0)||(jogar>1));
	}
	return 0;
}
