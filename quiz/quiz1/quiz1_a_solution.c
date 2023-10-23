#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define LIST_START 0
#define LIST_END 5

typedef struct
{
    int data;
    intptr_t link;
} xorlist_t;

void dump_list(xorlist_t *pt)
{
    intptr_t prev = (intptr_t)NULL;

    while (pt)
    {
        printf("%d\n", pt->data);
        xorlist_t *current = pt;
        /* Decode xored pointers with last node's address to find next */
        pt = (xorlist_t *)(pt->link ^ prev);
        prev = (intptr_t)current;
    }
}

/* insert head */
void insert_head(xorlist_t **head, int data)
{
    xorlist_t *new_node = malloc(sizeof(xorlist_t));
    new_node->data = data;

    if (!*head)
    {
        new_node->link = (intptr_t)NULL;
    }
    else
    {
        /* Update original link of head node */
        (*head)->link = (*head)->link /* Fill Your Code */ ^ (intptr_t)new_node;
        new_node->link = (intptr_t)*head /* Fill Your Code */;
    }

    *head = new_node;
}

/* remove a node from head */
void remove_head(xorlist_t **head)
{
    if (!(*head))
        return;

    xorlist_t *tmp = (xorlist_t *)(*head)->link;
    /* Update the link of new head */
    if (tmp)
        tmp->link ^= (intptr_t)*head /* Fill Your Code */;
    free(*head);
    *head = tmp;
}

void release_list(xorlist_t *pt)
{
    intptr_t prev = (intptr_t)NULL;
    while (pt)
    {
        xorlist_t *current = pt;
        pt = (xorlist_t *)(pt->link ^ prev);
        prev = (intptr_t)current /* Fill Your Code */;
        free(current);
    }
}

int main()
{
    xorlist_t *head = malloc(sizeof(xorlist_t)), *tail;
    xorlist_t *pt = head;
    intptr_t last_node = (intptr_t)NULL;
    for (int c = LIST_START; c < LIST_END; ++c)
    {
        xorlist_t *new_node = malloc(sizeof(xorlist_t));
        *pt = (xorlist_t){.data = c, .link = (intptr_t)new_node ^ last_node};
        last_node = (intptr_t)pt;
        pt = new_node;
    }
    *pt = (xorlist_t){.data = LIST_END, .link = last_node ^ (intptr_t)NULL};
    tail = pt;

    insert_head(&head, 99);
    dump_list(head);

    remove_head(&tail);
    dump_list(tail);

    release_list(head);

    return 0;
}