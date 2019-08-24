#include<stdio.h>
#include<conio.h>
#include<stdbool.h>
#include<unistd.h>
void sort();
 struct Process 
 { 
   int pid; 
   int at; 
   int bt;  
   int ct;
   int tat;
   int wt; 
 };
 
 int n;

 Process processes[50];
 void initialise()
 {
  
  printf("\nenter the no of processes:");
  scanf("%d",&n);
  int i;
   for(i=0;i<n;i++)
   {
  	Process p;
  	p.pid=i+1;
  	printf("\nArrival time for process %d :",p.pid);
  	scanf("%d",&p.at);
  	if(p.at==0)
  	{
  	printf("\nArrival time for process %d cannot be 0,Enter again :",p.pid);
  	scanf("%d",&p.at);
	}
  	printf("\nBurst time for process %d:",p.pid);
  	scanf("%d",&p.bt);
  	processes[i]=p;
   } 
  
   
 }
 void sort()
 {
 	Process temp;
 	for(int j=0;j<n-1;j++)
 	{
	 
 	 for(int i=0;i<n-j-1;i++)
 	 {
 		
 		if(processes[i].bt>processes[i+1].bt)
 		{
 			temp=processes[i];
 			processes[i]=processes[i+1];
 			processes[i+1]=temp;
		}

	 }
	 
    }
    
    
    //processes array sorted according to burst time!
 }
 
 void display()
 {
 	printf("\nProcess id\t\tArrival time\t\tBurst time");
 	for(int i=0;i<n;i++)
 	{
 		printf("\n%d\t\t\t%d\t\t\t%d",processes[i].pid,processes[i].at,processes[i].bt);
	}
 }
 
 int min=1000;
 int pos;
 void minArrival()
 {
 	for(int i=0;i<n;i++)
 	{
 		if(processes[i].at<min)
 		{
 			min=processes[i].at;
 			pos=i;
		}
	}
 }
 
Process queue[10];
int current=-1;
int k=0;
int time;
 void SJF()
 {
 	
 	time=min;
 	queue[0]=processes[pos];
   bool flag=true;
   
    int i;
 	
     for(i=0;i<n;i++)  //picking up processes
     { 
     	int j;
     	
     	for( j=0;j<n;j++)      //checks for each process if it is arrived in the time
     	{ 
		 flag=true;
     	 if(time>=processes[j].at)
     	 {
     		int s;
     		//check if it is already in queue or not 
     		for( s=0;s<(sizeof(queue)/sizeof(queue[0]));s++)
     		{
			 
     		 if(queue[s].pid==processes[j].pid)
     		 {
     			flag=false; //process is already in queue
     			break;
			 }

		    }
		    //add the process
		    if(flag==true)
		    {
		     k++;
     		queue[k]=processes[j];
     	    }
		 }
	    }
	    //inner loop finished
	    current=current+1;
	    //calculating completion time,arrival time and burst time 
	    queue[current].ct=time+queue[current].bt;
	    queue[current].tat=queue[current].ct-queue[current].at;
	    queue[current].wt=queue[current].tat-queue[current].bt;
	    
		time=time+queue[current].bt+2;
	//	printf("time : %d",time);		
	 }
	 //outer loop finished
 }
  	int totalWT;
 	int totalTAT;
 	float avgWT;
 	float avgTAT;
 	
 void CalculateValues()
 {
     //printf("\n inside calcualtevalues()");
    Process temp;
 	for(int j=0;j<n-1;j++)
 	{
	 
 	 for(int i=0;i<n-j-1;i++)
 	 {
 		
 		if(queue[i].pid>queue[i+1].pid)
 		{
 			temp=queue[i];
 			queue[i]=queue[i+1];
 			queue[i+1]=temp;
		}

	 }
	 
    }
    for(int i=0;i<k+1;i++)
    {
    	totalWT=totalWT+queue[i].wt;
    	totalTAT=totalTAT+queue[i].tat;
	}
	//printf("\nvalue of n:%d",n);
	//printf("\ntotal waiting time:%d",totalWT);
    avgWT=float(totalWT)/n;
    //printf("\naverage waiting time:%d",avgWT);
    avgTAT=(totalTAT)/float(n);
    //printf("\naverage turnaround time:%d",avgTAT);
 }
 
 void finalDisplay()
 {
 	printf("\n\nProcess id\t\tArrival time\t\tBurst time\t\tcompletion time\t\tTurnaround time\twaiting time");
 	for(int i=0;i<k+1;i++)
 	{
 		printf("\n%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d",queue[i].pid,queue[i].at,queue[i].bt,queue[i].ct,queue[i].tat,queue[i].wt);
	}
	printf("\n\nAverage waiting time:%f\n\nAverage turnaround time:%f\n\nTotal time taken by processor to process all the jobs:%d",avgWT,avgTAT,time);
 }
 
 void calculatePerformance()
 {
 	float throughput;
 	throughput=float(n)/(time);
 	printf("\n\nCalculating performance of the scheduler!");
 	sleep(1);
 	printf("\n\nthroughput:%f",throughput);
 	sleep(1);
 	printf("\n\ntotal waiting time:%d",totalWT);
 	sleep(1);
 	printf("\n\ntotal turnaround time:%d",totalTAT);
 	//sleep(1);
 	printf("\n\n\nfor best performance throughput should be more and average waiting time,turnaround time should be less!");
 }
main()
{
  initialise();
  display();
   sort();
   minArrival();
   SJF();
  printf("\n\norder of execution:");
  int i;
  for(i=0;i<k+1;i++)
  {
  printf("%d\t",queue[i].pid);
  }
  
  CalculateValues();
  finalDisplay();
   char ch;
  printf("\n\ndo you want to calculate performace of the scheduler:? ");
  scanf("%s",&ch);
  if(ch=='y')
  {
  	calculatePerformance();
  }
  else
  {
  	printf("\n\nThank you for using our software!");
  }
}
