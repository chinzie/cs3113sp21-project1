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
	char *buf = (char *) malloc (10000000 *  sizeof(char));//buffer to hold arbitrary amount of numbers
	int count = 0;
	int index = 0;
	int P; //Processes available to run instructions (always 1)
        int p; //Number of threads (amount of processes)
        int N; //Number of instructions (number of instruction lines)
	
	unsigned char e;
	if (argc > 1)
	{
		//printf("argc is > 1\n");
		FILE *file_handle;
		file_handle = fopen(argv[1], "r");
		//if the argument is coming from file input, not stdin
		//use fscanf one byte at a time
        	while (fscanf(file_handle, "%c", buf) == 1)
        	{	
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

	//for if input is stdin
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
	//begin algorithm to set numbers that are larger than single digits
	//so if a number is two digits (25) it will go into one array space instead of two
	//same with three (125), four, ...
	//this goes up to six digit long numbers
	//this algorithm was made by myself (Colin Hinzie)
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
			int tru = 1;//this helps me keep track of what the machine has determined how large the number is
			//so if tru = 4 treat it as a 4 digit long number
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
									f = c - '0';// subtract a '0' from a char to convert it into an integer
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
									//multiply by 10 with respect to how large the number is
                                                                	p = f * 100000 + r * 10000 + a * 1000 + b * 100 + y * 10 + u;
                                                                	temparr[hold] = p;//holds the number into one array place
                                                                	hold++;
                                                                	i++;//increment this many times to make up for read space
                                                                	i++;
                                                                	i++;
                                                                	i++;
									i++;
								}
							}
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

	
	int dep = 0;//will be used a lot as it will be the length of the pid array and the burst array which hold the values of pid and burst time
	count = 0;//reset count value
	for (int i = 0; i < hold;)//allocate pid and burst times into respective arrays
	{
		//set the beginning values: P, p, N
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
			//allocate the values into their respective arrays
			//skips the priority value for now
			//can be used later
			pid[dep] = temparr[i];
                	burst[dep] = temparr[i+1];
                	i = i + 3;
                	dep++;
		}
					//ignore priority value for now
		count++;
	}
	
	//put the values into new arrays
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
	}

	double ps = p;//convert to doubles and divide
	double bursts = val;
	double throughput = ps / bursts;
	


	//calculate waiting time
	double avgWait;
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

	double total[dep];//create array that will hold all burst times
	for (int i = 0; i < dep; i++)
	{
		total[i] = burst[i];
	}
	double totalSum;//create double that will hold total amount of burst times
	for (int i = 0; i < dep; i++)
	{
		totalSum += total[i];
	}
	double responseSum;
	for (int i = 1; i < dep; i++)
	{
		int tru = 1;
		for (int k = i-1; k > -1; k--)//go backwards to see if it is the first instance
		{
			if (pid[i] == pid[k])
			{
				tru = 0;//not the first instance
				break;
			}
		}
		if (tru == 1)//the first instance so count the response time (all bursts before it)
		{
			for (int k = i - 1; k > -1; k--)
			{
				responseSum = responseSum + burst[k];
			}
		}
	}
	responseSum = responseSum / ps;

	totalSum = totalSum + avgWait;//this is the sum of the total wait time plus the total burst time
	

	avgResponse = totalSum / 2 / ps;//average response time
	double turnAround = totalSum / ps;//turn around time
	


	int voluntarySwitch = p;//voluntary switch amount is just p from input
	
	
	//double avgBurst = bursts / ps;//average burst time
	//double waiting = turnAround - avgBurst;//waiting time
	

	int nonVoluntarySwitch;

	int counter = 0;//holds number of involuntary context switches
	for (int i = 0; i < dep; i++)//start to calculate involuntary context switches
	{
		int tru = 1;
		int current = pidarr[i];
		for (int k = i -1; k > -1; k--)//check to see if it has shown up before
		{
			if (pid[k] == current)
			{
				tru = 0;//has shown up so it means it will be an involuntary
				break;
			}
		}
		if (tru == 0)
		{
			if (current != pidarr[i-1])//is the one before it the same? if so dont count it
			{
				counter++;
			}
			else
			{
				continue;
			}
		}
	}

	//print everything
	nonVoluntarySwitch = counter;
	

	double cpuUtilization = 100.00; //util always 100 for this instance as P = 1

	//use .2lf to round to nearest .01 place
	printf("%d\n", voluntarySwitch);
	printf("%d\n", nonVoluntarySwitch);
	printf("%.2lf\n", cpuUtilization);
	printf("%.2lf\n", throughput);
	printf("%.2lf\n", turnAround);
	printf("%.2lf\n", avgWaits);
	printf("%.2lf\n", responseSum);

	return 0;

}
