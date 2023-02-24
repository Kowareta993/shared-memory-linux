#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node
{
    char value[200];
    long key;
    int index;
    struct Node *next;
};

