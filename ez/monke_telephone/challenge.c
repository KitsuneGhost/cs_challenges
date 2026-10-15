#include <stdio.h>
#include <stdlib.h>

extern char *gets(char *s);

void wrong_number(void) {
    puts("Wrong number! No bananas on this line.");
}

void banana_delivery(void) {
    puts("Banana hotline! Your secret order is ready!");
    FILE *flag = fopen("/app/flag.txt", "r");
    if (!flag) {
        puts("Monke can't find the secret bananas :(");
        exit(1);
    }

    char flag_buffer[128];
    if (fgets(flag_buffer, sizeof(flag_buffer), flag))
        puts(flag_buffer);

    fclose(flag);
}

int main(void) {
    struct {
        char message[32];
        void (*callback)(void);
    } call;

    call.callback = wrong_number;
    setbuf(stdout, NULL);

    puts("=== Monke Telephone ===");
    puts("Monke wants to call the banana hotline.");
    printf("Leave a message: ");

    if (!gets(call.message))
        return 1;

    puts("Connecting monke...");
    call.callback();
    return 0;
}
