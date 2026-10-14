#include <stdio.h>

extern char *gets(char *s);

int main() {
    struct {
        char name[32];
        unsigned int bananas;
    } monke;

    monke.bananas = 0;

    setbuf(stdout, NULL);

    puts("=== Banana Counter ===");
    puts("Monke wants to join the 100 Banana Club!");
    puts("But monke has no bananas :(");
    printf("What is monke's name? ");

    if (!gets(monke.name))
        return 1;

    printf("Bananas: %u\n", monke.bananas);

    if (monke.bananas < 100) {
        puts("Not enough bananas. No club for monke :(");
        return 0;
    }

    puts("SO MANY BANANAS! Welcome to the club!");

    FILE *flag = fopen("/app/flag.txt", "r");
    if (!flag) {
        puts("Monke can't find the secret banana stash :(");
        return 1;
    }

    char flag_buffer[128];
    if (fgets(flag_buffer, sizeof(flag_buffer), flag))
        puts(flag_buffer);

    fclose(flag);
    return 0;
}
