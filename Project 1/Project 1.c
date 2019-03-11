#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

pid_t valid_fork(void);

int main(int argc, char *argv[])
{
    //initization
    int input;//input by user
    int status;//for waitpid parameter's point
    int MAXLEVEL = 5;//max level 
    pid_t firstchildPID = 0;//initialize first child
    pid_t secondchildPID = 0;//initialize second child
    
    //examine user input
    if(argc != 2) {
        printf("ERROR: you should enter one arguement as level you wait generate to run the program\n");
        exit(1);
    }
        
    //get input
    input = atoi(argv[1]);

    //deal with invalid input
    if(input > MAXLEVEL) {
        printf("ERROR:change the level to 5 according to the requirement");
        input = MAXLEVEL;
    }
    else if(input < 1){
        printf("ERROR:change the level to 1 according to the requirement");
        input = 1;
    }

    printf("\nLevel\tProcs\tParent\tChild 1\tChild 2\n");
    printf("No.\tID\tID\tID\tID\n");
          
    //main part: binary tree generation by for loop
        for(int currentLevel = 0; currentLevel <= input; currentLevel++){ 
        //when child process of level 4 created by its level 3 parent, it also copy firstchildPID from its parent. However, now there is no new firstchildPID cover the old one, so we directly lead i to 0. Actually, there is no child of level 4 process.
        	if(currentLevel == input)
        		firstchildPID = 0;
    	if(currentLevel < input){
    		//create first child
	    	firstchildPID = valid_fork();
	    	//only parent process who has already created first child can create second
	        	if(firstchildPID != 0)
	        		secondchildPID = valid_fork();
        	}
  	//make sure the result print in level order by sleep function
        	sleep(currentLevel);

        	//print out process result who has both first and second child
        	//if it is level 4, directly print
        	if((firstchildPID > 0 && secondchildPID > 0)||currentLevel == input ){
        		printf("%d\t%ld\t%ld\t%ld\t%ld\n", currentLevel, (long)getpid(), (long)getppid(), (long)firstchildPID, (long)secondchildPID);
        		break;
        	}
    }
    
    //parents must waits for each child to complete processing before exiting(avoid zombie)
    waitpid(firstchildPID, &status, 0);
    waitpid(secondchildPID, &status, 0);
    exit(0);
}

//function used to check whether new process generate successfully
//@para: null
//@return: pid  the new process
pid_t valid_fork(){
    pid_t pid;
    if ((pid = fork()) < 0)
    {
        perror ("\n ERROR:problem when generate process");
        exit(1);
    }
    return pid;
}


// // Brett Tomita - Project 1
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/types.h>

// int main(int argc, char *argv[])
// {
//     if(argc < 2) // If no parameter is passed for the number of levels, display a message & quit
//     {
//             printf("ERROR: Please provide the number of levels the tree should have (1-5)\n");
//             return 0;
//     }
// 	int levels = atoi(argv[1]);  // Get number of levels the binary tree should have from 1'st argument
//     pid_t left, right;	//  Split tree into 2 halves: left & right
//     printf("\n\tLevel\tProcess ID\tParent ID\tChild 1 ID\tChild 2 ID\n ");	// Column Headers

//     // fork in binary tree format
//     for(int i=0; i<=levels; i++)
//     {
//     	// Make sure last level of children don't have any child processes
//     	if(i == levels)
//     	{
//     		while(left != 0 || right != 0)
//     		{
//     			waitpid(left, WUNTRACED, 0);
//     			waitpid(right, WUNTRACED, 0);
//     		}
//     		printf("\t%i\t%d\t\t%d\t\t%d\t\t%d\n",i, getpid(),getppid(), left, right);
//     		exit(0);
//     	}
//         else if((left = fork()) && (right = fork()) && i < levels)	// Left and right halves of binary tree create children
//         {
// 	        printf("\t%i\t%d\t\t%d\t\t%d\t\t%d\n",i, getpid(),getppid(), left, right);// print parent & child info
// 	        if(wait(NULL) > 0) // Wait for children
// 	        {
// 	        	sleep(i);
// 	        	exit(0);
// 	        }
//         }
//     }
//     exit(0);
// }

	
