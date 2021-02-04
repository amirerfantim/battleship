#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <stdbool.h>

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
int coor_spliter();
int check_available_coor();
struct node* find();

int main() {
   get_ship();
  // printList(&head2);
  // printList(&head1);
}

/*
int check_available_coor(int cte, int first, int end, int hor_or_vert){ // hor =1= horizontal & vert =2= vertical
    int i;

    if(hor_or_vert == 1) {
        for (i = first; i <= end; i++) {
            struct node *foundLink = find(cte, i , &head2);
            if(foundLink != NULL) {
                printf("%d %d %d %d\n", foundLink->row_coor, foundLink->column_coor, cte, i);
                return  -1;
            }
        }
    }
    else if(hor_or_vert == 2) {
        for (i = first; i <= end; i++) {
            if (find(i, cte, &head2) != NULL){
                return -1;
            }
        }
    }
    return 0;
}
*/
void get_ship(){
    get_coordinates(5, 1);
    system("cls");
    print_map(10,10,5);
    get_coordinates(3, 2);
    system("cls");
    print_map(10,10,8);
    get_coordinates(3, 3);
    system("cls");
    print_map(10,10,11);
        /*
    get_coordinates(2, 4);
    get_coordinates(2, 5);
    get_coordinates(2, 6);
    get_coordinates(1, 7);
    get_coordinates(1, 8);
    get_coordinates(1, 9);
    get_coordinates(1, 10);
     */


}

int coor_spliter(int n,int row_col, struct node **head) { // row =1= return row num & col =2= return column num
    struct node *ptr = *head;
    int result;

    if(row_col == 1) {
         result = ptr->row_coor;
    }
    if(row_col == 2) {
         result = ptr->column_coor;
    }

    int i=0;

    while(ptr != NULL) {
        if(i == n) {
            if(row_col == 1) {
                result = ptr->row_coor;
                break;
            }
            if(row_col == 2) {
                result = ptr->column_coor;
                break;
            }
        }
        ptr = ptr->next;
        i++;
    }

    return result;
}

void print_map(int inner_row, int inner_column, int length){
    int i1, i2, i3, col_counter = 1, j = length-1, splitted_row[length], splitted_col[length];
    for(i1 = 0; i1 < length; i1++){
        splitted_row[i1] = coor_spliter(i1, 1, &head1);
        splitted_col[i1] = coor_spliter(i1, 2, &head1);
    }


    printf("   ");

    for(i3 = 0; i3 < 4*inner_column; i3++) {
        if((i3 +2) % 4 == 0) {
            printf("%d", col_counter);
            col_counter++;
        }else{
            printf("-");
        }
    }

    printf("\n");
    char show_ship[row * column+1] ;
    for(i1 = 0; i1 <= row * column; i1++){
        show_ship[i1] = ' ';
    }

    int i4 =0;
    for (i1 = 0; i1 < row; i1++) {
        for (i2 = 0; i2 < column; i2++) {
            if (splitted_row[j] == i1 + 1 && splitted_col[j] == i2 + 1) {
                show_ship[i4] = 'S';
                j--;
                i1 = 0;
                i2 = 0;
                i4=0;
            }
            i4++;
        }
    }

    i4 = 0;
    for(i1 = 0; i1 < inner_row; i1++){
        printf("%3d", i1+1);
        for(i2 = 0; i2 < inner_column; i2++){
            printf("| %c ", show_ship[i4]);
            i4++;
        }

        printf("|\n   ");

        for(i3 = 0; i3 < 4*inner_column; i3++) {
            printf("-");
        }
        printf("-\n");
    }


}

void get_coordinates(int length, int ship_num) {
    printf("\nenter coordinates of %d block length ship:\n", length);
    int first_row, first_column, end_row, end_column;

    printf("enter row number of start point: ");
    scanf("%d", &first_row);
    printf("enter column number of start point: ");
    scanf("%d", &first_column);
    printf("enter row number of end point: ");
    scanf("%d", &end_row);
    printf("enter column number of end point: ");
    scanf("%d", &end_column);

    int i, min_row, max_row, min_column, max_column;
    min_row = (int)fminf( (float)first_row, (float)end_row);
    min_column = (int)fminf( (float)first_column, (float)end_column);
    max_row = (int)fmaxf( (float)first_row, (float)end_row);
    max_column = (int)fmaxf( (float)first_column, (float)end_column);

    if(max_row <= row && max_column <= column && min_row > 0 && min_column > 0) {
        if (first_row == end_row && ( max_column - min_column + 1) == length) {
        //    if(check_available_coor(first_row, min_column, max_column, 1) == 0) {
                i = min_column;
                insert_coordinates(first_row, i - 1, ship_num, &head2);

                for (; i <= max_column; i++) {
                    insert_coordinates(first_row, i, ship_num, &head1);
                    insert_coordinates(first_row + 1, i, ship_num, &head2);
                    insert_coordinates(first_row - 1, i, ship_num, &head2);
                }
                insert_coordinates(first_row, i, ship_num, &head2);
        //    }
        /*
            else{
                printf("\nYou cannot place a ship here...\nit has been taken :)\nTry Again\n\n");
                get_coordinates(length, ship_num);
            }
            */
        }

        else if (first_column == end_column && (max_row - min_row + 1) == length) {

         //   if(check_available_coor(first_column, min_row, max_row, 2) == 0) {
                i = min_row;
                insert_coordinates(i - 1, first_column, ship_num, &head2);

                for (; i <= max_row; i++) {
                    insert_coordinates(i, first_column, ship_num, &head1);
                    insert_coordinates(i, first_column + 1, ship_num, &head2);
                    insert_coordinates(i, first_column - 1, ship_num, &head2);
                }
                insert_coordinates(i, first_column, ship_num, &head2);
         /*   } else{
                printf("\nYou cannot place a ship here...\nit has been taken or next to another ship :)"
                       "\nTry Again\n\n");
                get_coordinates(length, ship_num);
            }
            */
        }
        else{
            printf("\nyou entered invalid inputs! :)\nTry Again...\n\n");
            get_coordinates(length,ship_num);
        }
    }

    else{
        printf("\nyou entered invalid inputs!! :)\nTry Again...\n\n");
        get_coordinates(length,ship_num);
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

/*
struct node* find(int inner_row,  int inner_column, struct node **head) {

    struct node* current = *head;

    if(*head == NULL) {
        return NULL;
    }

    while(current->row_coor != inner_row) {
            if (current->next == NULL) {
                return NULL;
            } else {
                current = current->next;
            }

        return current;
    }
}
 */

