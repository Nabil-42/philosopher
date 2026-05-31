# Usage — Philosophers

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

All time values are in milliseconds.

## Examples

```bash
# 5 philosophers, die if not eating within 800ms, eat 200ms, sleep 200ms
./philo 5 800 200 200

# Stop after each philosopher has eaten 7 times
./philo 5 800 200 200 7
```

## Output Format

```
timestamp_in_ms philosopher_number action
```

Actions: `is thinking`, `has taken a fork`, `is eating`, `is sleeping`, `died`

Example output:

```
0       1 is thinking
0       2 is thinking
1       1 has taken a fork
1       1 has taken a fork
1       1 is eating
201     1 is sleeping
...
```

## Notes

- If a philosopher dies, the simulation stops and `died` is printed
- No philosopher should die if the timing parameters allow it
- Data races are prevented — verified with thread sanitizer