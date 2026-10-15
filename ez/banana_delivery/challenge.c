#include <stdio.h>
#include <string.h>

extern char *gets(char *s);

int main(void) {
    struct {
        char label[32];
        char destination[16];
    } parcel;

    strcpy(parcel.destination, "zoo");
    setbuf(stdout, NULL);

    puts("=== Banana Delivery ===");
    puts("Monke ordered bananas for the treehouse!");
    puts("But the delivery monke wrote the wrong destination.");
    printf("Write a parcel label: ");

    if (!gets(parcel.label))
        return 1;

    if (strcmp(parcel.destination, "treehouse") != 0) {
        puts("Wrong destination. Monke is still hungry :(");
        return 0;
    }

    puts("Bananas delivered to the treehouse!");

    FILE *flag = fopen("/app/flag.txt", "r");
    if (!flag) {
        puts("Monke lost the delivery receipt :(");
        return 1;
    }

    char flag_buffer[128];
    if (fgets(flag_buffer, sizeof(flag_buffer), flag))
        puts(flag_buffer);

    fclose(flag);
    return 0;
}
