/*
the symbol "curpath" represents an intermediate value used to simplify the description of the algorithm used by cd.

1. 2. no directory operand ('cd')
	envp HOME == empty --> error & return 
	envp HOME != empty --> go to $HOME
*/
#include "minishell.h"

int	ft_cd(t_base *base)
{
	char	*path;
	char	*tmp;
	t_env	*pwd;
	t_env	*oldpwd;

	pwd = find_env_var(base, "PWD");
	oldpwd = find_env_var(base, "OLDPWD");
	if (pwd == NULL || oldpwd == NULL)
		return (1);
	if (base->lst->arg[1] == NULL || ft_strncmp(base->lst->arg[1], ".", 2) == 0
		|| ft_strncmp(base->lst->arg[1], "~", 2) == 0
		|| ft_strncmp(base->lst->arg[1], "~/", 3) == 0)
		path = get_path(base, "HOME");
	else
		path = ft_strdup(base->lst->arg[1]);
	if (!path)
		return (1);
	if (path[0] != '/') //step 7
	{
		tmp = path;
		path = ft_calloc(ft_strlen(pwd->value) + ft_strlen(base->lst->arg[1])
			+ 2, sizeof(char));
		free(tmp);
		if (!path)
			return (ft_perror("malloc", 1));
		ft_strcpy(path, pwd->value);
		if (path[ft_strlen(path) - 1] != '/')
			ft_strcat(path, "/");
		ft_strcat(path, base->lst->arg[1]);
	}

	// else if (ft_strncmp(base->lst->arg[1], "-", 2) == 0)
	// 	path = get_path(base, "OLDPWD");
	if (ft_chdir(path, base) == 1)
		return (ft_free((void *)path, 1));
	if (base->lst->arg[1] && ft_strncmp(base->lst->arg[1], "-", 2) == 0)
		printf("%s\n", path);
	return (ft_free((void *)path, 0));
}
/*
3. directory operand begins with a '/' ('cd /......')
    set curpath to the operand and proceed to step 7.

4. If the first component of the directory operand is dot or dot-dot ('cd .' or 'cd ..')
	proceed to step 6.

5. CDPATH (ENVIRONMENT VARIABLE) case --> not concerned here ?

6. Set curpath to the directory operand.

7. If curpath does not begin with a <slash> character,
	set curpath to the string formed by the concatenation of 
		- the value of PWD
		- a <slash> character if the value of PWD did not end with a <slash> character
		- and curpath.
-------------------------------------------

8. The curpath value shall then be converted to canonical form as follows, 
considering each component from beginning to end,
in sequence:

    a. Dot components and any <slash> characters that separate them from the next component shall be deleted.

    b. For each dot-dot component, if there is a preceding component and it is neither root nor dot-dot, then:

        i.  If the preceding component does not refer (in the context of pathname resolution with symbolic links
            followed) to a directory, 
				--> display an error message & return

        ii. The preceding component, all <slash> characters separating the preceding component from dot-dot,
            dot-dot, and all <slash> characters separating dot-dot from the following component (if any) 
			shall be deleted.

    c. An implementation may further simplify curpath by removing any trailing <slash> characters that are not
    	also leading <slash> characters, replacing multiple non-leading consecutive <slash> characters with a single
        <slash>, and replacing three or more leading <slash> characters with a single <slash>.
		If, as a result of this canonicalization, the curpath variable is null, no further steps shall be taken.

9. If curpath length > {PATH_MAX} bytes && the directory operand length <= {PATH_MAX} bytes (including \0), 
	then curpath shall be converted from an absolute pathname to an equivalent relative pathname if possible. 
	This conversion shall always be considered possible if the value of PWD, with a trailing <slash> added 
	if it does not already have one, is an initial substring of curpath.  
	Whether or not it is considered possible under other circumstances is unspecified.
    Implementations may also apply this conversion if curpath is not longer than {PATH_MAX} bytes 
	or the directory operand was longer than {PATH_MAX} bytes.

       10. ///// chdir() called with curpath as the path argument. /////
		   If these actions fail for any reason, the cd utility shall
           display an appropriate error message and the remainder of this step shall not be executed.
		   
		   the PWD environment variable shall be set to the value that curpath had on entry to step 9
		   (i.e., before conversion to a relative pathname). 
		   the OLDPWD environment variable shall also be set to the value of the old working directory 
			(that is the current working directory immediately prior to the call to cd).
		   
		If there is insufficient permission on the new directory, or on any parent of that directory,
		to determine the current working directory, the value of the PWD environment variable is unspecified.
*/
