//
// Created by guust on 5/28/23.
//

#include <stdio.h>
#include "parser.h"


#define START_COSEM_OBJ '/'




void parse_data(char *data, size_t length) {
    for (int i = 0; i < length  ; ++i) {
       if(data[i] == START_COSEM_OBJ){
           printf("Found START OBJ: %d\n", i);
           printf("%c\n",data[i++]);
           printf("%c\n",data[i++]);
           printf("%c\n",data[i++]);

       }
    }
}

void test_data() {
    printf("Hello from lib\n");
}
