/*
 * CSOPESY - Marquee Project: Command Line Interface Exercise
 *
 * Main menu console for the future text marquee. The program prints a
 * welcome header once, then loops on a "Command> " prompt, reading one
 * line at a time and dispatching it to the matching command handler.
 *
 * Only standard C++ streams are used (std::cin / std::cout), and all
 * command matching is done with std::string comparisons.
 *
 * Build:  g++ -std=c++17 -Wall -Wextra -o console main.cpp
 * Run:    ./console
 */

#include <iostream>
#include <string>

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

/*
 * Returns a copy of `text` with leading and trailing whitespace removed.
 * Internal whitespace is kept untouched so that set_text preserves the
 * spacing the user typed between words.
 */
std::string trim(const std::string& text)
{
    const std::string whitespace = " \t\r\n";

    const std::string::size_type start = text.find_first_not_of(whitespace);
    if (start == std::string::npos) {
        return "";  // the string is empty or all whitespace
    }

    const std::string::size_type end = text.find_last_not_of(whitespace);
    return text.substr(start, end - start + 1);
}

/*
 * Splits an input line into the command (first word) and the argument
 * (everything after the first word). Both parts are trimmed.
 */
void splitInput(const std::string& line, std::string& command, std::string& argument)
{
    const std::string trimmedLine = trim(line);

    const std::string::size_type space = trimmedLine.find_first_of(" \t");
    if (space == std::string::npos) {
        // Single word, no argument.
        command = trimmedLine;
        argument = "";
    } else {
        command = trimmedLine.substr(0, space);
        argument = trim(trimmedLine.substr(space + 1));
    }
}

// ---------------------------------------------------------------------------
// Command handlers (one function per command)
// ---------------------------------------------------------------------------

/* Prints the welcome header shown once at startup. */
void printHeader()
{
    std::cout << "Welcome to CSOPESY!\n";
    std::cout << "\n";
    std::cout << "Group developer:\n";
    std::cout << "De La Cruz, Juan\n";
    std::cout << "Santos, Alex\n";
    std::cout << "\n";
    std::cout << "Version date: 2026-09-18\n";
    std::cout << "\n";
}

/* `help` - lists every command and its description. */
void printHelp()
{
    std::cout << "help - displays the commands and its description\n";
    std::cout << "start_marquee - starts the marquee \"animation\"\n";
    std::cout << "stop_marquee - stops the marquee \"animation\"\n";
    std::cout << "set_text - accepts a text input and displays it as a marquee\n";
    std::cout << "set_speed - sets the marquee animation refresh in milliseconds\n";
    std::cout << "exit - terminates the console\n";
}

/*
 * `set_text <your_string>` - stores the text after the command in
 * `marqueeText` and confirms it. An empty argument prints a usage
 * message instead of overwriting the stored text with nothing.
 */
void setText(const std::string& argument, std::string& marqueeText)
{
    if (argument.empty()) {
        std::cout << "Usage: set_text <your_string>\n";
        return;
    }

    marqueeText = argument;
    std::cout << "Text saved for marquee: " << marqueeText << "\n";
}

/* Placeholder for marquee commands that are listed in help but not built yet. */
void printNotImplemented(const std::string& command)
{
    std::cout << command << " is not yet implemented.\n";
}

/* Printed for any input that does not match a known command. */
void printUnknownCommand(const std::string& input)
{
    std::cout << "Unrecognized command: " << input << "\n";
    std::cout << "Type 'help' to see the list of available commands.\n";
}

// ---------------------------------------------------------------------------
// Main loop
// ---------------------------------------------------------------------------

int main()
{
    std::string marqueeText;  // text saved by set_text; outlives the loop

    printHeader();

    std::string line;
    while (true) {
        std::cout << "Command> ";

        // On EOF (Ctrl+D / Ctrl+Z) getline fails; leave the loop cleanly
        // instead of spinning on a closed input stream.
        if (!std::getline(std::cin, line)) {
            std::cout << "\n";
            break;
        }

        std::string command;
        std::string argument;
        splitInput(line, command, argument);

        // Blank input: just show the prompt again, no blank line or error.
        if (command.empty()) {
            continue;
        }

        // Dispatcher: commands are case-sensitive and must match exactly.
        // Commands that take no argument (help, exit) are rejected when extra
        // text follows them, so "exit now" is treated as unrecognized.
        if (command == "help" && argument.empty()) {
            printHelp();
        } else if (command == "set_text") {
            setText(argument, marqueeText);
        } else if (command == "exit" && argument.empty()) {
            std::cout << "Terminating console...\n";
            break;
        } else if (command == "start_marquee" || command == "stop_marquee"
                   || command == "set_speed") {
            printNotImplemented(command);
        } else {
            printUnknownCommand(trim(line));
        }

        std::cout << "\n";  // blank line between command output and next prompt
    }

    return 0;
}
