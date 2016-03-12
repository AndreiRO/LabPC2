#ifndef HAMMING_H_
#define HAMMING_H_


/* solomon-red */

int
get_bit(char *bitvector, int index)
{
    int byte = index / 8;
    int pos  = index % 8;
    
    return (bitvector[byte] & (1 << pos)) >> pos;
}

char
form_byte(char bit0,
          char bit1,
          char bit2,
          char bit3)
{

    char message = 0;
    
    message = message | ((bit0 ^ bit1 ^ bit3) << 0);    
    message = message | ((bit0 ^ bit2 ^ bit3) << 1);    
    message = message | (bit0 << 2);    
    message = message | ((bit1 ^ bit2 ^ bit3) << 3);    
    message = message | (bit1 << 4);    
    message = message | (bit2 << 5);    
    message = message | (bit3 << 6);
    
    return message;
}


int
validate(char c)
{
  char d0 = (c & (1 << 2)) >> 2;
  char d1 = (c & (1 << 4)) >> 4;
  char d2 = (c & (1 << 5)) >> 5;
  char d3 = (c & (1 << 6)) >> 6;
  
  char p0 = d0 ^ d1 ^ d3 ^ (c & (1 << 0));
  char p1 = d0 ^ d2 ^ d3 ^ ((c & (1 << 1)) >> 1);
  char p2 = d1 ^ d2 ^ d3 ^ ((c & (1 << 3)) >> 3);
  
  if (p0 == 0 && p1 == 0 && p2 == 0) return 1;
  return 0;
}

char
get_original(char o1, char o2)
{
  char d0 = (o1 & (1 << 2)) >> 2;
  char d1 = (o1 & (1 << 4)) >> 4;
  char d2 = (o1 & (1 << 5)) >> 5;
  char d3 = (o1 & (1 << 6)) >> 6;
  
  char d4 = (o2 & (1 << 2)) >> 2;
  char d5 = (o2 & (1 << 4)) >> 4;
  char d6 = (o2 & (1 << 5)) >> 5;
  char d7 = (o2 & (1 << 6)) >> 6;
  
  char m = 0;
  m = m | d0;
  m = m | (d1 << 1);
  m = m | (d2 << 2);
  m = m | (d3 << 3);
  m = m | (d4 << 4);
  m = m | (d5 << 5);
  m = m | (d6 << 6);
  m = m | (d7 << 7);
  
  return m;
}

char
fix_char(char c)
{
  if (validate(c)) return c;
  
  printf("%x->", c);
  char d0 = (c & (1 << 2)) >> 2;
  char d1 = (c & (1 << 4)) >> 4;
  char d2 = (c & (1 << 5)) >> 5;
  char d3 = (c & (1 << 6)) >> 6;

  char p0 = (c & (1 << 0)) >> 0;
  char p1 = (c & (1 << 1)) >> 1;
  char p2 = (c & (1 << 3)) >> 3;
  
  char s0 = p0 ^ d0 ^ d1 ^ d3;
  char s1 = p1 ^ d0 ^ d2 ^ d3;
  char s2 = p2 ^ d1 ^ d2 ^ d3;
  
  if (s0 == 1 && s1 == 0 && s2 == 0)
  {
    p0 = p0 ^ 1;
  }
  else if (s0 == 0 && s1 == 1 && s2 == 0)
  {
    p1 = p1 ^ 1;
  }
  else if (s0 == 0 && s1 == 0 && s2 == 1)
  {
    p2 = p2 ^ 1;
  }
  else if (s0 == 1 && s1 == 1 && s2 == 0)
  {
    d0 = d0 ^ 1;
  }
  else if (s0 == 1 && s1 == 0 && s2 == 1)
  {
    d1 = d1 ^ 1;
  }
  else if (s0 == 0 && s1 == 1 && s2 == 1)
  {
    d2 = d2 ^ 1;
  }
  else if (s0 == 1 && s1 == 1 && s2 == 1)
  {
    d3 = d3 ^ 1;
  }
  
  char message = 0;
    
  message = message | (p0);    
  message = message | (p1 << 1);    
  message = message | (d0 << 2);    
  message = message | (p2 << 3);    
  message = message | (d1 << 4);    
  message = message | (d2 << 5);    
  message = message | (d3 << 6);
  printf("%x\n", message);
  
  return message;
}


#endif