## Minishell  
### Builtin function

#### cd with only a relative or absolute path  

Used function  
```c
int chdir(const char *path);
```
##### Relative path
```bash
# Navigate to user's home
- cd
- cd ~
- cd ~/

# Navigate to root
cd /

# Navigate to parent directory
cd ..

# Navigate to the previous directory (OLDPWD)
cd -
```

If we are in /home/myusername,  
relative path to /home/myusername/Documents/42/ = "Documents/42/"

##### Absolute path
```bash
cd /home/$USER
cd /home/(username)
cd $HOME
```

ERROR MESSAGE:  
```bash
bash: cd: (path): No such file or directory
``` 
