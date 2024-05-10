//
// Created by amand on 4/27/2024.
//

#include "textreading.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void test_user(const char* chunk) {
    char input[1000];
    printf("\nType the passage and press enter to submit:\n");
    clock_t start_time = clock(); // recording time - clock_t is a long int that stores cpu cycles
    fgets(input, sizeof(input), stdin); // read user input
    input[strcspn(input, "\n")] = '\0'; //remove newline from input

    if (input[0] == '\0') { // if input is empty
        printf("You did not type anything. Please try again.\n");
        return;
    } //necessary because the wpm bugs out rly bad if i let them just press enter lol

    if (strcmp(input, chunk) == 0) { // if input matches the chunk perfectly
        clock_t end_time = clock(); // stop recording time
        double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC; // time is the difference between the two times, clocks per sec is the number of seconds

        // calculating words per minute (avg word is 5 long)
        int num_words = strlen(chunk) / 5; // 5 as average word size is apparently how wpm is calculated generally
        double wpm = (num_words / time_taken) * 60;

        // results
        printf("You typed the passage correctly in %.2f seconds.\n", time_taken);
        printf("Words per minute: %.2f\n Accuracy: 100%%\n", wpm);
    } else {
        clock_t end_time = clock();
        double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        int num_words = strlen(chunk) / 5;
        double wpm = (num_words / time_taken) * 60;


        int matching_chars = 0;
        int chunk_length = strlen(chunk);

        for (int i = 0; input[i] != '\0' && chunk[i] != '\0'; i++) { //for determining accuracy
            if (input[i] == chunk[i]) { //really not the best method but what can you do
                matching_chars++;
            }
        }

        // print results
        printf("You typed the passage in %.2f seconds.\n", time_taken);
        double accuracy = (double)matching_chars / chunk_length * 100;
        printf("Words per minute: %.2f\n Accuracy: %.2f%%\n", wpm, accuracy);

    }
}

void start_test(char mode, int level) {
    char filename[100]; // 100 characters because it only works w/ full filepath :/
    //hardcoded because the compiler doesn't like it if i use relative paths?
    if (mode != '#') { //if not number mode
        snprintf(filename, sizeof(filename), "C:\\Users\\amand\\Documents\\Classes\\introToC\\Assignments\\finalproject\\TypingTest\\texts\\textbank%d.txt",
                 ((rand() % 3) + 1)); //the texts right now are dracula, frankenstein and sherlock holmes
    } else { //if number mode
        //numbers get special type because it's actually so difficult normally
        if (level == 1) { //this is pi with spaces
            snprintf(filename, sizeof(filename), "C:\\Users\\amand\\Documents\\Classes\\introToC\\Assignments\\finalproject\\TypingTest\\texts\\pi1.txt");
        } else if (level == 2) { //this is pi without spaces
            snprintf(filename, sizeof(filename), "C:\\Users\\amand\\Documents\\Classes\\introToC\\Assignments\\finalproject\\TypingTest\\texts\\pi2.txt");
        } else if (level == 3) { //this is pi in hexidecimal
            snprintf(filename, sizeof(filename), "C:\\Users\\amand\\Documents\\Classes\\introToC\\Assignments\\finalproject\\TypingTest\\texts\\pi3.txt");
        }
    }


    // read a random chunk
    char* chunk = read_random_chunk(mode, level, filename);
    if (chunk == NULL) {
        return; //abort if failed
    }

    // for selecting mode & displaying random text
    printf("Please start typing the following passage:\n\n");
    switch (mode) {
        case 'c': //with no break, it also uses the v case
        case 'v':
            printf("%s\n", modify_passage(mode, chunk));
            test_user(modify_passage(mode, chunk));
            break;
        default:
            printf("%s\n", chunk);
            test_user(chunk);
    }

    free(chunk); //no leaks here!
}

char* read_random_chunk(char mode, int level, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file"); //perror - print error message
        return NULL;
    }

    // find size of file
    fseek(file, 0, SEEK_END); //sets the file position of the stream to the given offset
    long file_size = ftell(file); //the current file position of the given stream
    rewind(file); // sets the file position to the beginning of the file of the given stream

    // this is what google says i should do to generate a random number lol
    srand(time(NULL));

    // generate a random position within the file
    long random_position = rand() % file_size;

    // find a random position - thank you stack overflow...
    fseek(file, random_position, SEEK_SET); //seek set is beginning of file

    int max_size; //to determine size based on level
    if (mode == '#') { //check mode number vs letters
        max_size = 20; //stuck at 20 because number mode is HARD
    } else {
        //level types in letter modes; not sure whether i should use a
        // switch but figured this is better than a bunch of internal breaks
        if (level == 1) {
            max_size = 100;
        } else if (level == 2) {
            max_size = 200;
        } else if (level == 3) {
            max_size = 500;
        } else {
            printf("Not a proper level! Giving you the default...");
            max_size = 100;
        }
    }

    char* chunk = (char*)malloc(max_size + 1); // add space for the '\0' character
    if (chunk == NULL) {
        printf("Error: Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    // reading the chunk from file
    int i; //initialized out here so i can refer later
    for (i = 0; i < max_size; i++) { //for length of max length
        int c = fgetc(file); //gets the next character (an unsigned char) from the specified stream and advances the position indicator for the stream
        if (c == EOF) {
            break;  // end of file reached
        }
        if (c == '\n') {
            chunk[i] = ' '; // replacing with space so the strcmp works better
        } else {
            chunk[i] = (char)c;
        }
    }
    chunk[i] = '\0';  // end the chunk string

    fclose(file);

    return chunk;
}



char* modify_passage(char mode, const char* original_passage) {
    char* modified_passage = (char*)malloc(strlen(original_passage) + 1); // allocating memory for what's going to be modified
    if (modified_passage == NULL) { //if there's nothing in the modified passage
        printf("Error: Memory allocation failed\n");
        return NULL;
    }
    strcpy(modified_passage, original_passage); // copy original into what's gonna be modified

    // mode should tell what kind of modification to make
    switch (mode) {
        case 'c':
            // for removing vowels
            for (int i = 0; modified_passage[i] != '\0'; i++) {
                char c = modified_passage[i];
                if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
                    c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
                    for (int j = i; modified_passage[j] != '\0'; j++) { // shift everything left
                        modified_passage[j] = modified_passage[j + 1];
                    }
                    i--; // fix index now that it's removed
                }
            }
            break;
        case 'v':
            // removing consonants
            for (int i = 0; modified_passage[i] != '\0'; i++) {
                char c = modified_passage[i];
                if (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) &&
                    !(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
                      c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')) {
                    for (int j = i; modified_passage[j] != '\0'; j++) {
                        modified_passage[j] = modified_passage[j + 1];
                    }
                    i--;
                }
            }
            break;
        default:
            printf("Invalid mode!\n");
            free(modified_passage); // freeing to avoid memory leaks :)
            return NULL;
    }

    // for removing consecutive spaces, they just make things much harder
    int len = strlen(modified_passage);
    for (int i = 0; i < len - 1; i++) { //for length of passage
        if (modified_passage[i] == ' ' && modified_passage[i + 1] == ' ') { //is there a double space?
            for (int j = i + 1; j < len; j++) { // shift what's left over
                modified_passage[j] = modified_passage[j + 1];
            }
            len--; // fix length
            i--; // fix index
        }
    }

    return modified_passage;
}
