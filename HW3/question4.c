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

    int count = 0 ;

    for (int i=0 ; i<USER_NUM ; i++) {
        for (int j=i ; j < USER_NUM ; j++) {
            if ((relationArray[i][j] == relationArray[j][i]) && (relationArray[i][j] == 1)) {
                set[count].user1 = idx2id(i) ;
                set[count].user2 = idx2id(j) ;
                set[count].check = 0 ; // init 
                //printf("%d %d %d\n", count, set[count].user1, set[count].user2) ;
                count += 1;
            }
        }
    }
    
    printf("%d\n", count) ; // 3873
    //printf("found set\n") ;

    int markingArray[USER_NUM] = {0, } ;
    int markSign = 1;
    int newID = 0 ;

    queue qq ;
    initQueue(&qq) ;

    for(int i=0 ; i<USER_NUM ; i++) {
        if(isNoMutual(idx2id(i))) {
            markingArray[i] = -1 ;
            printf("%d has no mutual\n", idx2id(i)) ;
        }
    }

    for(int i=0 ; i<USER_NUM ; i++) {
        if(markingArray[i] == 0) {
            newID = i ;
            while(1) {
                markingArray[newID] = markSign ;
                for (int j=0 ; j<count ; j++) {
                    if(set[j].user1 == idx2id(newID)) {
                        insert(&qq, set[j].user2) ;
                    }
                }
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

    FILE *fp_result = fopen("marking", "w") ;
    for(int i=0 ; i<USER_NUM ; i++) {
        fprintf(fp_result, "%d\n", markingArray[i]) ;
    }

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
            if (data == curr->val) // remove duplicated user
                return ;
        }
        q->rear->next = new;
    }
    
    q->rear = new ; 
    q->count += 1 ;
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
}#include <stdio.h>
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

    int count = 0 ;

    for (int i=0 ; i<USER_NUM ; i++) {
        for (int j=i ; j < USER_NUM ; j++) {
            if ((relationArray[i][j] == relationArray[j][i]) && (relationArray[i][j] == 1)) {
                set[count].user1 = idx2id(i) ;
                set[count].user2 = idx2id(j) ;
                set[count].check = 0 ; // init 
                //printf("%d %d %d\n", count, set[count].user1, set[count].user2) ;
                count += 1;
            }
        }
    }
    
    printf("%d\n", count) ; // 3873
    //printf("found set\n") ;

    int markingArray[USER_NUM] = {0, } ;
    int markSign = 1;
    int newID = 0 ;

    queue qq ;
    initQueue(&qq) ;

    for(int i=0 ; i<USER_NUM ; i++) {
        if(isNoMutual(idx2id(i))) {
            markingArray[i] = -1 ;
            printf("%d has no mutual\n", idx2id(i)) ;
        }
    }

    for(int i=0 ; i<USER_NUM ; i++) {
        if(markingArray[i] == 0) {
            newID = i ;
            while(1) {
                markingArray[newID] = markSign ;
                for (int j=0 ; j<count ; j++) {
                    if(set[j].user1 == idx2id(newID)) {
                        if (markingArray[set[j].user2] != 0)
                            continue ;
                        insert(&qq, set[j].user2) ;
                    }
                    if(set[j].user2 == idx2id(newID)) {
                        if (markingArray[set[j].user1] != 0)
                            continue ;
                        insert(&qq, set[j].user1) ;
                    }
                }
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

    FILE *fp_result = fopen("temp.txt", "w") ;
    for(int i=0 ; i<USER_NUM ; i++) {
        fprintf(fp_result, "%d\n", markingArray[i]) ;
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
            if (data == curr->val) // remove duplicated user
                return ;
        }
        q->rear->next = new;
    }
    
    q->rear = new ; 
    q->count += 1 ;
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