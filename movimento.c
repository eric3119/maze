void movimento(char matriz[TAM][TAM], char tecla, int *posx, int *posy){

	if((tecla=='w')&&(matriz[*posx-1][*posy] != 'w')){
		matriz[*posx][*posy] = ' ';
		(*posx)--;
		matriz[*posx][*posy] = '#';
	}
	if((tecla=='a')&&(matriz[*posx][*posy-1] != 'w')){
		matriz[*posx][*posy] = ' ';
		(*posy)--;
		matriz[*posx][*posy] = '#';
	}
	if((tecla=='s')&&(matriz[*posx+1][*posy] != 'w')){
		matriz[*posx][*posy] = ' ';
		(*posx)++;
		matriz[*posx][*posy] = '#';
	}
	if((tecla=='d')&&(matriz[*posx][*posy+1] != 'w')){
		matriz[*posx][*posy] = ' ';
		(*posy)++;
		matriz[*posx][*posy] = '#';
	}
}
