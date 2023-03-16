#include <stdio.h>
#include <regex.h> //obsługa RegEx

char *regex = "^[0-9]+[+*^/-][0-9]+([+*^/-][0-9]+)*(;[0-9]+[+*^/-][0-9]+([+*^/-][0-9]+)*)*$";
char input[1000];

int match(const char *string, char *pattern) 
{
    regex_t re;
    
    if (regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB) != 0)
        return(0);     

    int status = regexec(&re, string, 0, NULL, 0);
    regfree(&re);

    if (status != 0)
        return(0); 

    return(1);
}

int main ()
{
    printf("Akceptowane wyrazenia: 2+2;3+3 lub 2+2 lub 12+2*9;3*8-2/3");
    printf("\nNieakceptowane wyrazenia: 12+9; lub 12.9+9");

    printf ("\n\nPodaj wyrazenie: ");
    scanf("%[^\n]", input); 
    //wszystkie znaki aż do znaku \n (wcisniecie entera)

    int result = match(input, regex);

    if(result == 1)
        printf("\nWyrazenie %s jest poprawne", input);  
    else
        printf("\nWyrazenie %s nie jest poprawne", input);  
    
    return 0;
}