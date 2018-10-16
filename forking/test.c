// C program to find number of Zombie processes a 
// system can handle.
#include<stdio.h>
#include<unistd.h>
 
int main()
{
    int count = 0;
    while (fork() > 0)
    {
        count++;
        printf("%d\t", count);
    }
}