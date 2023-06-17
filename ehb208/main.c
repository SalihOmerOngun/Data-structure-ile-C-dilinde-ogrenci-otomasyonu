
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/*
(A) O(n**2)
(B) O(n**2)
(C) O(n**2)
(E) O(n**2)
*/

/*CODE EXPLANATION:
firstly, we define node stack and student linkedlist. we have 3 different stack code, id and name.code keep faculty code, id keep ids, name keep student names. 
Pushname and popname function push and pop name for name stack. pop and push functions pop and push for id and code stacks. 
addname functions add new element to name stack. addnumber add new elements to code/id stack.
createstu create a new linkedlist. delstu delete a linkedlist. 
when  we add new record to student automation sytem, run getrecord function. this function use createstu,addnumber and addname.
when we delete a record from automation sytsem ve use delrecord function. this function use del and delstu. 
Del function delete a record from any stack(code,id,name) according to student number.
Lastly, printname prints the name of the elements of stack, we use print for id stack and name stack. 
printnumber prints the school number of elements of stack ,we use print code stack */

struct node {// it create a new stack for numbers(id,faculty code)
	char* name;
	int data;
	int number;
	struct node* next;
}*id = NULL, *code = NULL, *name=NULL;

struct node* pushname(struct node* root, char* kar,int number) {// it push name to the name stack
	struct node* temp = (struct node*)malloc(sizeof(struct node));
	temp->number = number;
	temp->name = kar;
	temp->next = root;
	root = temp;
	return root;
}

char* popname(struct node** root){// it pop name from the name stack
	struct node* temp = *root;
	*root = temp->next;
	char* kar = temp->name;
	free(temp);
	temp = NULL;
	return kar;
}

void printname(struct node* root) {// it print student names in the  stack
	struct node* temp = root;
	printf("%s ", root->name);
	temp = root->next;
	while (temp != NULL) {
		printf("%s ", temp->name);
		temp = temp->next;
	}
}

struct node* addname(struct node* root, char* kar, int number) {// it add a name sequentially to the name stack. this function use popname and pushname functions 
	struct node* newname = NULL; // it create a new name stack
	if (root == NULL) {
		root = pushname(root, kar,number);
	}
	else {
		while (strcmp(kar,root->name)>0) {//if root->name is less than the name we will add, it will pop the name from the general name stack
			int number1 = root->number;
			char* name = popname(&root);// it pop name from name stack
			newname = pushname(newname, name,number1);// it push the  name new stack
			if (root == NULL) {
				break;
			}
		}
		root = pushname(root, kar,number);// it push our name to name stack
		while (newname != NULL) {// it push names which were deleted to our name stack
			int number1 = newname->number;
			char* name = popname(&newname);
			root = pushname(root, name,number1);
		}
	}
	return root;
}

struct node* push(struct node* root, int data,char* kar, int number) {// it push a number to a stack
	struct node* temp = (struct node*)malloc(sizeof(struct node));
	temp->name = kar;
	temp->number=number;
	temp->data = data;
	temp->next = root;
	root = temp;
	return root;
}

int pop(struct node** root) {// it pop  a number from the stack
	struct node* temp = *root;
	*root = temp->next;
	int x = temp->data;
	free(temp);
	temp = NULL;
	return x;
}

void printnumber(struct node* root) {// it print school numbers in the stack
	struct node* temp = root;
	printf("%d ", root->number);
	temp = root->next;
	while (temp != NULL) {
		printf("%d ", temp->number);
		temp = temp->next;
	}
}

struct node* addnumber(struct node* root, int data,char* kar, int number) {// it add a number sequentially to the name stack. this function use pop and push functions
	struct node* newid = NULL;// it create a new stack
	if (root == NULL) {// if the stack is empty, it push the number to the first node
		root = push(root, data,kar,number);
	}
	else {
		while (data > root->data) {// if root->data is less than our value, it pop the root->data form general stak and push the our new stack
			char* name1 = root->name;
			int number1 = root->number;
			int value = pop(&root);
			newid = push(newid, value,name1,number1);
			if (root == NULL) {
				break;
			}
		}
		root = push(root, data,kar,number);// it push our value to convenient place
		while (newid != NULL) {// it push values which were deleted to general stack
			char* name1 = newid->name;
			int number1 = newid->number;
			int value = pop(&newid);
			root = push(root, value,name1,number1);
		}
	}
	return root;
}

struct student {// it create new linked list for each record
	char* kar;
	int no;
	struct student* next;
};


struct student* delstu(struct student* root) {// it delete linkedlist
	struct student* temp = NULL;
	while (root != NULL) {
		temp = root;
		root = root->next;
		free(temp);
		temp = NULL;
	}
	return root;
}


struct student* createstu(int no, char* kar) {// it create linkedlist
	struct student* root = (struct student*)malloc(sizeof(struct student));
	root->no = no;
	root->kar = NULL;
	root->next = NULL;
	struct student* temp = (struct student*)malloc(sizeof(struct student));
	temp->kar = kar;
	temp->no = NULL;
	root->next = temp;
	temp->next = NULL;
	return root;
}


int findid(int a) {// it find ids in school numbers
	int idvalue = 0;
	for (int i = 0; i < 4; i++) {
		int x = a % 10;
		a = a / 10;
		idvalue += x * pow(10, i);
	}
	return idvalue;
}

struct student* getrecord(int number, char* kar) {// it get records.this function use addnumber, addname and createstu functions
	struct student* root = NULL;
	root = createstu(number,kar);
	int codevalue = number / 1000000; // it find faculty codes in school numbers
	code = addnumber(code, codevalue,kar,number);// it run addnumber functions for faculty code
	name = addname(name, kar,number);// it run addname functions for name
	int idvalue = findid(number);
	id = addnumber(id, idvalue,kar,number);// it run addnumber functions for id
	return root;
}

struct node* del(struct node* root, int number) {//it deletes according to number
	struct node* newid = NULL;
	struct node* temp = NULL;
	if (root == NULL) {
		return root;
	}
	else {
		while (root->number != number) {// if root->number!=null it pop root and push to new stack
			char* name1 = root->name;
			int number1 = root->number;
			int value = pop(&root);
			newid = push(newid, value, name1, number1);
		}
		temp = root;
		root = root->next;//deletes the root to which the number belongs.
		free(temp);
		temp = NULL;
		while (newid != NULL) {// our element again push our first stack 
			char* name1 = newid->name;
			int number1 = newid->number;
			int value = pop(&newid);
			root = push(root, value, name1, number1);
		}
	}
	return root;
}

struct student* delrecord(struct student* root, int number) {// it delete according to number for each stack(id,name,number), this function use del and delstu function
	code = del(code, number);
	id = del(id, number);
	name = del(name, number);
	root = delstu(root);
}


int main() {
	struct student* root = NULL;
	root= getrecord(735102105, &"selcuk_turan");
	root= getrecord(700102085, &"emir_oz");
	root= getrecord(780102013, &"arif_alacakan");
	root= getrecord(741102005, &"mustafa_ekmer");
	printnumber(code);
	printf("    ");
	printname(name);
	printf("   ");
	printname(id);
	root = delrecord(root, 741102005);
	printf(" deleted  ");
	printnumber(code);
	printf("    ");
	printname(name);
	printf("   ");
	printname(id);
	if (root == NULL) {
		printf("   root is null");
	}
	return 0;
}


