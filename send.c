#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include "lib.h"
#include "hamming.h"

#define HOST "127.0.0.1"
#define PORT 10000

int
main(int argc,char** argv)
{
  init(HOST,PORT);
  msg t;


  char message[] = "ABC";
  char *hamming_message = (char*)calloc(sizeof(char), 2 * (strlen(message) + 1));
  
  int len = strlen(message);
  int i = 0, j = 0, k = 0;
  for (; i < len; ++ i)
  {
    for ( k = 0; k < 2; ++ k)
    {
      hamming_message[j] = form_byte(get_bit(message, j * 4),
                                      get_bit(message, j * 4 + 1),
                                      get_bit(message, j * 4 + 2),
                                      get_bit(message, j * 4 + 3));
      j = j + 1;
    } 
  }
  
  
  printf("Sent: \n");
  for (i = 0; i < 2 * (len + 1); ++ i)
  {
    printf("-%x-\n", hamming_message[i]);
  }
  printf("\n");
  memcpy(t.payload, hamming_message, 2 * (len + 1));
  
  t.len = 2 * (strlen(message) + 1);
  send_message(&t);

  free(hamming_message);

  return 0;
}
