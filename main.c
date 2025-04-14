/*
 * datafetch.c
 * Get system data.
 *
 * Written by Michael Ł. (Micha1207) in GNU Emacs.
 * Last edit on: 13 Apr 2025
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Include files with functions
#include "cpu.h"
#include "ram.h"
#include "cpu-temp.h"

#define DATA_CMD "uname -a" // Define command for getting system info. This one is BASH command.
#define OS_FILE  "/etc/os-release"

int main(){ // Main function.
  /* SYS_INFO */
  FILE *cmd = popen(DATA_CMD, "r"); 
  
  char dt[2048];
  char os[64], hnm[64], krn[64], u1[64], u2[64], u3[64], u4[64], u5[64], u6[64], u7[64], u8[64], u9[64], arch[64], type[64];

  if (fgets(dt, sizeof(dt), cmd) == NULL) {
    printf("Cannot get data out of `%s'.\n", DATA_CMD);
    pclose(cmd);
    return 1;
  }
  
  sscanf(dt, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s", os, hnm, krn, u1, u2, u3, u4, u5, u6, u7, u8, u9, arch, type);

  /* OS NAME */
  FILE *osnf = fopen(OS_FILE, "r");
  if (osnf == NULL) {
    printf("%s: No such file or directory. \n", OS_FILE);
  }
  
  char line[128];
  char osnm[64];
  while (fgets(line, sizeof(line), osnf) != NULL) {
    if (strstr(line, "PRETTY_NAME=")) {
      sscanf(line, "PRETTY_NAME=\"%[^\"]\"", osnm);
    }
  }
  
  fclose(osnf);
  
  /* CPU */
  float cpu_usage = cpu_data();  // Run cpu_data function to get CPU usage.
  int   cpu_tempc = cpu_tempf(); // Run cpu_tempf() to get CPU Temp.
  
  /* RAM */
  float ram_total, ram_usage; // Declare RAM Variables.

  ram_data(&ram_total, &ram_usage); // Run ram_data function.

  float ram_free = ram_total - ram_usage; // Calculate free RAM.

  /* Print result */
  printf("SYSTEM\n");
  printf("\tON Name:   %s\n", osnm);
  printf("\tOS Type:   %s\n", type);         // Print OS type.
  printf("\tHostname:  %s\n", hnm);          // Print hostname.
  printf("\tKernel:    %s\n", krn);          // Print kernel name.
  printf("\tArch:      %s\n", arch);         // Print CPU architecture.
  
  printf("CPU\n");
  printf("\tUsage: %.2f%%\n", cpu_usage);    // Print CPU usage.
  printf("\tTemp:  %d\u00B0C\n", cpu_tempc); // Print CPU temp.

  printf("RAM\n"); 
  printf("\tTotal: %.2f GB\n", ram_total);   // Print All RAM space.
  printf("\tUsage: %.2f GB\n", ram_usage);   // Print used RAM space.
  printf("\tFree:  %.2f GB\n", ram_free);    // Print free RAM.
    
  return 0;
}
