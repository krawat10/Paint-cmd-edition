#include<stdlib.h>
#include <stdio.h>
#include"conio2.h"

/* Uwaga: w docelowym programie nalezy zadeklarowac odpowiednie
   stale, na przyklad po to, aby wyeliminowac z programu
   wartosci numeryczne umieszczajac w ich miejsce
   dobrze dobrane identyfikatory */
#define menu_position 1



int main(int argc, char *argv[]) {
	wektor stack_memory;
	newVector(&stack_memory);
	controls info = { false, false, 0,0, false, 0, 0 };
	int zn = 0, x = 40, y = 12, attr = 7, back = 0, zero = 0;
	char txt[32] = "kod klawisza: 0x";
	char file_name[32] = "brak pliku";	
	char *buf = (char*)malloc(sizeof(char) * 50*20);
	char *copybuffer = (char*)malloc(sizeof(char) * 50*20);
	fileopen_init(buf);
	info.width = 20;
	info.height =50;
	char *filename = (char*)malloc(sizeof(char) * 20);
	fill_name(filename);
	if (argv[1] != NULL)  //czy otweiramy z linii komend
	{
		info.Argv = true;
		filename = argv[1];
		fileopen_path(buf, &stack_memory, filename, &info);
	}	
	save_picture_stack(buf, &stack_memory, info.width, info.height);
	stack_memory.used = 0;

	// je¿eli program jest kompilowany w czystym jêzyku C
	// proszê odkomentowaæ poni¿sz¹ liniê
	Conio2_Init();
	settitle("Mateusz Krawczyk 150348");

	do {		
		textbackground(BLACK);
		clrscr();
		write_picture(buf, picture_position, &info);
		textbackground(BLACK);
		textcolor(WHITE);
		gotoxy(menu_position, 1);
		cputs("esc = wyjscie ");
		gotoxy(menu_position, 2);
		cputs("strzalki = poruszanie");
		gotoxy(menu_position, 3);
		cputs("spacja = zmiana koloru");
		gotoxy(menu_position, 4);
		cputs("backspace = cofnij");
		gotoxy(menu_position, 5);
		cputs("i = wczytanie obrazu domyœlnego");
		gotoxy(menu_position, 6);
		cputs("n - wczytane obrazu");
		gotoxy(menu_position, 7);
		cputs("s = zapis obrazu o podanej nazwie");
		gotoxy(menu_position, 8);
		cputs("l = rysowanie linii");
		if (zero) {
			txt[16] = '0';
			txt[17] = '0';
			txt[18] = ' ';
			txt[19] = '0';
			txt[20] = 'x';
			_itoa(zn, txt + 21, 16);
		}
		else {
			_itoa(zn, txt + 16, 16);
		}
		gotoxy(menu_position, 9);
		cputs("k - rysowanie prostokata");
		gotoxy(menu_position, 10);
		cputs("backspace - cofnij");
		gotoxy(menu_position, 11);
		cputs("alt+strzalki - kopiowanie obszaru");
		gotoxy(menu_position, 12);
		cputs("c - skopiowanie fragmentu");
		gotoxy(menu_position, 13);
		cputs("p - wklejenie fragmentu");
		gotoxy(menu_position, 14);
		cputs("1234567890qwert - wybor kolorow");
		gotoxy(menu_position, 15);
		cputs(txt);
		gotoxy(menu_position, 16);
		cputs(filename);
		gotoxy(menu_position, 17);
		cputs(int_to_array(x));		
		cputs(":");
		cputs(int_to_array(y));
		gotoxy(menu_position, 18);
		if (stack_memory.used == 0) { cputs("funkcja cofnij niedostepna"); }
		else { cputs("c = cofnij"); }
		gotoxy(menu_position, 19);	
		if (info.active_copy) { cputs("schowek aktywny"); }
		else { cputs("schowek pusty"); }
		gotoxy(menu_position, 22);
		cputs("wymiar:"); cputs(int_to_array(info.width)); cputs(int_to_array(info.height));
		gotoxy(x, y);
		textcolor(attr);		
		textbackground(back);
		putch('*');
		zero = 0;
		zn = getch();
		if (zn == 0) {
			zero = 1;
			zn = getch();
			if (zn == 0x48) y--;
			else if (zn == 0x50) y++;
			else if (zn == 0x4b) x--;
			else if (zn == 0x4d) x++;
		}
		else if (zn == ' ') attr = (attr + 1) % 16;
		else if (zn == 0x0d) back = (back + 1) % 16;
		else if (zn == 'i')
		{
			fileopen(buf, &stack_memory, &info); fill_name(filename);
		}
		else if (zn == 'o') fileopen_path(buf, &stack_memory, filename, &info);
		else if (zn == 'l') draw_line(buf, x, y, &stack_memory, &info, attr);
		else if (zn == 8) open_picture_stack(buf, &stack_memory, info.width, info.height);  //backspace
		else if (zn == 'k') draw_rectangle(buf, x, y, &stack_memory, &info, attr);
		else if (zn == 'n') new_picture(buf, &stack_memory, &info);
		else if (zn == 'c') copy(buf, x, y, copybuffer, &info);
		else if (zn == 'p') paste(buf, x, y, copybuffer, &info, &stack_memory);
		else if (zn == 's') filesave(buf, info, filename);
		else if (zn == '1') attr = BLACK;
		else if (zn == '2') attr = BLUE;
		else if (zn == '3') attr = GREEN;
		else if (zn == '4') attr = CYAN;
		else if (zn == '5') attr = RED;
		else if (zn == '6') attr = MAGENTA;
		else if (zn == '7') attr = BROWN;
		else if (zn == '8') attr = LIGHTGRAY;
		else if (zn == '9') attr = DARKGRAY;
		else if (zn == '0') attr = LIGHTBLUE;
		else if (zn == 'q') attr = LIGHTGREEN;
		else if (zn == 'w') attr = LIGHTCYAN;
		else if (zn == 'e') attr = LIGHTRED;
		else if (zn == 'r') attr = LIGHTMAGENTA;
		else if (zn == 't') attr = YELLOW;
		else if (zn == 'y') attr = WHITE;
	} while (zn != 27);

	return 0;
}

