# 🧘‍♂️ Philosophers

**Philosophers** is a project from the 42 curriculum that explores concurrency and synchronization using threads and mutexes. The goal is to simulate the classic **Dining Philosophers Problem**, ensuring proper resource management and avoiding deadlocks.

---

## 🛠 Features

- **Thread Management**: Each philosopher runs as an independent thread.
- **Mutexes**: Used to prevent race conditions on shared resources (e.g., forks).
- **Accurate Timing**: Includes a custom `usleep` implementation for precise timing.
- **Resource Cleanup**: Ensures all threads and mutexes are properly released.
- **Simulation Logic**:
  - Philosophers alternate between thinking, eating, and sleeping.
  - They must pick up two forks to eat.
  - Simulation stops if a philosopher dies or after a defined number of meals.

---

## 🛠 Installation  

No compilation is necessary, as a pre-built binary is provided.

### 1. Clone the Repository  
    
    git clone https://github.com/yourusername/philosophers.git
    cd philosophers ; make

### 2. Run program:

    ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]

### 3. Exemple
    ./philo 5 800 200 200

## ❗️ Rules and Restrictions
- A philosopher dies if they don’t start eating within time_to_die milliseconds.
- Philosophers can only pick up forks that are not currently in use.
- Simulation stops when:
    - A philosopher dies.
    - Optional: All philosophers have eaten the specified number of times.

## 🧩 Implementation Details
- Initialization:
    - The program initializes threads, mutexes, and shared data structures before starting the  simulation.

- Routine:
    - Each philosopher follows a loop: Think → Pick Up Forks → Eat → Put Down Forks → Sleep.

- Monitoring:
    - A separate thread monitors the status of philosophers to detect starvation or completion of the meal limit.



## 📂 Directory Structure

```plaintext
.
├── Makefile               # Build script
├── README.md              # Project documentation
├── includes               # Header files
│   └── philo.h            # Main header for the project
├── lib                    # Utility functions
│   ├── ft_atoi.c          # Convert string to integer
│   ├── ft_calloc.c        # Memory allocation with initialization
│   ├── ft_print.c         # Custom print functions
│   ├── ft_strlen.c        # String length utility
│   ├── ft_usleep.c        # Precise sleep implementation
│   └── get_time.c         # Time handling functions
└── src                    # Source files
    ├── init.c             # Initialization of resources and structures
    ├── main.c             # Entry point of the program
    ├── monitoring.c       # Monitoring philosophers' states
    ├── parsing.c          # Input argument validation and parsing
    └── routine.c          # Core philosopher actions (eat, sleep, think)


