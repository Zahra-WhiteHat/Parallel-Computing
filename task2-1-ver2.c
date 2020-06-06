#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

#define N 4 // number of threads
const int COUNT = 100000000;

double calculate_pi(long start, long stop) {
    double s = 0;
    for(int i=start; i<stop; i++) {
        s = s + pow(-1, i+1) * 4 / (2*i - 1);
    }
    return s;
}


int main() {
	pid_t pid;
    int size = COUNT / N;
    struct timeval  tv1, tv2;
    int d[N][2]; // d[i][0] - read, d[i][1] - write

	printf("Main process, pid=%d, ppid=%d\n", getpid(), getppid());
    
    gettimeofday(&tv1, NULL);

    double chunk_sum = 0;
    for(int i=0; i<N; i++) {
        pipe(d[i]); 

        pid = fork();
        if (pid == 0) {
            chunk_sum = chunk_sum + calculate_pi(i*size + 1, i*size+size);
            printf("Chunk sum in process %d is: %.10f \n", i, chunk_sum);
            write(d[i][1], &chunk_sum, sizeof(double));            
            return 0;
        }
    }

    double pi = 0;
    for(int i=0; i<N; i++) {
        double chunk;
        read(d[i][0], &chunk, sizeof(double));
        pi = pi + chunk;
    }

    
    while(wait(NULL) != -1) {}; // To check we in parent process only

    gettimeofday(&tv2, NULL);

    printf("Total pi=%.10f\n", pi);
    printf ("Total time = %f seconds\n",
         (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
         (double) (tv2.tv_sec - tv1.tv_sec));
}