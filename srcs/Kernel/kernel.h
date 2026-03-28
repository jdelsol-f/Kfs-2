#ifndef KERNEL_H
# define KERNEL_H

#include "Colors/Color.h"
#include "Printf/printf.h"
#include "terminal-management/term.h"
#include "Write_functions/write_functions.h"

/* type vars */

typedef struct s_screen
{
    uint16_t buffer[2125];
    int col;
    int row;
}t_screen;  

typedef enum e_bool
{
    true = 1,
    false = 0
}   t_bool;

typedef unsigned char   uint8_t;
typedef unsigned short  uint16_t;
typedef unsigned int    uint32_t;
typedef char            int8_t;
typedef short           int16_t;
typedef int             int32_t;
typedef unsigned        size_t;

/* sys vars */

#define VGA_WIDTH   80
#define VGA_HEIGHT  25
#define VGA_MEMORY  0xB8000

/* Functions */

void term_init();
void term_scrolling();
void term_putentryat(char c, uint8_t color, size_t col, size_t row);
void term_putchar(char c);
size_t strlen(const char* str);
void term_write(const char* data, size_t size)
size_t strlen(const char* str);

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg);
static inline uint16_t vga_entry(unsigned char uc, uint8_t color) ;
uint8_t term_setcolor(uint8_t color);

#endif