void verif_mapa(int i, int j, int *disp){
	
	int k;
	
	for (k=0; k<4; k++) disp[k]=0;

	if ((i-2>0)&&(mapa[i-2][j]=='0'))
		disp[ESQ]=1;	

	if((i+2<TAM)&&(mapa[i+2][j]=='0'))
		disp[DIR]=1;

	if((j-2>0)&&(mapa[i][j-2]=='0'))
		disp[CIMA]=1;

	if((j+2<TAM)&&(mapa[i][j+2]=='0'))
		disp[BAIXO]=1;	
}

void criar_mapa(int i, int j, int aux, jog dados){
	
	int escolha, disp[4], k, loop=1, possDisp;

	mapa[i][j]='$';
	if((!pontuacao)&&(!comp)){
			al_clear_to_color(al_map_rgb(0, 0, 0));
			desenhar_mapa(dados);
			al_flip_display();			
		}
	verif_mapa(i, j, disp);
	
	while(loop){
		verif_encerrar();
		
		possDisp=0;		
		for(k=0; k<4; k++)possDisp+=disp[k];

		if(possDisp==0) loop=0;
		
		escolha = rand()%4;		

		if((escolha==CIMA)&&disp[CIMA]){
			mapa[i][j-1]=' ';
				aux = escolha;				
				criar_mapa(i, j-2, aux, dados);
		}
		else if((escolha==BAIXO)&&disp[BAIXO]){
			mapa[i][j+1]=' ';
				aux = escolha;
				criar_mapa(i, j+2, aux, dados);
		}
		else if((escolha==ESQ)&&disp[ESQ]){
			mapa[(i)-1][j]=' ';
				aux = escolha;
				criar_mapa(i-2, j, aux, dados);
		}
		else if((escolha==DIR)&&disp[DIR]){
			mapa[i+1][j]=' ';
				aux = escolha;
				criar_mapa(i+2, j, aux, dados);
		}
		verif_mapa(i, j, disp);
		if((!pontuacao)&&(!comp)){
			al_clear_to_color(al_map_rgb(0, 0, 0));
			desenhar_mapa(dados);			
			al_flip_display();			
		}
	};
	mapa[i][j]=' ';
}