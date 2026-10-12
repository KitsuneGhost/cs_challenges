#include <stdio.h>

extern char* gets(char* s);


void setup() {
    setbuf(stdout, NULL);
    setbuf(stdin, NULL);
    setbuf(stderr, NULL);
}


int win() {
    printf("BANANA??? BANANA!!!");

    FILE *flag = fopen("/app/flag.txt", "r");
    if (!flag) {
        puts("MONKE CANT READ FLAG :(");
        return 1;
    }

    char flag_buffer[128];
    if (fgets(flag_buffer, sizeof(flag_buffer), flag)) {
        puts(flag_buffer);
    }

    fclose(flag);
    return 1;
}


int main(void) {
    char buff[64];
    char option[2];

    setup();

    printf("Monke Spelling Bee\n");
    printf("Give monke words and monke will spell them!\n");
    printf("Monke has no secrets!\n");
    printf("It's just a monke!\n");

    printf("Wanna play? (Y/N)");
    scanf("%s", option);

    while (option == "Y\n" || option == "y\n") {

        printf("A word for monke: \n");
        gets(buff);

        for (int i = 0; i < 64; i++) {
            printf("%c ", buff[i]);
        }

        printf("\n");

        printf("Wanna play again?");
        scanf("%s", option);

        return 0;
    }
}
