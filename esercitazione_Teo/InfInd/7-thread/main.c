#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


//this function is the code of Pthread
void * my_pthread_fn(void* args)
{
    printf("\t\t\t\t\t\t\t\t hello Word! I am the slave Thread ID: %d\n", (void *) args);
    return (void *) args;
}

// TO DO:
// - creare 16 thread - check
// - indicizzare gli ID dei thread in ordine partendo dal 0 (mainthread)s -check
// - nel corpo del thread stampiamo il self con relativo ID - check 

int main()
{

    /*
    
        int pthread_create (pthread_t *ID,
                            pthread_attr_t *attr,
                            void *(*body)(void *),
                            void * arg
 		     );
    */

    int NTHREADS = 16;
    pthread_t mythread[NTHREADS];
    pthread_attr_t attr;

    int res = pthread_attr_init(&attr);

    printf("Hello World! I am the MASTER thread, before creating slaves\n");
    for(int i=0; i<NTHREADS; i++)
    {
        res = pthread_create (&mythread[i],                            // ==> FORK
                                &attr,
                                my_pthread_fn,
                                (void *) (i+1));

            if(res != 0)
            {
                printf("Error: OS returned %d\n", res);
                exit(res);
            }
    }
    

    res = pthread_attr_destroy(&attr);
    printf("Hello World! I am the MASTER thread, after creating slaves\n");

    // Here, I can do other stuff

    printf("\t\tHello World! I am the MASTER thread, and I am doing some stuff...\n");

    /*
        int pthread_join ( pthread_t th,
                        void **thread_return);
    */
    void * returnvalue;
    printf("Hello World! I am the MASTER thread, before joining slaves\n");
    for (int i=0; i<NTHREADS; i++)
    {
        res = pthread_join (mythread[i], &returnvalue);    // <== JOIN
    }
    printf("Hello World! I am the MASTER thread, after joining slaves\n");
    
    return 0;
}