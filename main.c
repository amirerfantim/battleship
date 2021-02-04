#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define row 10
#define column 10

struct node {

    int row_coor, column_coor, ship_num ;
    struct node *next;
};
struct node *head1 = NULL; // ship coordinates
struct node *head2 = NULL; // forbidden coordinates

/*
void printList(struct node **head) {
    struct node *ptr = *head;
    printf("\n[ ");

    while(ptr != NULL) {
        printf("(%d,%d,[%d]) ",ptr->row_coor,ptr->column_coor, ptr->ship_num);
        ptr = ptr->next;
    }

    printf(" ]");
}
*/

void print_map();
void get_coordinates();
void insert_coordinates();
void get_ship();

int main() {
   print_map(row, column);
  // get_ship();
  // printList(&head2);
  //printList(&head1);
}

void get_ship(){
    get_coordinates(5, 1);
    get_coordinates(3, 2);
    get_coordinates(3, 3);
    get_coordinates(2, 4);
    get_coordinates(2, 5);
    get_coordinates(2, 6);
    get_coordinates(1, 7);
    get_coordinates(1, 8);
    get_coordinates(1, 9);
    get_coordinates(1, 10);

}

void print_map(int inner_row, int inner_column){
    int i1, i2, i3, col_counter = 1;
    printf("   ");

    for(i3 = 0; i3 < 4*inner_column; i3++) {
        if((i3 +2) % 4 == 0) {
            printf("%d", col_counter);
            col_counter++;
        }else{
            printf("-");
        }
    }

    printf("-\n");

    for(i1 = 0; i1 < inner_row; i1++){
        printf("%3d", i1+1);
        for(i2 = 0; i2 < inner_column; i2++){
            printf("|   ");
        }

        printf("|\n   ");

        for(i3 = 0; i3 < 4*inner_column; i3++) {
            printf("-");
        }
        printf("-\n");
    }

}

void get_coordinates(int lenght, int ship_num) {
    printf("\nenter coordinates of %d block lenght ship:\n", lenght);
    int first_row, first_column, end_row, end_column;

    printf("enter row number of start point: ");
    scanf("%d", &first_row);
    printf("enter column number of start point: ");
    scanf("%d", &first_column);
    printf("enter row number of end point: ");
    scanf("%d", &end_row);
    printf("enter column number of end point: ");
    scanf("%d", &end_column);

    int i ;
    if(fmax(first_row, end_row) <= row && fmax(first_column, end_column) <= column
    && fmin(first_row, end_row)  > 0 && fmin(first_column, end_column) > 0) {

        if (first_row == end_row && (int) (abs(first_column - end_column) + 1) == lenght) {

            i = (int) fminf((float) first_column, (float) end_column);
            insert_coordinates(first_row, i - 1, ship_num, &head2);

            for (; i <= (int) fmaxf((float) first_column, (float) end_column); i++) {
                insert_coordinates(first_row, i, ship_num, &head1);
                insert_coordinates(first_row + 1, i, ship_num, &head2);
                insert_coordinates(first_row - 1, i, ship_num, &head2);
            }
            insert_coordinates(first_row, i, ship_num, &head2);
        }

        else if (first_column == end_column && (int) (abs(first_row - end_row) + 1) == lenght) {

            i = (int) fminf((float) first_row, (float) end_row);
            insert_coordinates(i - 1, first_column, ship_num, &head2);

            for (; i <= (int) fmaxf((float) first_row, (float) end_row); i++) {
                insert_coordinates(i, first_column, ship_num, &head1);
                insert_coordinates(i, first_column + 1, ship_num, &head2);
                insert_coordinates(i, first_column - 1, ship_num, &head2);
            }
            insert_coordinates(i, first_column, ship_num, &head2);
        }
        else{
            printf("\nyou entered invalid inputs! :)\nTry Again...\n\n");
            get_coordinates(lenght,ship_num);
        }
    }

    else{
        printf("\nyou entered invalid inputs! :)\nTry Again...\n\n");
        get_coordinates(lenght,ship_num);
    }
}

void insert_coordinates( int inner_row,int inner_column,int ship_num, struct node **head){
    struct node *link = (struct node*) malloc(sizeof(struct node));

    link->row_coor = inner_row;
    link->column_coor = inner_column;
    link->ship_num = ship_num;

    link->next = *head;
    *head = link;
}

