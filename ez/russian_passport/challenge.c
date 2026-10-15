#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static void show_flag(void) {
    FILE *f = fopen("/app/flag.txt", "r");
    if (!f) { puts("Flag unavailable locally; use Docker for the full setup."); return; }
    char flag[128];
    if (fgets(flag, sizeof(flag), f)) puts(flag);
    fclose(f);
}

static const char *latin[32] = {
    "A", "B", "V", "G", "D", "E", "ZH", "Z", "I", "I", "K", "L", "M", "N", "O", "P",
    "R", "S", "T", "U", "F", "KH", "TS", "CH", "SH", "SHCH", "", "Y", "", "E", "YU", "YA"
};

/* A deliberately simplified house transliteration scheme, not a passport standard. */
static int transliterate(char *dst, const unsigned char *src, size_t n) {
    size_t out = 0;

    for (size_t i = 0; i < n;) {
        if (src[i] < 0x80) {
            dst[out++] = (char)src[i++]; continue;
        }

        if (i + 1 >= n || (src[i] != 0xd0 && src[i] != 0xd1) ||
            (src[i + 1] & 0xc0) != 0x80) return 0;

        unsigned cp = ((src[i] & 0x1f) << 6) | (src[i + 1] & 0x3f);
        i += 2;
        const char *s;

        if (cp == 0x401 || cp == 0x451) s = "E";
        else {
            if (cp >= 0x430 && cp <= 0x44f) cp -= 0x20;
            if (cp < 0x410 || cp > 0x42f) return 0;
            s = latin[cp - 0x410];
        }
        /* BUG: no check that the expanded spelling fits the destination. */
        while (*s) dst[out++] = *s++;
    }

    dst[out] = 0;
    return 1;
}

int main(void) {
    struct {
        char name[32];
        char stamp[9];
        char spare[96];
    } passport;

    _Static_assert(offsetof(__typeof__(passport), stamp) == 32, "unexpected layout");

    unsigned char input[64];
    memset(&passport, 0, sizeof(passport));
    memcpy(passport.stamp, "PENDING", 7);
    setbuf(stdout, NULL);

    puts("=== Паспортный стол ===");
    puts("Enter a Russian name in UTF-8 (at most 31 input bytes).");
    puts("Our house alphabet writes Щ as SHCH. ASCII is accepted too.");
    printf("Name: ");

    if (!fgets((char *)input, sizeof(input), stdin)) return 1;
    size_t n = strcspn((char *)input, "\n");

    if (n > 31) { puts("Name too long."); return 0; }
    if (!transliterate(passport.name, input, n)) { puts("Unsupported name."); return 0; }

    printf("Passport stamp: %.8s\n", passport.stamp);

    if (!memcmp(passport.stamp, "SHCHSHCH", 8)) {
        puts("Паспорт одобрен! / Passport approved!"); show_flag();
    } else puts("Please wait for approval.");

    return 0;
}
