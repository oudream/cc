#ifndef TEMP_H
#define TEMP_H


#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<math.h>

void shift( char notation[]);				//中缀表达式转换为后缀表达式的转换函数
float calculate(float a[][2],int k);		//计算后缀表达式
int judge(char notation[]);					//判断输入的中缀表达式是否符合要求
int grade(char a);							//返回运算符的等级
void display(float a[][2],int k);			//在屏幕上显示后缀表达式

//主函数
void main()
{
    char notation [100];
    char choice;
    do
    {
        printf("请输入正确的中缀表达式:\n");
        printf("例如：2*3+4/3-(2+1)\n");
        scanf("%s",&notation);
        if(judge(notation))
        {
            shift(notation);
        }
        else
            printf("你的表达式有错误，请仔细检查！\n");

    fflush(stdin);
        printf("\n你是否需要继续计算（是输入Y/y，否输入其他任意键）\n");
        scanf("%c",&choice);
        getchar();
        system("cls");
    }while(choice=='Y'||choice=='y');
    printf("\n程序结束，谢谢使用！\n");
}
//判定函数
int judge(char notation[])
{
    int i,m,num=1,p1=0,p2=0;
    for(i=0;notation[i]!='\0';i++)								//排除表达式外的字符
    {
        if(notation[i]!='('&&notation[i]!=')'&&notation[i]!='+'&&notation[i]!='-'
            &&notation[i]!='*'&&notation[i]!='/'&&!isdigit(notation[i])&&notation[i]!='.')
        {
            num=0;
            return num;
        }
    }
    if(notation[0]=='*'||notation[0]=='/'||notation[0]==')'||notation[0]=='.')	//排除第一个字符为*，/，)，.
    {
        num=0;
        return num;
    }
    for(i=0;notation[i]!='\0';i++)	  //排除'+'，'-'，'*'，'/','.'之间的连续出现以及'+'，'-','*'，'/','.'后面直接加')'
    {
        if(notation[i]!='('&&notation[i]!=')'&&!isdigit(notation[i]))
        {
            if(notation[i+1]!='('&&!isdigit(notation[i+1]))
            {
                num=0;
                return num;
            }
        }
        if(notation[i]=='('&&(notation[i+1]==')'||notation[i+1]=='.'||notation[i+1]=='*'||notation[i+1]=='/'))
        {										//排除'('和')','.','*','/'一起连用
            num=0;
            return num;
        }
        if(notation[i]==')'&&(notation[i+1]=='('||notation[i+1]=='.'))//排除')'和'('，'.'一起连用
        {
            num=0;
            return num;
        }
    }
    for(i=0;notation[i]!='\0';i++)								//小数位不得超过4位
    {
        if(notation[i]=='.'&&notation[i+1]!='\0'&&notation[i+2]!='\0'&&notation[i+3]!='\0'&&notation[i+4]!='\0'&&notation[i+5]!='\0')
        {
            if(isdigit(notation[i+1])&&isdigit(notation[i+2])&&isdigit(notation[i+3])&&isdigit(notation[i+4])&&isdigit(notation[i+5]))
            {
                num=0;
                return num;
            }
        }
    }
    for(i=0;notation[i]!='\0';i++)					//排除一个小数中有两个小数点的情况
    {
        if(notation[i]=='.')
        {
            i++;
            while(isdigit(notation[i]))
            {
                i++;
            }
            if(notation[i]=='.')
            {
                num=0;
                return 0;
            }
        }
    }
    for(i=0;notation[i]!='\0';i++)					//排除')'后面不可以直接跟数字以及'('前面不可以加数字
    {
        if(notation[i]==')'&&isdigit(notation[i+1]))
        {
            num=0;
            return num;
        }
        if(isdigit(notation[i])&&notation[i+1]=='('	)
        {
            num=0;
            return num;
        }
    }
    for(i=0;notation[i]!='\0';i++)			//约束数字的位数一共最多为七位
    {
        if(isdigit(notation[i]))
        {
            m=0;							//用来计数，数字的位数为7
            while(isdigit(notation[i])||notation[i]=='.')
            {
                i++;
                m++;
                if(notation[i]=='.')
                {
                    m--;
                }
            }
            if(m>7)
            {
                num=0;
                return num;
            }
        }
    }
    for(i=0;notation[i]!='\0';i++)		//'('与')'需要配对存在
    {
        if(notation[i]=='(')
            p1++;
        if(notation[i]==')')
            p2++;
        if(p1!=p2)
        {
            num=0;
            return num;
        }
    }
    return num;

}
//转换函数
void shift( char notation[])
{
    char s1[100];
    s1[0]='#';
    float s2[100][2];				//第一维放后缀表达式的元素，第二维表示小数点的位数以及是否是运算符
    int i=0,j=1,k=0,t=0;
    float sum,num1=0,num2=0;		//num1为存储整数位num2为存储小数位
    while(notation[i]!='\0')
    {
        if(i==0&&notation[i]=='+')	//第一位为正号的情况
        {
            if(isdigit(notation[++i]))
            {
                num1=0;						//整数部分
                while(isdigit(notation[i]))
                {
                    num1=num1*10+(notation[i]-'0');		//notation[i]-'0'可以将字符转换为整数0~9
                    i++;
                }
                num2=0;						//小数部分
                t=0;
                if(notation[i]=='.')
                {
                    i++;
                    while(isdigit(notation[i]))
                    {
                        num2=float (num2+pow(0.1,++t)*(notation[i]-'0'));
                        i++;
                    }
                }
                s2[k++][0]=float(num1+num2);
                s2[k-1][1]=float(t);
            }
        }
        if(i==0&&notation[i]=='-')	//第一位为负号的情况，代码与正号类似
        {
            if(isdigit(notation[++i]))
            {
                num1=0;
                while(isdigit(notation[i]))
                {
                    num1=(-1)*num1*10+(-1)*(notation[i]-'0');
                    i++;
                }
                num2=0;
                t=0;
                if(notation[i]=='.')
                {
                    i++;
                    while(isdigit(notation[i]))
                    {
                        num2=float(num2+(-1)*pow(0.1,++t)*(notation[i]-'0'));
                        i++;
                    }
                }
                s2[k++][0]=float(num1+num2);
                s2[k-1][1]=float(t);
            }
        }
        if(isdigit(notation[i]))	//当前字符为数字的情况与为正号的情况一样
        {
            num1=0;
            while(isdigit(notation[i]))
            {
                num1=num1*10+(notation[i]-'0');
                i++;
            }
            num2=0;
            t=0;
            if(notation[i]=='.')
            {
                i++;
                while(isdigit(notation[i]))
                {
                    num2=float(num2+pow(0.1,++t)*(notation[i]-'0'));
                    i++;
                }
            }
            s2[k++][0]=float(num1+num2);
            s2[k-1][1]=float(t);
        }
        if(notation[i]=='+'||notation[i]=='-'||notation[i]=='*'||notation[i]=='/')
        {								//当前的字符为操作符时，如果s1的站定为'('则将字符直接送入s1
            if(s1[j-1]=='(')
            {
                s1[j++]=notation[i++];
            }
        }
        if(notation[i]=='+'||notation[i]=='-'||notation[i]=='*'||notation[i]=='/')
        {								//当前字符为操作符时的普通的情况
            if(grade(notation[i])>grade(s1[j-1]))
            {
                s1[j++]=notation[i++];
            }
            else
            {
                s2[k++][0]=s1[--j];
                s2[k-1][1]=-1;
                s1[j++]=notation[i++];
            }
        }
        if(notation[i]=='(')			//当前字符为'('的情况
        {
            s1[j++]=notation[i++];
            if(notation[i]=='+')		//'('后跟正号的情况
            {
                if(isdigit(notation[++i]))
                {
                    num1=0;
                    while(isdigit(notation[i]))
                    {
                        num1=num1*10+(notation[i]-'0');
                        i++;
                    }
                    num2=0;
                    t=0;
                    if(notation[i]=='.')
                    {
                        i++;
                        while(isdigit(notation[i]))
                        {
                            num2=float(num2+pow(0.1,++t)*(notation[i]-'0'));
                            i++;
                        }
                    }
                    s2[k++][0]=float(num1+num2);
                    s2[k-1][1]=float(t);
                }
            }
            if(notation[i]=='-')	//'('后跟负号的情况
            {

                if(isdigit(notation[++i]))
                {
                    num1=0;
                    while(isdigit(notation[i]))
                    {
                        num1=float((-1)*num1*10+(-1)*(notation[i]-'0'));
                        i++;
                    }
                    num2=0;
                    t=0;
                    if(notation[i]=='.')
                    {
                        i++;
                        while(isdigit(notation[i]))
                        {
                            num2=float(num2+(-1)*pow(0.1,++t)*(notation[i]-'0'));
                            i++;
                        }
                    }
                    s2[k++][0]=float(num1+num2);
                    s2[k-1][1]=float(t);
                }
            }
        }
        if(notation[i]==')')		//当前字符为')'的情况
        {
            while(s1[--j]!='(')
            {
                s2[k++][0]=s1[j];
                s2[k-1][1]=-1;
            }
            i++;
        }
    }
    while(j>0&&s1[--j]!='#')	//依次将s1中的除了'#'外的所有操作符出栈，相当于最后的扫尾工作
    {
        s2[k++][0]=s1[j];
        s2[k-1][1]=-1;
    }
    printf("\n后缀表达式（逆波兰表达式）：\n");
    display(s2,k-1);
    printf("\n表达式的值为：\n");
    sum=calculate(s2,k-1);
    printf("%7.4f",sum);
}
//计算函数
float calculate(float a[][2],int k)
{
    int i,t=0,j=k;
    float b[100][2],c[100];
    for(i=k;i>=0;i--)
    {
        b[i][0]=a[k-i][0];
        b[i][1]=a[k-i][1];
    }
    i=k;
    while(j>=0)
    {
        if(b[i][1]!=-1)
        {
            c[t]=float (b[i][0]);
            j--;
            i--;
            t++;
        }
        if(b[i][1]==-1)	//每当遇到一个运算符则将栈最上面的两个数出栈进行运算，然后再入栈
        {
            if(int(b[i][0])=='+')
            {
                c[t-2]=float (c[t-2]+c[t-1]);
            }
            if(int(b[i][0])=='-')
            {
                c[t-2]=float (c[t-2]-c[t-1]);
            }
            if(int(b[i][0])=='*')
            {
                c[t-2]=float (c[t-2]*c[t-1]);
            }
            if(int(b[i][0])=='/')
            {
                c[t-2]= float (c[t-2]/c[t-1]);
            }
            j--;
            i--;
            t--;
        }
    }
    return c[0];	//运算到最后，栈中的元素即为结果
}
//等级函数
int grade(char a)	//按照运算符的优先级
{
    if(a=='#')
        return 0;
    if(a=='(')
        return 1;
    if(a=='-'||a=='+')
        return 2;
    if(a=='*'||a=='/')
        return 3;
    if(a==')')
        return 4;
    else
        return 5;
}
//显示函数
void display(float a[][2],int k)
{
    int i;
    for(i=0;i<=k;i++)
    {
        if(a[i][1]==0)
            printf(" %d",int(a[i][0]));
        if(a[i][1]==1)
            printf(" %7.1f",a[i][0]);
        if(a[i][1]==2)
            printf(" %7.2f",a[i][0]);
        if(a[i][1]==3)
            printf(" %7.3f",a[i][0]);
        if(a[i][1]==4)
            printf(" %7.4f",a[i][0]);
        if(a[i][1]==-1)
            printf(" %c",int (a[i][0]));
    }
}


#endif // TEMP_H
