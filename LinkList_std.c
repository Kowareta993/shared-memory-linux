#include <stdio.h>
#include "Node_std.h"

int main(){

    struct Node *head = NULL;
    for (int i = 0; i < 8; i++)
    {
        Add(&head,"Melika_zamani",i,i);
    }
    for (int i = 0; i < 8; i++)
    {
        remove_node(&head,"Melika_zamani",i);
    }
    for (int i = 0; i < 4; i++)
    {
        Add(&head,"Melika_zamani",5-i,5-i);
    }
    Add(&head,"Melika_zamani",10,10);
    Add(&head,"Melika_zamani",0,0);
    sort(&head);
    PrintList(&head);
	
    printf("%s", "\n");
    return 0; 
}
