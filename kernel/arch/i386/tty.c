#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include <kernel/tty.h>

#include "vga.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

void terminal_initialize(void)
{
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    terminal_row = 0;
    terminal_column = 0;
    terminal_buffer = VGA_MEMORY;

    for(size_t y=0; y <= terminal_column ; y++)
    {
        for(size_t x=0; x <= terminal_row ; x++)
        {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ',terminal_color);
        }
    }

}

void terminal_setcolor(uint8_t color)
{
    terminal_color = color;
}

void terminal_putentryat(unsigned char c, uint8_t color, int x, int y)
{
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(c,color);
}

void terminal_scroll(void)
{
    // row 2 becomes row 1 , 3 becomes 2 and such ; delete the first row and shift the lower rows by 1
    for(size_t y=1; y<VGA_HEIGHT; y++)
    {
        for(size_t x=0; x<VGA_WIDTH; x++)
        {
            terminal_buffer[(y-1)*VGA_WIDTH+x] = terminal_buffer[y*VGA_WIDTH+x];
        }
    }
    // delete the last row 
    for(size_t x=0; x<VGA_WIDTH; x++)
    {
        terminal_buffer[ (VGA_HEIGHT-1) * VGA_WIDTH + x ] = vga_entry(' ', terminal_color);
    }
}

void terminal_putchar(char c)
{
    unsigned char uc = c;

    terminal_putentryat(uc,terminal_color,terminal_column,terminal_row);
    terminal_column++;
    //when column becomes 80(end of width) -> next row and column = 0
    if(terminal_column == VGA_WIDTH)
    {
        terminal_column = 0;
        terminal_row++;
    }
    //when last row -> scroll and set row to last 
    if(terminal_row == VGA_HEIGHT)
    {
        terminal_scroll();
        terminal_row = VGA_HEIGHT - 1;
    }
}

void terminal_write(const char* data, size_t size)
{
    for(size_t i=0; i<size ; i++)
    {
        terminal_putchar(data[i]);
    }
}

void terminal_writestring(const char* data)
{
    terminal_write(data,strlen(data));
}