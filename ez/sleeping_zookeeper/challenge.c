#include <stdio.h>
#include <stdlib.h>

extern char *gets(char *s);

void win(void) {
    puts("Zookeeper is asleep! The secret banana stash is yours!");
    FILE *flag = fopen("/app/flag.txt", "r");
    if (!flag) {
        puts("Monke can't find the secret bananas :(");
        exit(1);
    }

    char flag_buffer[128];
    if (fgets(flag_buffer, sizeof(flag_buffer), flag))
        puts(flag_buffer);

    fclose(flag);
    exit(0);
}

int main(void) {
    char excuse[64];

    setbuf(stdout, NULL);

    puts("=== Sleeping Zookeeper ===");
    puts("The zookeeper is guarding the secret banana stash.");
    puts("Monke needs a really good excuse to get past...");
    printf("Tell the zookeeper your excuse: ");

    if (!gets(excuse))
        return 1;

    puts("Nice try, monke. Back to your tree!");
    return 0;
}
