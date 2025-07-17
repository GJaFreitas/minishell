#include "minishell.h"
#include "parser.h"
#include "lexer.h"
#include "structs.h"
#include <readline/readline.h>
#include <readline/history.h>
#include "exec.h"

int	g_sig;


/*test ================================================================= */

t_cmd *create_test_cmd(char *cmd, char *redir_type, char *filename)
{
    t_cmd *command = ft_calloc(1, sizeof(t_cmd));
    
    command->args = ft_calloc(2, sizeof(char *));
    command->args[0] = ft_strdup(cmd);
    command->args[1] = NULL;

    if (redir_type && filename)
    {
        command->redirect = ft_calloc(1, sizeof(t_redirect));
        command->redirect->args[0] = ft_strdup(redir_type);
        command->redirect->args[1] = ft_strdup(filename);
        command->redirect->next = NULL;
    }
    
    // Default file descriptors
    command->redirect_in = 0;
    command->redirect_out = 1;
    
    return command;
}

// Test function to create a pipeline
t_cmd *create_test_pipeline(char **cmds, int num_cmds)
{
    if (num_cmds == 0)
        return NULL;
    
    t_cmd *head = create_test_cmd(cmds[0], NULL, NULL);
    t_cmd *current = head;
    
    for (int i = 1; i < num_cmds; i++)
    {
        current->next = create_test_cmd(cmds[i], NULL, NULL);
        current = current->next;
    }
    
    return head;
}

// Function to run the tests
void run_redirection_tests(char **env)
{
    // Test case 1: Simple output redirection (ls > output.txt)
    ft_printf("\n\n===== TEST 1: Simple output redirection (ls > output.txt) =====\n");
    t_cmd *test1 = create_test_cmd("/bin/ls", ">", "output.txt");
    ft_exec_all(test1, env);
    ft_printf("Check output.txt file for the result\n");
    
    // Test case 2: Append output redirection (echo hello >> output.txt)
    ft_printf("\n\n===== TEST 2: Append output redirection (echo hello >> output.txt) =====\n");
    t_cmd *test2 = create_test_cmd("/bin/echo", ">>", "output.txt");
    test2->args = ft_calloc(3, sizeof(char *));
    test2->args[0] = ft_strdup("/bin/echo");
    test2->args[1] = ft_strdup("hello");
    test2->args[2] = NULL;
    ft_exec_all(test2, env);
    ft_printf("Check output.txt file for the result\n");
    
    // Test case 3: Input redirection (cat < output.txt)
    ft_printf("\n\n===== TEST 3: Input redirection (cat < output.txt) =====\n");
    t_cmd *test3 = create_test_cmd("/bin/cat", "<", "output.txt");
    ft_exec_all(test3, env);
    
    // Test case 4: Pipeline (ls | grep a)
    ft_printf("\n\n===== TEST 4: Pipeline (ls | grep a) =====\n");
    char *pipeline_cmds[] = {"/bin/ls", "/bin/grep"};
    t_cmd *test4 = create_test_pipeline(pipeline_cmds, 2);
    test4->next->args = ft_calloc(3, sizeof(char *));
    test4->next->args[0] = ft_strdup("/bin/grep");
    test4->next->args[1] = ft_strdup("a");
    test4->next->args[2] = NULL;
    ft_exec_all(test4, env);
    
    // Test case 5: Pipeline with redirections (cat < input.txt | grep hello > output2.txt)
    ft_printf("\n\n===== TEST 5: Pipeline with redirections =====\n");
    ft_printf("Creating test input file...\n");
    int fd = open("input.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    write(fd, "hello world\nhello minishell\ngoodbye\n", 36);
    close(fd);
    
    char *pipeline_cmds2[] = {"/bin/cat", "/bin/grep"};
    t_cmd *test5 = create_test_pipeline(pipeline_cmds2, 2);
    
    // Add input redirection to cat
    test5->redirect = ft_calloc(1, sizeof(t_redirect));
    test5->redirect->args[0] = ft_strdup("<");
    test5->redirect->args[1] = ft_strdup("input.txt");
    
    // Set up grep command
    test5->next->args = ft_calloc(3, sizeof(char *));
    test5->next->args[0] = ft_strdup("/bin/grep");
    test5->next->args[1] = ft_strdup("hello");
    test5->next->args[2] = NULL;
    
    // Add output redirection to grep
    test5->next->redirect = ft_calloc(1, sizeof(t_redirect));
    test5->next->redirect->args[0] = ft_strdup(">");
    test5->next->redirect->args[1] = ft_strdup("output2.txt");
    
    ft_exec_all(test5, env);
    ft_printf("Check output2.txt for results\n");
}


/*test ================================================================= */


// Display prompt and read the next line given to it
t_cmd	*prompt(char **env)
{
	char *line;
	char cwd[CWD_BUFFER];

	if (!getcwd(cwd, CWD_BUFFER))
		perror("getcwd() error\n");
	if (feof(stdin))
		return (ft_printf("exit"), NULL);
	ft_memcpy(cwd + ft_strlen(cwd) - 1, " » ", 4);
	line = readline(cwd);
	if (!line)
		exit(0);
	return (parser(lexer(line), env));
}

static void	shell_loop(char **env)
{
	t_cmd	*cmd;

	while (1)
	{
		cmd = prompt(env);
		ft_exec_all(cmd, env);
	}
	
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	
    #ifdef TEST_REDIRECTIONS
        ft_printf("\n===== RUNNING REDIRECTION TESTS =====\n");
        run_redirection_tests(env);
        ft_printf("\n===== TESTS COMPLETED, STARTING SHELL =====\n\n");
	#else
		shell_loop(env);
    #endif	
	return (0);
}
