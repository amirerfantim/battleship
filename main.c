#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct node {
    int row, column ;
    struct node *next;
};
struct node *head = NULL;

void print_map();
void get_coordinates();
void insert_coordinates();

int row, column;
int main() {
    scanf("%d %d", &row, &column);
    print_map(row, column);
    get_coordinates(5);
}

void print_map(int row, int column){
    int i1, i2, i3, col_counter = 1;
    printf("   ");

    for(i3 = 0; i3 < 4*column; i3++) {
        if((i3 +2) % 4 == 0) {
            printf("%d", col_counter);
            col_counter++;
        }else{
            printf("-");
        }
    }

    printf("-\n");

    for(i1 = 0; i1 < row; i1++){
        printf("%3d", i1+1);
        for(i2 = 0; i2 < column; i2++){
            printf("|   ");
        }

        printf("|\n   ");

        for(i3 = 0; i3 < 4*column; i3++) {
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
    else if(first_row == end_row && (int)(abs(first_column - end_column)) == lenght ){
        for(i = (int)fminf(first_column,end_column); i < (int)fmaxf(first_column,end_column); i++){
            insert_coordinates(first_row, i);
        }
    }
    else if(first_column == end_column && (int)(abs(first_row - end_row)) == lenght ){
        for(i = (int)fminf(first_row,end_row); i < (int)fmaxf(first_row,end_row); i++){
            insert_coordinates(i, first_column);
        }
    }
    else{
        printf("you entered invalid inputs! :)\nTry Again...\n");
        get_coordinates(lenght);
    }

}

void insert_coordinates( int row,int column){
    struct node *link = (struct node*) malloc(sizeof(struct node));

    link->row = row;
    link->column = column;

    link->next = head;
    head = link;
}