#include <stdio.h>

extern char *gets(char *s);

int main(void) {
    char username[32];
    int is_admin = 0;

    printf("[+] A simplified credentials system for VaultCorp employees!\n");
    printf("[+] It was made fully in C, which makes it balzingly fast!\n");
    printf("[+] Don't worry, I tested it with my own username and it works perfectly!\n");

    printf("[+] Please enter your username:\n");
    gets(username);

    if (is_admin) {
        printf("[!] Admin Access granted!\n");
        printf("bruh{flag_example}");
    } else {
        printf("[!] Login successfull!\n");
    }

    return 0;
}
