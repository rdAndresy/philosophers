# philosophers
Project to learn about basics of threading, data races, and how to use mutexes to get rid of them.

## The Dining Philosophers Problem
[The dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) is a famous problem in computer science used to illustrate common issues in [concurrent programming](https://en.wikipedia.org/wiki/Concurrency_(computer_science)). The problem was originally formulated in 1965 by [Edsger Dijkstra](https://en.wikipedia.org/wiki/Edsger_W._Dijkstra), and is stated as follows:

       X amount of philosophers sit at a round table with bowls of food.
       Forks are placed in front of each philosopher.
       There are as many forks as philosophers.
       All day the philosophers take turns eating, sleeping, and thinking.
       A philosopher must have two forks in order to eat, and each fork
       may only be used by one philosopher at a time. At any time a
       philosopher can pick up or set down a fork,
       but cannot start eating until picking up both forks.
       The philosophers alternatively eat, sleep, or think.
       While they are eating, they are not thinking nor sleeping,
       while thinking, they are not eating nor sleeping,
       and, of course, while sleeping, they are not eating nor thinking.

## How to use

The program should take the following arguments: *number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]*
* **number_of_philosophers**: The number of philosophers and also the number of forks.
* **time_to_die** (in milliseconds): If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
* **time_to_eat** (in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
* **time_to_sleep** (in milliseconds): The time a philosopher will spend sleeping.
* **number_of_times_each_philosopher_must_eat** (optional argument): If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies.

Each philosopher has a number ranging from 1 to number_of_philosophers.

Philosopher number 1 sits next to philosopher number number_of_philosophers. Any other philosopher number N sits between philosopher number N - 1 and philosopher number N + 1.

## How to read logs
Any state change of a philosopher is formatted as follows:
* timestamp_in_ms X has taken a fork
* timestamp_in_ms X is eating
* timestamp_in_ms X is sleeping
* timestamp_in_ms X is thinking
* timestamp_in_ms X died
timestamp_in_ms is the current timestamp in milliseconds and X the philosopher number.

## Project constraints
* Global variables are forbidden
* A message announcing a philosopher died should be displayed no more than 10 ms after the actual death of the philosopher.