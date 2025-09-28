#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
	char *task;
	struct node *next;
} nt;

void print_list(nt *head){
	nt *current = head;
	while(current!=NULL){
		printf("%s\n", current->task);
		current = current->next;
	}
}

void add_task(nt *head, char *val){
	if(head->task==NULL){
		head->task = val;
		head->next = NULL;
	} else {
		nt *current = head;
		while(current->next!=NULL){
			current = current->next;
		}

		current->next = malloc(sizeof(nt));
		current->next->task = val;
		current->next->next = NULL;
	}
	
}

char* pop(nt **head){
	char* retval = NULL;
	nt *new_node = NULL;

	if(*head == NULL){
		return "error: no todo list";
	}

	new_node = (*head)->next;
	retval = (*head)->task;
	free(*head);
	*head = new_node;
	return retval;
	
}

char* delete_task(nt **head, int n){
	int i = 0;
	char* retval = NULL;
	nt *current = *head;
	nt *temp_node = NULL;

	if (n == 0){
		pop(head);
	}

	for (i=0;i<n-1;i++){
		if(current->next == NULL){
			return "error: no item in the list";
		}
		current = current->next;
	}

	if(current->next == NULL){
		return "error: no item in the list";
	}

	temp_node = current->next;
	retval = current->task;
	current->next = temp_node->next;
	free(temp_node);
	return retval;
}

int main(){
	nt *head = NULL;
	head = malloc(sizeof(nt));
	head->task = "Create a new list";
	head->next = malloc(sizeof(nt));
	head->next->task = "Create an item";
	head->next->next = NULL;
	
	int option;

	printf("Please select an option:\n");
	printf("1: Add a task\n");
	printf("2: Delete a task\n");

	scanf("%d", &option);

	while(getchar() != '\n') {}

	if(option == 1){
		printf("Enter a task: ");
		char val[20];
		fgets(val, 20, stdin);
		val[strcspn(val,"\n")] = '\0';
		add_task(head, val);
	} else if (option == 2){
		print_list(head);
		printf("Enter the index to delete: ");
		int index;
		scanf("%d", &index);
		while(getchar() != '\n') {}

		printf("You have deleted the task: \n");
		delete_task(&head, index);
	}
	
	print_list(head);
	
}
