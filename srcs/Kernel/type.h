#ifndef TYPE_H
# define TYPE_H

# define VGA_WIDTH   80
# define VGA_HEIGHT  25
# define VGA_MEMORY  0xB8000
# define VGA_COLS VGA_WIDTH
# define VGA_ROWS VGA_HEIGHT
# define CONSOLEPROMT "[KFS]> "

#define NULL ( (void *) 0)
typedef unsigned char   uint8_t;
typedef unsigned short  uint16_t;
typedef unsigned int    uint32_t;
typedef char            int8_t;
typedef short           int16_t;
typedef int             int32_t;
typedef unsigned        size_t;
typedef char            bool;

typedef enum e_bool
{
    true = 1,
    false = 0
}   t_bool;

typedef struct s_prompt
{
    int col;
    int row;
}t_prompt;

typedef struct s_screen
{
    uint16_t buffer[2125];
    int col;
    int row;
    t_prompt prompt;
    uint8_t term_color;
}t_screen;   

typedef struct s_gdt
{
    uint8_t *addr;
    uint8_t *start;
    uint8_t *kernel_code;
    uint8_t *kernel_data;
    uint8_t *kernel_stack;
    uint8_t *user_code;
    uint8_t *user_data;
    uint8_t *user_stack;
    
}   t_gdt;

typedef struct s_general_struct //reminder to find an appropriate name
{
    int row;
    int col;
    t_screen term_one;
    t_screen term_two;
    int buff_indicator;
    t_prompt term_prompt;
    uint8_t term_color;
    t_gdt   my_gdt;
} t_general_struct;
 


#endif