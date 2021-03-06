#include "headers.h"
#include "functions.h"
#include "theme.h"

int id1, id2;
int g_bot_or_human; // 1 == bot | 2 == human
char username1[20] = "Player 1", username2[20] = "Player 2";

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
struct users *saved_games;

struct node *head1_p1 = NULL; //ship coordinates
struct node *head2_p1 = NULL; // forbidden coordinates
struct node *head_atkp1 = NULL; // coordinates that player1 attacked
struct node *head_desp1 = NULL; // ship coordinates that player  1 destroyed
struct node *water_p1 = NULL; // water around destroyed ship

struct node *head1_p2 = NULL; // ship coordinates
struct node *head2_p2 = NULL; // forbidden coordinates
struct node *head_atkp2 = NULL; // coordinates that player2 attacked
struct node *head_desp2 = NULL; // ship coordinates that player 2 destroyed
struct node *water_p2 = NULL; // water around destroyed ship

// for play-back player 1
struct node *h_ships_p1 = NULL; // ship coordinates
struct node *ha_water_p1 = NULL; // forbidden coordinates
struct node *h_atk_p1 = NULL; // to save coordinates that player2 attacked
struct node *h_des_p1 = NULL; // ship coordinates that player 2 destroyed
struct node *h_water_p1 = NULL; // water around destroyed ship
struct node *show_atk_p1 = NULL; // to show attacked coor's one-by-ne

// for play-back player 2
struct node *h_ships_p2 = NULL; // ship coordinates
struct node *ha_water_p2 = NULL; // forbidden coordinates
struct node *h_atk_p2 = NULL; // to save coordinates that player2 attacked
struct node *h_des_p2 = NULL; // ship coordinates that player 2 destroyed
struct node *h_water_p2 = NULL; // water around destroyed ship
struct node *show_atk_p2 = NULL; // to show attacked coor's one-by-ne


// bot == 1 || human =+2
void save_game(){

    char user[20], temp[20], file_address[50], address_temp[50], folder_name[50];
    printf("enter your file name [maximum of 10 character]: ");
    scanf("%s", user);
    printf("\n");
    insert_users(user, 0, 0, &saved_games);
    WriteUsersToFile(saved_games, 2);

    strcpy(folder_name, "mkdir data\\users\\");
    strcat(folder_name, user);
    system(folder_name);

    strcpy(file_address,  "data\\users\\");
    strcat(file_address, user);
    strcat(file_address,"\\");
    strcpy(address_temp, file_address);

    strcat(file_address, "data.txt");

    FILE *fp = fopen(file_address, "w");
    fseek(fp,0, SEEK_SET);
    fprintf(fp,"%d,%d,%d", g_bot_or_human, id1, id2);
    fclose(fp);


    strcpy(file_address, address_temp);
    strcat(file_address, user);
    WriteListToFile(head1_p1, file_address, "ship", "p1");

    strcpy(file_address, address_temp);
    strcat(file_address, user);
    WriteListToFile(head_atkp1, file_address, "atk", "p1");

    strcpy(file_address, address_temp);
    strcat(file_address, user);
    WriteListToFile(head_desp1, file_address, "des", "p1");

    strcpy(file_address, address_temp);
    strcat(file_address, user);
    WriteListToFile(head2_p1, file_address, "awat", "p1");

    strcpy(file_address, address_temp);
    strcat(file_address, user);
    WriteListToFile(water_p1, file_address, "pwat", "p1");



    strcpy(file_address, address_temp);
    strcat(file_address, user);
    WriteListToFile(head1_p2, file_address, "ship", "p2");

    strcpy(file_address, address_temp);
    strcat(file_address, user);
    WriteListToFile(head_atkp2, file_address, "atk", "p2");

    strcpy(file_address, address_temp);
    strcat(file_address, user);
    WriteListToFile(head_desp2, file_address, "des", "p2");

    strcpy(file_address, address_temp);
    strcat(file_address, user);
    WriteListToFile(head2_p2, file_address, "awat", "p2");

    strcpy(file_address, address_temp);
    strcat(file_address, user);
    WriteListToFile(water_p2, file_address, "pwat", "p2");

    WriteUsersToFile(start1, 1);

}

int load_game(){
    char user[20], temp[20], file_address[50], address_temp[50];
    ReadUsersIn(&saved_games, 2);
    print_games(&saved_games);
    printf("\n");

    printf("enter your file name you wanna load: ");
    scanf("%s", user);
    printf("\n");

    strcpy(file_address,  "data\\users\\");
    strcat(file_address, user);
    strcat(file_address,"\\");
    strcpy(address_temp, file_address);

    strcat(file_address, "data.txt");

    FILE *fp = fopen(file_address, "r");
    fseek(fp,0, SEEK_SET);

    char parsedLine[102];
    fgets(parsedLine, 100, fp);
    int bot_or_human = atoi(strtok(parsedLine, ","));
    id1 = atoi(strtok(NULL, ","));
    find_users(id1, 1,  0, &start1, &playing_users);
    id2 = atoi(strtok(NULL, ","));
    find_users(id2, 2,  0, &start1, &playing_users);


    fclose(fp);

    strcpy(file_address, address_temp);
    strcat(file_address, user);
    ReadListIn(&head1_p1, file_address, "ship", "p1");

    strcpy(file_address, address_temp);
    strcat(file_address, user);
    ReadListIn(&head_atkp1, file_address, "atk", "p1");

    strcpy(file_address, address_temp);
    strcat(file_address, user);
    ReadListIn(&head_desp1, file_address, "des", "p1");

    strcpy(file_address, address_temp);
    strcat(file_address, user);
    ReadListIn(&head2_p1, file_address, "awat", "p1");

    strcpy(file_address, address_temp);
    strcat(file_address, user);
    ReadListIn(&water_p1, file_address, "pwat", "p1");



    strcpy(file_address, address_temp);
    strcat(file_address, user);
    ReadListIn(&head1_p2, file_address, "ship", "p2");

    strcpy(file_address, address_temp);
    strcat(file_address, user);
    ReadListIn(&head_atkp2, file_address, "atk", "p2");

    strcpy(file_address, address_temp);
    strcat(file_address, user);
    ReadListIn(&head_desp2, file_address, "des", "p2");

    strcpy(file_address, address_temp);
    strcat(file_address, user);
    ReadListIn(&head2_p2, file_address, "awat", "p2");

    strcpy(file_address, address_temp);
    strcat(file_address, user);
    ReadListIn(&water_p2, file_address, "pwat", "p2");

    return bot_or_human;
}

void two_player_game(){
    //get_ship(&head1_p1, &head2_p1);
    //get_ship(&head1_p2, &head2_p2);

    cleanup_all();

    list_duplicator(&head1_p1, &h_ships_p1);
    list_duplicator(&head2_p1, &ha_water_p1);
    list_duplicator(&head1_p2, &h_ships_p2);
    list_duplicator(&head2_p2, &ha_water_p2);


    while(head1_p1 != NULL && head1_p2 != NULL) {
        print_atk_map(&head_atkp1, &head1_p2, &head_desp2, &water_p2);

        printf("\n%s's Turn:\n1. Attack  2. Save 3. Rocket  4. Exit\n", username1);
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
        printf("\n%s's Turn:\n1. Attack  2. Save Game  3. Rocket  4. Exit\n", username2);
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
        printf("\n%s WON!\nCongratulations!\n", username2);
    }

    if(head1_p2 == NULL){
        print_atk_map(&head_atkp1, &head1_p2, &head_desp2, &water_p2);
        printf("\n%s WON!\nCongratulations!\n", username1);
    }
    WriteUsersToFile(start1, 1);

    sleep(5);
    system("cls");
    printf("\nNOW THE PLAY BACK!\n");
    playback();

}

void play_with_bot(){
    int hit_or_not;
    //get_ship(&head1_p1, &head2_p1);
    get_random_ship(&head1_p2, &head2_p2);

    cleanup_all();

    list_duplicator(&head1_p1, &h_ships_p1);
    list_duplicator(&head2_p1, &ha_water_p1);
    list_duplicator(&head1_p2, &h_ships_p2);
    list_duplicator(&head2_p2, &ha_water_p2);



    while(head1_p1 != NULL && head1_p2 != NULL) {
        print_atk_map(&head_atkp1, &head1_p2, &head_desp2, &water_p2);
        printf("\n%s's Turn:\n1. Attack  2. Save  3. Rocket 4. Exit\n", username1);
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

        //print_atk_map(&head_atkp2, &head1_p1, &head_desp1, &water_p1);
        hit_or_not = attack_coordinates(2, &head_atkp2, &head1_p1, &head_desp1
                , &water_p1, &head2_p1, 1, &h_atk_p2);
        while(hit_or_not == 1){
            hit_or_not = attack_coordinates(2, &head_atkp2, &head1_p1, &head_desp1
                    , &water_p1, &head2_p1, 1, &h_atk_p2);
            system("cls");
            print_atk_map(&head_atkp2, &head1_p1, &head_desp1, &water_p1);
        }
        system("cls");
        print_atk_map(&head_atkp2, &head1_p1, &head_desp1, &water_p1);
        countdown(2);
        system("cls");
    }

    if(head1_p1 == NULL){
        print_atk_map(&head_atkp2, &head1_p1, &head_desp1, &water_p1);
        printf("\nBOT WON!\nOops! :(\n");
    }

    if(head1_p2 == NULL){
        print_atk_map(&head_atkp1, &head1_p2, &head_desp2, &water_p2);
        printf("\n%s WON!\nCongratulations!\n", username1);
    }

    WriteUsersToFile(start1, 1);

    sleep(5);
    system("cls");
    printf("\nNOW THE PLAY BACK!\n");
    playback();
}

// one or two means player1  or player2
void what_player_choose(int one_or_two){
    int command, hit_or_not;

    command = get_command();
    if(command == 1 && one_or_two == 1){
        hit_or_not = attack_coordinates(one_or_two, &head_atkp1, &head1_p2,&head_desp2,
                                        &water_p2, &head2_p2, 0, &h_atk_p1);
        system("cls");
        print_atk_map(&head_atkp1, &head1_p2, &head_desp2, &water_p2);
        countdown(2);

        while(hit_or_not == 1 && head1_p2 != NULL){
            system("cls");
            printf("\nUse Your Bonus:\n");
            print_atk_map(&head_atkp1, &head1_p2, &head_desp2, &water_p2);
            hit_or_not = attack_coordinates(one_or_two, &head_atkp1, &head1_p2,&head_desp2,
                                            &water_p2, &head2_p2, 0, &h_atk_p1);
            system("cls");
            print_atk_map(&head_atkp1, &head1_p2, &head_desp2, &water_p2);
            countdown(2);
        }
        system("cls");
    }

    else if(command == 1 && one_or_two == 2){
        hit_or_not = attack_coordinates(one_or_two, &head_atkp2, &head1_p1,&head_desp1,
                                        &water_p1, &head2_p1, 0, &h_atk_p2);
        system("cls");
        print_atk_map(&head_atkp2, &head1_p1, &head_desp1, &water_p1);
        countdown(2);
        while(hit_or_not == 1 && head1_p1 != NULL){
            system("cls");
            printf("\nUse Your Bonus:\n");
            print_atk_map(&head_atkp2, &head1_p1, &head_desp1, &water_p1);
            hit_or_not = attack_coordinates(one_or_two, &head_atkp2, &head1_p1,&head_desp1,
                                            &water_p1, &head2_p1, 0, &h_atk_p2);
            system("cls");
            print_atk_map(&head_atkp2, &head1_p1, &head_desp1, &water_p1);
            countdown(2);
        }
        system("cls");
    }

    else if(command == 2){
        save_game();
        printf("\n%s Turn:\n1. Attack  2. Save  3.Rocket  4. Exit\n", username1);
        what_player_choose(one_or_two);
    }
    else if(command == 3){
        int enough_points;
        if(one_or_two == 1){
            enough_points = rocket_users(id1, 1, &start1);
            if(enough_points == 1){
                rocket(one_or_two);
            }else{
                printf("\nNot enough points!\n");
                sleep(1);
                printf("1. Attack  2. Save  3.Rocket  4. Exit\n");
                what_player_choose(1);
            }
        }else if(one_or_two == 2){
            enough_points = rocket_users(id2, 2, &start1);
            if(enough_points == 1){
                rocket(one_or_two);
            }else{
                printf("\nNot enough points!\n");
                sleep(1);
                printf("1. Attack  2. Save  3.Rocket  4. Exit\n");
                what_player_choose(2);
            }
        }
    }

    else if(command == 4){
        printf("\n\n    GOOD BYE :)\n");
        exit(0);
    }else{
        printf("\nWrong input! TryAgian...\n");
        what_player_choose(one_or_two);
    }
}

void main_menu(){
    int command1, command2;
    show_main_menu();
    command1 = get_command();

    if(command1 == 1){
        system("cls");
        players_menu("Player 1",1,&head1_p1, &head2_p1);

        system("cls");
        players_menu("Player 2",2,&head1_p2, &head2_p2);

        g_bot_or_human = 2;
        two_player_game();

    }else if(command1 == 2){
        system("cls");
        players_menu("Player",1,&head1_p1, &head2_p1);
        g_bot_or_human = 1;

        play_with_bot();

    }else if (command1 == 3){
        system("cls");
        int bot_or_human = load_game();

        find_users(id1, 1, 0, &start1, &playing_users);
        find_users(id2, 2, 0, &start1, &playing_users);

        if(bot_or_human == 1) {
            g_bot_or_human = 1;
            play_with_bot();
        }else{
            g_bot_or_human = 2;
            two_player_game();
        }


    }else if(command1 == 4){
        system("cls");
        sort(&start1);
        reverse(&start1);
        print_users(&start1);

        countdown(5);
        system("cls");
        main_menu();

    }else if(command1 == 5){
        theme();

    }else if (command1 == 6){
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
           "4.Score Board\n"
           "5.Theme\n"
           "6. Exit\n");
}

int get_command(){
    int command;
    printf("enter your command: ");
    scanf("%d", &command);
    return  command;
}

void create_newuser(int one_or_two) {
    char username[20];
    printf("enter a username [maximum of 15 characters]: ");
    scanf("%s", username);
    printf("Congratulations %s!\n", username);

    int id = length_users(&start1) + 1;
    if(one_or_two == 1){
        id1 = id;
    }else if(one_or_two == 2){
        id2 = id;
    }
    insert_users(username, 0, id, &start1);
    find_users(id, one_or_two,0, &start1);
    WriteUsersToFile(start1, 1);

}

void print_users(struct users **head) {
    struct users *ptr = *head;
    printf("\n\n");
    int i = 1;
    printf(" Row   Username             Points   ID\n\n");
    while (ptr != NULL) {
        printf("%3d.   %-20s %-4d     %-3d\n", i, ptr->username, ptr->points, ptr->ID);
        ptr = ptr->next;
        i++;
    }
}

void print_games(struct users **head) {
    struct users *ptr = *head;
    printf("\n\n");
    int i = 1;
    printf(" Row   Name\n\n");
    while (ptr != NULL) {
        printf("%3d.   %-20s\n", i, ptr->username);
        ptr = ptr->next;
        i++;
    }
}

void players_menu(char player[],int one_or_two, struct node** ships,struct node **water){
    int command;
    system("cls");
    printf("\n%s:\n", player);

    show_player_menu();
    command = get_command();
    if(command == 1){
        system("cls");
        choose_user_menu(player,one_or_two, ships, water);
        put_ships_menu(player,one_or_two, ships, water);
    }
    else if(command == 2){
        system("cls");
        put_ships_menu(player,one_or_two, ships, water);
        choose_user_menu(player,one_or_two, ships, water);

    }else{
        system("cls");
        main_menu();
    }
}

void put_ships_menu(char player[],int one_or_two, struct node** ships,struct node **water){
    int command;
    system("cls");

    show_ships_menu(player);
    command = get_command();

    if(command == 1){
        system("cls");
        get_random_ship(ships,water);


    }else if(command == 2){
        system("cls");
        get_ship(ships, water);

    }else {
        system("cls");
        printf("WRONG INPUT!\n");
        players_menu(player,one_or_two, ships, water);
    }
}

void choose_user_menu(char player[],int one_or_two, struct node** ships,struct node **water){
    int command;
    show_choose_user(player);
    command = get_command();

    if(command == 1){
        system("cls");
        int user_row, id, users_leng;

        print_users(&start1);
        users_leng = length_users(&start1);

        printf("\nChoose an user (enter ID number  to choose): ");
        scanf("%d", &user_row);
        if(user_row > users_leng){
            system("cls");
            printf("WRONG INPUT!\n");
            choose_user_menu(player, one_or_two, ships, water);
        }
        else{
            system("cls");
            id = user_row;
            find_users(id, one_or_two,0, &start1);
        }
    }
    else if(command == 2){
        system("cls");
        create_newuser(one_or_two);
    }
    else{
        system("cls");
        printf("WRONG INPUT!\n");
        players_menu(player,one_or_two, ships, water);
    }

}

void show_player_menu(){
    printf("1. Choose User\n"
           "2. Put Ships\n");
}

void show_choose_user(char player[]){
    printf("%s:\n1. Choose from available users\n"
           "2. New user\n", player);
}

void show_ships_menu(char player[]){
    printf("%s:\nPut ships:\n1. Auto\n2. Manual\n", player);
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
        printf("This will be hidden after %d second(s)...\n", i);
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


    get_coordinates(2, 4, head1, head2);
    system("cls");
    print_map(13, head1);

    get_coordinates(2, 5, head1, head2);
    system("cls");
    print_map(15, head1);

    get_coordinates(2, 6, head1, head2);
    system("cls");
    print_map(17, head1);

    get_coordinates(1, 7, head1, head2);
    system("cls");
    print_map(18, head1);

    get_coordinates(1, 8, head1, head2);
    system("cls");
    print_map(19, head1);

    get_coordinates(1, 9, head1, head2);
    system("cls");
    print_map(20, head1);

    get_coordinates(1, 10, head1, head2);
    system("cls");
    print_map(21, head1);

    //WriteListToFile(head1_p1, 1, 1);

    countdown(5);
    system("cls");

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
    random_coordinates(2, 4, head1, head2);
    random_coordinates(2, 5, head1, head2);
    random_coordinates(2, 6, head1, head2);
    random_coordinates(1, 7, head1, head2);
    random_coordinates(1, 8, head1, head2);
    random_coordinates(1, 9, head1, head2);
    random_coordinates(1, 10, head1, head2);


    system("cls");
}

// if head==p1 then ships==p2
// if rand_or_not == 1 ->random if == 0 ->manual
int attack_coordinates(int one_or_two, struct node **attack, struct node **ships2, struct node **destroy,
                       struct node** water, struct node **all_water, int rand_or_not, struct node ** playback_atk) {
    printf("\nenter coordinate you wanna hit:\n");
    int inner_row, inner_column, points;

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
            insert_coordinates(inner_row, inner_column, ship_num, ship_length, playback_atk);
        }
        else{
            printf("\nYou've already hit this coordinate...\nTry Again\n\n");
            attack_coordinates(one_or_two,attack, ships2, destroy, water, all_water, rand_or_not, playback_atk);
        }
    }


    else{
        printf("\nyou entered invalid inputs!! :)\nTry Again...\n\n");
        attack_coordinates(one_or_two, attack, ships2, destroy, water, all_water, rand_or_not, playback_atk);
    }

    int check_destroyed = 0;
    if(hit_or_not != 0){
        check_destroyed = destroyed_ship(ship_num, ship_length, attack);
    }
    if(check_destroyed == 1){
        find_add(ship_num, attack, ships2, destroy);
        find_add(ship_num, all_water, all_water, water );
    }
    if(hit_or_not != 0 && one_or_two == 1){
        find_users(id1, 1, 1, &start1, &playing_users);
        if(check_destroyed == 1){
            points = points_to_add(ship_length);
            find_users(id1, 1, points, &start1, &playing_users);
        }
    }else if(hit_or_not != 0 && one_or_two == 2 && rand_or_not == 0){
        find_users(id2, 2, 1, &start1, &playing_users);
        if(check_destroyed == 1){
            points = points_to_add(ship_length);
            find_users(id2, 2, points, &start1, &playing_users);
        }
    }
    return hit_or_not;
}

int points_to_add(int ship_length){
    if(ship_length == 1){
        return 25;
    } else if(ship_length == 2){
        return 12;
    } else if(ship_length == 3){
        return 8;
    } else{
        return 5;
    }
}

void rocket(int one_or_two){
    static int once_p1 = 0, once_p2 = 0;
    int command,  rocket_num, loop, tester, hitted;
    printf("\nUse Your Rocket!\n1. Vertical  2. Horizontal\n");
    command = get_command();
    if(command == 1){
        printf("enter the column number you wanna hit: ");
        scanf("%d", &rocket_num);
        tester = valid_rocket_coor(rocket_num);

        if(tester == 0){
            rocket(one_or_two);
        }
        else if(one_or_two == 1 && once_p1 != 1){

            once_p1 = 1;

            for(loop = 1; loop < 11; loop++){
                hitted = rocket_coordinates(loop, rocket_num, one_or_two, &head_atkp1, &head1_p2,&head_desp2,
                                            &water_p2, &head2_p2);
                if(hitted == 1){
                    break;
                }
            }
            print_atk_map(&head_atkp1, &head1_p2, &head_desp2, &water_p2);
            countdown(2);
            system("cls");

        }else if (one_or_two == 2 && once_p2 != 1){

            once_p2 = 1;

            for(loop = 1; loop < 11; loop++) {
                hitted = rocket_coordinates(loop, rocket_num, one_or_two, &head_atkp2, &head1_p1, &head_desp1,
                                            &water_p1, &head2_p1);
                if(hitted == 1) {
                    break;
                }
            }
            print_atk_map(&head_atkp2, &head1_p1, &head_desp1, &water_p1);
            countdown(2);
            system("cls");
        }
        else{
            printf("\n You used Rocket once in this game!\n");
            printf("\n1. Attack  2. Save 3. Rocket  4. Exit\n");
            what_player_choose(one_or_two);
        }

    }else if(command == 2){
        printf("enter the row number you wanna hit: ");
        scanf("%d", &rocket_num);
        tester = valid_rocket_coor(rocket_num);

        if(tester == 0){
            rocket(one_or_two);
        }
        else if(one_or_two == 1 && once_p1 != 1){

            once_p1 = 1;

            for(loop = 1; loop < 11; loop++){
                hitted = rocket_coordinates(rocket_num, loop, one_or_two, &head_atkp1, &head1_p2,&head_desp2,
                                            &water_p2, &head2_p2);
                if(hitted == 1){
                    break;
                }
            }
            print_atk_map(&head_atkp1, &head1_p2, &head_desp2, &water_p2);
            countdown(2);
            system("cls");

        }else if (one_or_two == 2 && once_p2 != 1){

            once_p2 = 1;

            for(loop = 1; loop < 11; loop++) {
                hitted = rocket_coordinates(rocket_num, loop, one_or_two, &head_atkp2, &head1_p1, &head_desp1,
                                            &water_p1, &head2_p1);
                if(hitted == 1){
                    break;
                }
            }
            print_atk_map(&head_atkp2, &head1_p1, &head_desp1, &water_p1);
            countdown(2);
            system("cls");
        }
        else{
            printf("\n You used Rocket once in this game!\n");
            printf("\n1. Attack  2. Save 3. Rocket  4. Exit\n");
            what_player_choose(one_or_two);
        }
    }else{
        printf("\n1. Attack  2. Save 3. Rocket  4. Exit\n");
        what_player_choose(one_or_two);
    }

}

int valid_rocket_coor(int rocket_num){
    if(rocket_num < 11 && rocket_num > 0){
        return 1;
    }
    return 0;
};

int rocket_coordinates(int inner_row, int inner_column, int one_or_two, struct node **attack, struct node **ships2,
                       struct node **destroy, struct node** water, struct node **all_water) {

    int hit_or_not = counter_linked(ships2, inner_row, inner_column), points;
    int ship_num = 0, ship_length = 0;
    struct node* search_result = find(inner_row, inner_column, ships2);

    if(search_result != NULL){
        ship_num = search_result->ship_num;
        ship_length = search_result->ship_length;
    }

    if(search_linked(attack, inner_row, inner_column) == false) {
        insert_coordinates(inner_row, inner_column, ship_num, ship_length, attack);
    }

    int check_destroyed = 0;
    if(hit_or_not != 0){
        check_destroyed = destroyed_ship(ship_num, ship_length, attack);
    }

    if(check_destroyed == 1){
        find_add(ship_num, attack, ships2, destroy);
        find_add(ship_num, all_water, all_water, water );
    }

    if(hit_or_not != 0 && one_or_two == 1){
        find_users(id1, 1, 1, &start1, &playing_users);
        if(check_destroyed == 1){
            points = points_to_add(ship_length);
            find_users(id1, 1, ship_length, &start1, &playing_users);
        }
    }else if(hit_or_not != 0 && one_or_two == 2){
        find_users(id2, 2, 1, &start1, &playing_users);
        if(check_destroyed == 1){
            points = points_to_add(ship_length);
            find_users(id2, 2, ship_length, &start1, &playing_users);
        }
    }

    return hit_or_not;
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
        printf("* saved *\n");

    } else {
        printf("FILE OPEN ERROR\n");
    }

}

// 1 for user & 2 for game
void WriteUsersToFile(struct users* start, int user_or_game) {
    FILE *pFile;
    if(user_or_game == 1) {
        pFile = fopen("data\\users101.bin", "wb");
    }else if(user_or_game == 2){
        pFile = fopen("data\\savedgames101.bin", "wb");
    }

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
        printf("* saved *\n");

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

// 1 for user & 2 for game
struct users *ReadUsersIn(struct users **start, int user_or_game) {

    FILE *pFile;
    if(user_or_game == 1) {
        pFile = fopen("data\\users101.bin", "rb");
    }else if(user_or_game == 2){
        pFile = fopen("data\\savedgames101.bin", "rb");

    }
    if(pFile != NULL) {

        //CleanUp(*start);
        *start = NULL;

        fseek(pFile, 0, SEEK_END);
        long fileSize = ftell(pFile);
        rewind(pFile);

        int numEntries = (int)(fileSize / (sizeof(struct users)));
        //printf("numEntries:%d\n",numEntries);

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
void find_users(int key,int one_or_two ,int add_point, struct users** head1, struct users** add) {

    struct users* current = *head1;

    while(current != NULL) {
        if(current->ID == key){
            //insert_users(current->username, current->points, one_or_two, add);
            current->points = current->points + add_point;
            if(one_or_two == 1){
                id1 = current->ID;
                strcpy(username1, current->username);
            }
            else if(one_or_two == 2){
                id2 = current->ID;
                strcpy(username2, current->username);
            }
        }
        current = current->next;
    }


}

struct node* find_by_pos(int num, struct node ** head1) {
    int i = 0;
    struct node *ptr = *head1;

    while(i < num-1) {
        ptr = ptr->next;
        i++;
    }
    return ptr;
}

int rocket_users(int key,int one_or_two , struct users** head1) {

    struct users* current = *head1;

    while(current != NULL) {
        if(current->ID == key){
            //insert_users(current->username, current->points, one_or_two, add);
            if(current->points >= 100){
                current->points = current->points - 100;
                return  1;
            }
            else{
                return 0;
            }
            if(one_or_two == 1){
                id1 = current->ID;
                strcpy(username1, current->username);
            }
            else if(one_or_two == 2){
                id2 = current->ID;
                strcpy(username2, current->username);
            }
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

                tempData = current->ID;
                current->ID = next->ID;
                next->ID = tempData;

                strcpy(tempname, current->username);
                strcpy(current->username, next->username);
                strcpy(next->username, tempname);
            }

            current = current->next;
            next = next->next;
        }
    }
}

void reverse(struct users** head_ref) {
    struct users* prev   = NULL;
    struct users* current = *head_ref;
    struct users* next;

    while (current != NULL) {
        next  = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    *head_ref = prev;
}

void reverse_node(struct node** head_ref) {
    struct node* prev   = NULL;
    struct node* current = *head_ref;
    struct node* next;

    while (current != NULL) {
        next  = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    *head_ref = prev;
}

void list_duplicator(struct node ** main, struct node **add) {

    struct node *ptr = *main;

    while(ptr != NULL) {
        insert_coordinates(ptr->row_coor, ptr->column_coor, ptr->ship_num, ptr->ship_length, add);
        ptr = ptr->next;
    }
}


// play-back functions

int playback_attack(int pos, int one_or_two,struct node ** show_atk, struct node **playback_atk,
                    struct node **ships2, struct node **destroy,  struct node** water, struct node **all_water) {
    int inner_row, inner_column;

    struct node *current = find_by_pos(pos,  playback_atk);
    inner_row = current->row_coor;
    inner_column = current->column_coor;

    int hit_or_not = counter_linked(ships2, inner_row, inner_column);
    int ship_num = 0, ship_length = 0;
    struct node* search_result = find(inner_row, inner_column, ships2);

    if(search_result != NULL){
        ship_num = search_result->ship_num;
        ship_length = search_result->ship_length;
    }

    insert_coordinates(inner_row, inner_column,  ship_num, ship_length, show_atk);


    int check_destroyed = 0;
    if(hit_or_not != 0){
        check_destroyed = destroyed_ship(ship_num, ship_length, show_atk);
    }
    if(check_destroyed == 1){
        find_add(ship_num, show_atk, ships2, destroy);
        find_add(ship_num, all_water, all_water, water );
    }
    if(hit_or_not != 0 && one_or_two == 1){
        find_users(id1, 1, 1, &start1, &playing_users);
        if(check_destroyed == 1){
            find_users(id1, 1, ship_length, &start1, &playing_users);
        }
    }else if(hit_or_not != 0 && one_or_two == 2){
        find_users(id2, 2, 1, &start1, &playing_users);
        if(check_destroyed == 1){
            find_users(id2, 2, ship_length, &start1, &playing_users);
        }
    }
    return hit_or_not;
}

void playback(){
    int loop1 = 1,  loop2 = 1;
    reverse_node(&h_atk_p2);
    reverse_node(&h_atk_p1);

    while(h_ships_p1 != NULL && h_ships_p2 != NULL) {

        int hit_or_not  = 1;
        printf("\n%s Turn\n", username1);
        print_atk_map(&show_atk_p1, &h_ships_p2, &h_des_p2, &h_water_p2);
        sleep(1);
        system("cls");

        while(hit_or_not == 1) {
            hit_or_not = playback_attack(loop1,1,&show_atk_p1, &h_atk_p1,  &h_ships_p2, &h_des_p2,
                                         &h_water_p2, &ha_water_p2);
            printf("\n%s Turn\n", username1);
            print_atk_map(&show_atk_p1, &h_ships_p2, &h_des_p2, &h_water_p2);
            sleep(1);
            system("cls");
            loop1++;
        }

        if(h_ships_p2 == NULL){
            break;
        }
        hit_or_not = 1;

        printf("\n%s Turn\n", username2);
        print_atk_map(&show_atk_p2, &h_ships_p1, &h_des_p1, &h_water_p1);
        sleep(1);
        system("cls");

        while(hit_or_not == 1) {
            hit_or_not = playback_attack(loop2,2,&show_atk_p2, &h_atk_p2,  &h_ships_p1, &h_des_p1,
                                         &h_water_p1, &ha_water_p1);
            loop2++;

            printf("\n%s Turn\n", username2);
            print_atk_map(&show_atk_p2, &h_ships_p1, &h_des_p1, &h_water_p1);
            sleep(1);
            system("cls");
        }

    }

    if(h_ships_p2 == NULL){
        print_atk_map(&h_atk_p2, &h_ships_p1, &h_des_p1, &h_water_p1);
        printf("\n%s WON!\nCongratulations!\n", username1);
        sleep(3);
        system("cls");
    }

    if(h_ships_p1 == NULL){
        print_atk_map(&h_atk_p1, &h_ships_p2, &h_des_p2, &h_water_p2);
        printf("\n%s WON!\nCongratulations!\n", username2);
        sleep(3);
        system("cls");
    }


}


