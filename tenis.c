#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <stdlib.h>

#define VEL_JOGADOR 10.0
#define MAX_BOLINHAS 12

const float FPS = 100;  

const int SCREEN_W = 900;
const int SCREEN_H = 700;

const int JOGADOR_W = 100;
const int JOGADOR_H = 50;

//------------Structs-------------

typedef struct Jogador{
	float x, y;
	float vel;
	int up, left, right, down;
	ALLEGRO_COLOR cor;
} Jogador;

typedef struct Bolinha{
	float x;
	float y;
	float r;
	float varx;
	float vary;
	int num;
	int naTela;
	ALLEGRO_COLOR cor;
} Bolinha;

//----------Relativo aos jogadores---------------

//inicia um jogador
void initJogador(Jogador *jogador){
	jogador->x = SCREEN_W/2 - 50;
	jogador->y = SCREEN_H - 50;
	jogador->vel = VEL_JOGADOR;
	jogador->up = 0;
	jogador->down = 0;
	jogador->left = 0;
	jogador->right = 0;
	jogador->cor = al_map_rgb(rand()%255, rand()%255, rand()%255);
}

//cria um segundo jogador
void jogador2(Jogador *jogador){
	jogador->y = 0;
}

//desenha os jogadores
void drawJogador(Jogador *jogador){
	al_draw_filled_rectangle(jogador->x, jogador->y, 
							jogador->x + JOGADOR_W, jogador->y + JOGADOR_H,
							jogador->cor);
}

//atualiza a posicao dos jogadores(permite movimentar)
void updateJogador(Jogador jogadores[], int i) {
	if(i == 0){
		if(jogadores[0].up && jogadores[0].y > SCREEN_H/2 + JOGADOR_H) {
			jogadores[0].y -= jogadores[0].vel;
		}if(jogadores[0].down && jogadores[0].y < SCREEN_H - JOGADOR_H){
			jogadores[0].y += jogadores[0].vel;
		}if(jogadores[0].left && jogadores[0].x > 0){
				jogadores[0].x -= jogadores[0].vel;
		}if(jogadores[0].right && jogadores[0].x < SCREEN_W - JOGADOR_W){
				jogadores[0].x += jogadores[0].vel;
		}
	}else{
		if(jogadores[1].up && jogadores[1].y > 0) {
			jogadores[1].y -= jogadores[1].vel;
		}if(jogadores[1].down && jogadores[1].y < SCREEN_H/2 - JOGADOR_H*2){
			jogadores[1].y += jogadores[1].vel;
		}if(jogadores[1].left && jogadores[1].x > 0){
			jogadores[1].x -= jogadores[1].vel;
		}if(jogadores[1].right && jogadores[1].x < SCREEN_W - JOGADOR_W){
			jogadores[1].x += jogadores[1].vel;
		}
	}
}

//Desenho do cenário

void desenharCenario(){
	//Colore a tela de verde
	al_clear_to_color(al_map_rgb(0, 195, 0));
	//Desenho das linhas horizontais do campo
	al_draw_line(50, 600, 850, 600,
				al_map_rgb(255,255,255), 4.0);
	al_draw_line(50, 100, 850, 100,
				al_map_rgb(255,255,255), 4.0);
	al_draw_line(0, SCREEN_H/2, SCREEN_W, SCREEN_H/2,
				al_map_rgb(255,255,255), 8.0);
	//Desenho das linhas verticais do campo
	al_draw_line(50, 0, 50, SCREEN_H,
				al_map_rgb(255,255,255), 4.0);
	al_draw_line(850, 0, 850, SCREEN_H,
				al_map_rgb(255,255,255), 4.0);
	al_draw_line(SCREEN_W/2, 100, SCREEN_W/2, 600,
				al_map_rgb(255,255,255), 4.0);
}

//-------------------Monitorar as bolinhas----------------------

//Funcao que cria uma bolinha "coringa"
void criaBolinha(Bolinha *bolinha, int count_bolinhas){
			bolinha->x = 0;
			bolinha->y = 0;
			bolinha->r = 5 + rand()%11;
			bolinha->varx = 0;
			bolinha->vary = 0;
			bolinha->num = count_bolinhas;
}

//Funcao que define como serao e de onde sairao as bolinhas
void posicaoBolinha(Bolinha *bolinha, int prox_bolinha){
	switch(prox_bolinha){
		case 0:
			bolinha->x = SCREEN_W;
			bolinha->y = 0;
			bolinha->varx = -3;
			bolinha->vary = 3;
			bolinha->naTela = 1;
			bolinha->cor = al_map_rgb(255, 0, 0);
		break;
		case 1:
			bolinha->x = 0;
			bolinha->y = 0;
			bolinha->varx = 3;
			bolinha->vary = 3;
			bolinha->naTela = 1;
			bolinha->cor = al_map_rgb(0, 255, 0);
		break;
		case 2:
			bolinha->x = 0;
			bolinha->y = SCREEN_H;
			bolinha->varx = 3;
			bolinha->vary = -3;
			bolinha->naTela = 1;
			bolinha->cor = al_map_rgb(0, 0, 255);
		break;
		case 3:
			bolinha->x = SCREEN_W;
			bolinha->y = SCREEN_H;
			bolinha->varx = -3;
			bolinha->vary = -3;
			bolinha->naTela = 1;
			bolinha->cor = al_map_rgb(0, 0, 0);
		break;
	}
}

void removeBolinha(int *bolinhas_tela){
	(*bolinhas_tela)--;
}

void apareceNaTela(int *bolinhas_tela){
	(*bolinhas_tela)++;
}

//solta a bolinha na tela
void vemNaTela(int *count_bolinhas){
	(*count_bolinhas)++;
}

//solta a proxima bolinha na tela
void vemProxima(int *prox_bolinha){
	if((*prox_bolinha) >= 3){
		(*prox_bolinha) = 0;
	}else{
		(*prox_bolinha)++;
	}
}

//contador para impedir mais do que o limite de bolinhas
void flowCount(int *count_r){
	if((*count_r) >=11){
		(*count_r) = 0;
	}else{
		(*count_r)++;
	}
}

//recoloca uma bolinha na tela caso o numero maximo de bolinhas nao tenha sido atingido
void respawnBolinha(Bolinha bolinhas[], int prox_bolinha, int count_r){
	int count = 0;
	for(int i = count_r; i < MAX_BOLINHAS; i++){
		if(bolinhas[i].naTela == 0 && count == 0){
			posicaoBolinha(&bolinhas[i], prox_bolinha);
			count++;
		}else{
			continue;
		}
	}
}

//Funcao que detecta se a bolinha esta ou nao na tela
int screenDetection(Bolinha *bolinha){
	if(bolinha->y > SCREEN_H || bolinha->y < SCREEN_H){
		bolinha->naTela = 0;
	}else{
		bolinha->naTela = 1;
	}
}

//------------Tratativas das bolinhas--------------------

void drawnBolinha(Bolinha *bolinha) {
	al_draw_filled_circle(bolinha->x, bolinha->y, 
							bolinha->r, 
							bolinha->cor);
}

void colisaoComParede(Bolinha *bolinha, int bolinhas_tela){
	if(bolinha->x > SCREEN_W || bolinha->x < 0){
		bolinha->varx = -bolinha->varx;
	}
}

//movimentacao da bolinha
void updateBolinha(Bolinha *bolinha){
	bolinha->x += bolinha->varx;
	bolinha->y += bolinha->vary;
}

//colisoes mais dinamicas no eixo x
float flowBolinhaAxis(int aux_x) {
	int s=1;
	if(aux_x < 0) s=-1;
	aux_x = aux_x * (0.25 + 2*(float)rand()/RAND_MAX);
	if(s * aux_x < 2)
		aux_x = 2*s;
	else if(s * aux_x > 2 && s * aux_x < 10)
		aux_x = 8*s;
	else if(s * aux_x > 10)
		aux_x = 10*s;
	return aux_x;
}

//colisoes mais dinamicas no eixo y
float flowBolinhaY(int aux_y) {
	int s=1;
	if(aux_y < 0) s=-1;
	aux_y = aux_y*(0.25+1.1*(float)rand()/RAND_MAX);
	if(s*aux_y < 2)
		aux_y = 2*s;
	else if(s*aux_y > 2 && s*aux_y < 10)
		aux_y = 8*s;
	else if(s*aux_y > 10)
		aux_y = 10*s;
	return -aux_y;
}

//--------------------------------------Colisao das bolinhas e jogadores--------------------------------------------

void colisaoJogadorBolinha(Bolinha *bolinha, Jogador jogadores[], int j, ALLEGRO_EVENT ev){
	switch (ev.keyboard.keycode){
		case ALLEGRO_KEY_M:
					if(bolinha->x <= jogadores[0].x + JOGADOR_W && bolinha->x >= jogadores[0].x && bolinha->y <= jogadores[0].y + JOGADOR_H && bolinha->y + bolinha->r >= jogadores[0].y && bolinha->vary > 0){
						float aux_x = bolinha->varx;
						float aux_y = bolinha->vary;
						bolinha->varx = 0;
						bolinha->vary = 0;
						bolinha->varx = flowBolinhaAxis(aux_x);
						bolinha->vary = flowBolinhaY(aux_y);
						if(bolinha->vary > 0){
							bolinha->vary *= -1;
						}
					}
		break;
		case ALLEGRO_KEY_C:
					if(bolinha->x <= jogadores[1].x + JOGADOR_W && bolinha->x >= jogadores[1].x && bolinha->y <= jogadores[1].y + JOGADOR_H && bolinha->y + bolinha->r >= jogadores[1].y && bolinha->vary < 0){
						float aux_x = bolinha->varx;
						float aux_y = bolinha->vary;
						bolinha->varx = 0;
						bolinha->vary = 0;
						bolinha->varx = flowBolinhaAxis(aux_x);
						bolinha->vary = flowBolinhaY(aux_y);
						if(bolinha->vary < 0){
							bolinha->vary *= -1;
						}
					}
		break;
	}
}

int main(int argc, char **argv){

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
   
	//----------------------- rotinas de inicializacao ---------------------------------------
    
	//inicializa o Allegro
	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}
 
	//cria uma tela com dimensoes de SCREEN_W, SCREEN_H pixels
	display = al_create_display(SCREEN_W, SCREEN_H);
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}

	//inicializa o módulo de primitivas do Allegro
    if(!al_init_primitives_addon()){
		fprintf(stderr, "failed to initialize primitives!\n");
        return -1;
    }	

	//cria um temporizador que incrementa uma unidade a cada 1.0/FPS segundos
    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}

	//instala o teclado
	if(!al_install_keyboard()) {
		fprintf(stderr, "failed to install keyboard!\n");
		return -1;
	}
	
	//instala o mouse
	if(!al_install_mouse()) {
		fprintf(stderr, "failed to initialize mouse!\n");
		return -1;
	}

	//inicializa o modulo allegro que carrega as fontes
	al_init_font_addon();

	//inicializa o modulo allegro que entende arquivos tff de fontes
	if(!al_init_ttf_addon()) {
		fprintf(stderr, "failed to load tff font module!\n");
		return -1;
	}
	
	//carrega o arquivo arial.ttf da fonte Arial e define que sera usado o tamanho 32 (segundo parametro)
    ALLEGRO_FONT *text = al_load_font("arial.ttf", 32, 1);   
	if(text == NULL) {
		fprintf(stderr, "font file does not exist or cannot be accessed!\n");
	}

 	//cria a fila de eventos
	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		return -1;
	}
   


	//registra na fila os eventos de tela (ex: clicar no X na janela)
	al_register_event_source(event_queue, al_get_display_event_source(display));
	//registra na fila os eventos de tempo: quando o tempo altera de t para t+1
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	//registra na fila os eventos de teclado (ex: pressionar uma tecla)
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	//registra na fila os eventos de mouse (ex: clicar em um botao do mouse)
	al_register_event_source(event_queue, al_get_mouse_event_source());  

	int count_bolinhas = 0, prox_bolinha = 0, bolinhas_tela = 0, pts_jog1 = 0, pts_jog2 = 0, count_r = 0, seconds = 0;

	Jogador jogadores[2];
	for (int i = 0; i<2; i++){
		initJogador(&jogadores[i]);
	}
	
	jogador2(&jogadores[1]);

	Bolinha bolinhas[MAX_BOLINHAS];

	int playing = 1;
	//inicia o temporizador
	al_start_timer(timer);
	while(playing){
		ALLEGRO_EVENT ev;
		//espera por um evento e o armazena na variavel de evento ev
		al_wait_for_event(event_queue, &ev);

		//se o tipo de evento for temporizador)
		if(ev.type == ALLEGRO_EVENT_TIMER) {

			desenharCenario();
			
			for (int i = 0; i<2; i++){
				drawJogador(&jogadores[i]);
			}
			
			for (int i = 0; i<2; i++){
				updateJogador(jogadores, i);
			}

			for (int i = 0; i <MAX_BOLINHAS; i++){
				colisaoComParede(&bolinhas[i], bolinhas_tela);
				screenDetection(&bolinhas[i]);
			}
			
			if(al_get_timer_count(timer)%(int)FPS == 0){
			if(seconds == 5){
					seconds = 0;
					if(count_bolinhas < MAX_BOLINHAS){
						criaBolinha(&bolinhas[count_bolinhas], count_bolinhas);
						posicaoBolinha(&bolinhas[count_bolinhas], prox_bolinha);
						vemNaTela(&count_bolinhas);
						vemProxima(&prox_bolinha);
					}else{
						respawnBolinha(bolinhas, prox_bolinha, count_r);
						flowCount(&count_r);
						vemProxima(&prox_bolinha);
					}
				}else{
					seconds++;
				}
			}
			

			for (int i = 0; i <MAX_BOLINHAS; i++){
				updateBolinha(&bolinhas[i]);
				drawnBolinha(&bolinhas[i]);
			}
			//atualiza a tela
			al_flip_display();

		}
		//se o tipo de evento for o fechamento da tela (clique no x da janela)
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			playing = 0;
		}

		//se o tipo de evento for um pressionar de uma tecla
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			//imprime qual tecla foi
			printf("\ncodigo tecla: %d", ev.keyboard.keycode);
			for (int i = 0; i < MAX_BOLINHAS; i++){
				for (int j = 0; j< 2; j++){
					//moveJogador(jogadores, j, ev);
					switch(ev.keyboard.keycode) {
				if (j == 0 ){
					case (ALLEGRO_KEY_LEFT):
						if (jogadores[0].x > 0){
							jogadores[0].left = 1;
						}
					break;	
					case (ALLEGRO_KEY_RIGHT):
						if (jogadores[0].x < SCREEN_W){
							jogadores[0].right = 1;
						}
					break;
					case (ALLEGRO_KEY_UP):
						if (jogadores[0].y > 0){
							jogadores[0].up = 1;
						}
					break;
					case (ALLEGRO_KEY_DOWN):
						if (jogadores[0].y < SCREEN_H){
							jogadores[0].down = 1;
						}
					break;
				}else{
					case (ALLEGRO_KEY_A):
						if (jogadores[1].x > 0){
							jogadores[1].left = 1;
						}
					break;
					case (ALLEGRO_KEY_D):
						if (jogadores[1].x < SCREEN_W){
							jogadores[1].right = 1;
						}
					break;
					case (ALLEGRO_KEY_W):
						if (jogadores[1].y > 0){
							jogadores[1].up = 1;
						}
					break;
					case (ALLEGRO_KEY_S):
						if (jogadores[1].y < SCREEN_H/2){
							jogadores[1].down = 1;
						}
					break;
			}
			}
				colisaoJogadorBolinha(&bolinhas[i], jogadores, j, ev);
				}
			}
		}

		else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
			//imprime qual tecla foi
			printf("\ncodigo tecla: %d", ev.keyboard.keycode);
			for (int i = 0; i < 2; i++){
				switch(ev.keyboard.keycode) {
				if (i == 0){
				case (ALLEGRO_KEY_LEFT):
					jogadores[0].left = 0;
				break;
				case (ALLEGRO_KEY_RIGHT):
					jogadores[0].right = 0;
				break;
				case (ALLEGRO_KEY_UP):
					jogadores[0].up = 0;
				break;
				case (ALLEGRO_KEY_DOWN):
					jogadores[0].down = 0;
				break;
			}else{
				case (ALLEGRO_KEY_A):
					jogadores[1].left = 0;
				break;
				case (ALLEGRO_KEY_D):
					jogadores[1].right = 0;
				break;
				case (ALLEGRO_KEY_W):
					jogadores[1].up = 0;
				break;
				case (ALLEGRO_KEY_S):
					jogadores[1].down = 0;
				break;
			}
			}
			}
		}

	} //fim do while
     
	//procedimentos de fim de jogo (fecha a tela, limpa a memoria, etc)
	
 
	al_destroy_timer(timer);
	al_destroy_font(text);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
   
 
	return 0;
}
