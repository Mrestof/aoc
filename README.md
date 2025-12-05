# Mrestof's Advent of Code solutions

A collection of inputs, solutions and some tools around them, all for yearly
Advent of Code.

## Run the solutions

If you want to run some of the solutions yourself, follow the appropriate
section below.

### 2025 C [5/12]

1. Have the required tools installed
    - aocd (advent-of-code-data 2.0.1)
        - Have your session key set. For details check [their
          docs](https://github.com/wimglenn/advent-of-code-data#quickstart).
        - You either must have `aocd` in PATH, or it must be installed in the
          `.venv`, that you can put somewhere in the project folder, above, or
          at the same level as `run.sh`, so that it can automatically source
          the venv and use the tool from it
    - entr (to automatically recompile and run)
    - ts (for timestamps)
    - gcc (to compile)
2. Run the solutions
    - Run a single solution
        - Execute `run.sh` script with no arguments to run the latest updated c
          file in `src` dir.
        - Execute `run.sh src/yearYYYY/dayD.c` script with a filiename passed
          as the first argument to compile and run the specified file.
    - Continuosly recompile and run on any changes to files
        - Execute `concom.sh` to watch the source files for any changes, and on
          each new write to a file, automatically execute `run.sh`

### 2024 Go [1/25]

1. Have Go compiler installed.
    > [ArchLinux guide](https://wiki.archlinux.org/title/Go) for reference
2. Go to solutions in Go and run the entrypoint, it will run all the available
   solutions.
    ```bash
    cd ./solutions/go/
    go run .
    ```

### 2023 Rust [1/25]

1. Have Rust with Cargo installed.
    > [ArchLinux guide](https://wiki.archlinux.org/title/Rust) for reference
2. Go to solutions in Rust and run the entrypoint, it will run all the
   available solutions.
    ```bash
    cd ./solutions/rust/
    cargo run
    ```

### 2021 Python [3/25]

1. Prepare requirements:
    - Have Python of version 3.10 or higher.
    - Have all the packages from `meta/python/requirements.txt` file installed.
    - Have your session key specified for the `aocd` library, for details check
      their [docs](https://github.com/wimglenn/advent-of-code-data#quickstart).
2. Run any single solution by running an appropriate `main.py` script in
   `./solutions/python/`, it will not print anything but will automatically try
   to submit the calculated answers with your session key.
