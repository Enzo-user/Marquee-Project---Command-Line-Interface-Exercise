# Marquee Project - Command Line Interface Exercise

A CSOPESY exercise: a C++ main menu console that serves as the front end for a
future text marquee. On startup it prints a welcome header, then repeatedly
shows a `Command>` prompt and interprets what the user types.

The whole program lives in `main.cpp` and uses only standard C++ I/O streams
(`std::cin` / `std::cout`) with `std::string` comparisons for command matching.

## Build and run

Using g++ (MinGW, Linux, macOS):

```bash
g++ -std=c++17 -Wall -Wextra -o console main.cpp
./console
```

Using MSVC (from a Developer Command Prompt):

```bat
cl /EHsc /W4 /std:c++17 /Fe:console.exe main.cpp
console.exe
```

## Commands

| Command | Description |
| --- | --- |
| `help` | Displays the commands and their descriptions |
| `set_text <your_string>` | Saves the text after the command as the marquee text |
| `exit` | Terminates the console |

`start_marquee`, `stop_marquee`, and `set_speed` are listed in `help` but are not
implemented yet; entering them prints a "not yet implemented" message. Any other
input prints an error and returns to the prompt. Commands are case-sensitive.

## Sample session

```
Welcome to CSOPESY!

Group developer:
De La Cruz, Juan
Santos, Alex

Version date: 2026-09-18

Command> help
help - displays the commands and its description
start_marquee - starts the marquee "animation"
stop_marquee - stops the marquee "animation"
set_text - accepts a text input and displays it as a marquee
set_speed - sets the marquee animation refresh in milliseconds
exit - terminates the console

Command> set_text Operating Systems are fun!
Text saved for marquee: Operating Systems are fun!

Command> exit
Terminating console...
```
