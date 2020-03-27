/*
 * Copyright (c) Adil Bin Bhutto. All rights reserved.
 * Description: 
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int noT,noNT;
char STK[300];
int TOP = -1;
typedef struct rule
{
	char lhs;
	char rhs[20];
	int num;
}rule;
struct rule rules[30];
typedef struct frst
{
	char c;
	char set[30];
	int len;
}frst;
struct frst firsts[30];
typedef struct follow
{
	char c;
	char set[30];
	int len;
	int visited;
}follow;
struct follow follows[30];
int isNonTerminal(char c,int noRules)
{	
	for(int i=0;i<noRules;i++)
	{
		if(rules[i].lhs==c)
		return 1;
	}
	return 0;
}
void push(char c)
{
	STK[++TOP]=c;
}
void pop()
{
	STK[TOP--]='\0';
}
void printStack()
{
	int i;
	printf("\nTOP=%d\n",TOP);
	for(i=0;i<20;i++)
	{
		if(STK[i]=='\0')
			break;
		printf("%c",STK[i]);
	}	
}
int inarr(char* arr,char c,int noRules)
{
	int i;
	for(i=0;i<noRules;i++)
	{
		if(arr[i]==c)
			return 1;
	}
	return 0;
}
int isInFirSet(char NT, char ch,int noNT)
{
	int i=0;
	int j=0;
	for(i=0;i<noNT;i++)
	{
		if(firsts[i].c==NT)
			break;
	}
	for(j=0;j<=firsts[i].len;j++)
	{		
		if(firsts[i].set[j]==ch)
			return 1;
	}
	return 0;
}
int isInFolSet(char NT, char ch,int noNT)
{
	int i=0;
	int j=0;
	for(i=0;i<noNT;i++)
	{
		if(follows[i].c==NT)
			break;
	}
	for(j=0;j<=follows[i].len;j++)
	{		
		if(follows[i].set[j]==ch)
				return 1;
	}
	return 0;
}

void copyfirst(char NT1,char NT2,int noNT)
{
	int i,j;
	char ch;
	for(i=0;i<noNT;i++)
	{
		if(firsts[i].c==NT1)
		break;
	}
	for(j=0;j<noNT;j++)
	{
		if(firsts[j].c==NT2)
			break;
	}
	int ind;
	int k;
	for(k=0;k<firsts[j].len;k++)
	{
		ind = firsts[i].len;
		ch = firsts[j].set[k];
		if(!isInFirSet(NT1,ch,noNT)&&ch!='e')
		{
			firsts[i].set[ind]=ch;
			firsts[i].len++;
		}		
	}

}
void copyfollow(char NT1,char NT2,int noNT)
{
	printf("\n");
	int i,j;
	char ch;
	for(i=0;i<noNT;i++)
	{
		if(follows[i].c==NT1)
		break;
	}
	for(j=0;j<noNT;j++)
	{
		if(follows[j].c==NT2)
		break;
	}
	int ind;
	int k;
	for(k=0;k<follows[j].len;k++)
	{
		ind = follows[i].len;
		ch = follows[j].set[k];
		if(!isInFolSet(NT1,ch,noNT)&&ch!='e')
		{
			follows[i].set[ind]=ch;
			follows[i].len++;
		}		
	}

}
void copyfollowfirst(char NT1,char NT2,int noNT)
{
	int i,j;
	char ch;
	for(i=0;i<noNT;i++)
	{
		if(follows[i].c==NT1)
		break;
	}
	for(j=0;j<noNT;j++)
	{
		if(firsts[j].c==NT2)
		break;
	}
	int ind;
	int k;
	for(k=0;k<firsts[j].len;k++)
	{
		ind = follows[i].len;
		ch = firsts[j].set[k];
		if(!isInFolSet(NT1,ch,noNT)&&ch!='e')
		{
			follows[i].set[ind]=ch;
			follows[i].len++;
		}		
	}

}

void copyfollowfollow(char NT1,char NT2,int noNT)
{
	int i,j;
	char ch;
	for(i=0;i<noNT;i++)
	{
		if(follows[i].c==NT1)
		break;
	}
	for(j=0;j<noNT;j++)
	{
		if(follows[j].c==NT2)
		break;
	}
	int ind;
	int k;
	for(k=0;k<follows[j].len;k++)
	{
		ind = follows[i].len;
		ch = follows[j].set[k];
		if(!isInFolSet(NT1,ch,noNT)&&ch!='e')
		{
			follows[i].set[ind]=ch;
			follows[i].len++;
		}		
	}

}

void add2first(char NT1,int noRules,int noNT,int rhslen,int ruleno)
{
	rhslen = rhslen+1;
	//printf("\nNT=%c,ruleno=%d,rhslen=%d\t",NT1,ruleno,rhslen);
	int i=0,k=0;
	int j,index;
	char NT2;
	for(k=0;k<rhslen;)
	{
			char NT2=rules[ruleno].rhs[k];
			if(!isNonTerminal(NT2,noRules))
			{
				//add that terminal to NT1
				for(j=0;j<noNT;j++)
				{
					if(firsts[j].c==NT1)
						break;
				}
				if(!isInFirSet(NT1,NT2,noNT))			
				{
					index = firsts[j].len;
					firsts[j].set[index]=NT2;
					firsts[j].len++;
					return;
				}
				//printf("\n");			
			}
			else if(isNonTerminal(NT2,noRules))
			{
				int temp=0;
				for(j=0;j<noRules;j++)
				{
					if((rules[j].lhs==NT2)&&isNonTerminal(rules[j].rhs[0],noRules))
					{
						temp = 1;
						//printf("\n%c\t%s",rules[j].lhs,rules[j].rhs);
						add2first(NT2,noRules,noNT,rules[j].num,j);	
						copyfirst(NT1,NT2,noRules);	
					}
				}
				if(temp==0)
				{
					copyfirst(NT1,NT2,noRules);
				}
				//printf("\n");	
			}
			if((k==rhslen-1)&&isInFirSet(NT2,'e',noNT))
			{
				//printf("\nk=%d,NT1=%c,NT2=%c\n",k,NT1,NT2);
				int m;
				int index;
				for(m=0;m<noNT;m++)
				{
					if(firsts[m].c==NT1)
						break;
				}
				if(!isInFirSet(NT1,'e',noNT))			
				{
					index = firsts[m].len;
					firsts[m].set[index]='e';
					firsts[m].len++;
				}
				return;
			}
			else if(isInFirSet(NT2,'e',noNT)&&(isNonTerminal(NT2,noRules)))
			{ //printf("JJJJJ\n");
				k++;}
			else {//printf("MMMMM\n");
				return;}
			
	}
	//printf("\n");
	
}
void add2follow(char ch,char NT1,int noNT)
{
	int j,index;
	for(j=0;j<noNT;j++)
	{
		if(follows[j].c==NT1)
			break;
	}
	if(!isInFolSet(NT1,ch,noNT))			
	{
		index = follows[j].len;
		follows[j].set[index]=ch;
		follows[j].len++;
	}
}

int charIndexT(char c,char* term,int noT)
{
	int i;
	if(c=='\0')
		return -1;
	for(i=0;i<noT;i++)
	{
		if(c==term[i])
			return i;
	}
	return -1;
}
int charIndexNT(char c,char* nonTerm,int noNT)
{
	int i;
	if(c=='\0')
		return -1;
	for(i=0;i<noNT;i++)
	{
		if(c==nonTerm[i])
			return i;
	}
	return -2;
}
void printTable(int TABLE[noNT][noT],char* term,char *nonTerm)
{
	printf("\nParsing Table:\n");
	int i,j;
	for(i=0;i<noT;i++)
	{
		printf("\t%c",term[i]);
	}
	printf("\n");
	for(i=0;i<noNT;i++)
	{
		printf("%c\t",nonTerm[i]);
		for(j=0;j<noT;j++)
		{
			printf("%d\t",TABLE[i][j]);
		}
		printf("\n");
	}
}

void findfollow(int NT1,int noRules,int noNT)
{
	int i,j,k,x,m;
	for(i=0;i<noNT;i++)
	{
		if(follows[i].c==NT1)
		{
			if(follows[i].visited==1)
			{
				return;
			}
			else
			{
				follows[i].visited=1;
				break;
			}
			
		}
	}
	for(j=0;j<noRules;j++)
	{
		char next;
		for(k=0;k<=rules[j].num;k++)
		{
			if(k==rules[j].num)
			{
				if(rules[j].rhs[k]==NT1)
				{
					findfollow(rules[j].lhs,noRules,noNT);
					copyfollowfollow(NT1,rules[j].lhs,noNT);
				}
			}
			else if(rules[j].rhs[k]==NT1)
			{
				x = k;
				next = rules[j].rhs[++x];
				while(x<(rules[j].num+1))
				{
					int temp;
					if(!isNonTerminal(next,noRules))
					{
						add2follow(next,NT1,noNT);
						break;
					}
					else if(isNonTerminal(next,noRules))
					{
						copyfollowfirst(NT1,next,noNT);
						if(isInFirSet(next,'e',noNT))
						{
							if(x==rules[j].num)
							{
								findfollow(rules[j].lhs,noRules,noNT);
								copyfollowfollow(NT1,rules[j].lhs,noNT);	
							}
							else
								next = rules[j].rhs[x+1];
						}
						
					}
					x++;
				}
			
			}
		}
	}	
}
int main()
{
/*
 * Grammar:
 * 		0	D  -> w(C)bSz						
 * 		1	C  -> iXE 
 *		2	X  -> q
 *		3	X  -> v									
 * 		4	S  -> i=E;S 
 *		5	S  -> e								
 * 		6	E  -> TR											
 *		7	R -> +TR
 *		8	R -> e 								
 * 		9	T  -> FH 												
 *		10	H -> *FH
 *		11	H -> e 						
 * 		12	F  -> (E)
 *		13	F  -> i
 *		14	F  -> n 									
 */		
	rules[0].lhs = 'D';
	strncpy(rules[0].rhs, "w(C)bSz", 7);
	rules[0].num = 6;

	rules[1].lhs = 'C';
	strncpy(rules[1].rhs, "iXE", 3);
	rules[1].num = 2;

	rules[2].lhs = 'X';
	strncpy(rules[2].rhs, "q", 1);
	rules[2].num = 0;

	rules[3].lhs = 'X';
	strncpy(rules[3].rhs, "v", 1);
	rules[3].num = 0;

	rules[4].lhs = 'S';
	strncpy(rules[4].rhs, "i=E;S", 5);
	rules[4].num = 4;

	rules[5].lhs = 'S';
	strncpy(rules[5].rhs, "e", 1);
	rules[5].num = 0;

	rules[6].lhs = 'E';
	strncpy(rules[6].rhs, "TR", 2);
	rules[6].num = 1;

	rules[7].lhs = 'R';
	strncpy(rules[7].rhs, "+TR", 3);
	rules[7].num = 2;

	rules[8].lhs = 'R';
	strncpy(rules[8].rhs, "e", 1);
	rules[8].num = 0;

	rules[9].lhs = 'T';
	strncpy(rules[9].rhs, "FH", 2);
	rules[9].num = 1;

	rules[10].lhs = 'H';
	strncpy(rules[10].rhs, "*FH", 3);
	rules[10].num = 2;

	rules[11].lhs = 'H';
	strncpy(rules[11].rhs, "e", 1);
	rules[11].num = 0;

	rules[12].lhs = 'F';
	strncpy(rules[12].rhs, "(E)", 3);
	rules[12].num = 2;

	rules[13].lhs = 'F';
	strncpy(rules[13].rhs, "i", 1);
	rules[13].num = 0;

	rules[14].lhs = 'F';
	strncpy(rules[14].rhs, "n", 1);
	rules[14].num = 0;


	int i,j,k=0;
	int noRules=15;
	char NT,NT1,NT2;
	printf("\n");
	printf("Rule   \t\tRule no.\n");
	for(i=0;i<noRules;i++)
	{
		printf("%c   ->\t",rules[i].lhs);
		for(j=0;j<(rules[i].num)+1;j++)
		{
			printf("%c",rules[i].rhs[j]);
		}
		printf("\t%d\n",i);
	}	
	//nonTerminal calc
	char arr[noRules];
	char ch;
	for(i=0;i<noRules;)
	{
		ch = rules[i].lhs;
		if(!inarr(arr,ch,noRules))
			arr[k++]=ch;
		else if(inarr(arr,ch,noRules))
			i++;
	}

	for(i=0;i<k;i++)
	{
		firsts[i].c=arr[i];
		follows[i].c=arr[i];
	}
	int index;
	noNT = k;
	char nonTerm[k];
	for(i=0;i<k;i++)
	{
		nonTerm[i]=arr[i];
	}
	//term calc
	char term[40];
	k=0;
	for(i=0;i<noRules;i++)
	{
		int len;
		len = rules[i].num+1;
		for(j=0;j<=len;j++)
		{
			ch = rules[i].rhs[j];
			if(!isNonTerminal(ch,noRules))
			{
				if((!inarr(term,ch,noRules))&&ch!='\0'&&ch!='e')
				{		
					term[k++]=ch;
				}
			}
		}
	}
	term[k++]='$';
	noT = k;
	//printing non term and term. . .		
	printf("\nTerminals are:\t\t");
	for(i=0;i<noT;i++)
	{
		printf("%c\t",term[i]);
	}
	printf("\nNon-Terminals are:\t");
	for(i=0;i<noNT;i++)
	{
		printf("%c\t",nonTerm[i]);
	}

	//first set calculation
	for(i=0;i<noRules;i++)
	{
		char first=0;
		char second=0;
		first = rules[i].rhs[0];
		if(rules[i].num!=0)
			second = rules[i].rhs[1];
		if(!isNonTerminal(first,noRules))
		{
			NT = rules[i].lhs;			
			for(j=0;j<noNT;j++)
			{
				if(firsts[j].c==NT)
				break;
			}
			if(!isInFirSet(NT,first,noNT))			
			{
				index = firsts[j].len;
				firsts[j].set[index]=first;
				firsts[j].len++;
			}			
		}

	}
	
	for(i=0;i<noRules;i++)
	{
		char first=0;
		char second=0;
		first = rules[i].rhs[0];
		if(rules[i].num!=0)
			second = rules[i].rhs[1];
		if(isNonTerminal(first,noRules))
		{
			NT1 = rules[i].lhs;
			add2first(NT1,noRules,noNT,rules[i].num,i);
		}
	}
	printf("\n\nFIRST SET: \n");
	for(i=0;i<noNT;i++)
	{
		printf("%c  :  %s\n",firsts[i].c,firsts[i].set);
	}	
	//follow set calculation
	add2follow('$',follows[0].c,noNT);
	for(i=0;i<noNT;i++)
	{
		NT1 = follows[i].c;
		findfollow(NT1,noRules,noNT);
	}
	printf("\nFOLLOW SET: \n");
	for(i=0;i<noNT;i++)
	{
		printf("%c  :  %s\n",follows[i].c,follows[i].set);
	}
	//terminals
	
	//making table for predictive parsing
	int TABLE[noNT][noT];
	int Tind,NTind;
	for(i=0;i<noNT;i++)
	{
		for(j=0;j<noT;j++)
			TABLE[i][j]=-1;
	}
	for(i=0;i<noRules;i++) 
	{
		NT = rules[i].lhs;
		NT1 = rules[i].rhs[0];
		if(!isNonTerminal(NT1,noRules))
		{
			Tind = charIndexT(NT1,term,noT);
			NTind = charIndexNT(NT,nonTerm,noT);		
			if((Tind!=-1)&&(NTind!=-1))
				TABLE[NTind][Tind] = i;
			if(NT1=='e')
			{
				for(j=0;j<noNT;j++)
				{
					if(follows[j].c==NT)
						break;
				}
				for(k=0;k<follows[j].len;k++)
				{
					ch = follows[j].set[k];
					Tind = charIndexT(ch,term,noT);
					NTind = charIndexNT(NT,nonTerm,noT);		
					if((Tind!=-1)&&(NTind!=-1)&&(TABLE[NTind][Tind]==-1))
						TABLE[NTind][Tind] = i;
				}
			}
		}
		else if(isNonTerminal(NT1,noRules))
		{
			for(j=0;j<noNT;j++)
			{
				if(firsts[j].c==NT1)
					break;
			}
			for(k=0;k<firsts[j].len;k++)
			{
				ch = firsts[j].set[k];
				Tind = charIndexT(ch,term,noT);
				NTind = charIndexNT(NT,nonTerm,noT);		
				if((Tind!=-1)&&(NTind!=-1))
					TABLE[NTind][Tind] = i;
			}
			if(isInFirSet(NT1,'e',noNT))
			{
				for(j=0;j<noNT;j++)
				{
					if(follows[j].c==NT)
						break;
				}
				for(k=0;k<follows[j].len;k++)
				{
					ch = follows[j].set[k];
					Tind = charIndexT(ch,term,noT);
					NTind = charIndexNT(NT,nonTerm,noT);		
					if((Tind!=-1)&&(NTind!=-1)&&(TABLE[NTind][Tind]==-1))
						TABLE[NTind][Tind] = i;
				}	
			}
		}
	}
	printTable(TABLE,term,nonTerm);
	printf("\n");
	
	return 0;
}
