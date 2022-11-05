// Author name : Bhanu Teja Soipeta
//email : bhanu.soipeta@okstate.edu
// Date : 09/11/2022

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct SUM
{
   float id;
   float avgCal;
   float avgSedMin;
   float avgLightActiveMin;
   float avgFairyActiveMin;
   float avgVeryActiveMin;
   float avgSedDis;
   float avgLightActiveDis;
   float avgFairlyActiveDis;
   float avgVeryActiveDis;
   float avgSteps;
//    float avgWL_kg;
//    float avgWL_lb;
};

int **readFile(FILE *fp, int n){
    int** arr = malloc(950 * sizeof(int**));
        for (int i = 0; i < 950; i++){
            arr[i] = (int*)malloc(n * sizeof(int*));
        }

        int i,j;
        char *token;
        char help[500];
        for(i=0; i<941; i++){
            if(fp == NULL) exit(1);
            if(feof(fp)) exit(1);
            fgets(help, 500, fp);
            token = strtok(help,",");
            for(j=0; j<n; j++){
                char* target = strdup(token);
                arr[i][j] = target;
                token = strtok(NULL, ",");
            }    
        }
        return arr;
}


int main(){
    // int n = 200;
    FILE *fp1;
    FILE *fp2;
    FILE *fp3;
    FILE *rm;
    char *token;
    char help[500];
    
    rm = fopen("readFileTemporary.txt", "w");
    
    //read files
    int **dc, **di, **ds;
    fp1 = fopen("dailyCalories.txt", "r");
    dc = readFile(fp1,3);
    fclose(fp1);
    fp2 = fopen("dailyIntensities.txt", "r");
    di = readFile(fp2,10);
    fclose(fp2);
    fp3 = fopen("dailySteps.txt", "r");
    ds = readFile(fp3,3);
    fclose(fp3);
    

//super arr
    int **sa = malloc(sizeof(int**)*950);
        for (int i = 0; i < 950; i++){
            sa[i] = (int*)malloc(16 * sizeof(int*));
        }
        


    for (int i = 0; i < 941; i++) {
        for (int j = 0; j < 16; j++) {
            if(j<3){
            sa[i][j]=dc[i][j];
            }

            if((j>=3) && (j<13)){
            sa[i][j]=di[i][j-3];
            }

            if((j>=13) && (j<16)){
            sa[i][j]=ds[i][j-13];
            }
        }       
    }

     for (int i = 0; i < 941; i++) {
            printf("done\n");
        for (int j = 0; j < 16; j++) {
            printf("%s ", sa[i][j]);
            fprintf(rm, "%s ",sa[i][j]);
        }
    }  


 //deletecolumn
    for (int i = 0; i < 941; ++i) {
        for (int j = 0; j < 16; j++) {
            if(j>=3){
            sa[i][j]=sa[i][j+1];
            }
        }
    }

    for (int i = 0; i < 941; ++i) {
        for (int j = 0; j < 15; j++) {
            if(j>=3){
            sa[i][j]=sa[i][j+1];
            }
        }
    }

    for (int i = 0; i < 941; ++i) {
        for (int j = 0; j < 14; j++) {
            if(j>=11){
            sa[i][j]=sa[i][j+1];
            }
        }
    }

    for (int i = 0; i < 941; ++i) {
        for (int j = 0; j < 13; j++) {
            if(j>=11){
            sa[i][j]=sa[i][j+1];
            }
        }
    }

// summary
    for (int i = 0; i < 941; i++) {
        for (int j = 0; j < 11; j++) {
            // printf("%s ", sa[i][j]);
            fprintf(rm, "%s \t",sa[i][j]);
        }
    }


// output
printf("please enter the respondent ID:");
char input[10];
scanf("%s", &input);

// summary of a singe respondant
struct SUM sum = {0,0,0,0,0,0,0,0,0,0,0,};
int found = 0;
int count = 0;
for(int i=0; i<941; i++){
    char *input = "1503960366";
    if(strcmp(input,sa[i][0]) == 0) {
        found = 1;
        sum.id = atol(input);
        for(int j=0; j<12; j++){
            float avgCal = sa[i][2];
            float avgSedMin = sa[i][3];
            float avgLAMin = sa[i][4];
            float avgFAMin = sa[i][5];
            float avgVAMin = sa[i][6];
            float avgSedDis = sa[i][7];
            float avgLADis = sa[i][8];
            float avgFADis = sa[i][9];
            float avgVADis = sa[i][10];
            float avgSteps = sa[i][11];
            float avgCal = sa[i][12];
            sum.avgCal = sum.avgCal + avgCal;
            sum.avgSedMin = sum.avgCal + atol(sa[i][3]);
            sum.avgLightActiveMin = sum.avgCal + atol(sa[i][4]);
            sum.avgFairyActiveMin = sum.avgCal + atol(sa[i][5]);
            sum.avgVeryActiveMin = sum.avgCal + atol(sa[i][6]);
            sum.avgSedDis = sum.avgCal + atol(sa[i][7]);
            sum.avgLightActiveDis = sum.avgCal + atol(sa[i][8]);
            sum.avgFairlyActiveDis = sum.avgCal + atol(sa[i][9]);
            sum.avgVeryActiveDis = sum.avgCal + atol(sa[i][10]);
            sum.avgSteps = sum.avgCal + atol(sa[i][11]);
            count++;
            // sum.avgWL_kg = sum.avgCal + atol(sa[i][2]);
            // sum.avgWL_lb = sum.avgCal + atol(sa[i][2]);
            
        }
    }
    // if(sa[i][0] == input);
}

//print output
if(found == 0) printf ("invalid input");
else{
    printf("for respondent with ID %lf the summay is\n", sum.id);
    printf("averageCalories = %lf \n", (sum.avgCal)/count);
    printf("averageSedentaryMinutes = %lf \n", (sum.avgSedMin)/count);
    printf("averageLightlyActiveMinutes = %lf \n", (sum.avgLightActiveMin)/count);
    printf("averageFairlyActiveMinutes = %lf \n", (sum.avgFairyActiveMin)/count);
    printf("averageVeryActiveMinutues = %lf \n", (sum.avgVeryActiveMin)/count);
    printf("averageSedentaryActiveDistance = %lf \n", (sum.avgSedDis)/count);
    printf("averageLightlyActiveDistance = %lf \n", (sum.avgLightActiveDis)/count);
    printf("averageFairlyActiveDistance = %lf \n", (sum.avgFairlyActiveDis)/count);
    printf("averageVeryActiveDistance = %lf \n", (sum.avgVeryActiveDis)/count);
    printf("averageSteps = %lf \n", (sum.avgSteps)/count);
    // printf("weightLost_inKg = %lf \n", sum.avgWL_kg);
    // printf("weightLost_inLbs = %lf \n", sum.avgWL_lb);
}


    
}
