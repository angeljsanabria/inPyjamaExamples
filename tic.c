/*
CHEATSHEET
gcc tic.c -o app
./app

gcc tic.c -o app && ./app

*/

#include<stdio.h>
#include<string.h>


#define XPER_CELL 7
#define XPER_CENTER_CELL ((XPER_CELL/2)+1)
#define YPER_CELL 3
#define X_CELL 3
#define Y_CELL 3
#define XCELL_CHAR '-'
#define YCELL_CHAR '|'
#define CELL_NONE 0x20
#define SALTO_LINEA() printf("\n");
#define REGIONES 3
#define RENGLONES 3
#define P1_CENTER 'O'
#define P2_CENTER 'X'
#define MOVIMIENTOS 9
#define INTENTOS 3

void _lineah(){
    int hsize = (int)(XPER_CELL*X_CELL);
    for(int x= 0; x<= hsize; x++)   printf("%c", XCELL_CHAR);
}


void _tablero (int* mv){

    int x;
    int hsize = (int)(XPER_CELL*X_CELL);
    int isycenter = 0;

    int move = 0;
    int region, yregion;
    _lineah();
    SALTO_LINEA();
    for (region = 0; region < REGIONES; region++){
        for (yregion = 0; yregion <= RENGLONES; yregion++){  
            isycenter = 0;          
            if(yregion == YPER_CELL){
                _lineah();
                SALTO_LINEA(); 
                break;
            }else if (yregion == (int)(YPER_CELL/2)){
                isycenter = 1;
            }

            int xoffset=0;
            for(x= 0; x<= hsize; x++){
                int isxcenter = 0;
                //printf("%d", XPER_CENTER_CELL);
                if((x==0) || (x % XPER_CELL == 0)){
                    printf("%c", YCELL_CHAR);
                    if(x) xoffset = xoffset + XPER_CELL;
                }          
                else if (isycenter && ((x % (xoffset+XPER_CENTER_CELL)) == 0)){
                    printf("%c", mv[move]);
                    move++;
                }      
                else    printf("%c", CELL_NONE);
                
            }
            SALTO_LINEA(); 
        }
    }

    SALTO_LINEA();

    
    return;
}

int _isNumber(int n){
    if ((n < 0x30) || (n>0x39)) return 0;
    return 1;
}

int get_play(int player){
    
    int retries = 0;
    do{
        retries++;
        printf("Player %d Selecciona tu jugada: ", (player+1));
        int c = getchar(); // Read a character
        if (_isNumber(c)) {
            // Convert the character digit to its integer value
            // by subtracting the ASCII value of '0'
            int number = c - '0' -1;
            return number;
        } else if(c != 10){
            printf("Invalido: No es un numero\n");
            if(retries > INTENTOS)  return 0xFFFF;
        }

    }while(1);

}


void main(){
    // init moves
    int moves[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    int player = 0;
    int play;
    // tablero
    for (int plays = 0; plays < MOVIMIENTOS; plays++){

        _tablero(moves);
        play = get_play(player);
        if(play > MOVIMIENTOS){
            printf("*******/n FINALIZADO POR ERROR DE JUGADOR /n ********");
            return;
        }
        if(!player){
            moves[play] = P1_CENTER;
            player++;
        }else{
            moves[play] = P2_CENTER;
            player = 0;

        }

    }
    
    return;
}