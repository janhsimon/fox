#include "tokenizer.h"

#include <stdlib.h> // for malloc
#include <string.h> // for strncmp

#include "error.h"
#include "var.h"

enum state
{
  STATE_PARSING_KEYWORD,
  STATE_PARSING_IDENTIFIER
};

void skip_whitespaces(const char **src)
{
  while (**src == ' ' || **src == '\t')
  {
    ++(*src);
  }
}

void skip_line(const char **src)
{
  while (**src != '\n' && **src != 0)
  {
    ++(*src);
  }

  // move one extra character ahead for the \n
  if (**src == '\n')
  {
    ++(*src);
  }
}

void add_token(enum token_type type, struct token **tail)
{
  struct token *t = malloc(sizeof(struct token));
  t->type = type;
  (*tail)->next = t;
  *tail = t;
}

struct token *tokenize(const char *src)
{
  unsigned int line_counter = 0;
  struct token *head = malloc(sizeof(struct token));
  head->type = TOKEN_TYPE_HEAD;
  struct token *tail = head;

  while (*src != 0)
  {
    set_error_line(++line_counter);
    skip_whitespaces(&src);

    if (*src == '#')
    {
      skip_line(&src);
      continue;
    }
    else if (strncmp(src, "return", 6) == 0)
    {
      add_token(TOKEN_TYPE_RETURN, &tail);
      src += 6;
      skip_whitespaces(&src);

      if (*src < 'a' || *src > 'z')
      {
        error(ERROR_EXPECTED_IDENTIFIER, "var");
        return 0;
      }
      tail->value = (int)(*src);
    }
    else if (strncmp(src, "var", 3) == 0)
    {
      add_token(TOKEN_TYPE_VAR, &tail);
      src += 3;
      skip_whitespaces(&src);

      if (*src < 'a' || *src > 'z')
      {
        error(ERROR_EXPECTED_IDENTIFIER, "var");
        return 0;
      }
      tail->value = (int)(*src);
    }
    else if (*src == '\n')
    {
      skip_line(&src);
      continue;
    }
    else
    {
      if (*src < 'a' || *src > 'z')
      {
        error(ERROR_EXPECTED_IDENTIFIER, src);
        return 0;
      }
      add_token(TOKEN_TYPE_CALL, &tail);
      tail->value = (int)*src;
      src += 1;
      skip_whitespaces(&src);

      if (*src < '0' || *src > '9')
      {
        error(ERROR_EXPECTED_NUMBER, "return");
        return 0;
      }
      tail->value2 = (int)(*src) - '0';
    }

    skip_line(&src);
  }

  add_token(TOKEN_TYPE_TAIL, &tail);
  tail->next = 0;

  return head;
}