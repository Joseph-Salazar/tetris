#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <time.h>
using namespace std;
using namespace System;


#define EXIT 100
#define WALL 5
#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ESPACIO 32
#define ESC 27
#define ABAJO 80
#define ANCHO 10
#define ALTO 20
#define MAN 15
#define MAL 10




typedef struct posicion {// VALIDAMOS POSICION CON STRUCT
	int X;
	int Y;
} conocido;
typedef char Tablero;

void Coordenadas(int x, int y) {// VALIDACION DE LA POSICION
	Console::SetCursorPosition(x, y);
}

int recibe_tecla() {// PARA QUE HAGA CASO LAS TECLAS . 
	if (_kbhit()) return _getch();
	return -1;
}
void bordes(Tablero map[ALTO][ANCHO]) {//DIBUJA LOS BORDES DEL TABLERO.
	int a, b;
	for (a = 0; a <= ALTO + 1; a++) {
		for (b = 0; b <= ANCHO + 1; b++) {
			Coordenadas(b + 1, a + 1);
			if (a == 0 || b == 0 || a == ALTO + 1 || b == ANCHO + 1)
				Console::ForegroundColor = ConsoleColor::Red;
			cout << "#";// lo dibuja asi xd
		}
		cout << endl;
	}
	Coordenadas(MAN, 1);

	cout << "Siguiente";

	for (a = 2; a <= 7; a++) {// segundo recuadro el chiquito xd
		for (b = MAN; b <= MAN + 5; b++) {
			if (b == MAN || b == MAN + 5 || a == 2 || a == 7) {

				Coordenadas(b, a);
				Console::ForegroundColor = ConsoleColor::Red;
				cout << "*";
			}
		}
	}

}

int Menu() {//reciba los datos 
	int tecla_presiona;
	Coordenadas(6, 12);
	cout << "Izquierda : flecha izquierda " << endl;
	Coordenadas(6, 13);
	cout << "Derecha : flecha derecha " << endl;
	Coordenadas(6, 14);
	cout << "Rotacion : tecla arriba" << endl;
	Coordenadas(6, 15);
	cout << "Bajar: espacio" << endl;
	Coordenadas(6, 16);
	cout << "Salir: 'q'" << endl;

	while (1) {
		tecla_presiona = recibe_tecla();
		if (tecla_presiona == 's' || tecla_presiona == 'S') break;
		if (tecla_presiona == 'q' || tecla_presiona == 'Q') break;

		Coordenadas(7, 17);
		cout << "Presiona s para empezar " << endl;

	}

	return tecla_presiona;
}

void DIBUJA_PIEZA_AL_CAER(Tablero map[ALTO][ANCHO]) {
	int c, d;

	for (c = 0; c < ALTO; c++) {
		for (d = 0; d < ANCHO; d++) {
			Coordenadas(d + 2, c + 2);
			if (map[c][d] == 0)
			{
				cout << " ";//NO DEJE RASTRO
			}
			if (map[c][d] == 1)
			{
				Console::ForegroundColor = ConsoleColor::Cyan;
				cout << "*";//Las piezas son dibujadas con una a
			}
		}
		cout << endl;
	}

}
void MuestraPuntaje(int puntaje) {//puntaje
	Coordenadas(MAN + 4, MAL + 2);
	cout << puntaje;

}

void pieza_segundo_recuadro(Tablero map[ALTO][ANCHO], int forma[4][4]) {//muestra pieza segundo recuadro
	int e, f;
	for (e = 3; e <= 6; e++) {
		for (f = MAN + 1; f <= MAN + 4; f++) {
			Coordenadas(f, e);
			cout << " ";

		}
	}
	for (e = 3; e <= 6; e++) {
		for (f = MAN + 1; f <= MAN + 4; f++) {
			if (forma[e - 3][f - MAN - 1] == 1) {//forma de la siguiente pieza
				Coordenadas(f, e);
				Console::ForegroundColor = ConsoleColor::Cyan;
				cout << "*";
			}
		}
	}
}

void pinta_pieza(Tablero map[ALTO][ANCHO], int forma[4][4], conocido ubicacion) {//pintar pieza en mapa
	int g, h;

	for (g = 0; g < 4; g++) {
		for (h = 0; h < 4; h++) {
			if (forma[g][h] == 1) {
				map[ubicacion.Y + g][ubicacion.X + h] = 1;
			}
		}
	}

}

void vacia_mapa(Tablero map[ALTO][ANCHO]) {
	int i, j = 0;
	for (i = 0; i < ALTO; i++) {
		for (j = 0; j < ANCHO; j++) {
			map[i][j] = 0;// LIMPIA EL INTERIOR DEL MAPA
		}
	}
}
void posicion_inicial_pieza(conocido * ubicacion) {
	ubicacion->X = 3;
	ubicacion->Y = 0;
}
void forma_la_pieza(int forma[4][4], int formasi[4][4]) {
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			forma[i][j] = formasi[i][j];// no se separe la pieza
		}
	}
}
void recibe_figuras(int figura[4][4]) {

	int forma[7][4][4] = {
		{ { 0,1,0,0 },{ 0,1,0,0 },{ 0,1,0,0 },{ 0,1,0,0 } },
		{ { 0,0,0,0 },{ 0,1,1,0 },{ 0,1,1,0 },{ 0,0,0,0 } },
		{ { 0,0,0,0 },{ 0,1,0,0 },{ 1,1,1,0 },{ 0,0,0,0 } },
		{ { 0,0,1,0 },{ 0,1,1,0 },{ 0,1,0,0 },{ 0,0,0,0 } },
		{ { 0,1,0,0 },{ 0,1,1,0 },{ 0,0,1,0 },{ 0,0,0,0 } },
		{ { 0,0,0,0 },{ 0,1,0,0 },{ 0,1,1,1 },{ 0,0,0,0 } },
		{ { 0,0,0,0 },{ 0,1,1,1 },{ 0,1,0,0 },{ 0,0,0,0 } }
	};
	srand((time(NULL)));

	switch (rand() % 7) {
	case 0:
		forma_la_pieza(figura, forma[0]);
		break;
	case 1:
		forma_la_pieza(figura, forma[1]);
		break;
	case 2:
		forma_la_pieza(figura, forma[2]);
		break;
	case 3:
		forma_la_pieza(figura, forma[3]);
		break;
	case 4:
		forma_la_pieza(figura, forma[4]);
		break;
	case 5:
		forma_la_pieza(figura, forma[5]);
		break;
	case 6:
		forma_la_pieza(figura, forma[6]);
		break;
	default:
		break;
	}
}
void borra_rastro_pieza(Tablero map[ALTO][ANCHO], int forma[4][4], conocido * ubicacion) {
	int h, w;
	for (h = 0; h < 4; h++) {
		for (w = 0; w < 4; w++) {
			if (forma[h][w] == 1)
				map[ubicacion->Y + h][ubicacion->X + w] = 0;
		}
	}
}

int limite_izquierdo_con_direccionales(int forma[4][4]) {
	int x, y, iza = 4;
	for (y = 0; y < 4; y++) {
		for (x = 0; x < 4; x++) {
			if (forma[x][y] == 1) {
				if (iza > y)
					iza = y;
			}
		}
	}
	return iza;
}
int limite_derecho_con_direccionales(int forma[4][4]) {
	int x, y, dera = 0;
	for (y = 3; y >= 0; y--) {
		for (x = 3; x >= 0; x--) {
			if (forma[x][y] == 1) {
				if (dera < y)
					dera = y;
			}
		}
	}
	return dera + 1;// +1 por el limite del mapa del contorno
}
int Limite_direccional_de_abajo(int forma[4][4]) {
	int x, y, abaal = 0;
	for (y = 3; y >= 0; y--) {
		for (x = 3; x >= 0; x--) {
			if (forma[x][y] == 1) {
				if (abaal < x)
					abaal = x;
			}
		}
	}
	return abaal + 1;
}
int colision_bloque_abajo(int forma[4][4], int w) {//colision bloques
	int x, y = -1;
	for (x = 3; x >= 0; x--) {
		if (forma[x][w] == 1) {
			if (y < x)
				y = x;
		}
	}
	return y;
}
int colision_bloque_izquierda(int forma[4][4], int h) {
	int w, izquierda = 5;
	for (w = 0; w < 4; w++) {
		if (forma[h][w] == 1) {
			if (izquierda > w)
				izquierda = w;
		}
	}
	return izquierda;
}
int colision_bloque_derecha(int forma[4][4], int h) {
	int w, derecha = -1;
	for (w = 0; w < 4; w++) {
		if (forma[h][w] == 1) {
			if (derecha < w)
				derecha = w;
		}
	}
	return derecha;
}
void limite_para_la_derecha(Tablero map[ALTO][ANCHO], int forma[4][4], conocido *ubicacion) {
	int izq = limite_izquierdo_con_direccionales(forma);
	int Vec[4] = { 0 };
	int i;
	for (i = 0; i < 4; i++) {
		Vec[i] = colision_bloque_izquierda(forma, i);

	}
	if ((ubicacion->X) + izq > 0) {
		if (!((Vec[0] != 5 && map[ubicacion->Y][ubicacion->X + Vec[0] - 1] != 0)
			|| (Vec[1] != 5 && map[ubicacion->Y + 1][ubicacion->X + Vec[1] - 1] != 0)
			|| (Vec[2] != 5 && map[ubicacion->Y + 2][ubicacion->X + Vec[2] - 1] != 0)
			|| (Vec[3] != 5 && map[ubicacion->Y + 3][ubicacion->X + Vec[3] - 1] != 0))) {

			borra_rastro_pieza(map, forma, ubicacion);
			(ubicacion->X)--;
		}
	}
}
void limite_para_izquierda(Tablero map[ALTO][ANCHO], int forma[4][4], conocido *ubicacion) {
	int der = limite_derecho_con_direccionales(forma);
	int Vec[4] = { 0 };
	int i;
	for (i = 0; i < 4; i++) {
		Vec[i] = colision_bloque_izquierda(forma, i);

	}

	if ((ubicacion->X) + der < ANCHO) {
		if (!((Vec[0] != 5 && map[ubicacion->Y][ubicacion->X + Vec[0] + 1] != 0)
			|| (Vec[1] != 5 && map[ubicacion->Y + 1][ubicacion->X + Vec[1] + 1] != 0)
			|| (Vec[2] != 5 && map[ubicacion->Y + 2][ubicacion->X + Vec[2] + 1] != 0)
			|| (Vec[3] != 5 && map[ubicacion->Y + 3][ubicacion->X + Vec[3] + 1] != 0))) {

			borra_rastro_pieza(map, forma, ubicacion);
			(ubicacion->X)++;
		}

	}
}

int mantiene_figura(Tablero map[ALTO][ANCHO], int forma[4][4], conocido *ubicacion) {
	int w, h;
	for (w = 0; w < 4; w++) {
		for (h = 0; h < 4; h++) {
			if (forma[h][w] == 1) {//hace que no pinte el cuadro al caer
				map[ubicacion->Y + h][ubicacion->X + w] = 1;
			}
		}
	}
	return 0;
}

int caida_del_bloque(Tablero map[ALTO][ANCHO], int forma[4][4], conocido *ubicacion) {
	int hondo = Limite_direccional_de_abajo(forma);
	int vec2[4] = { 0 };
	int i;
	for (i = 0; i < 4; i++) {
		vec2[i] = colision_bloque_abajo(forma, i);//uno a uno encima del otro
	}
	if (ubicacion->Y + hondo == ALTO
		|| (vec2[1] != -1 && map[ubicacion->Y + vec2[1] + 1][ubicacion->X + 1] != 0)
		|| (vec2[0] != -1 && map[ubicacion->Y + vec2[0] + 1][ubicacion->X + 0] != 0)
		|| (vec2[3] != -1 && map[ubicacion->Y + vec2[3] + 1][ubicacion->X + 3] != 0)
		|| (vec2[2] != -1 && map[ubicacion->Y + vec2[2] + 1][ubicacion->X + 2] != 0)
		) {
		//cae en 1 en 1 y 
		mantiene_figura(map, forma, ubicacion);

		Sleep(1000 / 8);//velocidad de espera para la otra pieza
		return true;
	}


	if (ubicacion->Y + hondo < ALTO) {
		borra_rastro_pieza(map, forma, ubicacion);
		Sleep(125);
		(ubicacion->Y)++;
	}
	return false;
}
int caida_del_bloque2(Tablero map[ALTO][ANCHO], int forma[4][4], conocido *ubicacion) {
	int hondo = Limite_direccional_de_abajo(forma);
	int vec2[4] = { 0 };
	int i;
	for (i = 0; i < 4; i++) {
		vec2[i] = colision_bloque_abajo(forma, i);//uno a uno encima del otro
	}
	if (ubicacion->Y + hondo == ALTO
		|| (vec2[1] != -1 && map[ubicacion->Y + vec2[1] + 1][ubicacion->X + 1] != 0)
		|| (vec2[0] != -1 && map[ubicacion->Y + vec2[0] + 1][ubicacion->X + 0] != 0)
		|| (vec2[3] != -1 && map[ubicacion->Y + vec2[3] + 1][ubicacion->X + 3] != 0)
		|| (vec2[2] != -1 && map[ubicacion->Y + vec2[2] + 1][ubicacion->X + 2] != 0)
		) {
		//cae en 1 en 1 y 
		mantiene_figura(map, forma, ubicacion);

		Sleep(1000 / 8);//velocidad
		return true;
	}


	if (ubicacion->Y + hondo < ALTO) {
		borra_rastro_pieza(map, forma, ubicacion);
		Sleep(125);
		(ubicacion->Y)++;
	}
	return false;
}
int caida_del_bloque3(Tablero map[ALTO][ANCHO], int forma[4][4], conocido *ubicacion) {
	int hondo = Limite_direccional_de_abajo(forma);
	int vec2[4] = { 0 };
	int i;
	for (i = 0; i < 4; i++) {
		vec2[i] = colision_bloque_abajo(forma, i);//uno a uno encima del otro
	}
	if (ubicacion->Y + hondo == ALTO
		|| (vec2[1] != -1 && map[ubicacion->Y + vec2[1] + 1][ubicacion->X + 1] != 0)
		|| (vec2[0] != -1 && map[ubicacion->Y + vec2[0] + 1][ubicacion->X + 0] != 0)
		|| (vec2[3] != -1 && map[ubicacion->Y + vec2[3] + 1][ubicacion->X + 3] != 0)
		|| (vec2[2] != -1 && map[ubicacion->Y + vec2[2] + 1][ubicacion->X + 2] != 0)
		) {
		//cae en 1 en 1 y 
		mantiene_figura(map, forma, ubicacion);

		Sleep(1000 / 8);//velocidad
		return true;
	}


	if (ubicacion->Y + hondo < ALTO) {
		borra_rastro_pieza(map, forma, ubicacion);
		Sleep(320);
		(ubicacion->Y)++;
	}
	return false;
}
int caida_del_bloque4(Tablero map[ALTO][ANCHO], int forma[4][4], conocido *ubicacion) {
	int hondo = Limite_direccional_de_abajo(forma);
	int vec2[4] = { 0 };
	int i;
	for (i = 0; i < 4; i++) {
		vec2[i] = colision_bloque_abajo(forma, i);//uno a uno encima del otro
	}
	if (ubicacion->Y + hondo == ALTO
		|| (vec2[1] != -1 && map[ubicacion->Y + vec2[1] + 1][ubicacion->X + 1] != 0)
		|| (vec2[0] != -1 && map[ubicacion->Y + vec2[0] + 1][ubicacion->X + 0] != 0)
		|| (vec2[3] != -1 && map[ubicacion->Y + vec2[3] + 1][ubicacion->X + 3] != 0)
		|| (vec2[2] != -1 && map[ubicacion->Y + vec2[2] + 1][ubicacion->X + 2] != 0)
		) {
		//cae en 1 en 1 y 
		mantiene_figura(map, forma, ubicacion);

		Sleep(1000 / 8);//velocidad
		return true;
	}


	if (ubicacion->Y + hondo < ALTO) {
		borra_rastro_pieza(map, forma, ubicacion);
		Sleep(125);
		(ubicacion->Y)++;
	}
	return false;
}
int caida_del_bloque5(Tablero map[ALTO][ANCHO], int forma[4][4], conocido *ubicacion) {
	int hondo = Limite_direccional_de_abajo(forma);
	int vec2[4] = { 0 };
	int i;
	for (i = 0; i < 4; i++) {
		vec2[i] = colision_bloque_abajo(forma, i);//uno a uno encima del otro
	}
	if (ubicacion->Y + hondo == ALTO
		|| (vec2[1] != -1 && map[ubicacion->Y + vec2[1] + 1][ubicacion->X + 1] != 0)
		|| (vec2[0] != -1 && map[ubicacion->Y + vec2[0] + 1][ubicacion->X + 0] != 0)
		|| (vec2[3] != -1 && map[ubicacion->Y + vec2[3] + 1][ubicacion->X + 3] != 0)
		|| (vec2[2] != -1 && map[ubicacion->Y + vec2[2] + 1][ubicacion->X + 2] != 0)
		) {
		//cae en 1 en 1 y 
		mantiene_figura(map, forma, ubicacion);

		Sleep(1000 / 8);//velocidad
		return true;
	}


	if (ubicacion->Y + hondo < ALTO) {
		borra_rastro_pieza(map, forma, ubicacion);
		Sleep(125);
		(ubicacion->Y)++;
	}
	return false;
}
int caida_del_bloque6(Tablero map[ALTO][ANCHO], int forma[4][4], conocido *ubicacion) {
	int hondo = Limite_direccional_de_abajo(forma);
	int vec2[4] = { 0 };
	int i;
	for (i = 0; i < 4; i++) {
		vec2[i] = colision_bloque_abajo(forma, i);//uno a uno encima del otro
	}
	if (ubicacion->Y + hondo == ALTO
		|| (vec2[1] != -1 && map[ubicacion->Y + vec2[1] + 1][ubicacion->X + 1] != 0)
		|| (vec2[0] != -1 && map[ubicacion->Y + vec2[0] + 1][ubicacion->X + 0] != 0)
		|| (vec2[3] != -1 && map[ubicacion->Y + vec2[3] + 1][ubicacion->X + 3] != 0)
		|| (vec2[2] != -1 && map[ubicacion->Y + vec2[2] + 1][ubicacion->X + 2] != 0)
		) {
		//cae en 1 en 1 y 
		mantiene_figura(map, forma, ubicacion);

		Sleep(1000 / 8);//velocidad
		return true;
	}


	if (ubicacion->Y + hondo < ALTO) {
		borra_rastro_pieza(map, forma, ubicacion);
		Sleep(140);
		(ubicacion->Y)++;
	}
	return false;
}
void rotar_pieza(Tablero map[ALTO][ANCHO], int forma[4][4], conocido * ubicacion) {
	int i, j;
	int tmp[4][4];
	int izq, der, abaj;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (forma[i][j] == 1)//rota pieza con la direccional arriba
			{
				tmp[j][3 - i] = forma[i][j];
				forma[i][j] = 0;//para que no deje rastro al rotar
			}

		}
	}

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (tmp[i][j] == 1) {// no se deforma la pieza al rotar. pd. carlos
				forma[i][j] = 1;
			}

		}
	}


	izq = limite_izquierdo_con_direccionales(forma);//FUNCION LLAMA
	if (ubicacion->X + izq < 0) {// LIMITE 
		limite_para_izquierda(map, forma, ubicacion);
		if (izq == 0) limite_para_izquierda(map, forma, ubicacion);
	}

	der = limite_derecho_con_direccionales(forma);
	if (ubicacion->X + der > ANCHO) {
		limite_para_la_derecha(map, forma, ubicacion);
		if (der == 4)limite_para_la_derecha(map, forma, ubicacion);
	}//LIMITE DERECHO


	abaj = Limite_direccional_de_abajo(forma);
	if (ubicacion->Y + abaj > ALTO) {
		borra_rastro_pieza(map, forma, ubicacion);
		(ubicacion->Y)--;
		if (abaj == 4) (ubicacion->Y)--;
	}//LIMITE DE ABAJO
}

int cae_rapido_la_pieza(Tablero map[ALTO][ANCHO], int forma[4][4], conocido * ubicacion) {
	int final = Limite_direccional_de_abajo(forma);
	int vfinal[4] = { 0 };
	int i;
	for (i = 0; i < 4; i++) {
		vfinal[i] = colision_bloque_abajo(forma, i);// INCRUSTA CON COLISION DE FUNCION
	}
	while (1) {
		if (ubicacion->Y + final == ALTO
			|| (vfinal[1] != -1 && map[ubicacion->Y + vfinal[1] + 1][ubicacion->X + 1] != 0)
			|| (vfinal[0] != -1 && map[ubicacion->Y + vfinal[0] + 1][ubicacion->X + 0] != 0)
			|| (vfinal[3] != -1 && map[ubicacion->Y + vfinal[3] + 1][ubicacion->X + 3] != 0)
			|| (vfinal[2] != -1 && map[ubicacion->Y + vfinal[2] + 1][ubicacion->X + 2] != 0)
			) {

			mantiene_figura(map, forma, ubicacion);

			Sleep(125);
			return true;
		}
		if (ubicacion->Y + final < ALTO) {
			borra_rastro_pieza(map, forma, ubicacion);
			(ubicacion->Y)++;
		}
	}

	return false;
}


void borra_linea(Tablero map[ALTO][ANCHO], int h) {
	int w;
	for (w = 0; w < ANCHO; w++) {
		map[h][w] = 0; //ELIMINA LINEA CUANDO LLENA LA MATRIZ
	}
}
void tablero_colapsa(Tablero map[ALTO][ANCHO], int h) {
	int w;
	while (h > 1) {
		for (w = 0; w < ANCHO; w++) {
			map[h][w] = map[h - 1][w]; // hace que las piezas bajen despues de borrar fila
		}
		h--;
	}

}
void DetectaLineas(Tablero map[ALTO][ANCHO], conocido ubicacion, int * score) {
	int h, w, full, count = 0;

	for (h = ALTO; h >= (ubicacion.Y - 1); h--) {
		full = 0;
		for (w = 0; w < ANCHO; w++) {
			if (map[h][w] == 0) { // DETECTA CUANDO LA LINEA ESTA LLENO ASI BORRA Y COLAPSA
				break;
			}
			else {
				full++;
			}
		}

		if (full == ANCHO) {
			(*score) += 5;
			borra_linea(map, h);
			tablero_colapsa(map, h);
		}
	}

}
int juego_acaba(Tablero map[ALTO][ANCHO], int score) {
	int w = 0;
	for (w = 0; w < ANCHO; w++) {
		if (map[0][w] == 1) {
			Coordenadas(MAN - 7, MAL - 2);
			cout << "Perdiste" << endl;
			Coordenadas(MAN - 6, MAL - 1);
			cout << "puntaje " << score;
			Coordenadas(1, ALTO + 3);


			system("pause");
			return true;
		}
	}

	return false;
}
int juego(Tablero map[ALTO][ANCHO]) {
	int hit;
	int final = false;
	int var = true;
	int puntaje = 0;
	int forma[4][4] = { 0 };
	int forma2[4][4] = { 0 };
	conocido localizacion = { 2,2 };
	vacia_mapa(map);
	bordes(map);
	DIBUJA_PIEZA_AL_CAER(map);

	posicion_inicial_pieza(&localizacion);
	recibe_figuras(forma);
	recibe_figuras(forma2);
	pieza_segundo_recuadro(map, forma2);
	while (1) {

		if (final == true) {
			if (juego_acaba(map, puntaje)) return EXIT;

			DetectaLineas(map, localizacion, &puntaje);
			DetectaLineas(map, localizacion, &puntaje);
			posicion_inicial_pieza(&localizacion);
			forma_la_pieza(forma, forma2);
			recibe_figuras(forma2);
			pieza_segundo_recuadro(map, forma2);
			final = false;
		}

		MuestraPuntaje(puntaje);
		pinta_pieza(map, forma, localizacion);
		DIBUJA_PIEZA_AL_CAER(map);
		final = caida_del_bloque(map, forma, &localizacion);
		if (final == true) continue;

		hit = recibe_tecla();
		if (hit == 't' || hit == 'T') break;
		if (hit == 'p' || hit == 'P') {
			system("pause"); system("cls");
			DIBUJA_PIEZA_AL_CAER(map); bordes(map);
		}
		if (hit == ESPACIO) {
			cae_rapido_la_pieza(map, forma, &localizacion);
		}
		if (hit == 224 || hit == 0) {
			hit = _getch();
			if (hit == ARRIBA) {
				rotar_pieza(map, forma, &localizacion);
			}
			else if (hit == IZQUIERDA) {
				limite_para_la_derecha(map, forma, &localizacion);
			}
			else if (hit == DERECHA) {
				limite_para_izquierda(map, forma, &localizacion);
			}
		}
	}
	return EXIT;
}
int main() {
	Console::CursorVisible = false;
	char map[ALTO][ANCHO] = { 0 };
	int tecla;
	int menu;
	int speed = 120;
	int score = 0;
	Console::ForegroundColor = ConsoleColor::Cyan;
	cout << "####### ####### ####### ######    ###    #####" << endl;
	cout << "   #    #          #    #     #    #    #     #" << endl;
	cout << "   #    #          #    #     #    #    #" << endl;
	cout << "   #    #####      #    ######     #     #####" << endl;
	cout << "   #    #          #    #   #      #          #" << endl;
	cout << "   #    #          #    #    #     #    #     #" << endl;
	cout << "   #    #######    #    #     #   ###    #####" << endl;
	cout << endl;
	cout << " Ingresa   el   numero   1  para   comenzar   el  juego " << endl;
	cin >> menu;
	switch (menu)
	{
	case 1:

		while (1) {
			tecla = Menu();
			if (tecla == 'q' || tecla == 'Q') break;
			system("cls");
			juego(map);
			Sleep(speed++);
			system("cls");
		}
	}
}