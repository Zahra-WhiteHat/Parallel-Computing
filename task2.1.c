// Linear structure of processes: P1 -> P2 -> P3 & P4

#include <unistd.h>
#include <stdio.h>

#define part 4
int n = 7000000;
float pi1;
float pi2;
float pi;

float sum1(n)     
{
	
	for (int i = 0; i < n; i++) { 
		
		pi1 += 1.0/(i*4.0 + 1.0);
   	}
  	return pi1;
}


float sum2(n)       
{
	
	for (int i = 0; i < n ; i++) { 
		pi2 -= 1.0/(i*4.0 + 3.0);
 	}
	return pi2;	
}

float result(float pi1, float pi2,int n)
{
	
	 for (int i = 0; i < n ; i++) { 
	 pi = (pi1+pi2) * 4.0;
	}
	return pi;
}

int main(void) {

 	int size = n / part;
   	//struct timeval  tv1, tv2;
   	int A[part][2]; // d[i][0] - read, d[i][1] - write

	pid_t pid, pid1, pid2, pid_temp, pid_temp1, pid_temp2, pid_temp3; 
	pid_t ppid, ppid1, ppid2, ppid_temp, ppid_temp1, ppid_temp2, ppid_temp3;
	int status, status1, status2, status3;

	printf("Parent start\n");
	pid_temp = getpid();
	ppid_temp = getppid();
	printf(" Parent PID :: %i\n",pid_temp);
	printf(" Parent parent PID :: %i\n",ppid_temp);
	
	double b;
	read(A , &b , 3);

	

	pid = fork();

	if ( pid < 0 ) {        
		return 1;
	}
	else if ( pid == 0 ) {
		//in Child1
		printf("\tChild1 start\n");
		pid_temp1 = getpid();
		ppid_temp1 = getppid();
		printf("\t Child1 PID :: %i\n",pid_temp1);
		printf("\t Child1 parent PID :: %i\n",ppid_temp1);
		
		double r;
		r = result(pi1,pi2,n);
		write(A[1][1], &r , sizeof(double));            
		//write(result(pi1,pi2,n));

		pid1 = fork();
		if ( pid1 < 0 ) {        
			return 1;
		}
		else if ( pid1 == 0 ) {
			//in Child2
			printf("\t\tChild2 start\n");
			pid_temp2 = getpid();
			ppid_temp2 = getppid();
			printf("\t\t Child2 PID :: %i\n",pid_temp2);
			printf("\t\t Child2 parent PID :: %i\n",ppid_temp2);

			double s1;
			s1 = sum1(n);
			write(A[1][2], &s1 ,sizeof(double)); 
			//write(sum1(n));

			return 0; // for stops Child2
		}
		pid1 = fork();
		if ( pid1 < 0 ) {        
			return 1;
		}
		else if ( pid1 == 0 ) {
			//in Child3
			printf("\t\tChild3 start\n");
			pid_temp3 = getpid();
			ppid_temp3 = getppid();
			printf("\t\t Child3 PID :: %i\n",pid_temp3);
			printf("\t\t Child3 parent PID :: %i\n",ppid_temp3);
			
			double s2;
			s2 = sum2(n);
			write(A[2][1], &s2 , sizeof(double));  
			//write(sum2(n));

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
