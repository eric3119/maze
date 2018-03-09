
    ALLEGRO_DISPLAY *janela = NULL;
    ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
    ALLEGRO_FONT *fonte = NULL;
    ALLEGRO_EVENT evento;
    ALLEGRO_MONITOR_INFO monitor;
    ALLEGRO_THREAD *thread = NULL;
    ALLEGRO_THREAD *threadmov = NULL;
    ALLEGRO_BITMAP *fundo = NULL;
    ALLEGRO_AUDIO_STREAM *musica = NULL;

int inicAllegro(){

	if (!al_init()){		
        fprintf(stderr, "erro al_init\n");
        return 0;
    }

    if (!al_init_primitives_addon()){
        fprintf(stderr, "erro al_init_primitives_addon\n");
        return 0;
    }
    if(!al_init_image_addon()){
        fprintf(stderr, "erro al_init_image_addon\n");
        return 0;
    }

    al_get_monitor_info(0 , &monitor);
    int desktop_width = monitor.x2 - monitor.x1;
    int desktop_height = monitor.y2 - monitor.y1;

    LARGURA_TELA = ALTURA_TELA = desktop_height-150;
    
    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    
    if (!janela){
        fprintf(stderr, "erro al_create_display\n");
        return 0;
    }

    fila_eventos = al_create_event_queue();

    if (!fila_eventos){

    	al_destroy_display(janela);
        fprintf(stderr, "erro al_create_event_queue\n");        
        return 0;
    }

    al_init_font_addon();

    if (!al_init_ttf_addon()){
        fprintf(stderr, "erro al_init_ttf_addon\n");
        return 0;
    }

    fonte = al_load_font("sndfnt/trheavy.ttf", tamFonte, 0);
    
    if (!fonte){
        al_destroy_display(janela);
        fprintf(stderr, "erro al_load_font\n");
        return 0;
    }

    if (!al_install_keyboard()){
        fprintf(stderr, "erro al_install_keyboard\n");
        return 0;
    }

    if (!al_install_audio())
    {
        fprintf(stderr, "erro al_install_audio\n");
        return 0;
    }
 
    if (!al_init_acodec_addon())
    {
        fprintf(stderr, "erro al_init_acodec_addon\n");
        return 0;
    }
    if (!al_reserve_samples(1))
    {
        fprintf(stderr, "erro al_reserve_samples\n");
        return false;
    }
    musica = al_load_audio_stream("sndfnt/sound.ogg", 3, 1024);
    if (!musica)
    {
        fprintf(stderr, "erro al_load_audio_stream\n");    
        return 0;
    } 
    
    al_hide_mouse_cursor(janela);
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));    

    al_set_window_position(janela, (desktop_width-LARGURA_TELA)/2, (desktop_height-ALTURA_TELA)/2);
    al_set_window_title(janela, "Labirinto");

    if(!al_attach_audio_stream_to_mixer(musica, al_get_default_mixer())){
        fprintf(stderr, "erro al_attach_audio_stream_to_mixer\n");
        return 0;
    }
    if(!al_set_audio_stream_playmode(musica,ALLEGRO_PLAYMODE_LOOP)){
        fprintf(stderr, "erro al_set_audio_stream_playmode\n");
        return 0;
    }
    //al_play_sample(musica, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);

    return 1;
}
void encerrar(){
    al_show_mouse_cursor(janela);
    if(al_show_native_message_box(NULL, "Labirinto","Sair","",
                NULL, ALLEGRO_MESSAGEBOX_OK_CANCEL)==1){

        libera_matriz();
        al_destroy_bitmap(fundo);
        al_destroy_display(janela);
        al_destroy_thread(thread);  
        al_destroy_font(fonte);
        al_destroy_event_queue(fila_eventos);
        remove("arquivo.png");

        exit(0);
    }
    al_hide_mouse_cursor(janela);
}

void verif_encerrar(){
    if(!al_is_event_queue_empty(fila_eventos)){

            al_wait_for_event(fila_eventos, &evento);
 
            if (evento.type == ALLEGRO_EVENT_KEY_DOWN){

                switch(evento.keyboard.keycode){
                    
                    case ALLEGRO_KEY_ESCAPE:
                        encerrar();
                    }
            }else if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                        encerrar();
            }
        }
}