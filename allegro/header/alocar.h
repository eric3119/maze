char **aloca_matriz(){
	int i;
  	char** matriz = (char**)calloc(TAM, sizeof(char*));

  	for (i=0; i<TAM; i++){
		matriz[i] = (char*)calloc(TAM, sizeof(char));
	}

  	return matriz;
}

void libera_matriz(){
	int i;
	for (i=0; i<TAM; i++){
		free(mapa[i]);
	}
	free(mapa);
}
void escolher_tamanho(){
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_text(fonte,al_map_rgb(255, 255, 255),LARGURA_TELA/2,ALTURA_TELA/2-4*tamFonte,
	    		ALLEGRO_ALIGN_CENTRE,"Tamanho");
	al_draw_text(fonte,al_map_rgb(255, 255, 255),LARGURA_TELA/2,ALTURA_TELA/2-2*tamFonte,
	    		ALLEGRO_ALIGN_CENTRE,"1- 25x25");
	al_draw_text(fonte,al_map_rgb(255, 255, 255),LARGURA_TELA/2,ALTURA_TELA/2,
	    		ALLEGRO_ALIGN_CENTRE,"2- 35x35");
	al_draw_text(fonte,al_map_rgb(255, 255, 255),LARGURA_TELA/2,ALTURA_TELA/2+2*tamFonte,
	    		ALLEGRO_ALIGN_CENTRE,"3- 47x47");
	al_flip_display();
	do{
		al_wait_for_event(fila_eventos, &evento);        		
		
		if(evento.type == ALLEGRO_EVENT_KEY_DOWN){	            	
		
			switch(evento.keyboard.keycode){
				case ALLEGRO_KEY_1:
				case ALLEGRO_KEY_PAD_1:
					TAM = 25;
					w 	= 35;
					break;
				case ALLEGRO_KEY_2:
				case ALLEGRO_KEY_PAD_2:
					TAM = 35;
					w 	= 30;
					break;
				case ALLEGRO_KEY_3:
				case ALLEGRO_KEY_PAD_3:
					TAM = 47;
					w 	= 22;
					break;
				case ALLEGRO_KEY_ESCAPE:
				al_show_mouse_cursor(janela);
				if(al_show_native_message_box(NULL, "Labirinto","Sair","",
                NULL, ALLEGRO_MESSAGEBOX_OK_CANCEL)==1){
						al_destroy_display(janela);
						al_destroy_thread(thread);	
					    al_destroy_font(fonte);
					    al_destroy_event_queue(fila_eventos);

					exit(0);
				}
				al_hide_mouse_cursor(janela);
				break;
				default:
				al_show_native_message_box(NULL, "Labirinto",
                "Erro", "Opção não existe",
                NULL, ALLEGRO_MESSAGEBOX_ERROR);					
			}
		}		
	}while(TAM==0);

	mapa = aloca_matriz();
}