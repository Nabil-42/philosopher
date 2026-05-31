# Philosophers

[![Language](https://img.shields.io/badge/Language-C-A8B9CC?style=flat&logo=c)](https://github.com/Nabil-42/philosopher)
[![School](https://img.shields.io/badge/%C3%89cole_42-Paris-00babc?style=flat)](https://42.fr)
[![Norminette](https://img.shields.io/badge/Norminette-compliant-brightgreen?style=flat)](https://github.com/42School/norminette)

Implementation of the classic dining philosophers problem using POSIX threads and mutexes.

## Description

`philosophers` simulates N philosophers sitting at a round table, each alternating between thinking, picking up forks, eating, and putting down forks. The challenge is to prevent deadlocks and starvation while correctly detecting when a philosopher has died.

## Rules

- Each philosopher is a thread
- Each fork is a mutex shared between two adjacent philosophers
- A philosopher dies if they have not eaten within `time_to_die` milliseconds
- The simulation stops when one philosopher dies, or when all have eaten `number_of_times` times (optional)

## Usage

```bash
make
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

Example:
```bash
./philo 5 800 200 200
```

## Architecture

```
main → parse args → init forks (mutexes) → init philosophers (threads)
     → each thread: loop { think → lock forks → eat → unlock → sleep }
     → monitor thread: check timestamps → detect death → stop all
```

## Stack

- **Language**: C
- **Key concepts**: POSIX threads (`pthread_create`, `pthread_join`), mutexes (`pthread_mutex_t`), race conditions, deadlock prevention

## 42 Project Info

| Field | Value |
|-------|-------|
| **Project** | Philosophers |
| **Circle** | 3 |
| **Norminette** | Compliant |

## What I Learned

- Thread lifecycle management with `pthread_create` and `pthread_join`
- Mutex locking strategies to avoid deadlocks
- Precise timing with `gettimeofday` and `usleep`
- Detecting race conditions and data races