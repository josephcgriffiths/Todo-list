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

int main(){
	nt *head = NULL;
	head = malloc(sizeof(nt));
	
	int option;

	printf("Please select an option:\n");
	printf("1: Add a task\n");

	scanf("%d", &option);

	while(getchar() != '\n') {}

	if(option == 1){
		printf("Enter a task: ");
		char val[20];
		fgets(val, 20, stdin);
		val[strcspn(val,"\n")] = '\0';
		add_task(head, val);
	}

	print_list(head);
	
}
