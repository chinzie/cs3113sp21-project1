#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
	printf("starting\n");
	char *buf = (char *) malloc (1000000 *  sizeof(char));
	int count = 0;
	int index = 0;
	int P; //Processes available to run instructions (always 1)
        int p; //Number of threads (amount of processes)
        int N; //Number of instructions (number of instruction lines)
	char temp[100000];
	char pid[100000];
	char burst[100000];
	printf("done starting\n");
	if (argc > 1)
	{
		printf("argc is > 1\n");
		FILE *file_handle;
		file_handle = fopen(argv[1], "r");
		printf("allocating\n");
        	while (fgets(buf, 1, file_handle) != NULL)
        	{
                	buf[index] = *buf;
                	unsigned char c = buf[index];
                	if (buf[index] == '\n'|| buf[index] == ' ')
                	{
                        	//printf("newline");
                        	continue;
                	}
                	if (count == 0)
                	{
                        	//printf("P is set\n");
                        	P = c - '0';

                	}
                	if (count == 1)
                	{

                        	//printf("p is set\n");
                        	p = c - '0';
                	}
                	if (count == 2)
                	{	

                        	//printf("N is set\n");
                        	N = c - '0';
                	}
                	if (count > 2)//start reading instructions
                	{
                        	temp[index] = c;
                        	index++;
                	}
        	        count++;
	        }
	}
	int n;
	while ((n = (read(0, buf, 1))) > 0)
	{
		printf("done go here\n");
		buf[index] = *buf;
		unsigned char c = buf[index];
		if (buf[index] == '\n'|| buf[index] == ' ')
		{
			//printf("newline");
			continue;
		}
		if (count == 0)
		{
			//printf("P is set\n");
			P = c - '0';

		}
                if (count == 1)
                {

                        //printf("p is set\n");
                        p = c - '0';
                }
                if (count == 2)
                {

                        //printf("N is set\n");
                        N = c - '0';
                }
                if (count > 2)//start reading instructions
                {
			temp[index] = c;
                        index++;
                }
                count++;
	}

	/*
	for (int i = 0; i < index; i++)
	{
		printf("%c\n", temp[i]);
	}
	*/	
	
	
	

	int dep = 0;
	for (int i = 0; i < index;)//allocate pid and burst times into respective arrays
	{				//ignore priority value for now
		pid[dep] = temp[i];
		burst[dep] = temp[i+1];
		i = i + 3;
		dep++;
	}

	double arr[100000];
	for (int i = 0; i < dep; i++)
	{
		char c = burst[i];
		arr[i] = c - '0';
	}

	double pidarr[100000];
	for (int i = 0; i < dep; i++)
	{
		char c = pid[i];
		pidarr[i] = c - '0';
	}

	
	//calculate throughput
	double val;//total burst time
	for (int i = 0; i < dep; i++)
	{
		double c = arr[i];
		val += c;
		//printf("burst: %d\n", arr[i]);
		//printf("val: %d\n", val);
	}

	double ps = p;//convert to floats and divide
	double bursts = val;
	double throughput = ps / bursts;
	//printf("p: %d\n", p);
	//printf("throughput: %.2f\n", throughput);


	//calculate waiting time
	double avgWait;
	for (int i = 0; i < dep; i++)
	{
		double initial = 0;
		avgWait = initial + avgWait + arr[i];
	}
	double avgWaits = avgWait;
	avgWaits = avgWaits / ps;
	double turnAround = avgWaits + bursts / ps;//turn around time
	//printf("avg response time: %.2f\n", avgWaits);


	int voluntarySwitch = p;
	//printf("voluntary: %d\n", voluntarySwitch);
	//printf("turnaround time: %.2f\n", turnAround);
	//calculate response time
	double avgBurst = bursts / ps;
	double waiting = turnAround - avgBurst;
	//printf("average wait time: %.2f\n", waiting);

	int nonVoluntarySwitch;

	int counter = 0;
	for (int i = 0; i < dep; i++)
	{
		if (pidarr[i] != pidarr[i+1])
		{
			
			//check rest of array to see if pid shows up again
			for (int j = i+1; j < dep; j++)
			{
				if (i == 0 && pidarr[i] == pidarr[j] && pidarr[i] != pidarr[j+1])
				{
					//printf("%d\n", pidarr[j]);
					//printf("first\n");
					counter++;
				}
				if (pidarr[i] == pidarr[j] && pidarr[i] != pidarr[j-1] && pidarr[i] != pidarr[j+1])
				{
					//printf("%d\n", pidarr[j]);
					//printf("here\n");
					counter++;
				}
				if (i == dep - 1 && pidarr[i] == pidarr[j] && pidarr[i] != pidarr[j-1])
				{
					//printf("%d\n", pidarr[j]);
					//printf("last\n");
					counter++;
				}
			}
		}
	}

	nonVoluntarySwitch = counter;
	//printf("non voluntary : %d\n", nonVoluntarySwitch);

	double cpuUtilization = 100.00; //util always 100 for this instance as P = 1

	printf("%d\n", voluntarySwitch);
	printf("%d\n", nonVoluntarySwitch);
	printf("%.2lf\n", cpuUtilization);
	printf("%.2lf\n", throughput);
	printf("%.2lf\n", turnAround);
	printf("%.2lf\n", waiting);
	printf("%.2lf\n", avgWaits);


	return 0;

}
