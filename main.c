#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <math.h>
#include <GL/glut.h>

/**
* \brief struktura przechowująca punkty.
* @param No numer punktu.
* @param x współrzędna x punktu.
* @param y współrzędna y punktu.
* @param *next wskaźnik na następny element.
*/

struct list_node{
    int No;
    int x;
    int y;
    struct list_node * next;
};

void push_back( struct list_node **head, int x, int y, int No);
void pop_by_No(struct list_node **head, int No);
struct list_node *get(struct list_node *head, int No);
int list_size(struct list_node *head);
int input(int a, int b);
int ilosc_punktow();
void losuj_punkty(struct list_node **head, int liczba_punktow);
void zapisz_do_pliku(struct list_node *head);
void zapisz_do_pliku_wynik(const float *result, const int *counter_1, const int *counter_2, const int *counter_3, const double *timer);
void wyswietl_punkty(struct list_node *head);
int wczytaj_z_pliku(struct list_node **head, char nazwa[]);
void wprowadz_punkty(struct list_node **head, int liczba_punktow);
float dlugosc(int x1,int y1,int x2,int y2);
void komiwojazer(struct list_node *head, int liczba_punktow, int *counter_1, int *counter_2, int *counter_3, float *lengthWay, double *timer);
void komiwojazer_example(struct list_node *head, int liczba_punktow, float *lengthWay);
int wybor_wyswietlania();
void komiwojazer_screen(struct list_node *head, int liczba_punktow, int *counter_1, int *counter_2, int *counter_3, float *lengthWay, double *timer);
void windowDisplay();


struct list_node *head_wyswietlanie = NULL; ///<Wskaźnik na listę z miastami do wyświetlenia graficznego

/**
* \brief Główne menu programu
*
* Funkcja zarzadzająca całym programem.
*/

int main(int argc, char **argv) {

    glutInit(&argc, argv); // init do wyswietlania grafiki

    int count[3]= {0}, *counter_1 = &count[0], *counter_2 = &count[1], *counter_3 = &count[2];
    // 0 - ilość zmiany punktu; 1 - ilosc obliczonych dlugosci pkt; 2 - ilosc wykonań pętli wewnętrznej;
    float length = 0, *lengthWay = &length;
    double time = 0, *timer = &time;
    while(1) {
        struct list_node *head = NULL;
        system("cls");
        printf("Witam w programie Komiwojażer! Proszę wybierz interesującą Cię opcję.\n\n");
        printf("1. Wprowadzanie punktów samodzielnie.\n");
        printf("2. Losowanie punktów.\n");
        printf("3. Wczytywanie punktów z pliku.\n");
        printf("4. Przedstawienie pracy algorytmu.\n");
        printf("5. Zakończ program.\n");

        switch (input(1,5)) {
            default:
            case 5: {
                return 0;
            }
            case 1: {
                wprowadz_punkty(&head, ilosc_punktow());
                zapisz_do_pliku(head);
                wyswietl_punkty(head);
                switch(wybor_wyswietlania()){
                    case 1: {
                        komiwojazer(head,list_size(head), counter_1, counter_2, counter_3, lengthWay, timer);
                        break;
                    }
                    case 2:{
                        komiwojazer_screen(head,list_size(head), counter_1, counter_2, counter_3, lengthWay, timer);
                        return 0;
                    }
                }
                komiwojazer(head,list_size(head), counter_1, counter_2, counter_3, lengthWay, timer);
                zapisz_do_pliku_wynik(lengthWay, counter_1, counter_2, counter_3, timer);
                break;
            }
            case 2: {
                losuj_punkty(&head, ilosc_punktow());
                zapisz_do_pliku(head);
                wyswietl_punkty(head);
                switch(wybor_wyswietlania()){
                    case 1: {
                        komiwojazer(head,list_size(head), counter_1, counter_2, counter_3, lengthWay, timer);
                        break;
                    }
                    case 2:{
                        komiwojazer_screen(head,list_size(head), counter_1, counter_2, counter_3, lengthWay, timer);
                        return 0;
                    }
                }
                zapisz_do_pliku_wynik(lengthWay, counter_1, counter_2, counter_3, timer);
                break;
            }
            case 3:{
                if (wczytaj_z_pliku(&head, "punkty.txt") != 0){
                    break;
                }
                wyswietl_punkty(head);
                switch(wybor_wyswietlania()){
                    case 1: {
                        komiwojazer(head,list_size(head), counter_1, counter_2, counter_3, lengthWay, timer);
                        break;
                    }
                    case 2:{
                        komiwojazer_screen(head,list_size(head), counter_1, counter_2, counter_3, lengthWay, timer);
                        return 0;
                    }
                }
                zapisz_do_pliku_wynik(lengthWay, counter_1, counter_2, counter_3, timer);
                break;
            }
            case 4:{
                system("cls");
                printf("UWAGA! algorytm wykonuje się krokowo, nie zalecana wysoka liczba punktów!\n");
                printf("1. Wczytaj punkty testowe (POLECANE!)\n");
                printf("2. Wprowadź punkty samodzielnie\n");
                printf("3. Losuj punkty\n");
                printf("4. Wczytaj punkty z własnego pliku\n");
                printf("5. Powrót do menu\n");
                switch(input(1,5)){
                    case 1:{
                        if (wczytaj_z_pliku(&head, "example.txt") != 0){
                            break;
                        }
                        wyswietl_punkty(head);
                        komiwojazer_example(head,list_size(head), lengthWay);
                        break;
                    }
                    case 2:{
                        wprowadz_punkty(&head, ilosc_punktow());
                        zapisz_do_pliku(head);
                        wyswietl_punkty(head);
                        komiwojazer_example(head, list_size(head), lengthWay);
                    }
                    case 3:{
                        losuj_punkty(&head, ilosc_punktow());
                        zapisz_do_pliku(head);
                        wyswietl_punkty(head);
                        komiwojazer_example(head, list_size(head), lengthWay);
                        break;
                    }
                    case 4:{
                        if (wczytaj_z_pliku(&head, "punkty.txt") != 0){
                            break;
                        }
                        wyswietl_punkty(head);
                        komiwojazer_example(head, list_size(head), lengthWay);
                        break;
                    }
                    case 5:{
                        break;
                    }
                }
            }
        }
    }
}

/**
* \brief Dodawanie punktu na koniec listy.
* @param **head wskaźnik na głowę listy z punktami.
* @param x współrzędna x punktu.
* @param y współrzędna y punktu.
* @param No numer dodawanego punktu.
*/

void push_back(struct list_node **head, int x, int y, int No){
    if(*head==NULL){
        *head = (struct list_node *)malloc(sizeof(struct list_node));
        (*head)->x = x;
        (*head)->y = y;
        (*head)->No = No;
        (*head)->next = NULL;
    }else{
        struct list_node *new_node=*head;
        while (new_node->next != NULL) {
            new_node = new_node->next;
        }
        new_node->next = (struct list_node *)malloc(sizeof(struct list_node));
        new_node->next->x = x;
        new_node->next->y = y;
        new_node->next->No = No;
        new_node->next->next = NULL;
    }
}

/**
* \brief Usuwanie określonego przez numer punktu
*
* Funkcja wyszukuje poprzedni od usuwanego element w celu poprawnego przypisania wskaźników po usunięciu
* wybranego punktu.
* @param **head Wskaźnik na głowę listy z punktami.
* @param No numer usuwanego elementu
*/

void pop_by_No(struct list_node **head, int No){
    struct list_node *current=*head;
    struct list_node *tmp;
    if((*head) -> No == No){
        tmp=(*head)->next;
        free(*head);
        *head=tmp;
    }
    else{
        while(current -> next -> No != No){
            current=current->next;
        }
        if(current -> next -> next == NULL){
            free(current->next);
            current->next=NULL;
        }
        else {
            tmp = current->next;
            current->next = tmp->next;
            free(tmp);
        }
    }

}

/**
* \brief Wyszukiwanie określonego punktu.
*
* Funkcja przeszukuje listy i powórnuje zmienną "No" aż nie będzie się jej wartość zgadzać z
* przekazaną do funkcji. Zwraca wskaźnik szukanego elementu.
* @param *head wskaźnik na głowę listy z punktami.
* @param No wartość szukana.
* @return Wskaźnik szukanego elementu.
*/

struct list_node *get(struct list_node *head, int No){
    struct list_node *current=head;
    while(current -> No != No){
        current = current -> next;
    }
    return current;
}

/**
* \brief Zliczanie długości listy.
*
* Funkcja zlicza długość listy w celu poznania ilości punktów które są w niej zapisane.
* @param *head Wskaźnik na głowę listy z punktami.
* @return Ilość elementów listy.
*/

int list_size(struct list_node *head){
    int counter=0;
    if(head==NULL){
        return counter;
    }
    else{
        struct list_node *current=head;
        do {
            counter++;
            current = current->next;
        }while (current != NULL);
    }
    return counter;
}
/**
* \brief Walidacja danych wprowadzanych przez użytkownika.
*
* Funkcja sprawdza czy w podanym ciągu znaków wprowadzanym przez użytkownika nie znajdują
* się żadne litery czy znaki interpunkcyjne i zwraca jedynie liczby całkowite.
* @param a Najmniejsza akceptowana wprowadzona liczba.
* @param b Najwieksza akceptowana wprowadzona liczba.
* @return Liczba wprowadzona przez użytkownika.
*
*/

int input(int a, int b){
    char bufortab[10], *koniec;
    scanf("%s", bufortab);
    int bufor = strtol(bufortab, &koniec, 10);
    if(a == 0 || b == 0) {
        while (*koniec == *bufortab) {
            puts("\nBłąd, zła dana wejściowa. Proszę wpisz ponownie.");
            scanf("%s", bufortab);
            bufor = strtol(bufortab, &koniec, 10);
        }
        return bufor;
    }
    else{
        while ((*koniec == *bufortab) || (bufor < a) || (bufor > b)) {
            puts("Błąd, zła dana wejściowa. Proszę wpisz ponownie.");
            scanf("%s", bufortab);
            bufor = strtol(bufortab, &koniec, 10);
        }
        return bufor;
    }
}
/**
* \brief Pobiera od użytkownika liczbę punktów do wprowadzenia lub wygenerowania
*
* Funkcja prosi użytkownika o wprowadzenie liczby punktów. Sprawdza czy jest to poprawna wartość
* oraz ją zwraca.
* @return Liczba punktow
*/
int ilosc_punktow(){
    system("cls");
    int liczba_punktow;
    do {
        printf("Wprowadź liczbę punktów:");
        liczba_punktow = input(0, 0);
        if(liczba_punktow <= 1){
            printf("Błąd! Liczba punktów musi być większa od 1. Proszę wprowadzić dane ponownie\n\n");
        }
    }while(liczba_punktow <= 1);
    return liczba_punktow;
}

/**
* \brief Losowanie punktów
*
* Funkcja losuje określoną ilość punktów w pewnym zakresie podanym przez użytkownika
* oraz dopisuje je do listy.
* @param **head wskaźnik na głowę listy z punktami.
* @param liczba_punktow liczba losowanych punktów.
*/

void losuj_punkty(struct list_node **head, int liczba_punktow){
    int begin, end;
    do {
        system("cls");
        printf("Początek przedziału losowania liczb:");
        begin = input(0, 0);
        printf("Koniec przedziału losowania liczb:");
        end = input(0, 0);
        system("cls");
        if(begin > end){
            printf("Błąd! koniec nie może miec większej wartości niż początek. Proszę wprowadzić dane ponownie.\n\n");
            Sleep(1500);
        }
        else if(begin == end){
            printf("Błąd! Wartości nie mogą być jednakowe. Proszę wprowadzić dane ponownie.\n\n");
            Sleep(1500);
        }
    }while(end < begin);
    srand(time(NULL));
    for (int i = 0; i < liczba_punktow; i++) {
        int x = rand() % (end - begin + 1) + begin;
        int y = rand() % (end - begin + 1) + begin;
        push_back(head, x, y, i);
    }
}

/**
* \brief Zapisywanie punktów do pliku
*
* Funkcja zapisuje wylosowane lub wprowadzone samodzielnie punkty do pliku tekstowego.
* @param *head Wskaźnik na głowę listy z punktami.
*/

void zapisz_do_pliku(struct list_node *head){
    system("cls");
    printf("Czy chcesz zapisać aktualne punkty do pliku?\n(UWAGA!) Program nadpisze aktualny plik z punktami jeżeli taki jest utworzony!\n1.Tak\n2.Nie\n");
    switch(input(1,2)) {
        case 1:{
            FILE *file;
            if ((file = fopen("punkty.txt", "w")) == NULL) {
                printf("Nastąpił błąd podczas próby utworzenia pliku z punktami\n");
                Sleep(2000);
                system("cls");
                return;
            } else {
                struct list_node *current = head;
                do {
                    fprintf(file, "%d %d\n", current->x, current->y);
                    current = current->next;
                } while (current != NULL);
            }
            fclose(file);
            system("cls");
            return;
        }
        default:{
            system("cls");
            break;
        }
    }
}

/**
* \brief Zapisywanie wyników pracy algorytmu do pliku
*
* Funkcja zapisuje wyniki pracy algorytmu do pliku tekstowego
* @param *result Droga przebyta przez komiwojażera obliczona przez algorytm.
* @param *counter_1 Ilość zmian punktu sprawdzanego przy liczeniu odległości między miastami przy pracy alogrytmu
* @param *counter_2 Ilość obliczonych i sprawdzonych odległości między miastami przy pracy algorytmu
* @param *counter_3 Ilosc wykonań pętli wewnętrznej przy paracy algorytmu
* @param *timer Czas pracy algorytmu
*/

void zapisz_do_pliku_wynik(const float *result, const int *counter_1, const int *counter_2, const int *counter_3, const double *timer){
    system("cls");
    printf("Czy chcesz zapisać aktualny wynik do pliku?\n(UWAGA!) Program nadpisze aktualny plik z wynikiem, jeżeli taki jest utworzony!\n1.Tak\n2.Nie\n");
    switch(input(1,2)) {
        case 1:{
            FILE *file;
            if ((file = fopen("wynik.txt", "w")) == NULL) {
                printf("Nastąpił błąd podczas próby utworzenia pliku z punktami\n");
                Sleep(2000);
                system("cls");
                return;
            } else {
                fprintf(file, "Minimalna długość ścieżki: %lf\n", *result);
                fprintf(file, "Ilość zmian punktu: %d razy\n", *counter_1);
                fprintf(file, "Długość punktu została obliczona %d razy\n", *counter_2);
                fprintf(file, "Ilość wywołań pętli pośredniej: %d razy\n", *counter_3);
                fprintf(file, "Czas wykonania algorytmu wynosi: %.2lf s.\n", *timer);
            }
            fclose(file);
            system("cls");
            return;
        }
        default:{
            system("cls");
            break;
        }
    }
}

/**
* \brief Wczytywanie punktów z pliku
*
* Funkcja otwiera plik tekstowy oraz przepisuje wartości punktów zapisane w nim
* do struktury.
* @param **head Wskaźnik na głowę listy z punktami.
* @param nazwa[] Nazwa odczytywanego pliku.
* @return 0 w przypadku powodzenia, -1 błędu.
*/


int wczytaj_z_pliku(struct list_node **head, char nazwa[]){
    FILE *file;
    system("cls");
    file = fopen(nazwa, "r");
    if (file == NULL) {
        printf("Wystąpił błąd podczas próby otwarcia pliku z punktami lub plik nie istnieje\n");
        Sleep(2000);
        return -1;
    }
    else{
        int i = 0;
        char x[20], y[20], *koniecx, *koniecy;
        while(fscanf(file, "%s %s", x, y) != EOF){
            int xp = strtol(x, &koniecx, 10);
            int yp = strtol(y, &koniecy, 10);
            if(*koniecx==*x || *koniecy == *y){
                break;
            }
            else{
                push_back(head, xp, yp, i);
                i++;
            }
        }
        fclose(file);
    }
    return 0;
}

/**
* \brief Wypisywanie punktów w liście.
*
* Funkcja wypisuje wszystkie punkty które aktualnie zawiera lista.
* @param *head Wskaźnik na głowę listy z punktami.
*/


void wyswietl_punkty(struct list_node *head){
    system("cls");
    printf("Czy chcesz wyświetlić aktualnie wybrane punkty?\n1.Tak\n2.Nie\n");
    switch(input(1,2)) {
        case 1: {
            system("cls");
            struct list_node *current = head;
            puts("Twoje punkty to:\n");
            for (int i = 1; current != NULL; i++) {
                printf("%d. X=%3d, Y=%3d\n", i, current->x, current->y);
                current = current->next;
            }
            printf("\nWciśnij '1' aby kontynuować\n");
            input(1,1);
            system("cls");
            return;
        }
        default: {
            return;
        }
    }
}
/**
* \brief Wprowadzanie samodzielnie punktów
*
* Funkcja pobiera od użytkownika określoną liczbę współrzednych punktów i zapisuje je do listy
* @param **head Wskaźnik na głowę listy z punktami.
* @param liczba_punktów Ilość punktów które użytkownik musi wprowadzić.
*/

void wprowadz_punkty(struct list_node **head, int liczba_punktow){
    system("cls");
    printf("Proszę wprowadź punkty, każdy zatwierdzaj enterem.\n");
    for (int i = 0; i < liczba_punktow; i++) {
        int x,y;
        printf("Liczba wymaganych punktów do wprowadzenia: %d\n", liczba_punktow - i);
        printf("%d.X=", i + 1);
        x = input(0, 0);
        printf("%d.Y=", i + 1);
        y = input(0, 0);
        push_back(head, x, y, i);
        system("cls");
    }
    system("cls");
}

/**
* \brief Długość między dwoma punktami
*
* Funkcja pomocnicza w algorytmie komiwojażera, oblicza odległosć między dwoma podanymi punktami
* @param x1 Współrzędna X punktu 1
* @param y1 Współrzędna Y punktu 1
* @param x2 Współrzędna X punktu 2
* @param y2 Współrzędna Y punktu 2
* @return Odległość między punktami
*/

float dlugosc(int x1,int y1,int x2,int y2){
    return (float)sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

/**
* \brief Algorytm główny
*
* Funkcja która uruchamia algorytm oraz wypisuje wyniki oraz drogę przebytą przez Komiwojażera
*
* @param *head Wskaźnik na głowę listy z punktami
* @param liczba_punktow Liczba punktów zapisanych w liście
* @param *counter_1 Ilość zmian punktu sprawdzanego przy liczeniu odległości między miastami przy pracy alogrytmu
* @param *counter_2 Ilość obliczonych i sprawdzonych odległości między miastami przy pracy algorytmu
* @param *counter_3 Ilosc wykonań pętli wewnętrznej przy paracy algorytmu
* @param Finalna długość trasy przebytej przez Komiwojażera.
* @param *timer Czas pracy algorytmu.
*
*/

void komiwojazer(struct list_node *head, int liczba_punktow, int *counter_1, int *counter_2, int *counter_3, float *lengthWay, double *timer){
    DWORD start = GetTickCount();
    system("cls");
    struct list_node *current_outP;
    struct list_node *current_inP;
    struct list_node *current;
    printf("Od którego miasta chcesz rozpocząć swoją wędrówkę? Wpisz jego numer: ");
    current_outP = get(head, (input(1, liczba_punktow))-1);
    system("cls");
    while(head->next != NULL){
        current = head;
        float min;
        if(current_outP == current) {
            current = current -> next;
            *counter_1+=1;
        }
        current_inP = current;
        min = dlugosc(current_outP->x, current_outP->y, current->x, current->y);
        *counter_2+=1;
        current = head;
        while(current != NULL){
            *counter_3+=1;
            if(dlugosc(current_outP -> x,current_outP -> y,current -> x,current -> y) < min && current_outP != current){
                min = dlugosc(current_outP -> x,current_outP -> y,current -> x,current -> y);
                *counter_2+=2;
                current_inP = current;
            }
            current = current -> next;
            *counter_1+=1;
        }
        printf("%d(%3d,%3d) -> %d(%3d,%3d) = %lf\n", current_outP -> No+1, current_outP -> x, current_outP -> y, current_inP -> No+1, current_inP -> x, current_inP -> y, min);
        pop_by_No(&head, current_outP -> No);
        current_outP = current_inP;
        *lengthWay += min;
    }
    *timer = (GetTickCount() - start)/1000.0;
    pop_by_No(&head, current_outP -> No);
    printf("\nSzczegóły pracy algorytmu:\n");
    printf("\nTrasa przebyta przez komiwojażera między wszystkimi miastami: %lf\n", *lengthWay);
    printf("Ilość zmian punktu: %d razy\n", *counter_1);
    printf("Odległość między miastami została obliczona %d razy\n", *counter_2);
    printf("Ilość wywołań pętli pośredniej: %d razy\n", *counter_3);
    printf("Czas wykonania algorytmu wynosi: %.2lf s.\n", *timer);
    printf("\nWciśnij '1' aby kontynuować\n");
    input(1,1);
    system("cls");
}

/**
* \brief Funkcja przykładowa algorytmu
*
* Funkcja ta pokazuje krok po kroku przebieg algorytmu i wykonane na nim operacje.
* @param *head Wskaźnik na głowę listy z punktami.
* @param liczba_punktow Liczba punktów zapisanych w liście.
* @param Finalna długość trasy przebytej przez Komiwojażera.
*/

void komiwojazer_example(struct list_node *head, int liczba_punktow, float *lengthWay){
    system("cls");
    printf("Przedstawienie działania algorytmu na podstawie wcześniej zdefiniowanych punktów.\n");
    printf("Ilość punktów: %d\n", liczba_punktow);
    printf("\nDo wykonania algorytmu wymagane jest stworzenie trzech dodatkowych wskaźników:\n\n");
    printf("current_outP - Wskaźnik na miasto, z którego szukamy najbliższego miasta.\n");
    printf("current_inP - Wskaźnik na miasto, które leży najbliżej do w/w.\n");
    printf("current - Wskaźnik bufor, na nim sprawdzamy odległości z miasta wyjściowego i szukamy najbliższego.\n\n");
    printf("Pętla główna działa do momentu, w którym na liście miast pozostanie jeden element.\n");
    printf("Pętla sprawdzająca odległości z miasta outP do najbliższego sprawdza każde miasto aż nie dojdziemy do końca listy.\n");
    printf("\nWciśnij '1' aby kontynuować\n");
    input(1,1);
    system("cls");

    struct list_node *current_outP;
    struct list_node *current_inP;
    struct list_node *current;
    int i=0;
    printf("Od którego miasta chcesz rozpocząć swoją wędrówkę? Wpisz jego numer: ");
    current_outP = get(head, (input(1, liczba_punktow))-1);
    system("cls");

    while(head->next != NULL){
        printf("Iteracja pętli głównej nr %d\n\n", i+1);
        current = head;
        float min;
        if(current_outP == current) {
            current = current -> next;
            printf("Sprawdzane miasto jest miastem wyjściowym. Nastąpi przejście na następny punkt.\n");
        }
        current_inP = current;
        printf("Obliczenie odległości wyjściowej między miastami. (w celu odniesienia się do niej w późniejszych etapach)\n\n");
        min = dlugosc(current_outP->x, current_outP->y, current->x, current->y);
        current = head;
        printf("Sprawdzanie odległości między punktami:\n");
        int j = 0;
        while(current != NULL){
            printf("Iteracja pętli wewnętrznej nr %d\n", j+1);
            if(dlugosc(current_outP -> x,current_outP -> y,current -> x,current -> y) < min && current_outP != current){
                printf("    Nowa Odległość jest mniejsza niż poprzednio obliczona. Nastąpi podmiana minimalnej odległości.\n");
                min = dlugosc(current_outP -> x,current_outP -> y,current -> x,current -> y);
                current_inP = current;
            }
            current = current -> next;
            j++;
        }
        printf("\nWyjście z pętli sprawdzającej odległości, wypisanie wyniku:\n");
        printf("\n%d(%3d,%3d) -> %d(%3d,%3d) = %lf\n", current_outP -> No+1, current_outP -> x, current_outP -> y, current_inP -> No+1, current_inP -> x, current_inP -> y, min);
        printf("\nMiasto wyjściowe outP (Nr. %d) zostaje usunięte z listy (nie ma potrzeby ponownego sprawdzania go w jakimkolwiek kroku)", current_outP->No+1);
        printf("\nMiasto docelowe intP (Nr. %d) zostaje zapisane jako miasto wyjściowe outP", current_inP->No+1);
        printf("\nOdległość miedzy miastami zostaje dodana do poprzednio obliczonych odległości.");
        pop_by_No(&head, current_outP -> No);
        current_outP = current_inP;
        *lengthWay += min;
        i++;
        printf("\n\nObecna długość pokonanej trasy: %.2lf\n", *lengthWay);
        printf("\nWciśnij '1' aby kontynuować\n");
        input(1,1);
        system("cls");
    }
    pop_by_No(&head, current_outP -> No);
    printf("Nastąpiło wyjście z pętli głównej.\nIlość dostępnych punktów podróży wynosi 0, czyli podróżnik przebywał w każdym z miast.\n");
    printf("\nMinimalna długość ścieżki: %lf\n", *lengthWay);
    printf("\nWciśnij '1' aby kontynuować\n");
    input(1,1);
    system("cls");
}

/**
* \brief Algorytm główny - wyświetlanie
*
* Funkcja która uruchamia algorytm oraz wypisuje wyniki oraz drogę przebytą przez Komiwojażera.
* Dodatkowo pokazuje graficznie przy użyciu biblioteki OpenGL drogę komiwojażera między miastami.
*
* @param *head Wskaźnik na głowę listy z punktami
* @param liczba_punktow Liczba punktów zapisanych w liście
* @param *counter_1 Ilość zmian punktu sprawdzanego przy liczeniu odległości między miastami przy pracy alogrytmu
* @param *counter_2 Ilość obliczonych i sprawdzonych odległości między miastami przy pracy algorytmu
* @param *counter_3 Ilosc wykonań pętli wewnętrznej przy paracy algorytmu
* @param Finalna długość trasy przebytej przez Komiwojażera.
* @param *timer Czas pracy algorytmu.
*
* @bug Funkcja wyłącza program po zamknięciu okna grafiki (bardzo prymitywna implementacja biblioteki i
 nie przystosowany do grafiki kod)
*/

void komiwojazer_screen(struct list_node *head, int liczba_punktow, int *counter_1, int *counter_2, int *counter_3, float *lengthWay, double *timer){

    DWORD start = GetTickCount();
    system("cls");
    struct list_node *current_outP;
    struct list_node *current_inP;
    struct list_node *current;
    printf("Od którego miasta chcesz rozpocząć swoją wędrówkę? Wpisz jego numer: ");
    current_outP = get(head, (input(1, liczba_punktow))-1);
    system("cls");

    push_back(&head_wyswietlanie, current_outP->x, current_outP->y, 0);

    while(head->next != NULL){
        current = head;
        float min;
        if(current_outP == current) {
            current = current -> next;
            *counter_1+=1;
        }
        current_inP = current;
        min = dlugosc(current_outP->x, current_outP->y, current->x, current->y);
        *counter_2+=1;
        current = head;
        while(current != NULL){
            *counter_3+=1;
            if(dlugosc(current_outP -> x,current_outP -> y,current -> x,current -> y) < min && current_outP != current){
                min = dlugosc(current_outP -> x,current_outP -> y,current -> x,current -> y);
                *counter_2+=2;
                current_inP = current;
            }
            current = current -> next;
            *counter_1+=1;
        }
        printf("%d(%3d,%3d) -> %d(%3d,%3d) = %lf\n", current_outP -> No+1, current_outP -> x, current_outP -> y, current_inP -> No+1, current_inP -> x, current_inP -> y, min);
        push_back(&head_wyswietlanie, current_inP->x, current_inP->y, 0);
        pop_by_No(&head, current_outP -> No);
        current_outP = current_inP;
        *lengthWay += min;
    }
    *timer = (GetTickCount() - start)/1000.0;
    pop_by_No(&head, current_outP -> No);

    printf("\nSzczegóły pracy algorytmu:\n");
    printf("\nTrasa przebyta przez komiwojażera między wszystkimi miastami: %lf\n", *lengthWay);
    printf("Ilość zmian punktu: %d razy\n", *counter_1);
    printf("Odległość między miastami została obliczona %d razy\n", *counter_2);
    printf("Ilość wywołań pętli pośredniej: %d razy\n", *counter_3);
    printf("Czas wykonania algorytmu wynosi: %.2lf s.\n", *timer);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(800,600);
    glutCreateWindow("Komiwojazer ~ Maciej Umanski, Jakub Witas - 1ID15B");
    glutDisplayFunc(windowDisplay);
    glClearColor(1.0,1.0,1.0,1.0);
    glutMainLoop();
}
/**
* \brief Funkcja wyświetlająca drogę komiwojażera przy użyciu biblioteki OpenGL
*
* Funkcja oblicza i rysuje na ekranie układ współrzednych, punkty (miasta) oraz drogę między nimi.
* Z uwagi na słabą implementacje funkcja wymaga zmiennych globalnych przechowujących dane o punktach.
*/
void windowDisplay(){

    struct list_node *bufor = head_wyswietlanie;

    int maxVal = head_wyswietlanie->x;
    while(bufor != NULL){
        if(abs(bufor->x) > maxVal){
            maxVal = abs(bufor->x);
        }
        if(abs(bufor->y) > maxVal){
            maxVal = abs(bufor->y);
        }
        bufor = bufor->next;
    }
    maxVal += 3;

    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(1.0);
    glColor4f(0.0,0.0,0.0,1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0,-1);
    glVertex2f(0,1);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(-1,0);
    glVertex2f(1,0);
    glEnd();

    glPointSize(5.0);
    glColor4f(0.0,0.0,1.0,1);
    glBegin(GL_POINTS);
    glVertex2f((float)head_wyswietlanie->x/(float)maxVal,(float)head_wyswietlanie->y/(float)maxVal);
    glEnd();

    bufor = head_wyswietlanie->next;

    while(bufor != NULL){
        glPointSize(3.0);
        glColor4f(1.0,0.0,0.0,1);
        glBegin(GL_POINTS);
        glVertex2f((float)bufor->x/(float)maxVal,(float)bufor->y/(float)maxVal);
        glEnd();
        bufor = bufor -> next;
    }

    bufor = head_wyswietlanie;

    while(bufor->next != NULL){
        glLineWidth(1.0);
        glColor4f(0.0,1.0,0.0, 1);
        glBegin(GL_LINE_LOOP);
        glVertex2f((float)bufor->x/(float)maxVal,(float)bufor->y/(float)maxVal);
        glVertex2f((float)bufor->next->x/(float)maxVal,(float)bufor->next->y/(float)maxVal);
        glEnd();
        bufor = bufor -> next;
    }

    glutSwapBuffers();
}

/**
* \brief Pytanie o wyświetlenie algorytmu
*
* Funkcja pytająca użytkownika czy chce wyświetlić algorytm graficznie czy tylko Tekstowo.
*
* @return 1 - tekstowo, 2 - graficznie.
*/
int wybor_wyswietlania(){
    system("cls");
    printf("Chcesz wyświetlić dane graficznie czy tekstowo?.\n");
    printf("Uwaga! Program kończy swoje działanie po wyświetleniu okna z punktami!\n\n");
    printf("1. Tekstowo.\n");
    printf("2. Graficznie.\n");
    int wybor = input(1,2);
    return wybor;
}
