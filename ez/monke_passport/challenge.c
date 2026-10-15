#include <stdio.h>

extern char *gets(char *s);

int main(void) {
    struct {
        char name[32];
        unsigned int species;
    } passport;

    passport.species = 0;

    setbuf(stdout, NULL);

    puts("=== Monke Passport ===");
    puts("Welcome to the jungle border!");
    puts("Only certified monkes may enter the banana kingdom.");
    printf("Name on passport: ");

    if (!gets(passport.name))
        return 1;

    printf("Species code: 0x%08x\n", passport.species);

    if (passport.species != 0x454b4e4d) {
        puts("That is not a monke passport. No bananas for you!");
        return 0;
    }

    puts("Certified monke! Welcome to the banana kingdom!");

    FILE *flag = fopen("/app/flag.txt", "r");
    if (!flag) {
        puts("Monke lost the entry stamp :(");
        return 1;
    }

    char flag_buffer[128];
    if (fgets(flag_buffer, sizeof(flag_buffer), flag))
        puts(flag_buffer);

    fclose(flag);
    return 0;
}
