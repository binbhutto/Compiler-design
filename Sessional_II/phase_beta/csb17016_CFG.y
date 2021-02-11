/* Copyright (c) Adil Bin Bhutto. All rights reserved. */


%{
void Initialize();
void GenerateCondition_code();
void TerminateLoop();
void push();
void GenerateCompare_code();
void GenerateAssignment_code();
void GenerateCode();
%}

%token   WHILE ID NUM EQUAL NOT_EQUAL LT_EQUAL GT_EQUAL LT GT
%right  '='
%left   '+' '-'
%left   '*' '/'

%%

D : WHILE {Initialize();} '('C')' {GenerateCondition_code();} '{' S '}' {TerminateLoop();}
C : ID {push();} X E {GenerateCompare_code();}
X : EQUAL {push();}
  | NOT_EQUAL {push();}
  | LT_EQUAL {push();}
  | GT_EQUAL {push();}
  | LT {push();}
  | GT {push();}
  ;
S : ID {push();} '=' {push();} E {GenerateAssignment_code();}';' S
  |;
  ;
E : E '+'{push();} E{GenerateCode();} 
  | E '-'{push();} E{GenerateCode();} 
  | E '*'{push();} E{GenerateCode();} 
  | E '/'{push();} E{GenerateCode();}
  | '(' E ')'
  | ID {push();} 
  | NUM {push();}
  ;

%%

#include "lex.yy.c"
#include<stdio.h>
#include<string.h>

char Stack[1000][100];
int top = 0;
char insideVariable[3]="t0";


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
    strcpy(Stack[++top],yytext);
}
void GenerateCode() {
    printf("\t%s = %s %s %s\n", insideVariable,Stack[top-2], Stack[top-1], Stack[top]);
    top-=2;
    strcpy(Stack[top], insideVariable);
    insideVariable[1]++;
}
void GenerateCompare_code() {
    printf("\t%s = %s %s %s\n",insideVariable, Stack[top-2], Stack[top-1], Stack[top]);
    top-=2;
    strcpy(Stack[top], insideVariable);
    insideVariable[1]++;
}
void GenerateAssignment_code() {
    printf("\t%s = %s\n", Stack[top-2], Stack[top]);
    top-=2;
}
void Initialize() {
    printf("\nStart: \n");
}
void GenerateCondition_code() {
    printf("\t%s = not %s\n", insideVariable, Stack[top]);
    printf("\tif %s goto End\n", insideVariable);
    insideVariable[1]++;
}
void TerminateLoop() {
    printf("\tgoto Start\n");
    printf("End:\n\tend of while loop\n\n");
}
