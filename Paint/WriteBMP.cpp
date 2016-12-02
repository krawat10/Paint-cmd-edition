#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"conio2.h"

unsigned char bitmap[1000];
void BMPmake(char* buf, char *active, controls *t)
{

	bitmap[0] = 'B';
	bitmap[1] = 'M';
	bitmap[2] = 54 + (*t).height*(*t).width*3; // + sizeofpicture	(pixel * 3)
	for (int i = 3; i < 10; i++) bitmap[i] = 0;
	bitmap[10] = 54;
	for (int i = 11; i < 14; i++) bitmap[i] = 0;
	bitmap[14] = 40;
	for (int i = 15; i < 18; i++) bitmap[i] = 0;
	bitmap[18] = (*t).width; 
	for (int i = 19; i < 22; i++) bitmap[i] = 0;
	bitmap[22] = (*t).height; 
	for (int i = 23; i < 26; i++) bitmap[i] = 0;
	bitmap[26] = 1;
	bitmap[27] = 0;
	bitmap[28] = 24; 
	for (int i = 29; i < 34; i++) bitmap[i] = 0;
	bitmap[34] = (*t).height*(*t).width * 3; 
	for (int i = 35; i < 40; i++) bitmap[i] = 0;
	bitmap[40] = 48;
	bitmap[41] = 177;
	bitmap[42] = 0;
	bitmap[43] = 0;
	bitmap[44] = 48;
	bitmap[45] = 177;
	for (int i = 46; i < 54; i++) bitmap[i] = 0;
	int c = 0;
	for (int i = (54 + (*t).height*(*t).width * 3 - 3), k = 1,  counter = 1 ; i >= 54 ; i = i - 3, counter++)
	{		
		c = k*(*t).width - counter;
			if (*(buf + c) == WHITE) { bitmap[i + 2] = 255; bitmap[i + 1] = 255; bitmap[i] = 255; }
			else if (*(buf + c) == BLACK) { bitmap[i + 2] = 0; bitmap[i + 1] = 0; bitmap[i] = 0; }
			else if (*(buf + c) == BLUE) { bitmap[i + 2] = 0; bitmap[i + 1] = 0; bitmap[i] = 255; }
			else if (*(buf + c) == GREEN) { bitmap[i + 2] = 0; bitmap[i + 1] = 128; bitmap[i] = 0; }
			else if (*(buf + c) == CYAN) { bitmap[i + 2] = 0; bitmap[i + 1] = 255; bitmap[i] = 255; }
			else if (*(buf + c) == RED) { bitmap[i + 2] = 255; bitmap[i + 1] = 0; bitmap[i] = 0; }
			else if (*(buf + c) == MAGENTA) { bitmap[i + 2] = 255; bitmap[i + 1] = 0; bitmap[i] = 255; }
			else if (*(buf +  c) == BROWN) { bitmap[i + 2] = 165; bitmap[i + 1] = 42; bitmap[i] = 42; }
			else if (*(buf +  c) == LIGHTGRAY) { bitmap[i + 2] = 211; bitmap[i + 1] = 211; bitmap[i] = 211; }
			else if (*(buf +  c) == DARKGRAY) { bitmap[i + 2] = 169; bitmap[i + 1] = 169; bitmap[i] = 169; }
			else if (*(buf +  c) == LIGHTBLUE) { bitmap[i + 2] = 173; bitmap[i + 1] = 216; bitmap[i] = 230; }
			else if (*(buf +  c) == LIGHTGREEN) { bitmap[i + 2] = 144; bitmap[i + 1] = 238; bitmap[i] = 144; }
			else if (*(buf +  c) == LIGHTCYAN) { bitmap[i + 2] = 224; bitmap[i + 1] = 255; bitmap[i] = 255; }
			else if (*(buf +  c) == LIGHTRED) { bitmap[i + 2] = 255; bitmap[i + 1] = 204; bitmap[i] = 203; }
			else if (*(buf +  c) == LIGHTMAGENTA) { bitmap[i + 2] = 255; bitmap[i + 1] = 119; bitmap[i] = 255; }
			else if (*(buf +  c) == YELLOW) { bitmap[i + 2] = 255; bitmap[i + 1] = 255; bitmap[i] = 0; }
			c++;
			if (counter == (*t).width)
			{
				k++;
				counter = 0;
			}
			
	}
	FILE *file;
	file = fopen(active, "w+");	
	for (int i = 0; i < (54 + (*t).height*(*t).width*3); i++)
	{
		fputc(bitmap[i], file);
	}
	fclose(file);
}

void bmpopen_path(char *buff, wektor *vector, char *active, controls *info, FILE *pFile)
{
	int bmpBuffer[1001][3];
	pFile = fopen(active, "r");
	for (int i = 0; i < 18; i++)
	{
		getc(pFile);
	}
	int SizeX = getc(pFile);

	for (int i = 0; i < 3; i++)
	{
		getc(pFile);
	}
	int sizeY = getc(pFile);
	(*info).width = SizeX;
	(*info).height = sizeY;
	for (int i = 0; i < 31; i++)
	{
		getc(pFile);
	}
	for (int i = 0; i < SizeX*sizeY; i++)
	{
		bmpBuffer[i][2] = getc(pFile);
		bmpBuffer[i][1] = getc(pFile);
		bmpBuffer[i][0] = getc(pFile);
	}

	for (int counter = 1, k = SizeX*sizeY - 1, l=1; k >= 0; counter++)
	{	
			if (bmpBuffer[l*SizeX - counter][0] == 255 && bmpBuffer[l*SizeX - counter][1] == 255 && bmpBuffer[l*SizeX - counter][2] == 255) *(buff + k) = WHITE;
			else if (bmpBuffer[l*SizeX - counter][0] == 0 && bmpBuffer[l*SizeX - counter][1] == 0 && bmpBuffer[l*SizeX - counter][2] == 255) *(buff + k) = BLUE;
			else if (bmpBuffer[l*SizeX - counter][0] == 0 && bmpBuffer[l*SizeX - counter][1] == 128 && bmpBuffer[l*SizeX - counter][2] == 0) *(buff + k) = GREEN;
			else if (bmpBuffer[l*SizeX - counter][0] == 0 && bmpBuffer[l*SizeX - counter][1] == 255 && bmpBuffer[l*SizeX - counter][2] == 255) *(buff + k) = CYAN;
			else if (bmpBuffer[l*SizeX - counter][0] == 255 && bmpBuffer[l*SizeX - counter][1] == 0 && bmpBuffer[l*SizeX - counter][2] == 0) *(buff + k) = RED;
			else if (bmpBuffer[l*SizeX - counter][0] == 255 && bmpBuffer[l*SizeX - counter][1] == 0 && bmpBuffer[l*SizeX - counter][2] == 255) *(buff + k) = MAGENTA;
			else if (bmpBuffer[l*SizeX - counter][0] == 165 && bmpBuffer[l*SizeX - counter][1] == 42 && bmpBuffer[l*SizeX - counter][2] == 42) *(buff + k) = BROWN;
			else if (bmpBuffer[l*SizeX - counter][0] == 211 && bmpBuffer[l*SizeX - counter][1] == 211 && bmpBuffer[l*SizeX - counter][2] == 211) *(buff + k) = LIGHTGRAY;
			else if (bmpBuffer[l*SizeX - counter][0] == 169 && bmpBuffer[l*SizeX - counter][1] == 169 && bmpBuffer[l*SizeX - counter][2] == 169) *(buff + k) = DARKGRAY;
			else if (bmpBuffer[l*SizeX - counter][0] == 173 && bmpBuffer[l*SizeX - counter][1] == 216 && bmpBuffer[l*SizeX - counter][2] == 230) *(buff + k) = LIGHTBLUE;
			else if (bmpBuffer[l*SizeX - counter][0] == 144 && bmpBuffer[l*SizeX - counter][1] == 238 && bmpBuffer[l*SizeX - counter][2] == 144) *(buff + k) = LIGHTGREEN;
			else if (bmpBuffer[l*SizeX - counter][0] == 224 && bmpBuffer[l*SizeX - counter][1] == 255 && bmpBuffer[l*SizeX - counter][2] == 255) *(buff + k) = LIGHTCYAN;
			else if (bmpBuffer[l*SizeX - counter][0] == 255 && bmpBuffer[l*SizeX - counter][1] == 204 && bmpBuffer[l*SizeX - counter][2] == 203) *(buff + k) = LIGHTRED;
			else if (bmpBuffer[l*SizeX - counter][0] == 255 && bmpBuffer[l*SizeX - counter][1] == 119 && bmpBuffer[l*SizeX - counter][2] == 255) *(buff + k) = LIGHTMAGENTA;
			else if (bmpBuffer[l*SizeX - counter][0] == 255 && bmpBuffer[l*SizeX - counter][1] == 255 && bmpBuffer[l*SizeX - counter][2] == 0) *(buff + k) = YELLOW;
			else if (bmpBuffer[l*SizeX - counter][0] == 0 && bmpBuffer[l*SizeX - counter][1] == 0 && bmpBuffer[l*SizeX - counter][2] == 0) *(buff + k) = BLACK;
			else *(buff + k) = BLACK;
			if (counter == SizeX)
			{
				l++;
				counter = 0;
			}
			k--;		
	}

}