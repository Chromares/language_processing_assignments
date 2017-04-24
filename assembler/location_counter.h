//
// Created by shantanu on 3/9/16.
//

#ifndef ASSEMBLER_2PASS_LOCATION_COUNTER_H
#define ASSEMBLER_2PASS_LOCATION_COUNTER_H

typedef struct location_count {
    long long int count;
    struct location_count *next;
}location_count;

typedef struct location_counter {
    struct location_count *head;
    long long int length;
    struct location_count *previous_line;
}location_counter;

void step_update_LC(location_counter *LC, long long int op_length);


#endif //ASSEMBLER_2PASS_LOCATION_COUNTER_H
