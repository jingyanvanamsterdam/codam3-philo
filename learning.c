#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t	mutex;

void	*func(void *arg)
{
	int	res;
	printf("testing from threads\n");
	res = malloc(sizeof(int));
	pthread_mutex_lock(&mutex);
	// doing something after waiting for the lock to turn to 0 and then turn it back to 1 so can run the code here.
	pthread_mutex_unlock(&mutex);

	int	i = *(int*)arg;
	printf("%d is i\n", i);
	free(arg);
	return ((void *)&res);
}

int	main(void)
{
	pthread_t	t1, t2;

	pthread_mutex_init(&mutex, NULL);
	if (pthread_create(&t1, NULL, func, NULL) != 0)
		return 1;
	if (pthread_create(&t2, NULL, func, NULL) != 0)
		return 1;
	pthread_join(t1, NULL); // like a wait func for waiting t1;
	pthread_join(t2, NULL); // like a wait func for waiting t1;
	pthread_mutex_destroy(&mutex);

	// create in array of threads: like philos
	pthread_t th[4];
	int	*res; 
	for (int i = 0; i < 4; i++)
	{
		if (pthread_create(th + i, NULL, func, NULL) != 0)
			return 1;
	}
	for (int i = 0; i < 4; i++)
	{
		// the second arg is a pointer to some value we waan to get from the return value of the threads. 
		if (pthread_join(t1, (void **)&res) != 0)
			return 2;
	}
	free(res);
///---- passing value into funcs
	pthread_t	threads[10];
	int i;
	for (i = 0; i < 10; i++)
	{
		int *a = malloc(sizeof(int));
		*a = i;
		// because after the threads is created, the i ++; 
		// if i is passed directly, it will be the number after increment. 
		// we need to free the pointer in the thread function. otherwise same problem
		// but if we need to use the *a as the return value of the threads, we can do it outside and free after join. 
		if (pthread_create(threads + i, NULL, func, a) != 0)
			perror("failed at creating thread.");
	}
	pthread_mutex_destroy(&mutex);
	return (0);
}