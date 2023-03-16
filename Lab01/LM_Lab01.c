#include <stdio.h>

int state = 0; //stany q0,q1,q2,...,q24
int coin = 0; //wrzucana moneta: 1, 2 lub 5

//tablice przejsc: 
int tab_coin_1[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,20,21,22,23,24};
int tab_coin_2[] = {2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,20,21,22,23,24}; 
int tab_coin_5[] = {5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,20,21,22,23,24};
int tab_przejscia[]; //komentarz po sprawdzeniu: POPRAWIĆ KONIECZNIE INIT!! albo malloc, albo [24] wpisać
int n = 0; //zmienna do tab_przejscia

int loop = 1; //do petli while w int main()
int pokaz_reszte = 1; //do if, ktory ma printf ile reszty wydano; ta zmienna pozwala na wyswietlanie reszty tylko raz

void check_coin(int coin) //sprawdzanie, czy wrzucono poprawną monetę
{
    if (coin != 1 && coin != 2 && coin != 5) //jezeli moneta nie jest 1, 2 lub 5
    {
        printf("Nieprawidlowa moneta! Koniec programu");
        loop = 0; //powoduje przerwanie petli while w int main
    }
}

void if_coin_fun() //ponieważ powtarza się dwa razy kod, wrzucono w funkcję; dotyczy obsługi monet, a potem stanu
{
    if(coin == 1)
    {
        printf("state: %d",tab_coin_1[state]);
        state = tab_coin_1[state]; //stan = odpowiedni stan z tabeli przejsc dla monety 1
    }
    if(coin == 2)
    {
        printf("state: %d",tab_coin_2[state]);
        state = tab_coin_2[state]; //stan = odpowiedni stan z tabeli przejsc dla monety 2
    }
    if(coin == 5)
    {
        printf("state: %d",tab_coin_5[state]);
        state = tab_coin_5[state]; //stan = odpowiedni stan z tabeli przejsc dla monety 5
    }
}

void state_fun(int no_state) //poniewaz kazdy stan jest realizowany tak samo (w jezyku C), przygotowalem ku temu funkcje
{
    if(state == no_state) //przechodzenie miedzy stanami (state), na poczatku jest state == 0
    {
        if (no_state >= 20) //stan akceptujacy od q20 do q24
        {
            printf("\n**Osiągnięto stan akceptujący! Koniec działania**");

            if(pokaz_reszte == 1) //chce, by reszta byla wydawana tylko raz
            {
                printf("\nWydano bilet na mycie samochodu");
                printf("\nWydano resztę: %d",(no_state - 20));
                printf("\nTablica przejść: ");
                for(int i=0; i<=n; i++) //pokaz tablice przejsc
                {
                    printf("\nstate: %d: q%d", i+1, tab_przejscia[i]);
                }
                pokaz_reszte = 0;
            }
            printf("\nMozesz wrzucic monete, lecz bedzie to ignorowane: "); //by spelnic zalozenie DFA, mozna wrzucac dalej
            scanf("%d", &coin); //pobierz monete od uzytkownika
            check_coin(coin); //sprawdz monete
            if_coin_fun(); //sprawdz monete i wybierz odpowiedni stan; tutaj ciagle bedziemy w koncowym
        }

        else //stany nieakceptujace od q0 do q19
        {
            printf("\nWrzuc monete: ");
            scanf("%d", &coin); //pobierz monete od uzytkownika
            check_coin(coin); //sprawdz monete
            if_coin_fun(); //sprawdz monete i wybierz odpowiedni stan
            n++;
            tab_przejscia[n] = state; //przypisywanie stanu do tabeli przejsc wyswietlanej na koncu
        }
    }
}

int main(void)
{
	printf("LM_LAB01 DFA \n");

    while(loop==1) //by zachowac zalozenie DFA, nieskonczona petla
    {
        state_fun(0);
        state_fun(1);
        state_fun(2);
        state_fun(3);
        state_fun(4);
        state_fun(5);
        state_fun(6);
        state_fun(7);
        state_fun(8);
        state_fun(9);
        state_fun(10);
        state_fun(11);
        state_fun(12);
        state_fun(13);
        state_fun(14);
        state_fun(15);
        state_fun(16);
        state_fun(17);
        state_fun(18);
        state_fun(19);
        state_fun(20);
        state_fun(21);
        state_fun(22);
        state_fun(23);
        state_fun(24);
    }
  	return 0;		
}