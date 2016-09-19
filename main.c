#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_N_SN 30

int show_menu(void);
void add_position(void);
void add_position_indep(void);
void load_file_pos(void);
void save_file_pos(void);
void change_position(void);
void rnumber_check(void);
void add_catalogue(void);
void add_catalogue_indep(void);
void add_number_cat(void);
void load_files(void);
void save_files(void);
void delete_catalogue(void);
void change_catalogue_name(void);
void del_number_cat(void);
void replace_number_cat(void);
void search_repl_num_cat(void);
void add_repl_num_cat(void);
void move_position(void);
void add_pos_to_catalogue(void);
void delete_pos_from_cat();
void delete_pos_from_list(void);
void searching_by_parameter(void);
void show_catalogue(void);
void show_list_cat(void);
void show_positions(void);
void file_manipulation(void);

FILE * fpozycje, * fkatalog, * fbaza;

struct position{
	char surname [MAX_N_SN];
	char name [MAX_N_SN];
	char reg_number [8];
	int year;
	struct position * next_pos_ptr;
};
	struct position *head=NULL;
	struct position *current=NULL;
	struct position *previous=NULL;
	struct position *check_num_1=NULL;
	int ipom=0;
	int i_pos=0;

struct list_of_pos{
	char surname [MAX_N_SN];
	char name [MAX_N_SN];
	char reg_number [8];
	int year;
	struct list_of_pos * next_lp_ptr;
};
	int ipom_list=0;
	int i_pos_list=0;

struct catalogue{
	char title [MAX_N_SN];
	int ipos_c;
	struct list_of_pos *head_list, *current_list, *previous_list, *tmp_list;
	struct catalogue * next;
};
	//ipos_c=0;
	struct list_of_pos *head_list=NULL;
	struct list_of_pos *current_list=NULL;
	struct list_of_pos *previous_list=NULL;
	struct list_of_pos *tmp_list=NULL;
	struct catalogue *head_c=NULL;
	struct catalogue *current_c=NULL;
	struct catalogue *previous_c=NULL;
	struct catalogue *check_c=NULL;
	struct catalogue *tmp_c=NULL;
	int ipom_c=0;
	int i_pos_c=0;

int x;	
int y=0;
char number[8];
char enter[MAX_N_SN];
char enter_2[MAX_N_SN];

int main(void){
	int choice;

	while ((choice = show_menu()) != 15){
		
		head=current=previous=check_num_1=NULL;
		ipom=i_pos=0;
		ipom_list=i_pos_list=0;
		head_list=current_list=previous_list=tmp_list=NULL;
		head_c=current_c=previous_c=check_c=tmp_c=NULL;
		ipom_c=i_pos_c=0;
		y=0;
		
		if ((fpozycje=fopen("pozycje.txt", "a+")) == NULL){
		fputs("Can't open file pozycje.txt\n", stderr);
		exit(1);
		}
		
		if ((fkatalog=fopen("katalog.txt", "a+")) == NULL){
		fputs("Can't open file katalog.txt\n", stderr);
		exit(1);
		}
		
		if ((fbaza=fopen("baza.txt", "a+")) == NULL){
		fputs("Can't open file baza.txt\n", stderr);
		exit(1);
		}
		
		switch (choice){
			case 1: add_position(); break;
			case 2: change_position(); break;
			case 3: add_catalogue(); break;
			case 4: delete_catalogue(); break;
			case 5: change_catalogue_name(); break;
			case 6: move_position(); break;
			case 7: add_pos_to_catalogue(); break;
			case 8: delete_pos_from_cat(); break;
			case 9: delete_pos_from_list(); break;
			case 10: searching_by_parameter(); break;
			case 11: show_catalogue(); break;
			case 12: show_list_cat(); break;
			case 13: show_positions(); break;
			case 14: file_manipulation(); break;
		} // end of switch (choice)
	} // end of while (menu)
	fclose(fpozycje);
	fclose(fbaza);
	fclose(fkatalog);
	return 0;	
} // end of main

int show_menu(void){
	int choice;
	puts("==================================================================");
	puts("Choose option:");
	puts("1) Add position			2) Change position");
	puts("3) Add catalogue		4) Delete catalogue");
	puts("5) Change catalogue name	6) Move position");
	puts("7) Add position to catal.	8) Delete position from catalogue");
	puts("9) Delete pos. from list	10) Searching by parameter");
	puts("11) Show chosen catalog.	12) Show list's catalogues");
	puts("13) Show positions		14) File manipulation");
	puts("15) Exit program");
	puts("==================================================================");
	while (scanf("%d", &choice) != 1){
		printf("Error, \"choice\" had to be a number\n");
		while (getchar() != '\n')
			continue;
	}
 	getchar();
 	puts("==================================================================");
	return choice;
}

void add_position(void){
	add_position_indep();
	save_file_pos();
}

void add_position_indep(void){
	
	load_file_pos();
	
	puts("Enter new surname.");
	puts("If you're end, click [enter] at the begining.");
	while(gets(enter) != NULL && enter[0] != '\0'){
		current = (struct position *)malloc(sizeof(struct position));
		if (head==NULL) head=current;
		else previous->next_pos_ptr=current;
		current->next_pos_ptr=NULL;
		
		strcpy(current->surname,enter);
		
		puts("Enter name");
		gets(current->name);
		
		puts("Enter a registration number");
		rnumber_check();
		
		puts("Enter a year of production");
		while (getchar() != '\n');
		while (scanf("%d", &current->year) != 1){
			printf("Error! It has to be a number. Please, try again:\n");
			while (getchar() != '\n')
				continue;		
		}
		while (getchar() != '\n');
		
		puts("Please, enter next surname");
		previous=current;
		i_pos++;
	}// End of while (gets new position)
}

void save_file_pos(void){
	if (head!=NULL){ // save file
		if (freopen("pozycje.txt", "w", fpozycje) == NULL){
			fputs("Can't open file pozycje.txt\n", stderr);
			exit(1);
		}
		current=head;
		fprintf(fpozycje, "%d\n", i_pos);
		while(current!=NULL){
			fprintf(fpozycje, "%s %s %s %d\n", current->surname, current->name, current->reg_number, current->year);
			current=current->next_pos_ptr;
		}
	}
	else { // save file
		if (freopen("pozycje.txt", "w", fpozycje) == NULL){
			fputs("Can't open file pozycje.txt\n", stderr);
			exit(1);
		}
		puts("File is empty.");
	}
	current=head;
	previous=head;
	head=NULL;
	while (current!=NULL){
		current=current->next_pos_ptr;
		free(previous);
		previous=current;
	}
	fclose(fpozycje);
	fclose(fbaza);
	fclose(fkatalog);
}

void load_file_pos(void){
	ipom=0;
	rewind(fpozycje); // read from file
	current=(struct position *)malloc(sizeof(struct position));
	fscanf(fpozycje, "%d\n", &i_pos);
	while((fscanf(fpozycje, "%s %s %s %d\n", &(current->surname), &(current->name), &(current->reg_number), &(current->year)))==4){
		if (head==NULL) head=current;
		if (++ipom==i_pos){
			current->next_pos_ptr=NULL;
			previous=current;
			break;
		}
		current->next_pos_ptr=(struct position *)malloc(sizeof(struct position));
		current=current->next_pos_ptr;
		previous=current;
	} // end of read from file
	ipom=0;
}


void show_positions(void){
	
	load_file_pos();
	
	if (head!=NULL){
		puts("File content:");
		current=head;
		while(current!=NULL){
			printf("%10s %10s %10s %10d\n", current->surname, current->name, current->reg_number, current->year);
			current=current->next_pos_ptr;
		}
	}
	save_file_pos();
}

void file_manipulation(void){
	FILE *file;
	char comand[5];
	char filename[20];
	char decision[2];
	printf("Enter comand (ex. load pozycje.txt):\n");
	while (1){
		scanf("%s %s", &comand, &filename);
		while (getchar() != '\n');
		if (strcmp(comand, "load")==0){
			if(strcmp(filename, "pozycje.txt")==0){
				add_position_indep();
			}
			if(strcmp(filename, "katalog.txt")==0){
				add_catalogue_indep();
			}
			if(strcmp(filename, "baza.txt")==0){
				if (freopen("baza.txt", "w", fbaza) == NULL){
				fputs("Can't open file baza.txt\n", stderr);
				exit(1);
				puts("Data from the file baza.txt were successfully removed");
				}
			}
		}
	
		if (strcmp(comand, "save")==0){
			if(strcmp(filename, "pozycje.txt")==0){
				save_file_pos();
			}
			if(strcmp(filename, "katalog.txt")==0){
				save_files();
				save_file_pos();
			}
			if(strcmp(filename, "baza.txt")==0){
				fclose(fbaza);
			}
		}
		puts("Do you want to continue manipulations (Y/N)?");
		if((decision[0] = getchar())=='N') break;
			else{
				puts("Enter new comand.");
				continue;
			}
	}
}

void change_position(void){
	
	load_file_pos();
	
	puts ("Enter registration number to change");
	gets(number);
	
	current=head;
	previous=head;
	if(i_pos!=0){
		for(ipom=1;ipom<=i_pos;ipom++){
			if (strcmp(current->reg_number, number)==0){
				break;
			}
			previous=current;
			current=previous->next_pos_ptr;
		}
	}
	else puts("Error. There is no data to search.");
	puts("============================================");
	puts ("Choose option:");
	puts ("1. Delete		2. Change number");
	puts ("3. Change name		4. Change surname");
	puts ("5. Change year		q. Back to menu");
	puts("============================================");
	while (scanf("%d", &x)==1){
		switch (x){
			case 1: {
				while (getchar() != '\n');
				if (current==head){
					head=head->next_pos_ptr;
					previous=previous->next_pos_ptr;
					free(current);
					current=head;
					i_pos--;
					puts("Successfully removed.");
					break;
				}
				previous->next_pos_ptr=current->next_pos_ptr;
				free(current);
				current=previous->next_pos_ptr;
				i_pos--;
				puts("Successfully removed.");
				break;
			}
			case 2: {
				puts("Enter number");
				gets(current->reg_number);
				rnumber_check();
				break;
			}
			case 3: {
				puts("Enter name");
				while (getchar() != '\n');
				gets(current->name);
				puts("Successfully changed");
				break;
			}
			case 4: {
				puts("Enter surname");
				while (getchar() != '\n');
				gets(current->surname);
				puts("Successfully changed");
				break;
			}
			case 5: {
				puts("Enter a year of production");
				while (getchar() != '\n');
				while (scanf("%d", &current->year) != 1){
					printf("Error! It has to be a number. Please, try again:\n");
				while (getchar() != '\n');
				}
				while (getchar() != '\n');
				break;
			}
		}//end of switch
	while (getchar() != '\n');
	puts ("Choose next option.");
	}//end of while
	while (getchar() != '\n');
	
	save_file_pos();
}

void rnumber_check(void){
	for(ipom=0;ipom<7;){
		current->reg_number[ipom] = getchar();
		if (ipom<3){
			if(current->reg_number[ipom]>=65&&current->reg_number[ipom]<=90)
				ipom++;
			else{
				ipom=0;
				printf("Error! The number must to be following format - AAA0000\n");
				while (getchar() != '\n')
					continue;
			}
		}
		else{
			if(ipom>=3 && ipom<7 && current->reg_number[ipom]>=48&&current->reg_number[ipom]<=57){
				if (ipom==6){
					check_num_1=head;
						while(check_num_1!=NULL){
							if (check_num_1==current){
								check_num_1=check_num_1->next_pos_ptr;
								continue;
							}
							if (strcmp(current->reg_number, check_num_1->reg_number)==0){
								ipom=-1;
								puts("Error. The number already exist. Try again.");
								while (getchar() != '\n');
								break;
							}
							check_num_1=check_num_1->next_pos_ptr;
						}	
					ipom++;
					continue;	
				}
			ipom++;
			}
			else{
				ipom=0;
				printf("Error! The number must to be following format - AAA0000\n");
				while (getchar() != '\n')
					continue;
				}
		}
	}// End of for
}

void add_catalogue_indep(void){
	
	load_file_pos();
	load_files();
	
	puts("Enter new catalogue name.");
	puts("If you're end, click [enter] at the begining.");
	while(gets(enter) != NULL && enter[0] != '\0'){
		current_c = (struct catalogue *)malloc(sizeof(struct catalogue));
		if (head_c==NULL) head_c=current_c;
		else previous_c->next=current_c;
		current_c->next=NULL;
		
		strcpy(current_c->title,enter);
		check_c=head_c;
		while(check_c!=NULL){
			if (check_c==current_c){
				check_c=check_c->next;
				continue;
			}
			if (strcmp(current_c->title, check_c->title)==0){
				puts("Error. The catalogue already exist. Try again.");
				ipom_c=-1;
				break;
			}
			check_c=check_c->next;
		}
		if (ipom_c==-1){
		free(current_c);
		previous_c->next=NULL;
		current_c=NULL;
		ipom_c=0;
		continue;
		} 
		
		add_number_cat();
		
		puts("Please, enter next catalogue name.");
		previous_c=current_c;
		i_pos_c++;
	}// End of while (gets new position)
}

void add_catalogue(void){
	add_catalogue_indep();
	save_file_pos();
	save_files();
}

void load_files(void){
	ipom_c=0; ipom_list=0;
	rewind(fkatalog); // read from file
	rewind(fbaza);
	current_c=(struct catalogue *)malloc(sizeof(struct catalogue));
	fscanf(fbaza, "%d\n", &i_pos_c);
	while((fscanf(fbaza, "%s\n", &(current_c->title)))==1){
		current_c->current_list=(struct list_of_pos *)malloc(sizeof(struct list_of_pos));
		fscanf(fbaza, "%d\n", &(current_c->ipos_c));
		while((current_c->ipos_c)!=0 && (fscanf(fbaza, "%s %s %s %d\n", &(current_c->current_list->surname), 
			&(current_c->current_list->name), &(current_c->current_list->reg_number), &(current_c->current_list->year)))==4){
			if (current_c->head_list==NULL) current_c->head_list=current_c->current_list;
			if (++ipom_list==(current_c->ipos_c)){
				current_c->current_list->next_lp_ptr=NULL;
				current_c->previous_list=current_c->current_list;
				ipom_list=0;
				break;
			}
			current_c->current_list->next_lp_ptr=(struct list_of_pos *)malloc(sizeof(struct list_of_pos));
			current_c->current_list=current_c->current_list->next_lp_ptr;
			current_c->previous_list=current_c->current_list;
		} // end of read from "inside" file
		
		if (head_c==NULL) head_c=current_c;
		if (++ipom_c==i_pos_c){
			current_c->next=NULL;
			previous_c=current_c;
			ipom_c=0;
			break;
		}
		current_c->next=(struct catalogue *)malloc(sizeof(struct catalogue));
		current_c=current_c->next;
		previous_c=current_c;
	} // end of read from file
	ipom_list=0; ipom_c=0;
}

void save_files(void){
	if (head_c!=NULL){
		if (freopen("baza.txt", "w", fbaza) == NULL){
			fputs("Can't open file baza.txt\n", stderr);
			exit(1);
		}
		if (freopen("katalog.txt", "w", fkatalog) == NULL){
			fputs("Can't open file katalog.txt\n", stderr);
			exit(1);
		}
		puts("==================================================================");
		puts("File content:");
		current_c=head_c;
		fprintf(fbaza, "%d\n", i_pos_c);
		while(current_c!=NULL){
			printf("%s\n", current_c->title);
			fprintf(fbaza, "%s\n", current_c->title);
			fprintf(fkatalog, "%s\n", current_c->title);
			
			current_c->current_list=current_c->head_list;
			fprintf(fbaza, "%d\n", current_c->ipos_c);
			while(current_c->current_list!=NULL){
				printf("%15s %10s %10s %10d\n", current_c->current_list->surname, current_c->current_list->name, 
				current_c->current_list->reg_number, current_c->current_list->year);
				fprintf(fbaza, "%s %s %s %d\n", current_c->current_list->surname, current_c->current_list->name, 
				current_c->current_list->reg_number, current_c->current_list->year);
				current_c->current_list=current_c->current_list->next_lp_ptr;
			}
			
			current_c=current_c->next;
		}
	}
	else { // save file
		if (freopen("baza.txt", "w", fbaza) == NULL){
			fputs("Can't open file baza.txt\n", stderr);
			exit(1);
		}
		if (freopen("katalog.txt", "w", fkatalog) == NULL){
			fputs("Can't open file katalog.txt\n", stderr);
			exit(1);
		}
		puts("File is empty.");
	}
	
	current_c=head_c;
	previous_c=head_c;
	head_c=NULL;
	while (current_c!=NULL){
		
		current_c->current_list=current_c->head_list;
		current_c->previous_list=current_c->head_list;
		current_c->head_list=NULL;
		while (current_c->current_list!=NULL){
			current_c->current_list=current_c->current_list->next_lp_ptr;
			free(current_c->previous_list);
			current_c->previous_list=current_c->current_list;
		}
		current_c=current_c->next;
		free(previous_c);
		previous_c=current_c;
	}
	
	fclose(fbaza);
	fclose(fkatalog);
	fclose(fpozycje);
}

void delete_catalogue(void){
	load_files();
	
	puts("Enter catalogue name to delete.");
	gets(enter);
	
	previous_c=head_c;
	current_c=head_c;
	if(i_pos_c!=0){
		for(ipom_c=1;ipom_c<=i_pos_c;ipom_c++){
			if (strcmp(current_c->title, enter)==0){
				if (current_c==head_c){
					head_c=head_c->next;
					previous_c=previous_c->next;
					free(current_c);
					current_c=head_c;
					i_pos_c--;
					puts("Successfully removed.");
					break;
				}
				previous_c->next=current_c->next;
				free(current_c);
				current_c=previous_c->next;
				i_pos_c--;
				puts("Successfully removed.");
				break;
			}
			previous_c=current_c;
			current_c=previous_c->next;
		}
	}
	else puts("Error. There is no data to search.");
	
	save_files();
}

void change_catalogue_name(){
	load_files();
	puts("Enter catalogue's name to change");
	gets(enter);
	
	previous_c=head_c;
	current_c=head_c;
	if(i_pos_c!=0){
		for(ipom_c=1;ipom_c<=i_pos_c;ipom_c++){
			if (strcmp(current_c->title, enter)==0){
				puts("Enter new name");
				gets(enter_2);
				
				check_c=head_c;
				while(check_c!=NULL){
					if (check_c==current_c){
						check_c=check_c->next;
						continue;
					}
					if (strcmp(enter_2, check_c->title)==0){
						puts("Error. The catalogue already exist. Try again.");
						ipom_c=-1;
						break;
					}
					check_c=check_c->next;
				}
				if (ipom_c==-1){
				ipom_c=0;
				continue;
				}
				
				strcpy(current_c->title, enter_2);
				puts("Successfully changed.");
				break;
			}
			previous_c=current_c;
			current_c=previous_c->next;
		}
	}
	else puts("Error. There is no data to search.");
	
	save_files();
}

void show_list_cat(void){
	rewind (fkatalog);
	while (fscanf(fkatalog, "%s\n", &enter)!=EOF)
		puts(enter);
	fclose(fkatalog);
}

void show_catalogue(void){
	load_files();
	puts("Enter catalogue's name you want to show.");
	gets(enter);
	
	previous_c=head_c;
	current_c=head_c;
	if(i_pos_c!=0){
		for(ipom_c=1;ipom_c<=i_pos_c;ipom_c++){
			if (strcmp(current_c->title, enter)==0){
				current_c->previous_list=current_c->head_list;
				current_c->current_list=current_c->head_list;
				while(current_c->current_list!=NULL){
					printf("%15s %10s %10s %10d\n", current_c->current_list->surname, 
					current_c->current_list->name, current_c->current_list->reg_number, 
					current_c->current_list->year);
					current_c->current_list=current_c->current_list->next_lp_ptr;
				}
				ipom_c=0;
				break;
			}
			previous_c=current_c;
			current_c=previous_c->next;
		}
	}
	else puts("Error. There is no data to search.");
	
	save_files();
}

void searching_by_parameter(void){
	load_files();
	
	puts ("Choose search option:");
	puts ("1. By number		2. By year");
	puts ("3. By surname		4. By name");
	puts ("q. Back to menu");
	while (scanf("%d", &x)==1){
		while (getchar() != '\n');
		switch (x){
			case 1: {
				puts("Enter registration number.");
				gets(enter);
				previous_c=head_c;
				current_c=head_c;
				if(i_pos_c!=0){
					for(ipom_c=1;ipom_c<=i_pos_c;ipom_c++){
							current_c->previous_list=current_c->head_list;
							current_c->current_list=current_c->head_list;
							while(current_c->current_list!=NULL){
								if (strcmp(current_c->current_list->reg_number, enter)==0){
									printf("%10s %10s %10s %10s %10d\n", current_c->title, 
									current_c->current_list->surname, current_c->current_list->name, 
									current_c->current_list->reg_number, current_c->current_list->year);
									break;
								}
								current_c->current_list=current_c->current_list->next_lp_ptr;
							}
						previous_c=current_c;
						current_c=previous_c->next;
					}
				}
				else puts("Error. There is no data to search.");
							break;
			}
			case 2: {
				puts("Enter year.");
				scanf("%d", &x);
				previous_c=head_c;
				current_c=head_c;
				if(i_pos_c!=0){
					for(ipom_c=1;ipom_c<=i_pos_c;ipom_c++){
							current_c->previous_list=current_c->head_list;
							current_c->current_list=current_c->head_list;
							while(current_c->current_list!=NULL){
								if ((current_c->current_list->year)==x){
									printf("%10s %10s %10s %10s %10d\n", current_c->title, 
									current_c->current_list->surname, current_c->current_list->name, 
									current_c->current_list->reg_number, current_c->current_list->year);
								}
								current_c->current_list=current_c->current_list->next_lp_ptr;
							}
						previous_c=current_c;
						current_c=previous_c->next;
					}
				}
				else puts("Error. There is no data to search.");
				while (getchar() != '\n');
				break;
			}
			case 3: {
				puts("Enter surname.");
				gets(enter);
				previous_c=head_c;
				current_c=head_c;
				if(i_pos_c!=0){
					for(ipom_c=1;ipom_c<=i_pos_c;ipom_c++){
							current_c->previous_list=current_c->head_list;
							current_c->current_list=current_c->head_list;
							while(current_c->current_list!=NULL){
								if (strcmp(current_c->current_list->surname, enter)==0){
									printf("%10s %10s %10s %10s %10d\n", current_c->title, 
									current_c->current_list->surname, current_c->current_list->name, 
									current_c->current_list->reg_number, current_c->current_list->year);
								}
								current_c->current_list=current_c->current_list->next_lp_ptr;
							}
						previous_c=current_c;
						current_c=previous_c->next;
					}
				}
				else puts("Error. There is no data to search.");
				break;
			}
			case 4: {
				puts("Enter name.");
				gets(enter);
				previous_c=head_c;
				current_c=head_c;
				if(i_pos_c!=0){
					for(ipom_c=1;ipom_c<=i_pos_c;ipom_c++){
							current_c->previous_list=current_c->head_list;
							current_c->current_list=current_c->head_list;
							while(current_c->current_list!=NULL){
								if (strcmp(current_c->current_list->name, enter)==0){
									printf("%10s %10s %10s %10s %10d\n", current_c->title, 
									current_c->current_list->surname, current_c->current_list->name, 
									current_c->current_list->reg_number, current_c->current_list->year);
								}
								current_c->current_list=current_c->current_list->next_lp_ptr;
							}
						previous_c=current_c;
						current_c=previous_c->next;
					}
				}
				else puts("Error. There is no data to search.");
				break;
			}
		}//end of switch
	puts ("Choose next option.");
	}//end of while
	while (getchar() != '\n');
	
	save_files();
}

void delete_pos_from_list(void){
	load_files();
	
	puts("Enter registration number.");
	gets(enter);
	previous_c=head_c;
	current_c=head_c;
	if(i_pos_c!=0){
		for(ipom_c=1;ipom_c<=i_pos_c;ipom_c++){
				current_c->previous_list=current_c->head_list;
				current_c->current_list=current_c->head_list;
				while(current_c->current_list!=NULL){
					if (strcmp(current_c->current_list->reg_number, enter)==0){
						if (current_c->current_list==current_c->head_list){
							current_c->head_list=current_c->head_list->next_lp_ptr;;
							current_c->previous_list=current_c->previous_list->next_lp_ptr;;
							free(current_c->current_list);
							current_c->previous_list=current_c->head_list;
							(current_c->ipos_c)--;
							puts("Successfully removed.");
							break;
						}
						current_c->previous_list->next_lp_ptr=current_c->current_list->next_lp_ptr;;
						free(current_c->current_list);
						current_c->current_list=current_c->previous_list->next_lp_ptr;
						(current_c->ipos_c)--;
						puts("Successfully removed.");
						break;
					}
					current_c->current_list=current_c->current_list->next_lp_ptr;
				}
			previous_c=current_c;
			current_c=previous_c->next;
		}
	}
	else puts("Error. There is no data to search.");
	
	save_files();
}

void add_pos_to_catalogue(void){
	load_files();
	load_file_pos();
	puts("Enter catalogue name you want to change");
	gets (enter);
	current_c=head_c;
	previous_c=head_c;
	if(i_pos_c!=0){
		for(ipom_c=1;ipom_c<=i_pos_c;ipom_c++){
			if(strcmp(current_c->title, enter)==0){
				add_number_cat();
				break;
			}
			previous_c=current_c;
			current_c=previous_c->next;	
		}
	}
	else puts("Error. There is no data to search.");
	save_files();
	save_file_pos();
}

void add_number_cat(void){
	puts("Choose positions to the catalogue."); //Add from list
	puts("Enter registration number you want to add in.");
	while(1){
		gets(number);
		current=head;
		if(i_pos!=0){
			for(ipom=1;ipom<=i_pos;ipom++){
				if (strcmp(current->reg_number, number)==0){
					current_c->current_list=(struct list_of_pos *)malloc(sizeof(struct list_of_pos));	
					if (current_c->head_list==NULL) current_c->head_list=current_c->current_list;
					else current_c->previous_list->next_lp_ptr=current_c->current_list;
					current_c->current_list->next_lp_ptr=NULL;
						
					strcpy(current_c->current_list->surname,current->surname);
					strcpy(current_c->current_list->name,current->name);
					strcpy(current_c->current_list->reg_number,current->reg_number);
					(current_c->current_list->year)=(current->year);
						
					current_c->previous_list=current_c->current_list;			
					(current_c->ipos_c)++;
					ipom_list=-1;
					break;
				}
				previous=current;
				current=previous->next_pos_ptr;
			}
			if (ipom_list==-1){
				ipom_list=0;
				puts("Do you want to add new position to the catalogue? (Yes - 1/ No - 0)");
				scanf("%d", &y);
				while (getchar() != '\n');
				if (y==1){
				puts("Enter new registration number");
				continue;
				}
				else break; //from while(1)
			}
			else {
				puts("There is no such number. Please, enter new number");
				continue; // while(1)
			} 
		}
		else{
			puts("Error. There is no data to search.");
			break;//from while(1)
		}
	}
}

void delete_pos_from_cat(){
	load_files();
	puts("Enter catalogue name you want to change");
	gets (enter);
	current_c=head_c;
	previous_c=head_c;
	if(i_pos_c!=0){
		for(ipom_c=1;ipom_c<=i_pos_c;ipom_c++){
			if(strcmp(current_c->title, enter)==0){
				del_number_cat();
				break;
			}
			previous_c=current_c;
			current_c=previous_c->next;	
		}
	}
	else puts("Error. There is no data to search.");
	save_files();
}

void del_number_cat(void){
	puts("Enter registration number you want to delete.");
	while(1){
		gets(number);
		current_c->current_list=current_c->head_list;
		current_c->previous_list=current_c->head_list;
		if((current_c->ipos_c)!=0){
			for(ipom_list=1;ipom_list<=(current_c->ipos_c);ipom_list++){
				if (strcmp(current_c->current_list->reg_number, number)==0){
					
					if (current_c->current_list==current_c->head_list){
						current_c->head_list=current_c->head_list->next_lp_ptr;
						current_c->previous_list=current_c->previous_list->next_lp_ptr;
						free(current_c->current_list);
						current_c->current_list=current_c->head_list;
						(current_c->ipos_c)--;
						puts("Successfully removed.");
						ipom_list=-1;
						break;
					}
					current_c->previous_list->next_lp_ptr=current_c->current_list->next_lp_ptr;
					free(current_c->current_list);
					current_c->current_list=current_c->previous_list/*->next_lp_ptr*/;
					(current_c->ipos_c)--;
					puts("Successfully removed.");
					ipom_list=-1;
					break;
				}
				current_c->previous_list=current_c->current_list;
				current_c->current_list=current_c->previous_list->next_lp_ptr;
			}
			if (ipom_list==-1){
				ipom_list=0;
				puts("Do you want to delete another position from the catalogue? (Yes - 1/ No - 0)");
				scanf("%d", &y);
				while (getchar() != '\n');
				if (y==1){
				puts("Enter new registration number");
				continue;
				}
				else break; //from while(1)
			}
			else {
				puts("There is no such number. Please, enter new number");
				continue; // while(1)
			} 
		}
		else{
			puts("Error. There is no data to search.");
			break;//from while(1)
		}
	}
}

void move_position(void){
	load_files();
	
	puts("Enter catalogue name from which a position will be moved.");
	gets (enter);
	current_c=head_c;
	previous_c=head_c;
	if(i_pos_c!=0){
		for(ipom_c=1;ipom_c<=i_pos_c;ipom_c++){
			if(strcmp(current_c->title, enter)==0){
				replace_number_cat();
				break;
			}
			previous_c=current_c;
			current_c=previous_c->next;	
		}
	}
	else puts("Error. There is no data to search.");
	
	save_files();
}

void replace_number_cat(void){
	puts("Enter registration number you want to remove");
	while(1){
		gets(number);
		current_c->current_list=current_c->head_list;
		current_c->previous_list=current_c->head_list;
		if((current_c->ipos_c)!=0){
			for(ipom_list=1;ipom_list<=(current_c->ipos_c);ipom_list++){
				if (strcmp(current_c->current_list->reg_number, number)==0){
					
					if (current_c->current_list==current_c->head_list){
						current_c->head_list=current_c->head_list->next_lp_ptr;
						current_c->previous_list=current_c->previous_list->next_lp_ptr;
						
						tmp_c=(struct catalogue *)malloc(sizeof(struct catalogue));
						tmp_c->tmp_list=(struct list_of_pos *)malloc(sizeof(struct list_of_pos));
						tmp_c->tmp_list=current_c->current_list;
						tmp_c->tmp_list->next_lp_ptr=NULL;
						//
						current_c->current_list->next_lp_ptr=NULL;
						free(current_c->current_list);
						//
						current_c->current_list=current_c->head_list;
						(current_c->ipos_c)--;
						search_repl_num_cat();
						break;
					}
					current_c->previous_list->next_lp_ptr=current_c->current_list->next_lp_ptr;
					
					tmp_c=(struct catalogue *)malloc(sizeof(struct catalogue));
					tmp_c->tmp_list=(struct list_of_pos *)malloc(sizeof(struct list_of_pos));
					tmp_c->tmp_list=current_c->current_list;
					tmp_c->tmp_list->next_lp_ptr=NULL;
					//
					current_c->current_list->next_lp_ptr=NULL;
					free(current_c->current_list);
					//
					current_c->current_list=current_c->previous_list->next_lp_ptr;
					(current_c->ipos_c)--;
					search_repl_num_cat();
					break;
				}
				current_c->previous_list=current_c->current_list;
				current_c->current_list=current_c->previous_list->next_lp_ptr;
			}
			if (ipom_list==-1){
				ipom_list=0;
				break;
			}
			else {
				puts("There is no such number. Please, enter new number");
				continue; // while(1)
			} 
		}
		else{
			puts("Error. There is no data to search.");
			break;//from while(1)
		}
	}
}

void search_repl_num_cat(void){
	puts("Enter catalogue name in which position will be moved");
	gets (enter_2);
	current_c=head_c;
	previous_c=head_c;
	if(i_pos_c!=0){
		for(ipom_c=1;ipom_c<=i_pos_c;ipom_c++){
			if(strcmp(current_c->title, enter_2)==0){
				add_repl_num_cat();
				break;
			}
			previous_c=current_c;
			current_c=previous_c->next;	
		}
	}
	else puts("Error. There is no data to search.");
}

void add_repl_num_cat(void){
	current_c->previous_list=current_c->head_list;
	current_c->current_list=current_c->head_list;
	while(current_c->current_list!=NULL){
		current_c->previous_list=current_c->current_list;
		current_c->current_list=current_c->current_list->next_lp_ptr;
	}
	//
	current_c->current_list=(struct list_of_pos *)malloc(sizeof(struct list_of_pos));
	//
	current_c->current_list=tmp_c->tmp_list;
	free(tmp_c->tmp_list);
	free(tmp_c);
	tmp_c->tmp_list=NULL;
	tmp_c=NULL;
	if (current_c->head_list==NULL) current_c->head_list=current_c->current_list;
	else current_c->previous_list->next_lp_ptr=current_c->current_list;
	current_c->current_list->next_lp_ptr=NULL;									
	current_c->previous_list=current_c->current_list;			
	(current_c->ipos_c)++;
	puts("Successfully removed.");
	ipom_list=-1;
}
