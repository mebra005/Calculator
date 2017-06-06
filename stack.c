#include"stack.h"

// function to create a new node
struct node * new_node(int val) {
	// allocate memory for new node
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	if (temp == NULL)
		printf("Error: Memory Cannot be allocated\n");
	temp->value = val;
	temp->next = NULL;
	return temp;
}

// function to push value on top of stack
void push(struct node **top, int val) {
	struct node * temp;
	// create new node
	temp = new_node(val);
	// add node to top
	temp->next = *top;
	*top = temp;
}

// function to pop value from top
void pop(struct node **head)
{
	struct node *temp;
	// point temp to top node
	temp = *head;
	// move head to next node
	*head = (*head)->next;
	// free top node
	free(temp);
}

// function returns value at top of stack
int top(struct node *head)
{
	if (isEmpty(head) == FALSE)
		return head->value;
	else
		return -1;
}

// function returns true if stack is empty
int isEmpty(struct node *head)
{

	if (head == NULL)
		return TRUE;
	else
		return FALSE;
}

// function to display the linked list
void display(struct node *p) {
	while (p != NULL){
		printf("%d\n", p->value);
		p = p->next;
	}
}
