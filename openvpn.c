#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

char openvpn_path[100];

void which_openvpn()
{
  FILE *in;
  extern FILE *popen();

  if(!(in = popen("which openvpn", "r"))){
    exit(1);
  }

  while(fgets(openvpn_path, sizeof(openvpn_path), in)!=NULL){
    printf("%s", openvpn_path);
  }
  pclose(in);
}

bool spawn_openvpn(char openvpn_config[])
{
  if(openvpn_config == NULL) {
    printf("please select a config path\n");
    return false;
  }
  else {
    which_openvpn();
    printf("spawning openvpn: %s\n", openvpn_path);
    char *argv[6] = {
      NULL,
      "--config",
      NULL
    };
    argv[0] = openvpn_path;
    argv[2] = openvpn_config;
    printf("argument: %s\n", argv[1]);
    execv("/usr/local/sbin/openvpn", argv);
    return true;
  }
}

void *terminate_openvpn()
{
  //kill(openvpn_pid);
}
