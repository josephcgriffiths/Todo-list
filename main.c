#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

typedef struct node{
	char *task;
	int number;	
	bool status;
	struct node *next;
} nt;

void print_list(nt *head){
	nt *current = head;
	printf("+----+------------------------------+--------+\n");
	printf("| ID | Task                         | Status |\n");
	printf("+----+------------------------------+--------+\n");
	while(current!=NULL){
		printf("| %-2d | %-28s |  %c     |\n", current->number, current->task, current->status ? 'X' : ' ');	
		printf("+----+------------------------------+--------+\n");
		current = current->next;
	}
}

int get_number(nt *head){
	int i = 0;
	nt *current = head;
	while(current!=NULL){
		i++;
		current = current->next;
	}

	return i;
}

void after_delete(nt *head){
	nt *current = head;
	int i = 1;
	while(current!=NULL){
		current->number = i;
		current = current->next;
		i++;
	}
}

void add_task(nt *head, char *val){
	if(head->task==NULL){
		head->task = strdup(val);
		head->number = get_number(head); 
		head->status = false;
		head->next = NULL;
	} else {
		nt *current = head;
		while(current->next!=NULL){
			current = current->next;
		}

		current->next = malloc(sizeof(nt));
		current->next->task = strdup(val);
		current->next->number = get_number(head); 
		current->next->status = false;
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
	assert(head!=NULL);
	assert(n>=0);

	int i = 0;
	char* retval = NULL;
	nt *current = *head;
	nt *temp_node = NULL;

	if (n == 0){
		return pop(head);
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
	retval = temp_node->task;
	current->next = temp_node->next;
	free(temp_node);
	return retval;
}

void changeStatus(nt *head, int task){
	nt *current = head;
	while(current->number!= task){
		current = current->next;
	}

	current->status = true;
}

void saveToFile(nt *head){
	FILE *fptr;
	
	fptr = fopen("main.txt", "w");
	
	for(nt *current = head; current; current = current->next){
		fprintf(fptr, "%d\t%s\t%d\n", current->number, current->task, current->status);
	}
	fclose(fptr);
}

void freeHead(nt *head){
	while(head){
		nt *next = head->next;
		free(head->task);
		free(head);
		head = next;
	}
}

void reloadData(nt **head, int id, const char *task, bool status){
	nt *node = malloc(sizeof(nt));

	node->number = id;
	node->task = strdup(task);
	node->status = status;
	node->next = NULL;

	if(*head == NULL){
		*head = node;
		return;
	}

	nt *current = *head;
	while(current->next){
		current = current->next;
	}

	current->next = node;
}

void loadFiles(nt **head){
	FILE *fptr;

	fptr = fopen("main.txt", "r");

	freeHead(*head);
	*head = NULL;
	
	char line[2048];
	while(fgets(line, sizeof line, fptr)){
		int id = 0, status = 0;
		char task_buf[2000];

		sscanf(line, "%d\t%1999[^\t]\t%d", &id, task_buf, &status);
		reloadData(head, id, task_buf, status);

	}

	fclose(fptr);

}

int main(){
	nt *head = NULL;
	head = malloc(sizeof(nt));
	head->task = NULL;
	head->number = 0;
	head->next = NULL;

	int option = 0;

	while (option!= 7){
		printf("+-----------------------------+\n");
		printf("|Please select an option:     |\n");
		printf("+-----------------------------+\n");	
		printf("| 1 | Add a task              |\n");
		printf("+---+-------------------------+\n");
		printf("| 2 | Delete a task           |\n");
		printf("+---+-------------------------+\n");
		printf("| 3 | Print Tasks             |\n");
		printf("+---+-------------------------+\n");
		printf("| 4 | Update Task Status      |\n");
		printf("+---+-------------------------+\n");
		printf("| 5 | Save your Tasks         |\n");
		printf("+---+-------------------------+\n");
		printf("| 6 | Reload your Tasks       |\n");
		printf("+---+-------------------------+\n");
		printf("| 7 | Leave the Application   |\n");
		printf("+---+-------------------------+\n");
		scanf("%d", &option);

		while(getchar() != '\n') {}
		
		// Moves position to 1,1 and clears the screen
		printf("\e[1;1H\e[2J");

		if(option == 1){
			printf("Enter a task: ");
			char val[30];
			fgets(val, 30, stdin);
			val[strcspn(val,"\n")] = '\0';
			add_task(head, val);
		} else if (option == 2){
			print_list(head);
			printf("Enter the index to delete: ");
			int index;
			scanf("%d", &index);
			index -= 1;
			while(getchar() != '\n') {}

			printf("You have deleted the task: \n");
			delete_task(&head, index);
			after_delete(head);	
		} else if (option == 3){
			print_list(head);
		} else if (option == 4) {
			printf("What task would you like to update?\n");
			print_list(head);
			int task;
			scanf("%d", &task);
			while(getchar() != '\n') {}
			changeStatus(head, task);
		} else if (option == 5){
			saveToFile(head);
		} else if (option == 6){
			loadFiles(&head);
		}
	
	}

	return 0;
	
}
