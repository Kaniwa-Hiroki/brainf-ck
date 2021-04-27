#include <stdio.h>

#define MEMORY_SIZE 10000
#define INPUT_SIZE 10000

char memory[MEMORY_SIZE];
char input[INPUT_SIZE];
int head = 0;
int input_head = 0;
int input_length = 0;

void init_memory(void);
void bf_rules(char character);

int main(int argc, char *argv[])
{
    FILE *fp;
    char character;

    init_memory();

    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("error: file not found.\n");
        return 0;
    }
    else
    {
        while ((character = fgetc(fp)) != EOF)
        {
            if (character == '+' ||
                character == '-' ||
                character == '>' ||
                character == '<' ||
                character == '[' ||
                character == ']' ||
                character == '.' ||
                character == ',')
            {
                input[input_head] = character;
                input_head++;
            }
        }
        input_length = input_head;
        for (input_head = 0; input_head < input_length; input_head++)
            bf_rules(input[input_head]);
    }

    printf("\n");
    fclose(fp);
    return 0;
}

void init_memory(void)
{
    int i;
    for (i = 0; i < MEMORY_SIZE; i++)
        memory[i] = 0;
}

void bf_rules(char character)
{
    int block_start = 0;
    int block_end = 0;
    int bracket_count = 0;

    switch (character)
    {
    case '+':
        memory[head]++;
        break;
    case '-':
        memory[head]--;
        break;
    case '>':
        head++;
        break;
    case '<':
        head--;
        break;
    case '[':
        input_head++;
        block_start = input_head;
        while (1)
        {
            if ((input[input_head] == ']') && (bracket_count == 0))
            {
                block_end = input_head;
                break;
            }
            else if (input[input_head] == '[')
                bracket_count++;
            else if (input[input_head] == ']')
                bracket_count--;
            input_head++;
        }
        while (1)
        {
            if (memory[head] == 0)
                break;
            else
            {
                for (input_head = block_start; input_head < block_end; input_head++)
                {
                    bf_rules(input[input_head]);
                }
            }
        }
        break;
    case '.':
        printf("%c", memory[head]);
        break;
    case ',':
        scanf("%c", &memory[head]);
        break;
    default:
        break;
    }
    return;
}