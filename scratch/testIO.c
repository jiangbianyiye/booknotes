#include<stdio.h>

int main(int argc, char const *argv[])
{
    char buffer[32];
    gets(buffer);
    //fgets(buffer,32,stdin);
    fprintf(stdout,"%s",buffer);
    printf("[]\n");
    return 0;
}