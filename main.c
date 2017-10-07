#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int TAM, pontuacao=0;

/*struct teste{
	
	int i, j, aux, pontuacao=0;
	char mapa[TAM][TAM];

};*/

void desenhar_mapa(char mapa[TAM][TAM]);

#include "progresso.c"
#include "criar_mapa.c"
#include "movimento.c"

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


int main(){
	
	int jogar=1;

	while(jogar){

		do{
			puts("Digite um numero impar:");
			scanf("%d", &TAM);
		}while(TAM%2==0);// verificar numero par
		
		int i,j, posx, posy, aux=4;
		char mapa[TAM][TAM], tecla;

		srand(time(NULL));// numero aleatorio

		/* preparar matriz */
		for(i=0; i<TAM; i++){
			for(j=0; j<TAM; j++){
				if((i%2==0)||(j%2==0)){
					mapa[i][j]='w';
				}else{
					mapa[i][j]='0';
				}
			}
		}

		i=j=posx=posy=1;

		if((TAM/2)%2==0)
			i=j=(TAM/2)-1;
		else
			i=j=(TAM/2);
		printf("%d", i);

		criar_mapa(mapa, &i, &j, aux);

		mapa[1][1] = '#';
		mapa[TAM-1][TAM-2] = '+';
		desenhar_mapa(mapa);
		do{
			scanf("%c", &tecla);
			movimento(mapa, tecla, &posx, &posy);
			desenhar_mapa(mapa);
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