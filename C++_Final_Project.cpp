#include <iostream>
#include <fstream>
#include <string.h>
#include <ctime>
#include <cstdlib>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

std::fstream fp;

void multiplayer(char* arr, char* player1name, char* player2name);
char* check_winner(char* arr);
void box(char* arr);
void history();
void computer(char* arr, char* player1name, char* player2name);
int redundency(char* arr, int user_input, char* player1name);
int redundency_comp(char* arr, int user_input, char* player1name);

int main() {
    fp.open("C++Final_Records.txt", std::ios::app);
    int user;
    while (user != 3) {
        system("cls");
        char arr[9] = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
        char player1name[50], player2name[50];
        std::cout << "\n\n\n\n\n\n\n\t\t\t\t\t------TIC_TAC_TOE------\n\n\n";
        std::cout << "\t\t\t\t\tPress 1: Multiplayer\n\n";
        std::cout << "\t\t\t\t\tPress 2: Vs Computer\n\n";
        std::cout << "\t\t\t\t\tPress 3: History \n\n";
        std::cout << "\t\t\t\t\tPress 4: Quit the game\n\n";
        std::cout << "\t\t\t\t\t----->";
        int user = getche();

        switch (user) {
            case '1': {
                int moves = 0;
                system("cls");
                std::cout << "\n\n\n\n\n\n\n\t\t\tEnter player1 name (Don't use spaces): ";
                std::cin >> player1name;
                std::cout << "\n\n\t\t\tEnter player2 name (Don't use spaces): ";
                std::cin >> player2name;

                if (player1name[0] == '\0') {
                    strcpy(player1name, "Player 1");
                }
                if (player2name[0] == '\0') {
                    strcpy(player2name, "Player 2");
                }

                fp << "\t\t\t\t" << player1name << "\t " << player2name << "\t";
                system("cls");
                box(arr);
                multiplayer(arr, player1name, player2name);
                user = 0;
                break;
            }
            case '2': {
                int moves = 0;
                system("cls");
                std::cout << "\n\n\n\n\n\n\n\t\t\tEnter player1 name (Don't use spaces): ";
                std::cin >> player1name;

                if (player1name[0] == '\0') {
                    strcpy(player1name, "Player 1");
                }
                char player2name[11] = "Computer";
                fp << "\t\t\t\t" << player1name << "\t " << player2name << "\t";
                system("cls");
                box(arr);
                computer(arr, player1name, player2name);
                user = 0;
                break;
            }
            case '3': {
                system("cls");
                history();
                user = 0;
                break;
            }
            case '4': {
                exit(0);
            }
        }
    }

    fp.close();
    return 0;
}

void box(char* arr) {
    system("cls");
    std::cout << "\n\n\n\n\n\n\n\t\t\t\t-------------------------------------\n";
    for (int i = 0; i < 9; i += 3) {
        std::cout << "\t\t\t\t|           |           |           |\n";
        std::cout << "\t\t\t\t|           |           |           |\n";
        std::cout << "\t\t\t\t|     " << arr[i] << "     |     " << arr[i + 1] << "     |     " << arr[i + 2] << "     |\n";
        std::cout << "\t\t\t\t|           |           |           |\n";
        std::cout << "\t\t\t\t|           |           |           |\n";
        std::cout << "\t\t\t\t-------------------------------------\n";
    }
}

char* check_winner(char* arr) {
    for (int i = 0; i < 9; i += 3) {
        if (arr[i] == arr[i + 1] && arr[i] == arr[i + 2]) {
            return &arr[i];
        }
    }
    for (int i = 0; i < 3; i++) {
        if (arr[i] == arr[i + 3] && arr[i] == arr[i + 6]) {
            return &arr[i];
        }
    }
    if (arr[0] == arr[4] && arr[0] == arr[8]) {
        return &arr[0];
    }
    if (arr[2] == arr[4] && arr[2] == arr[6]) {
        return &arr[2];
    }
    return NULL;
}

void multiplayer(char* arr, char* player1name, char* player2name) {
    int moves = 0;
    char player1[10];
    char player2[10];
    while (moves < 9) {
    	
    	// Player 1 Turn
        std::cout << "\t\t\t\t" << player1name << "'s Turn\n";
        std::cout << "\t\t\t\tWhere do you want to put X?: ";
        int X_place;
        std::cin >> X_place;
        int pos = redundency(arr, X_place, player1name);
        arr[pos - 1] = 'X';
        box(arr);
        moves++;
        if (check_winner(arr) != NULL) {
            std::cout << "\t\t\t\t\t" << player1name << " is the winner!\n";
            fp << "\t" << player1name << "_won";
            break;
        } else if (moves == 9) {
            std::cout << "\t\t\t\t\tThe game is a draw!\n";
            fp << "\tDraw";
            break;
        }
        
        // Player 2 Turn
        std::cout << "\t\t\t\t" << player2name << "'s Turn\n";
        std::cout << "\t\t\t\tWhere do you want to put O?: ";
        int O_place;
        std::cin >> O_place;
        int pos2 = redundency(arr, O_place, player2name);
        arr[pos2 - 1] = 'O';
        box(arr);
        moves++;
        if (check_winner(arr) != NULL) {
            std::cout << "\t\t\t\t\t" << player2name << " is the winner!\n";
            fp << "\t" << player2name << "_won";
            break;
        } else if (moves == 9) {
            std::cout << "\t\t\t\t\tThe game is a draw!\n";
            fp << "\tDraw";
            break;
        }
    }
    fp << "\t" << moves << "\n";
    std::cout << "\n\t\t\t\tPress any Key to get back to the menu......";
    getch();
}

void computer(char* arr, char* player1name, char* player2name) {
    int moves = 0;
    char player1[10];
    char player2[10];
    srand(time(NULL));
    while (moves < 9) {
    	
    	//Player 1 Turn
        std::cout << "\t\t\t\t" << player1name << "'s Turn\n";
        std::cout << "\t\t\t\tWhere do you want to put X?: ";
        int X_place;
        std::cin >> X_place;
        int pos = redundency(arr, X_place, player1name);
        arr[pos - 1] = 'X';
        box(arr);
        moves++;
        if (check_winner(arr) != NULL) {
            std::cout << "\t\t\t\t\t" << player1name << " is the winner!\n";
            fp << "\t" << player1name << "_won";
            break;
        } else if (moves == 9) {
            std::cout << "\t\t\t\t\tThe game is a draw!\n";
            fp << "\tDraw";
            break;
        }
        
        //Computer Turn
        int O_place = rand() % 10 + 1;
        int pos2 = redundency_comp(arr, O_place, player2name);
        arr[pos2 - 1] = 'O';
        box(arr);
        moves++;
        if (check_winner(arr) != NULL) {
            std::cout << "\t\t\t\t\t" << player2name << " is the winner!\n";
            fp << "\t" << player2name << "_won";
            break;
        } else if (moves == 9) {
            std::cout << "\t\t\t\t\tThe game is a draw!\n";
            fp << "\tDraw";
            break;
        }
    }
    fp << "\t" << moves << "\n";
    std::cout << "\n\t\t\t\tPress any Key to get back to the menu......";
    getch();
}

void history() {
	fp.close();
	fp.open("C++Final_Records.txt", std::ios::in);
    char c;
    fp.seekp(0, std::ios::beg);
    std::cout << "\n\n\n\n\n\n\n\t\t\t\t\t-------History-------\n\n";
    c = fp.get();
    while (!fp.eof()) {
        std::cout << c;
        c = fp.get();
    }
    fp.close();
    fp.open("C++Final_Records.txt", std::ios::app);
    std::cout << "\n\n";
    std::cout << "\t\t\t\tPress any key to get back to the menu......";
    getch(); // Use getch() to wait for a key press
}

int redundency(char* arr, int user_input, char* player1name )
{
	
	if (arr[user_input - 1] == 'O' || arr[user_input - 1] == 'X')
	{
		box(arr);
		std::cout << "\t\t\t\tInvalid input, Try again\n";
		std::cout << "\t\t\t\t" << player1name << "'s Turn\n";
        std::cout << "\t\t\t\tWhere do you want to put X?: ";
        std::cin >> user_input;
        int val = redundency(arr, user_input, player1name);
        return val;
	}
	return user_input;
	
}
int redundency_comp(char* arr, int user_input, char* player1name)
{
	if (arr[user_input - 1] == 'O' || arr[user_input - 1] == 'X')
	{
        user_input = rand() % 10 + 1;
        int val = redundency_comp(arr, user_input, player1name);
        return val;
	}
	return user_input;
	
}
