#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct node
{
   struct node *right;
   struct node *left;
   int data;
}node_t;


node_t *minimo(node_t *head);
void erase(node_t **head, int dato);
void free_tree(node_t *tree);
void in_order(node_t *head, int *array, int *count);
int node_count(node_t *head);
void insert_node(int data, node_t **head);
node_t *node_create(int data);

int main()
{
    int n, m, i, numero;
    node_t *head=NULL;
    char letra;
    scanf("%d %d\n", &n, &m);
    for(i=0; i<m; i++)
    {
        scanf("%c", &letra);
        switch(letra)
        {
        case 'I':
            scanf("%d\n", &numero);
            if(numero<=n)
            {
                insert_node(numero,&head);
            }
            break;
        case 'E':
            scanf("%d\n", &numero);
            if(numero<=n)
            {
                erase(&head, numero);
            }
            break;
        case 'C':
            getchar();
            int count = node_count(head);
            printf("%d\n", count);
            break;
        }
//        if(letra == 'I')
//        {
//            scanf("%d\n", &numero);
//            if(numero<=n)
//            {
//                insert_node(numero,&head);
//            }
//        }
//        if(letra=='C')
//        {
//            getchar();
//            int count = node_count(head);
//            printf("%d \n", count);
//        }
//        if(letra=='E')
//        {
//            scanf("%d\n", &numero);
//            if(numero<=n)
//            {
//                erase(&head, numero);
//            }
//        }


    }
    free_tree(head);
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

void erase(node_t **head, int dato)
{
    if(*head == NULL)
    {
        return;
    }
    if(dato<(*head)->data)
    {
        erase(&(*head)->left, dato);
    }
    else if(dato>(*head)->data)
    {
        erase(&(*head)->right, dato);
    }
    else
    {
        if((*head)->left && (*head)->right)
        {
            node_t *sucesor = minimo((*head)->right);
            (*head)->data = sucesor->data;
            erase(&(*head)->right, sucesor->data);
        }
        else
        {
            node_t *tmp = *head;
            if((*head)->left == NULL)
            {
                *head = (*head)->right;
            }
            else if((*head)->right == NULL)
            {
                *head = (*head)->left;
            }
            free (tmp);
        }
    }
}

node_t *minimo(node_t *head)
{
    if (head == NULL)
    {
        return head;
    }
    while(head->left != NULL)
    {
        head=head->left;
    }
    return head;
}