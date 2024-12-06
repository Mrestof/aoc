# Mrestof's Advent of Code solutions

A collection of inputs, solutions and some tools around them,
all for yearly Advent of Code.

## Run the solutions

If you want to run some of the solutions by yourself,
follow the appropriate section below.

### Python [3/25]

1. Prepare requirements:
    - Have Python of version 3.10 or higher.
    - Have all the packages from `meta/python/requirements.txt` file installed.
    - Have your session key specified for the `aocd` library, for details check
    their [docs](https://github.com/wimglenn/advent-of-code-data#quickstart).
2. Run any single solution by running an appropriate `main.py` script
in `./solutions/python/`, it will not print anything but will automatically
try to submit the calculated answers with your session key.

### Rust [1/25]

1. Have Rust with Cargo installed.
    > [ArchLinux guide](https://wiki.archlinux.org/title/Rust) for reference
2. Go to solutions in Rust and run the entrypoint, it will run all the available solutions.
    ```bash
    cd ./solutions/rust/
    cargo run
    ```

### Go [1/25]

1. Have Go compiler installed.
    > [ArchLinux guide](https://wiki.archlinux.org/title/Go) for reference
2. Go to solutions in Go and run the entrypoint, it will run all the available solutions.
    ```bash
    cd ./solutions/go/
    go run .
    ```
