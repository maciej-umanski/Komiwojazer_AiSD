#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <math.h>
#include <GL/glut.h>

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

//SEKCJA WSTYDU//
int wybor_wyswietlania();
void komiwojazer_screen(struct list_node *head, int liczba_punktow, int *counter_1, int *counter_2, int *counter_3, float *lengthWay, double *timer);
void windowDisplay();
int x_screen[100000], y_screen[100000], countz = 0, maxVal = 0;
//KONIEC SEKCJI WSTYDU//

int main(int argc, char **argv) {

    glutInit(&argc, argv); // init do wyswietlania grafiki

    int count[3]= {0}, *counter_1 = &count[0], *counter_2 = &count[1], *counter_3 = &count[2];
    // 0 - ilo˜† zmiany punktu; 1 - ilosc obliczonych dlugosci pkt; 2 - ilosc wykonaä p©tli wewn©trznej;
    float length = 0, *lengthWay = &length;
    double time = 0, *timer = &time;
    while(1) {
        struct list_node *head = NULL;
        system("cls");
        printf("Witam w programie Komiwoja¾er! Prosz© wybierz interesuj¥c¥ Ci© opcj©.\n\n");
        printf("1. Wprowadzanie punkt¢w samodzielnie.\n");
        printf("2. Losowanie punkt¢w.\n");
        printf("3. Wczytywanie punkt¢w z pliku.\n");
        printf("4. Przedstawienie pracy algorytmu.\n");
        printf("5. Zakoäcz program.\n");

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
                printf("UWAGA! algorytm wykonuje si© krokowo, nie zalecana wysoka liczba punkt¢w!\n");
                printf("1. Wczytaj punkty testowe (POLECANE!)\n");
                printf("2. Wprowad« punkty samodzielnie\n");
                printf("3. Losuj punkty\n");
                printf("4. Wczytaj punkty z wˆasnego pliku\n");
                printf("5. Powr¢t do menu\n");
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
            puts("\nBˆ¥d, zˆa dana wej˜ciowa. Prosz© wpisz ponownie.");
            scanf("%s", bufortab);
            bufor = strtol(bufortab, &koniec, 10);
        }
        return bufor;
    }
    else{
        while ((*koniec == *bufortab) || (bufor < a) || (bufor > b)) {
            puts("Bˆ¥d, zˆa dana wej˜ciowa. Prosz© wpisz ponownie.");
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
        printf("Wprowad« liczb© punkt¢w:");
        liczba_punktow = input(0, 0);
        if(liczba_punktow <= 1){
            printf("Bˆ¥d! Liczba punkt¢w musi by† wi©ksza od 1. Prosz© wprowadzi† dane ponownie\n\n");
        }
    }while(liczba_punktow <= 1);
    return liczba_punktow;
}

void losuj_punkty(struct list_node **head, int liczba_punktow){
    int begin, end;
    do {
        system("cls");
        printf("Pocz¥tek przedziaˆu losowania liczb:");
        begin = input(0, 0);
        printf("Koniec przedziaˆu losowania liczb:");
        end = input(0, 0);
        system("cls");
        if(begin > end){
            printf("Bˆ¥d! koniec nie mo¾e miec wi©kszej warto˜ci ni¾ pocz¥tek. Prosz© wprowadzi† dane ponownie.\n\n");
            Sleep(1500);
        }
        else if(begin == end){
            printf("Bˆ¥d! Warto˜ci nie mog¥ by† jednakowe. Prosz© wprowadzi† dane ponownie.\n\n");
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
    printf("Czy chcesz zapisa† aktualne punkty do pliku?\n(UWAGA!) Program nadpisze aktualny plik z punktami je¾eli taki jest utworzony!\n1.Tak\n2.Nie\n");
    switch(input(1,2)) {
        case 1:{
            FILE *file;
            if ((file = fopen("punkty.txt", "w")) == NULL) {
                printf("Nast¥piˆ bˆ¥d podczas pr¢by utworzenia pliku z punktami\n");
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
    printf("Czy chcesz zapisa† aktualny wynik do pliku?\n(UWAGA!) Program nadpisze aktualny plik z wynikiem, je¾eli taki jest utworzony!\n1.Tak\n2.Nie\n");
    switch(input(1,2)) {
        case 1:{
            FILE *file;
            if ((file = fopen("wynik.txt", "w")) == NULL) {
                printf("Nast¥piˆ bˆ¥d podczas pr¢by utworzenia pliku z punktami\n");
                Sleep(2000);
                system("cls");
                return;
            } else {
                fprintf(file, "Minimalna dˆugo˜† ˜cie¾ki: %lf\n", *result);
                fprintf(file, "Ilo˜† zmian punktu: %d razy\n", *counter_1);
                fprintf(file, "Dˆugo˜† punktu zostaˆa obliczona %d razy\n", *counter_2);
                fprintf(file, "Ilo˜† wywoˆaä p©tli po˜redniej: %d razy\n", *counter_3);
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
        printf("Wyst¥piˆ bˆ¥d podczas pr¢by otwarcia pliku z punktami lub plik nie istnieje\n");
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
    printf("Czy chcesz wy˜wietli† aktualnie wybrane punkty?\n1.Tak\n2.Nie\n");
    switch(input(1,2)) {
        case 1: {
            system("cls");
            struct list_node *current = head;
            puts("Twoje punkty to:\n");
            for (int i = 1; current != NULL; i++) {
                printf("%d. X=%3d, Y=%3d\n", i, current->x, current->y);
                current = current->next;
            }
            printf("\nWci˜nij '1' aby kontynuowa†\n");
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
    printf("Prosz© wprowad« punkty, ka¾dy zatwierdzaj enterem.\n");
    for (int i = 0; i < liczba_punktow; i++) {
        int x,y;
        printf("Liczba wymaganych punkt¢w do wprowadzenia: %d\n", liczba_punktow - i);
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
    printf("Od kt¢rego miasta chcesz rozpocz¥† swoj¥ w©dr¢wk©? Wpisz jego numer: ");
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
    printf("\nSzczeg¢ˆy pracy algorytmu:\n");
    printf("\nTrasa przebyta przez komiwoja¾era mi©dzy wszystkimi miastami: %lf\n", *lengthWay);
    printf("Ilo˜† zmian punktu: %d razy\n", *counter_1);
    printf("Odlegˆo˜† mi©dzy miastami zostaˆa obliczona %d razy\n", *counter_2);
    printf("Ilo˜† wywoˆaä p©tli po˜redniej: %d razy\n", *counter_3);
    printf("Czas wykonania algorytmu wynosi: %.2lf s.\n", *timer);
    printf("\nWci˜nij '1' aby kontynuowa†\n");
    input(1,1);
    system("cls");
}

void komiwojazer_example(struct list_node *head, int liczba_punktow, float *lengthWay){
    system("cls");
    printf("Przedstawienie dziaˆania algorytmu na podstawie wcze˜niej zdefiniowanych punkt¢w.\n");
    printf("Ilo˜† punkt¢w: %d\n", liczba_punktow);
    printf("\nDo wykonania algorytmu wymagane jest stworzenie trzech dodatkowych wska«nik¢w:\n\n");
    printf("current_outP - Wska«nik na miasto, z kt¢rego szukamy najbli¾szego miasta.\n");
    printf("current_inP - Wska«nik na miasto, kt¢re le¾y najbli¾ej do w/w.\n");
    printf("current - Wska«nik bufor, na nim sprawdzamy odlegˆo˜ci z miasta wyj˜ciowego i szukamy najbli¾szego.\n\n");
    printf("P©tla gˆ¢wna dziaˆa do momentu, w kt¢rym na li˜cie miast pozostanie jeden element.\n");
    printf("P©tla sprawdzaj¥ca odlegˆo˜ci z miasta outP do najbli¾szego sprawdza ka¾de miasto a¾ nie dojdziemy do koäca listy.\n");
    printf("\nWci˜nij '1' aby kontynuowa†\n");
    input(1,1);
    system("cls");

    struct list_node *current_outP;
    struct list_node *current_inP;
    struct list_node *current;
    int i=0;
    printf("Od kt¢rego miasta chcesz rozpocz¥† swoj¥ w©dr¢wk©? Wpisz jego numer: ");
    current_outP = get(head, (input(1, liczba_punktow))-1);
    system("cls");

    while(head->next != NULL){
        printf("Iteracja p©tli gˆ¢wnej nr %d\n\n", i+1);
        current = head;
        float min;
        if(current_outP == current) {
            current = current -> next;
            printf("Sprawdzane miasto jest miastem wyj˜ciowym. Nast¥pi przej˜cie na nast©pny punkt.\n");
        }
        current_inP = current;
        printf("Obliczenie odlegˆo˜ci wyj˜ciowej mi©dzy miastami. (w celu odniesienia si© do niej w p¢«niejszych etapach)\n\n");
        min = dlugosc(current_outP->x, current_outP->y, current->x, current->y);
        current = head;
        printf("Sprawdzanie odlegˆo˜ci mi©dzy punktami:\n");
        int j = 0;
        while(current != NULL){
            printf("Iteracja p©tli wewn©trznej nr %d\n", j+1);
            if(dlugosc(current_outP -> x,current_outP -> y,current -> x,current -> y) < min && current_outP != current){
                printf("    Nowa Odlegˆo˜† jest mniejsza ni¾ poprzednio obliczona. Nast¥pi podmiana minimalnej odlegˆo˜ci.\n");
                min = dlugosc(current_outP -> x,current_outP -> y,current -> x,current -> y);
                current_inP = current;
            }
            current = current -> next;
            j++;
        }
        printf("\nWyj˜cie z p©tli sprawdzaj¥cej odlegˆo˜ci, wypisanie wyniku:\n");
        printf("\n%d(%3d,%3d) -> %d(%3d,%3d) = %lf\n", current_outP -> No+1, current_outP -> x, current_outP -> y, current_inP -> No+1, current_inP -> x, current_inP -> y, min);
        printf("\nMiasto wyj˜ciowe outP (Nr. %d) zostaje usuni©te z listy (nie ma potrzeby ponownego sprawdzania go w jakimkolwiek kroku)", current_outP->No+1);
        printf("\nMiasto docelowe intP (Nr. %d) zostaje zapisane jako miasto wyj˜ciowe outP", current_inP->No+1);
        printf("\nOdlegˆo˜† miedzy miastami zostaje dodana do poprzednio obliczonych odlegˆo˜ci.");
        pop_by_No(&head, current_outP -> No);
        current_outP = current_inP;
        *lengthWay += min;
        i++;
        printf("\n\nObecna dˆugo˜† pokonanej trasy: %.2lf\n", *lengthWay);
        printf("\nWci˜nij '1' aby kontynuowa†\n");
        input(1,1);
        system("cls");
    }
    pop_by_No(&head, current_outP -> No);
    printf("Nast¥piˆo wyj˜cie z p©tli gˆ¢wnej.\nIlo˜† dost©pnych punkt¢w podr¢¾y wynosi 0, czyli podr¢¾nik przebywaˆ w ka¾dym z miast.\n");
    printf("\nMinimalna dˆugo˜† ˜cie¾ki: %lf\n", *lengthWay);
    printf("\nWci˜nij '1' aby kontynuowa†\n");
    input(1,1);
    system("cls");
}

void komiwojazer_screen(struct list_node *head, int liczba_punktow, int *counter_1, int *counter_2, int *counter_3, float *lengthWay, double *timer){

    maxVal = head->x;

    struct list_node *temp = head;

    while(temp->next != NULL){
        if(abs(temp->x) > maxVal){
            maxVal = temp->x;
        }
        if(abs(temp->y) > maxVal){
            maxVal = temp->y;
        }
        temp = temp->next;
    }

    DWORD start = GetTickCount();
    system("cls");
    struct list_node *current_outP;
    struct list_node *current_inP;
    struct list_node *current;
    printf("Od kt¢rego miasta chcesz rozpocz¥† swoj¥ w©dr¢wk©? Wpisz jego numer: ");
    current_outP = get(head, (input(1, liczba_punktow))-1);
    system("cls");
    x_screen[countz] = current_outP -> x;
    y_screen[countz] = current_outP -> y;
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
        x_screen[countz+1] = current_inP -> x;
        y_screen[countz+1] = current_inP -> y;
        countz++;
        pop_by_No(&head, current_outP -> No);
        current_outP = current_inP;
        *lengthWay += min;
    }
    *timer = (GetTickCount() - start)/1000.0;
    pop_by_No(&head, current_outP -> No);

    printf("\nSzczeg¢ˆy pracy algorytmu:\n");
    printf("\nTrasa przebyta przez komiwoja¾era mi©dzy wszystkimi miastami: %lf\n", *lengthWay);
    printf("Ilo˜† zmian punktu: %d razy\n", *counter_1);
    printf("Odlegˆo˜† mi©dzy miastami zostaˆa obliczona %d razy\n", *counter_2);
    printf("Ilo˜† wywoˆaä p©tli po˜redniej: %d razy\n", *counter_3);
    printf("Czas wykonania algorytmu wynosi: %.2lf s.\n", *timer);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(800,600);
    glutCreateWindow("Komiwojazer ~ Maciej Umanski, Jakub Witas - 1ID15B");
    glutDisplayFunc(windowDisplay);
    glClearColor(1.0,1.0,1.0,1.0);
    glutMainLoop();
}

void windowDisplay(){
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
    glVertex2f((float)x_screen[0]/(float)maxVal,(float)y_screen[0]/(float)maxVal);
    glEnd();

    for(int i = 1; i < countz-1; i++){
        glPointSize(3.0);
        glColor4f(1.0,0.0,0.0,1);
        glBegin(GL_POINTS);
        glVertex2f((float)x_screen[i]/(float)maxVal,(float)y_screen[i]/(float)maxVal);
        glEnd();
    }

    glPointSize(5.0);
    glColor4f(1.0,0.0,0.0,1);
    glBegin(GL_POINTS);
    glVertex2f((float)x_screen[countz]/(float)maxVal,(float)y_screen[countz]/(float)maxVal);
    glEnd();

    for(int i = 0; i < countz-1; i++){
        glLineWidth(1.0);
        glColor4f(0.0,1.0,0.0, 1);
        glBegin(GL_LINE_LOOP);
        glVertex2f((float)x_screen[i]/(float)maxVal,(float)y_screen[i]/(float)maxVal);
        glVertex2f((float)x_screen[i+1]/(float)maxVal,(float)y_screen[i+1]/(float)maxVal);
        glEnd();
    }

    glLineWidth(1.0);
    glColor4f(0.0,1.0,0.0, 1);
    glBegin(GL_LINE_LOOP);
    glVertex2f((float)x_screen[countz-1]/(float)maxVal,(float)y_screen[countz-1]/(float)maxVal);
    glVertex2f((float)x_screen[countz]/(float)maxVal,(float)y_screen[countz]/(float)maxVal);
    glEnd();

    glutSwapBuffers();
}

int wybor_wyswietlania(){
    system("cls");
    printf("Chcesz wy˜wietli† dane graficznie czy tekstowo?.\n");
    printf("Uwaga! Program koäczy swoje dziaˆanie po wy˜wietleniu okna z punktami!\n\n");
    printf("1. Tekstowo.\n");
    printf("2. Graficznie.\n");
    int wybor = input(1,2);
    return wybor;
}