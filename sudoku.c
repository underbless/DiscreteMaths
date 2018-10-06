#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){
    FILE *in, *form, *middle, *out;
    char num[9][9];
    char result[9][9];
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            result[i][j]='?';
        }
    }
    
    in = fopen("input.txt", "r");
    form = fopen("formula.txt", "w");

    //formula.txt
    //declaring constants
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            fprintf(form, "(declare-const x%d%d Int)\n", i, j);
        }
    }fprintf(form, "\n");
    //setting boundaries for numbers
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            fprintf(form, "(assert(and (> x%d%d 0) (< x%d%d 10)))\n", i, j, i, j);
        }
    }fprintf(form, "\n");
    
    //asserting already assigned values
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            fscanf(in, "%c ", &num[i][j]);
            if(num[i][j]!='?'){
                fprintf(form, "(assert (= x%d%d %c))\n", i, j, num[i][j]);
            }
        }
    }fprintf(form, "\n");

    //applying distinct for rows
    for(int i=0; i<9; i++){
        fprintf(form, "(assert (distinct ");
        for(int j=0; j<9; j++){
            fprintf(form, "x%d%d ", i, j);
        }
        fprintf(form, "))\n");
    }fprintf(form, "\n");
    //applying distinct for columns
    for(int i=0; i<9; i++){
        fprintf(form, "(assert (distinct ");
        for(int j=0; j<9; j++){
            fprintf(form, "x%d%d ", j, i);
        }
        fprintf(form, "))\n");
    }fprintf(form, "\n");
    //applying distinct for boxes

    for(int k=0; k<9; k+=3){
        fprintf(form, "(assert (distinct ");
        for(int i=k; i<k+3; i++)
            for(int j=0; j<3; j++)
                fprintf(form, "x%d%d ", i, j);
        fprintf(form, "))\n");
        fprintf(form, "(assert (distinct ");
        for(int i=k; i<k+3; i++)
            for(int j=3; j<6; j++)
                fprintf(form, "x%d%d ", i, j);
        fprintf(form, "))\n");
        fprintf(form, "(assert (distinct ");
        for(int i=k; i<k+3; i++)
            for(int j=6; j<9; j++)
                fprintf(form, "x%d%d ", i, j);
        fprintf(form, "))\n");
    }

    
    
    
    
    
    fprintf(form, "(check-sat)\n");
    fprintf(form, "(get-model)\n");
    
    //out = fopen("output.txt", "w");
    fclose(in); fclose(form);
    system("z3 formula.txt > middle.txt");
    
    middle = fopen("middle.txt", "r");
    out = fopen("output.txt", "w");

    //result parsing 

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
        }else if(strncmp(str, "    ", 4)==0){
            result[x][y]=str[4];
            //printf("result[%d][%d] - %c\n", x, y, result[x][y]);
        }
    }

    //printing result to output.txt
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            fprintf(out, "%c ", result[i][j]);
        }
        fprintf(out, "\n");
    }
    
    fclose(middle); fclose(out);
    return 0;
}