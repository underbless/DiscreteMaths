#include <stdio.h>
#include <stdlib.h>
#define USER_NUM 5128

typedef struct node_ {
    int val ;
    struct node_* next ;
} node ;

typedef struct queue_ {
    node *front; 
    node *rear; 
    int count; 
} queue ;

typedef struct mutual_ {
    int user1 ;
    int user2 ;
    int check ;
} mutual ;
 
int *id_set ;
mutual set[4000] ;

void initQueue(queue *q) ;
int isEmpty(queue *q) ;  
void insert(queue *q, int data) ;  
int delete(queue *q) ; 
int length(queue *q) ;


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

int isNoMutual(int id) { 
    for (int i=0 ; i<3873 ; i++) {
        if (set[i].user1 == id || set[i].user2 == id) {
            return 0 ;
        }
    }
    return 1 ;
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

    int **relationArray = (int **)malloc(sizeof(int*) * USER_NUM) ;

    for (int i=0 ; i<USER_NUM ; i++) {
        relationArray[i] = (int *)malloc(sizeof(int) * USER_NUM) ;
    }

    FILE *fp_data = fopen("twitter_sampled.txt", "r") ;
    int x, y ;

    for (int i=0 ; i<21270 ; i++) {
        fscanf(fp_data, "%d %d", &x, &y) ;
        x = id2idx(x) ;
        y = id2idx(y) ;

        relationArray[x][y] = 1 ;
    }
    fclose(fp_data) ;
    
    printf("read data\n") ;

    int markingArray[USER_NUM] = {0, } ;
    int markSign = 1;
    int newID = 0 ;

    queue qq ;
    initQueue(&qq) ;

    for(int i=0 ; i<USER_NUM ; i++) {
        if(markingArray[i] == 0) {
            newID = i ;
            while(1) {
                //printf("current i : %d\n", newID) ;
                //if (markingArray[newID] != 0)
                //    continue ;

                markingArray[newID] = markSign ;

                for (int j=0 ; j<USER_NUM ; j++) {
                    if (relationArray[newID][j] == 1) {
                        if (markingArray[j] != 0)
                            continue ;
                        insert(&qq, idx2id(j)) ;
                    }
                }

                for (int j=0 ; j<USER_NUM ; j++) {
                    if (relationArray[j][newID] == 1) {
                        if (markingArray[j] != 0)
                            continue ;
                        insert(&qq, idx2id(j)) ;
                    }
                }
                printf("length : %d and markSign : %d\n", length(&qq), markSign) ;

                if (isEmpty(&qq)) {
                    markSign += 1 ;
                    break ;
                } else {
                    newID = delete(&qq) ;
                    newID = id2idx(newID) ;
                }
            }
        }
    }

    FILE *fp_result = fopen("marking_3.txt", "w") ;
    for(int i=0 ; i<USER_NUM ; i++) {
        fprintf(fp_result, "%d,%d\n", idx2id(i), markingArray[i]) ;
    }
    fclose(fp_result) ;
    for (int i=0 ; i<USER_NUM ; i++) {
        free(relationArray[i]) ;
    }
    free(relationArray) ;
    free(id_set) ;
}

void initQueue(queue *q) {
    q->front = NULL ;
    q->rear = NULL ;
    q->count = 0 ;
}


int isEmpty(queue *q) {
    if (q->count == 0)
        return 1 ;
    else 
        return 0 ;
}


void insert(queue *q, int data) {
    node *new = (node *)malloc(sizeof(node)) ;
    new->val = data;
    new->next = NULL;
 
    if (isEmpty(q)) {
        q->front = new ;
    } else {
        for (node *curr = q->front ; curr != NULL ; curr = curr->next) {
            if (data == curr->val) { // remove duplicated user
                free(new) ;
                return ;
            }  
        }
        q->rear->next = new;
    }
    
    q->rear = new ; 
    q->count += 1 ;
    return ;
}


int delete(queue *q) { // return -1 when queue is empty
    node *temp = NULL;

    if (isEmpty(q)) {
        return -1 ;
    }

    temp = q->front ; 
    int value = temp->val ; 

    q->front = temp->next ; 
    free(temp);
    q->count -= 1 ;

    return value;
}

int length(queue *q) {
    return q->count ;
}