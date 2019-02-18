#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define USER_NUM 5128

int *id_set ;

int *follower ;

int *count;

int magic_jump(){
    int i = rand() / USER_NUM;
    return i ;
}

int id2idx(int id) {
    for (int i=0 ; i<USER_NUM ; i++) {
        if (id_set[i] == id)
            return i ;
    }
    return -1 ;
}

int idx2id(int idx) {
    return id_set[idx] ;
}

int main() {
    FILE *fp_id = fopen("id_array.txt", "r") ;

    int i = 0 ;
    id_set = (int *)malloc(sizeof(int) * USER_NUM) ;

    int temp = 0 ;
    for (int i=0 ; i<USER_NUM ; i++) {
        fscanf(fp_id, "%d", &temp) ;
        id_set[i] = temp ;
    }
    fclose(fp_id) ;

    int **follow_list = (int **)malloc(sizeof(int*) * USER_NUM) ;

    for (int i=0 ; i<USER_NUM ; i++) {
        follow_list[i] = (int *)malloc(sizeof(int) * USER_NUM) ;
    }
    //make an ID list.

    FILE *fp_data = fopen("twitter_sampled.txt", "r") ;
    
    int x, y ;

    for (int i = 0 ; i < 21270 ; i++) {
        fscanf(fp_data, "%d %d", &x, &y) ;
        x = id2idx(x) ;
        y = id2idx(y) ;

        follow_list[x][y] = 1 ;
    }
    fclose(fp_data);

    follower = (int *)malloc(sizeof(int) * USER_NUM) ;
    
    srand(time(NULL));

    int position = 0;
    count = (int *)malloc(sizeof(int) * USER_NUM) ;
    int ten_per = 0;
    int find = 0;
    int move_pos = 0;

    int try = 0;

    while(try < 50000){
        ten_per = rand() / 10;
        if(ten_per == 0){       //10%
            position = magic_jump();
            count[position] += 1;
        }
        else{       //90%
            int r = 0;
            for(int j = 0; j < USER_NUM; j++) { //compare number and save to 2d matrix
                if(follow_list[position][j]==1){
                    follower[r] = j;
                    r++;
                }
            }
            if(r == 0){     //if user follow nobody.
                position = magic_jump();
                count[position] += 1;
            }
            else{       //if user follow someone.
                move_pos = rand() / r;
                position = idxtoid(follower[move_pos]);
                count[position] += 1;
            }
        }
        try++;
    }

    int id_change, val_change;

    for(int j = 0; j < 5128; j++){
        for(int i = 0; i < 5127; i++) { 
            if(count[i]<count[i+1]) {
                val_change=count[i+1];
                count[i+1]=count[i];
                count[i]=val_change;
                id_change=id_set[i+1];
                id_set[i+1]=id_set[i];
                id_set[i]=id_change;
            }
        }
    }

    int cnt = 0;

    for(i=0;i<20;i++) {
        printf("Random surfer has visited user_%d(id) %d times.\n",id_set[i],count[i]);  
        cnt++;
    }
    printf("%d\n",cnt);

    for (i=0 ; i<USER_NUM ; i++) {
        free(follow_list[i]) ;
    }
    free (count);
    free (*follow_list);
    free (follower);
    free (id_set);
}
