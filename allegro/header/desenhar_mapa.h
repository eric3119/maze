void desenhar_mapa(jog dados){
	int i, j;
    float v1= (2*ALTURA_TELA -(float)TAM*w)/(4*w), 
    	  v2= (2*LARGURA_TELA -(float)TAM*w)/(4*w),
    	  x, y;    
       	
       	al_draw_textf(fonte,al_map_rgb(255, 255, 255),LARGURA_TELA/2,1,
    	ALLEGRO_ALIGN_CENTRE,"Pontuaçao %d x %d",pontuacao, comp);


	    for(i=1;i<TAM; i+=2){
	        for(j=1;j<TAM; j+=2){
	            x = (v1*w);
	            y = (v2*w);

	            if(mapa[i][j]=='$')
	            	al_draw_filled_rectangle(x-1, y-1, (x+w)-1, (y+w)-1, al_map_rgb(255, 150, 100));

	            if(mapa[i-1][j]=='w'){
	                al_draw_line(x, y, x+w, y, al_map_rgb(0, 230, 255), 2.0);
	            }
	            if(mapa[i+1][j]=='w'){
	                al_draw_line(x, y+w, x+w, y+w, al_map_rgb(0, 230, 255), 2.0);
	            }
	            if(mapa[i][j-1]=='w'){
	                al_draw_line(x, y, x, y+w, al_map_rgb(0, 230, 255), 2.0);
	            }
	            if(mapa[i][j+1]=='w'){
	                al_draw_line(x+w, y, x+w, y+w, al_map_rgb(0, 230, 255), 2.0);
	            }
	            v1++;
	        }
	        v2++;
	        v1=(2*ALTURA_TELA -(float)TAM*w)/(4*w);
	    }    
}

void atualizar_posicoes(dThread d1, jog dados){
	float posx, posy, jogy, jogx;

	posx = d1.posx-1; 	posy = d1.posy-1;	
	posx/=2;	posy/=2;

	jogy = dados.jogy-1; 	jogx = dados.jogx-1;
	jogy/=2;	jogx/=2;	

    float v1= (2*ALTURA_TELA -(float)TAM*w)/(4*w), 
    	  v2= (2*LARGURA_TELA -(float)TAM*w)/(4*w),
    	  x, y;

	al_draw_bitmap(fundo, 0, 0, 0); 

	v1+=jogy;
   	v2+=jogx;

   	x = (v1*w);
	y = (v2*w);

   	al_draw_filled_rectangle(x, y, (x+w), (y+w), al_map_rgb(150, 150, 150));
	
	v1-=jogy;
	v2-=jogx;    	
	
	v1+=posy;
	v2+=posx;
	
	x = (v1*w);
	y = (v2*w);

   	al_draw_filled_rectangle(x-1, y-1, (x+w)-1, (y+w)-1, al_map_rgb(40, 150, 40));
   	al_flip_display();
}