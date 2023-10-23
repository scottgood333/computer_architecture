#include <assert.h>
#include <stdlib.h>

struct list_node
{
    int val;
    struct list_node *next;
};

struct list_node *reverse(struct list_node **head /* Fill Your Code */)
{
    struct list_node *next = NULL, *ret;
    while (*head)
    {
        ret = malloc(sizeof(struct list_node));
        ret->val = (*head)->val /* Fill Your Code */;
        ret->next = next /* Fill Your Code */;
        next = ret /* /* Fill Your Code */;
        *head = (*head)->next;
    }
    return ret;
}

/* Assume that NEW_LL_1234() properly malloc’s a linked list
 * 1 -> 2 -> 3 -> 4, and returns a pointer that points to the first
 * list_node in the linked list. Assume that before test_reverse
 * returns, head and ret will be properly freed.
 */
void test_reverse()
{
    struct list_node *head = NEW_LL_1234();
    assert(head->val == 1);       /* returns True */
    assert(head->next->val == 2); /* returns True */
    struct list_node *ret = reverse(&head);
    assert(head != ret);   /* ret is a new copy of the original list */
    assert(ret->val == 4); /* should return True */
}