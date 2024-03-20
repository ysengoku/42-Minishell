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
	base->lst = NULL;
	base->env = envp;

	/* test case */
	/* < in cat | grep Hello | wc -l > out_expected */
	/* Expected result: '3' in out_expected */
	base->lst = malloc(sizeof(t_line));
	base->lst->read = malloc(sizeof(char **));
	base->lst->write = malloc(sizeof(char **));
	base->lst->read[0] = ft_strdup("in");
	base->lst->write[0] = NULL;
	base->lst->arg = malloc(sizeof(char **));
	base->lst->arg[0] = ft_strdup("/bin/cat");
	base->lst->arg[1] = NULL;
	base->lst->append = false;
	base->lst->next = NULL;

	t_line	*new;
	new = malloc(sizeof(t_line));
	new->read = malloc(sizeof(char **));
	new->write = malloc(sizeof(char **));
	new->read[0] = NULL;
	// new->write = NULL;
	new->write[0] = ft_strdup("out");
	new->arg = malloc(sizeof(char **));
	new->arg[0] = ft_strdup("/bin/grep");
	new->arg[1] = ft_strdup("Hello");
	new->arg[2] = NULL;
	new->append = false;
	new->next = NULL;
	base->lst->next = new;

	new = NULL;
	new =  malloc(sizeof(t_line));
	new->read = malloc(sizeof(char **));
	new->write = malloc(sizeof(char **));
	new->read[0] = NULL;
	new->write[0] = ft_strdup("out2");
	new->write[1] = ft_strdup("out");
	new->arg = malloc(sizeof(char **));
	new->arg[0] = ft_strdup("/usr/bin/wc");
	new->arg[1] = ft_strdup("-l");
	new->arg[2] = NULL;
	new->append = true;
	new->next = NULL;
	base->lst->next->next = new;

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
	free(base->lst->arg);
	free(base->lst->next->arg[0]);
	free(base->lst->next->arg[1]);
	// free(base->lst->next->write);
	free(base->lst->next->next->arg[0]);
	free(base->lst->next->next->arg[1]);
	free(base->lst->next->next->write);
	while (base->lst->next)
	{
		free(base->lst->arg);
		free(base->lst);
		base->lst = base->lst->next;
	}
	free(base);
    return 0;
}
