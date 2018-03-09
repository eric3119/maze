#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define CIMA 0
#define BAIXO 1
#define ESQ 2
#define DIR 3

float LARGURA_TELA;
float ALTURA_TELA;

int TAM=0;
float w;

const int tamFonte = 15;

int pontuacao=0, comp=0, sair=0;

char **mapa;

struct jogador{
   	int jogx, jogy;
};
typedef struct jogador jog;
struct dThread{
   	int posx, posy;
};

typedef struct dThread dThread;

int  inicAllegro();
void encerrar();
void verif_encerrar();

void desenhar_mapa(jog dados);
void atualizar_posicoes(dThread d1, jog dados);

void verif_mapa(int i, int j, int *disp);
void criar_mapa(int i, int j, int aux, jog dados);

void caminho(int i, int j);

void *movimento(ALLEGRO_THREAD *thr, void *arg);
int  movimento2(int tecla, jog *dados);

char **aloca_matriz();
void libera_matriz();
void escolher_tamanho();

#include "header/iniciar_encerrar.h"
#include "header/desenhar_mapa.h"
#include "header/criar_mapa.h"
#include "header/resposta.h"
#include "header/movimento.h"
#include "header/alocar.h"

int main(){
	jog dados;
	dThread d1;

	int jogar=1,			
		tecla,
		i, j, aux;	

	if(!inicAllegro()){
		return 0;
	}

	escolher_tamanho();
	
	srand(time(NULL));
	
	while(jogar){

		tecla=0;
		d1.posx = d1.posy = (TAM-2);
		dados.jogx = dados.jogy = 1;

		for(i=0; i<TAM; i++){
			for(j=0; j<TAM; j++){
				if((i%2==0)||(j%2==0)){
					mapa[i][j]='w';
				}else{
					mapa[i][j]='0';
				}
			}
		}

		if((TAM/2)%2==0)
			i = j = (TAM/2)-1;
		else
			i = j = TAM/2;
		
		criar_mapa(i, j, 4, dados);
		saida = 0;
		caminho(TAM-2, TAM-2);
		
		
		mapa[TAM-1][TAM-2] = '+';
		
		al_clear_to_color(al_map_rgb(0, 0, 0));
		desenhar_mapa(dados);
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
		desenhar_mapa(dados);
		al_flip_display();
		
	    sair=0;
	    tecla=-1;   		
	   		
    		al_save_bitmap("arquivo.png", al_get_backbuffer(janela));
    		fundo = al_load_bitmap("arquivo.png");

    		al_flush_event_queue(fila_eventos);	
	    	thread = al_create_thread(movimento, &d1);
    		al_start_thread(thread);

    	while(!sair){atualizar_posicoes(d1, dados);

	        while(!al_is_event_queue_empty(fila_eventos)){
	        	
	        	al_wait_for_event(fila_eventos, &evento);        		
			       	if(evento.type == ALLEGRO_EVENT_KEY_DOWN){		            			
				                switch(evento.keyboard.keycode){		                	
					                case ALLEGRO_KEY_UP:
					                    tecla = CIMA;
					                    break;
					                case ALLEGRO_KEY_DOWN:
					                    tecla = BAIXO;
					                    break;
					                case ALLEGRO_KEY_LEFT:
					                    tecla = ESQ;
					                    break;
					                case ALLEGRO_KEY_RIGHT:
					                    tecla = DIR;
					                    break;
					                case ALLEGRO_KEY_ESCAPE:
					                    jogar = 0;
					                    sair  = 1;					                    
					                    break;
				                }
		                	do{	atualizar_posicoes(d1, dados);
		                		if(!sair){
					             	sair = movimento2(tecla, &dados);
					            }	
					            al_flush_event_queue(fila_eventos);		        
								al_wait_for_event(fila_eventos, &evento);								
			                }while(evento.type != ALLEGRO_EVENT_KEY_UP);
		                	
		                }else if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
			            	jogar = 0;
			            	sair  = 1;
			            }
			            
		 				atualizar_posicoes(d1, dados);
	        }
	    }
	    al_destroy_thread(thread);
	    if(jogar){	    	
		    atualizar_posicoes(d1, dados);
		    al_draw_filled_rectangle((LARGURA_TELA/2)-150, (ALTURA_TELA/2)-20,
		    	(LARGURA_TELA/2)+150, (ALTURA_TELA/2)+20, al_map_rgb(255, 255, 255));
		    
		    al_draw_text(fonte,al_map_rgb(0, 0, 0),LARGURA_TELA/2,ALTURA_TELA/2-tamFonte,
	    		ALLEGRO_ALIGN_CENTRE,"Enter -> Continuar");
		    al_draw_text(fonte,al_map_rgb(0, 0, 0),LARGURA_TELA/2,ALTURA_TELA/2,
	    		ALLEGRO_ALIGN_CENTRE,"ESC -> Sair");
		    al_flip_display();
		
		    sair=0;	    
	    }else{
	    	sair=1;
	    }
	    al_flush_event_queue(fila_eventos);	
	    while(!sair){
		    
		    while(!al_is_event_queue_empty(fila_eventos)){
		            
		            al_wait_for_event(fila_eventos, &evento);
		 
		            if (evento.type == ALLEGRO_EVENT_KEY_DOWN){

		                switch(evento.keyboard.keycode){

			                case ALLEGRO_KEY_ENTER:
			                    jogar = 1;
			                    sair  = 1;			                    
			                    break;
			                case ALLEGRO_KEY_ESCAPE:
			                    sair  = 1;
			                    jogar = 0;
			                    break;
		                }
		            }else if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
		                sair  = 1;
		                jogar = 0;
		            }
		        }
	    }
	    al_destroy_bitmap(fundo);
	}
	libera_matriz();	
	al_destroy_audio_stream(musica);
	al_destroy_display(janela);	
    al_destroy_font(fonte);
    al_destroy_event_queue(fila_eventos);
    remove("arquivo.png");
	
	return 0;
}