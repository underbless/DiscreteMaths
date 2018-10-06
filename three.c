#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE *in, *form, *out, *middle;
    char num[8][8];
    char result[8][8];

    in = fopen("input.txt", "r");
    form = fopen("formula.txt", "w");
     
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            fprintf(form, "(declare-const x%d%d Int)\n", i, j);
        }
    }

    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            fprintf(form, "(assert(or (= x%d%d 0) (= x%d%d 1)))\n", i, j, i, j);
        }
    }

    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            fscanf(in, "%c ", &num[i][j]);
            if(num[i][j] == 'O'){
                fprintf(form, "(assert (= x%d%d %d))\n", i, j, 1);
            }
            if(num[i][j] == 'X'){
                fprintf(form, "(assert (= x%d%d %d))\n", i, j, 0);
            }
        }
    }

    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if(i + 1 < 8 && i - 1 >= 0)
                fprintf(form, "(assert (not (and (= x%d%d x%d%d) (= x%d%d x%d%d))))\n", i + 1, j, i,j, i - 1, j, i,j);
            if(j + 1 < 8 && j - 1 >= 0)
                fprintf(form, "(assert (not (and (= x%d%d x%d%d) (= x%d%d x%d%d))))\n", i, j + 1, i,j, i, j - 1, i,j);
        }
    }

     for(int i=0; i<8; i++){
         fprintf(form, "(assert (= (+ ");
         for(int j=0; j<8; j++){
            fprintf(form, "x%d%d ", i, j);
         }
         fprintf(form, ") 4 ))\n");
     }

     for(int j=0; j<8; j++){
         fprintf(form, "(assert (= (+ ");
         for(int i=0; i<8; i++){
            fprintf(form, "x%d%d ", i, j);
         }
         fprintf(form, ") 4 ))\n");
     }

    fprintf(form, "(check-sat)\n");
    fprintf(form, "(get-model)\n");
    
    fclose(in); fclose(form);
    
    system("z3 formula.txt > middle.txt");
    
    middle = fopen("middle.txt", "r");
    out = fopen("output.txt", "w");

    char sat[5];
    fscanf(middle, "%s\n", sat);

    if(strcmp(sat, "unsat")==0){
        printf("Impossible\n");
        exit(0);
    }

    int x, y;
    char str[100];
    while(!feof(middle)){
        fgets(str, 100, middle);
        if(strncmp(str, "  (de", 5)==0){
            x=str[15] - '0'; y=str[16] - '0';
        }
        else if(strncmp(str, "    ", 4)==0){
            if(str[4] == '1')
                result[x][y]='O';
            else
                result[x][y]='X';
        }
    }

    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            fprintf(out, "%c ", result[i][j]);
        }
        fprintf(out, "\n");
    }
    
    fclose(middle); fclose(out);
    return 0;
}