#include "_lib.h"

int _str_len(char *str)
{
  int len;
  
  if (!str) return (-1);
  len = 0;
  while (*str++) len++;
  return (len);
}

int _print_string(char *str, int fd)
{
  int len;

  if (!str) return (-1);
  len = _str_len(str);
  len = write(fd, str, len);
  return (len);
}

int _print_error(char *str)
{
  return (_print_string(str, 2));
}

int _print_message(char *str)
{
  return (_print_string(str, 1));
}
