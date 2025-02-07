#include <stdio.h>
#include <unistd.h>
#include<math.h>
int main()
{
    for (i = 0; i < 4; i++) {
        fork(); 
    }
    printf("Welcome to OS Lab\n");
    return 0;
}

