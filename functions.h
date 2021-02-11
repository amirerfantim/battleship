#include "headers.h"

#define row 10
#define column 10



void main_menu();
void show_main_menu();
void players_menu();
void show_player_menu();
void choose_user_menu();
void show_choose_user();
void put_ships_menu();
void show_ships_menu();
void create_newuser();
int get_command();
void print_map();
void print_atk_map();
void countdown();
void get_coordinates();
int attack_coordinates();
void rocket();
int valid_rocket_coor();
int rocket_coordinates();
int rocket_users();
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
int points_to_add();
void cleanup_list();
void cleanup_all();
void two_player_game();
void play_with_bot();
void what_player_choose();
void save_game();
int load_game();
void insert_users();
void sort();
void reverse();
void reverse_node();
void list_duplicator();
void print_users();
void print_games();
int length_users();
void playback();
void playback_map();
int playback_attack();

struct node *ReadNextFromFile();
struct node *ReadListIn();
struct users *ReadNextUser();
struct users *ReadUsersIn();
struct node *find();
struct node* find_by_pos();
struct node* delete_1var();
struct node* delete_2var();
bool search_linked();



