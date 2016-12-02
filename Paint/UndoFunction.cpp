#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"conio2.h"

void save_picture_stack(char * buf, wektor *v, int width, int height)
{
	for (int i = width*height - 1; i >= 0 ; i--)
	{
		push(v, *(buf + i));
	}
	v->used++;
}

void remove_picture_stack(wektor *v, int width, int height)
{
	for (int i = 0; i < width*height; i++)
	{
		pop(v);
	}
	v->used--;
}

void open_picture_stack(char * buf, wektor *v, int width, int height)
{
	if(v->used > 0){
	remove_picture_stack(v, width, height);
	for (int i = 0; i < width*height; i++)
	{
		*(buf + i) = pop(v);
	}
	save_picture_stack(buf, v, width, height);
	v->used--;
	}
	return;
}