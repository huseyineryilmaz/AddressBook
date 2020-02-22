#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define MAX_NAME 30
#define MAX_ADDR 30
#define MAX_CITY 30
#define MAX_PCODE 50
#define MAX_PNUM 50

#define MAX_BUFFER 500
#define DELIMETER "#"

#define MAXCHAR 1000

struct _record{
	char name[MAX_NAME];
	char address[MAX_ADDR];
	char city[MAX_CITY];
	char postcode[MAX_PCODE];
	char phonenumber[MAX_PNUM];
	char ch;
};


typedef struct _record RECORD;


/*void DisplayRecordbyName(FILE *fp,char *name){
	FILE *fpp;
	fpp = fopen("deletedIndex.txt", "r");
	int counter=0;
	RECORD r;
	int nbytes;
	int num=0;
	int check=0;
	int y;
	int display=1;
	char str[MAXCHAR];
	fseek(fp,0,SEEK_SET);
	while(!feof(fp)){
		fread(&r,sizeof(RECORD),1,fp);
		counter++;
		if(nbytes>0){
			if(strcmp(r.name,name)==0){
				check=counter;
			}
		}
	}
	fseek(fpp,0,SEEK_SET);
	while(fgets(str, MAXCHAR, fpp) != NULL){
		y = atoi(str);
		if( y  == check){
			display=0;
		}
	}

	fseek(fp,0,SEEK_SET);
	while(!feof(fp)){
		fread(&r,sizeof(RECORD),1,fp);
		//if(nbytes>0){
			if(strcmp(r.name,name)==0 && display==1){
				DisplayRecord(r);
				num=1;
				break;
			}
		//}
	}
	if (num==0)
		printf("'%s' does not exist!..\n", name);

	fclose(fpp);
}*/

void DisplayRecordbyName(char *name){
	FILE *fpp;
	FILE *fpp2;
	fpp = fopen("deletedIndex.txt", "r");
	fpp2 = fopen("data.dat", "r+");
	RECORD r;
	char str[MAXCHAR];
	int display=1;
	int y;
	int counter=0;
	int num=0;
	fseek(fpp2,0,SEEK_SET);

	while(!feof(fpp2)){
		display=1;
		fread(&r,sizeof(RECORD),1,fpp2);
		counter++;
		fseek(fpp,0,SEEK_SET);
		while(fgets(str, MAXCHAR, fpp) != NULL){
			y = atoi(str);
			if( y  == counter){
				display=0;
				break;
			}
		}
		if(display == 1 && strcmp(r.name,name)==0){
			DisplayRecord(r);
			num=1;
		}
	}
	if(num==0)
		printf("%s does not exist!!\n", name);
	fclose(fpp);
	fclose(fpp2);
}


void DeleteRecord(FILE *fp,char *name){
	FILE *fpp;
	fpp = fopen("deletedIndex.txt", "a");
	RECORD r;
	int nbytes;
	int counter=0;
	int check=0;
	char str[MAXCHAR];
	int y;
	int print=1;
	fseek(fp,0,SEEK_SET);
	fseek(fpp, 0, SEEK_SET);
	while(!feof(fp)){
		fread(&r,sizeof(RECORD),1,fp);
		++counter;
		if(nbytes>0){
			if(strcmp(r.name,name)==0){
				fprintf(fpp,"%d\n", counter);
				break;
			}
		}
	}
	fclose(fpp);
}

void UpdateRecord(FILE *fp,char *name){
	FILE *fpp;
	fpp = fopen("deletedIndex.txt", "a");
	RECORD r;
	int nbytes;
	int counter=0;
	int check=0;
	char str[MAXCHAR];
	int y;
	int print=1;
	int fn = 0;

	fseek(fp,0,SEEK_SET);
	fseek(fpp, 0, SEEK_SET);
	while(!feof(fp)){
		fread(&r,sizeof(RECORD),1,fp);
		++counter;
		if(nbytes>0){
			if(strcmp(r.name,name)==0){
				fprintf(fpp,"%d\n", counter);
				break;
			}
		}
	}
	fclose(fpp);
}

void DisplayAll(){
	FILE *fpp;
	FILE *fpp2;
	fpp = fopen("deletedIndex.txt", "r");
	fpp2 = fopen("data.dat", "r+");
	RECORD r;
	char str[MAXCHAR];
	int display=1;
	int y;
	int counter=0;
	while(!feof(fpp2)){
		display=1;
		fread(&r,sizeof(RECORD),1,fpp2);
		counter++;
		fseek(fpp,0,SEEK_SET);
		while(fgets(str, MAXCHAR, fpp) != NULL){
			y = atoi(str);
			if( y  == counter){
				display=0;
				break;
			}
		}
		if(display == 1){
			DisplayRecord(r);
		}
	}
	fclose(fpp);
	fclose(fpp2);
}



void BulkLoad(char *bulkFile,char *dataFile){
	RECORD r;
	RECORD r2;
	char opcode[50];
	FILE *bfp;
	FILE *fp;
	FILE *fp2;
	char *p;
	char buffer[MAX_BUFFER];
	int n=0;
	int fn=0;
	int num = 0;
	int num2=0;
	
	bfp=fopen(bulkFile,"r");
	fp=fopen(dataFile,"r+");
	if(fp==NULL){
		fp=fopen(dataFile,"w+");
	}

	while(!feof(bfp)){
		if(fgets(buffer,MAX_BUFFER,bfp)){
			buffer[strlen(buffer)-1]=0;

			printf("%d &s",++n,buffer);
			p=strtok(buffer,DELIMETER);
			fn=0;
			while(p){
				printf("Field: %s\n",p);
				switch(fn){
					case 0:{strcpy(opcode,p);break;}
					case 1:{strcpy(r.name,p);
							strcpy(r2.name,p);break;}
					case 2:{strcpy(r.address,p);
							strcpy(r2.address,p);break;}
					case 3:{strcpy(r.city,p);
							strcpy(r2.city,p);break;}
					case 4:{strcpy(r.postcode,p);
							strcpy(r2.postcode,p);break;}
					case 5:{strcpy(r.phonenumber,p);
							strcpy(r2.phonenumber,p);break;}
				}
				fn++;
				p=strtok(NULL,DELIMETER);
			}
			if(strcmp(opcode,"insert")==0){
				fwrite(&r,sizeof(RECORD),1,fp);
			}
			if(strcmp(opcode,"delete")==0){
				DeleteRecord(fp, r.name);
			}
			if(strcmp(opcode,"show")==0){
				DisplayRecordbyName(r.name);
			}
			if(strcmp(opcode,"update")==0){
				UpdateRecord(fp,r.name);
				fseek(fp,0,SEEK_END);
				fwrite(&r2,sizeof(RECORD),1,fp);
			}
			if(strcmp(opcode,"displayAll")==0){
				DisplayAll();
			}
		}
	}
	fclose(bfp);
	fclose(fp);
}
void DisplayRecord(RECORD r){
	printf("%-10s: %s\n","Name",r.name);
	printf("%-10s: %s\n","Address",r.address);
	printf("%-10s: %s\n","City",r.city);
	printf("%-10s: %s\n","Postcode",r.postcode);
	printf("%-10s: %s\n","Phonenumber",r.phonenumber);
}

void DisplayRecordbyRRN(char *dataFile,int RRN){
	FILE *fp;
	fp=fopen(dataFile,"r");
	fseek(fp,sizeof(RECORD)*RRN,SEEK_SET);
	while(!feof(fp)){
		
	}
}

int main(int argc, char *argv[]){
	if(argc!=2){
		printf("Usage: hw1.exe datafile.txt \n ");
		exit(-1);
	}
	BulkLoad(argv[1],"data.dat");
	return(0);
}
