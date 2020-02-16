#include<stdio.h>
#include<string.h>
#include<ctype.h>

void keyword(char* str) 
{ 
    if (!strcmp(str, "if") || !strcmp(str, "else") || 
        !strcmp(str, "while") || !strcmp(str, "do") ||  
        !strcmp(str, "break") ||  
         !strcmp(str, "continue") || !strcmp(str, "int") 
        || !strcmp(str, "double") || !strcmp(str, "float") 
        || !strcmp(str, "return") || !strcmp(str, "char") 
        || !strcmp(str, "case") || !strcmp(str, "char") 
        || !strcmp(str, "sizeof") || !strcmp(str, "long") 
        || !strcmp(str, "short") || !strcmp(str, "typedef") 
        || !strcmp(str, "switch") || !strcmp(str, "unsigned") 
        || !strcmp(str, "void") || !strcmp(str, "static") 
        || !strcmp(str, "struct") || !strcmp(str, "goto")) 
        printf("keyword : %s\n",str);
    
    else
    	printf("identifier : %s\n",str);
} 
int main()
{
	FILE *f1, *f2,*f3,*f4;
	char c,str[10],st1[10],ip[100];
	int num[100], l_no =0,t_val =0,i=0,j=0,k=0;
	int x=0;
	printf("input the program expression\n");
	f1 = fopen("input.txt","w");
	scanf("%[^\n]",ip);

	printf("given string: ");
	while(x<strlen(ip)) // debug output string
	{
		c = ip[x];
		printf("%c",c);
		putc(c,f1);
		x++;
	}
	
	printf("length of expression: %d",strlen(ip));
	fclose(f1);
	printf("\n");
	f1 = fopen("csb17016_01_q2_input","r");
	f2 = fopen("id_key.txt","w");
	f3 = fopen("operator.txt","w");
	f4 = fopen("delimiter.txt","w");
	while(!feof(f1))
	{
		c =getc(f1);
		if(isdigit(c))
		{
			t_val = c -'0';
			c =getc(f1);
			
			while(isdigit(c))
			{
				t_val*=10+c -'0'; // cal. no by no.
				c =getc(f1);
			}
		num[i++] = t_val;
		ungetc(c,f1);
		
		printf(" constants: %d \n",t_val);
		}
		else if(isalpha(c))  //idertifier & keywords
		{

			putc(c,f2);
			c =getc(f1);
			while(isdigit(c)||isalpha(c)||c=='_')
			{
				putc(c,f2);
				c = getc(f1);
			}
			putc(' ',f2);
			ungetc(c,f1);	
		}
		
		
			
		else if(c == '+' || c == '-' || c == '*' ||  c == '/' || c == '>' || c == '<' ||  c == '=') //operator
        	{
        		char c1 = getc(f1);
        		if(c=='+' && c1=='+')
        			putc('++',f3); // ig_warn: multi char 
        		
        		if(c=='-' && c1=='-')
        			putc('--',f3);
        		
        		if(c=='=' && c1=='=')
        			putc('==',f3);
        		if(c=='>' && c1=='=')
        			putc('>=',f3);
				if(c=='<' && c1=='=')
        			putc('<=',f3);	
				
				putc(c,f3);
				putc(' ',f3);
				ungetc(c1,f1);		 // minor bug , extra printed last operator;
			}
			
		else if(c == ',' || c == ';' || c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}' || c ==' ') 
			{
				putc(c,f4);

			}
			
	}

	fclose(f4);
	fclose(f2);
	fclose(f3);
	fclose(f1);
	fclose(f4);

	f3 = fopen("operator.txt","r");
	f4 = fopen("delimiter.txt","r");
	printf("\n operators are: ");
	while((c=getc(f3))!=EOF)
	{
		printf("%c",c);
		
	}
	
	printf("\n delimiter are: ");
	while((c=getc(f4))!=EOF)
	{
		printf("%c ",c);
		
	}
	printf("\n");
	fclose(f3);
	
	f2= fopen("id_key.txt","r");
	k=0;
	printf("KEYWORDS & IDENTIFIERS: \n");
	while(!feof(f2))
	{
		c=getc(f2);
		if(c!=' ')
			str[k++]=c;
		else
			{
				str[k]='\0';
				keyword(str);
			
				k=0;
			}
	}
	fclose(f2);

	
	
}