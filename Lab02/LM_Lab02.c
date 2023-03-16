#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#define FILENAME "tekst.txt" //tutaj nazwa pliku z odczytywaniem, prosze na koncu ani poczatku nie umieszczac znaku # jako rozdzielajacy, lecz tylko pomiedzy slowa

char *state = "0"; //stany q0,q1,q2,...,q16;
//jako char * by zrobić string, bo jest stan "x", który wymaga char i np. "16", który z powodu char w "x", będzie teraz stringiem (tj. char *)
int obsluz_return_sprawdz_znak = 0; //stany 0 i 1, 0 - OK, 1 - zły podany znak

/*
**Słowa w tekst.txt proszę podawać w formacie:**
slowo#slowo#slowo
Gdzie slowo to np. 223222, abccc, 123aaa itd.
Na końcu nie zamieszczać #

**Tabela przejść:**
"x" - brak przejścia
Jest ona dwuwymiarowa z stanu q0, gdzie sa 2 mozliwosci pojscia po NFA.
Tak naprawdę ten drugi wymiar jest mi tylko potrzebny do q0, ale z racji języka C muszę uzupełnić potem wszędzie, by zgadzał się wymiar tabeli (programistycznie).

NFA, które wygląda tak jak w zadaniu, można sprawdzić w taki sposób, żeby wykonać pętle tyle razy,ile jest znaków w wyrazie (np. 223222 = 6 razy) i po każdej iteracji "ucinać" z lewej strony symbol.

Będzie to odpowiadało zapętleniu na początku i osiągniemy taki sam efekt.

Przykład: 223222 (6 znaków w wyrazie)
To, co jest w nawiasach, pozostaje w q0
1) ()223222
2) (2)23222
3) (22)3222
4) (223)222 <- OK
5) (2232)22
6) (22322)2
*/

//Tabele przejść:
//drugi wymiar potrzebny tylko do q0, pozostałe stany maja wpisane jako drugi "x"
char *tab_0[17][2] = { 
    {"1","0"},{"2","x"},{"3","x"},{"3","x"},{"x","x"},{"x","x"},{"x","x"},{"x","x"},{"x","x"},{"x","x"},{"x","x"},{"x","x"},{"x","x"},{"x","x"},{"x","x"},{"x","x"},{"16","x"}
};

char *tab_1[17][2] = { 
    {"4","0"},{"x","x"},{"x","x"},{"3","x"},{"5","x"},{"3","x"},{"x","x"},{"x","x"},{"x","x"},{"x","x"},{"x","x"},{"x","x"},{"x","x"},{"x","x"},{"x","x"},{"x","x"},{"16","x"}
};

char *tab_2[17][2] = { 
    {"6","0"},{"x","x"},{"x","x"},{"3","x"},{"x","x"},{"x","x"},{"7","x"},{"3","x"},{"x","x"},{"x","x"},{"x","x"},{"x","x"},{"x","x"},{"x","x"},{"x","x"},{"x","x"},{"16","x"}
};

char *tab_3[17][2] = { 
    {"8","0"},{"x","x"},{"x","x"},{"3","x"},{"x","x"},{"x","x"},{"x","x"},{"x","x"},{"9","x"},{"3","x"},{"x","x"},{"x","x"},{"x","x"},{"x","x"},{"x","x"},{"x","x"},{"16","x"}
};

char *tab_a[17][2] = { 
    {"10","0"},{"x","x"},{"x","x"},{"3","x"},{"x","x"},{"x","x"},{"x","x"},{"x","x"},{"x","x"},{"x","x"},{"11","x"},{"16","x"},{"x","x"},{"x","x"},{"x","x"},{"x","x"},{"16","x"}
};

char *tab_b[17][2] = { 
    {"12","0"},{"x","x"},{"x","x"},{"3","x"},{"x","x"},{"x","x"},{"x","x"},{"x","x"},{"x","x"},{"x","x"},{"x","x"},{"x","x"},{"13","x"},{"16","x"},{"x","x"},{"x","x"},{"16","x"}
};

char *tab_c[17][2] = { 
    {"14","0"},{"x","x"},{"x","x"},{"3","x"},{"x","x"},{"x","x"},{"x","x"},{"x","x"},{"x","x"},{"x","x"},{"x","x"},{"x","x"},{"x","x"},{"x","x"},{"15","x"},{"16","x"},{"16","x"}
};

//Funkcja otwiera plik i zwraca całą zawartość, niezależnie od ilości tekstu
char *otworz_plik()
{
    //deklaracja zmiennych
    FILE *infile;
    char *buffer;
    long numbytes;

    //otworz plik
    infile = fopen(FILENAME, "r");
    
    //exit(0), jezeli plik nie istnieje
    if(infile == NULL)
    {
        printf("**Blad, sprawdz nazwe pliku!**");
        exit(EXIT_FAILURE); //albo exit(1), efekt ten sam
    }
    
    //znajdz liczbe bajtów
    fseek(infile, 0L, SEEK_END);
    numbytes = ftell(infile);
    
    //zresetuj wskaźnik pozycji pliku do początku pliku 
    fseek(infile, 0L, SEEK_SET);	
    
    //pobierz wystarczajaca ilosc pamieci do buffer trzymajacego tekst
    buffer = (char*)calloc(numbytes, sizeof(char));	
    
    //blad pamieci
    if(buffer == NULL)
    {
        printf("**Blad pamieci!**");
        exit(EXIT_FAILURE);
    }
    
    //skopiuj caly tekst do bufora
    fread(buffer, sizeof(char), numbytes, infile);
    fclose(infile);

    //zwroc zawartosc 
    return buffer;

    //uwolnij pamiec ktora uzywalismy do buffer
    free(buffer);
}

//Sprwadzanie poprawności symboli w tekście / słowach
int sprawdz_znak(char input)
{
    int zwroc = 0;
    if (input != '0' && input != '1' && input != '2' && input != '3' && input != 'a' && input != 'b' && input != 'c')
    {
        printf("\n**Nieprawidlowy znak %c! Koniec analizy tego slowa**\n",input);
        printf("\n***************************************************************\n");
        return(zwroc = 1);
    }
    else
    {
        return(zwroc = 0);
    }
}

//Obsługa tabeli przejść
void if_fun(char input, char czy_only_q0)
{
    //atoi - Ascii TO Integer
    //atoi - zamiana z string na int, bo trzeba podać int jako argument do tabeli

    if (czy_only_q0 == 'n') //nie - nie zapetlamy w q0
    {
        if(input == '0')
            state = tab_0[atoi(state)][0]; 
        if(input == '1')
            state = tab_1[atoi(state)][0];
        if(input == '2')
            state = tab_2[atoi(state)][0];
        if(input == '3')
            state = tab_3[atoi(state)][0];
        if(input == 'a')
            state = tab_a[atoi(state)][0];
        if(input == 'b')
            state = tab_b[atoi(state)][0];
        if(input == 'c')
            state = tab_c[atoi(state)][0];
    }

    if (czy_only_q0 == 't') //'t' - tak - zapetlenie w q0
    {
        if(input == '0')
            state = tab_0[atoi(state)][1]; 
        if(input == '1')
            state = tab_1[atoi(state)][1];
        if(input == '2')
            state = tab_2[atoi(state)][1];
        if(input == '3')
            state = tab_3[atoi(state)][1];
        if(input == 'a')
            state = tab_a[atoi(state)][1];
        if(input == 'b')
            state = tab_b[atoi(state)][1];
        if(input == 'c')
            state = tab_c[atoi(state)][1];
    }
}

int main (void)
{
    //czyszczenie konsoli z poprzednich inforamcji
    system("clear"); 

    //Otwarcie calego pliku
    char *tekst;
    tekst = otworz_plik();
    printf("\ntekst: %s",tekst);
    printf("\n\n***************************************************************\n");

    //Podzielenie tekstu (co znak #)
    char *token = strtok(tekst, "#");
    char *slowa[sizeof(token)];
    int ile_slow = 0; //ile wykryto łącznie słów
    while(token != NULL)
    {
        slowa[ile_slow] = token;
        token = strtok(NULL, "#"); //sprawdzanie względem NULL, by działało
        ile_slow++;
    }

    //Główny silnik:
    for(int i=0; i < ile_slow; i++) //Tyle, ile jest słów
    {
        //Czyszczenie zmiennych
        obsluz_return_sprawdz_znak = 0; //czyszczenie zmiennej dot. sprawdzania znakow

        //Pokaz slowo, ktore jest analizowane
        printf("\nslowo %d: %s",i,slowa[i]);
        //Trzeba stworzyć "podsłowa" z coraz mniejszą ilością znaków do sprawdzenia
        //tj. ucinajac z lewej strony coraz wiecej, a uciete zastapic zapetleniem w q0

        //Ale zaczniemy od obslugi przejsc q0 samych

        //OBSŁUGA SAMYCH Q0
        printf("\n\nzapetlenie w q0: ");
        for (int j=0; j < strlen(slowa[i]); j++) //po calej dlugosci danego slowa i tylko q0 
        {
            char jeden_znak = *(slowa[i]+j); //pobranie JEDNEGO ZNAKU OD LEWEJ STRONY
            obsluz_return_sprawdz_znak = sprawdz_znak(jeden_znak); //sprawdz znak
            if(obsluz_return_sprawdz_znak == 0) //0 jak zwraca - to OK, 1 - nie 
            {
                printf("\n jeden_znak_q0: %c", jeden_znak);
                if_fun(jeden_znak, 't'); //funkcja dot. stanów, przesuwanie się po grafie
                //Pokaz aktualny stan
                printf("\nstate: q%s",state); 
            }
            else //obsluz_return_sprawdz_znak == 1
                j=1000; //nie chce sprawdzac dalej, bo jest bledny znak, j=1000 - wyjscie z petli
            
        }  

        //Wykryto zly znak wejsciowy
        //pomin to slowo, continue - loop petli z slowami jest pomijany (brak analizowanych ponizej podslow), idziemy do kolejego slowa
        if(obsluz_return_sprawdz_znak == 1)
        {
            obsluz_return_sprawdz_znak = 0; //resetujemy bo globalna
            continue;
        }

        //PODSLOWA
        for(int j=0; j < strlen(slowa[i]); j++) //Ile znaków w wyrazie, tyle podsłów
        {
            //Wyciagnij po jednym znaku od lewej strony
            char jeden_znak = *(slowa[i]+j); 
            //tyle podslow, ile znaków w słowie
            char *podslowa[strlen(slowa[i])]; //bo trzeba zdefiniowac rozmiar
            //Trzeba ucinać po 1 symbolu z lewej strony i przypisać:
            podslowa[j] = slowa[i] + j;

            //Pokaz podslowa:
            printf("\n\npodslowa[%d]: %s",j,podslowa[j]);
            //Teraz majac podslowa, trzeba każdy sprawdzić kazdy znak po kolei i iść przesuwać stany

            //roznica pomiedzy dlugoscia slowa, a podslowem
            //moze byc podslowo takie samo, jak i slowo, wtedy roznica = 0
            //moze byc podslowo krotsze o np. 1 znak (ze juz ucielo 1 znak z lewej)
            //wtedy w miejsce tego ucietego chce wstawic 'zapetlenie' w q0
            int roznica = strlen(slowa[i]) - strlen(podslowa[j]);

            //JAKO PODSŁOWO ROZUMIEMY TĘ CZĘŚĆ, KTÓRA JUZ NIE BĘDZIE ZAPĘTLONA W Q0
            //roznica - chodzi o to, by teraz obsluzyc to zapetlenie w q0 poczatkowe

            if(roznica != 0)
            {
                for (int j=0; j < roznica; j++) //q0 tyle razy, ile jest roznica 
                {
                    char jeden_znak = *(slowa[i]+j); //j.w, pobieranie jednego znaku itd
                    printf("\n jeden_znak_q0: %c", jeden_znak);
                    if_fun(jeden_znak, 't'); //funkcja dot. stanów, przesuwanie się po grafie
                    //Pokaz aktualny stan
                    printf("\nstate: q%s",state); 
                }      
            }

            //obsluga samych 'podslow'
            //tzn tych przejsc dalej, niz same q0
            for(int k=0; k < strlen(podslowa[j]); k++) //tyle, ile znakow w podslowie
            {
                //Ponownie pobierz po jednym znaku z lewej strony danego podslowa
                char jeden_znak_podslowa = *(podslowa[j]+k); 

                printf("\n jeden_znak_podslowa: %c",jeden_znak_podslowa);

                //w taki sposób trzeba sprawdzać string, state == "0" w C daje warning by użyć strcmp (które zwraca 0, jeżeli jest w state i drugi argument ten sam znak)
                if(strcmp(state, "x") != 0) //jeżeli nie ma "x", czyli nadal możemy iść po grafie
                {
                    if_fun(jeden_znak_podslowa, 'n'); //funkcja dot. stanów, przesuwanie się po grafie
                    //Pokaz aktualny stan
                    printf("\nstate: q%s",state); 
                 }
                else //jeżeli wykryto "x"
                {
                    printf("\n**State qx - nie sprawdzamy dalej!**");
                    break; //wyjdź z pętli, nie sprawdzaj dalej, bo nie ma po co
                }
            }

            if(strcmp(state, "3") == 0 || strcmp(state, "16") == 0) //w podslowie wykryto ktorych z stanow akceptujacych
            {
                j = 1000; //ie sprawdzamy dalej podslow, poiewaz juz wykryto, dalej nie ma sensu
            }

            if(strcmp(state, "3") == 0) //wykryto stan 3 
            {
                printf("\n**Znaleziono trzykrotne powtórzenie cyfry!**");
            }
            if(strcmp(state, "16") == 0) //wykryto stan 16
            {
                printf("\n**Znaleziono trzykrotne powtórzenie litery!**");
            }

            //Zresetuj stan z powrotem do zera, by teraz móc analizować kolejne podsłowo
            state = "0";
        }

        printf("\n\n***************************************************************\n");
    }

    return 0;
}