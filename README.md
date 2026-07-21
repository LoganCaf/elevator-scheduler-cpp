# Elevator Scheduler in C++

A C++23 elevator simulation that compares first-in, first-out routing with a greedy nearest-stop scheduler. The simulator tracks queued destinations, visit order, current floor, and total travel time.

For the route `12 -> 2 -> 9 -> 1 -> 32`, nearest-stop scheduling lowers simulated travel time from 560 to 420 units, a 25% reduction.

## Scheduling Strategies

- **FIFO:** visits destinations in the order they were requested.
- **Nearest stop:** repeatedly chooses the pending destination with the shortest distance from the current floor.

## Build and Run

Requirements: a C++23 compiler, CMake 3.20 or newer, and Git. CMake retrieves Catch2 during configuration.

```bash
cmake -S . -B build
cmake --build build
./build/elevator
```

Enter a starting floor, a comma-separated destination list, and whether to optimize the route.

## Test

```bash
ctest --test-dir build --output-on-failure
```

The Catch2 suite contains 20 test cases covering initialization, destination queues, movement, numeric boundaries, FIFO routing, and nearest-stop routing. GitHub Actions rebuilds and runs the suite on every push and pull request.
