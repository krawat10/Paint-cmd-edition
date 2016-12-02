#include<stdlib.h>
#include <stdio.h>
#include"conio2.h"

void new_picture(char *buff, wektor *vector, controls* info)
{
	//Ponieranie wymiarów z klawiatury i wyswietlanie wprowadzanych zmian
	gotoxy(1, 20);
	cputs("Podaj szerokosc:");
	int zn = getch();
	(*info).width = 10 * (zn - 48);
	gotoxy(1, 21);
	cputs(int_to_array((*info).width));
	zn = getch();
	(*info).width += (zn - 48);
	gotoxy(1, 21);
	cputs(int_to_array((*info).width));
	gotoxy(1, 20);
	cputs("Podaj dlugosc:");
	zn = getch();
	(*info).height = 10 * (zn - 48);
	gotoxy(4, 21);
	cputs(int_to_array((*info).height));
	zn = getch();
	(*info).height += (zn - 48);
	gotoxy(4, 21);
	cputs(int_to_array((*info).height));
	FILE *file = fopen("start.txt", "r");
	for (int i = 0; i < (*info).width * (*info).width; i++)
	{
		*(buff + i) = fgetc(file);
	}
	fclose(file);
	save_picture_stack(buff, vector, (*info).width, (*info).height);
}

char* int_to_array(int number)
{
	//zamiana liczb dziesietnych na wiersz
	int Aa = number / 10 + 48;
	int aA = number % 10 + 48;
	char *Array = (char*)malloc(sizeof(char) * 2);
	Array[0] = Aa;
	Array[1] = aA;
	Array[2] = '\0';
	return Array;
}

void write_picture(char *buff, int start, controls *info)
{
	//ustawienie poczatku obrazu
	int x = 0 + start;
	int y = 1;
	//wyswietlanie danych z bufora
	for (int i = 0; i < (*info).height*(*info).width; i++, x++)
	{
		gotoxy(x, y);
		textbackground(*(buff + i));
		cputs(" ");
		if (x == (*info).width + start - 1)
		{
			x = start - 1;
			y++;
		}
		if (y == (*info).height + 1) break;
	}
}

void fill_name(char* filename)
{
	for (int i = 0; i < 20; i++)
	{
		*(filename + i) = ' ';
	}
	*(filename + 20) = '\0';
}

void fileopen(char *buff, wektor *vector, controls *info) //otwieranie przyk³¹dowego pliku
{
	FILE *plik = fopen("test.txt", "r");
	if (plik == NULL)
	{
		gotoxy(1, 10);
		cputs("Cos sie popsulo");
	}
	else
	{
		for (int i = 0; i < 50 * 20; i++)
		{
			*(buff + i) = fgetc(plik); //wpisywanie danych do bufora g³ównego
		}
	}
	(*info).width = 50;
	(*info).height = 20;
	fclose(plik);
	newVector(vector); 
	save_picture_stack(buff, vector, 50, 20);
	vector->used = 0;
}

void fileopen_init(char *buff)
{
	FILE *file = fopen("start.txt", "r");
	for (int i = 0; i < 50 * 20; i++)
	{
		*(buff + i) = fgetc(file);
	}
	fclose(file);
}

void filesave(char *buff, controls info, char *filename) // zapisywanie obrazka
{
	int zn;
	fill_name(filename);
	gotoxy(1, 20);
	cputs("podaj sciezke dostepu:");
	int i = 0;
	do {
		zn = getch();
		gotoxy(1, 21);
		*(filename + i) = zn;
		i++;
		cputs(filename); //wyœwietlanie ci¹gu w czasie rzeczywistym
	} while (zn != 13);
	*(filename + i - 1) = '\0';
	if (*(filename + i - 4) == 'b' && *(filename + i - 3) == 'm' && *(filename + i - 2) == 'p')
	{
		BMPmake(buff, filename, &info);
	}
	if (*(filename + i - 4) == 'x' && *(filename + i - 3) == 'p' && *(filename + i - 2) == 'm')
	{
		XPMsave(&info, buff, filename);
	}
	else
	{
		FILE *file = fopen(filename, "wb");
		int Xx = (char)info.width / 10 + 48;  //pierwsze 4 znaki w pliku okreœlaj¹ wymiary
		int xX = info.width % 10 + 48;
		int Yy = info.height / 10 + 48;
		int yY = info.height % 10 + 48;

		fputc((char)Xx, file);
		fputc((char)xX, file);
		fputc((char)Yy, file);
		fputc((char)yY, file);
		for (int i = 0; i < info.height*info.width; i++) //odczyt z bufora g³ównego
		{
			fputc(*(buff + i), file);
		}
		fclose(file);
	}
}


void fileopen_path(char *buff, wektor *vector, char *active, controls *info)
{
	int i = 0;
	if (!(*info).Argv)
	{
		int zn;
		gotoxy(1, 20);
		fill_name(active);
		cputs("podaj sciezke dostepu:");
		
		do {
			zn = getch();
			gotoxy(1, 21);
			*(active + i) = zn;
			i++;
			cputs(active);

		} while (zn != 13);
		*(active + i - 1) = '\0';
	}
	else
	{ 
		do
		{
			i++;
		} while (*(active + i) != '\0');
		
	}	
	char elo[3] = { *(active + i - 4), *(active + i - 3), *(active + i - 2) };
	gotoxy(1, 21);
	cputs(active);
	FILE *file;
	file = fopen(active, "r");
	if (file == NULL)
	{
		gotoxy(1, 10);
		cputs("Podany plik nie istnieje");
		getch();
		return;
	}
	else
	{
		if (elo[0] == 'b' && elo[1] == 'm' && elo[2] == 'p')
		{

			bmpopen_path(buff, vector, active, info, file);
		}
		else if (elo[0] == 'x' && elo[1] == 'p' && elo[2] == 'm')
		{

			XPMload(buff, vector, active, info, file);
		}
		else
		{
			(*info).width = (fgetc(file) - 48) * 10 + (fgetc(file) - 48);
			(*info).height = (fgetc(file) - 48) * 10 + (fgetc(file) - 48);
			for (int i = 0; i < (*info).width * (*info).height; i++)
			{
				*(buff + i) = fgetc(file);
			}
		}
	}

	fclose(file);
	newVector(vector);
	save_picture_stack(buff, vector, (*info).width, (*info).height);
	vector->used = 0;
}
void draw_rectangle(char *buf, int x, int y, wektor *vector, controls *info, int color)
{
	int zn = 0;
	int start_X = x;
	int start_Y = y;
	bool poziom;
	bool pion;
	int absoluteX;
	int absoluteY;
	do
	{
		if (zn == 0x48) y--;
		else if (zn == 0x50) y++;
		else if (zn == 0x4b) x--;
		else if (zn == 0x4d) x++;
		else if (zn == 27) return;
		gotoxy(x, y);
		write_picture(buf, picture_position, info);
		poziom = (start_X <= x);
		pion = (start_Y <= y);
		absoluteX = poziom ? x - start_X : start_X - x;
		absoluteY = pion ? y - start_Y : start_Y - y;

		for (int posY = 0; posY < (absoluteY + 1); posY++)
		{
			for (int posX = 0; posX < (absoluteX + 1); posX++)
			{
				if (pion && poziom)gotoxy(start_X + posX, start_Y + posY);
				if (!pion && poziom)gotoxy(start_X + posX, start_Y - posY);
				if (pion && !poziom)gotoxy(start_X - posX, start_Y + posY);
				if (!pion && !poziom)gotoxy(start_X - posX, start_Y - posY);
				cputs("x");
			}
		}
		zn = getch();
	} while (zn != 'k');
	if (zn == 27)return;
	for (int posY = 0; posY < (absoluteY + 1); posY++)
	{
		for (int posX = 0; posX < (absoluteX + 1); posX++)
		{
			if (pion && poziom)*(buf + ((*info).width*(start_Y + posY - 1) + (start_X + posX - picture_position))) = color;
			if (!pion && poziom)*(buf + ((*info).width*(start_Y - posY - 1) + (start_X + posX - picture_position))) = color;
			if (pion && !poziom)*(buf + ((*info).width*(start_Y + posY - 1) + (start_X - posX - picture_position))) = color;
			if (!pion && !poziom)*(buf + ((*info).width*(start_Y - posY - 1) + (start_X - posX - picture_position))) = color;
			cputs("x");
		}
	}
	save_picture_stack(buf, vector, (*info).width, (*info).height);
}
void draw_line(char *buf, int x, int y, wektor *vector, controls *info, int color)
{
	int zn = 0;
	int start_X = x;
	int start_Y = y;
	bool poziom;
	bool pion;
	int absoluteX;
	int absoluteY;
	do
	{
		if (zn == 0x48) y--;
		else if (zn == 0x50) y++;
		else if (zn == 0x4b) x--;
		else if (zn == 0x4d) x++;
		else if (zn == 27) return;
		gotoxy(x, y);
		write_picture(buf, picture_position, info);
		poziom = (start_X <= x);
		pion = (start_Y <= y);
		absoluteX = poziom ? x - start_X : start_X - x;
		absoluteY = pion ? y - start_Y : start_Y - y;

		if (absoluteX >= absoluteY)
		{
			for (int posX = 0; posX < (absoluteX + 1); posX++)
			{
				if (absoluteX != 0) {
					if (pion && poziom)gotoxy(start_X + posX, start_Y + ((absoluteY)* (posX)) / (absoluteX));
					if (!pion && poziom)gotoxy(start_X + posX, start_Y - ((absoluteY)* (posX)) / (absoluteX));
					if (pion && !poziom)gotoxy(start_X - posX, start_Y + ((absoluteY)* (posX)) / (absoluteX));
					if (!pion && !poziom)gotoxy(start_X - posX, start_Y - ((absoluteY)* (posX)) / (absoluteX));
				}
				else
				{
					gotoxy(start_X, start_Y);
				}
				cputs("x");
			}
		}
		if (absoluteY > absoluteX)
		{
			for (int posY = 0; posY < (absoluteY + 1); posY++)
			{
				if (absoluteY != 0) {
					if (pion && poziom)gotoxy(start_X + ((absoluteX * posY) / absoluteY), start_Y + posY);
					if (!pion && poziom)gotoxy(start_X + ((absoluteX * posY) / absoluteY), start_Y - posY);
					if (pion && !poziom)gotoxy(start_X - ((absoluteX * posY) / absoluteY), start_Y + posY);
					if (!pion && !poziom)gotoxy(start_X - ((absoluteX * posY) / absoluteY), start_Y - posY);
				}
				else
				{
					gotoxy(start_X, start_Y);
				}
				cputs("x");
			}
		}
		zn = getch();
	} while (zn != 'l');

	if (absoluteX >= absoluteY)
	{
		for (int posX = 0; posX < (absoluteX + 1); posX++)
		{
			if (absoluteX != 0) {
				if (pion && poziom)*(buf + ((*info).width*(start_Y + (((absoluteY)* (posX)) / (absoluteX)) - 1) + (start_X + posX - picture_position))) = color;
				if (!pion && poziom)*(buf + (*info).width*(start_Y - (((absoluteY)* (posX)) / (absoluteX)) - 1) + (start_X + posX - picture_position)) = color;
				if (pion && !poziom)*(buf + (*info).width*(start_Y + (((absoluteY)* (posX)) / (absoluteX)) - 1) + (start_X - posX - picture_position)) = color;
				if (!pion && !poziom)*(buf + (*info).width*(start_Y - (((absoluteY)* (posX)) / (absoluteX)) - 1) + (start_X - posX - picture_position)) = color;

			}
			else
			{
				*(buf + (*info).width*start_Y + start_X);
			}

		}
	}
	if (absoluteY > absoluteX)
	{
		for (int posY = 0; posY < (absoluteY + 1); posY++)
		{
			if (absoluteY != 0) {
				if (pion && poziom)*(buf + (*info).width*(start_Y + posY - 1) + start_X + ((absoluteX * posY) / absoluteY) - picture_position) = color;
				if (!pion && poziom)*(buf + (*info).width*(start_Y - posY - 1) + start_X + ((absoluteX * posY) / absoluteY) - picture_position) = color;
				if (pion && !poziom)*(buf + (*info).width*(start_Y + posY - 1) + start_X - ((absoluteX * posY) / absoluteY) - picture_position) = color;
				if (!pion && !poziom)*(buf + (*info).width*(start_Y - posY - 1) + start_X - ((absoluteX * posY) / absoluteY) - picture_position) = color;
			}
			else
			{
				*(buf + (*info).width*start_Y + start_X) = color;
			}

		}
	}
	save_picture_stack(buf, vector, (*info).width, (*info).height);
}



