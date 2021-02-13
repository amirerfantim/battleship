//Theme function
#include "headers.h"
#include "functions.h"
#include "theme.h"

void theme(){
    printf("\n    0 = Black       8 = Gray\n"
           "    1 = Blue        9 = Light Blue\n"
           "    2 = Green       A = Light Green\n"
           "    3 = Aqua        B = Light Aqua\n"
           "    4 = Red         C = Light Red\n"
           "    5 = Purple      D = Light Purple\n"
           "    6 = Yellow      E = Light Yellow\n"
           "    7 = White       F = Bright White\n");

    fflush(stdin);
    char code[10], command[3];

    strcpy(code, "color ");

    printf("\n enter code of your background: ");
    scanf("%s", command);
    strcat(code, command);

    fflush(stdin);

    printf("\n enter code of your text: ");
    scanf("%s", command);
    strcat(code, command);

    system(code);
    system("cls");
    main_menu();

}