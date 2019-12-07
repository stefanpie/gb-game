#include <gb/gb.h>
#include <stdio.h>
#include <rand.h>
#include "number_sprites.c"
#include "background_sprites.c"


UINT8 spritesize = 8;
UINT16 simple_tile_grid[16];

void setup_tile_grid_values(){
    UINT16 i = 0;
    for(i = 0; i < 16; i++){
        simple_tile_grid[i] = i;
    }
    
}

// Utility function to swap two elements A[i] and A[j] in the array
void swap(UINT16 A[], int i, int j) {
	UINT16 temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}

// Function to shuffle an array A[] of n elements
void shuffle_tile_grid()
{
    int i;
    for(i=0;i<16;i++){
        swap(simple_tile_grid,i,i+(((int)rand)%(16-i)));
    }
}

void setup_blank_bg(){
    UINT16 i;
    UINT16 j;
    unsigned char bg_array[] = {0x42};
    for (i = 0; i < 32; i++){
        for (j = 0; j < 32; j++){
            set_bkg_tiles(i,j,1,1, &bg_array);
        }
    }
    
}

void draw_tile_grid(){
    UINT16 i;
    UINT16 sprite_offset;
    UINT16 x;
    UINT16 y;
    UINT16 width = 16;
    UINT16 height = 16;
    unsigned char bg_array[4];
    for(i = 0; i < 16; i++){

        x = ((i % 4)*2) + 6;
        y = ((i / 4)*2) + 5;


        // printf("%d\n", (int)tile_grid[i].tile_grid_idx);

        
        sprite_offset = (simple_tile_grid[i])*4;

        
        if (simple_tile_grid[i]==15){
            bg_array[0] = 0x42;
            bg_array[1] = 0x42;
            bg_array[2] = 0x42;
            bg_array[3] = 0x42;
        }
        else{
            bg_array[0] = 0+sprite_offset;
            bg_array[1] = 2+sprite_offset;
            bg_array[2] = 1+sprite_offset;
            bg_array[3] = 3+sprite_offset;
        }
        set_bkg_tiles(x, y, 2, 2, &bg_array);
    }    
}

void setup_tile_grid_border(){
    unsigned char h_border[] = {0x3d,0x3d,0x3d,0x3d,0x3d,0x3d,0x3d,0x3d};
    unsigned char v_border[] = {0x3c,0x3c,0x3c,0x3c,0x3c,0x3c,0x3c,0x3c};
    unsigned char c_ul[] = {0x3e};
    unsigned char c_ur[] = {0x3f};
    unsigned char c_ll[] = {0x41};
    unsigned char c_lr[] = {0x40};

    set_bkg_tiles(6, 4, 8, 1, &h_border);
    set_bkg_tiles(6, 13, 8, 1, &h_border);

    set_bkg_tiles(5, 5, 1, 8, &v_border);
    set_bkg_tiles(14, 5, 1, 8, &v_border);

    set_bkg_tiles(5, 4, 1, 1, &c_ul);
    set_bkg_tiles(14, 4, 1, 1, &c_ur);
    set_bkg_tiles(5, 13, 1, 1, &c_ll);
    set_bkg_tiles(14, 13, 1, 1, &c_lr);
}

void slide(unsigned int direction){
    UINT16 idx_of_16;
    UINT16 idx_of_left;
    UINT16 i;
    INT16 x_16;
    INT16 y_16;
    INT16 x_left;
    INT16 y_left;
    UINT16 temp_value;
    
    for(i = 0; i< 16; i++){
        // printf("%d\n", (int)simple_tile_grid[i]);
        if((int)simple_tile_grid[i] == 15){
            idx_of_16 = i;
            break;
            
        }
    }

    x_16 = idx_of_16 % 4;
    y_16 = idx_of_16 / 4;
    if(direction == J_RIGHT){
        x_left = x_16 - 1;
        y_left = y_16;
    }
    if(direction == J_LEFT){
        x_left = x_16 + 1;
        y_left = y_16;
    }
    if(direction == J_UP){
        x_left = x_16 ;
        y_left = y_16 + 1;
    }
    if(direction == J_DOWN){
        x_left = x_16 ;
        y_left = y_16 - 1;
    }

    
    idx_of_left = x_left + (4*y_left);
    if((x_left >= 0 ) && (x_left < 4)){
        if((y_left >= 0 ) && (y_left < 4)){
            temp_value = simple_tile_grid[idx_of_16];
            simple_tile_grid[idx_of_16] = simple_tile_grid[idx_of_left];
            simple_tile_grid[idx_of_left] = temp_value;
            draw_tile_grid();
        }
    }
}

void main(){
    SPRITES_8x8;

    set_bkg_data(0,60,number_sprites);
    set_bkg_data(60,7,background_sprites);
    setup_tile_grid_values();
    initarand(DIV_REG);
    shuffle_tile_grid();
    setup_blank_bg();
    draw_tile_grid();
    setup_tile_grid_border();

    DISPLAY_ON;
    SHOW_BKG;
    while(1) {
        unsigned int press = joypad();
        switch(press) {
            case J_LEFT:
            case J_RIGHT:
            case J_UP:
            case J_DOWN:
                slide(press);
                break;
            case J_START:
                break;
            case J_SELECT:
                break;
            case J_A:
                break;
            case J_B:
                break;
        }
        delay(100);
    }
}