#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#define NUM_THREADS 10

 
char **bookNames; // books entered by user
int c = 0; // number of books entered by user
int found[100]; // books found or not

// read and serach files for given book names
// function given as input to threads
void *ReadFile(void* filename) {
    
    FILE *file;
    file = fopen(filename, "r");
    
    char help[20000];
    char *string;

    if(file == NULL){
        printf("Unable to open file.\n");
        return;
    }

    //structure of books
    struct Records{
    char title[255];
    char genre[255];
    char rating[255];
    char summary[10000];
    };

    struct Records books[650];

    int cols = 0;
    int rows = 0;
    int i = 0;
    int count = 0;

    //reads the file
    while(fgets(help, sizeof(help), file) != NULL){
    // reads one line of file into help2
        cols = 0;
        rows++;
        
        if(rows == 1){
            continue;
        }

        if ((strlen(help)>0) && (help[strlen (help) - 1] == '\n')){//removes any new line indicators
            help[strlen (help) - 2] = '\0';
        }
         // seperates the sentence by comma unless it is between quotes
        string = strtok(help, ",(?=([^\"]*\"[^\"]*\")*[^\"]*$)");

        count = 0;
        // stores the file details in array of structs
        while(string){
        
            if(cols == 0){
                    strcpy(books[i].title, string);
            }
             
            if(cols == 1){
                strcpy(books[i].genre, string);
            }

            if(cols == 2){
                strcpy(books[i].rating, string);
            }

            if(cols == 3){
                strcpy(books[i].summary, string);
                break;
            }

            
            count++;
            if(count < 3){
                string = strtok(NULL, ",(?=([^\"]*\"[^\"]*\")*[^\"]*$)");
            }
            else{
                string = strtok(NULL,"\"");
            }
            cols++;
        }
        i++;
    }
    
    printf("Thread with thread_id = %d is being cancelled\n", pthread_self());
    fclose(file);
    printf("%s file closed\n", filename);

    //searches for the user given book names in the files read by program
    for(int j=0; j<c; j++){
        for(int a=1; a<rows; a++){
            if(strcmp(books[a].title, bookNames[j]) == 0){       
                printf("%s\t %s\t %s\n %s\n", books[a].title, books[a].genre, books[a].rating, books[a].summary);
                found[j] = 0;// found is made 0 for found book
                break;
            }
        }
    }

   pthread_exit(NULL);
}

   
//main function 
void main(int argc, char *argv[]){

    char name[300];
    printf("Enter the number of books in the list: ");
    scanf("%d",&c);
    getchar();
    bookNames = (char **)malloc(sizeof(char *) * c);
    //user input
    for(int j=0; j<c; j++) {
    bookNames[j] = (char *)malloc(sizeof(char) * 32);
    printf("Enter the book name: ");
    gets(bookNames[j]);
    }

    //found is declared as all one's
    for(int j=0; j<c; j++){
        found[j] = 1;
    }

    //creating threads
    pthread_t threads[NUM_THREADS];
    for(int i = 0 ; i<argc-1 ; i++){
        pthread_create( &threads[i], NULL , ReadFile , argv[i+1]);
        pthread_join(threads[i], NULL);
    }

    for(int j=0; j<c; j++){
        if(found[j] == 1){
             printf("%s not found \n", bookNames[j]);
        }
    }
}
