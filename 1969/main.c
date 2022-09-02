/*
 ____ ________  ________________ 
/_   /   __   \/  _____/   __   \
 |   \____    /   __  \\____    /
 |   |  /    /\  |__\  \  /    / 
 |___| /____/  \_____  / /____/  
                     \/        

v 4.0

*/


//Bibliotecas
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <allegro.h>


//Funções
void sair();
void blocos();
void mapa();
void control();
int colidir(int Ax, int Ay, int Bx, int By, int Aw, int Ah, int Bw, int Bh);
void menu();
void aliencontrol();
void vidaplayer();
void portal();
void alien_morto();
void tutorial();
void chave();
void controlemapa();
void bordamapa();
void boss();
void salaboss();



//Objetos
struct obj{ int wx, wy, x, y, w, h;};

//player
struct obj
	p =	 {0, 0, 5, 500, 99, 125},
	bloco[13][25];
;

//alien
struct obj
	a =	 {0, 0, 805, 673, 90, 133};
;

struct obj
	a2 = {0, 0, 300, 378, 90, 133};
;


struct obj
	port = {0, 0, 300, 365, 90, 133}; //portal
;

struct obj
	c1 = {0, 0, 805, 673, 80, 86};  //chave 1 
;

struct obj
	c2 = {0, 0, 300, 365, 80, 86}; //chave 2
;

struct obj
	b = {0, 0, 0, 200, 535, 600}; //boss
;


//Variáveis Globais
int sai    = 0;
int width  = 1920;
int height = 1080;
int nsala = 0;
int dir = 0;
int nTile = 0;
int sentido = 1;
int gravity = 3;
int vly = 0;
int caindo = 1;
int vup = 30;
int pulando = 0;
int plimit = 0;	
char mp[13][25];
int out = -1000;
int aTile = 0;
int projetil_vel = 100;
int projetil_range = 1000;
int projetil_x;
int projetil_y;
int tempo_ataque = 1080;
int ataque_per = 1;
int num_frames = 3;
int loop = 0;
int sentido_ataque = 2;
int alienvida = 4;
int alienvida2 = 4;
int aliens_mortos = 0;
int player_hp = 3;
int alienmov = 1;
int alienmov2 = 1;
int loopalien = 0;
int aliendir = 20;
int aliendir2 = 20;
int flag_dir;
int chaves = 0;
int alienshoot = 0;
int alienplayer;
int aliensentido;
int loop_ataque_alien = 0;
int sentido_ataque_alien = 0;
int projetil_alien_y;
int projetil_alien_x;
int projetil_vel_alien = 20;
int projetil_vel_alien2 = 10;
int projetil_range_alien = 800;
int alienplayer2;
int loopalien2 = 0;
int alienshoot2 = 0;
int flag_dir2;
int a2Tile;
int aliensentido2;
int sentido_ataque_alien2 = 0;
int loop_ataque_alien2 = 0;
int projetil_alien_x2;
int projetil_alien_y2;
int player_pular = 1;
int flagborda_xe = 0;
int flagborda_xd = 0;
int flagborda_y = 0;
int loopborda = 0;
int bTile = 0;
int boss_dir;
int bossvida = 500;
int completed = 0;
int bossplayer;
int bossmov = 1;
int loopboss = 0;
int boss_shoot = 0;
int bossdir = 0;
int flag_b_dir;
int boss_sentido;
int sentido_ataque_boss = 0;
int projetil_boss_y;
int projetil_boss_x;
int projetil_vel_boss = 50;
int loop_ataque_boss = 0;
int projetil_range_boss = 800;
int bosstime = 0;
int tempo_ataque_boss = 0;
int cond_boss_shoot = 0;
int ataque = 1;
int delay = 0;


//Bitmaps e samples
BITMAP *buffer, *imagem, *bgteste, *alien, *menulogo, *loading, *projetil, *bola, 
		*guialien, *gameover, *deadbuffer, *portalsprite, *aliendeadsprite, *tuts,
		*loading2, *toolsprite, *bossimg, *bgboss, *victory, *vicbuffer;
SAMPLE *pulo, *peca, *fase, *cai, *menusom, *tirosom, *aliensom, *som1, *somdead, *som0,
		*vitoria, *som3;


int main() {
	
    //Iniciação
	allegro_init();
    install_keyboard();
    install_timer();
	set_color_depth(32);
	set_window_title("1969: The Game");
	set_close_button_callback(sair);
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);  
	set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, width, height, 0, 0);
	
	//Variáveis Locais
	buffer = create_bitmap(width, height);
	loading = create_bitmap(width, height);
	loading2 = create_bitmap(width, height);
	deadbuffer = create_bitmap(width, height);
	vicbuffer = create_bitmap(width, height);
	imagem = load_bitmap("src/imagemn.bmp", NULL);
	bgteste = load_bitmap("src/novo.bmp", NULL);
	alien = load_bitmap("src/inimigo.bmp", NULL);
	menulogo = load_bitmap("src/menu.bmp", NULL);
	tuts = load_bitmap("src/cute.bmp", NULL);
	projetil = load_bitmap("src/blaster.bmp", NULL);
	bola = load_bitmap("src/laseralien.bmp", NULL);
	guialien = load_bitmap("src/gui.bmp", NULL);
	gameover = load_bitmap("src/dead.bmp", NULL);
	portalsprite = load_bitmap("src/portal.bmp", NULL);
	aliendeadsprite = load_bitmap("src/aliendead.bmp", NULL);
	toolsprite = load_bitmap("src/tool8.bmp", NULL);
	bgboss = load_bitmap("src/bg2.bmp", NULL);
	bossimg = load_bitmap("src/bossalien.bmp", NULL);
	victory = load_bitmap("src/victory.bmp", NULL);
	
	//Sons
	menusom = load_sample("src/title.wav");	
	som1 = load_sample("src/jun.wav");
	pulo = load_sample("src/pulo.wav");
	tirosom = load_sample("src/laser.wav");
	somdead = load_sample("src/gameover.wav");
	som0 = load_sample("src/spac.wav");
	peca = load_sample("src/peca.wav");
	som3 = load_sample("src/boss.wav");
	vitoria = load_sample("src/vitoria.wav");
		
	//Fontes
	FONT* aero = load_font("src/aero.pcx", NULL, NULL);
	FONT* code = load_font("src/code.pcx", NULL, NULL);
	
	//Alinhamento da matriz
	for (int i=0; i<13; i++){
		for (int j=0; j<25; j++){
			bloco[i][j].y = i*98;
			bloco[i][j].x = j*113;
			bloco[i][j].w = 113;
			bloco[i][j].h = 98;
			bloco[i][j].wy = 1740;
			bloco[i][j].wx = 0;
		}
	}
	
	mapa();
	
	if (nsala == 0)
		play_sample(menusom, 100, 128, 1000, 1);


///////////////////////////////////////////////////GAME///////////////////////////////////////////////////
		
	while (!(sai || key[KEY_ESC]))
	{		
				
		
		if (nsala == 0){
					
		menu();
		
		
		}
		
		
		if (nsala == 4){
			
		tutorial();	
			
			
		}
		
		if (nsala == 3){
			

			blocos();
			
				
			draw_sprite(buffer, bgboss, 0, 0);	//fundo	
			
			control();
			
							
			salaboss();
			
			
			bordamapa();
			
			vidaplayer();
			
			
			
			
			masked_blit(imagem, buffer, p.wx + nTile*99, p.wy + dir *125, p.x, p.y+20, p.w, p.h); //player e tiles
			
			masked_blit(bossimg, buffer, b.wx + bTile*535, b.wy + flag_b_dir*600, b.x, b.y, b.w, b.h); // boss

/*
			textprintf_ex(buffer, code, 100, 100, makecol(255,255,255), -1, "cond shoot: %d", cond_boss_shoot);
			
			textprintf_ex(buffer, code, 100, 200, makecol(255,255,255), -1, "posicao y: %d", p.y);
			textprintf_ex(buffer, code, 100, 250, makecol(255,255,255), -1, "posicao x: %d", p.x);
			
			textprintf_ex(buffer, code, 100, 350, makecol(255,255,255), -1, "b x: %d", b.x);
			textprintf_ex(buffer, code, 100, 300, makecol(255,255,255), -1, "boss dir: %d", bossdir);
			textprintf_ex(buffer, code, 100, 400, makecol(255,255,255), -1, "bossmov: %d", bossmov);
*/	
			
			textprintf_ex(buffer, code, 100, 400, makecol(255,255,255), -1, "hp: %d", bossvida);
			draw_sprite(screen, buffer, 0, 0); //buffer
			rest(20);
			clear(buffer);	
			
		if (nsala == 5){
			
		draw_sprite(deadbuffer, gameover, 0, 0);
		draw_sprite(screen, deadbuffer, 0, 0); //buffer dead
		stop_sample(som1);
		stop_sample(som3);
		play_sample(somdead, 80, 128, 1000, 0);	
			
			}
			
			
				
		if (nsala == 6){
		draw_sprite(vicbuffer, victory, 0, 0);
		draw_sprite(screen, vicbuffer, 0, 0);
		stop_sample(som3);
		play_sample(vitoria, 80, 128, 1000, 0);			
		
		
		}
	
		}
		
		
		
		
		
		if (nsala == 1){
			
				
		control();
		
		blocos();
		
		aliencontrol();		
		
		alien_morto();
		

		draw_sprite(buffer, guialien, 0, 0);
		
		textprintf_ex(buffer, aero, 70, 30, makecol(0,0,0), -1, "%d", aliens_mortos);
		textprintf_ex(buffer, aero, 280, 30, makecol(0,0,0), -1, "%d", chaves);

		chave();
		
		bordamapa();
		
		controlemapa();		
		
		
		masked_blit(imagem, buffer, p.wx + nTile*99, p.wy + dir *125, p.x, p.y+20, p.w, p.h); //player e tiles

		masked_blit(alien, buffer, a.wx + aTile*90, a.wy + flag_dir*133, a.x, a.y, a.w, a.h); //alien  1
		masked_blit(alien, buffer, a2.wx + a2Tile*90, a2.wy + flag_dir2*133, a2.x, a2.y, a2.w, a2.h); //alien  2
		
/*
		textprintf_ex(buffer, code, 100, 200, makecol(255,255,255), -1, "posicao y: %d", p.y);
		textprintf_ex(buffer, code, 100, 250, makecol(255,255,255), -1, "posicao x: %d", p.x);
*/

		draw_sprite(screen, buffer, 0, 0); //buffer
		rest(20);
		clear(buffer);	
				
		draw_sprite(buffer, bgteste, 0, 0);	//fundo	
		
        vidaplayer();
        
        
        if (nsala == 5){
			
		draw_sprite(deadbuffer, gameover, 0, 0);
		draw_sprite(screen, deadbuffer, 0, 0); //buffer dead
		stop_sample(som1);
		play_sample(somdead, 80, 128, 1000, 0);	
			
			}
			
			
		}
		
	
}
///////////////////////////////////////////////////GAME///////////////////////////////////////////////////
	
	//Finalização
	destroy_bitmap(buffer);
	destroy_bitmap(imagem);
	destroy_bitmap(bgteste);
	destroy_bitmap(alien);
	destroy_bitmap(loading);
	destroy_bitmap(menulogo);
	destroy_bitmap(projetil);
	destroy_bitmap(bola);
	destroy_bitmap(guialien);
	destroy_bitmap(gameover);
	destroy_bitmap(deadbuffer);
	destroy_bitmap(portalsprite);
	destroy_bitmap(aliendeadsprite);
	destroy_bitmap(tuts);
	destroy_bitmap(toolsprite);
	destroy_bitmap(bossimg);
	destroy_bitmap(bgboss);
	
	
	destroy_sample(menusom);
	destroy_sample(som1);
	destroy_sample(som0);
	destroy_sample(tirosom);
	destroy_sample(pulo);
	destroy_sample(fase);
	destroy_sample(cai);
	destroy_sample(aliensom);
	destroy_sample(somdead);
	destroy_sample(peca);
	

	return 0;
}
END_OF_MAIN();




void menu(){
	
	draw_sprite(loading, menulogo, 0, 0);
	draw_sprite(screen, loading, 0, 0); //loading


	if (key[KEY_E]){
		clear(menulogo);
		stop_sample(menusom);
		
		nsala=4;
		
		
		play_sample(som0, 80, 128, 1000, 1);
		
		}
		
}


void tutorial(){
	
	draw_sprite(loading2, tuts, 0, 0);
	draw_sprite(screen, loading2, 0, 0); //loading 2


	if (key[KEY_SPACE]){
		clear(tuts);
		stop_sample(som0);
		
		nsala=1;
		play_sample(som1, 80, 128, 1000, 1);
		
		}
	
}
	
	


void mapa(){

	int i,j;   
	char mapa[13][25] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
						 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},							
						 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						 {3,3,2,2,2,3,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},							
						 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
						 {3,3,2,2,2,2,2,2,2,2,2,2,3,2,2,2,2,2,2,2,2,2,2,2,0},							
						 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},							
						 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1}}; 

	for (i=0; i<13; i++){
		for (j=0; j<25; j++){
			if (mapa[i][j]) bloco[i][j].wx = (mapa[i][j]-1)	*bloco[i][j].w;
			else {
				bloco[i][j].x = out;
				mp[i][j] = mapa[i][j];
			}
		}
	}
	
		

}


void blocos(){
	
		for(int i=0; i<13; i++){
			for (int j=0; j<25; j++){
				if (colidir(p.x, p.y, bloco[i][j].x+80, bloco[i][j].y, 148, 142, bloco[i][j].w-80, 4)){
					if (mp[i][j] != 6 && mp[i][j] != 8){
						caindo = 0;
						p.y = bloco [i][j].y - p.h;
					}
				}
				masked_blit(imagem, buffer, bloco[i][j].wx, bloco[i][j].wy, bloco[i][j].x, bloco[i][j].y, bloco[i][j].w, bloco[i][j].h);
		}
	}
	
}



void control(){
	
	
	if ((key[KEY_UP] && !pulando && !vly && !key[KEY_X] && !loop == 1 && flagborda_y == 0)){ /*frame do pulo quando cai*/
		play_sample(pulo, 45, 128, 1000, 0);
		plimit = p.y;
		pulando = 1;
		
		if (sentido == 1){		
			dir = 6;
			nTile = 0;}
		else if (sentido == 0){
			dir = 7;
			nTile = 0;}
 	}
		if (pulando||caindo){
			if (key[KEY_RIGHT] && flagborda_xd == 0) {
				p.x += 10; dir= 6; nTile=0;}
			else if (key[KEY_LEFT] && flagborda_xe == 0) {
				p.x -= 10; dir= 7; nTile=0;}	
			}

	else {
		if (key[KEY_RIGHT]&& ! key[KEY_X] && !p.x == 0 && !pulando && !caindo && flagborda_xd == 0 ){
			p.x+= 15; dir= 0; 
			nTile++; sentido= 1;}
		else if (key[KEY_LEFT]&& ! key[KEY_X] && !p.x == 0 && !pulando && !caindo && flagborda_xe == 0){
			p.x-= 15; dir= 1; 
			nTile++; sentido= 0;}		
		else nTile = 0;
			if (nTile < 0) nTile = 5;
			if (nTile > 5) nTile = 0;

		}
		if (((key[KEY_X])&& !key[KEY_UP] && !caindo ==1 && sentido == 1 && sentido_ataque != 0) || sentido_ataque == 1) {
			sentido_ataque = 1;
			play_sample(tirosom, 10, 128, 1000, 0);
			
					
				dir = 2;
				nTile++;
				
				
				if (loop==0){projetil_x = p.x + p.w ; projetil_y = p.y - 50 + p.h;}
				if (projetil_x - p.x <= projetil_range){
				
					projetil_x += projetil_vel;
					masked_blit (projetil, buffer, 0, 0, projetil_x, projetil_y, 40,12);
					loop += 1;		
				
				
				
				}
				else {loop = 0; sentido_ataque = 2;}
				
			}
		
			if (((key[KEY_X])&& !key[KEY_UP] && caindo ==0 && sentido == 0 && sentido_ataque != 1) || sentido_ataque == 0) {
			sentido_ataque = 0;
			play_sample(tirosom, 10, 128, 1000, 0);
			
				
				dir = 3;
				nTile++;
				
				
				
				if (loop==0){projetil_x = p.x + p.w + 20 ; projetil_y = p.y - 40 + p.h;}
				if (p.x - projetil_x<= projetil_range){
				
					projetil_x -= projetil_vel;
					masked_blit (projetil, buffer, 0, 0, projetil_x, projetil_y, 40,12);
					loop += 1;
			
				
				
				}
				else {loop = 0; sentido_ataque = 2;}
				
			}
			
	
	
			
	//condições
	if (pulando && p.y > plimit - 30){
		p.y += vly;
		vly = -vup;
		caindo = 1;
		}

	else if (caindo==1){
		pulando = 0;
		vly += gravity;
		p.y += vly;}
		
	else {
		pulando = 0;
		vly = 0;	
	}

	caindo = 1;
	
	
	
//cheat
	if (key[KEY_P]){
			ataque = 500;
				}

	
}
	


//Função de colisão
int colidir(int Ax, int Ay, int Bx, int By, int Aw, int Ah, int Bw, int Bh){
	if (Ax + Aw > Bx && Ax < Bx + Bw && Ay + Ah > By && Ay < By + Bh)
	return 1;
	return 0;
 }
 
 
 
 void vidaplayer(){
		
	if (nsala == 1){
		
	if ( (colidir(p.x, p.y, a.x, a.y, p.w, p.h, a.w, a.h)) 
		|| (colidir(p.x, p.y, a2.x, a2.y, p.w, p.h, a2.w, a2.h))
		|| (colidir(p.x, p.y, projetil_alien_x, projetil_alien_y, p.w, p.h, 20, 20)) 
		|| (colidir(p.x, p.y, projetil_alien_x2, projetil_alien_y2, p.w, p.h, 20, 20))
		){
	
		player_hp = 0;	
	}
}
	
	if (nsala == 3 && ((p.x / 100) == (b.x /100))&& delay > 500){
		player_hp =0;
	}
	
	if (player_hp == 0 || p.y > 1500){
		
		nsala = 5;
	
	}
		
}



 
 void aliencontrol(){
		
//alien 1

	alienplayer = p.y + a.y;
	
	 if (alienmov == 1 && loopalien == 0 && !alienshoot == 1){
		if (aliendir == 0){
			if (flag_dir == 0){
				aliendir = -40;}
			if (flag_dir == 1){
				aliendir = 40;}				
			}
		
		if (aliendir > 0 && aliendir <= 40){	 //direita
			a.x+= 10; aliendir--; aTile++;	flag_dir = 0;
			aliensentido = 1; }
			
			
		else if (aliendir < 0){  //esquerda
			a.x-= 10; aliendir++; aTile--; flag_dir = 1; 
			aliensentido = 0;}	
	
		loopalien+=1;
		alienmov = 0;
		
		if (aTile < 0) aTile = 5 ;
		if (aTile > 5) aTile = 0 ;		
		
		}
		
	else if (alienplayer > 1100 && alienplayer < 1800 ){  //range do tiro
		
		alienshoot = 1;
		
		if (p.x > 1000)
			sentido_ataque_alien = 1;
		else
			sentido_ataque_alien = 0;
		
		
		if (p.x > 1000 && sentido_ataque_alien != 0 ){	 //direita
		
			sentido_ataque_alien = 1;
			
			aTile++; flag_dir = 2;

			
				
				if (loop_ataque_alien==0){projetil_alien_x = a.x + a.w -100 ; projetil_alien_y = a.y - 60 + a.h;}
				if (projetil_alien_x - a.x <= projetil_range_alien){
					
				
					projetil_alien_x += projetil_vel_alien;
					masked_blit (bola, buffer, 0, 0, projetil_alien_x, projetil_alien_y, 100,100);
					loop_ataque_alien += 1;
				
				
				
				
				}
				else {loop_ataque_alien = 0; sentido_ataque_alien = 2;}
				
			}
			
			
						
		else if  (p.x < 1000 && sentido_ataque_alien != 1 ){  //esquerda
			aTile--; flag_dir = 3; 
			
			sentido_ataque_alien = 0;
			
			aTile--; flag_dir = 3;

				
				if (loop_ataque_alien==0){projetil_alien_x = a.x + a.w -100 ; projetil_alien_y = a.y - 60 + a.h;}
				if (a.x - projetil_alien_x<= projetil_range_alien){
				
					projetil_alien_x -= projetil_vel_alien;
					masked_blit (bola, buffer, 0, 0, projetil_alien_x, projetil_alien_y, 100,100);
					loop_ataque_alien += 1;
				
				
			
				}
				else {loop_ataque_alien = 0; sentido_ataque_alien = 2;}
				
			}
			
			
	
		
		if (aTile < 0) aTile = 5 ;
		if (aTile > 5) aTile = 0 ;
		
	}	
		
	else {loopalien = 0; alienmov = 1; alienshoot = 0;}
	
	
 
 //////////
 
 
 //alien 2

	alienplayer2 = p.y + a2.y;
	
	 if (alienmov2 == 1 && loopalien2 == 0 && !alienshoot2 == 1){
		if (aliendir2 == 0){
			if (flag_dir2 == 0){
				aliendir2 = -40;}
			if (flag_dir2 == 1){
				aliendir2 = 40;}				
			}
		
		if (aliendir2 > 0 && aliendir2 <= 40){	 //direita
			a2.x+= 10; aliendir2--; a2Tile++;	flag_dir2 = 0;
			aliensentido2 = 1; }
			
			
		else if (aliendir2 < 0){  //esquerda
			a2.x-= 10; aliendir2++; a2Tile--; flag_dir2 = 1; 
			aliensentido2 = 0;}	
	
		loopalien2+=1;
		alienmov2 = 0;
		
		if (a2Tile < 0) a2Tile = 5 ;
		if (a2Tile > 5) a2Tile = 0 ;		
		
		}
		
	else if (alienplayer2 < 800 && alienplayer2 > 0 ){  //range do tiro
		
		alienshoot2 = 1;
		
		if (p.x > 250)
			sentido_ataque_alien2 = 1;
		else if (p.x < 160)
			sentido_ataque_alien2 = 0;
		
		
		if (p.x > 250 && sentido_ataque_alien2 != 0 ){	 //direita
		
			sentido_ataque_alien2 = 1;
			
			a2Tile++; flag_dir2 = 2;

				
				if (loop_ataque_alien2==0){projetil_alien_x2 = a2.x + a2.w -100 ; projetil_alien_y2 = a2.y - 60 + a2.h;}
				if (projetil_alien_x2 - a2.x <= projetil_range_alien){
				
					projetil_alien_x2 += projetil_vel_alien;
					masked_blit (bola, buffer, 0, 0, projetil_alien_x2, projetil_alien_y2, 100,100);
					loop_ataque_alien2 += 1;
				
				
				
				
				}
				else {loop_ataque_alien2 = 0; sentido_ataque_alien2 = 2;}
				
			}
			
			
						
		else if  (p.x < 250 && sentido_ataque_alien2 != 1 ){  //esquerda

			
			sentido_ataque_alien2 = 0;
			
			a2Tile--; 
			flag_dir2 = 3;

				
				if (loop_ataque_alien2==0){projetil_alien_x2 = a2.x + a2.w -100 ; projetil_alien_y2 = a2.y - 60 + a2.h;}
				if (a2.x - projetil_alien_x2<= projetil_range_alien){
				
					projetil_alien_x2 -= projetil_vel_alien;
					masked_blit (bola, buffer, 0, 0, projetil_alien_x2, projetil_alien_y2, 100,100);
					loop_ataque_alien2 += 1;
				
				
				
				
				}
				else {loop_ataque_alien2 = 0; sentido_ataque_alien2 = 2;}
				
			}
			
			
	
			
			
		
		if (a2Tile < 0) a2Tile = 5 ;
		if (a2Tile > 5) a2Tile = 0 ;
		
	}	
		
	else {loopalien2 = 0; alienmov2 = 1; alienshoot2 = 0;}
	
	
 
 //////////
 

	
	
	if (colidir(a.x, a.y, projetil_x, projetil_y, 100, 100, a.w, a.h)){
	
		alienvida--;	
		
		if (alienvida == 0){
			aliens_mortos++;
			a.y = out;
			projetil_alien_y = out;			
		}
	}
	
	
	if (colidir(a2.x, a2.y, projetil_x, projetil_y, 100, 100, a2.w, a2.h)){
	
		alienvida2--;	
		
		if (alienvida2 == 0){
			aliens_mortos++;
			a2.y = out;
			projetil_alien_y2 = out;	
					
		}
	}

	
		
} 


void alien_morto(){
	
	
		if (alienvida == 0){

			alienmov = 0;
			draw_sprite(buffer, aliendeadsprite, a.x, a.y-1180);	
		}
		
		if (alienvida2 == 0){
			alienmov2 = 0;
			draw_sprite(buffer, aliendeadsprite, a2.x, a2.y-800);	
		}
		
	
}


void chave(){
	
	
	
	draw_sprite(buffer, toolsprite, c1.x, c1.y);
	draw_sprite(buffer, toolsprite, c2.x, c2.y);
	


	if (colidir(p.x, p.y, c1.x, c1.y, p.w, p.h, c1.w, c1.h)){
		play_sample(peca, 10, 128, 1000, 0);
		chaves++;			
		c1.y = out;
		
		}
		
	if (colidir(p.x, p.y, c2.x, c2.y, p.w, p.h, c2.w, c2.h)){
		
		play_sample(peca, 10, 128, 1000, 0);	
		chaves++;			
		c2.y = out;
		
		}

		
		if (chaves == 2){
		draw_sprite(buffer, portalsprite, 1700, 600);
		}

}

void bordamapa(){
	
	if (loopborda == 0){
	
		if (p.x < 0){flagborda_xe = 1;	loopborda+=1;}
		
		else if (p.x > 1900){flagborda_xd = 1; loopborda+=1;}
		
		else {flagborda_xe = 0; flagborda_xd = 0;}

	
	}
	else {loopborda=0;}
	
	if (p.y < 0){flagborda_y = 1;}
	else {flagborda_y = 0;}
		

	
}


void controlemapa(){
	
	if (p.x > 1700 && chaves == 2 && aliens_mortos == 2 ){
		
		
		if (key[KEY_SPACE]){
		
			clear(buffer);
			
			nsala = 3;
			
			p.x = 600;
			p.y = 600;
			
			stop_sample(som1);
			play_sample(som3, 100, 128, 1000, 1);
			
	}
		
	}
	
	
}





void salaboss(){
	
	delay++;
	
	//movimentação do boss
	
	if ((p.x / 100) == (b.x /100)) {cond_boss_shoot = 1;}
	else {cond_boss_shoot = 0;}

	
	if (bossmov == 1 && loopboss == 0 && cond_boss_shoot == 0){
		if (bossdir == 0){
			if (boss_sentido == 1){
				bossdir = -130;}
			if (boss_sentido == 0){
				bossdir = 130; }				
			}
		
		if (bossdir > 0 && bossdir <= 130){	 //direita
			b.x+= 10; bossdir--; bTile++; flag_b_dir = 0;
			boss_sentido = 1;}
			
			
		else if (bossdir < 0){  //esquerda
			b.x-= 10; bossdir++; bTile--; flag_b_dir = 0; 
			boss_sentido = 0; }	
		
	
		loopboss+=1;
		bossmov = 0;
		
		}
		
		if (bTile < 0) bTile = 3 ;
		if (bTile > 3) bTile = 0 ;
		
		
		
////

	else if (cond_boss_shoot == 1 ){  //range do tiro
		
		boss_shoot = 1;
				
		sentido_ataque_boss = 1;
			
			bTile++; flag_b_dir = 1;
			
		if (bTile < 0) bTile = 3 ;
		if (bTile > 3) bTile = 0 ;	

				
				if (loop_ataque_boss==0 ){loop_ataque_boss += 1;}			
				
				else {loop_ataque_boss = 0; sentido_ataque_boss = 2;}
	
		}
			
			


////		
	
		
	else {loopboss = 0; bossmov = 1;}

 
 //////////
	
	
	
	
	
	//colisão que dá dano no boss
	
	if (colidir(projetil_x, projetil_y, b.x, b.y, 100, 100, b.w, b.h)){
	
		bossvida-=ataque;	
		
		if (bossvida <= 0){
			b.y = out;
			projetil_y = out;	
			nsala = 6;		
		}
	}
	

	
	///////
	
	
	
}




void sair(){sai= 1;}
END_OF_FUNCTION(sair);

