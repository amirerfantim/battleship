#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

#define row 10
#define column 10


struct users {
    char username[20];
    int points;
    int ID;
    struct users *next;
};

struct node {
    int row_coor, column_coor,ship_length, ship_num ; // ship_num equal to hit number in atk list's.
    struct node *next;
};

struct users *start1;
struct users *playing_users;

struct node *head1_p1 = NULL; // ship coordinates
struct node *head2_p1 = NULL; // forbidden coordinates
struct node *head_atkp1 = NULL; // coordinates that player1 attacked
struct node *head_desp1 = NULL; // ship coordinates that player  1 destroyed
struct node *water_p1 = NULL; // water around destroyed ship

struct node *head1_p2 = NULL; // ship coordinates
struct node *head2_p2 = NULL; // forbidden coordinates
struct node *head_atkp2 = NULL; // coordinates that player2 attacked
struct node *head_desp2 = NULL; // ship coordinates that player 2 destroyed
struct node *water_p2 = NULL; // water around destroyed ship


void printList(struct node **head) {
    struct node *ptr = *head;
    printf("\n[ ");
    while (ptr != NULL) {
        printf("(%d,%d,[%d] {%d})\n ", ptr->row_coor, ptr->column_coor, ptr->ship_num, ptr->ship_length);
        ptr = ptr->next;
    }
    printf(" ]");
}

void main_menu();
void show_main_menu();
void players_menu();
void show_player_menu();
void show_choose_user();
void show_ships_menu();
void create_newuser();
int get_command();
void print_map();
void print_atk_map();
void countdown();
void get_coordinates();
void attack_coordinates();
void insert_coordinates();
void random_coordinates();
void get_random_ship();
void get_ship();
int destroyed_ship();
int coor_spliter();
int check_available_coor();
void WriteListToFile();
void WriteUsersToFile();
int length();
int counter_linked();
int counter_shipnum();
void find_add();
void find_users();
void cleanup_list();
void cleanup_all();
void two_player_game();
void play_with_bot();
void what_player_choose();
void save_game();
void load_game();
void insert_users();
void sort();
void print_users();
int length_users();
struct node *ReadNextFromFile();
struct node *ReadListIn();
struct users *ReadNextUser();
struct users *ReadUsersIn();
struct node *find();
struct node* delete_1var();
struct node* delete_2var();
bool search_linked();


int main() {
    srand(time(0));
    system("cls");
    ReadUsersIn(&start1);
    //main_menu();
    //load_game();
    print_atk_map(&head_atkp1, &head1_p2, &head_desp2, &water_p2);
    print_atk_map(&head_atkp2, &head1_p1, &head_desp1, &water_p1);


/*
    main_menu();
    print_users(&playing_users);
    WriteUsersToFile(start1);
*/
    /*
    sort(&start1);
    print_users(&start1);


    create_newuser();
    create_newuser();
    create_newuser();

    print_users(&start1);
    WriteUsersToFile(start1);
*/
    //get_random_ship(&head1_p1, &head2_p1);
    //load_game();
    //two_player_game();
    //play_with_bot();
    //WriteListToFile(&head1_p1);
    //ReadListIn(&head1_p1);
    //print_map(10, &head1_p1);
    //printList(&head1_p1);
    //save_game();
    //cleanup_all();
    //main_menu();
    //cleanup_list(&head2_p1);
    //cleanup_list(&head2_p2);
}

void save_game(){
    char user[20], temp[20];
    printf("enter your file name [maximum of 10 character]: ");
    scanf("%s", user);
    printf("\n");

    strcpy(temp, user);
    WriteListToFile(head1_p1, user, "ship", "p1");
    strcpy(user, temp);
    WriteListToFile(head_atkp1, user, "atk", "p1");
    strcpy(user, temp);
    WriteListToFile(head_desp1, user, "des", "p1");
    strcpy(user, temp);
    WriteListToFile(head2_p1, user, "awat", "p1");
    strcpy(user, temp);
    WriteListToFile(water_p1, user, "pwat", "p1");
    strcpy(user, temp);

    WriteListToFile(head1_p2, user, "ship", "p2");
    strcpy(user, temp);
    WriteListToFile(head_atkp2, user, "atk", "p2");
    strcpy(user, temp);
    WriteListToFile(head_desp2, user, "des", "p2");
    strcpy(user, temp);
    WriteListToFile(head2_p2, user, "awat", "p2");
    strcpy(user, temp);
    WriteListToFile(water_p2, user, "pwat", "p2");
    strcpy(user, temp);

}

void load_game(){
    char user[20], temp[20];
    printf("enter your file name [maximum of 10 character]: ");
    scanf("%s", user);
    printf("\n");

    strcpy(temp, user);
    ReadListIn(&head1_p1, user, "ship", "p1");
    strcpy(user, temp);
    ReadListIn(&head_atkp1, user, "atk", "p1");
    strcpy(user, temp);
    ReadListIn(&head_desp1, user, "des", "p1");
    strcpy(user, temp);
    ReadListIn(&head2_p1, user, "awat", "p1");
    strcpy(user, temp);
    ReadListIn(&water_p1, user, "pwat", "p1");
    strcpy(user, temp);

    ReadListIn(&head1_p2, user, "ship", "p2");
    strcpy(user, temp);
    ReadListIn(&head_atkp2, user, "atk", "p2");
    strcpy(user, temp);
    ReadListIn(&head_desp2, user, "des", "p2");
    strcpy(user, temp);
    ReadListIn(&head2_p2, user, "awat", "p2");
    strcpy(user, temp);
    ReadListIn(&water_p2, user, "pwat", "p2");
    strcpy(user, temp);
}

void two_player_game(){
    //get_ship(&head1_p1, &head2_p1);
    //get_ship(&head1_p2, &head2_p2);
    cleanup_all();

    while(head1_p1 != NULL && head1_p2 != NULL) {
        print_atk_map(&head_atkp1, &head1_p2, &head_desp2, &water_p2);

        printf("\nPlayer 1 Turn:\n1. Attack\t2. Save\t3. Exit\n");
        what_player_choose(1);

        /*
        attack_coordinates(&head_atkp1, &head1_p2, &head_desp2, &water_p2, &head2_p2, 0);
        system("cls");
        print_atk_map(&head_atkp1, &head1_p2, &head_desp2, &water_p2);
        countdown(2);
        system("cls");
         */

        if(head1_p2 == NULL){
            break;
        }

        print_atk_map(&head_atkp2, &head1_p1, &head_desp1, &water_p1);
        printf("\nPlayer 1 Turn:\n1. Attack\t2. Save\t3. Exit");
        what_player_choose(2);
        /*
        attack_coordinates(&head_atkp2, &head1_p1, &head_desp1, &water_p1, &head2_p1, 0);
        system("cls");
        print_atk_map(&head_atkp2, &head1_p1, &head_desp1, &water_p1);
        countdown(2);
        system("cls");
         */
    }

    if(head1_p1 == NULL){
        print_atk_map(&head_atkp2, &head1_p1, &head_desp1, &water_p1);
        printf("\nPlayer 2 WON!\nCongratulations!\n");
    }

    if(head1_p2 == NULL){
        print_atk_map(&head_atkp1, &head1_p2, &head_desp2, &water_p2);
        printf("\nPlayer 1 WON!\nCongratulations!\n");
    }

}

void play_with_bot(){
    get_ship(&head1_p1, &head2_p1);
    get_random_ship(&head1_p2, &head2_p2);
    cleanup_all();

    while(head1_p1 != NULL && head1_p2 != NULL) {
        print_atk_map(&head_atkp1, &head1_p2, &head_desp2, &water_p2);
        printf("\nPlayer 1 Turn:\n");
        attack_coordinates(&head_atkp1, &head1_p2, &head_desp2, &water_p2, &head2_p2, 0);
        system("cls");
        print_atk_map(&head_atkp1, &head1_p2, &head_desp2, &water_p2);
        countdown(2);
        system("cls");

        if(head1_p2 == NULL){
            break;
        }

        print_atk_map(&head_atkp2, &head1_p1, &head_desp1, &water_p1);
        printf("\nPlayer 2 Turn:\n");
        attack_coordinates(&head_atkp2, &head1_p1, &head_desp1, &water_p1, &head2_p1, 1);
        system("cls");
        print_atk_map(&head_atkp2, &head1_p1, &head_desp1, &water_p1);
        countdown(2);
        system("cls");
    }

    if(head1_p1 == NULL){
        print_atk_map(&head_atkp2, &head1_p1, &head_desp1, &water_p1);
        printf("\nPlayer 2 WON!\nCongratulations!\n");
    }

    if(head1_p2 == NULL){
        print_atk_map(&head_atkp1, &head1_p2, &head_desp2, &water_p2);
        printf("\nPlayer 1 WON!\nCongratulations!\n");
    }

}
// one or two means player1  or player2
void what_player_choose(int one_or_two){
    int command;
    command = get_command();
    if(command == 1 && one_or_two == 1){
        attack_coordinates(&head_atkp1, &head1_p2, &head_desp2, &water_p2, &head2_p2, 0);
        system("cls");
        print_atk_map(&head_atkp1, &head1_p2, &head_desp2, &water_p2);
        countdown(2);
        system("cls");
    }

    else if(command == 1 && one_or_two == 1){
        attack_coordinates(&head_atkp2, &head1_p1, &head_desp1, &water_p1, &head2_p1, 0);
        system("cls");
        print_atk_map(&head_atkp2, &head1_p1, &head_desp1, &water_p1);
        countdown(2);
        system("cls");
    }

    else if(command == 2){
        save_game();
    }

    else if(command == 3){
        printf("\n\n    GOOD BYE :)\n");
        exit(0);
    }else{
        printf("\nWrong input! TryAgian...\n");
        what_player_choose(one_or_two);
    }
}

void main_menu(){
    int command1;
    show_main_menu();
    command1 = get_command();

    if(command1 == 1){
        system("cls");
        players_menu("player 1",&head1_p1, &head2_p1);
        system("cls");
        players_menu("player 2",&head1_p2, &head2_p2);
        two_player_game();
    }else if(command1 == 2){
        system("cls");
        play_with_bot();
    }else if (command1 == 3){
        system("cls");
        load_game();
    }else if(command1 == 4){
        system("cls");
        sort(&start1);
        print_users(&start1);
    }else if (command1 == 5){
        system("cls");
        printf("\n\n    GOOD BYE :)\n");
        exit(0);
    }else{
        system("cls");
        main_menu();
    }

}

void show_main_menu(){
    printf("\n"
           "1. Play with a Friend\n"
           "2. Play with bot\n"
           "3. Load a Game\n"
           "4. Score Board\n"
           "5. Exit\n");
}

int get_command(){
    int command;
    printf("enter your command: ");
    scanf("%d", &command);
    return  command;
}

void create_newuser(){
    char username[20];
    printf("enter a username [maximum of 15 characters]: ");
    scanf("%s", username);
    printf("Congratulations %s!\n", username);
    int id = length_users(&start1) + 1;
    insert_users(username, 0, id, &start1);
}

void print_users(struct users **head) {
    struct users *ptr = *head;
    printf("\n\n");
    int i = 1;
    printf(" Row   Username             Points\n\n");
    while (ptr != NULL) {
        printf("%3d.   %-20s %d\n", i, ptr->username, ptr->points);
        ptr = ptr->next;
        i++;
    }
}

void players_menu(char player[],struct node** ships,struct node **water){
    printf("\n%s:\n", player);
    int command2, command3, command4;

    system("cls");

    show_choose_user();
    command3 = get_command();

    if(command3 == 1){
        system("cls");
        int user_row, id, users_leng;

        print_users(&start1);
        users_leng = length_users(&start1);

        printf("\nChoose an user (enter row number  to choose): ");
        scanf("%d", &user_row);
        if(user_row > users_leng){
            system("cls");
            printf("WRONG INPUT!\n");
            players_menu(player,ships, water);
        }
        else{
            system("cls");
            id = users_leng - (user_row - 1);
            find_users(id, 1, &start1, &playing_users);
        }
    }
    else if(command3 == 2){
        system("cls");
        create_newuser();
    }
    else{
        system("cls");
        printf("WRONG INPUT!\n");
        main_menu();
    }

    system("cls");
    show_ships_menu();
    command4 = get_command();

    if(command4 == 1){
        system("cls");
        get_random_ship(ships,water);

    }else if(command4 == 2){
        system("cls");
        get_ship(ships, water);

    }else {
        system("cls");
        printf("WRONG INPUT!\n");
        main_menu();
    }

}

void show_player_menu(){
    printf("1. Choose User\n"
           "2. Put Ships\n");
}

void show_choose_user(){
    printf("1. Choose from available users\n"
           "2. New user\n");
}

void show_ships_menu(){
    printf("Put ships:\n1. Auto\n2. Manual\n");
}

int check_available_coor(int cte, int first, int end, int hor_or_vert, struct node **head2){ // hor =1= horizontal & vert =2= vertical
    int i;
    bool result;
    if(hor_or_vert == 1) {
        for (i = first; i <= end; i++) {
            result = search_linked(head2, cte, i);
            if(result == true) {
                return  -1;
            }
        }
    }
    else if(hor_or_vert == 2) {
        for (i = first; i <= end; i++) {
            result = search_linked(head2, i, cte);
            if (result == true){
                return -1;
            }
        }
    }
    return 0;
}

void countdown(int duration){
    for(int i = duration; i>0; i--) {
        printf("This map will be hidden after %d second(s)...\n", i);
        sleep(1);
    }
}

void get_ship(struct node **head1, struct node **head2){
    get_coordinates(4, 1, head1, head2);
    system("cls");
    print_map(4, head1);

    get_coordinates(3, 2, head1, head2);
    system("cls");
    print_map(7, head1);

    get_coordinates(3, 3, head1, head2);
    system("cls");
    print_map(10, head1);
/*
    get_coordinates(2, 4, head1, head2);
    system("cls");
    print_map(13, head1);

    get_coordinates(2, 5, head1, head2);
    system("cls");
    print_map(15, head1);

    get_coordinates(2, 6, head1, head2);
    system("cls");
    print_map(17, head1);
    */

    //WriteListToFile(head1_p1, 1, 1);

    countdown(5);
    system("cls");

/*
    get_coordinates_p1(1, 7);
    get_coordinates_p1(1, 8);
    get_coordinates_p1(1, 9);
    get_coordinates_p1(1, 10);
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

void print_map(int length, struct node **head1){

    int i1, i2, i3, col_counter = 1, j , splitted_row[length], splitted_col[length];

    for(i1 = 0; i1 < length; i1++){
        splitted_row[i1] = coor_spliter(i1, 1, head1);
        splitted_col[i1] = coor_spliter(i1, 2, head1);
    }

    fflush(stdin);

    printf("   ");

    for(i3 = 0; i3 < 4*column; i3++) {
        if((i3 +2) % 4 == 0) {
            printf("%d", col_counter);
            col_counter++;
        }else{
            printf("-");
        }
    }

    printf("\n");
    char show_ship[row+1][column+1]  ;
    for(i1 = 0; i1 <= row ; i1++){
        for(i2 = 0; i2 <= column; i2++) {
            show_ship[i1][i2] = ' ';
        }
    }

    int i4 =0;
    j =0;
    for (i1 = 0; i1 < row; i1++) {
        for (i2 = 0; i2 < column; i2++) {
            if(splitted_row[j] == 1 && splitted_col[j] == 1){
                show_ship[0][0] = 'S';
                j++;
            }
            else if(splitted_row[j] == i1 + 1 && splitted_col[j] == i2 + 1) {
                show_ship[i1][i2] = 'S';
                j++;
                i1 = 0;
                i2 = 0;
                //i4=0;
            }
            // i4++;
        }
    }

    i4 = 0;
    for(i1 = 0; i1 < row; i1++){
        printf("%3d", i1+1);
        for(i2 = 0; i2 < column; i2++){
            printf("| %c ", show_ship[i1][i2]);
            //i4++;
        }

        printf("|\n   ");

        for(i3 = 0; i3 < 4*column; i3++) {
            printf("-");
        }
        printf("-\n");
    }
}

void print_atk_map(struct node **attack, struct node **ships, struct node **destroy, struct node **water){

    int i1, i2, i3, col_counter = 1,inner_length = length(attack), j1 ;
    int splitted_row[2*inner_length], splitted_col[2*inner_length];
    int des_length = length(destroy), des_row[2*des_length], des_col[2*des_length];
    int water_length = length(water), wat_row[2*water_length], wat_col[2*water_length];

    printf("   ");

    for(i1 = 0; i1 < inner_length; i1++){
        splitted_row[i1] = coor_spliter(i1, 1, attack);
        splitted_col[i1] = coor_spliter(i1, 2, attack);
    }

    for(i1 = 0; i1 < des_length; i1++){
        des_row[i1] = coor_spliter(i1, 1, destroy);
        des_col[i1] = coor_spliter(i1, 2, destroy);
    }

    for(i1 = 0; i1 < water_length; i1++){
        wat_row[i1] = coor_spliter(i1, 1, water);
        wat_col[i1] = coor_spliter(i1, 2, water);
    }


    for(i3 = 0; i3 < 4*column; i3++) {
        if((i3 +2) % 4 == 0) {
            printf("%d", col_counter);
            col_counter++;
        }else{
            printf("-");
        }
    }



    printf("\n");
    int hit_spots[2*row][2*column] ;
    for(i1 = 0; i1 < row ; i1++){
        for(i2 = 0; i2 < column; i2++) {
            hit_spots[i1][i2] = 0;
        }
    }

    int i4 =0, j2 = 0;
    j1 =0;

    bool hit_or_not;
    if(inner_length > 0) {
        for (i1 = 0; i1 < row; i1++) {
            for (i2 = 0; i2 < column; i2++) {
                if (j1 < inner_length) {
                    if (splitted_row[j1] == 1 && splitted_col[j1] == 1) {
                        hit_or_not = search_linked(ships, 1, 1);
                        if (hit_or_not == true) {
                            hit_spots[0][0] = 2;
                        }
                        if (hit_or_not == false) {
                            hit_spots[0][0] = 1;
                        }

                        j1++;
                    }
                    if (splitted_row[j1] == i1 + 1 && splitted_col[j1] == i2 + 1) {
                        hit_or_not = search_linked(ships, i1 + 1, i2 + 1);
                        if (hit_or_not == true) {
                            hit_spots[i1][i2] = 2;
                        }
                        if (hit_or_not == false) {
                            hit_spots[i1][i2] = 1;
                        }
                        j1++;
                        i1 = 0;
                        i2 = 0;
                        // i4 = 0;
                    }
                }
            }
            // i4++;
        }
    }


    j2 = 0;
    if(water_length > 0) {
        for (i1 = 0; i1 < row; i1++) {
            for (i2 = 0; i2 < column; i2++) {
                if (j2 < water_length) {
                    if (wat_row[j2] == 1 && wat_col[j2] == 1) {
                        hit_spots[0][0] = 1;
                        j2++;
                    }
                    if (wat_row[j2] == i1 + 1 && wat_col[j2] == i2 + 1) {
                        hit_spots[i1][i2] = 1;
                        j2++;
                        i1 = 0;
                        i2 = 0;
                    }
                }
            }
        }
    }


    j2 = 0;
    /*
    for(i1 = 0; i1 < des_length; i1++){
        printf("\n%d %d\n", des_row[i1], des_col[i1]);
    }
     */
    if(des_length > 0) {
        for (i1 = 0; i1 < row; i1++) {
            for (i2 = 0; i2 < column; i2++) {
                if (j2 < des_length) {
                    if (des_row[j2] == 1 && des_col[j2] == 1) {
                        hit_spots[0][0] = 3;
                        j2++;
                    }
                    if (des_row[j2] == i1 + 1 && des_col[j2] == i2 + 1) {
                        hit_spots[i1][i2] = 3;
                        j2++;
                        i1 = 0;
                        i2 = 0;
                    }
                }
            }
        }
    }
    /*
    for(i1 = 0; i1 < des_length; i1++){
        printf("\n%d %d", des_row[i1],des_col[i1]);
    }
    printf("\n");
     */

    i4 = 0;
    for(i1 = 0; i1 < row; i1++){
        printf("%3d", i1+1);
        for(i2 = 0; i2 < column; i2++){
            if(hit_spots[i1][i2] == 1){
                printf("| W ");
            }
            else if(hit_spots[i1][i2] == 2){
                printf("| E ");
            }
            else if(hit_spots[i1][i2] == 3){
                printf("| C ");
            }
            else{
                printf("|   ");
            }

        }

        printf("|\n   ");

        for(i3 = 0; i3 < 4*column; i3++) {
            printf("-");
        }
        printf("-\n");

    }
/*
    for(int loop1 = 0; loop1 < row; loop1++){
        for(int loop2 = 0; loop2 < column; loop2++ ) {
            printf("%d", hit_spots[loop1][loop2]);
        }
    }
    printf("\n");
    */

}

void get_coordinates(int length, int ship_num, struct node **head1, struct node **head2) {
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
            if(check_available_coor(first_row, min_column, max_column, 1, head2) == 0 &&
               check_available_coor(first_row, min_column, max_column, 1, head1) == 0 ) {
                i = min_column;
                insert_coordinates(first_row, i - 1, ship_num, length, head2);
                insert_coordinates(first_row-1, i - 1, ship_num, length, head2);
                insert_coordinates(first_row+1, i - 1, ship_num, length, head2);

                for (; i <= max_column; i++) {
                    insert_coordinates(first_row, i, ship_num, length, head1);
                    insert_coordinates(first_row + 1, i, ship_num, length, head2);
                    insert_coordinates(first_row - 1, i, ship_num, length, head2);
                }
                insert_coordinates(first_row, i, ship_num, length, head2);
                insert_coordinates(first_row+1, i, ship_num, length, head2);
                insert_coordinates(first_row-1, i, ship_num, length, head2);
            }
            else{
                printf("\nYou cannot place a ship here...\nTry Again\n\n");
                get_coordinates(length, ship_num, head1, head2);
            }

        }

        else if (first_column == end_column && (max_row - min_row + 1) == length) {

            if(check_available_coor(first_column, min_row, max_row, 2, head2) == 0 &&
               check_available_coor(first_column, min_row, max_row, 2, head1) == 0  ) {
                i = min_row;
                insert_coordinates(i - 1, first_column, ship_num,length, head2);
                insert_coordinates(i - 1, first_column+1, ship_num,length, head2);
                insert_coordinates(i - 1, first_column-1, ship_num,length, head2);

                for (; i <= max_row; i++) {
                    insert_coordinates(i, first_column, ship_num, length, head1);
                    insert_coordinates(i, first_column + 1, ship_num, length, head2);
                    insert_coordinates(i, first_column - 1, ship_num, length, head2);
                }
                insert_coordinates(i, first_column, ship_num, length, head2);
                insert_coordinates(i, first_column+1, ship_num, length, head2);
                insert_coordinates(i, first_column-1, ship_num, length, head2);
            }

            else {
                printf("\nYou cannot place a ship here...\nit has been taken or next to another ship :)"
                       "\nTry Again\n\n");
                get_coordinates(length, ship_num, head1, head2);
            }

        }
        else{
            printf("\nyou entered invalid inputs! :)\nTry Again...\n\n");
            get_coordinates(length,ship_num, head1, head2);
        }
    }

    else{
        printf("\nyou entered invalid inputs!! :)\nTry Again...\n\n");
        get_coordinates(length,ship_num, head1, head2);
    }
}

void random_coordinates(int length, int ship_num, struct node **head1, struct node **head2) {
    int first_row, first_column, end_row, end_column, hor_or_vert, i;

    hor_or_vert = rand() % 2;
    //hor =0= horizontal,  vert =1= vertical
    if (hor_or_vert == 0) {
        first_row = end_row = (rand() % row) + 1;
        first_column = (rand() % (column - length + 1)) + 1;
        end_column = first_column + length - 1;
    }
    if (hor_or_vert == 1) {
        first_column = end_column = (rand() % column) + 1;
        first_row = (rand() % (row - length + 1)) + 1;
        end_row = first_row + length - 1;
    }
    //printf("\n[%d] %d %d | %d %d \n", hor_or_vert, first_row, first_column, end_row, end_column );
    if (first_row == end_row) {
        if (check_available_coor(first_row, first_column, end_column, 1, head2) == 0 &&
            check_available_coor(first_row, first_column, end_column, 1, head1) == 0) {
            i = first_column;
            insert_coordinates(first_row, i - 1, ship_num, length, head2);
            insert_coordinates(first_row - 1, i - 1, ship_num, length, head2);
            insert_coordinates(first_row + 1, i - 1, ship_num, length, head2);
            for (; i <= end_column; i++) {
                insert_coordinates(first_row, i, ship_num, length, head1);
                insert_coordinates(first_row + 1, i, ship_num, length, head2);
                insert_coordinates(first_row - 1, i, ship_num, length, head2);
            }
            insert_coordinates(first_row, i, ship_num, length, head2);
            insert_coordinates(first_row + 1, i, ship_num, length, head2);
            insert_coordinates(first_row - 1, i, ship_num, length, head2);
        } else {
            random_coordinates(length, ship_num, head1, head2);
        }

    } else if (first_column == end_column) {

        if (check_available_coor(first_column, first_row, end_row, 2, head2) == 0 &&
            check_available_coor(first_column, first_row, end_row, 2, head1) == 0) {
            i = first_row;
            insert_coordinates(i - 1, first_column, ship_num, length, head2);
            insert_coordinates(i - 1, first_column + 1, ship_num, length, head2);
            insert_coordinates(i - 1, first_column - 1, ship_num, length, head2);

            for (; i <= end_row; i++) {
                insert_coordinates(i, first_column, ship_num, length, head1);
                insert_coordinates(i, first_column + 1, ship_num, length, head2);
                insert_coordinates(i, first_column - 1, ship_num, length, head2);
            }
            insert_coordinates(i, first_column, ship_num, length, head2);
            insert_coordinates(i, first_column + 1, ship_num, length, head2);
            insert_coordinates(i, first_column - 1, ship_num, length, head2);
        } else {

            random_coordinates(length, ship_num, head1, head2);
        }

    } else {

        random_coordinates(length, ship_num, head1, head2);
    }
}

void get_random_ship(struct node **head1, struct node **head2){
    random_coordinates(4, 1, head1, head2);
    random_coordinates(3, 2, head1, head2);
    random_coordinates(3, 3, head1, head2);
    /*
    random_coordinates(2, 4, head1, head2);
    random_coordinates(2, 5, head1, head2);
    random_coordinates(2, 6, head1, head2);
    random_coordinates(1, 7, head1, head2);
    random_coordinates(1, 8, head1, head2);
    random_coordinates(1, 9, head1, head2);
    random_coordinates(1, 10, head1, head2);
     */

    system("cls");
}

// if head==p1 then ships==p2
// if rand_or_not == 1 ->random if == 0 ->manual
void attack_coordinates(struct node **attack, struct node **ships2, struct node **destroy,
        struct node** water, struct node **all_water, int rand_or_not) {
    printf("\nenter coordinate you wanna hit:\n");
    int inner_row, inner_column;

    if(rand_or_not == 0) {
        printf("enter row number: ");
        scanf("%d", &inner_row);
        printf("enter column number: ");
        scanf("%d", &inner_column);
        fflush(stdin);

    }else{
        inner_row = (rand() % row) + 1;
        inner_column = (rand() % column) +1;
    }

    int hit_or_not = counter_linked(ships2, inner_row, inner_column);
    int ship_num = 0, ship_length = 0;
    struct node* search_result = find(inner_row, inner_column, ships2);

    if(search_result != NULL){
        ship_num = search_result->ship_num;
        ship_length = search_result->ship_length;
    }

    if(inner_row <= 10 && inner_row > 0 && inner_column <= 10 && inner_column > 0) {
        if(search_linked(attack, inner_row, inner_column) == false) {
            insert_coordinates(inner_row, inner_column, ship_num, ship_length, attack);
        }
        else{
            printf("\nYou've already hit this coordinate...\nTry Again\n\n");
            attack_coordinates(attack, ships2, destroy, water, all_water, rand_or_not);
        }
    }


    else{
        printf("\nyou entered invalid inputs!! :)\nTry Again...\n\n");
        attack_coordinates(attack, ships2, destroy, water, all_water, rand_or_not);
    }

    int check_destroyed = 0;
    if(hit_or_not != 0){
        check_destroyed = destroyed_ship(ship_num, ship_length, attack);
    }
    if(check_destroyed == 1){
        find_add(ship_num, attack, ships2, destroy);
        find_add(ship_num, all_water, all_water, water );
    }
}

void insert_coordinates( int inner_row,int inner_column,int ship_num,int ship_length, struct node **head){
    struct node *link = (struct node*) malloc(sizeof(struct node));

    link->row_coor = inner_row;
    link->column_coor = inner_column;
    link->ship_num = ship_num;
    link->ship_length = ship_length;

    link->next = *head;
    *head = link;
}

void insert_users( char name[], int points,int id, struct users **head){
    struct users *link = (struct users*) malloc(sizeof(struct users));

    strcpy(link->username, name);
    link->points = points;
    link->ID = id;

    link->next = *head;
    *head = link;
}

int destroyed_ship(int ship_num,int ship_length,  struct node** attack){
    int counter = 0;
    counter = counter_shipnum(attack, ship_num);

    if(counter == ship_length){
        return 1;
    }
    return 0;
}

bool search_linked(struct node** head1, int inner_row, int inner_col){
    struct node* current = *head1;
    while (current != NULL)
    {
        if ((current->row_coor == inner_row) && (current->column_coor == inner_col))
            return true;
        current = current->next;
    }
    return false;
}

int counter_linked(struct node** head1, int inner_row, int inner_col){
    int counter = 0;
    struct node* current = *head1;
    while (current != NULL)
    {
        if ((current->row_coor == inner_row) && (current->column_coor == inner_col)) {
            counter++;
        }
        current = current->next;
    }
    return counter;
}

int counter_shipnum(struct node** head1, int key){
    int counter = 0;
    struct node* current = *head1;
    while (current != NULL)
    {
        if (current->ship_num == key) {
            counter++;
        }
        current = current->next;
    }
    return counter;
}

void WriteListToFile(struct node* start, char filename[], char code[], char player_num[]) {
    FILE *pFile;
    strcat(filename, code);
    strcat(filename, player_num);
    strcat(filename, ".bin");
    pFile = fopen(filename, "wb");

    if(pFile != NULL) {
        struct node *currentCar = start;

        struct node *holdNext = NULL;
        struct node *holdPrevious = NULL;

        while(currentCar != NULL) {
            holdNext = currentCar->next;

            currentCar->next = NULL;

            fseek(pFile, 0, SEEK_END);
            fwrite(currentCar, sizeof(struct node), 1, pFile);

            currentCar->next = holdNext;

            holdNext = NULL;
            holdPrevious = NULL;

            currentCar = currentCar->next;
        }
        fclose(pFile);
        pFile = NULL;
        printf("* saved *");

    } else {
        printf("FILE OPEN ERROR\n");
    }

}

void WriteUsersToFile(struct users* start) {
    FILE *pFile;
    pFile = fopen("users101.bin", "wb");

    if(pFile != NULL) {
        struct users *currentCar = start;

        struct users *holdNext = NULL;
        struct users *holdPrevious = NULL;

        while(currentCar != NULL) {
            holdNext = currentCar->next;

            currentCar->next = NULL;

            fseek(pFile, 0, SEEK_END);
            fwrite(currentCar, sizeof(struct users), 1, pFile);

            currentCar->next = holdNext;

            holdNext = NULL;
            holdPrevious = NULL;

            currentCar = currentCar->next;
        }
        fclose(pFile);
        pFile = NULL;
        printf("* saved *");

    } else {
        printf("FILE OPEN ERROR\n");
    }

}

struct node *ReadNextFromFile(struct node *start, FILE *pFile) {
    size_t returnValue;
    if(start == NULL) {
        start = malloc(sizeof(struct node));
        returnValue = fread(start, sizeof(struct node), 1, pFile);\
        start->next = NULL;
    } else {
        struct node *indexCar = start;
        struct node *newCar = malloc(sizeof(struct node));
        while(indexCar->next != NULL) {
            indexCar = indexCar->next;
        }
        returnValue = fread(newCar, sizeof(struct node), 1, pFile);
        indexCar->next = newCar;
        newCar->next = NULL;
    }
    return start;
}

struct node *ReadListIn(struct node **start, char filename[], char code[], char player_num[]) {

    FILE *pFile;
    strcat(filename, code);
    strcat(filename, player_num);
    strcat(filename, ".bin");
    pFile = fopen(filename, "rb");
    if(pFile != NULL) {

        //CleanUp(*start);
        *start = NULL;

        fseek(pFile, 0, SEEK_END);
        long fileSize = ftell(pFile);
        rewind(pFile);

        int numEntries = (int)(fileSize / (sizeof(struct node)));
        printf("numEntries:%d\n",numEntries);

        int loop ;
        for(loop = 0; loop < numEntries; ++loop) {
            fseek(pFile, (sizeof(struct node) * loop), SEEK_SET);
            *start = ReadNextFromFile(*start, pFile);
        }
    }  else {
        printf("FILE OPEN ERROR FOR READ\n");
    }

    return *start;

}

struct users *ReadNextUser(struct users *start, FILE *pFile) {
    size_t returnValue;
    if(start == NULL) {
        start = malloc(sizeof(struct users));
        returnValue = fread(start, sizeof(struct users), 1, pFile);\
        start->next = NULL;
    } else {
        struct users *indexCar = start;
        struct users *newCar = malloc(sizeof(struct users));
        while(indexCar->next != NULL) {
            indexCar = indexCar->next;
        }
        returnValue = fread(newCar, sizeof(struct users), 1, pFile);
        indexCar->next = newCar;
        newCar->next = NULL;
    }
    return start;
}

struct users *ReadUsersIn(struct users **start) {

    FILE *pFile;
    pFile = fopen("users101.bin", "rb");
    if(pFile != NULL) {

        //CleanUp(*start);
        *start = NULL;

        fseek(pFile, 0, SEEK_END);
        long fileSize = ftell(pFile);
        rewind(pFile);

        int numEntries = (int)(fileSize / (sizeof(struct users)));
        printf("numEntries:%d\n",numEntries);

        int loop ;
        for(loop = 0; loop < numEntries; ++loop) {
            fseek(pFile, (sizeof(struct users) * loop), SEEK_SET);
            *start = ReadNextUser(*start, pFile);
        }
    }  else {
        printf("FILE OPEN ERROR FOR READ\n");
    }

    return *start;

}

int length(struct  node **head) {
    int length = 0;
    struct node *current;
    if(*head != NULL) {
        for (current = *head; current != NULL; current = current->next) {
            length++;
        }
    }

    return length;
}

int length_users(struct  users **head) {
    int length = 0;
    struct users *current;
    if(*head != NULL) {
        for (current = *head; current != NULL; current = current->next) {
            length++;
        }
    }

    return length;
}

struct node* find(int inner_row,int inner_col, struct node** head1) {

    struct node* current = *head1;

    if(*head1 == NULL) {
        return NULL;
    }

    while(current != NULL) {
        if(current->row_coor == inner_row && current->column_coor == inner_col){
            break;
        }
        if(current->next == NULL) {
            return NULL;
        } else {
            current = current->next;
        }
    }

    return current;
}

void find_add(int key, struct node** head1,struct node** del, struct node** add) {

    struct node* current = *head1;

    while(current != NULL) {
        if(current->ship_num == key){
            insert_coordinates(current->row_coor,current->column_coor, current->ship_num, current->ship_length, add);
            delete_1var(key, del);
        }
        current = current->next;
    }


}

// if one_or_two =1= player1 | =2= player2   key is ID
void find_users(int key,int one_or_two ,struct users** head1, struct users** add) {

    struct users* current = *head1;

    while(current != NULL) {
        if(current->ID == key){
            insert_users(current->username, current->points, one_or_two, add);
        }
        current = current->next;
    }


}

void cleanup_list(struct node **head) {
    struct node *ptr = *head;
    while (ptr != NULL) {
        if(ptr->row_coor > 10 || ptr->row_coor < 1 || ptr->column_coor > 10 || ptr->column_coor < 1){
            delete_2var(ptr->row_coor, ptr->column_coor, head);
        }
        ptr = ptr->next;
    }
}

void cleanup_all() {
    cleanup_list(&head2_p1);
    cleanup_list(&head2_p2);
}

struct node* delete_1var(int key, struct node** head1) {

    struct node* current = *head1;
    struct node* previous = NULL;

    if(*head1 == NULL) {
        return NULL;
    }

    while(current->ship_num != key) {

        if(current->next == NULL) {
            return NULL;
        } else {
            previous = current;
            current = current->next;
        }
    }

    if(current == *head1) {
        *head1 = (*head1)->next;
    } else {
        previous->next = current->next;
    }

    return current;
}

struct node* delete_2var(int key,int data, struct node** head1) {

    struct node* current = *head1;
    struct node* previous = NULL;

    if(*head1 == NULL) {
        return NULL;
    }

    while(current->row_coor != key || current->column_coor != data) {

        if(current->next == NULL) {
            return NULL;
        } else {
            previous = current;
            current = current->next;
        }
    }

    if(current == *head1) {
        *head1 = (*head1)->next;
    } else {
        previous->next = current->next;
    }

    return current;
}

void sort(struct users **head) {

    int i, j, k,tempData;
    char tempname[20];
    struct users *current;
    struct users *next;

    int size = length_users(head);
    k = size ;

    for ( i = 0 ; i < size - 1 ; i++, k-- ) {
        current = *head;
        next = (*head)->next;

        for ( j = 1 ; j < k ; j++ ) {

            if ( current->points > next->points ) {
                tempData = current->points;
                current->points = next->points;
                next->points = tempData;

                strcpy(tempname, current->username);
                strcpy(current->username, next->username);
                strcpy(next->username, tempname);
            }

            current = current->next;
            next = next->next;
        }
    }
}
