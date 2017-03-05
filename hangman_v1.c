#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <unistd.h>

int j=0;
int correct[100];

void clear(void);
void greet(void);
void bdraw(char *y, int x);
bool check(char *y, int z, char *x);
void right(char *y, int z, char *x);
bool won(int z);
int main(void)
{
    greet();
    printf("Please enter a word: ");
    char *answer = get_string();
    
    printf("Your word is: %s\n", answer);
    printf("The board will clear now.\n");
    
    int len = strlen(answer);
    
    clear();
    
    char guess;
    int remain = 5;
    
    char draw[len];
    for (int i=0; i<len; i++)
    {
        draw[i] = answer[i];
    }
    
    while (true)
    {
        
        
        // draw current state of the board
        for (int i=0; i<len; i++)
        {
            if (correct[i] == 0)
            {
                printf("_ ");
            }
            else
            {
                printf("%c ", draw[i]);
            }
        }
        
        printf("\n");
        
        printf("Guess left: %i\n", remain);
        printf("Enter your guess: ");
        guess = get_char();
        
        if (check(&guess, len, draw) == false)
        {
            remain--;
            if (remain == 0)
            {
                printf("You lost the game!\n");
                return 0;
            }
            else
            {
                printf("Incorrect guess, %i try left.\n", remain);
            }

        }
        else
        {
            right(&guess, len, draw);
        }
        
        if (won(len) == true)
        {
            printf("Congratulations! You have won!\n");
            return 0;
        }
        
    }
}

void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

void greet(void)
{
    clear();
    printf("WELCOME TO THE QUIZ GAME\n");
    usleep(2000000);
}

void bdraw(char *y, int x)
{
    for (int i=0; i<x; i++)
    {
        printf("%c ", y[i]);
    }
    printf("\n");
}

bool check(char *y, int z, char *x)
{
    for (int i=0; i<z; i++)
    {
        if (*y == x[i])
        {
            return true;
        }
    }
    
    return false;
}

void right(char *y, int z, char *x)
{
    for (int i=0; i<z; i++)
    {
        if (*y == x[i])
        {
            j = i;
            correct[j] = i+1;
        }
    }
}

bool won(int z)
{
    for (int i=0; i<z; i++)
    {
        if (correct[i] == 0)
        {
            return false;
        }
    }
    
    return true;
}
