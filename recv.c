#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "lib.h"
#include "hamming.h"

#define HOST "127.0.0.1"
#define PORT 10001

int main(int argc,char** argv){
  msg r;
  init(HOST,PORT);

  if (recv_message(&r)<0){
    perror("Receive message");
    return -1;
  }

  int i = 0;
  printf("Got message: \n");
  for (; i < r.len; ++ i)
  {
    r.payload[i] = fix_char(r.payload[i]);
    if (validate(r.payload[i]))
    {
      printf("-%x-\n", r.payload[i]);
    }
    else
    {
      printf("Error: -%x- \n", r.payload[i]);
    }
  }
  printf("\nOriginal message\n");
  
  for (i = 0; i < r.len; i += 2)
  {
    char orig = get_original(r.payload[i], r.payload[i + 1]);
    printf("%c", orig);
  }
  
  
  
  return 0;
}
