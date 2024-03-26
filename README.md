## Minishell  
### Builtin function

#### cd with only a relative or absolute path  

Used function  
```c
int chdir(const char *path);
```
##### Relative path
NAVIGATE TO USER'S HOME  
```bash
- cd
- cd ~
- cd ~/
```
NAVIGATE TO ROOT  
```bash
cd /
```
NAVIGATE TO PARENT DIR  
```bash
cd ..
```
NAVIGATE TO THE PREVIOUR DIR  
```bash
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
