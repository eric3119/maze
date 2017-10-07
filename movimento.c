void movimento(char mapa[TAM][TAM], char tecla, int *posx, int *posy){

	if((tecla=='w')&&(mapa[*posx-1][*posy] != 'w')){
		mapa[*posx][*posy] = ' ';
		(*posx)--;
		mapa[*posx][*posy] = '#';
	}
	if((tecla=='a')&&(mapa[*posx][*posy-1] != 'w')){
		mapa[*posx][*posy] = ' ';
		(*posy)--;
		mapa[*posx][*posy] = '#';
	}
	if((tecla=='s')&&(mapa[*posx+1][*posy] != 'w')){
		mapa[*posx][*posy] = ' ';
		(*posx)++;
		mapa[*posx][*posy] = '#';
	}
	if((tecla=='d')&&(mapa[*posx][*posy+1] != 'w')){
		mapa[*posx][*posy] = ' ';
		(*posy)++;
		mapa[*posx][*posy] = '#';
	}
}