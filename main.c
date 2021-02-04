#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define row 10
#define column 10

struct node {
    int row_coor, column_coor ;
    struct node *next;
};
struct node *head1 = NULL; // ship coordinates
struct node *head2 = NULL; // forbidden coordinates

/*
void printList(struct node **head) {
    struct node *ptr = *head;
    printf("\n[ ");

    while(ptr != NULL) {
        printf("(%d,%d) ",ptr->row_coor,ptr->column_coor);
        ptr = ptr->next;
    }

    printf(" ]");
}
 */

void print_map();
void get_coordinates();
void insert_coordinates();

int main() {
    print_map(row, column);
    get_coordinates(5);
   // printList(&head2);
   // printList(&head1);
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

void get_coordinates(int lenght) {
    printf("enter coordinates of %d block lenght ship:\n", lenght);
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
    if(fmax(first_row, end_row) > row || fmax(first_column, end_column) > column
    || fmin(first_row, end_row) < 1 || fmin(first_column, end_column) < 1){
        printf("your input was out of range ! :)\nTry Again...\n");
        get_coordinates(lenght);
    }

    else if(first_row == end_row && (int)(abs(first_column - end_column) + 1) == lenght ){

        i = (int)fminf((float)first_column,(float)end_column);
        insert_coordinates(first_row, i-1, &head2);

        for(; i <= (int)fmaxf((float)first_column,(float)end_column); i++){
            insert_coordinates(first_row, i, &head1);
            insert_coordinates(first_row+1, i, &head2);
            insert_coordinates(first_row-1, i, &head2);
        }
        insert_coordinates(first_row, i, &head2);
    }

    else if(first_column == end_column && (int)(abs(first_row - end_row) + 1) == lenght ){

        i = (int)fminf((float)first_row,(float)end_row);
        insert_coordinates(i-1, first_column, &head2);

        for(; i <= (int)fmaxf((float)first_row,(float)end_row); i++){
            insert_coordinates(i, first_column, &head1);
            insert_coordinates(i, first_column+1, &head2);
            insert_coordinates(i, first_column-1, &head2);
        }
        insert_coordinates(i, first_column, &head2);
    }

    else{
        printf("you entered invalid inputs! :)\nTry Again...\n");
        get_coordinates(lenght);
    }
}

void insert_coordinates( int inner_row,int inner_column, struct node **head){
    struct node *link = (struct node*) malloc(sizeof(struct node));

    link->row_coor = inner_row;
    link->column_coor = inner_column;

    link->next = *head;
    *head = link;
}

