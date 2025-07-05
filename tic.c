/*
CHEAT SHEET
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
#define WIN1    (3+5+7)
#define WIN2    (11+13+17)
#define WIN3    (19+23+29)
#define WIN4    (3+11+10)
#define WIN5    (5+13+23)
#define WIN6    (7+17+29)
#define WIN7    (3+13+29)
#define WIN8    (19+13+7)

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
    system("clear");  
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
        int c = getchar(); // Read a character
        if (_isNumber(c)) {
            // Convert the character digit to its integer value
            // by subtracting the ASCII value of '0'
            int number = c - '0';
            return (number -1);
        } else if(c != 10){
            printf("Invalido: No es un numero\n");
            if(retries > INTENTOS)  return 0xFFFF;
        }
    }while(1);
}


void _add_points(int *points, int ip, int play){
    points[ip] = play+1;
    return;
}

int _check_win(int *m, int target){

    if      ((m[0] == target) && (m[1] == target) && (m[2] == target))  return 1;
    else if ((m[3] == target) && (m[4] == target) && (m[5] == target))  return 1;
    else if ((m[6] == target) && (m[7] == target) && (m[8] == target))  return 1;

    else if ((m[0] == target) && (m[4] == target) && (m[8] == target))  return 1;
    else if ((m[6] == target) && (m[4] == target) && (m[2] == target))  return 1;

    else if ((m[0] == target) && (m[3] == target) && (m[6] == target))  return 1;
    else if ((m[1] == target) && (m[4] == target) && (m[7] == target))  return 1;
    else if ((m[2] == target) && (m[5] == target) && (m[8] == target))  return 1;

    return 0;
}

void _won_msg(int player){
    printf("\n#### WINNER ###\n");
    printf("-- PLAYER %d --\n", (player+1));
    printf("##############\n");
}

void main(){
    // init moves
    int moves[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    int player = 0;
    int play;
    int plays = 0;
    // tablero

    do{   
        _tablero(moves);
        
        printf("\nPlayer %d Selecciona tu jugada: ", (player+1));
        play = get_play(player);
        if(play > MOVIMIENTOS){
            printf("*******/n FINALIZADO POR ERROR DE JUGADOR /n ********");
            return;
        }
        
        // ver si ya se hizo la jugada
        if((moves[play] == P1_CENTER) || (moves[play] == P2_CENTER)){
            printf("Jugada repetida! \n");
            continue;  
        } 
            
        if(!player){
            moves[play] = P1_CENTER;
            if(_check_win(&moves[0], P1_CENTER)){
                _tablero(moves);
                _won_msg(player);
                return;
            }
        }else{
            moves[play] = P2_CENTER;
            if(_check_win(&moves[0], P2_CENTER)){
                _tablero(moves);
                _won_msg(player);
                return;
            }
        }

        if(!player) player = 1;
        else        player = 0;
            
        plays++;
    }while(plays < MOVIMIENTOS);
    
    return;
}