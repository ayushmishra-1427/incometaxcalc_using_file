#include<stdio.h>
#include<string.h>
struct data{
	char name[50];
	int sal;
	int tax;
}d[100];
int taxcal(int d){
	int tax = 0;
    if (d <= 10000) {
        tax = 0;
    } else if (d <= 50000) {
        tax = (d - 10000) * 0.1;
    } else if (d <= 100000) {
        tax = 4000 + (d - 50000) * 0.2;
    } else {
        tax = 14000 + (d - 100000) * 0.3;
    }
    return tax;
}
void enterkro(){
	system("cls");
	FILE *fp;
	int n,i;
	printf("\nEnter total no of records you want to enter right now: \n");
	scanf("%d",&n);
	fp=fopen("Tax_detail.txt","ab+");
	for(i=0;i<n;i++)
	{
	printf("Enter name of the person :");
	scanf("%s",d[i].name);
	printf("Enter his/her annual salary :");
	scanf("%d",&d[i].sal);
	d[i].tax=taxcal(d[i].sal);
	fwrite(&d[i],sizeof(d[i]),1,fp);
	if (n==1){
		printf("This persons tax amount :%d\n",d[0].tax);
	}
	}
	fclose(fp);
	printf("\033[32m Record(s) Sucessfully entered \033[0m\n\n\n\n");
}
void dikhao(){
	system("cls");
	printf("SNo.\tNAME\tSALARY\t\tTAX AMOUNT\n");
	FILE *fp;
	fp=fopen("Tax_detail.txt","rb");
	if(fp==NULL){
        printf("Unable to open the file\n");
    }
	int n = 0;
    while (fread(&d[n], sizeof(d[n]), 1, fp) == 1) {
        printf("%d\t%s\t%.8d\t%.8d\n", n+1,d[n].name, d[n].sal, d[n].tax);
        n++;
    }
    printf("\n\n");
    fclose(fp);
}
void khojo(){
	system("cls");
	char c[50];
	printf("\nEnter name to search record:");
	scanf("%s",&c);
	FILE *fp;
	fp=fopen("Tax_detail.txt","rb");
	if(fp==NULL){
        printf("Unable to open the file\n");
    }
    int f=0;
    int n = 0;
    while (fread(&d[n], sizeof(d[n]), 1, fp) == 1) {
    	if (strcmp(c,d[n].name)==0){
    		f=1;
    		printf("\033[32mRecord FOUND\033[0m\n");
    		printf("NAME\tSALARY\t\tTAX AMOUNT\n");
    		printf("%s\t%.8d\t%.8d\n\n\n\n",d[n].name, d[n].sal, d[n].tax);
    	}
    	n++;
	}
	if (f==0){
		printf("\033[31mRECORD NOT FOUND\033[0m\n\n");
	}
}
int avail(char c[50]){
	FILE *fp;
	fp=fopen("Tax_detail.txt","rb");
	int f=0;
    int n=0;
    while (fread(&d[n],sizeof(d[n]),1,fp)==1){
    	if (strcmp(c,d[n].name)==0){
    		f=1;
    	}
    	n++;
	}
	if (f==0){
		return 0;
	}
	else{
		return 1;
	}
}
void edit(){
	system("cls");
	int ch;
	char c[50];
	printf("\nEnter name to update record:");
	scanf("%s",c);
	FILE *fp;
	FILE *ft;
	fp=fopen("Tax_detail.txt","rb");
	ft=fopen("Temp.txt","wb");
	if(fp==NULL){
        printf("Unable to open the file\n");
    }
    if(avail(c)==0){
    	printf("\033[31mRecord Not Found \033[0m\n\n");
	}
	else{
	int n=0;
	while (fread(&d[n],sizeof(d[n]),1,fp)==1){
    	if (strcmp(c,d[n].name)!=0){
    		fwrite(&d[n],sizeof(d[n]),1,ft);
	}
	else{
		printf("Enter what you want to update:\n");
		printf("\t1. Update Name\n");
		printf("\t2. Update salary\n");
		printf("\t3. Update both\n");
		printf("Enter Your choice: ");
		scanf("%d",&ch);
		switch(ch){
			case 1:
				printf("Enter Name:");
				scanf("%s",d[n].name);
				break;
			case 2:
				printf("Enter Salary:");
				scanf("%d",&d[n].sal);
				d[n].tax=taxcal(d[n].sal);
				break;
			case 3:
				printf("Enter Name:");
				scanf("%s",d[n].name);
				printf("Enter Salary:");
				scanf("%d",&d[n].sal);
				d[n].tax=taxcal(d[n].sal);
				break;
			default :
				printf("\033[31mSorry! Wrong choice\033[0m\n");
				break;
		}
		fwrite(&d[n],sizeof(d[n]),1,ft);
	}
	n++;
	}
	fclose(fp);
	fclose(ft);
	n=0;
	fp=fopen("Tax_detail.txt","wb");
	ft=fopen("Temp.txt","rb");
	while (fread(&d[n],sizeof(d[n]),1,ft)==1){
		fwrite(&d[n],sizeof(d[n]),1,fp);
		n++;
	}
	fclose(fp);
	fclose(ft);
	printf("\033[32mRecord Updated sucessfully\033[0m\n\n");
	
}
}
void htado(){
	system("cls");
	int ch;
	char c[50];
	printf("\nEnter name to search record:");
	scanf("%s",c);
	FILE *fp;
	FILE *ft;
	fp=fopen("Tax_detail.txt","rb");
	ft=fopen("Temp.txt","wb");
	if(fp==NULL){
        printf("Unable to open the file\n");
    }
    if(avail(c)==0){
    	printf("\033[31mRecord Not Found \033[0m\n\n");
	}
	else{
	int n=0;
	while (fread(&d[n],sizeof(d[n]),1,fp)==1){
    	if (strcmp(c,d[n].name)!=0){
    		fwrite(&d[n],sizeof(d[n]),1,ft);
	}
	n++;
	}
	fclose(fp);
	fclose(ft);
	n=0;
	fp=fopen("Tax_detail.txt","wb");
	ft=fopen("Temp.txt","rb");
	while (fread(&d[n],sizeof(d[n]),1,ft)==1){
		fwrite(&d[n],sizeof(d[n]),1,fp);
		n++;
	}
	fclose(fp);
	fclose(ft);
	printf("\033[32mRecord deleted sucessfully\033[0m\n\n");
	}
	

}
void main(){
	int n;
	printf("\033[31m      ------Welcome to the income tax calculator------\033[0m\n\n\n\n");
	do{
	printf("\t1. Add new record\n");
	printf("\t2. List all Tax Payer along with income tax to be paid\n");
	printf("\t3. Search\n");
	printf("\t4. Edit\n");
	printf("\t5. Delete Record\n");
	printf("\t6. Exit the program\n\n");
	printf("Enter the value:");
	scanf("%d",&n);
	switch(n){
		case 1:
			enterkro();
			break;
		case 2:
			dikhao();
			break;
		case 3:
			khojo();
			break;
		case 4:
			edit();
			break;
		case 5:
			htado();
			break;
		case 6:
			printf("\033[32mYou have decided to exit the code ..... Bye Bye , see you next time \033[0m");
			break;
		default:
			printf("\033[31m wrong input try again \033[0m\n\n");
	}
	}while(n!=6);
}
