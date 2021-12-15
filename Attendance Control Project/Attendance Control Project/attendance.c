#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Beneath definitions should be changed according to the lesson's start time.
#define MIN_TIME_SECONDS 39600 //11:00 a.m. - beginning of the lesson.
#define MAX_TIME_SECONDS 39900 //11:05 a.m. - time until attendance of the student is checked.

#pragma warning(disable : 4996)

//Structure for storing the time at which student joins the classes.
struct time
{
	int hour;
	int minute;
	int second;
	char joinTime_total[15];
	int myTime;
};
//To store basic student information.
struct student
{
	int num;
	char name[30];
	struct time time_attended;
	struct student* next; //Self-reference structure to create a linked list.
};
typedef struct student Student; 

Student* createInfo(void); //Function to read a student's information from the *.txt file.
Student* allocateStud(int studID, char name[], int hour, int minute, int second, int myTime); //Function to dynamically allocate students' information to heap memory. 
Student* append(Student* end, Student* newptr); //Function to create a linked list.
//
Student* insertAtFront(Student* start, Student* newptr);
Student* sortedCopy(Student* start);						//These functions are used to create a sorted copy of a linked list.
Student* insertIntoSorted(Student* start, Student* newDig);
//
void printList(Student* start); //Function to print a sorted copy of the linked list.
void freeList(Student* start); //Function to free dynamically allocated data.

int main(void)
{
	Student* start = NULL, * sortedStart = NULL;
	FILE* fp;
	char fname[] = "Sheet1.txt";
	char ch;

	//Opening the file and checking for any errors.
	if ((fp = fopen(fname, "r")) == NULL)
	{
		printf("An error occured while opening the file.\n");
		exit(EXIT_FAILURE);
	}

	start = createInfo(); //Creating a linked list and storing its address to 'start'.
	sortedStart = sortedCopy(start); //Creating a sorted linked list and storing its address to 'sortedStart'.

	printList(sortedStart);
	freeList(start);
	freeList(sortedStart);

	fclose(fp); //Closing the file.

	return 0;
}


Student* createInfo()
{
	Student* start = NULL, * end = NULL, * newptr = NULL;
	FILE* fp;

	char fname[] = "Sheet1.txt";
	if ((fp = fopen(fname, "r")) == NULL)
	{
		printf("An error occured while opening the file.\n");
		exit(EXIT_FAILURE);
	}

	char tmp[100];
	char* ptr;
	int studNum;
	char name[20];
	int hour_joined, minute_joined, second_joined, myTime;

	//Reading information from the file.
	while (!feof(fp) && fgets(tmp, sizeof(tmp), fp) != '\0')
	{
		//Dividing the string into pieces in order to read a student's information.
		//strtok is used, because while converting an excel(.xlsx) file to a text(.txt) file, every space( ) between words is converted into commas(,).
		ptr = tmp;
		ptr = strtok(tmp, ",");
		studNum = atoi(ptr);
		ptr = strtok(NULL, ",");
		strcpy(name, ptr);
		ptr = strtok(NULL, ":");
		hour_joined = atoi(ptr);
		ptr = strtok(NULL, ":");
		minute_joined = atoi(ptr);
		ptr = strtok(NULL, ",");
		second_joined = atoi(ptr);
		//Calculating time, at which student is joined the class, in seconds.
		myTime = (hour_joined * 3600) + (minute_joined * 60) + second_joined;
		//Allocating data.
		newptr = allocateStud(studNum, name, hour_joined, minute_joined, second_joined, myTime);

		if (start == NULL)
		{
			start = end = newptr;
		}
		else
		{
			end = append(end, newptr);
		}
	}

	fclose(fp);
	return(start);
}

Student* allocateStud(int studID, char name[], int hour, int minute, int second, int myTime)
{
	Student* ptr = (Student*)malloc(sizeof(Student));
	ptr->num = studID;
	strcpy(ptr->name, name);
	ptr->time_attended.hour = hour;
	ptr->time_attended.minute = minute;
	ptr->time_attended.second = second;
	ptr->time_attended.myTime = myTime;

	//Checking whether a student is joined the classes on time, late, or didn't join.
	if (MIN_TIME_SECONDS < myTime && myTime < MAX_TIME_SECONDS) //11:00:00 < myTime < 11:04:59
	{
		strcpy(ptr->time_attended.joinTime_total, "출석"); //On time
	}
	else if(MAX_TIME_SECONDS <= myTime && myTime < MAX_TIME_SECONDS + 900) //11:05:00 <= myTime < 11:19:59
	{
		strcpy(ptr->time_attended.joinTime_total, "지각"); //Late
	}
	else  //myTime > 11:19:59
	{
		strcpy(ptr->time_attended.joinTime_total, "결석"); //Didn't join.
	}
	
	ptr->next = NULL;
	return (ptr);
}
Student* append(Student* end, Student* newptr)
{
	//Linking two nodes.
	end->next = newptr;
	return (end->next);
}
Student* sortedCopy(Student* start)
{
	Student* ptr = start;
	Student* sortedStart = NULL;
	Student* newptr;
	//Creating a sorted copy of an existing linked list.
	if (start != NULL) //Checking whether a linked list exists or not.
	{
		sortedStart = allocateStud(start->num, start->name, start->time_attended.hour, start->time_attended.minute, start->time_attended.second, start->time_attended.myTime);
		ptr = ptr->next;
	}
	while (ptr != NULL)
	{
		newptr = allocateStud(ptr->num, ptr->name, ptr->time_attended.hour, ptr->time_attended.minute, ptr->time_attended.second, ptr->time_attended.myTime);
		sortedStart = insertIntoSorted(sortedStart, newptr);
		ptr = ptr->next;
	}
	return (sortedStart);
}
Student* insertAtFront(Student* start, Student* newptr)
{
	//New head of the list. 
	newptr->next = start;
	return (newptr);
}
Student* insertIntoSorted(Student* start, Student* newDig)
{
	Student* ptr = start;
	Student* prev = NULL;

	//Sorting student's information according to time they joined the class, from the earliest to the latest.
	while ((ptr != NULL) && ptr->time_attended.myTime < newDig->time_attended.myTime)
	{
		prev = ptr;
		ptr = ptr->next;
	}
	if (prev == NULL)
	{
		start = insertAtFront(start, newDig); //New head is found.
	}
	else
	{
		prev->next = newDig; //Just linking two nodes.
		newDig->next = ptr;
	}
	return (start);
}

void printList(Student* start)
{
	Student* ptr = start;
	//Printing students' information till the end of the list.
	while (ptr != NULL)
	{
		printf("%s %d:%d:%d %s\n", ptr->name,  ptr->time_attended.hour, ptr->time_attended.minute, ptr->time_attended.second, ptr->time_attended.joinTime_total);
		ptr = ptr->next;
	}
}
void freeList(Student* start)
{
	Student* ptr = start;
	/*We cannot simply write free(start) to free entire memory space, because we have different
	  pieces of memory that are linked together and "start" is the starting point of the memory
	  from which we should start freeing the heap.
	  If we simply write free(start), we will delete the starting point of the used memory,
	  losing control over all subsequent memory spaces.
	  So we should first store the starting point of the memory to a new pointer to structure "ptr"
	  and then free the current start of the used memory. */
	while (ptr != NULL)
	{
		start = ptr;
		ptr = ptr->next;
		free(start);
	}
}