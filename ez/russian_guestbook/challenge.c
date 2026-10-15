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

/* Intentionally vulnerable: the caller budgets input bytes, not output bytes. */
static void to_utf8(char *dst, const unsigned char *src, size_t n) {
    size_t out = 0;

    for (size_t i = 0; i < n; ++i) {
        uint32_t cp = src[i];

        if (cp >= 0xc0) cp = 0x0410 + cp - 0xc0;
        else if (cp == 0xa8) cp = 0x0401;
        else if (cp == 0xb8) cp = 0x0451;

        if (cp < 0x80) dst[out++] = (char)cp;
        else {
            dst[out++] = (char)(0xc0 | (cp >> 6));
            dst[out++] = (char)(0x80 | (cp & 0x3f));
        }
    }

    dst[out] = 0;
}

int main(void) {
    struct {
        char text[32];
        uint32_t seal;
        char spare[64];
    } entry;

    _Static_assert(offsetof(__typeof__(entry), seal) == 32, "unexpected layout");

    unsigned char input[64];
    memset(&entry, 0, sizeof(entry));
    setbuf(stdout, NULL);

    puts("=== Гостевая книга ===");
    puts("Our old terminal uses Windows-1251. ASCII and Russian letters only.");
    puts("Messages may contain at most 31 input bytes.");
    printf("Message: ");

    if (!fgets((char *)input, sizeof(input), stdin)) return 1;
    size_t n = strcspn((char *)input, "\n");

    if (n > 31) { puts("Message too long."); return 0; }

    for (size_t i = 0; i < n; ++i)
        if (input[i] >= 0x80 && input[i] < 0xc0 && input[i] != 0xa8 && input[i] != 0xb8) {
            puts("Unsupported Windows-1251 byte."); return 0;
        }

    to_utf8(entry.text, input, n);
    printf("Archive seal: 0x%08x\n", entry.seal);

    if (entry.seal == UINT32_C(0x91d091d0)) {
        puts("Архив открыт! / Archive unlocked!"); show_flag();
    }
    else puts("The archive remains sealed.");

    return 0;
}
