#include <stdio.h>
#include <stdlib.h>

#define max 100

struct stack {
    char items[max];
    int top;
};

void initialize(struct stack *s);
void push(struct stack *s, char item);
char pop(struct stack *s);
int Empty(struct stack *s);
int func(char *text);

int main(int argc, char *argv[]) {

    FILE *file = fopen("text.txt", "r");
    if (!file) {
        perror("File does not open! ");
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    int fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *text = (char *)malloc(fileSize + 1);

    fread(text, 1, fileSize, file);
    text[fileSize] = '\0';

    fclose(file);

    struct stack myStack;
    initialize(&myStack);

    if (func(text)) {
        printf("Brackets work correctly\n");
    } else {
        printf("Brackets have mistakes\n");
    }

    free(text);

    return EXIT_SUCCESS;
}

void initialize(struct stack *s) {
    s->top = -1;
}

void push(struct stack *s, char item) {
    if (s->top == max - 1)
        printf("Stack is full, push process does not work! \n");

    s->items[++s->top] = item;
}

char pop(struct stack *s) {
    if (s->top == -1)
        printf("Stack is empty, pop process does not work! \n");

    return s->items[s->top--];
}

int Empty(struct stack *s) {
    return s->top == -1;
}

int func(char *text) {
    struct stack myStack;
    initialize(&myStack);

    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == '(' || text[i] == '{' || text[i] == '[')
            push(&myStack, text[i]);
        else if (text[i] == ')' || text[i] == '}' || text[i] == ']') {
            if (Empty(&myStack))
                return 0;
            char openbracket = pop(&myStack);
            if (text[i] == ')' && openbracket != '(' || text[i] == '}' && openbracket != '{' || text[i] == ']' && openbracket != '[')
                return 0;
        }
    }

    return Empty(&myStack) == 1;
}
