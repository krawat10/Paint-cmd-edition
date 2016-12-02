#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"conio2.h"

void XPMsave(controls *info, char *buff, char * filename)
{
	char header[] = { '!', ' ', 'X', 'P', 'M', '2', '\n' , '\0'};
	char Xx = (char)(((*info).width / 10) + 48);
	char xX = (char)(((*info).width % 10) + 48);
	char Yy = (char)(((*info).height / 10) + 48);
	char yY = (char)(((*info).width % 10) + 48);
	char size[] = { Xx, xX, ' ', Yy, yY, ' ', '1', '6', ' ', '1', '\n', '\0' };
	char color[] = {
		'a', ' ', 'c', ' ', '#', 'f', 'f', 'f', 'f', 'f', 'f', '\n',//white
		'b', ' ', 'c', ' ', '#', '0', '0', '0', '0', 'f', 'f', '\n',//blue
		'c', ' ', 'c', ' ', '#', '0', '0', '8', '0', '0', '0', '\n',//green
		'd', ' ', 'c', ' ', '#', '0', '0', 'f', 'f', 'f', 'f', '\n',//cyan
		'e', ' ', 'c', ' ', '#', 'f', 'f', '0', '0', '0', '0', '\n',//red
		'f', ' ', 'c', ' ', '#', 'f', 'f', '0', '0', 'f', 'f', '\n',//magneta
		'g', ' ', 'c', ' ', '#', 'a', '5', '2', 'a', '2', 'f', '\n',//brown
		'h', ' ', 'c', ' ', '#', 'd', '3', 'd', '3', 'd', '3', '\n',//lightgray
		'i', ' ', 'c', ' ', '#', 'a', '9', 'a', '9', 'a', '9', '\n',//darkgray
		'j', ' ', 'c', ' ', '#', 'a', 'd', 'd', '8', 'e', '6', '\n',//lightblue
		'k', ' ', 'c', ' ', '#', '9', '0', 'e', 'e', '9', '0', '\n',//lightgreen
		'l', ' ', 'c', ' ', '#', 'e', '0', 'f', 'f', 'f', 'f', '\n',//lightcyan
		'm', ' ', 'c', ' ', '#', 'f', 'f', 'a', '0', '7', 'a', '\n',//lightred
		'n', ' ', 'c', ' ', '#', 'f', '4', '6', '6', 'c', 'c', '\n',//lightmagneta
		'o', ' ', 'c', ' ', '#', 'f', 'f', 'f', 'f', '0', '0', '\n',//yellow
		'p', ' ', 'c', ' ', '#', '0', '0', '0', '0', '0', '0', '\0'//black
	};
	
		
	FILE *file;
	file = fopen(filename, "w");
	fputs(header, file);
	fputs(size, file);
	fputs(color, file);
	for (int i = 0; i < (*info).width*(*info).height; i++)
	{		
		if (i % ((*info).width) == 0 && i != 1)fputc('\n', file);		
		if (*(buff + i) == BLUE)fputc('b', file);
		else if (*(buff + i) == GREEN)fputc('c', file);
		else if (*(buff + i) == CYAN)fputc('d', file);
		else if (*(buff + i) == RED)fputc('e', file);
		else if (*(buff + i) == MAGENTA)fputc('f', file);
		else if (*(buff + i) == BROWN)fputc('g', file);
		else if (*(buff + i) == LIGHTGRAY)fputc('h', file);
		else if (*(buff + i) == DARKGRAY)fputc('i', file);
		else if (*(buff + i) == LIGHTBLUE)fputc('j', file);
		else if (*(buff + i) == LIGHTGREEN)fputc('k', file);
		else if (*(buff + i) == LIGHTCYAN)fputc('l', file);
		else if (*(buff + i) == LIGHTRED)fputc('m', file);
		else if (*(buff + i) == LIGHTMAGENTA)fputc('n', file);
		else if (*(buff + i) == YELLOW)fputc('o', file);
		else if (*(buff + i) == WHITE)fputc('a', file);
		else fputc('p', file);		
	}
	fclose(file);
}

void XPMload(char *buff, wektor *v, char *active, controls *info, FILE *pFile)
{		
	for (int i = 0; i < 7;i++)
	{
		getc(pFile);
	}	
	int x = (getc(pFile) - 48)*10 + (getc(pFile) - 48);
	getc(pFile);
	int y = (getc(pFile) - 48) * 10 + (getc(pFile) - 48);
	(*info).width = x;
	(*info).height = y;
	char tmp;
	for (int i = 0; i < 198; i++)
	{
		tmp = getc(pFile);
	}
	for (int i = 0; i < (*info).width*(*info).height; i++)
	{
		tmp = getc(pFile);
		if (tmp == 'b') *(buff + i) = BLUE;
		else if (tmp == 'c') *(buff + i) = GREEN;
		else if (tmp == 'd')*(buff + i) = CYAN;
		else if (tmp == 'e')*(buff + i) = RED;
		else if (tmp == 'f')*(buff + i) = MAGENTA;
		else if (tmp == 'g')*(buff + i) = BROWN;
		else if (tmp == 'h')*(buff + i) = LIGHTGRAY;
		else if (tmp == 'i')*(buff + i) = DARKGRAY;
		else if (tmp == 'j')*(buff + i) = LIGHTBLUE;
		else if (tmp == 'k')*(buff + i) = LIGHTGREEN;
		else if (tmp == 'l')*(buff + i) = LIGHTCYAN;
		else if (tmp == 'm')*(buff + i) = LIGHTRED;
		else if (tmp == 'n')*(buff + i) = LIGHTMAGENTA;
		else if (tmp == 'o')*(buff + i) = YELLOW;
		else if (tmp == 'a')*(buff + i) = WHITE;
		else if (tmp == '\n')i--;//gdy znajdzie nowy wiersz
		else *(buff + i) = BLACK;

	}	
	fclose(pFile);
}