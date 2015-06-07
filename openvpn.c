#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>


void find_openvpn(char *path)
{
  char *openvpn_paths[4] = {
    "/usr/bin/openvpn",
    "/usr/sbin/openvpn",
    "/usr/local/bin/openvpn",
    "/usr/local/sbin/openvpn"
  };
  for(int i = 0; i < sizeof(openvpn_paths) / sizeof(openvpn_paths); i++)
  {
    if( access(openvpn_paths[i], F_OK) != -1) {
      strcpy(path, openvpn_paths[i]);
      break;
    }
  }
}

bool spawn_openvpn(char openvpn_config[])
{
  char openvpn_path[50];
  find_openvpn(openvpn_path);
  printf("Found OpenVPN path: %s\n", openvpn_path);

  if(openvpn_config == NULL) {
    printf("Please select a config path\n");
    return false;
  } else {
    char *argv[3] = {
      openvpn_path,
      openvpn_config
    };
    printf("Spawning openvpn: %s %s %s\n", argv[0], argv[1], argv[2]);
    execv(openvpn_path, argv);
    return true;
  }
}

void *terminate_openvpn()
{
  //kill(openvpn_pid);
}
