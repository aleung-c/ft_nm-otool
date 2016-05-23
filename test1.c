#include <unistd.h>

void print_hello()
{
  write(1, "hello", 6); 
}

int main(void)
{
  print_hello();
  return (0);
}
