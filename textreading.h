//
// Created by amand on 4/27/2024.
//

#ifndef TYPINGTEST_TEXTREADING_H
#define TYPINGTEST_TEXTREADING_H

void start_test(char mode, int level);
char* read_random_chunk(char mode, int level, const char* filename);
void test_user(const char* chunk);
char* modify_passage(char mode, const char* original_passage);

#endif //TYPINGTEST_TEXTREADING_H
