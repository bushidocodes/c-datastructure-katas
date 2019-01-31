#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STRING 100

// Give an algorithm that determines if the input parentheses are valid. For example, given input “()”, your
// algorithm should return true. Whereas given input “(]”, your algorithm should return false. You can
// assume the given string only contains characters ‘(’, ‘)’, ‘[’, ‘]’, ‘{’, ‘}’.

char matches[3][2] = {"()", "[]", "{}"};

/* Returns -1 if not paren, 0 if opening paren, 1 if closing paren */
int isAParen(char charToCheck)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (charToCheck == matches[i][j])
            {
                return j;
            }
        }
    }
    return -1;
}

/* given a closing paren, returns the associated opening paren */
char findMatch(char charToCheck)
{
    for (int i = 0; i < 3; i++)
    {
        if (charToCheck == matches[i][1])
            return matches[i][0];
    }
    return '\0';
}

bool isValidParens(char *stringToCheck)
{
    char stackOfParens[MAX_STRING];
    int len_stackOfParens = 0;
    for (int i = 0; i < strlen(stringToCheck); i++)
    {
        if (isAParen(stringToCheck[i]) == 0) /* Add opening parentheses to the stack */
        {
            stackOfParens[len_stackOfParens] = stringToCheck[i];
            len_stackOfParens++;
        }
        else if (isAParen(stringToCheck[i]) == 1) /* Compare closing parentheses to the opening parenteses on the top of the stack */
        {
            if (findMatch(stringToCheck[i]) == stackOfParens[len_stackOfParens - 1])
            {
                len_stackOfParens--; /* If match, pop opening paren off the stack*/
            }
            else
            {
                return false; /* If no match, string is invalid */
            }
        }
    }

    return len_stackOfParens == 0; /* If any opening parens weren't closed, string is invalid */
}

int main(int argc, char *argv[])
{
    char buffer_str[MAX_STRING];
    fgets(buffer_str, MAX_STRING, stdin); /* Store STDIN to buffer_str */
    strtok(buffer_str, "\n");             /* Strip off the training NEWLINE */
    bool result = isValidParens(buffer_str);
    printf(result ? "Valid\n" : "Not Valid\n");
}