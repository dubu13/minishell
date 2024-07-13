# Minishell

A simple shell implementation in C, inspired by bash.

## Features

- Command execution
- Built-in commands: echo, cd, pwd, export
- Input/output redirection
- Pipes
- Signal handling
- Environment variable expansion

## Installation

1. Clone the repository:

```
git clone git@github.com:dubu13/minishell.git
```

2. Initialize and update the submodules:

```
make submodule
```

3. Compile the project:

```
make
```


## Usage

Run the shell:

```
./minishell
```

## Built-in Commands

- `echo`: Display a line of text
- `cd`: Change the current directory
- `pwd`: Print the current working directory
- `export`: Set environment variables

## Development

This project uses a custom library. The library is included as a Git submodule in the `lib` directory.

## Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.
