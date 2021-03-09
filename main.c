/*
*    Function Name : main.c
*  
*    Purpose : this is the main function of the assingment, in this file, the program runs and checks the input from the command line. It checks 
*    if there is the right amount of arguments. The program is given a file that has some option of items that has the name of the object, the 
*    weight of the object, and the price of the object. it then rins through the maxVal function and figures out the best inventory price option.
*
*    Inputs
*    argc - this checks how much arguments there are in the command line
*    char *argv[] - this stores the argument in a string
*
*    Return:
*    0 - command line problems, too much capacity, when the program is done running
*    2 - empty file
*    134- file is too big
*
*    For this programming assignment, I used global varibales
*
*/
#include <stdio.h>    //includes
#include <string.h>

int value[129];			//this array is for the value of the item
char name[129][33];		//this array is for storing the array names of the items
int weight[129];		//this array is for the storing of the weight of the item
int store[1025][129];		//this array is for the storing of the maxVal values and the inventory that fit those values
int maxValue[1025];		//this array is for storing the prices of the max values
int maxCount;			//this is an int for the maxCount, it it used to checks how much items there is

int maxVal(int cap);		//max Val function

int main(int argc, char *argv[] ) {		//command line arguments

  char file[50], buffer[60];			//some varibles derfined
  int cap;				
  if(argc == 3){				//wants the total of 3 arguments
    if(sscanf(argv[1], "%d", &cap) != 1){	//checks it to be an integer
      printf("Usage: knapsack capacity itemfile\n");
      return 0;
    }
    if(cap > 1024 || cap < 1) {			//range of 1 to 1024 capacity
      printf("Illegal capacity: should be between 1 and 1024\n");
      return 0;
    }
    for(int n=0; n < 1025; n++){		//for loop for setting the maxValues to -1, useful for the maxVal function
      maxValue[n]=-1;
      for(int m=0; m < 129; m++){		//for loop for setting the store to 0, usefule for the maxVal function, initliazing
        store[n][m]=0; 
      }
    }
    maxCount = 0;
    sscanf(argv[2], "%s", file);		//open file and read in the file row by row
    FILE *fp;
    fp=fopen(file, "r");
    if(fp == NULL) {   
      printf("Error: no weight/value pairs read\n");	//if NULL returns message
      return 2;
    }
    while(NULL != fgets(buffer, 60, fp)) { 
      sscanf(buffer, "%s %d %d", name[maxCount], &value[maxCount], &weight[maxCount]);    	//breaks up the line into separate arrays
      maxCount++;  										//counter
    }
    fclose(fp);					//closes file
    if(maxCount > 128) {			//if file is too bigm prints out error and exits
      printf("ERROR: Inventory contains too many items (max=128\nError: no weight/value pairs read\n*** stack smashing detected ***: knapsack terminated\nAborted\n");
      return 134;
    }
    if(maxCount == 0) {				//if file is empty, prints out message and exits
      printf("Error: no weight/value pairs read\n");
      return 2;
    }
    printf(" Weight  Value  Name\n");		//this is the printing out of the characteristics
    printf(" ------  -----  ----\n");
    for(int i=0; i != maxCount; i++){
      printf("%5d %7d  %s\n", weight[i], value[i], name[i]);		//loop to print out all the options into neat columns
    }
    printf("--------------------\n");
    printf("Bag's capacity=%d\n", cap);					//prints out the capacity
    printf("Highest possible value=%d\n", maxVal(cap));			//most value avaliable to get(this is the call of the maxVal function)
    for(int i=0; i < maxCount; i++) {					//this goes through the store and prints out all the items that can
      if(store[cap][i] != 0) {						//be taken for the best "deal"
        printf("Item %d (%s): %d\n", i, name[i], store[cap][i]);
      }
    }
  }
  else {
    printf("Usage: knapsack capacity itemfile\n");			//error message for incorrect argument count
    return 0;
  }
  return 0;								//end of program returns 0
          
}

/*
*  Function name: maxVal
*
*  Purpose : this is the funcion that find the best choice of the given capacity to get the biggest price. It stores the items that can be taken
*  for the best choice.
*
*  Inputs
*  cap - the given capacity
*
*   Returns:
*   0 - if the capacity is equal to 0
*  best - returns the best price of the given capacity
*/

int maxVal(int cap) {         			//this is the maxVal function that does most of the work of the program
  if(cap == 0) {				//checks if the capacity is 0 and if it is returns 0
    return 0;
  }
  if(maxValue[cap] != -1) {			//runs through the array and checks if the value is not -1
    return maxValue[cap];			//-1 means there was no value store that is needed
  }						//returns the maxValue[cap] it stores the total prices
  int best=0, present, item=-1;			//variable definitions
  for(int i=0; i < maxCount; i++) {		//for loop in order to check every option of the store
    if(( cap-weight[i] >= 0 )){			//checks if the asnwer will be greater than or equal to 0
      present=value[i]+maxVal(cap-weight[i]);	//recursive call for the maxVal to find the best option, sets it equal to present
      if(present > best){			//if the present is better or greater that the best
        best=present;				// sets the best equal to present
        item=i;					//and define item equal to i
      }
    }
  }
  for(int i=0; i < maxCount; i++) {    		//for loop to go up to maxCount which is how much options there is 
    store[cap][i]=store[cap-weight[item]][i];	//saves the store items
  }
  if(item != -1) {				//checks if the item is not -1 and then adds to it
    store[cap][item]++;
  }
  maxValue[cap]=best;				//stores the best price
  return best;					//returns best
}
