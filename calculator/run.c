# include <stdio.h>
// # include <stdlib.h>
# define MAX_SIZE 100

char input[MAX_SIZE];
char output[MAX_SIZE];
int top = -1;

typedef struct {
    int stack[MAX_SIZE];
    int top;
}StackType;



// 스택 상태
int isFull(){
    if (top >= MAX_SIZE -1){
        printf("stack is FULL\n");
        return 1;
    }
    return 0;
}

int isEmpty(){
    if (top == -1){
        printf("stack if EMPTY\n");
        return 1;
    }
    return 0;
}

int push(data){
    if (!isFull()){
        top ++;
        output[top] = data;
    }
}

int pop(){
    if (!isEmpty()){
        char temp = output[top];
        top --;
        return temp;
    }
}



int main (){
    
    char *op;
    char *str;
    int res;

    printf("식을 입력하세요 : ");
    scanf("%s", &str);

    printf("입력받은 문자열은 %s 입니다.\n", &str);

    

    return 0;
}

