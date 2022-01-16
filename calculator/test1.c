#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strlen

#define MAX_SIZE 100

typedef struct _StackType
{
    int arr[MAX_SIZE];
    int top;
} StackType;

// 초기화함수
int init(StackType *s)
{
    // 화살표 연산자로 구조체 멤버에 접근하여 값 할당
    s->top = -1;
}

// 스택
int isFull(StackType *s)
{
    return (s->top == (MAX_SIZE - 1));
}

int isEmpty(StackType *s)
{
    return (s->top == -1);
}

void push(StackType *s, int data)
{
    if (isFull(s))
    {
        fprintf(stderr, "stack is Full\n");
        return;
    }
    else
        s->arr[++(s->top)] = data;
}

int pop(StackType *s)
{
    if (isEmpty(s))
    {
        fprintf(stderr, "stack is Empty\n");
        exit(1);
    }
    else
        return s->arr[(s->top)--];
}

int peek(StackType *s)
{
    if (isEmpty(s))
    {
        fprintf(stderr, "stack is Empty\n");
        exit(1);
    }
    else
        return s->arr[s->top];
}

int pri(char op)
{
    switch (op)
    {
    case '(':
    case ')':
        return 0;
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    }
    // 숫자
    return -1;
}

void infix_to_postfix(char *infix, char *postfix)
{
    StackType op;
    init(&op);
    while (*infix != '\0')
    { // 수식이 끝날 때까지 반복
        if (*infix == '(')
        {
            push(&op, *infix);
            infix++;
        }
        else if (*infix == ')')
        {
            while (peek(&op) != '(')
            {
                *postfix++ = pop(&op);
                *postfix++ = ' ';
            }
            pop(&op);    // '(' 꺼냄
            infix++;
        }
        else if (*infix == '+' || *infix == '-' || *infix == '*' || *infix == '/')
        {
            while (!isEmpty(&op) && (pri(*infix) <= pri(peek(&op)))) // 현재 연산자 <= top 값
            {
                *postfix++ = pop(&op);
                *postfix++ = ' ';
            }
            push(&op, *infix);
            infix++;
        }
        else if (*infix >= '0' && *infix <= '9')
        {
            while ((*infix >= '0' && *infix <= '9'))
            {
                *postfix++ = *infix++;
            }
            *postfix++ = ' ';
        }
        else
            infix++;
    }
    while (!isEmpty(&op))
    {
        *postfix++ = pop(&op); // 남은거,,
        *postfix++ = ' ';
    }
    postfix--;
    *postfix = '\0';
}

int eval2(char *postfix){
    int value = 0, op1, op2, i;
    StackType num;
    init(&num);
    int cnt =0, j;
    
    while (*postfix != '\0'){
        if (*postfix == ' ')
        {
            *postfix++;
            cnt = 0;
        }

        if (*postfix == '+' || *postfix == '-' || *postfix == '*' || *postfix == '/'){
            // 연산자이면
            op2 = pop(&num);
            op1 = pop(&num);
            switch (*postfix)
            {
            case '+':
                push(&num, op1 + op2);
                break;
            case '-':
                push(&num, op1 - op2);
                break;
            case '*':
                push(&num, op1 * op2);
                break;
            case '/':
                push(&num, op1 / op2);
                break;
            }
            postfix++;
        }
        else {
            // 숫자이면
            // while ((*postfix >= '0' && *postfix <= '9'))
            // {
            //     // *postfix++ = *infix++;
            //     value = *postfix++ - '0'; // ch --> int
            //     value += 
            //     printf("while value : %d\n", value);
            //     // push(&num, value);
            //     cnt ++;
            // }
            if(cnt > 0 ){
                printf("cnt : %d\n", cnt);
            }
            value = *postfix - '0'; // ch --> int
            printf("value : %d\n", value);
            push(&num, value);
            cnt ++;
            postfix++;
        }
        // postfix++;
    }
    return pop(&num);
}

int eval(char *postfix)
{
    int value=0, op1, op2, i;
    StackType s;
    init(&s);
    char ch;
    // int len = strlen(postfix);
    // printf("len : %d\n", len);

    for (i = 0; i < postfix[i] != '\0'; i++)
    {
        // cnt =0;
        if (postfix[i] == ' ')
        {
            i++;
        }
        ch = postfix[i];

        // if (ch != '+' && ch != '-' && ch != '*' && ch != '/')
        if (ch >= '0' && ch <= '9')
        {
            // 숫자이면
            
            value = ch - '0'; // ch --> int
            printf("value : %d\n", value);
            push(&s, value);
        }
        else
        {
            // 연산자이면
            op2 = pop(&s);
            op1 = pop(&s);
            switch (ch)
            {
            case '+':
                push(&s, op1 + op2);
                break;
            case '-':
                push(&s, op1 - op2);
                break;
            case '*':
                push(&s, op1 * op2);
                break;
            case '/':
                push(&s, op1 / op2);
                break;
            }
        }
    }
    return pop(&s);
}

int main(void)
{
    char input[MAX_SIZE], output[MAX_SIZE];

    while (1)
    {
        printf("식을 입력하세요 : ");
        scanf("%s", &input);

        infix_to_postfix(input, output);
        printf("infix : %s\n", input);
        printf("postfix : %s\n", output);

        int i;
        for (i = 0; i < strlen(output); i++)
        {
            printf("output[%d] : %c\t", i, *(output + i));
        }printf("\n");

        int res = eval2(output);
        printf("res : %d\n\n", res);
    }
}
