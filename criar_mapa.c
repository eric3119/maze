#define CIMA 0
#define BAIXO 1
#define ESQ 2
#define DIR 3

void verif_mapa(char mapa[TAM][TAM], int *i, int *j, int *disp){
	
	int k;
	
	for (k=0; k<4; k++) disp[k]=0;

	if ((*i-2>0)&&(mapa[*i-2][*j]=='0'))
		disp[ESQ]=1;	

	if((*i+2<TAM)&&(mapa[*i+2][*j]=='0'))
		disp[DIR]=1;

	if((*j-2>0)&&(mapa[*i][*j-2]=='0'))
		disp[CIMA]=1;

	if((*j+2<TAM)&&(mapa[*i][*j+2]=='0'))
		disp[BAIXO]=1;
}

void criar_mapa(char mapa[TAM][TAM], int *i, int *j, int aux){

	int escolha, disp[4], k, prog, possDisp;

	mapa[*i][*j]=' ';

	verif_mapa(mapa, i, j, disp);
	desenhar_mapa(mapa);
	progresso(mapa);		

	do{
		possDisp=0;
		for(k=0; k<4; k++){
			possDisp+=disp[k];
		}

		if(possDisp==0)
			break;
		else if(possDisp<=2)
			aux=4;

		for(k=0; k<4000000; k++);

		do{	
			escolha = rand()%4;
		}while(escolha == aux);

		if((escolha==CIMA)&&disp[CIMA]){

			disp[CIMA]=0;
			mapa[*i][*j-1]=' ';
				aux = escolha;
				(*j)-=2;
				criar_mapa(mapa, i, j, aux);
				(*j)+=2;
		}
		if((escolha==BAIXO)&&disp[BAIXO]){

			disp[BAIXO]=0;
			mapa[*i][*j+1]=' ';
				aux = escolha;
				(*j)+=2;
				criar_mapa(mapa, i, j, aux);
				(*j)-=2;
		}
		if((escolha==ESQ)&&disp[ESQ]){

			disp[ESQ]=0;
			mapa[*i-1][*j]=' ';
				aux = escolha;
				(*i)-=2;
				criar_mapa(mapa, i, j, aux);
				(*i)+=2;
		}
		if((escolha==DIR)&&disp[DIR]){

			disp[DIR]=0;
			mapa[*i+1][*j]=' ';
				aux = escolha;
				(*i)+=2;
				criar_mapa(mapa, i, j, aux);
				(*i)-=2;
		}
		verif_mapa(mapa, i, j, disp);		
	}while(disp[escolha]== 0);
}