
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAXSTEPS 300
typedef struct BENDERUNIT *BB;
void print_map(char** map, int rows){
    for(int i = 0; i < rows; i++){
        printf("%s", map[i]);
    }
    return;
}


struct BENDERUNIT{
  
  int x;
  int y;
  int nx;
  int ny;
  int tx[2];
  int ty[2];
  int beer_mode;
  int inverter;
  char direction;    
};

void initialize_bender(BB *bender, char **map, int R, int C){
    
    BB newunit;
    newunit = malloc(sizeof(newunit));
    newunit->beer_mode = -1;
    newunit->inverter = -1;
    newunit->direction = 'S';
    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){
            if(map[i][j] == '@'){
                newunit->x = i;
                newunit->y = j;
            }
        }
    }
    newunit->nx = newunit->x + 1;
    newunit->ny = newunit->y;
    bender = &newunit;
}

BB initialize_bender2(char **map, int R, int C){

    BB BENDER;
    int fit= 0;
    BENDER = malloc(sizeof(BB));
    if(BENDER != NULL){
        BENDER->beer_mode = -1;
        BENDER->direction = 'S';
        BENDER->inverter = -1;
        for(int i = 0; i < R; i++){
            for(int j = 0; j < C; j++){
                if(map[i][j] == '@'){
                    BENDER->x = i;
                    BENDER->y = j;
                }
                if(map[i][j] == 'T'){
                    BENDER->tx[fit] = i;
                    BENDER->ty[fit] = j;
                    fit++;
                }
            }
        }
    }
    BENDER->nx = BENDER->x;
    BENDER->ny = BENDER->y;
    return BENDER;
}


void updatebender(BB bender, char **map){
    
    bender->x = bender->nx;
    bender->y = bender->ny;
    switch(map[bender->nx][bender->ny]){
        case 'N':
            bender->direction = 'N';
            break;
        case 'E':
            bender->direction = 'E';
            break;
        case 'S':
            bender->direction = 'S';
            break;
        case 'W':
            bender->direction = 'W';
            break;
        case 'B':
            bender->beer_mode *= -1;
            break;
        case 'I':
            bender->inverter *= -1;
            break;
        case 'T':
            (bender->x == bender->tx[0]) ? (bender->x = bender->tx[1]) : (bender->x= bender->tx[0]);
            (bender->y == bender->ty[0]) ? (bender->y = bender->ty[1]) : (bender->y= bender->ty[0]);
            break;

    }

}

void findNextLoc(BB BENDER){
    BENDER->nx = BENDER->x;
    BENDER->ny = BENDER->y;
    
    if(BENDER->direction == 'S')
        BENDER->nx+=1;
    if(BENDER->direction == 'N')
        BENDER->nx--;
    if(BENDER->direction == 'E')
        BENDER->ny+=1;
    if(BENDER->direction == 'W')
        BENDER->ny--;
}
void changeDirection(BB bender, char **map){
    
    char dirs[4] = {'S', 'E', 'N', 'W'};
    if(bender->inverter == -1){
        for(int i = 0; i < 4; i++){
            bender->direction = dirs[i];
            findNextLoc(bender);
            if(canBenderpass(bender, map) == 1){
                break;
            }
        }
    }else{
        for(int i = 0; i < 4; i++){
            bender->direction = dirs[3-i];
            findNextLoc(bender);
            if(canBenderpass(bender, map) == 1){
                break;
            }
        }
    }
    
}

void store_string(BB bender, char **path, int number){
    //path[number] = malloc(5 * sizeof(char));

    switch(bender->direction){
        case 'S':
            path[number] = "SOUTH";
            break;
        case 'E':
            path[number] = "EAST";
            break;
        case 'W':
            path[number] = "WEST";
            break;
        case 'N':
            path[number] = "NORTH";
            break;
    }

}

int canBenderpass(BB bender, char **map){
    
    switch(map[bender->nx][bender->ny]){
        case '#':
            return -1;
            break;
        case 'X':
            if(bender->beer_mode == 1){
                map[bender->nx][bender->ny] = ' ';
                return 1;
            }else{
                return -1;
            }
            break;
        default :
            return 1;
    }
            
}



int main()
{
    int R;
    int C;
    scanf("%d%d", &R, &C); fgetc(stdin);
    // INITIALIZE THE TOWN MAP
    char** maze;
    maze = malloc(R * sizeof(char*));
    for (int i = 0; i < R; i++ ){
        maze[i] = malloc(C*sizeof(char));
    }
    for (int i = 0; i < R; i++) {
        fgets(maze[i], 102, stdin);
    }
    // INITIALIZE THE DIRECTIONS
    char *path2booth[MAXSTEPS];
    for(int pj = 0; pj < MAXSTEPS; pj++){
        path2booth[pj] = malloc(6 * sizeof(char));
    }
    // INITIALIZE BENDER
    BB rodriguez;
    rodriguez = initialize_bender2(maze, R, C);
    
    // INITIALIZE LOOP
    int iter =0;
    // print_map(maze, R);

    while(maze[rodriguez->x][rodriguez->y] != '$'){
        findNextLoc(rodriguez);
        if(canBenderpass(rodriguez, maze) == -1){
            changeDirection(rodriguez, maze);
        }
        store_string(rodriguez, path2booth, iter);
        updatebender(rodriguez, maze);
        // printf("direction: %c\n", rodriguez->direction);
        // printf("location: %d %d\n", rodriguez->x, rodriguez->y);
        // printf("standing on: %c\n", maze[rodriguez->x][rodriguez->y]);
        iter++;
        if(iter > MAXSTEPS){break;}
    }
    if(iter > MAXSTEPS){ printf("LOOP\n");}
    else{
        for(int i = 0; i < iter; i++){
            printf("%s\n", path2booth[i]);
        }
    }
    return 0;
}
	

