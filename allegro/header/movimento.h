void *movimento(ALLEGRO_THREAD *thr, void *arg){
	dThread *d1 = (dThread*)arg;
	
	while(!sair){
			
			if((d1->posx==1)&&(d1->posy==1)){
				sair = 1;
				comp++;				
			}

		mapa[d1->posx][d1->posy] = ' ';
		
		if(mapa[d1->posx-1][d1->posy] == '@'){
			mapa[d1->posx-1][d1->posy] = ' ';
			d1->posx-=2;
		}else if(mapa[d1->posx][d1->posy-1] == '@'){
			mapa[d1->posx][d1->posy-1] = ' ';
			d1->posy-=2;
		}else if(mapa[d1->posx+1][d1->posy] == '@'){
			mapa[d1->posx+1][d1->posy] = ' ';
			d1->posx+=2;
		}else if(mapa[d1->posx][d1->posy+1] == '@'){
			mapa[d1->posx][d1->posy+1] = ' ';
			d1->posy+=2;
		}
		if(pontuacao<3)
			al_rest(0.6);
		else if(pontuacao<5)
			al_rest(0.3);
		else
			al_rest(0.27);

	}
	return NULL;
}

int movimento2(int tecla, jog *dados){
	
	mapa[dados->jogx][dados->jogy] = ' ';
	if((tecla==CIMA)&&(mapa[dados->jogx-1][dados->jogy] != 'w')){
		(dados->jogx)-=2;
	}else if((tecla==ESQ)&&(mapa[dados->jogx][dados->jogy-1] != 'w')){
		(dados->jogy)-=2;		
	}else if((tecla==BAIXO)&&(mapa[dados->jogx+1][dados->jogy] != 'w')){
		(dados->jogx)+=2;
	}else if((tecla==DIR)&&(mapa[dados->jogx][dados->jogy+1] != 'w')){
		(dados->jogy)+=2;
	}	
	if((dados->jogx==TAM-2)&&(dados->jogy==TAM-2)){		
	 	pontuacao++;
	 	return 1;		
	}
	return 0;
}