#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    int table[256]={0};

    char str[1000];

    scanf("%s",str);

    int len=strlen(str);

    for(int i=0;i<len;i++){

        char c=str[i];

        if(c==' ' || c=='\n')
            continue;

        table[(int)c]++;
    }

    for(int i=0;i<256;i++){

        if(table[i]>0){
            printf("%c : %d\n",i,table[i]);
        }
    }

    return 0;
}