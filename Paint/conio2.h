/*
 * kod szablonu z przedmiotu Podstawy Programowania
 * do wykorzystania jedynie w ramach tego przedmiotu
 * autor: K.M. Ocetkiewicz
 */
#ifndef CONIO2_H
#define CONIO2_H
#define picture_position 40

#define BLACK		0
#define BLUE		1
#define GREEN		2
#define CYAN		3
#define RED		4
#define MAGENTA		5
#define BROWN		6
#define LIGHTGRAY	7
#define DARKGRAY	8
#define LIGHTBLUE	9
#define LIGHTGREEN	10
#define LIGHTCYAN	11
#define LIGHTRED	12
#define LIGHTMAGENTA	13
#define YELLOW		14
#define WHITE		15

#define _NOCURSOR	0
#define _SOLIDCURSOR	1
#define _NORMALCURSOR	2

#ifndef EOF
#define EOF		-1
#endif

#define LASTMODE	-1
#define C80		3
#define C4350		8
#define FULLSCREEN	0x8000

extern int _wscroll;		// 1 = enable scroll
				// 0 = disable scroll

struct text_info {
	unsigned char curx;
	unsigned char cury;
	unsigned short attribute;
	unsigned short normattr;
	unsigned char screenwidth;
	unsigned char screenheight;
	};

#ifdef __cplusplus
extern "C" {
#endif
void gotoxy(int x, int y);
int wherex(void);
int wherey(void);
void _setcursortype(int cur_t);

void textattr(int newattr);
void textbackground(int newcolor);
void textcolor(int newcolor);

void clreol(void);
void clrscr(void);
void delline(void);
void insline(void);

int getch(void);
int getche(void);
int kbhit(void);
int ungetch(int ch);

int cputs(const char *str);
int putch(int c);

int gettext(int left, int top, int right, int bottom, void *dest);
int movetext(int left, int top, int right, int bottom, int destleft, int desttop);
int puttext(int left, int top, int right, int bottom, void *source);

void gettextinfo(struct text_info *info);

struct wektor {         
	int used;
	int memorySize;
	int actualPosition;
	char *vec;
};

struct controls
{
	bool active_rectangle;
	bool active_line;
	int width;
	int height;
	int Argv;
	int scrollX;
	int scrollY;
};
char* int_to_array(int number);
void fill_name(char* name);
void textmode(int mode);
void new_picture(char *buff, wektor *vector, controls* info);
void write_picture(char *buff, int start, controls *info);
void filesave(char *buff, controls info, char *filename);
void fileopen(char *buff, wektor *vector, controls *info);
void fileopen_init(char *buff);
void fileopen_path(char *buff, wektor *vector, char *active, controls *info);
void bmpopen_path(char *buff, wektor *vector, char *active, controls *info, FILE *pfile);
void BMPmake(char* buf, char *active, controls *t);

void draw_line(char *buff, int x, int y, wektor *vector, controls *info, int color);
void draw_rectangle(char *buf, int x, int y, wektor *vector, controls *info, int color);
void XPMsave(controls *info, char *buff, char * filename);
void XPMload(char *buff, wektor *vector, char *active, controls *info, FILE *pFile);

void newVector(wektor *vector);
void changeMemory(wektor *vector, int reallocate_size);
void push(wektor *vector, char val);
char pop(wektor *vector);

void save_picture_stack(char * buf, wektor *vector, int width, int height);
void remove_picture_stack(wektor *vector, int width, int height);
void open_picture_stack(char * buf, wektor *vector, int width, int height);


// bonus functions
void settitle(const char *title);

int Conio2_Init(void);
#ifdef __cplusplus
}
#endif

#endif
