//
// Created by shantanu on 3/9/16.
//

#include "location_counter.h"
#include <stdlib.h>

void step_update_LC(location_counter *LC, long long int op_length) {
    LC->previous_line->next = (location_count *) malloc(sizeof(location_count));
    LC->previous_line->next->count = LC->previous_line->count + op_length;
    LC->previous_line = LC->previous_line->next;
    LC->previous_line->next = NULL;
    return;
}


