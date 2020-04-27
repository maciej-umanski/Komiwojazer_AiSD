#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <math.h>

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


int main() {
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
                komiwojazer(head,list_size(head), counter_1, counter_2, counter_3, lengthWay, timer);
                zapisz_do_pliku_wynik(lengthWay, counter_1, counter_2, counter_3, timer);
                break;
            }
            case 2: {
                losuj_punkty(&head, ilosc_punktow());
                zapisz_do_pliku(head);
                wyswietl_punkty(head);
                komiwojazer(head,list_size(head), counter_1, counter_2, counter_3, lengthWay, timer);
                zapisz_do_pliku_wynik(lengthWay, counter_1, counter_2, counter_3, timer);
                break;
            }
            case 3:{
                if (wczytaj_z_pliku(&head, "punkty.txt") != 0){
                    break;
                }
                wyswietl_punkty(head);
                komiwojazer(head,list_size(head), counter_1, counter_2, counter_3, lengthWay, timer);
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

struct list_node *get(struct list_node *head, int No){
    struct list_node *current=head;
    while(current -> No != No){
        current = current -> next;
    }
    return current;
}

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

float dlugosc(int x1,int y1,int x2,int y2){
    return (float)sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

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
