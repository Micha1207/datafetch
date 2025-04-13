/*
 * datafetch.c
 * Get system data.
 *
 * Written by Michael Ł. (Micha1207) in GNU Emacs.
 * Last edit on: 13 Apr 2025
*/
#include <stdio.h>
#include <stdlib.h>

#define DATA_CMD  "uname -a" // Define command for getting system info. This one is BASH command.

int main(){ // Main function.
  FILE *cmd = popen(DATA_CMD, "r"); 
  
  char dt[2048];
  char os[64], hnm[64], krn[64], u1[64], u2[64], u3[64], u4[64], u5[64], u6[64], u7[64], u8[64], u9[64], arch[64], type[64];

  if (fgets(dt, sizeof(dt), cmd) == NULL) {
    printf("Cannot get data out of `%s'.\n", DATA_CMD);
    pclose(cmd);
    return 1;
  }
  
  sscanf(dt, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s", os, hnm, krn, u1, u2, u3, u4, u5, u6, u7, u8, u9, arch, type);
  
  printf("OS Type:  %s\n", type);
  printf("Hostname: %s\n", hnm);
  printf("Kernel:   %s\n", krn);
  printf("Arch:     %s\n", arch);
    
  return 0;
}
