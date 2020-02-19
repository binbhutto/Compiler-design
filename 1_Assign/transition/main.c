#include<stdio.h>
#include<iomainip>
#include 'stateTable.h'

int main() {
    std::map<char,int>Map;
        Map['U']=0;
        Map['C']=1;
        Map['A']=2;
        Map['G']=3;
    
    printf("%d",Map['U']);


}