#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
   struct node *right;
   struct node *left;
   int data;
}node_t;

int *sorted_data(node_t *tree);
void free_tree(node_t *tree);
void in_order(node_t *head, int *array, int *count);
int node_count(node_t *head);
int insert_node(int data, node_t **head);
node_t *node_create(int data);

int main (void)
{
    int n, i, numero, count;
    node_t *tree=NULL;
    scanf("%d", &n);
    for (i=0; i<n; i++)
    {
        scanf("%d", &numero);
        count = insert_node(numero, &tree);
        printf("%d\n", count);
    }
}

node_t *node_create(int data)
{
    node_t *node = (node_t*) malloc(sizeof(node_t));
    node->left = NULL;
    node->right = NULL;
    node->data = data;
    return node;
}

int insert_node(int data, node_t **head)
{
    int count=0;
    if(*head ==NULL)
    {
        *head = node_create(data);
        return count;
    }
    else
    {
        if(data < (*head)->data)
        {
            count = insert_node(data, &(*head)->left)+1;
        }
        else
        {
            if(data>(*head)->data)
            {
                count = insert_node(data, &(*head)->right)+1;
            }
        }
    }
    return count;
}

int node_count(node_t *head)
{
    if(head == NULL)
    {
        return 0;
    }
    int count_left = node_count(head->left);
    int count_right = node_count(head->right);
    return 1+count_left+count_right;
}

void in_order(node_t *head, int *array, int *count)
{
    if(head == NULL)
    {
        return;
    }
    in_order(head->left, array, count);
    int i = *count;
    *(array+i) = head->data;
    (*count)++;
    in_order(head->right, array, count);
}


void free_tree(node_t *tree)
{
    if(tree==NULL)
    {
        return;
    }
    free_tree(tree->left);
    free_tree(tree->right);
    free(tree);
}