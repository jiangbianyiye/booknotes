#include<stdio.h>

int main(int argc, char const *argv[])
{
    int long_size = sizeof(long);
    int longlong_size = sizeof(long long);
    printf("long:\t\t%d\nlong long:\t\t%d\n",long_size, longlong_size);
    return 0;
}
