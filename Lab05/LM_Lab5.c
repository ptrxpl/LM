#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
Gramatyka (już poprawiona):

S ::= W ; Z
Z ::= W ; Z | eps
W ::= PW’
W’ ::= eps | OW
P ::= R | (W)
R ::= LR’
R’ ::= eps | .L
L ::= CL’
L’ ::= eps | L
C ::= 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
O ::= * | : | + | - | ^

*/

int znakIndex = 0;

bool SprawdzCzyZnakNalezyDoFirstS(char znak);
bool SprawdzCzyZnakNalezyDoFirstZ(char znak);
bool SprawdzCzyZnakNalezyDoFirstW(char znak);
bool SprawdzCzyZnakNalezyDoFirstWPrim(char znak);
bool SprawdzCzyZnakNalezyDoFirstP(char znak);
bool SprawdzCzyZnakNalezyDoFirstR(char znak);
bool SprawdzCzyZnakNalezyDoFirstRPrim(char znak);
bool SprawdzCzyZnakNalezyDoFirstL(char znak);
bool SprawdzCzyZnakNalezyDoFirstLPrim(char znak);
bool SprawdzCzyZnakNalezyDoFirstC(char znak);
bool SprawdzCzyZnakNalezyDoFirstO(char znak);

void readS(char* input);
void readZ(char* input);
void readW(char* input);
void readWPrim(char* input);
void readP(char* input);
void readR(char* input);
void readRPrim(char* input);
void readL(char* input);
void readLPrim(char* input);
void readC(char* input);
void readO(char* input);

int main(void)
{
    char input[1000];
	printf ("Podaj wyrazenie: ");
	scanf("%[^\n]", input);
	printf ("Podano: %s\n",input);

    readS(input);

    //Nie wykryto nigdzie bledu, to:
    printf("**Wyrazenie zgodne z gramatyka**");

    return 0;
}

void readS(char* input)
{
	if (SprawdzCzyZnakNalezyDoFirstS(input[znakIndex]))
    {
		readW(input);
		if (';' == input[znakIndex])
        {
			znakIndex++;
			readZ(input);
		}
		else
        {
			printf ("Wyrazenie niepoprawne");
			exit(0);
		}
	}
    else
    {
		printf ("Wyrazenie niepoprawne");
		exit(0);
	}
}

void readZ(char* input)
{
	if (SprawdzCzyZnakNalezyDoFirstW(input[znakIndex]))
    {
		readW(input);
		if (';' == input[znakIndex])
        {
			znakIndex++;
			readZ(input);
		}
		else
        {
			printf ("Wyrazenie niepoprawne");
			exit(0);
		}
	}
}

void readW(char* input)
{
	if (SprawdzCzyZnakNalezyDoFirstP(input[znakIndex]))
    {
		readP(input);
		readWPrim(input);
	}
    else
    {
		printf ("Wyrazenie niepoprawne");
		exit(0);
	}
}

void readWPrim(char* input)
{
	if (SprawdzCzyZnakNalezyDoFirstO(input[znakIndex]))
		readO(input);
}

void readO(char* input)
{
	znakIndex++;
	if (SprawdzCzyZnakNalezyDoFirstW(input[znakIndex]))
		readW(input);
    else
    {
		printf ("Wyrazenie niepoprawne");
		exit(0);
	}
}

void readP(char* input)
{
	if (SprawdzCzyZnakNalezyDoFirstR(input[znakIndex]))
		readR(input);
	else if ('(' == input[znakIndex])
    {
		znakIndex++;
		
		readW(input);
		
		if (')' == input[znakIndex])
			znakIndex++;
		else
        {
			printf ("Wyrazenie niepoprawne");
			exit(0);
		}
	}
	else
    {
		printf ("Wyrazenie niepoprawne");
		exit(0);
	}
}

void readR(char* input)
{
	if (SprawdzCzyZnakNalezyDoFirstL(input[znakIndex]))
    {
		readL(input);
		readRPrim(input);
	}
	else
    {
		printf ("Wyrazenie niepoprawne");
		exit(0);
	}
}

void readL(char* input)
{
	if (SprawdzCzyZnakNalezyDoFirstC(input[znakIndex]))
    {
		readC(input);
		readLPrim(input);
	}
	else
    {
		printf ("Wyrazenie niepoprawne");
		exit(0);
	}
}

void readLPrim(char* input)
{
	if (SprawdzCzyZnakNalezyDoFirstL(input[znakIndex]))
		readL(input);
}

void readRPrim(char* input)
{	
	if('.' == input[znakIndex])
    {
		znakIndex++;
		readL(input);
	}
}

void readC(char* input)
{
	znakIndex++;
}

bool SprawdzCzyZnakNalezyDoFirstS(char znak)
{
	char firstS[11] = {'0','1','2','3','4', '5', '6', '7', '8', '9', '('};
	
	for (int i=0; i<11; i++)
    {
		if (firstS[i] == znak)
			return true;
	}
	
	return false;
}

bool SprawdzCzyZnakNalezyDoFirstZ(char znak)
{
    return (SprawdzCzyZnakNalezyDoFirstS(znak)); //poniewaz jest ten sam zestaw firstów
}

bool SprawdzCzyZnakNalezyDoFirstW(char znak)
{
    return (SprawdzCzyZnakNalezyDoFirstS(znak));    
}

bool SprawdzCzyZnakNalezyDoFirstWPrim(char znak)
{
	char firstWPrim[5] = {'*',':','+','-','^'};
	
	for (int i=0; i<5; i++)
    {
		if (firstWPrim[i] == znak)
			return true;
	}
	
	return false;
}

bool SprawdzCzyZnakNalezyDoFirstP(char znak)
{
    return (SprawdzCzyZnakNalezyDoFirstS(znak)); //poniewaz jest ten sam zestaw firstów
}

bool SprawdzCzyZnakNalezyDoFirstR(char znak)
{
	char firstR[10] = {'0','1','2','3','4', '5', '6', '7', '8', '9'};
	
	for (int i=0; i<10; i++)
    {
		if (firstR[i] == znak)
			return true;
	}
	
	return false;
}

bool SprawdzCzyZnakNalezyDoFirstRPrim(char znak)
{
	if ('.' == znak) //eps pomijam
		return true;
	else
		return false;
}

bool SprawdzCzyZnakNalezyDoFirstL(char znak)
{
    return (SprawdzCzyZnakNalezyDoFirstR(znak)); //poniewaz jest ten sam zestaw firstów
}

bool SprawdzCzyZnakNalezyDoFirstLPrim(char znak)
{
    return (SprawdzCzyZnakNalezyDoFirstR(znak)); //poniewaz jest ten sam zestaw firstów
}

bool SprawdzCzyZnakNalezyDoFirstC(char znak)
{
    return (SprawdzCzyZnakNalezyDoFirstR(znak)); //poniewaz jest ten sam zestaw firstów
}

bool SprawdzCzyZnakNalezyDoFirstO(char znak)
{
	char firstO[5] = {'*',':','+','-','^'};
	
	for (int i=0; i<5; i++)
    {
		if (firstO[i] == znak)
        	return true;
	}
	
	return false;
}