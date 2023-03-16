#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
TABELA PRZEJŚĆ
{x,y,z}
x - co zapisać na taśmie: "0, 1, -" - niech "-" będzie cyfrą 8
y - stan: 0, 1, 2, 3, 4 //8 odpowiada '-'
z - przesunięcie głowicy: 45 odpowiada - w ASCII, analogicznie 76 jako L, wyswietlam w printf jako %c to
*/

int tab_przejsc[5][3][3] = //wiersz, kolumna, element
{
    {{1,1,76}, {0,2,76}, {8,8,45}}, //q0: {1,q1,L} | {0,q2,L} | {-,-,-}
    {{1,3,76}, {0,4,76}, {8,8,45}}, //q1: {1,q3,L} | {0,q4,L} | {-,-,-}
    {{0,4,76}, {1,4,76}, {8,8,45}}, //q2: {0,q4,L} | {1,q4,L} | {-,-,-}
    {{0,3,76}, {1,3,76}, {8,3,45}}, //q3: {0,q3,L} | {1,q3,L} | {-,q3,-}
    {{1,3,76}, {0,4,76}, {1,3,45}}, //q4: {1,q3,L} | {0,q4,L} | {1,q3,-}
};

int input = 0; //to co wpisujemy z klawiatury (liczbe binarna wielocyfrowa)
int isBinaryResult; //1 - OK, 0 - nieOK; sprawdzenie, czy liczba jest binarna
int index_tasmy = 0; //do przedostania sie po tasmie 
int ile_max_przejsc = 0; //do inicjalizacji tablic oraz petli for

//Funkcja sprawdzajaca input (czy podano binarna liczbe)
int isBinary (int n) //n to input z klawiatury
{ 
    while (n != 0)
    { 
        int x = n % 10; //pobierz ostatia liczbe
        if (x * x != x) //x^2 = x tylko gdy x jest 0 lub 1 - sprawdzenie
            return 0; //NIEbinarna
        n /= 10; //"utnij" liczbe z prawej strony, bo n to i tak int
    } 
    return 1; //binarna
} 

//rozdzielenie cyfry co znak, przypisanie, na koncu (tj. poczatku tabeli) znak teta jako cyfra 2
void tasma_input(int input, int tasma[], int index_tasmy)
{
    tasma[0] = 2; //ostatni (a pierwszy od lewej) ma byc teta

    if(input == 0) //poniewaz 0 jest problematycznym inputem
        tasma[1] = input; //musi byc obsluzone oddzielnie

    else
    {
        while(input != 0) //dopoki input nie jest 0, tj. nie przeanalizowano wszytkiego ponizej (glownie dzielenia)
        {
            tasma[index_tasmy] = input%10; //pobiera ostatnia cyfre
            (index_tasmy)--; //zdekrementuj tasme, by dojechac do [1] ostatecznie
            input /= 10; //podziel przez 10, tj. z np. 213 zrob 21, bo input jest int
        }
    }
}

//pobieranie informacji z tabeli przejsc
void pobierz_z_tabeli_przejsc(int liczba, int stan, int tab_przejsc_dane[])
{
	tab_przejsc_dane[0] = tab_przejsc[stan][liczba][0]; //co zapisać na taśmie
	tab_przejsc_dane[1] = tab_przejsc[stan][liczba][1]; //stan
	tab_przejsc_dane[2] = tab_przejsc[stan][liczba][2]; //przesunięcie taśmy
}

int main(void)
{
    printf("Zwiekszanie liczby wielocyfrowej binarnej o 3");
    printf("\n\nInterpretacja pojawiajacych sie cyfr:");
    printf("\nSymbol 'teta' w podanej liczbie - cyfra 2");
    printf("\nPrzejscie w lewo w tabeli przejsc - cyfra 7");
    printf("\n\nPodaj liczbe wielocyfrowa binarna (bez teta, np. 1110): ");
    scanf("%d",&input);
    printf("\nPodano: %d",input);

    isBinaryResult = isBinary(input); //sprawdz czy liczba jest binarna

    if (input != 0) //gdy input nie jest zerem
    {
        ile_max_przejsc = ((int)floor(log10(abs(input))) + 1) + 1;
        //ile podano znakow + 1, zeby moc inicjalizowac tabele; np. 1111 = 4 znaki
        //max przejsc MT bedzie liczba znakow + ew. 1
        //w sytuacji np. 1111(15) -> 10010(18)

        index_tasmy = ile_max_przejsc - 1; //-1, zeby indeks moc dobry wywolac w tabeli
        //do tasmy, by ją przesuwać, ale bedziemy z niej odejmowac (w indeksie, zmienna z petli for) i tak (przesuwac sie w lewo)
    }

    else //poniewaz 0 jest problematycznym inputem (i wzór wyżej nie działa, bo: log10(0) = -inf)
    {
        ile_max_przejsc = 2; //trzeba ustalic to recznie
        index_tasmy = 1; //i to tez
    }

    int tasma[ile_max_przejsc]; //tasma z podzielonym pojedynczo inputem
    int tab_przejsc_dane[3]; //bo w tab_przejsc sa trzy 'elementy' w {}, np. {1,q1,L}
    int wynik[ile_max_przejsc][2]; //indeks 0 do stanow, indeks 1 do liczby

    int stan = 0; //init stan q0, od tego zaczynamy

    if(isBinaryResult == 1)
    {
        printf("\nPodana cyfra jest binarna\n");

        tasma_input(input, tasma, index_tasmy); //przypisanie do tabeli tasma

        for (int i=0; i<ile_max_przejsc; i++) //np. dla 1011: od 0 do 4 (5 razy), OK
        {			
			if(tasma[index_tasmy - i] != 2) //bo 2 oznacza teta, w tasma_input() funkcji
				printf("\nPo wczytaniu symbolu: %d", tasma[index_tasmy - i]);
			else 
				printf("\nPo wczytaniu symbolu pustego (tj. '2')");

            pobierz_z_tabeli_przejsc(tasma[index_tasmy - i], stan, tab_przejsc_dane);

            //if, zeby ladnie printf wygladal
            if (tab_przejsc_dane[1] == 8) //STAN 8 TO '-', brak przejscia, nie chce wyswietlac 'q-' tylko '-'
                printf("\nMT - {%d,q%d,%d,-,%c}",tasma[index_tasmy - i],stan,tab_przejsc_dane[0],tab_przejsc_dane[2]);

            else
                printf("\nMT - {%d,q%d,%d,q%d,%c}",tasma[index_tasmy - i],stan,tab_przejsc_dane[0],tab_przejsc_dane[1],tab_przejsc_dane[2]);

            stan = tab_przejsc_dane[1]; //przypisz stan do zmiennej stan
            wynik[index_tasmy - i][0] = tab_przejsc_dane[0]; //wynik = co zapisac na tasmie
            wynik[index_tasmy - i][1] = stan; //wynik = stan
        }

        if (tab_przejsc_dane[1] == 8)
		    printf("\n\nKoncowy stan MT: -");
        else
            printf("\n\nKoncowy stan MT: q%d",stan);

		printf("\nPokonana sciezka stanow: ");

        for (int j=0; j<ile_max_przejsc; j++)
        {
            if (wynik[index_tasmy - j][1] == 8) //j.w. z stanem 'q-' a '-'
                printf("- ");
            else
                printf("q%d ",wynik[index_tasmy - j][1]);
        }

        printf("\nWynik: ");

		for(int i=0; i<ile_max_przejsc; i++)
        {
			if(wynik[i][0] !=8) //nie chce pokazywac 8, czyli '-' tak defacto
				printf("%d", wynik[i][0]); 
		}
    }

    else //if(isBinaryResult != 1)
        printf("\n**Podana cyfra nie jest binarna lub wielocyfrowa, koniec programu**");

    return 0;
}