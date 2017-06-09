//
//  main.c
//  Detyra e kursit 2016
//
//  Created by Aldi Topalli on 20/05/16.
//  Copyright © 2016 Code Art. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct person{
    char name[20];
    char surname[20];
    char address[20];
    char number[20];
    char email[30];
} Person;

struct {
    FILE* pFile;
    char* path;
    int nr;
} global = {
    NULL,
    "/Users/user_name/Desktop/db.bin", //Replace user_name with your computer username
    0                                   //For windows use the approriate file path
};

Person database[200];

void clearstdin(){
    while(getchar() != '\n'){
        continue;
    }
}

void readF();
void instructions();
void reg();
int check(Person p);
void modify();
void order();
void del();
void search();
int from_name();
int from_number();
void save();
void statistika();
void nameLetter();
void sameSurname();
void companies();
void emailWrong();


int main(int argc, const char * argv[]) {
    
    if(!(global.pFile = fopen(global.path, "rb"))){
        if(!(global.pFile = fopen(global.path, "wb"))){
            perror("File cannot be found or opened!!\n");
        }
    }
    readF();
    
    int code = -1;
    
    while (code != 0) {
        instructions();
        scanf("%d", &code);
        switch (code) {
            case 1:
                reg();
                break;
            case 2:
                modify();
                break;
            case 3:
                del();
                break;
            case 4:
                search();
                break;
            case 5:
                order();
                break;
            case 6:
                statistika();
                break;
            case 7:
                system("clear");
                break;
            case 0:
                code = 0;
                save();
                break;
            default:
                printf("\nKodi i gabuar!!\n");
                code=0;
                break;
        }
    }
    
    
    
    return 0;
}



void readF(){
    global.pFile = fopen(global.path, "rb");
    if(global.pFile == NULL){
        perror("File cannot be opened!");
        exit(-1);
    }
    
    while(fread(&database[global.nr], sizeof(Person), 1, global.pFile)){
        global.nr++;
    }
    
    fclose(global.pFile);
}

void instructions(){
    printf("===============================================================\n");
    printf("                       INSTRUCTIONS\n");
    printf("===============================================================\n");
    printf("Type 1 to register a new person.\n");
    printf("Type 2 to modify the existing data of a person.\n");
    printf("Type 3 to delete an existing person.\n");
    printf("Type 4 to search a certain person.\n");
    printf("Type 5 to print in alphabetical order based on name and surname"
           " existing persons on the database.\n");
    printf("Type 6 to get some statistics.\n");
    printf("Type 7 to \"clear\" the screen.\n");
    printf("Type 0 to close the program.\n");
    printf("Your command: ");
}

void reg(){
    Person kontroll;
    
    printf("                   A person's data\n");
    printf("---------------------------------------------------------------\n");
    clearstdin();
    printf("Name: ");gets(kontroll.name);
    printf("Surname: ");gets(kontroll.surname);
    printf("Address: ");gets(kontroll.address);
    printf("Private Number: ");gets(kontroll.number);
    printf("Email: ");gets(kontroll.email);
    
    if(!check(kontroll)){
        database[global.nr] = kontroll;
        global.nr++;
    }
}

int check(Person p){
    
    
    for(int i = 0; i < global.nr; i++){
        if(strcmp(p.name, database[i].name) == 0 &&
           strcmp(p.surname, database[i].surname) == 0){
            printf("---------------------------------------------------------------"
                   "----\n");
            printf("              Given person already exists in the database.\n");
            printf("---------------------------------------------------------------"
                   "----\n");
            return 1;
        }
    }
    
    return 0;
    
}

void modify(){
    Person p;
    int flag = 0;
    
    printf("Give the required info of the person you want to modify.\n");
    clearstdin();
    printf("name: ");gets(p.name);
    printf("surname: ");gets(p.surname);
    
    for(int i = 0; i < global.nr; i++){
        for(int j = 0; j < strlen(database[i].name); j++){
            if(database[i].name[j] >= 65 && database[i].name[j] <= 90){
                database[i].name[j] = database[i].name[j] + 32;
            }
        }
        
        for(int j = 0; j < strlen(database[i].surname); j++){
            if(database[i].surname[j] >= 65 && database[i].surname[j] <= 90){
                database[i].surname[j] = database[i].surname[j] + 32;
            }
        }
    }
    
    for(int i = 0; i < strlen(p.name); i++){
        if(p.name[i] >= 65 && p.name[i] <= 90){
            p.name[i] = p.name[i] + 32;
        }
    }
    for(int i = 0; i < strlen(p.surname); i++){
        if(p.surname[i] >= 65 && p.surname[i] <= 90){
            p.surname[i] = p.surname[i] + 32;
        }
    }
    
    for(int i = 0; i < global.nr; i++){
        if(strcmp(p.name, database[i].name)==0 &&
           strcmp(p.surname, database[i].surname) == 0){
            printf("Name found. Give other data.\n");
            clearstdin();
            printf("Name: ");gets(database[i].name);
            printf("Surname: ");gets(database[i].surname);
            printf("Address: ");gets(database[i].address);
            printf("Number: ");gets(database[i].number);
            printf("Email-i: ");gets(database[i].email);
            
            flag++;
        }
    }
    
    if(flag == 0){
        printf("-------------------------------------------------------------------\n");
        printf("       Person does not exist in our database.\n");
        printf("-------------------------------------------------------------------\n");

    }
    
}


void order(){
    for(int i = 0; i < global.nr; i++){
        for(int j = 0; j < strlen(database[i].name); j++){
            if(database[i].name[j] >= 65 && database[i].name[j] <= 90){
                database[i].name[j] = database[i].name[j] + 32;
            }
        }
        
        for(int j = 0; j < strlen(database[i].surname); j++){
            if(database[i].surname[j] >= 65 && database[i].surname[j] <= 90){
                database[i].surname[j] = database[i].surname[j] + 32;
            }
        }
    }
    
    
    for(int i = 0; i <= global.nr; i++){
        for(int j = i+1; j < global.nr; j++){
            if((strcmp(database[j].name, database[i].name)<0)){
                Person temp = database[i];
                database[i] = database[j];
                database[j] = temp;
            }
        }
    }
    printf("-------------------------------------------------------------------\n");
    printf("name\t\tsurname\t\taddress\t\tnumber\t\tEmail\n");
    printf("-------------------------------------------------------------------\n");
    
    for(int i = 0; i < global.nr; i++){
        printf("%s\t\t%s\t\t%s\t\t%s\t%s\n", database[i].name,
               database[i].surname, database[i].address, database[i].number,
               database[i].email);
    }
    
}

void del(){
    Person p;
    int start_pos;
    
    printf("\nGive info of the person you want to delete.\n");
    clearstdin();
    printf("Name: ");gets(p.name);
    printf("Surname: "); gets(p.surname);
    
    
    for(int i = 0; i < global.nr; i++){
        if((strcmp(p.name, database[i].name) == 0)&&
           (strcmp(p.surname, database[i].surname) == 0)){
            start_pos = i;
            
            for(int j = start_pos; j < global.nr-1; j++){
                database[j] = database[j+1];
            }
            global.nr--;
            printf("-------------------------------------------------------------"
                   "------\n");
            printf("                    Deletion successful!\n");
            printf("-------------------------------------------------------------"
                   "------\n");
            return;
        }
    }
    
    printf("-------------------------------------------------------------------\n");
    printf("                Deletion not successful!\n");
    printf("-------------------------------------------------------------------\n");

}

void search(){
    int k = 0;
    
    printf("Choose search criteria.\n");
    printf("-------------------------------------------------------------------\n");
    printf("Type 1 to search based on name.\n");
    printf("Type 2 to search based on phone number.\n");
    printf("Your choice: ");scanf("%d", &k);
    
    switch (k) {
        case 1:
            if(from_name() == -1){
                printf("\nGiven person not found.\n");
            }
            break;
        case 2:
            if(from_number() == -1){
                printf("\nPerson with the given number not found.\n");
            }
            break;
            
        default:
            printf("Given code is wrong!\n");
            return;
            break;
    }
    
    printf("-------------------------------------------------------------------\n");
}

int from_name(){
    Person p;
    
    printf("Give the person to search.\n");
    clearstdin();
    printf("name: "); gets(p.name);
    printf("surname: ");gets(p.surname);
    
    for(int i = 0; i < global.nr; i++){
        if(strcmp(p.name, database[i].name) == 0 &&
           strcmp(p.surname, database[i].surname) == 0){
            printf("\nPerson found!!\n");
            printf("%s\t%s\t%s\t%s\t%s\n", database[i].name, database[i].surname,
                   database[i].address, database[i].number, database[i].email);
            return i;
        }
    }
    
    return -1;
}


int from_number(){
    Person p;
    clearstdin();
    printf("\nGive number:");gets(p.number);
    
    for(int i = 0; i < global.nr; i++){
        if(strcmp(p.number, database[i].number) == 0){
            printf("\nPerson found!!\n");
            printf("%s\t%s\t%s\t%s\t%s\n", database[i].name, database[i].surname,
                   database[i].address, database[i].number, database[i].email);
            return i;
        }
    }
    return -1;
}


void save(){
    global.pFile = fopen(global.path, "wb");
    
    for(int i = 0; i < global.nr; i++){
        fwrite(&database[i], sizeof(Person), 1, global.pFile);
    }
    
    
    fclose(global.pFile);
}

void statistika(){
    int zgjedhja = -1;
    printf("-------------------------------------------------------------------\n");
    printf("Choose the criteria to print statistics.\n");
    printf("Type 1 to show how many persons are there in the database.\n");
    printf("Type 2 to show the memory occupied by the database.\n");
    printf("Type 3 to show how many person's name starts with a given letter/\n");
    printf("Type 4 to show persons with the same surname, if yes how many.\n");
    printf("Type 5 to show how many persons are clients in one of the Albania's"
           " biggest telephone companies.\n");
    printf("Type 6 to show how many email addresses are not correct.\n");
    printf("Your choice: ");scanf("%d", &zgjedhja);
    printf("-------------------------------------------------------------------\n");
    switch (zgjedhja) {
        case 1:
            printf("\nUntil now there are %d person%c registered in the database.\n",
                   global.nr, (global.nr==1)?:'s');
            break;
        case 2:
            printf("\nFile occupies %zu byte.\n",
                   sizeof(Person)*global.nr);
            break;
        case 3:
            nameLetter();
            break;
        case 4:
            sameSurname();
            break;
        case 5:
            companies();
            break;
        case 6:
            emailWrong();
            break;
        default:
            break;
    }
    
    
    
    printf("-------------------------------------------------------------------\n");
}

void nameLetter(){
    char g;
    int cnt = 0;
    printf("Give the letter: ");
    clearstdin();
    scanf("%c", &g);
    
    for(int i = 0; i < global.nr; i++){
        if(database[i].name[0] == g){
            printf("%s\n", database[i].name);
            cnt++;
        }
    }
    
    if(cnt == 0){
        printf("\nNone of the existing names starts with the given letter.\n");
    }
}

void sameSurname(){
    printf("\n");
    for(int i = 0; i < global.nr; i++){
        for(int j = i+1; j < global.nr; j++){
            if(strcmp(database[i].surname, database[j].surname)==0)
                printf("%s %s---%s %s\n", database[i].surname, database[i].name,
                       database[j].surname, database[j].name);
        }
    }
}

void companies(){
    char* vod = "069", *tkom="068", *eag="067"; // each company's prefix numbers
    int v=0, t=0, e=0;
    
    for(int i = 0; i < global.nr; i++){
        if(strncmp(database[i].number, vod, 3) == 0){
            v++;
        }else if(strncmp(database[i].number, tkom, 3) == 0){
            t++;
        }else if(strncmp(database[i].number, eag, 3) == 0)
            e++;
    }
    
    printf("In the database there is a total of:\n");
    printf("%d numbers from \"Vodafone Albania\".\n", v);
    printf("%d numbers from \"Telekom Albania\".\n", t);
    printf("%d numbers from \"Eagle Mobile\".\n", e);
}

void emailWrong(){
    int check = 0;
    char c = '@';
    
    for(int i = 0; i < global.nr; i++){
        if(!strchr(database[i].email, c))
            check++;
    }
    
    printf("\nThere is a total of %d emails not in the right format in the database"
           " (do not contain the character \'@\')\n", check);
    
}









