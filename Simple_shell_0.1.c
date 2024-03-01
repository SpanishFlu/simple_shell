#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

/**
 * display_prompt - Displays the command prompt
 */
void display_prompt(void)
{
	printf("#cisfun$ ");
}

/**
 * read_command - Reads user input into the command buffer
 * @command: Buffer to store the user's input
 * Return: 1 on success, 0 on failure
 */
int read_command(char *command)
{
	if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
	{
		printf("\n");
		return (0);
	}

	command[strcspn(command, "\n")] = '\0';
	return (1);
}

/**
 * execute_command - Executes the user's command
 * @command: The user's command
 */
void execute_command(char *command)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("Fork error");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execlp(command, command, (char *)NULL);
		fprintf(stderr, "%s: command not found\n", command);
		exit(EXIT_FAILURE);
	}
	else
	{
		int status;

		waitpid(pid, &status, 0);

	if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS)
	{
		printf("Child process exited successfully.\n");
	}
	else
	{
		printf("Child process failed.\n");
	}
	}
}

/**
 * main - Entry point for the simple shell program
 *
 * This function serves as the entry point for the simple shell. It displays
 * a command prompt, waits for the user to input a command, executes the
 * command in a child process, and prints the result or an error message.
 * The shell continues to prompt for commands until the user exits by pressing
 * Ctrl+D. The function utilizes fork, exec, and waitpid system calls to
 * create and manage child processes.
 *
 * Return: Always returns 0 to indicate successful execution.
 */
int main(void)
{
	char command[MAX_COMMAND_LENGTH];

	while (1)
	{
		display_prompt();

		if (!read_command(command))
		{
			break;
		}

		execute_command(command);
	}

	return (0);
}

