#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

/*
	Alex Hromada
	anhromad
	M45218886
	Program 7: CPU
	CS1142
	Spring 2020
	
	This program uses a circular doubly linked list to simulate CPU task scheduling
*/

// Stores information about a particular job on the system
// Do NOT modify!
typedef struct
{
    int id;                 // Unique numeric ID for this job
    int startTime;          // Time the job entered the system
    int totalCycles;        // Total CPU cycles required by this job
    int remainingCycles;    // How many cycles remaining before it is done
} Job;

// Node in the doubly linked list
// Do NOT modify!
typedef struct node
{
    Job job;                // Data about this particular job
    struct node* next;      // Pointer to the next node in the doubly linked list
    struct node* prev;      // Pointer to the prev node in the doubly linked list
} Node;

// Tracks information about the state of the CPU scheduler
// Do NOT modify!
typedef struct
{
    Node* head;             // Current head of the linked list
    int time;               // Current time of the simulation
} State;

// Executes one cycle of the CPU scheduling simulation.
// The current job at the head of the linked list gets one cycle of CPU time.
//
// If the current job is done, it should be removed from the list and the function prints:
//   t=A, B done, elapsed C, idle D%\n
//   where A is the current time of the simulation
//         B is the job ID of the completed job
//         C is how many cycles have elapsed since the job was first added (including this cycle)
//         D is the percentage of cycles in which this job was idle (some other job was executing)
// 
// The head of the list should be advanced to the next node.
// The current time of the simulation should be advanced by one.
//
// Returns true if a job used the cycle, false if there were no available jobs.
bool executeCycle(State* state)
{
	// If there are no jobs currently
    if(state->head == NULL)
	{
		state->time = state->time + 1;
		return false;
	} 
	else
	{
		state->head->job.remainingCycles = state->head->job.remainingCycles - 1;  // Decrement remaining cycles counter
		
		if(state->head->job.remainingCycles == 0)
		{
			Node* curr = state->head;
			Node* precede = NULL;;
			//Node* succeed = state->head->next;
			
			int elapsed = state->time - curr->job.startTime + 1;
			double idle = 100.0 * ((double) ((elapsed) - state->head->job.totalCycles) / 
			(elapsed));
			
			printf("t=%d, %d done, elapsed %d, idle %.2f%%\n", state->time, state->head->job.id, elapsed, idle);
			
			// If the finished node is the only node in the list
			if(curr->next == state->head && precede == NULL)
			{
				state->head = NULL;
				free(curr);
			}
			else // If the list has more than one node
			{
				precede = state->head->prev;
			
				state->head = state->head->next;
				
				precede->next = state->head;
				state->head->prev = precede;
				free(curr);
			}


		}	
		else // Nothing to remove, move head down the list
		{
			state->head = state->head->next;
		}
		state->time = state->time + 1;  // Incremement current time
		return true;
	}
	
}

// Adds a new job to the linked list.
// The job is added as the node before the current head of the list.
// Thus the new job has to wait until all existing jobs get scheduled.
//
// Returns true on succss, false otherwise (e.g. failure to allocate memory).
bool addJob(State* state, int jobID, int jobTime)
{
	if(state->head == NULL)   // Empty list
	{
		Node* newNode = malloc(sizeof(Node));
		
		// If malloc errors
		if(newNode == NULL)
			return false;
		
		Job newJob;
	
		// Initialize all job variables with respective data
		newJob.id = jobID;
		newJob.totalCycles = jobTime;
		newJob.remainingCycles = jobTime;
		newJob.startTime = state->time;
		
		newNode->job = newJob;
		
		// Set next and prev pointers to itself
		newNode->next = newNode;
		newNode->prev = newNode;
		
		state->head = newNode;
		
		printf("t=%d, added %d\n", state->time, newNode->job.id);
		
		return true;
	}
	else  // List has data
	{
		Node* newNode = malloc(sizeof(Node));
		
		// If malloc errors
		if(newNode == NULL)
			return false;
		
		Job newJob;
		
		// Initialize all job variables with respective data
		newJob.id = jobID;
		newJob.totalCycles = jobTime;
		newJob.remainingCycles = jobTime;
		newJob.startTime = state->time;
		
		newNode->job = newJob;
		
		Node* previous = state->head->prev;
		
		newNode->prev = previous;
		newNode->next = state->head;
		state->head->prev = newNode;
		
		// Checks if the list only has 1 node, so it knows which node to add newNode after
		if(state->head->next == state->head)
		{
			state->head->next = newNode;
		}
		else
		{
			previous->next = newNode;
		}
		
		printf("t=%d, added %d\n", state->time, newNode->job.id);
		
		return true;
	}

}

// Prints out the jobs currently in the linked list in order of next execution. 
// Output format is:
//   t=A, print B:C D:E ...
//   where A is the current time of the simulation
//         B is the ID of the job at the head of the list
//         C is the remaining cycles for the job at the head of the list
//         D is the ID of the next job to be scheduled
//         E is the remaining cycles of the next job to be schedule
//         ... and so on for all jobs in the list
void printJobs(const State* state)
{
	Node* curr = state->head;
    printf("t=%d, print", state->time);
	if(state->head != NULL)
	{
		printf(" %d:%d", curr->job.id, curr->job.remainingCycles);
		curr = curr->next;
		while(curr != state->head)
		{
			printf(" %d:%d", curr->job.id, curr->job.remainingCycles);
			curr = curr->next;
		}
	}
	printf("\n");
}

// Remove all remaining jobs from the linked list, deallocating the associated memory.
// Also results in the head of the list being changed to NULL.
//
// Returns the number of removed jobs (0 if list is empty).
int freeJobs(State* state)
{
	// Returns if the list is empty
	if(state->head == NULL)
		return 0;
	Node* prec = state->head->prev;
	prec->next = NULL;   // Sets the end of the list to a null pointer so loop has a stopping point
	int remCount = 0;

	Node* curr = state->head;
    while(curr != NULL)
	{
		Node* after = curr->next;

		free(curr);
		curr = after;
		remCount++;

	}
	state->head = NULL;
    return remCount;
}

// Main program that simulates scheduling jobs on a CPU.
// Input is via standard input.
// Input consists of a string command followed by 0 or more integer arguments depending on the command.
// Do NOT modify the main function!
int main(void)
{
    // State struct keeps track of the head of the linked list and the current time of the simulation
    State state;
    state.head = NULL;
    state.time = 0;

    // String literals that are used in the input 
    const char* COMMAND_RUN = "run";
    const char* COMMAND_ADD = "add";
    const char* COMMAND_PRINT = "print";
    
    // Variables used to read in data depending ont he command
    char command[100];
    int cycles = 0;
    int id = 0;
    int jobTime = 0;
    
    // Used to keep track of how often the CPU was busy or idle
    int busyCycles = 0;
    int idleCycles = 0;
    
    while (scanf("%99s", command) == 1)
    {        
        if (strcmp(command, COMMAND_RUN) == 0)
        {
            // After the run command should come a positive number of cycles to execute
            if ((scanf("%d", &cycles) == 1) && (cycles > 0))
            {
                for (int i = 0; i < cycles; i++)
                {
                    if (executeCycle(&state))
                    {
                        busyCycles++;
                    }
                    else
                    {
                        idleCycles++;
                    }
                }
            }
            else
            {
                printf("Invalid run command\n");
                return 1;
            }
        }
        else if (strcmp(command, COMMAND_ADD) == 0)
        {
            // After the add command should come the process ID and a positive job time
            if ((scanf("%d %d", &id, &jobTime) == 2) && (jobTime > 0))
            {
                if (!addJob(&state, id, jobTime))
                {
                    printf("Failed to add job\n");
                    return 1;
                }
            }
            else
            {
                printf("Invalid add command\n");
                return 1;
            }
        }
        else if (strcmp(command, COMMAND_PRINT) == 0)
        {
            printJobs(&state);
        }
        else
        {
            printf("Unknown command = %s\n", command);
            return 1;
        }
    }
    
    // Compute how many cycles the CPU was busy
    double utilization = (double) busyCycles / (idleCycles + busyCycles) * 100.0;    
    printf("t=%d, end, CPU busy %.2f%%\n", state.time, utilization);

    // Deallocate any remaining jobs in the system
    printf("t=%d, freed %d remaining jobs\n", state.time, freeJobs(&state));
    
    return 0;
}

