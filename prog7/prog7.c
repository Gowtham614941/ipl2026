#include <stdio.h>
#include <string.h>

#define MAX_TEXT_LEN 1024
#define MAX_PAT_LEN 256

// 1. Precompute the LPS (Longest Proper Prefix which is also Suffix) array
void computeLPSArray(const char *pattern, int M, int *lps) {
    int len = 0; // Length of the previous longest prefix suffix
    lps[0] = 0;  // lps[0] is always 0
    int i = 1;

    while (i < M) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// 2. KMP Search function: Returns the first matching index, or -1 if not found
int KMPSearch(const char *text, const char *pattern) {
    int N = strlen(text);
    int M = strlen(pattern);

    // Edge case: empty pattern
    if (M == 0) return 0;

    // Create dynamic lps array to hold prefix values
    int lps[M];
    computeLPSArray(pattern, M, lps);

    int i = 0; // Index for text[]
    int j = 0; // Index for pattern[]
    
    while (i < N) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == M) {
            return i - j; // Pattern found!
        }
        else if (i < N && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    
    return -1; // Pattern not found
}

// Helper function to safely strip trailing newline characters
void stripNewline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

int main() {
    char text[MAX_TEXT_LEN];
    char pattern[MAX_PAT_LEN];

    // Get Text Input
    printf("Enter the main text: ");
    if (fgets(text, sizeof(text), stdin) == NULL) {
        printf("Error reading text.\n");
        return 1;
    }
    stripNewline(text);

    // Get Pattern Input
    printf("Enter the substring pattern to find: ");
    if (fgets(pattern, sizeof(pattern), stdin) == NULL) {
        printf("Error reading pattern.\n");
        return 1;
    }
    stripNewline(pattern);

    // Run KMP Search
    int index = KMPSearch(text, pattern);

    printf("\n--- Result ---\n");
    if (index != -1) {
        printf("Pattern found at index: %d\n", index);
    } else {
        printf("Pattern not found in the given text.\n");
    }

    return 0;
}