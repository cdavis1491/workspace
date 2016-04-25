#include <stdio.h>
#include <string.h>
 
int main()
{
    char string[] = "A B C";
    char *token;
    char *save;
 
    token = strtok_r(string, " ", &save); 
    while (token != NULL) {
        printf("%s\n", token);
        token = strtok_r(NULL, " ", &save);
    }
    return 0;
}