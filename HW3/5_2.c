#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define USER_NUM 5128
#define max_ele 42540

int *id_set ;  //global 선언 
int *id_marking;
int *a_storing1;
int ** relationArray;

int id2idx(int id) {
   int i;
    for ( i=0 ; i<USER_NUM ; i++) {
        if (id_set[i] == id)
            return i ;
    }
    return -1 ;
}

int idx2id(int idx) {
    return id_set[idx] ;
}

int bymagic() {
    int i;
    i=rand()%USER_NUM;  
    id_marking[i]+=1;
    return i;
}

void random_move(int *id_set, int *id_marking , int *a_storing1, int **relationArray) {
//random move
    int i,p,g;
   
    for ( i=0 ; i<USER_NUM ; i++) {
        a_storing1[i]=0;
        id_marking[i]=0;
    }
    
    int id_index,k,j;// id_index는 random surfer가 이동하는 node라고 생각하면됨(surfer의 발자취)!  
    
    srand(time(NULL));
    int number=0;
   
    while(number<50){
        int ar[10] = { 1,2, 2, 2, 2, 2, 2, 2, 2, 2 };
        p = ar[rand()%10];
        if(p==2) // 90% 확률 
        {
            if(number==0)
                id_index=rand()%USER_NUM;
            for ( i=0 ; i<USER_NUM ; i++) {
                a_storing1[i]=0 ;
            }
            k=0; // relationarray의 id_dex번째 row에서 '1'의 개수를 k로 카운팅 할 예정 
            
            for(j=0; j<USER_NUM ;j++) {
                if( relationArray[id_index][j] == 1) {
                    a_storing1[k]=j; //relationarray의 1인 지점 j 열의 index값을 저장 
                    k++;
                }    
            }
            if(k==0) {
                id_index=bymagic();
            }
            else {
                g=rand()%k;
                j=a_storing1[g];
                id_marking[j]+=1;
                id_index=j;         
            } 
        }
        else if(p==1)//10%확 률 
        {   
            id_index=bymagic();   
        }
        number++;
    }
}

void find_influential_20_users(int *id_marking , int *id_set) {
   //find influential users(내림차순 정렬) 
    int g,i,j,count,gg;
    count=0;
    for(j=0;j<5128;j++){
        for(i=0;i<5127;i++ ) {
            if(id_marking[i]<id_marking[i+1]) {
                g=id_marking[i+1];
                id_marking[i+1]=id_marking[i]; 
                id_marking[i]=g;
                gg=id_set[i+1];
                id_set[i+1]=id_set[i]; 
                id_set[i]=gg;
            }
        }
    }
}



int main() {

    int *a1 = (int *)malloc(sizeof(int) * max_ele) ;
    a_storing1 = (int *)malloc(sizeof(int) * USER_NUM) ;
    id_marking = (int *)malloc(sizeof(int) * USER_NUM) ;
    id_set = (int *)malloc(sizeof(int) * USER_NUM) ;
   
   
    FILE *fp_id = fopen("twitter_sampled.txt", "r") ;
     
    int i,x,y ;
    int temp = 0 ;

    for ( i=0 ; !feof(fp_id) ; i++) {
        fscanf(fp_id, "%d", &temp) ;
        a1[i] = temp ;
    }
    
    int k; 
    k=-1;   
    
    for ( x = 0; x < max_ele; x++) {
        if(a1[x]!=0) 
        k++;
        for ( y = 1+x; y < max_ele; y++) {      
            if(a1[x]!=0) {
                if(a1[x]==a1[y])
                    a1[y]=0;           
                else {
                    id_set[k]=a1[x];
                }
            }
        }
    } 
    fclose(fp_id) ;
   
    
    relationArray = (int **)malloc(sizeof(int*) * USER_NUM) ;  //2D relation Array  
    for (i=0 ; i<USER_NUM ; i++) {
        relationArray[i] = (int *)malloc(sizeof(int) * USER_NUM) ;
    }
    int j;
    for ( i=0 ; i<USER_NUM ; i++) {
        for ( j=0 ; j<USER_NUM ; j++) {
            relationArray[i][j]=0 ;
        }
    } 
    
    FILE *fp_data = fopen("twitter_sampled.txt", "r") ;
    
    for ( i=0 ; i<21270 ; i++) {
        fscanf(fp_data, "%d %d", &x, &y) ;
        x = id2idx(x) ;
        y = id2idx(y) ;
        relationArray[x][y] = 1;
    }

    fclose(fp_data) ;
    
    int count=0;
    for ( i=0 ; i<USER_NUM ; i++) {
        for ( j=0 ; j<USER_NUM ; j++) {
            if(relationArray[i][j] == 1 ) {
                count++;
            }
        }
    }
    
    int t3;
    clock_t t1,t2;   
    
    t1=clock();
    
    random_move(id_set,id_marking , a_storing1,relationArray);
    
    t2=clock();
    
    find_influential_20_users( id_marking , id_set);
    
    t3=(t1-t2)/(1000*60);
    printf("take a %d minute \n",t3);  


    count=0;
    
    for(i=0;i<20;i++ ) {
        printf("Random surfer has visited user_%d(id) %d times.\n",id_set[i],id_marking[i]);  
        count++;
    }

    printf("%d\n",count);
    
    for (i=0 ; i<USER_NUM ; i++) {
        free(relationArray[i]) ;
    }

    free(relationArray) ;
    free(id_marking) ;
    free(id_set) ;
    free(a_storing1) ;
    free(a1) ;
}