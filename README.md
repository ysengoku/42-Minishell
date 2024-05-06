## Minishell  
Minishell is a dynamic shell implementation in C including redirection, piping and expansion of environment variable as well as essential builtins.It was developped as the first team project within 42 school cursus.

### Usage
#### Interactive mode  
```bash
./minishell
```
#### Command line mode  
```bash
./minishell -c "commands"
```
#### To ignore leaks from readline with Valgrind (Thanks to @mcombeau)
```bash
valgrind --suppressions=.ignore_readline_leaks.supp --leak-check=full ./minishell
```
   

------------------------------------------------------------------------------
### Builtin function

#### cd with only a relative or absolute path  

Used function  
```c
int chdir(const char *path);
```
##### Relative path
```bash
# Navigate to parent directory
cd ..

# Navigate to the previous working directory (OLDPWD) & print PWD
cd -

# "Navigate" to the current working directory & update OLDPWD to cwd
cd ./

If we are in /home/myusername,  
relative path to /home/myusername/Documents/42/ = "Documents/42/"
```

##### Absolute path
```bash
cd /home/$USER
cd /home/(username)
cd $HOME
cd ~/Documents

# Navigate to user's home
- cd
- cd ~
- cd ~/
- cd --

# Navigate to root
cd /
```

##### ERROR MESSAGE:  
```bash
bash: cd: (path): No such file or directory
```
  
##### Algorithm (from man page)
  
###### No directory operand ('cd')
envp HOME == empty --> error & return  
envp HOME != empty --> go to $HOME  

###### Set curpath to the directory operand
Copy/duplicate the directory operand to curpath  
If curpath does not begin with a <slash> character, set curpath to the string formed by the concatenation of  
		- the value of PWD
		- a <slash> character if the value of PWD did not end with a <slash> character  
		- and curpath.  

###### Canonicalize the curpath value 
a. Dot components and any <slash> characters that separate them from the next component shall be deleted.  

b. For each dot-dot component, if there is a preceding component and it is neither root nor dot-dot, then:
The preceding component, all <slash> characters separating the preceding component from dot-dot, dot-dot, and all <slash> characters separating dot-dot from the following component (if any) shall be deleted.  

c. An implementation may further simplify curpath by removing any trailing <slash> characters that are not also leading <slash> characters, replacing multiple non-leading consecutive <slash> characters with a single <slash>, and replacing three or more leading <slash> characters with a single <slash>.  
If, as a result of this canonicalization, the curpath variable is null, no further steps shall be taken.  
 
###### chdir() called with curpath as the path argument.	
If these actions fail for any reason, the cd utility shallbdisplay an appropriate error message and the remainder of this step shall not be executed.  
		   
The PWD environment variable shall be set to the value that curpath had on entry to the previous step (i.e., before conversion to a relative pathname). 
The OLDPWD environment variable shall also be set to the value of the old working directory (that is the current working directory immediately prior to the call to cd).  
		   
If there is insufficient permission on the new directory, or on any parent of that directory, to determine the current working directory, the value of the PWD environment variable is unspecified.  
