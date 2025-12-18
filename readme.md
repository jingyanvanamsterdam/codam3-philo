## rules
./philo number_philo, time_die, time_eat, time_sleep, [number_of_times_each_philosopher_must_eat]
in miliseconds
time_die: start of last meal or start of simulation to now

A message announcing a philosopher’s death must be displayed within 10 ms of
their actual death.

Any state change of a philosopher must be formatted as follows:
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
Replace timestamp_in_ms with the current timestamp in milliseconds
and X with the philosopher number.

## resource: fork = semaphore 
1. grab: wait() 
2. release: signal()
binary value of semaphone: 1 = free as init

## threads: philosopher (in case of 5)
1. eat: wait(fork[i]; wait(fork[(i+1)%5]) => success: start eating
2. finish eat: singal(fork[i]); signal(fork[(i+1)%5])
3. sleep -> thinking

## lock
1. requesting a lock, while holding, no access to other people.
2. who is allowed to ask for the fork with priority 
3. atomic locking opration: no two asking at the same time. 

## Not understand
• A displayed state message should not overlap with another message.
• A message announcing a philosopher’s death must be displayed within 10 ms of
their actual death.