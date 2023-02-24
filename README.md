# Pipex
School 42 project

This project consists in managing a pipe.
Example of use:
In bash, this
< Makefile cat -e | wc -l > outfile
is the same as
./pipex Makefile "cat -e" "wc -l" outfile

This project can only execute simple shell commands.
