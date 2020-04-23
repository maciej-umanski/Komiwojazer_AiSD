#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <locale.h>
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
void zapisz_do_pliku_wynik(float *result, int *counter_1, int *counter_2, int *counter_3, double *timer);
void wyswietl_punkty(struct list_node *head);
int wczytaj_z_pliku(struct list_node **head, char nazwa[]);
void wprowadz_punkty(struct list_node **head, int liczba_punktow);
float dlugosc(int x1,int y1,int x2,int y2);
void komiwojazer(struct list_node *head, int liczba_punktow, int *counter_1, int *counter_2, int *counter_3, float *lengthWay, double *timer);
void komiwojazer_example(struct list_node *head, float *lengthWay);


int main() {
    setlocale(LC_ALL, "Polish");
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
                if (wczytaj_z_pliku(&head, "example.txt") != 0){
                    break;
                }
                wyswietl_punkty(head);
                komiwojazer_example(head, lengthWay);
                break;
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
    int liczba_punktow = 0;
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
    srand(time(0));
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

void zapisz_do_pliku_wynik(float *result, int *counter_1, int *counter_2, int *counter_3, double *timer){
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
        int x = 0, y = 0, i = 0;
        while(fscanf(file, "%d%d", &x, &y) != EOF){
            push_back(head, x, y, i);
            i++;
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
        int x = 0, y = 0;
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
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
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
        float min = 0;
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
    printf("\nMinimalna ogległość między miastami: %lf\n", *lengthWay);
    printf("Ilość zmian punktu: %d razy\n", *counter_1);
    printf("Odległość między miastami została obliczona %d razy\n", *counter_2);
    printf("Ilość wywołań pętli pośredniej: %d razy\n", *counter_3);
    printf("Czas wykonania algorytmu wynosi: %.2lf s.\n", *timer);
    printf("\nWciśnij '1' aby kontynuować\n");
    input(1,1);
    system("cls");
}

void komiwojazer_example(struct list_node *head, float *lengthWay){
    system("cls");
    printf("Przedstawienie działania algorytmu na podstawie wcześniej zdefiniowanych punktów.\n");
    printf("Ilość punktów: 5\n");
    printf("Punkt początkowy nr 3\n");
    printf("\nDo wykonania algorytmu wymagane jest stworzenie trzech dodatkowych list.\n");
    struct list_node *current_outP;
    struct list_node *current_inP;
    struct list_node *current;
    printf("\nNastąpi ustawienie punktu początkowego na nr 3. W przypadku rozpoczynania od miasta nr 1, ten krok zostałby pominięty.\n");
    current_outP = get(head, 3 - 1);
    //system("cls");
    int i=0, j=0;
    printf("Pętla główna działa do momentu, w którym na liście pozostanie jeden element.\n");
    printf("Pętla wewnętrzna działa aż nie dojdziemy do końca listy.\n");
    while(head->next != NULL){
        printf("\nIteracja pętli głównej nr %d\n", i);
        current = head;
        float min = 0;
        printf("Wyzerowanie najmniejszej odległości między dostępnymi miastami.\n");
        if(current_outP == current) {
            current = current -> next;
            printf("Obecny punkt jest taki sam jak szczyt listy. Nastąpi przejście na następny punkt.\n");
        }
        current_inP = current;
        printf("Obliczenie odległości między punktami.\n");
        min = dlugosc(current_outP->x, current_outP->y, current->x, current->y);
        current = head;
        while(current != NULL){
            printf("Iteracja pętli wewnętrznej nr %d\n", j);
            if(dlugosc(current_outP -> x,current_outP -> y,current -> x,current -> y) < min && current_outP != current){
                printf("Odległość między wybranym/ostatnio użytym punktem a punktem X jest mniejsza niż poprzednio obliczona odległość. Nastąpi podmiana minimalnej odległości.\n");
                min = dlugosc(current_outP -> x,current_outP -> y,current -> x,current -> y);
                current_inP = current;
            }
            current = current -> next;
            j++;
        }
        printf("\nWyjście z pętli wewnętrznej.\n");
        printf("\n%d(%3d,%3d) -> %d(%3d,%3d) = %lf\n", current_outP -> No+1, current_outP -> x, current_outP -> y, current_inP -> No+1, current_inP -> x, current_inP -> y, min);
        pop_by_No(&head, current_outP -> No);
        current_outP = current_inP;
        *lengthWay += min;
        i++;
        printf("Obecna długość trasy: %.2lf", *lengthWay);
        printf("\nWciśnij '1' aby kontynuować\n");
        input(1,1);
        system("cls");
    }
    pop_by_No(&head, current_outP -> No);
    printf("Nastąpiło wyjście z pętli głównej. Ilość dostępnych punktów podróży wynosi 0, czyli podróżnik przebywał w każdym z miast.\n");
    printf("\nMinimalna długość ścieżki: %lf\n", *lengthWay);
    printf("\nWciśnij '1' aby kontynuować\n");
    input(1,1);
    system("cls");
}
