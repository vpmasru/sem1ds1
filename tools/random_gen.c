#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int get_random_value(void)
{
    // Generates a random value between 1 and 1,000,000
    return rand() % 1000000 + 1;
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number_of_values>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int num = atoi(argv[1]);

    // Seed the random number generator with the current time
    srand(time(NULL));

    for (int i = 0; i < num; i++) {
        int random_val = get_random_value();
        printf("%d,", random_val);
    }

    printf("\n");

    return 0;
}
