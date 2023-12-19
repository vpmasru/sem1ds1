#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

void help_msg(const char *exec_name)
{
    printf("Usage: %s [-v] [file]\n", exec_name);
}

int main(int argc, char *argv[]) {
    int opt;
    int debug_flag = 0;
    int rc = EXIT_SUCCESS;

    while ((opt = getopt(argc, argv, "dh")) != -1) {
        switch (opt) {
            case 'v':
                debug_flag = 1;
                break;
            case 'h':
                help_msg(argv[0]);
                exit(EXIT_SUCCESS);
                break;
            default:
                help_msg(argv[0]);
                exit(EXIT_FAILURE);
                break;
        }
    }

    // Display options
    if (debug_flag) {
        printf("Verbose mode is enabled.\n");
    }

    // Display remaining arguments (non-option arguments)
    for (int i = optind; i < argc; i++) {
        printf("Non-option argument: %s\n", argv[i]);
    }

    return rc;
}
