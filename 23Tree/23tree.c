#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct node {
	int k1, k2, k3;
	struct node * p1, *p2, *p3;
	int isLeaf;
};

void printTree(struct node*p);
struct node* newNode(int k1, int k2, int k3);
void insert(struct node **root, struct node *leaf);
void add(struct node **y, struct node *leaf, struct node **newBro);

main()
{	
	struct node * root;
	root = NULL;	
	struct node* leaf = (struct node*)malloc(sizeof(struct node));
	leaf->isLeaf = 1;
	leaf->k1 = 5;		
	insert(&root, leaf);			
	struct node* leaf1 = (struct node*)malloc(sizeof(struct node));
	leaf1->isLeaf = 1;
	leaf1->k1 = 11;		
	insert(&root, leaf1);		
	struct node* leaf2 = (struct node*)malloc(sizeof(struct node));
	leaf2->isLeaf = 1;
	leaf2->k1 = 17;		
	insert(&root, leaf2);
	struct node* leaf3 = (struct node*)malloc(sizeof(struct node));
	leaf3->isLeaf = 1;
	leaf3->k1 = 20;		
	insert(&root, leaf3);
	printTree(root);
}

void insert(struct node **root, struct node *leaf)
{
	if((*root) == NULL)
	{		
		*root = leaf;		
		return;
	}
	else if((*root)->isLeaf == 1)
	{
		struct node* temp = (struct node*)malloc(sizeof(struct node));
		temp->k1 = (*root)->k1;
		temp->k2 = leaf->k1;
		temp->p1 = *root;
		temp->p2 = leaf;
		temp->isLeaf = 0;
		*root = temp;
	}
	else
	{
		struct node *newBro;
		newBro = NULL;
		add(root, leaf, &newBro); 
		if(newBro != NULL)
		{
			struct node* temp = (struct node*)malloc(sizeof(struct node));
			temp->k1 = (*root)->k2;
			temp->p1 = (*root);
			temp->k2 = newBro->k2;
			temp->p2 = newBro;
			temp->isLeaf = 0;
			(*root) = temp;
		}
	}
}

void add(struct node **y, struct node *leaf, struct node **newBro)
{
	if((*y)->p1->isLeaf == 1)
	{
		if((*y)->p3 == NULL)
		{
			printf("Entering Here\n");
			printf("%d %d %d\n", (*y)->k1, (*y)->k2, (*y)->k3);
			(*y)->p3 = leaf;
			(*y)->k3 = leaf->k1;
		}
		else
		{
			struct node* y1 = (struct node*)malloc(sizeof(struct node));
			y1->p1 = (*y)->p3;
			y1->k1 = (*y)->k3;
			(*y)->k3 = 0;
			(*y)->p3 = NULL;
			y1->p2 = leaf;
			y1->k2 = leaf->k1;
			y1->isLeaf = 0;
			(*newBro) = y1;
		}
	}
}

struct node* newNode(int k1, int k2, int k3)
{
	struct node* node = (struct node*)malloc(sizeof(struct node));
	node->k1 = k1;
	node->k2 = k2;
	node->k3 = k3;
	node->p1 = NULL;
	node->p2 = NULL;
	node->p3 = NULL;
	return node;
}

void printTree(struct node * p)
{
	printf("Printing level");
	if(p->isLeaf == 0)
	{
		printf("\t %d", p->k1);
		printf("\t %d", p->k2);
		printf("\t %d\n", p->k3);
	}
	else
	{
		printf("\t %d\n", p->k1);
	}
	
	if(p->p1 != NULL)
		printTree(p->p1);
	if(p->p2 != NULL)
		printTree(p->p2);
	if(p->p3 != NULL)
		printTree(p->p3);
}