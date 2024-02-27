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
void insert_node(int data, node_t **head);
node_t *node_create(int data);
int existe(node_t *head, int x);

int main()
{
    int n, m, i, j, numero, bandera = 0;
    int count=0;
    int *array_1=NULL;
    int *array_2=NULL;
    node_t *tree_1 = NULL;
    node_t *tree_2 = NULL;
    scanf("%d %d", &n, &m);

    for(i=0; i<n; i++)
    {
        scanf("%d", &numero);
        insert_node(numero, &tree_1);
    }
    for(i=0; i<m; i++)
    {
        scanf("%d", &numero);
        insert_node(numero, &tree_2);
    }
    if(n<m)
    {
        array_1 = sorted_data(tree_1);//n
        for(i = 0; i<n; i++)
        {
            count+=existe(tree_2, *(array_1+i));
        }
        if(count == n)
        {
            printf("A < B");
        }
        else
        {
            printf("A != B");
        }
    }

    if(n>m)
    {
        array_2 = sorted_data(tree_2);//m
        count = 0;
        for(i = 0; i<m; i++)
        {
            count=count+existe(tree_1, *(array_2+i));
        }
        if(count == m)
        {
            printf("A > B");
        }
        else
        {
            printf("A != B");
        }
    }
    if(n==m)
    {
        array_1 = sorted_data(tree_1);//n
        array_2 = sorted_data(tree_2);//m
        for(j = 0; j<m; j++)
        {
            if(*(array_1+j) != *(array_2+j))
                {
                    bandera = 1;
                }
        }
        if(bandera==0)
        {
            printf("A = B");
        }
        else
        {
            printf("A != B");
        }
    }
    free(tree_1);
    free(tree_2);
}

node_t *node_create(int data)
{
    node_t *node = (node_t*) malloc(sizeof(node_t));
    node->left = NULL;
    node->right = NULL;
    node->data = data;
    return node;
}

void insert_node(int data, node_t **head)
{
    if(*head ==NULL)
    {
        *head = node_create(data);
    }
    else
    {
        if(data < (*head)->data)
        {
            insert_node(data, &(*head)->left);
        }
        else
        {
            if(data>(*head)->data)
            {
                insert_node(data, &(*head)->right);
            }
        }
    }
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

node_t *build_tree(int *tree_data, size_t tree_data_len)
{
    node_t *head = NULL;
    size_t i;
    for(i=0; i<tree_data_len; i++)
    {
        insert_node(tree_data[i], &head);
    }
    return head;
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

int *sorted_data(node_t *tree)
{
    int count=0;
    int size = node_count(tree);
    int *array = (int*)malloc(sizeof(int)*size);
    in_order(tree, array, &count);
    return array;
}

int existe(node_t *head, int x)
{
    while (head != NULL)
    {
        if(head->data==x)
        {
            return 1;
        }
        else if(x<head->data)
        {
            head = head->left;
        }
        else
        {
            head = head->right;
        }
    }
    return 0;
}