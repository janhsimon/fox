int vars[26];

void write_var(char name, int value)
{
  vars[name - 'a'] = value;
}

int read_var(char name)
{
  return vars[name - 'a'];
}

int find_var(char name)
{
  if (vars[name - 'a'] == 11)
  {
    return 0;
  }
  return -1;
}