int saida = 0;

void caminho(int i, int j){
	
	if(i<0||i>TAM-1||j<0||j>TAM-1)return;

	if(mapa[i][j]=='@'||mapa[i][j]=='w')return;

	
	if(!saida){
		mapa[i][j]='@';
		caminho(i-1, j);
	
		caminho(i+1, j);

		caminho(i, j-1);

		caminho(i, j+1);
	}
	
	if((i+j!=2)&&(!saida))
			mapa[i][j]='x';
	else
		saida=1;
}