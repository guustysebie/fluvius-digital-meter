//
// Created by GuustYsebie on 31/05/2023.
//

#ifndef FLUVIUSSM_TEST_UTIL_H
#define FLUVIUSSM_TEST_UTIL_H

#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */


int compare_str(char *a, char *b) {
    unsigned int len1 = strlen(a);
    unsigned int len2 = strlen(b);
    if (len1 != len2) {
        return 1;
    }
    for (int i = 0; i < len1; ++i) {
        if (a[i] != b[i]) {
            return 1;
        }
    }

    return 0;
}

char *extract_file_name(char *path) {
    unsigned int len = strlen(path);
    unsigned int idx = 0;
    for (unsigned int i = len; i > 0; --i) {
        if (path[i] == '\\' || path[i] == '/') {
            idx--;
            break;
        }
        idx++;
    }
    char *name = malloc(sizeof(char) * len - idx + 1);
    unsigned int ctr = 0;
    for (unsigned int i = len - idx; i < len; ++i) {
        name[ctr++] = path[i];
    }
    name[ctr++] = '\0';
    return name;


}

char* format_str_inequality_result(char* a, char* b, unsigned  max_length){
    size_t nbytes = snprintf(NULL, 0, "\"%s\" != \"%s\"", a,b) + 1; /* +1 for the '\0' */
    if(nbytes > max_length){
        return "Result to long";
    }
    char *str = malloc(nbytes);
    snprintf(str, nbytes, "\"%s\" != \"%s\"", a,b);
    return str;
}

#define FDM_ASSERT_STR(a, b) if(compare_str(a,b)){ \
                char* result = format_str_inequality_result(a,b, 40) ;              \
                char* file_name =     extract_file_name( __FILE__);    \
                printf(RED "[WARN] %-25s | %-40s | LOCATION: %s:%d %s\n", __func__,result ,file_name , __LINE__ , RESET); \
                free(file_name) ;                                      \
                }

#define FDM_ASSERT_INT(a, b) if(a != b){           \
                char* file_name =     extract_file_name( __FILE__);    \
                printf(RED "[WARN] %-25s | %d != %d  LOCATION  %s %d %s\n", __func__ ,a,b, file_name , __LINE__ , RESET);                     \
                free(file_name) ;                                      \
                return 1;                      \
                }


#define FDM_ASSERT_OK() return 0;

#endif //FLUVIUSSM_TEST_UTIL_H
