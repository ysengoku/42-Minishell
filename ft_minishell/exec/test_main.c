#include <stdio.h>
#include <unistd.h>
#include "minishell.h"

#define BUFFER_SIZE 1024

int main(int ac, char **av, char **envp)
{
	t_base	*base;

	(void)ac;
	(void)av;

	base = malloc(sizeof(t_base));
	base->env = envp;

	/* test case */
	base->lst = malloc(sizeof(t_line) * 3);

	base->lst->read = ft_strdup("in");
	base->lst->write = NULL;
	base->lst->arg[0] = ft_strdup("cat");
	base->lst->arg[1] = NULL;

	base->lst->next->read = NULL;
	base->lst->next->write = NULL;
	base->lst->next->arg[0] = ft_strdup("grep");
	base->lst->next->arg[1] = ft_strdup("Hello");
	base->lst->next->arg[2] = NULL;

	base->lst->next->next->next = NULL;
	base->lst->next->write = ft_strdup("out");
	base->lst->next->arg[0] = ft_strdup("wc");
	base->lst->next->arg[1] = ft_strdup("-l");
	base->lst->next->arg[2] = NULL;
	base->lst->next->next->next = NULL;

	ft_exec(base);

// //     char *line;
// //     // while(1)
// //     // {
// //     //     // Read a line of input
// //     //     line = readline(">$ ");

// //     //     if (line)
// //     //     {
// //     //     // Print the line
// //     //         printf("You entered: %s\n", line);

// //     //     // Add the line to history
// //     //         add_history(line);

// //     //     // Free the allocated memory for the line
// //     //         free(line);
// //     //     }
// //     // }

//     // char line[BUFFER_SIZE];
//     // getcwd(line, sizeof(line));
//     // printf("%s\n", line);
//     t_line   *list;
//     list = NULL;
//     ft_pwd(list);

	free(base->lst->read);
	free(base->lst->arg[0]);
	free(base->lst->next->arg[0]);
	free(base->lst->next->arg[1]);
	free(base->lst->next->write);
	free(base->lst->next->arg[0]);
	free(base->lst->next->arg[1]);
	while (base->lst->next)
	{
		free(base->lst);
		base->lst = base->lst->next;
	}
	free(base);
    return 0;
}
