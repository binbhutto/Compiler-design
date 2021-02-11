%token  ID NUM WHILE
%right  '='
%left   '+' '-'
%left   '*' '/'
%left MINUS

%%

S : WHILE{L1();} '(' E ')'{Lcond();} E ';'{End();}
E : V '='{push();} E{codegen_assign();}
  | E '+'{push();} E{codegen();} 
  | E '-'{push();} E{codegen();} 
  | E '*'{push();} E{codegen();} 
  | E '/'{push();} E{codegen();}
  | '(' E ')'
  | '-'{push();} E{codegen_umin();} %prec MINUS
  | V
  | NUM{push();}
  ;
V : ID{push();}
  ;

%%

#include "lex.yy.c"
#include<stdio.h>
#include<string.h>

char st[100][10];
int top = 0;
char temp[3]="t0";

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("Please provide the file input as parameter.\ne.g. ./a.out file.c\n\n");
        exit(1);
    }
    yyin = fopen(argv[1], "r");
    yyparse();
    return 0;
}

void push() {
    strcpy(st[++top],yytext);
}

void codegen() {
    printf("\t%s = %s %s %s\n", temp,st[top-2], st[top-1], st[top]);
    top-=2;
    strcpy(st[top], temp);
    temp[1]++;
}

void codegen_umin() {
    printf("\t%s=-%s\n", temp, st[top]);
    top--;
    strcpy(st[top], temp);
    temp[1]++;
}

void codegen_assign() {
    printf("\t%s = %s\n", st[top-2], st[top]);
    top-=2;
}

void L1() {
    printf("\nL1: \n");
}

void Lcond() {
    printf("\t%s = not %s\n", temp, st[top]);
    printf("\tif %s goto End\n", temp);
    temp[1]++;
}

void End() {
    printf("\tgoto L1\n");
    printf("End:\n\tend of while loop\n\n");
}
