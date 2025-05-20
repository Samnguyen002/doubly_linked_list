#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//mau cua 1 head trong node
typedef struct node
{
	int data;
	struct node *next;
	struct node *prev;
}node_t;

node_t *create_node(int data)
{
	node_t *new_node = (node_t *)malloc(sizeof(node_t));
	new_node->data = data;
	new_node->next = NULL;
	new_node->prev = NULL;
	
	return new_node;
}

//them 1 node vao dau danh sach
void add_first_node(node_t **head, int data)
{
	node_t *new_nodee = create_node(data);
	new_nodee->next = *head;
	
	//truong hop DS rong, head = NULL thi khong can cap nhat phia sau
	if(*head != NULL)
		(*head)->prev =new_nodee;
		
	*head = new_nodee;
}

//them vao cuoi DSLK doi
void add_last_node(node_t **head, int data)
{
	node_t *new_node = create_node(data);
	
	if(*head == NULL)
	{
		*head = new_node;
		return;
	}
	
	node_t *temp = *head;	//node trung gian
	
	//duyet tu dau den cuoi
	for(; temp->next != NULL; temp = temp->next);
	
	temp->next = new_node;
	new_node->prev = temp;		//tro vao node cuoi khi do
	
}

int size(node_t *head);
//chèn 1 node vao giua DSKk
void add_node(node_t **head, int data, int index)
{
	node_t *new_node = create_node(data);
	
	int n =	size(*head);
	
	if(index < 1 || index > n)
	{
		printf("Vi tri khong hop le\n");
		return;
	}
	
	if(*head == NULL)
	{
		*head = new_node;
		return;
	}
	
	if(index == 1)
	{
		add_first_node(head, data);
		return;
	}
	else
	{
		node_t *temp = *head;
		for(int i = 1; i < index-1 && temp != NULL; i++)	//temp o node thu index-1 thoi
		{
			temp = temp->next;
		}
		
		new_node->next = temp->next;	//chen vao giua
		new_node->prev = temp;
		
		temp->next = new_node;
		
		//truong hop new_node khong phai node cuoi, thi cap nhat prev cua node sau new_node
		if(new_node->next != NULL)
		{
			new_node->next->prev = new_node;
		}
	}
}

//Xoa node khoi dau DSLK doi
void delete_first_node(node_t **head)
{
	if(*head == NULL)
		return;
	
	node_t *temp = *head;
	*head = (*head)->next;
	
	//truong hop DSLK chi co 1 node
	if(*head != NULL)
	{
		(*head)->prev = NULL;
	}
	temp->next == NULL;
	
	free(temp);
}

//Xoa node cuoi cua DSLK doi
void delete_last_node(node_t **head)
{
	if(*head == NULL)
		return;
			
	node_t *temp = *head;
	//truong hop chi co 1 node	
	if((*head)->next == NULL)
	{
		*head = NULL;
		free(temp);
		return;	
	}	
	
	for(; temp->next != NULL; temp = temp->next);		//temp tro dang la node cuoi
	
	temp->prev->next = NULL;
	temp->prev = NULL;
	
	free(temp);
}

//Xoa node o vi tri bat ki trong DSLK
void delete_node(node_t **head, int index)
{
	int n = size(*head);
	
	if(index < 1 || index > n)
	{
		printf("Vi tri khong hop le\n");
		return;
	}
	
	if(index == 1)
	{
		delete_first_node(head);
	}
	else
	{
		node_t *temp = *head;
		for(int i = 1; i < index-1; i++)	//temp dang o vi tri index-1
		{
			temp = temp->next;
		}
		
		node_t *release = temp->next; 	//node trung gian de giai phong
		temp->next = temp->next->next;
		
		//truong hop temp->next khong phai node cuoi
		if(temp->next != NULL)
		{
			release->next->prev = temp;
		}
		
		free(release);
	}
	
}

//duyet 1 danh sach
void traverse(node_t *head)
{
	while(head != NULL)
	{
		printf("%d ", head->data);
		head = head->next;
	}	
	
	printf("\n");
}

//ham duyet va size, khong thay doi DSLK, nen ko dung con tro cap 2
int size(node_t *head)
{
	int cnt = 1;
	while(head->next != NULL)
	{
		cnt++;
		head = head->next;
	}
	
	return cnt;
}

int main(int argc, char *argv[])
{
	node_t *head = create_node(5);
	
	while(1)
	{		
		printf("----------------------\n");
		printf("1. Them node dau danh sach\n");
		printf("2. Them node vao cuoi danh sach\n");
		printf("3. Chen 1 node vao DSLK\n");
		printf("4. Xoa node dau DSLK\n");
		printf("5. Xoa node cuoi DSLK\n");
		printf("6. Xoa node bat ki\n");
		printf("----------------------\n");
		int n;
		scanf("%d", &n);
		
		if(n == 1)
		{
			int data;
			scanf("%d", &data);
			add_first_node(&head, data);
			traverse(head);
			printf("so luong node %d\n", size(head));
		}
		else if(n == 2)
		{
			int data;
			scanf("%d", &data);
			add_last_node(&head, data);
			traverse(head);
		}
		else if(n == 3)
		{
			int data;
			scanf("%d", &data);
			int index;
			scanf("%d", &index);
			add_node(&head, data, index);
			traverse(head);	
		}
		else if(n == 4)
		{
			delete_first_node(&head);
			traverse(head);
		}
		else if(n == 5)
		{
			delete_last_node(&head);
			traverse(head);
		}
		else if(n == 6)
		{
			int index;
			scanf("%d", &index);
			delete_node(&head, index);
			traverse(head);
		}
	}
	return 0;
}
