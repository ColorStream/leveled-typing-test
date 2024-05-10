#include <stdio.h>
#include <io.h>
#include <stdlib.h>
#include "textreading.h"

char get_mode(void);
int get_level(void);
int get_continuous(void);
void continuous_mode(char mode, int level);

int main() {
    printf("Welcome to the Leveled Typing Test!\n");

    char mode = get_mode(); //i didn't want seperate functions but it keeps scanf from freaking out
    int level = get_level();

    int cont = get_continuous();
    if( cont == 'y'){
        system("cls"); //just so running it on the console is not so annoying
        printf("\nOkay, starting typing test . . .\n");
        continuous_mode(mode, level);
    } else {
        system("cls");
        printf("\nOkay, starting typing test . . .\n");
        start_test(mode, level);
        getchar(); getchar(); //this is just for the console to stay open to look at the result before exiting
    }

    return 0;
}

char get_mode(void) {
    printf("Pick a mode:\n [n] Normal \n [c] Consonants \n [v] Vowels \n [#] Numbers \n");

    char mode;
    do {
        printf("Enter mode: ");
        mode = getchar();
        while (getchar() != '\n'); // clear input buffer
        if (mode != 'n' && mode != 'c' && mode != 'v' && mode != '#') { //makes people re enter values
            printf("Invalid mode. Please enter a valid mode.\n");
        }
    } while (mode != 'n' && mode != 'c' && mode != 'v' && mode != '#');

    return mode;
}

int get_level(void) {
    printf("Pick a level:\n [1] Easy \n [2] Medium \n [3] Hard\n");

    int level;
    do {
        printf("Enter level: ");
        scanf("%d", &level);
        while (getchar() != '\n');
        if (level < 1 || level > 3) {
            printf("Invalid level. Please enter a valid level.\n");
        }
    } while (level < 1 || level > 3);

    return level;
}

int get_continuous(void) {
    printf("Continuous mode? \n [y] Yes \n [n] No \n");

    char mode;
    do {
        printf("Enter mode: ");
        mode = getchar();
        while (getchar() != '\n');
        if (mode != 'y' && mode != 'n') {
            printf("Invalid mode. Please enter a valid mode.\n");
        }
    } while (mode != 'y' && mode != 'n');

    return mode;
}

void continuous_mode(char mode, int level){
    while (1) {
        start_test(mode, level);

        char input[10];
        printf("Press enter to continue testing or type 'exit' to quit: ");
        fgets(input, sizeof(input), stdin);
        if (strcmp(input, "exit\n") == 0) {
            break;
        }
    }
}
