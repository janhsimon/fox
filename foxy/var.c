#include "var.h"

int vars[26];

void write_var(char name, int value)
{
  vars[name - 'a'] = value;
}

int read_var(char name)
{
  return vars[name - 'a'];
}