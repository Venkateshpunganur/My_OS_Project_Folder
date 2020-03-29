//Initial Code - Creating an Interface for the Project
#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <pthread.h>

#include <semaphore.h>



void* student_actions( void* student_id );

void* ta_actions();



#define NUM_WAITING_CHAIRS 3

#define DEFAULT_NUM_STUDENTS 5



sem_t sem_students;

sem_t sem_ta;

pthread_mutex_t mutex_thread;



int waiting_room_chairs[3];

int number_students_waiting = 0;

int next_seating_position = 0;

int next_teaching_position = 0;

int ta_sleeping_flag = 0;
int isNumber(char number[])

{

    int i;

		for ( i = 0 ; number[i] != 0; i++ )

    {

        if (!isdigit(number[i]))

            return 0;

    }

    return 1;

}



int isWaiting( int student_id ) {

	int i;

	for ( i = 0; i < 3; i++ ) {

		if ( wt_rm_chrs[i] == student_id ) { return 1; }

	}

	return 0;

}


int main( int argc, char **argv ){



	int i;

	int student_num;



	if (argc > 1 ) {

		if ( isNumber( argv[1] ) == 1) {

			student_num = atoi( argv[1] );

		}

		else {

			printf("Invalid input. Quitting program.");

			return 0;

		}

	}

	else {

		student_num = DEFAULT_NUM_STUDENTS;

	}



	int student_ids[student_num];

	pthread_t students[student_num];

	pthread_t ta;



	sem_init( &sem_students, 0, 0 );

	sem_init( &sem_ta, 0, 1 );



	//Create threads.

	pthread_mutex_init( &mutex_thread, NULL );

	pthread_create( &ta, NULL, ta_actions, NULL );

	for( i = 0; i < student_num; i++ )

	{

		student_ids[i] = i + 1;

		pthread_create( &students[i], NULL, student_actions, (void*) &student_ids[i] );

	}



	//Join threads

	pthread_join(ta, NULL);

	for( i =0; i < student_num; i++ )

	{

		pthread_join( students[i],NULL );

	}



	return 0;

}



