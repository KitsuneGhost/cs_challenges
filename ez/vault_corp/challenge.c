#include <stdio.h>

extern char *gets(char *s);

int main(void) {
    struct {
        char username[32];
        int is_admin;
    } user;

    user.is_admin = 0;

    setbuf(stdout, NULL);

    printf("[+] A simplified credentials system for VaultCorp employees!\n");
    printf("[+] It was made fully in C, which makes it balzingly fast!\n");
    printf("[+] Don't worry, I tested it with my own username and it works perfectly!\n");

    printf("[+] Please enter your username:\n");
    gets(user.username);

    if (user.is_admin) {
        printf("[!] Admin Access granted!\n");

        FILE *flag = fopen("/app/flag.txt", "r");
        if (!flag) {
            puts("[!] Error reading flag.");
            return 1;
        }

        char buffer[128];

        if (fgets(buffer, sizeof(buffer), flag)) {
            puts(buffer);
        }

        fclose(flag);


    } else {
        printf("[!] Login successfull!\n");
    }

    return 0;
}
