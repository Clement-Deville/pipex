# Pipex Project README

## Description

This project is part of the curriculum at 42 SCHOOL and involves implementing a program called Pipex, which simulates the functionality of the shell's pipe '|' operator in Unix-like operating systems. The objective is to execute commands provided as arguments to the program and redirect their standard input and output through pipes, mimicking the behavior of shell pipelines.

## Features

- Execute commands with input/output redirection using pipes.
- Handle multiple commands and redirections simultaneously.
- Support for both horizontal and vertical piping.
- Handle error exit code as bash would do.

## Getting Started

### Prerequisites

- A Unix-like operating system (Linux, macOS).
- Standard C library.

### Installation

To compile the Pipex program, run the following command in your terminal:

```bash
make
```

This will generate an executable file named pipex.

```bash
make bonus
```

This will generate an executable file named pipex_bonus.

```bash
make norminette
```
This will check the norme of the code.


## Usage

### Mandatory part

You can run the Pipex program with the following syntax:

```bash
./pipex file1 cmd1 cmd2 file2
```

- file1: Input file whose content will be redirected to the standard input of cmd1.
- cmd1: First command to be executed.
- cmd2: Second command to be executed.
- file2: Output file where the standard output of cmd2 will be redirected.

Example:

```bash
./pipex infile "ls -l" "wc -l" outfile
```

This will execute ls -l and wc -l commands with input from infile and output to outfile.

### Bonus part

You can run the Pipex Bonus program with the following syntax:

```bash
 ./pipex_bonus file1 cmd1 cmd2 cmd3 ... cmdn file2
```
- file1: Input file whose content will be redirected to the standard input of cmd1.
- cmd1: First command to be executed.
- cmdn: Nth command to be executed.
- file2: Output file where the standard output of cmdn will be redirected.

#### Here_doc

You can use the "here_doc" bash functionnality with the following syntax:

```bash
./pipex here_doc LIMITER cmd1 ... cmdn file
```

- here_doc: Modify the behavior of the program so the program reads stdin until "LIMITER" is write, and, the output is now append to "file".
- LIMITER: Limiter of the read from stdin
- cmd1: First command to be executed.
- cmdn: Nth command to be executed.
- file: Output file where the standard output of cmdn will be redirected as appended if file exists.

## Authors

- Clement DEVILLE
- login: cdeville
- github: https://github.com/Clement-Deville
