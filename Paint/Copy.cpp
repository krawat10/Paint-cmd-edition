#include<stdlib.h>
#include <stdio.h>
#include"conio2.h"

void copy(char *buf, int x, int y, char* copy, controls *info)
{	
	int zn = 0;
	int start_X = x;  //pozycje startowe
	int start_Y = y;  //pozycje startowe
	(*info).copy_poziom;
	(*info).copy_pion;
	int absoluteX;
	int absoluteY;
	do
	{
		if (zn == 0x98) y--;
		else if (zn == 0xa0) y++;
		else if (zn == 0x9b) x--;
		else if (zn == 0x9d) x++;
		else if (zn == 27) return;
		gotoxy(x, y);
		write_picture(buf, picture_position, info);
		(*info).copy_poziom = (start_X <= x);
		(*info).copy_pion = (start_Y <= y);
		absoluteX = (*info).copy_poziom ? x - start_X : start_X - x;
		absoluteY = (*info).copy_pion ? y - start_Y : start_Y - y;

		for (int posY = 0; posY < (absoluteY + 1); posY++)  //petla na osi Y
		{
			for (int posX = 0; posX < (absoluteX + 1); posX++) //rysowanie 'x' na osi X 
			{
				if ((*info).copy_pion && (*info).copy_poziom)gotoxy(start_X + posX, start_Y + posY);
				if (!(*info).copy_pion && (*info).copy_poziom)gotoxy(start_X + posX, start_Y - posY);
				if ((*info).copy_pion && !(*info).copy_poziom)gotoxy(start_X - posX, start_Y + posY);
				if (!(*info).copy_pion && !(*info).copy_poziom)gotoxy(start_X - posX, start_Y - posY);
				cputs("x");
			}
		}
		zn = getch();
	} while (zn != 'c'); //dopóki nie zatwierdzimy przyciskiem k to dalej rysujemy
	if (zn == 27)return;

	
	(*info).copyWidth = absoluteX + 1;
	(*info).copyHeight = absoluteY + 1;
	(*info).active_copy = true;

	for (int posY = 0, i = 0; posY < (absoluteY + 1); posY++)
	{
		for (int posX = 0; posX < (absoluteX + 1); posX++) //zapisywanie w g³ównym buforze.
		{
			if ((*info).copy_pion && (*info).copy_poziom) *(copy + i) = *(buf + ((*info).width*(start_Y + posY - 1) + (start_X + posX - picture_position)));
			if (!(*info).copy_pion && (*info).copy_poziom)*(copy + i) = *(buf + ((*info).width*(start_Y - posY - 1) + (start_X + posX - picture_position)));
			if ((*info).copy_pion && !(*info).copy_poziom)*(copy + i) = *(buf + ((*info).width*(start_Y + posY - 1) + (start_X - posX - picture_position)));
			if (!(*info).copy_pion && !(*info).copy_poziom)*(copy + i) = *(buf + ((*info).width*(start_Y - posY - 1) + (start_X - posX - picture_position)));
			i++;
		}
	}	
}

void paste(char *buf, int x, int y, char* copy, controls *info, wektor *vector)
{
	int i = 0;
	for (int posY = 0; posY < (*info).copyHeight; posY++)
	{
		for (int posX = 0; posX < (*info).copyWidth; posX++) //zapisywanie w g³ównym buforze.
		{					
			if ((*info).copy_pion && (*info).copy_poziom)*(buf + ((*info).width*(y + posY - 1) + (x + posX - picture_position))) = *(copy + i);
			if (!(*info).copy_pion && (*info).copy_poziom)*(copy + i) = *(buf + ((*info).width*(y - posY - 1) + (x + posX - picture_position))) = *(copy + i);
			if ((*info).copy_pion && !(*info).copy_poziom)*(copy + i) = *(buf + ((*info).width*(y + posY - 1) + (x - posX - picture_position))) = *(copy + i);
			if (!(*info).copy_pion && !(*info).copy_poziom)*(copy + i) = *(buf + ((*info).width*(y - posY - 1) + (x - posX - picture_position))) = *(copy + i);
			i++;
		}
	}
	save_picture_stack(buf, vector, (*info).width, (*info).height);
}