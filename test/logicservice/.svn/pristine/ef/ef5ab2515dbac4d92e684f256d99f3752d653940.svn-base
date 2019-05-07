#ifndef LOGICDEF_H
#define LOGICDEF_H






#define STACK_INCREASE_LEN 10
#define N 10

#define T_STACK char

typedef struct tagStack
{
    T_STACK * base;
    T_STACK * top;
    int stacksize;
} Stack;

void InitStack(Stack * s)
{//构造一个栈
    s->base =(T_STACK *)malloc(STACK_INCREASE_LEN*sizeof(Stack));
    if(!s->base) {puts("Create Stack Failse");return;}
    s->top = s->base;
    s->stacksize = STACK_INCREASE_LEN;
    puts("Create Stack Success");
}

void DestroyStack(Stack * s)
{//销毁栈
    if(!s->base)
    {
        puts("Stack is NULL");
        return;
    }
    free(s->base);
    s->base = NULL;
    puts("Stack Had Destroy");
}

int StackEmpty(Stack * s)
{//判断栈是否为空
    /* 以栈存在为前提 */
    /* 为空返回“true” 否则返回“false”*/
    if(s->base == s->top)
    return 1;
    return 0;
}

int StackLength(Stack * s)
{//获取栈的长度
    /* 以栈存在为前提 */
    return s->top - s->base;
}

T_STACK Top(Stack * s)
{//获取栈顶元素
    if(StackEmpty(s))
    {
        puts("stack empty");
        return 0;
    }
    return *(s->top-1);
}

void Push(Stack * s , T_STACK e)
{//入栈操作
    if(s->top - s->base > s->stacksize)
    {
        //溢出 追加空间
        s->base = (int *) realloc(s->base , (s->stacksize+STACK_INCREASE_LEN)*sizeof(Stack));
        if(!s->base){return;}
        //改变栈长属性 以及定位top指针的位置
        s->top = s->base + s->stacksize;
        s->stacksize+=STACK_INCREASE_LEN;
    }
    *s->top++=e;
}

T_STACK Pop(Stack * s)
{//出栈操作
    if(StackEmpty(s))
    {
        puts("stack empty");    return -1;
    }
    return *(--s->top);
}

void Pop2(Stack * s, T_STACK * e)
{//出栈操作
    if(StackEmpty(s))
    {
        puts("stack empty");
        return;
    }
    * e = * (--s->top);
}










//逆波兰式 （C语言版）
//#include<iostream.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#define max 100
char ex[max]; /*存储后缀表达式*/
void trans(){ /*将算术表达式转化为后缀表达式*/
    char str[max]; /*存储原算术表达式*/
    char stack[max]; /*作为栈使用*/
    char ch;
    int sum,i,j,t,top=0;
    printf("*****************************************\n");
    printf("*输入一个求值的表达式，以#结束。*\n");
    printf("******************************************\n");
    printf("算数表达式：");
    i=0; /*获取用户输入的表达式*/
    do{
        i++;
//        cin>>str[i];/*此步我用的是C++ C语言的话在后面 之所以用这个有一点区别 都*/
        scanf("%c",&str[i]);
    }while(str[i]!='#' && i!=max);
    sum=i;
    t=1;i=1;
    ch=str[i];i++;
    //
    while(ch!='#'){
        switch(ch){
        case '(': /*判定为左括号*/
            top++;stack[top]=ch;
            break;
        case ')': /*判定为右括号*/
            while(stack[top]!='('){
                ex[t]=stack[top];top--;t++;
            }
            top--;
            break;
        case '+': /*判定为加减号*/
        case '-':
            while(top!=0&&stack[top]!='('){
                ex[t]=stack[top];top--;t++;
            }
            top++;stack[top]=ch;
            break;
        case '*': /*判定为乘除号*/
        case '/':
            while(stack[top]=='*'||stack[top]=='/'){
                ex[t]=stack[top];top--;t++;
            }
            top++;stack[top]=ch;
            break;
        case ' ':break;
        default:while(ch>='0'&&ch<='9'){ /*判定为数字*/
                ex[t]=ch;t++;
                ch=str[i];i++;
            }
            i--;
            ex[t]=' ';t++;
        }
        ch=str[i];i++;
    }
    while(top!=0){
        ex[t]=stack[top];t++;top--;
    }
    ex[t]=' ';
    printf("\n\t原来表达式：");
    for(j=1;j<sum;j++)
        printf("%c",str[j]);
    printf("\n\t逆波兰式：",ex);
    for(j=1;j<t;j++)
        printf("%c",ex[j]);
}
void compvalue(){ /*计算后缀表达式的值*/
    float stack[max],d; /*作为栈使用*/
    char ch;
    int t=1,top=0; /*t为ex下标，top为stack下标*/
    ch=ex[t];t++;
    while(ch!=' '){
        switch(ch){
        case '+':
            stack[top-1]=stack[top-1]+stack[top];
            top--;
            break;
        case '-':
            stack[top-1]=stack[top-1]-stack[top];
            top--;
            break;
        case '*':
            stack[top-1]=stack[top-1]*stack[top];
            top--;
            break; case '/':
            if(stack[top]!=0) stack[top-1]=stack[top-1]/stack[top];
            else{
                printf("\n\t除零错误!\n");
                exit(0); /*异常退出*/
            }
            top--;
            break;
        default:
            d=0;
            while(ch>='0'&&ch<='9'){
                d=10*d+ch-'0'; /*将数字字符转化为对应的数值*/
                ch=ex[t];t++;
            }
            top++;
            stack[top]=d;
        }
        ch=ex[t];t++;
    }
    printf("\n\t计算结果:%g\n",stack[top]);
}

//void main()
//{
//    trans();
//    compvalue();
//}

//数据结构版
int precede(char op)
{ int x;
    switch(op)
    {
    case '*': x=2; break;
    case '/': x=2; break;
    case '+': x=1; break;
    case '-': x=1; break;
    default : x=0;
    }
    return x;
}

void RPExpression1(char * e , char * c)
{/* 返回表达式e的逆波兰式 */
//    char *c;
//    c=(char*)malloc(sizeof(char)*20); //不能用char c[]
    Stack stack1;
    Stack * s1 = & stack1;
    InitStack(s1);
    int i=0,j=0;
    char * ch = & e[i++];
    Push(s1,'@');
    while(*ch!= 0)
    {
        if(*ch=='(')
        {
            Push(s1,ch);
            *ch=e[i++];
        }
        else if(*ch==')')
        {
            while(Top(s1)!='(')
            {
                Pop2(s1,&c[j++]);
            }
            /* to[j++]=pop(&s1);*/
            Pop2(s1,ch);
            *ch=e[i++];
        }
        else if(*ch=='+'||*ch=='-'||*ch=='*'||*ch=='/')
        {
            char w;
            w=Top(s1);
            while(precede(w)>=precede(*ch))
            {
                Pop2(s1,&c[j++]);
                w=Top(s1);
            }
            Push(s1,ch);
            *ch=e[i++];
        }
        else
        {
            //while((ch<='z'&&ch>='a')||(ch<='Z' && ch>='A')){
            c[j++]=*ch;
            *ch=e[i++];
            //}
            //c[j++]=' ';
        }
    }
    Pop2(s1,ch);
    while(*ch!='@')
    {
        c[j++]=*ch;
        Pop2(s1,ch);
    }
    //c[j++]=;
    c[j++]=0;
//    return c;
}



char * RPExpression2(char * e)
/* 返回表达式e的逆波兰式 */
{
    //栈s1用于存放运算符，栈s2用于存放逆波兰式
    Stack stack1,stack2;
    Stack * s1 = & stack1;
    Stack * s2 = & stack2;
    InitStack(s1);
    InitStack(s2);

    //假设字符'#'是运算级别最低的运算符，并压入栈s1中
    Push(s1,'#');

    //p指针用于遍历传入的字符串，ch用于临时存放字符,length用于计算字符串长度
    char *p=e,ch;
    int length=0;
    for(;*p!='\0';p++)//逐个字符访问
    {
        switch(*p)
        {
        //遇'('则直接入栈s1
        case '(':
            Push(s1,*p);
            break;
            //遇')'则将距离栈s1栈顶的最近的'('之间的运算符，逐个出栈，依次送入栈s2,此时抛弃'('
        case ')':
            while(Top(s1)!='(')
            {
                Pop2(s1,ch);
                Push(s2,ch);
            }
            Pop2(s1,ch);
            break;
            //遇下列运算符，则分情况讨论：
            //1.若当前栈s1的栈顶元素是'('，则当前运算符直接压入栈s1；
            //2.否则，将当前运算符与栈s1的栈顶元素比较，若优先级较栈顶元素大，则直接压入栈s1中,
            //  否则将s1栈顶元素弹出，并压入栈s2中，直到栈顶运算符的优先级别低于当前运算符，然后再将当前运算符压入栈s1中
        case '+':
        case '-':
            for(ch=Top(s1);ch!='#';ch=Top(s1))
            {
                if(ch=='(')
                {
                    break;
                }
                else
                {
                    Pop2(s1,ch);
                    Push(s2,ch);
                }
            }
            Push(s1,*p);
            length++;
            break;
        case '*':
        case '/':
            for(ch=Top(s1);ch!='#'&&ch!='+'&&ch!='-';ch=Top(s1))
            {
                if(ch=='(')
                {
                    break;
                }
                else
                {
                    Pop2(s1,ch);
                    Push(s2,ch);
                }
            }
            Push(s1,*p);
            length++;
            break;
            //遇操作数则直接压入栈s2中
        default:
            Push(s2,*p);
            length++;
        }
    }
    //若栈s1非空，则将栈中元素依次弹出并压入栈s2中
    while(!StackEmpty(s1)&&Top(s1)!='#')
    {
        Pop2(s1,ch);
        Push(s2,ch);
    }
    //最后将栈s2输出，逆序排列成字符串;
    char *result;
    result=(char *)malloc(sizeof(char)*(length+1));
    result+=length;
    *result='\0';
    result--;
    for(;!StackEmpty(s2);result--)
    {
        Pop2(s2,ch);
        *result=ch;
    }
    ++result;
    return result;
}
#endif //LOGICDEF_H

