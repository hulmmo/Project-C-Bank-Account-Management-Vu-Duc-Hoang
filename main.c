#include<stdio.h>
#include<stdlib.h>
int main(int argc, char *argv[]) {
	int choice;
	do{
	printfMenu();
	printf("Enter The Choice: ");
	scanf("%d", &choice);
	getchar();
	
	switch(choice){
		case 1:
			adminMenu();
			printf("\n");
		break;
		case 2:
			userLogin();
			printf("\n");
		case 0:
			printf("====== Thank You =====\n====== See You Soon ====\n");
			exit(0);
		break;
		default:
			printf("Invalid Choice.\n");
		break;
		}
	}while(choice != 2);
	return 0;
}
