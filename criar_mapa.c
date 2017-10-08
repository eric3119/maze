#define CIMA 0
#define BAIXO 1
#define ESQ 2
#define DIR 3

void verif_mapa(struct var *variaveis, int *disp){
	
	int k;
	
	for (k=0; k<4; k++) disp[k]=0;

	if (((variaveis->i)-2>0)&&(variaveis->mapa[(variaveis->i)-2][variaveis->j]=='0'))
		disp[ESQ]=1;	

	if(((variaveis->i)+2<TAM)&&(variaveis->mapa[(variaveis->i)+2][variaveis->j]=='0'))
		disp[DIR]=1;

	if((variaveis->j-2>0)&&(variaveis->mapa[(variaveis->i)][variaveis->j-2]=='0'))
		disp[CIMA]=1;

	if((variaveis->j+2<TAM)&&(variaveis->mapa[(variaveis->i)][variaveis->j+2]=='0'))
		disp[BAIXO]=1;
}

void criar_mapa(struct var *variaveis){

	int escolha, disp[4], k, prog, possDisp;

	variaveis->mapa[(variaveis->i)][variaveis->j]=' ';

	verif_mapa(variaveis, disp);
	desenhar_mapa(variaveis->mapa);
	progresso(variaveis->mapa);		

	do{
		possDisp=0;
		for(k=0; k<4; k++){
			possDisp+=disp[k];
		}

		if(possDisp==0)
			break;
		else if(possDisp<=2)
			variaveis->aux=4;

		for(k=0; k<4000000; k++);

		do{	// escolha do numero aleatorio
			escolha = rand()%4;
		}while(escolha == variaveis->aux);

		if((escolha==CIMA)&&disp[CIMA]){

			disp[CIMA]=0;
			variaveis->mapa[(variaveis->i)][variaveis->j-1]=' ';
				variaveis->aux = escolha;
				(variaveis->j)-=2;
				criar_mapa(variaveis);
				(variaveis->j)+=2;
		}
		if((escolha==BAIXO)&&disp[BAIXO]){

			disp[BAIXO]=0;
			variaveis->mapa[(variaveis->i)][variaveis->j+1]=' ';
				variaveis->aux = escolha;
				(variaveis->j)+=2;
				criar_mapa(variaveis);
				(variaveis->j)-=2;
		}
		if((escolha==ESQ)&&disp[ESQ]){

			disp[ESQ]=0;
			variaveis->mapa[((variaveis->i))-1][variaveis->j]=' ';
				variaveis->aux = escolha;
				((variaveis->i))-=2;
				criar_mapa(variaveis);
				((variaveis->i))+=2;
		}
		if((escolha==DIR)&&disp[DIR]){

			disp[DIR]=0;
			variaveis->mapa[(variaveis->i)+1][variaveis->j]=' ';
				variaveis->aux = escolha;
				(variaveis->i)+=2;
				criar_mapa(variaveis);
				(variaveis->i)-=2;
		}
		verif_mapa(variaveis, disp);		
	}while(disp[escolha]== 0);
}
