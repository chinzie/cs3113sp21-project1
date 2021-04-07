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
	char *buf = (char *) malloc (10000000 *  sizeof(char));
	int count = 0;
	int index = 0;
	int P; //Processes available to run instructions (always 1)
        int p; //Number of threads (amount of processes)
        int N; //Number of instructions (number of instruction lines)
	
	//unsigned char c = '0';
	//printf("done starting\n");
	unsigned char e;
	if (argc > 1)
	{
		//printf("argc is > 1\n");
		FILE *file_handle;
		file_handle = fopen(argv[1], "r");
		
        	while (fscanf(file_handle, "%c", buf) == 1)
        	{	
                	//buf[index] = *buf;
                	//unsigned char c = buf[index];
			//pretemp[count] = c;
			buf[count] = *buf;
			if (count == 0)
			{
				e = buf[count];
			}
        	        count++;
	        }
		fclose(file_handle);
	}
	buf[0] = e;//file read seems to ignore the first element after loop so i allocate it here
	char pretemp[count];
	int temp[count];
	int pid[count];
	int burst[count];
	for (int i = 0; i < count; i++)
	{
		unsigned char c = buf[i];
		pretemp[i] = c;
	}

	
	int n;
	if ( argc == 1)
	while ((n = (read(0, buf, 1))) > 0)
	{
		//count = 0;
		
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
	int temparr[count];
	int hold = 0;
	for (int i = 0; i < count; i++)
	{
		int f;
		int r;
		int p;
		int a;
		int b;
		char d;
		char g;
		char h;
		char c = pretemp[i];
		int q = isdigit(c);
		if (q > 0)
		{
			int tru = 1;
			
			if (pretemp[i+1] != '\n' && pretemp[i+1] != ' ')
			{
				tru = 2;
				if (pretemp[i+1] != '\n' && pretemp[i+1] != ' ' && pretemp[i+2] != '\n' && pretemp[i+2] != ' ')
				{
					tru = 3;
					if (pretemp[i+3] != '\n' && pretemp[i+3] != ' ')
					{
						tru = 4;
						if (pretemp[i+4] != '\n' && pretemp[i+4] != ' ')
						{
							tru = 5;
							
							if (pretemp[i+5] != '\n' && pretemp[i+5] != ' ')
							{
								tru = 6;
								
								if (tru == 6)
								{
									//printf("six\n");
									f = c - '0';
                                                                	d = pretemp[i+1];
                                                                	r = d- '0';
                                                                	g = pretemp[i+2];
                                                                	a = g - '0';
                                                                	h = pretemp[i+3];
                                                                	b = h - '0';
                                                                	char x = pretemp[i+4];
                                                                	int y = x - '0';
									char z = pretemp[i+5];
									int u = z - '0';
                                                                	p = f * 100000 + r * 10000 + a * 1000 + b * 100 + y * 10 + u;
                                                                	temparr[hold] = p;
                                                                	hold++;
                                                                	i++;
                                                                	i++;
                                                                	i++;
                                                                	i++;
									i++;
									
									
								}
							}
							//printf("tru is: %d\n", tru);
							if (tru == 5)
							{
								//printf("five\n");
								f = c - '0';
                                                        	d = pretemp[i+1];
                                                        	r = d- '0';
                                                        	g = pretemp[i+2];
                                                        	a = g - '0';
                                                        	h = pretemp[i+3];
                                                        	b = h - '0';
								char x = pretemp[i+4];
								int y = x - '0';
                                                        	p = f * 10000 + r * 1000 + a * 100 + b * 10 + y;
                                                        	temparr[hold] = p;
                                                        	hold++;
                                                        	i++;
								i++;
                                                        	i++;
                                                        	i++;
								
							}
						}
						if (tru == 4)
						{
							//printf("quad\n");
							f = c - '0';
                                                	d = pretemp[i+1];
                                                	r = d- '0';
                                                	g = pretemp[i+2];
                                                	a = g - '0';
							h = pretemp[i+3];
							b = h - '0';
                                                	p = f * 1000 + r * 100 + a * 10 + b;
                                                	temparr[hold] = p;
                                                	hold++;
                                                	i++;
                                                	i++;
							i++;
						}
					}
					if (tru == 3)
					{
						//printf("triple\n");
						f = c - '0';
						d = pretemp[i+1];
						r = d- '0';
						g = pretemp[i+2];
						a = g - '0';
						p = f * 100 + r * 10 + a;
						temparr[hold] = p;
						hold++;
						i++;
						i++;
					}

				}
				if (tru == 2)
				{
					//printf("double\n");
					f = c - '0';
					d = pretemp[i+1];
					r = d - '0';
					p = f * 10 + r;
					temparr[hold] = p;
					hold++;
					i++;
				}
			}
			if (tru == 1)
			{
				//printf("single\n");
				f = c - '0';
                        	temparr[hold] = f;
                        	
                        	hold++;
			}
		}
	}

	
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
	
	
	double arr[count];
	for (int i = 0; i < dep; i++)
	{
		double c = burst[i];
		arr[i] = c;
	}

	double pidarr[count];
	for (int i = 0; i < dep; i++)
	{
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
				//printf("shows up before\n");
				tru = 0;
				break;
			}
		}
		if (tru == 1)
		{
			for (int k = i - 1; k > -1; k--)
			{
				//printf("adding %d\n", burst[k]);
				responseSum = responseSum + burst[k];
			}
		}
	}
	responseSum = responseSum / ps;

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
		int tru = 1;
		int current = pidarr[i];
		for (int k = i -1; k > -1; k--)//check to see if it has shown up before
		{
			if (pid[k] == current)
			{
				tru = 0;
				break;
			}
		}
		if (tru == 0)
		{
			if (current != pidarr[i-1])
			{
				counter++;
			}
			else
			{
				continue;
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
