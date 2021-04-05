#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdint.h>

int main(int argc, char **argv)
{
	unsigned char *buf = (char *) malloc (1000000 *  sizeof(char));
	int count = 0;
	int index = 0;
	int P; //Processes available to run instructions (always 1)
        int p; //Number of threads (amount of processes)
        int N; //Number of instructions (number of instruction lines)
	char temp[100000];
	char pid[100000];
	char burst[100000];

	//char var = 10;
	//char *ptr = &var;

	//char nl = '\n';
	//char *nle = &nl;
	//char spc = ' ';
	//char *spce = &spc;
	
	
	while (read(0, buf, 1) > 0)
	{
		buf[index] = *buf;
		unsigned char c = buf[index];
		if (buf[index] == '\n'|| buf[index] == ' ')
		{
			printf("newline");
			continue;
		}
		if (count == 0)
		{
			printf("P is set\n");
			P = c - '0';

		}
                if (count == 1)
                {

                        printf("p is set\n");
                        p = c - '0';
                }
                if (count == 2)
                {

                        printf("N is set\n");
                        N = c - '0';
                }
                if (count > 2)//start reading instructions
                {
			temp[index] = c;
                        index++;
                }
                count++;
	}

	for (int i = 0; i < index; i++)
	{
		printf("%c\n", temp[i]);
	}	
	
	
	

	int dep = 0;
	for (int i = 0; i < index;)//allocate pid and burst times into respective arrays
	{				//ignore priority value for now
		pid[dep] = temp[i];
		burst[dep] = temp[i+1];
		i = i + 3;
		dep++;
	}

	int arr[100000];
	for (int i = 0; i < dep; i++)
	{
		char c = burst[i];
		arr[i] = c - '0';
	}

	/*

	int voluntaryContextSwitch = 0;
	//int nonvoluntaryConextSwitch = 0;
	float cpuUtilization = 0;
	float throughPut = 0;
	//float turnaroundTime = 0;
	//float waitingTime = 0;
	//float responseTime = 0;


	//calculate context switches
	int voluntarypidChange = 0;
	//int nonvoluntary = 0;
	for (int i = 0; i < dep; i++)
	{
		if (pid[i] != pid[i+1])
		{
			voluntarypidChange++;
		}
		else
		{
			for (int j = 0; j < dep; j++)
			{
				if (pid[i] == pid[j])
				{
					
				}
			}
		}

	}


	*/
	//calculate throughput
	int val;//total burst time
	for (int i = 0; i < dep; i++)
	{
		int c = arr[i];
		val += c;
		printf("burst: %d\n", arr[i]);
		printf("val: %d\n", val);
	}

	float ps = p;//convert to floats and divide
	float bursts = val;
	float throughput = ps / bursts;
	printf("p: %d\n", p);
	printf("throughput: %.2f\n", throughput);


	//calculate waiting time
	int avgWait;
	for (int i = 0; i < dep; i++)
	{
		int initial = 0;
		avgWait = initial + avgWait + arr[i];
	}
	float avgWaits = avgWait;
	avgWaits = avgWaits / ps;
	float turnAround = avgWaits + bursts / ps;//turn around time
	printf("avg response time: %.2f\n", avgWaits);


	printf("turnaround time: %.2f\n", turnAround);
	//calculate response time
	float avgBurst = bursts / ps;
	float waiting = turnAround - avgBurst;
	printf("average wait time: %.2f\n", waiting);


	
	//voluntaryContextSwitch = voluntarypidChange;
	float cpuUtilization = 100.00; //utilization is 100 because P is 1
	//throughPut = p / val;
	//printf("%d\n", voluntaryContextSwitch);
	//printf("%f\n", cpuUtilization);
	//printf("throughput: %f\n", throughPut);

	/*










	*/

	//printf("P: %c\n", *P);
	//printf("p: %c\n", *p);
	//printf("N: %c\n", *N);
	/*
	for (int i = 0; i < dep; i++)
	{
		printf("%c ", pid[i]);
		printf("%c\n", burst[i]);
	}
	*/

}
