#include "headers.h"
#include "functions.h"
#include "theme.h"

struct users *start1;


int main() {
    system("color E0");
    srand(time(0));
    system("mkdir data\\users");

    ReadUsersIn(&start1, 1);
    sort(&start1);
    reverse(&start1);

    system("cls");
    printf ("\nXXXXX   XXXX  XXXXXX XXXXXX XX     XXXXXX  XXXXX XX  XX XX XXXX\n");
    printf ("XX  XX XX  XX   XX     XX   XX     XX     XX     XX  XX XX XX  XX\n");
    printf ("XXXXX  XX  XX   XX     XX   XX     XXXX    XXXX  XXXXXX XX XXXX\n");
    printf ("XX  XX XXXXXX   XX     XX   XX     XX         XX XX  XX XX XX\n");
    printf ("XXXXX  XX  XX   XX     XX   XXXXXX XXXXXX XXXXX  XX  XX XX XX\n");
    main_menu();

    WriteUsersToFile(start1, 1);

}


