
#include "kscreen.h"


uint8_t cursor_x = 0;
uint8_t cursor_y = 0;


struct screen_entry
{
	char value;
	unsigned fgcolor : 4;
	unsigned bgcolor : 4;
}__attribute__((packed));

static struct screen_entry *vidmem = (struct screen_entry *)0xb8000;


// Updates the hardware cursor.
static void move_cursor()
{
    uint16_t cursorLocation = cursor_y * 80 + cursor_x;
    vga_io_w(VGA_CRT_IC, VGA_CRTC_CURSOR_HI);  
    vga_io_w(VGA_CRT_DC, cursorLocation >> 8); 
    vga_io_w(VGA_CRT_IC, VGA_CRTC_CURSOR_LO); 
    vga_io_w(VGA_CRT_DC, cursorLocation);      
}


static void scroll(void)
{
	struct screen_entry blank;
	blank.bgcolor	= SCREEN_COLOR_BLACK;
	blank.fgcolor	= SCREEN_COLOR_WHITE;
	blank.value		= ' ';
	if (cursor_y >= SCREEN_HEIGHT)
	{
		int i;
		for (i = 0*80; i < (25 - 1)*80; ++i)
			vidmem[i] = vidmem[i + SCREEN_WIDTH];
		for (i = (SCREEN_HEIGHT - 1)*SCREEN_WIDTH; i < SCREEN_HEIGHT*SCREEN_WIDTH; ++i)
			vidmem[i] = blank;
		cursor_y = SCREEN_HEIGHT - 1;
	}
}

static void kput_entry(struct screen_entry _entry)
{
	switch (_entry.value)
	{
		case 0x08:
			if (cursor_x)
				cursor_x--;
			break;
		case 0x09:
			cursor_x = (cursor_x+8) & ~(8-1);
			break;
		case '\r':
			cursor_x = 0;
			break;
		case '\n':
			cursor_x = 0;
			cursor_y++;
			break;
		default:
			if (_entry.value >= ' ')
			{
				vidmem[cursor_y * SCREEN_WIDTH + cursor_x] = _entry;
				cursor_x++;
			}
			break;
	}
	if (cursor_x >= SCREEN_WIDTH)
	{
		cursor_x = 0;
		cursor_y ++;
	}
	scroll();
	move_cursor();
}

void kcls(void)
{
	struct screen_entry blank;
	blank.bgcolor	= SCREEN_COLOR_BLACK;
	blank.fgcolor	= SCREEN_COLOR_WHITE;
	blank.value		= ' ';
	int i;
	for (i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
		vidmem[i] = blank;
	cursor_x = 0;
	cursor_y = 0;
	move_cursor();
}

void kputc(char _c)
{
	struct screen_entry entry;
	entry.bgcolor	= SCREEN_COLOR_BLACK;
	entry.fgcolor	= SCREEN_COLOR_WHITE;
	entry.value		= _c;
	kput_entry(entry);
}



void kputs(char *_str)
{
	int i = -1;
	do kputc(_str[i++]);
	while(_str[i]);
}

