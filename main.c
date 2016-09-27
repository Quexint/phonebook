#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include IMPL

#define DICT_FILE "./dictionary/words.txt"

#define MAX_NUMBER 500000

char last_name_record[MAX_NUMBER][MAX_LAST_NAME_SIZE];

int max(int a, int b)
{
    return a > b ? a : b;
}

static double diff_in_second(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec-t1.tv_nsec < 0) {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}

int main(int argc, char *argv[])
{
    FILE *fp;
    int i, n;
    struct timespec start, end;
    double cpu_time1, cpu_time2;

    /* check file opening */
    fp = fopen(DICT_FILE, "r");
    if (fp == NULL) {
        printf("cannot open the file\n");
        return -1;
    }

    /* Save input to last_name_record */
    for(n = 0; fgets(last_name_record[n], sizeof(char) * MAX_LAST_NAME_SIZE, fp); n++) {
        i = 0;
        while(last_name_record[n][i] != '\0')
            i++;
        last_name_record[n][i - 1] = '\0';
    }
    /* close file as soon as possible */
    fclose(fp);

    /* build the entry */
    entry *pHead, *e;
    e = pHead = init_struct();
    printf("size of entry : %lu bytes\n", sizeof(entry));


    /* Only test `append()` without I/O time. */
#if defined(__GNUC__)
    __builtin___clear_cache((char *) pHead, (char *) pHead + sizeof(entry));
#endif
    clock_gettime(CLOCK_REALTIME, &start);
    for(i = 0; i < n; i++)
        e = append(last_name_record[i], e);
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time1 = diff_in_second(start, end);

    e = pHead;

    /* Make a testing with 1% of lastNames */
    int test_num = max(n / 100, 1);
    int *test_array = (int *) malloc(sizeof(int) * test_num);
    for(i = 0; i < test_num; i++)
        test_array[i] = rand() % n;

    e = pHead;

    assert(findName(last_name_record[0], e) &&
           "Did you implement findName() in " IMPL "?");
    /* assert(0 == strcmp(findName(input, e)->lastName, "zyxel")); */

#if defined(__GNUC__)
    __builtin___clear_cache((char *) pHead, (char *) pHead + sizeof(entry));
#endif
    /* compute the execution time */
    clock_gettime(CLOCK_REALTIME, &start);
    for(i = 0; i < test_num; i++)
        assert(NULL != findName(last_name_record[test_array[i]], e));
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time2 = diff_in_second(start, end);
    assert(e != NULL);

    FILE *output;
#if defined(OPT)
    output = fopen("opt.txt", "a");
#else
    output = fopen("orig.txt", "a");
#endif
    fprintf(output, "append() findName() %lf %lf\n", cpu_time1, cpu_time2);
    fclose(output);

    printf("execution time of append() : %lf sec\n", cpu_time1);
    printf("execution time of findName() : %lf sec\n", cpu_time2);

    free_struct(pHead);

    return 0;
}
