# Terminal Maze

A lightweight, highly customizable maze game that runs directly in your terminal. Written in C, it uses command-line arguments for maze generation, offering a classic gaming experience with a modern, configurable twist.

## Installation

[Terminal Maze Gameplay](./showcase.mp4)

Follow these instructions to get a copy of the project up and running on your local machine.

1.  **Clone the repository:**
    ```sh
    git clone https://github.com/RedeemedSpoon/Terminal-Maze.git
    ```

2.  **Navigate to the project directory:**
    ```sh
    cd Terminal-Maze
    mkdir build
    ```

3.  **Build the project using CMake and Make:**
    ```sh
    cd build && cmake ..
    make
    ```
    This will generate an executable file named `maze` in the `bin` directory.

## Usage

To run the game, execute the compiled binary from your terminal.

```sh
./bin/maze [options] # sudo mv ./bin/maze /usr/bin to access the game form anywhere
```

## Command-Line Options

The application supports the following options to customize the game experience:

| Flag | Long Flag | Argument | Description |
|:---|:---|:---|:---|
| `-h` | `--help` | | Displays the help message with all available options. |
| `-v` | `--version` | | Shows the current version of the program. |
| `-w` | `--window` | `WIDTHxHEIGHT` | Sets the maze dimensions. (e.g., `80x25`) |
| `-c` | `--color` | `<COLOR>` | Sets the color of the maze path. (e.g., `RED`, `BLUE`) |
| `-s` | `--seed` | `<SEED>` | Provides a seed for the random number generator, allowing for reproducible mazes. |
| `-t` | `--trail` | | Enables a trail that visually marks the player's path through the maze. |

## Contributing

Contributions are what make the open-source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".

1.  Fork the Project
2.  Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3.  Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4.  Push to the Branch (`git push origin feature/AmazingFeature`)
5.  Open a Pull Request

## License

Distributed under the GPLv3 License. See the `LICENSE` file for more information.
