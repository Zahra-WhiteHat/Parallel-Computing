// Linear structure of processes: P1 -> P2 -> P3 & P4

#include <unistd.h>
#include <stdio.h>

int main(void) {
	pid_t pid, pid1, pid2, pid_temp, pid_temp1, pid_temp2, pid_temp3; 
	pid_t ppid, ppid1, ppid2, ppid_temp, ppid_temp1, ppid_temp2, ppid_temp3;
	int status, status1, status2, status3;

	printf("Parent start\n");
	pid_temp = getpid();
	ppid_temp = getppid();
	printf(" Parent PID :: %i\n",pid_temp);
	printf(" Parent parent PID :: %i\n",ppid_temp);

	pid = fork();

	if ( pid < 0 ) {        
		return 1;
	}
	else if ( pid == 0 ) {
		// in Child1
		printf("\tChild1 start\n");
		pid_temp1 = getpid();
		ppid_temp1 = getppid();
		printf("\t Child1 PID :: %i\n",pid_temp1);
		printf("\t Child1 parent PID :: %i\n",ppid_temp1);
		pid1 = fork();
		if ( pid1 < 0 ) {        
			return 1;
		}
		else if ( pid1 == 0 ) {
			// in Child2
			printf("\t\tChild2 start\n");
			pid_temp2 = getpid();
			ppid_temp2 = getppid();
			printf("\t\t Child2 PID :: %i\n",pid_temp2);
			printf("\t\t Child2 parent PID :: %i\n",ppid_temp2);

			return 0; // for stops Child2
		}
		pid1 = fork();
		if ( pid1 < 0 ) {        
			return 1;
		}
		else if ( pid1 == 0 ) {
			// in Child3
			printf("\t\tChild3 start\n");
			pid_temp3 = getpid();
			ppid_temp3 = getppid();
			printf("\t\t Child3 PID :: %i\n",pid_temp3);
			printf("\t\t Child3 parent PID :: %i\n",ppid_temp3);
			
			return 0; // for stops Child3
		}
		else {
			// in Child1
			// Waiting for Child2       
			wait(&status1);
			printf("\tChild1 stopped\n");
		}        
		return 0; // for stops Child1
	}
	else {
		// Parent process
		// Waiting for Child1       
		wait(&status);
		printf("Parent stopped\n");
	} 
	return 0; // for stops Parent
}
