#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdint.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
	//printf("starting\n");
	char *buf = (char *) malloc (1000000 *  sizeof(char));
	int count = 0;
	int index = 0;
	int P; //Processes available to run instructions (always 1)
        int p; //Number of threads (amount of processes)
        int N; //Number of instructions (number of instruction lines)
	int temp[100000];
	char pretemp[100000];
	int pid[100000];
	int burst[100000];
	//unsigned char c = '0';
	//printf("done starting\n");
	if (argc > 1)
	{
		//printf("argc is > 1\n");
		FILE *file_handle;
		file_handle = fopen(argv[1], "r");
		
        	while (fscanf(file_handle, "%c", buf) == 1)
        	{	
                	buf[index] = *buf;
                	unsigned char c = buf[index];
			//printf("%c\n", c);

			pretemp[count] = c;

			/*
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
				//printf("adding to temp: ");
				//printf("%c\n", c);
                        	temp[index] = c;
                        	index++;
                	}
			*/
        	        count++;
	        }
		fclose(file_handle);
	}
	
	int n;
	if ( argc == 1)
	while ((n = (read(0, buf, 1))) > 0)
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
	int temparr[100000];
	int hold = 0;
	for (int i = 0; i < count; i++)
	{
		int f;
		int r;
		int p;
		char d;
		char c = pretemp[i];
		int q = isdigit(c);
		if (q > 0)
		{
			int tru = 1;
			if (pretemp[i+1] != '\n' && pretemp[i+1] != ' ')
			{
				//printf("double digit\n");
				f = c - '0';
				d = pretemp[i+1];
				r = d - '0';
				p = f * 10 + r;
				temparr[hold] = p;
				hold++;
				i++;
				tru = 0;
			}
			if (tru == 1)
			{
				f = c - '0';
                        	temparr[hold] = f;
                        	//printf("digit: %d\n", temparr[hold]);
                        	hold++;
			}
			//f = c - '0';
			//temparr[hold] = f;
			//printf("digit: %d\n", temparr[hold]);
			//hold++;
		}
	}


	/*
	printf("now here\n");
	int jub = 0;
	int holder = 0;
	for (int i = 0; i < count; i++)
	{
		int q;
		holder = temparr[i];
		q = isdigit(holder);
		if (q > 0)
		{
			printf("digit\n");
			temp[jub] = holder;
			jub++;
		
		}
		else
		{
			printf("no\n");
			continue;
		}
		
		if ((temparr[i] != '\n' && temparr[i] != ' ') && (temparr[i+1] == '\n' || temparr[i+1] == ' '))
		{		
			temp[jub] = holder;
			jub++;
		}
		if ((temparr[i] != '\n' && temparr[i] != ' ') && (temparr[i+1] != '\n' &&  temparr[i+1] != ' '))
		{
			printf("copy\n");
			int k = temparr[i+1];
			holder = (holder * 10) + k;
			printf("jub: %d\n", holder);
			temp[jub] = holder;
			jub++;
			i++;
		}
		

	}
	*/
	
	for (int i = 0; i < hold; i++)
	{
		//printf("%d\n", temparr[i]);
	}
	

		
		
		
	
	
	//printf("starting calc\n");

	
	int dep = 0;
	count = 0;
	int size = index;
	//printf("%d\n", size);
	for (int i = 0; i < hold;)//allocate pid and burst times into respective arrays
	{
		int c = temparr[i];
		if (count == 0)
                {
                        //printf("P is set\n");
			
                        P = c;
			i++;

                }
                if (count == 1)
                {

                        //printf("p is set\n");
                        p = c;
			i++;
                }
                if (count == 2)
                {

                        //printf("N is set\n");
                        N = c;
			i++;
                }
		if (count > 2)
		{
			//printf(" i is: %d\n", i);
			//printf(" temp is: %d\n", temparr[i]);
			pid[dep] = temparr[i];
                	burst[dep] = temparr[i+1];
                	i = i + 3;
                	dep++;
		}
					//ignore priority value for now
		count++;
	}
	for (int i =0; i < dep; i++)
	{
		//printf("pid: %d\n", pid[i]);
	}

	/*
	for (int i = 0; i < dep; i++)
	{
		if (pid[i] == pid[i+1])
		{
			int current = i;
			while(pid[i] == pid[i+1])
			{
				burst[current] += burst[i+1];
				i++;
			}
		}
	}
	*/		

	
	double arr[100000];
	for (int i = 0; i < dep; i++)
	{
		double c = burst[i];
		arr[i] = c;
	}

	double pidarr[100000];
	for (int i = 0; i < dep; i++)
	{
		//for (int k = 0; k < dep; k++)
                //{
                //        if (pid[k] == burst[k+1])
                //        {
                //                i++;
                //        }
                //}
		double c = pid[i];
		pidarr[i] = c;
	}
	

	
	//calculate throughput
	double val;//total burst time
	for (int i = 0; i < dep; i++)
	{
		double c = arr[i];
		val += c;
		//printf("burst: %f\n", arr[i]);
		//printf("val: %f\n", val);
	}

	double ps = p;//convert to floats and divide
	double bursts = val;
	double throughput = ps / bursts;
	//printf("p: %d\n", p);
	//printf("throughput: %.2f\n", throughput);


	//calculate waiting time
	double avgWait;//[dep];
	double avgResponse;
	for (int i = 1; i < dep; i++)
	{
		//from current spot, look up and see if same pid occurs, if it does then stop and add up
		int current = i;
		for (int k = i-1; k > -1; k--)
		{
			if (pid[current] == pid[k])
			{
				//printf("breaking\n");
				break;
			}
			//printf("adding\n");
			avgWait = avgWait + burst[k];
		
		}
	}



	
	/*
	double sum = 0;
	for (int i = 0; i < dep; i++)
	{
		sum += avgWait[i];
	}
	printf("sum: %f\n", sum);
	*/

	double avgWaits = avgWait;
	avgWaits = avgWaits / ps;

	double total[dep];
	for (int i = 0; i < dep; i++)
	{
		total[i] = burst[i];
	}
	double totalSum;
	for (int i = 0; i < dep; i++)
	{
		totalSum += total[i];
	}
	double responseSum;
	for (int i = 1; i < dep; i++)
	{
		int tru = 1;
		for (int k = i-1; k > -1; k--)
		{
			if (pid[i] == pid[k])
			{
				printf("shows up before\n");
				tru = 0;
				break;
			}
		}
		if (tru == 1)
		{
			for (int k = i - 1; k > -1; k--)
			{
				printf("adding %d\n", burst[k]);
				responseSum = responseSum + burst[k];
			}
		}
	}
	responseSum = responseSum / 4;

	totalSum = totalSum + avgWait;
	//printf("totalsum: %f\n", totalSum);

	avgResponse = totalSum / 2 / ps;
	double turnAround = totalSum / ps;//turn around time
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
	printf("%.2lf\n", avgWaits);
	printf("%.2lf\n", responseSum);


	return 0;

}
