#ifndef SAND_H
#define SAND_H
#include "const.h"
#include "matrix.h"

void makeSand(int mousex, int mousey){
    matrix[mousex][mousey] = 's';
}

void gravitySand(int tick){
    for(int x=1;x<bx;x++){
        for(int y=1;y<by;y++){
            if(matrix[x][y]=='s' && matrix[x][y+1]=='0'){
                matrix[x][y]='0';
                matrix[x][y+1]='s';
            }
            
        }
    }
}



#endif