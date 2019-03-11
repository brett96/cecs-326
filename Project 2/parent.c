# include<stdio.h>
# include<stdlib.h>
# include<sys/types.h>
# include<unistd.h>

int main(int argc, char *argv[]) 
{
    int i, arg1, arg2, sleepLen, numProcs;		// A = Argument 1 // B = Argument 2 // T = Sleeptime // n = Number of processes 
    pid_t cPid;		// Child PID
    char childNum[3]; 		// Character array for child number
   
    if (argc !=4) 		// If arguments are not 4 inputs
    { 
      printf("Invalid inputs, requires 4 arguments.\n", argv[0]); 
      exit(1); 
    }
    numProcs = 4;     // Number of processes = 4
    sleepLen = atoi(argv[1]);   // Argument index 1 is maximum sleeptime T
    arg1 = atoi(argv[2]); // Argument index 2 is first integer
    arg2 = atoi(argv[3]); // Argument index 3 is second integer

    if (sleepLen > 50 || sleepLen <= 0) // If argument T is greater than 50, 0, or negative, throw exception
    { 
      printf("Input error.\nMax sleeptime must be between 0 and 50.\n"); 
      exit(1); 
    }
    srand(time(NULL));
    // Print parent process, max sleep, and the two arguments
    printf("I am parent process, the maximum sleep time is %d and the two numbers are %d and %d.\n", sleepLen, arg1, arg2);
    // Sleep using T	
    sleep(rand()%sleepLen); 
    // Generate child processes using fork()
    for (i=0; i<numProcs;i++) 
    {  
        switch(cPid = fork())
        {
         case 0:
         	  sprintf(childNum, "%d", i);
         	  // Invoke child program, pass child number, sleeptime and arithmetic arguments
         	  execl("c2", argv[1], argv[2], argv[3], (char *)0);
         	  // If not, exec failure
         	  perror("Exec failure");
              return(1);
         case -1:
         	  // Fork failed
              perror ("The fork failed.\n"); 
          	  return(2); 
	 default:
	      // Print Forked Child 
	      printf("\nForked child %d\n", cPid);    
         }    // End switch
    } // End for
    exit(0);
}