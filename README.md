Philosophers is a 42 school project that aims to solve the dining philosophers problem, a classic synchronization problem in computer science.

Overview

A group of philosophers sit around a dining table and alternate between sleeping, thinking and eating.
The number of forks is limited, and equal to the number of philosophers. This leads to potential deadlock if philosophers try to acquire the same forks simultaneously. 
The challenge is to prevent deadlock and starvation while ensuring that philosophers can eat without conflicting with each other.
The implemented solution uses multi-threading and synchronization mechanisms to ensure that the philosophers can eat without deadlock or starvation.

Features

* Multi-threaded simulation: The project simulates multiple philosophers and forks using threads, allowing for concurrent execution of philosopher activities.
* Concurrency control: The project implements synchronization mechanisms (mutexes) to control access to shared resources (forks) and prevent race conditions.
* Deadlock prevention: The solution prevents deadlock by ensuring that philosophers can acquire the necessary forks without blocking each other indefinitely.
* Starvation avoidance: The solution ensures that all philosophers have an equal opportunity to eat.

Usage

* Compile with make
* Execute the program with the desired number of philosophers and simulation parameters:

  ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [(optional) number_of_times_each_philosopher_must_eat] 
* Observe the behavior of the philosophers as they alternate between thinking, eating, and sleeping, ensuring that they do not encounter deadlock or starvation.
