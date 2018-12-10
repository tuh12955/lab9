#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define LIMIT_TO_READING_LINES 30
#define NUMBER_OF_QUESTIONS_PER_STUDENT 11
#define ERROR_CODE_IN_INPUT_SCANNING 'e'

void display_startup_banner();
void printCSVFile(char *fname, char *fname1, char *csvFile);



/*
 * Location: Temple University Computer Science
 * Programmer: Alyssa Debrosse
 * Class: Introduction to C Programming 1057 Fall 2018 Section 005
 * Assignment: 9 - Bubble CSV and Github
 * Date: December 9, 2018
 * Version: 1
 * Description: Comparing each students id number on file one to their id number on file two in order to discover full 
 * name of student along with reported answers and grades. 
 *
 */

int main (){

	printCSVFile("newomr.txt","test_taker_names.txt","full_data.csv");


	return EXIT_SUCCESS;
}

/*
 * Function: display_startup_banner()
 * Programmer: Alyssa Debrosse
 * Date: Decemeber 9, 2018
 * Inputs:none
 * Outputs:none
 * Globals:__DATE__ __TIME__
 * Returns:none 
 * Description: Displays startup message to user
 *
 */

void display_startup_banner(){

	printf("GRADING OMR FORMS PROGRAM WRITTEN IN C \n");
	printf("Program written by Alyssa Debrosse. \n\n");
	printf("Program compiled on %s at %s\n\n", __DATE__, __TIME__);
}

/*
 * Function: printCSV()
 * Programmer: Alyssa Debrosse
 * Date: Decemebr 9, 2018
 * Inputs:char *fname, char *fname1, char *csvFile 
 * Outputs:none 
 * Globals:NUMBER_OF_QUESTIONS_PER_STUDENT, LIMIT_TO_READING_LINES, ERROR_CODE_IN_INPUT_SCANNING
 * Returns:none
 * Description: printing out CSV data to user in new file
 *
 */
 
void printCSVFile(char *fname, char *fname1, char *csvFile){

	FILE *firstFile=fopen(fname, "r");
	FILE *newFile=fopen(csvFile, "w+");

	fprintf(newFile,"IDENTITY, NAME, Q1,Q2,Q3,Q4,Q5,Q6,Q7,Q8,Q9,Q10,Q11,GRADE\n");
	int id;
	char scores[NUMBER_OF_QUESTIONS_PER_STUDENT];
	double grades[LIMIT_TO_READING_LINES];
	int count = 0;
	int i;
	int number_of_questions;
	char key[NUMBER_OF_QUESTIONS_PER_STUDENT+1];

	display_startup_banner();

	if(!firstFile){
		printf("Error opening first file %s. \n", fname);
		perror(fname);
		return;
  	}
	if(fscanf(firstFile, "%d", &id)==1){
		fscanf(firstFile, "%s", key);
		number_of_questions= strlen(key);
 	}
	printf("Read in the answer key:\n");
	for(i=0; i< number_of_questions; i++){
		printf("\tQuestion %d: %c\n", i+1, key[i]);
	}
	int error=0;
	count = 0;
	int cc = 0;
	int grade = 0;

	while(!feof(firstFile)&& (fscanf(firstFile, "%d", &(id))==1)){
		for(i=0; i< number_of_questions; i++){
			fscanf(firstFile, "%c", &(scores[i]));
		}
	for(i=0; i < number_of_questions; i++){
		if(scores[i] == key[i]){
			grade++;
		}
		else{
			if(scores[i]== ERROR_CODE_IN_INPUT_SCANNING){
				error=1;
			}
		}
	}

	int id1;
	char nm[128];
	FILE *secondFile=fopen(fname1, "r");

	if(!secondFile){
		printf("Error opening input file %s. \n",fname1);
		perror(fname);
		return;
	}
	while(!feof(secondFile)&&(fscanf(secondFile, "%d", &(id1))==1)){

		fscanf(secondFile,"%[^\n]s",nm);
			if(id==id1){
				fprintf(newFile,"%05d,%s,",id,nm);
				for(i=0; i <number_of_questions; i++)
					fprintf(newFile, "%c,", scores[i]);
		    		fprintf(newFile, "%d%%\n", 100 *(grade)/ number_of_questions);
			}
	}
	close(secondFile);

  close(newFile);
}
}

