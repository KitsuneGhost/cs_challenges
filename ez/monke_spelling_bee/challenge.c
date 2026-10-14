#include <stdio.h>

extern char *gets(char *s);

void setup() {
    setbuf(stdout, NULL);
    setbuf(stdin, NULL);
    setbuf(stderr, NULL);
}

void win() {
    puts("BANANA??? BANANA!!!");

    FILE *flag = fopen("/app/flag.txt", "r");

    if (!flag) {
        puts("MONKE CANT READ FLAG :(");
        return;
    }

    char flag_buffer[128];

    if (fgets(flag_buffer, sizeof(flag_buffer), flag)) {
        puts(flag_buffer);
    }

    fclose(flag);
}

int main() {
    char buff[64];
    char option[8];

    setup();

    puts("Monke Spelling Bee");
    puts("Give monke words and monke will spell them!");
    puts("Monke has no secrets!");
    puts("It's just a monke!");

    printf("Wanna play? (Y/N) ");

    if (!fgets(option, sizeof(option), stdin))
        return 1;

    while (option[0] == 'Y' || option[0] == 'y') {

        puts("A word for monke:");
        gets(buff);

        for (int i = 0; i < 64; i++) {
            printf("%c ", buff[i]);
        }

        puts("");

        printf("Wanna play again? ");

        if (!fgets(option, sizeof(option), stdin))
            break;
    }

    puts("MONKE GO SLEEP");
    return 0;
}
