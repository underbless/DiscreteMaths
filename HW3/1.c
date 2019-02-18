#include <stdio.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAX_SIZE 50000

void find_set();
void how_many_other_users_the_user_follows();
void how_many_followers_the_user_has();
int set[MAX_SIZE];  // unique set element(user)를 담을 int array(계속 써먹기 위해서 여기에 선언) 

void find_set() {
int a[MAX_SIZE];//sample file의 ordered pair을 담을 int array( element 한개당 array 한칸씩) 
    int i,j,x,y;
    FILE *f;
   f = fopen("twitter_sampled.txt", "r");
    i=0;
   
   while(!feof(f)) // 모든 relation의 element를 a array에 저 장 (반복된거 제거했음) 
   {fscanf(f, "%d ", &a[i]);
    j=i-2;
      if(i%2==1)
      { while(j>=0)
          { if(a[i]==a[j] && a[i-1]==a[j-1])// 짝수칸은 짝수칸끼리 홀수칸은 홀수 칸 끼리 비교 
            {i-=2;        //즉 동일 relation element가 존재 할 경우 다음 읽을 element로 바꿈(덮어씀) 
              break; 
          }
         j-=2;   
         }   
        }
    i++;   
   } 
     
     
     i=0;
    while(i<31189) //반복된 element 제거한 relation set을 저장한 a array의  모든 칸 print 해보기 (삭제해도 무방 ) 
    { 
    printf("%d\n", a[i]);
    i++;
    }
    printf("the number of pair의 모든 element수:%d\n",i);
  
   
   int iden1,iden2,number=0;
      // sample파일 relation에서 반복된게 사라졌는지 확인 (삭제해도 무방) 
    printf("relation 1 pair element 1 확인:");
    scanf("\n%d",&iden1);
     printf("relation 1 pair element 2 확인:");
    scanf("\n%d",&iden2);
     for (i = 0;i < 31189 ;i+=2){ 
      if (a[i]==iden1 && a[i+1]==iden2)
      number++; 
    }
     printf("반복횟수 :%d\n",number);
   
     
     
   // sample text에서 모든 중복되는 element를 걸려내고 unique set(user 5128개) array에 저장하기 (set 만들기)    
   int k; 
   k=-1;   
   // 1.앞for 구문을 통해 첫번째 index 부터 대상을 잡는다 .
   for ( x = 0; x < 42540; x++) {
      if(a[x]!=0) // 5. 뒤 for구문에 의해 0으로 바뀐 array는 카운트 하지 않는다 
     k++;
     for ( y = 1+x; y < 42540; y++) {      //2. 뒤 for구문을 통해 앞 for구문 대상과 비교되는 대상을 차례대로 array 끝까지  비교해준다. 
              if(a[x]!=0)               //3. 중복되는부분은 (뒤쪽 비교대상 array index를) 0으로 저장하고  0인부분은 set에 포함안함
           {   if(a[x]==a[y])
                  a[y]=0;           
                 else
                 {set[k]=a[x];}          //4. 중복안되면 set에 저장하 기
           }
    }
    } 

    fclose(f);
   }

void how_many_other_users_the_user_follows(){
   int a[MAX_SIZE];//sample file의 ordered pair을 담을 int array( element 한개당 array 한칸씩) 
   int i,j;
    FILE *f;
   f = fopen("twitter_sampled.txt", "r");
     i=0;
    while(!feof(f)) // 모든 relation의 element를 a array에 저 장 (반복된거 제거했음) 
   {fscanf(f, "%d ", &a[i]);
    j=i-2;
      if(i%2==1)
      { while(j>=0)
          { if(a[i]==a[j] && a[i-1]==a[j-1])// 짝수칸은 짝수칸끼리 홀수칸은 홀수 칸 끼리 비교 
            {i-=2;        //즉 동일 relation element가 존재 할 경우 다음 읽을 element로 바꿈(덮어씀) 
              break; 
          }
         j-=2;   
         }   
        }
    i++;   
   } 

    
    
      int iden,number=0;
      //알고 싶은 user 입력 & set array에서 몇번째 칸에 저장된는지 찾기
    printf("1.how many other users a user follows?\ninput user ID you want to know :");
    scanf("\n%d",&iden);
     for (i = 0;i < 5128 ;i++){
      if (set[i]==iden)
      break; 
    }
   
   // 0,2,4,6......칸에 x가 저장되있기 때문에 짝수칸만 비교 (x follow y) 
   for (j = 0;j < 42540 ;j+=2) {
        if(set[i]==a[j] ) 
        number++; 
      }
        printf("how many other users the user follows?: %d\n", number);
       
      fclose(f);
      
      }
    
  void how_many_followers_the_user_has(){
      int a[MAX_SIZE];//sample file의 ordered pair을 담을 int array( element 한개당 array 한칸씩)

      int i,j;
  
      FILE *f;
        f = fopen("twitter_sampled.txt", "r");
       i=0;
    while(!feof(f)) // 모든 relation의 element를 a array에 저 장 (반복된거 제거했음) 
   {fscanf(f, "%d ", &a[i]);
    j=i-2;
      if(i%2==1)
      { while(j>=0)
          { if(a[i]==a[j] && a[i-1]==a[j-1])// 짝수칸은 짝수칸끼리 홀수칸은 홀수 칸 끼리 비교 
            {i-=2;        //즉 동일 relation element가 존재 할 경우 다음 읽을 element로 바꿈(덮어씀) 
              break; 
          }
         j-=2;   
         }   
        }
    i++;   
   } 
   
   
   
    int iden,number=0;
    //알고 싶은 user 입력 & set array에서 몇번째 칸에 저장된는지 찾기
    printf("2.how many followers a user has?\ninput user ID you want to know :");
    scanf("\n%d",&iden);
    
    for (i = 0;i < 5128 ;i++){
           if (set[i]==iden)
           break; 
    }
    // 1,3,5,7......칸에 y가 저장되있기 때문에 홀수칸만 비교 (x follow y) 
   for (j = 1;j < 42540 ;j+=2) {
        if(set[i]==a[j] ) 
        number++; 
    }
    printf("how many followers the user has?: %d", number);

    fclose(f);
   }
    
    
    


int main()
{
   

 find_set();
 how_many_other_users_the_user_follows();
 how_many_followers_the_user_has();
}