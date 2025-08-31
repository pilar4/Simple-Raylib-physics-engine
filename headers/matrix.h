#ifndef MATRIX_H
#define MATRIX_H
#include "const.h"
//creating and initializing matrix with basic values that should be assigned at start

char matrix[bx][by];

void clearMatrix(void){
    for (int i = 1; i < bx; i++) {
        for (int j = 1; j < by; j++) {
            matrix[i][j] = '0';
        }
    }
}

void iniBarriers(void){
    for(int cell = 1; cell<bx; cell++){
        matrix[cell][1]='b';
        matrix[cell][by-1]='b';
    }        
    for(int cell = 1; cell<by; cell++){
        matrix[1][cell]='b';
        matrix[bx-1][cell]='b';
    }    
}


void iniMatrix(void){
    clearMatrix();
    iniBarriers();
}


#endif