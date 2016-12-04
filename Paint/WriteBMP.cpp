#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"conio2.h"


void BMPmake(char* buf, char *active, controls *t)
{
	unsigned char bmpBuffer[54 + 50 * 20 * 3] = {};
	//unsigned char *bmpBuffer = (unsigned char*)malloc(sizeof(char) * 50 * 20);
	bmpBuffer[0] = 'B';
	bmpBuffer[1] = 'M';
	bmpBuffer[2] = 54 + (*t).height*(*t).width*3; // + wymiary pliku (pixel * 3)
	for (int i = 3; i < 10; i++) bmpBuffer[i] = 0;
	bmpBuffer[10] = 54;
	for (int i = 11; i < 14; i++) bmpBuffer[i] = 0;
	bmpBuffer[14] = 40;
	for (int i = 15; i < 18; i++) bmpBuffer[i] = 0;
	bmpBuffer[18] = (*t).width; 
	for (int i = 19; i < 22; i++) bmpBuffer[i] = 0;
	bmpBuffer[22] = (*t).height; 
	for (int i = 23; i < 26; i++) bmpBuffer[i] = 0;
	bmpBuffer[26] = 1;
	bmpBuffer[27] = 0;
	bmpBuffer[28] = 24; 
	for (int i = 29; i < 34; i++) bmpBuffer[i] = 0;
	bmpBuffer[34] = (*t).height*(*t).width * 3; 
	for (int i = 35; i < 40; i++) bmpBuffer[i] = 0;
	bmpBuffer[40] = 48;
	bmpBuffer[41] = 177;
	bmpBuffer[42] = 0;
	bmpBuffer[43] = 0;
	bmpBuffer[44] = 48;
	bmpBuffer[45] = 177;
	for (int i = 46; i < 54; i++) bmpBuffer[i] = 0;
	int c = 0;
	for (int i = (54 + (*t).height*(*t).width * 3 - 3), k = 1,  counter = 1 ; i >= 54 ; i = i - 3, counter++)
	{		
		c = k*(*t).width - counter; //zapisywanie obrazu w bmp jest od dolnego rogu obrazu
			if (*(buf + c) == WHITE) { bmpBuffer[i + 2] = 254; bmpBuffer[i + 1] = 254; bmpBuffer[i] = 254; } // kolory zapisywanie nie RGB tylko BGR
			else if (*(buf + c) == BLACK) { bmpBuffer[i + 2] = 1; bmpBuffer[i + 1] = 1; bmpBuffer[i] = 1; }
			else if (*(buf + c) == BLUE) { bmpBuffer[i + 2] = 0; bmpBuffer[i + 1] = 0; bmpBuffer[i] = 255; }
			else if (*(buf + c) == GREEN) { bmpBuffer[i + 2] = 0; bmpBuffer[i + 1] = 128; bmpBuffer[i] = 0; }
			else if (*(buf + c) == CYAN) { bmpBuffer[i + 2] = 0; bmpBuffer[i + 1] = 255; bmpBuffer[i] = 255; }
			else if (*(buf + c) == RED) { bmpBuffer[i + 2] = 255; bmpBuffer[i + 1] = 0; bmpBuffer[i] = 0; }
			else if (*(buf + c) == MAGENTA) { bmpBuffer[i + 2] = 255; bmpBuffer[i + 1] = 0; bmpBuffer[i] = 255; }
			else if (*(buf +  c) == BROWN) { bmpBuffer[i + 2] = 165; bmpBuffer[i + 1] = 42; bmpBuffer[i] = 42; }
			else if (*(buf +  c) == LIGHTGRAY) { bmpBuffer[i + 2] = 211; bmpBuffer[i + 1] = 211; bmpBuffer[i] = 211; }
			else if (*(buf +  c) == DARKGRAY) { bmpBuffer[i + 2] = 169; bmpBuffer[i + 1] = 169; bmpBuffer[i] = 169; }
			else if (*(buf +  c) == LIGHTBLUE) { bmpBuffer[i + 2] = 173; bmpBuffer[i + 1] = 216; bmpBuffer[i] = 230; }
			else if (*(buf +  c) == LIGHTGREEN) { bmpBuffer[i + 2] = 144; bmpBuffer[i + 1] = 238; bmpBuffer[i] = 144; }
			else if (*(buf +  c) == LIGHTCYAN) { bmpBuffer[i + 2] = 224; bmpBuffer[i + 1] = 255; bmpBuffer[i] = 255; }
			else if (*(buf +  c) == LIGHTRED) { bmpBuffer[i + 2] = 255; bmpBuffer[i + 1] = 204; bmpBuffer[i] = 203; }
			else if (*(buf +  c) == LIGHTMAGENTA) { bmpBuffer[i + 2] = 255; bmpBuffer[i + 1] = 119; bmpBuffer[i] = 255; }
			else if (*(buf +  c) == YELLOW) { bmpBuffer[i + 2] = 255; bmpBuffer[i + 1] = 255; bmpBuffer[i] = 0; }
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
		fputc(bmpBuffer[i], file);
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
	for (int i = 0; i < SizeX*sizeY; i++) //odczyt kolorów pikseli
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