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
void wyswietl_punkty(struct list_node *head);
int wczytaj_z_pliku(struct list_node **head);
void wprowadz_punkty(struct list_node **head, int liczba_punktow);
float dlugosc(int x1,int y1,int x2,int y2);
void komiwojazer(struct list_node *head, int liczba_punktow);

int main() {
    setlocale(LC_ALL, "Polish");
    while(1) {
        struct list_node *head = NULL;
        system("cls");
        printf("Witam w programie Komiwojażer! Proszę wybierz interesującą Cię opcję.\n\n");
        printf("1. Wprowadzanie punktów samodzielnie.\n");
        printf("2. Losowanie punktów.\n");
        printf("3. Wczytywanie punktów z pliku.\n");
        printf("4. Zakończ program.\n");

        switch (input(1,4)) {
            default:
            case 4: {
                return 0;
            }
            case 1: {
                wprowadz_punkty(&head, ilosc_punktow());
                zapisz_do_pliku(head);
                wyswietl_punkty(head);
                komiwojazer(head,list_size(head));
                break;
            }
            case 2: {
                losuj_punkty(&head, ilosc_punktow());
                zapisz_do_pliku(head);
                wyswietl_punkty(head);
                komiwojazer(head,list_size(head));
                break;
            }
            case 3:{
                if (wczytaj_z_pliku(&head) != 0){
                    break;
                }
                wyswietl_punkty(head);
                komiwojazer(head,list_size(head));
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

int wczytaj_z_pliku(struct list_node **head){
    FILE *file;
    system("cls");
    file = fopen("punkty.txt", "r");
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

void komiwojazer(struct list_node *head, int liczba_punktow){
    DWORD start = GetTickCount();
    system("cls");
    float lengthWay = 0;
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
        }
        current_inP = current;
        min = dlugosc(current_outP->x, current_outP->y, current->x, current->y);
        current = head;
        while(current != NULL){
            if(dlugosc(current_outP -> x,current_outP -> y,current -> x,current -> y) < min && current_outP != current){
                min = dlugosc(current_outP -> x,current_outP -> y,current -> x,current -> y);
                current_inP = current;
            }
            current = current -> next;
        }
        printf("%d(%3d,%3d) -> %d(%3d,%3d) = %lf\n", current_outP -> No+1, current_outP -> x, current_outP -> y, current_inP -> No+1, current_inP -> x, current_inP -> y, min);
        pop_by_No(&head, current_outP -> No);
        current_outP = current_inP;
        lengthWay = lengthWay+min;
    }
    double timer = (GetTickCount() - start)/1000.0;
    pop_by_No(&head, current_outP -> No);
    printf("\nMinimalna długość ścieżki wynosi: %lf\n", lengthWay);
    printf("\nCzas wykonania algorytmu wynosi: %.2lf sekund.\n", timer);
    printf("\nWciśnij '1' aby kontynuować\n");
    input(1,1);
    system("cls");
}
