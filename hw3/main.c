#include <stdio.h>
#include <string.h>

#define MAX_LEN 1000

#define TOKEN_NUM 1
#define TOKEN_PLUS 2
#define TOKEN_LPAREN 3
#define TOKEN_RPAREN 4
#define TOKEN_END 5
#define TOKEN_ERROR 6

char input[MAX_LEN];
int pos = 0;
int token;
char numLexeme[MAX_LEN];
int errorFlag = 0;

void getToken();
void parse_S();
void parse_S_prime();
void parse_E();
void printIndent(int level);

int level = 0;

void printIndent(int level) {
    int i;
    for (i = 0; i < level; i++) {
        printf("  ");
    }
}

void getToken() {
    int i = 0;

    while (input[pos] == ' ' || input[pos] == '\n' || input[pos] == '\t') {
        pos++;
    }

    if (input[pos] == '\0') {
        token = TOKEN_END;
    }
    else if (input[pos] >= '0' && input[pos] <= '9') {
        while (input[pos] >= '0' && input[pos] <= '9') {
            numLexeme[i++] = input[pos++];
        }
        numLexeme[i] = '\0';
        token = TOKEN_NUM;
    }
    else if (input[pos] == '+') {
        pos++;
        token = TOKEN_PLUS;
    }
    else if (input[pos] == '(') {
        pos++;
        token = TOKEN_LPAREN;
    }
    else if (input[pos] == ')') {
        pos++;
        token = TOKEN_RPAREN;
    }
    else {
        token = TOKEN_ERROR;
    }
}

void parse_S() {
    if (errorFlag) return;

    switch (token) {
        case TOKEN_NUM:
        case TOKEN_LPAREN:
            printIndent(level);
            printf("S -> E S'\n");

            level++;
            parse_E();
            parse_S_prime();
            level--;
            return;

        default:
            errorFlag = 1;
            return;
    }
}

void parse_S_prime() {
    if (errorFlag) return;

    switch (token) {
        case TOKEN_PLUS:
            printIndent(level);
            printf("S' -> + S\n");

            level++;
            printIndent(level);
            printf("+\n");

            getToken();
            parse_S();
            level--;
            return;

        case TOKEN_RPAREN:
        case TOKEN_END:
            printIndent(level);
            printf("S' -> epsilon\n");
            return;

        default:
            errorFlag = 1;
            return;
    }
}

void parse_E() {
    if (errorFlag) return;

    switch (token) {
        case TOKEN_NUM:
            printIndent(level);
            printf("E -> num\n");

            level++;
            printIndent(level);
            printf("%s\n", numLexeme);
            level--;

            getToken();
            return;

        case TOKEN_LPAREN:
            printIndent(level);
            printf("E -> ( S )\n");

            level++;
            printIndent(level);
            printf("(\n");

            getToken();
            parse_S();

            if (token != TOKEN_RPAREN) {
                errorFlag = 1;
                return;
            }

            printIndent(level);
            printf(")\n");

            getToken();
            level--;
            return;

        default:
            errorFlag = 1;
            return;
    }
}

int main() {
    printf("Input expression: ");
    fgets(input, MAX_LEN, stdin);

    input[strcspn(input, "\n")] = '\0';

    getToken();
    parse_S();

    if (token != TOKEN_END) {
        errorFlag = 1;
    }

    if (errorFlag) {
        printf("Invalid input\n");
    } else {
        printf("Valid input\n");
    }

    return 0;
}