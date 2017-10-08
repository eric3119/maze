void progresso(char matriz[TAM][TAM]){
  int i, j;
  float prog=0, a, b, c, porcent;

  for(i=0; i<TAM; i++){
    for(j=0; j<TAM; j++){
      if(matriz[i][j]=='0'){
        prog++;
      }
    }
  }  

  a = (int) (TAM/2) + 1;
  
  b = (int) (TAM/2);
  
  c = TAM;

  porcent = 100-(prog/((c*c)-(c*a)-(a*b)))*100;
  
  printf("%.2f%%\n", porcent); 
}
