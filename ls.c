#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    // Q1
    printf("%d argument(s) :\n", argc);
    for (size_t i = 0; i < argc; i++) {
        printf("%s\n", argv[i]);
    }

    // Q2
    int option;
   
    while((option = getopt(argc, argv, "a:bc")) != -1){
        switch(option){
        
            case 'a':
                printf("Arg de a: %s\n", optarg);
                break;
            case 'b':
            case 'c':
                printf("Option: %c\n", option);
                break;
            case '?': // option inconnue renvoyé dans optopt
                printf("option inconnue: %c\n", optopt);
                break;
        }
    }
    for(; optind < argc; optind++){
        printf("arguments supplementaires: %s\n", argv[optind]);
    }
    return 0;
}
