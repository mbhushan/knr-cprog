#include<stdio.h>

#define MAXLINE 1000
#define TABSTOPS 4

int main(){

    char line[MAXLINE];
    char ch;
    int i,counter,curenttabstop,nexttabstop,blankcounter,tabs;
    i=counter=curenttabstop=nexttabstop=blankcounter=tabs=0;

    while((ch=getchar())!='\n' && i<MAXLINE){
        line[i] = ch;
        ++i;
    }

    for(int j=0;j<i && line[j]!='\n';j++){
        if(counter%TABSTOPS==0){
            curenttabstop=nexttabstop;
            nexttabstop=curenttabstop+TABSTOPS;
        }
        if(line[j]==' '){
            ++blankcounter;
            ++counter;
            if(counter==nexttabstop){
                printf("\t");
                blankcounter=0;
            }
        }else if(line[j]=='\n'){
            printf("%c",line[j]);
            counter=blankcounter=curenttabstop=nexttabstop=0;
        }
        else{
            while(blankcounter>0){
                printf("#");
                --blankcounter;
            }
            printf("%c",line[j]);
            ++counter;
        }
    }

    return 0;

}