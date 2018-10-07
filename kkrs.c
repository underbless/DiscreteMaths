#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){
    FILE *in, *form, *middle, *out;
    int num[2][8];
    char result[8][8];
    
    in = fopen("input.txt", "r");
    form = fopen("formula.txt", "w");
    
    //reading sums of rows and columns from input.txt
    for(int i=0; i<2; i++){
        for(int j=0; j<8; j++){
            fscanf(in, "%d ", &num[i][j]);
        }
    }

    //formula.txt
    //declared x11-x88 and y11-y88, because the values are different depending on whether it's row or column
    for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            fprintf(form, "(declare-const x%d%d Int)\n", i, j);
        }
    }fprintf(form, "\n");
    for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            fprintf(form, "(declare-const y%d%d Int)\n", i, j);
        }
    }fprintf(form, "\n");

    //each values can either be (0) or (values as row or column)
    for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            fprintf(form, "(assert (or (= x%d%d 0) (= x%d%d %d)))\n", i, j, i, j, j);
        }
    }fprintf(form, "\n");
    for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            fprintf(form, "(assert (or (= y%d%d 0) (= y%d%d %d)))\n", i, j, i, j, i);
        }
    }fprintf(form, "\n");

    //the sum of each rows and column are given, so the sum of values should match that number
    for(int i=1; i<9; i++){
        fprintf(form, "(assert (= %d (+ ", num[0][i-1]);
        for(int j=1; j<9; j++){
            fprintf(form, "x%d%d ", i, j);
        }
        fprintf(form, ")))\n");
    }fprintf(form, "\n");

    for(int i=1; i<9; i++){
        fprintf(form, "(assert (= %d (+ ", num[1][i-1]);
        for(int j=1; j<9; j++){
            fprintf(form, "y%d%d ", j, i);
        }
        fprintf(form, ")))\n");
    }fprintf(form, "\n");

    //when x is deactivated y must be deactivated too 
    for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            fprintf(form, "(assert (=> (= x%d%d 0) (= y%d%d 0)))\n", i, j, i, j);
        }
    }fprintf(form, "\n");

    fprintf(form, "(check-sat)\n");
    fprintf(form, "(get-model)\n");
    
    fclose(in); fclose(form);
    
    //using z3 and receiving result in middle.txt
    system("z3 formula.txt > middle.txt");
    
    middle = fopen("middle.txt", "r");
    out = fopen("output.txt", "w");

    char sat[5];
    fscanf(middle, "%s\n", sat);

    //if the puzzle is unsolvable, program prints 'Impossible'
    if(strcmp(sat, "unsat")==0){
        printf("Impossible\n");
        exit(0);
    }
    
    //parsing results. When 0 is given, it means the value is not activated --> O
    //when the value is a number(activated) --> X
    int x, y;
    char str[100];
    while(!feof(middle)){
        fgets(str, 100, middle);
        if(strncmp(str, "  (de", 5)==0){
            x=str[15] - '0'; y=str[16] - '0';
        }
        else if(strncmp(str, "    ", 4)==0){
            if(str[4] == '0')
                result[x-1][y-1]='O';
            else
                result[x-1][y-1]='X';
        }
    }
    
    //printing out result in output.txt
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            fprintf(out, "%c ", result[i][j]);
        }
        fprintf(out, "\n");
    }
    
    fclose(middle); fclose(out);

    return 0;
}