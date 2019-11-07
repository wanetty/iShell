#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <string.h>
#include <unistd.h>
#include <iostream> 
#include <vector>
#include <signal.h>
using namespace std;
//Make BY Wanetty 
int autodetect(){
 //TODO: Nothing
}

int sendCommand(char *command, int fd){
    int error;
    for(int i = 0; i < strlen(command);i++){
       error =  ioctl (fd, TIOCSTI, command+i);
       if (error == -1) return error;
    }
}
int doInteractiveShell(int &fd,int &pid){
    vector<char *> commands(13);
    char *intro= "\n";
    commands[0] = "python -c 'import pty; pty.spawn(\"/bin/bash\")'";
    commands[1] = intro;
    commands[2] = "export TERM=screen-256color";
    commands[3] = intro;
    commands[4] = "echo $TERM";
    commands[5] = intro;
    commands[6] = "stty raw -echo";
    commands[7] = intro;
    commands[8] = "fg";
    commands[9] = intro;
    commands[10] = intro;
    commands[11] = "export TERM=screen";
    commands[10] = intro;

    for (int i = 0; i <commands.size(); ++i){
         usleep(250000);
        int error = sendCommand(commands[i],fd);
        if (error == -1 ) return error;
        if(i  == 3) {
            usleep(250000);
            kill(pid,SIGTSTP);
        }
        
    }
    return 0;
}
int main (int argc, char *argv[]) {
    
    bool auto_detection = true;
    if(argc == 3){
        auto_detection = false;
    }else {
        printf("Usage: ishell <pts> <pid_of_revese> \n");
        exit(-1);
    }
    int fd;
    int pid = atoi(argv[2]);
    if (pid == 0)  printf("ERROR: El pid del proceso debe ser un numero diferente de 0.\n");
    if(auto_detection){
        fd = 0;
        printf("TODO: Crear el autodetector de shell con netcat.");
    }else{
        char *filedes = argv[1];
        fd = open(filedes,O_RDWR);
    }
    int error = doInteractiveShell(fd, pid);
    if (error == 0){
         printf("Shell interactiva correcta");
    }else{
       
        exit(-1);
    }

    exit(0);


}
