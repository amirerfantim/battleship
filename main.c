#include <stdio.h>
void print_map();
int main() {
    int row, column;
    scanf("%d %d", &row, &column);
    print_map(row,column);
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
