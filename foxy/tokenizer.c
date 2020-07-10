#include "tokenizer.h"

#include <stdlib.h> // for malloc
#include <string.h> // for strncmp

#include "error.h"
#include "var.h"

enum state {
  STATE_PARSING_KEYWORD,
  STATE_PARSING_IDENTIFIER
};

void skip_whitespaces(const char** src)
{
  while (**src == ' ' || **src == '\t') {
    ++(*src);
  }
}

void skip_line(const char** src)
{
  while (**src != '\n' && **src != 0) {
    ++(*src);
  }

  // move one extra character ahead for the \n
  if (**src == '\n') {
    ++(*src);
  }
}

void add_token(enum token_type type, struct token** tail)
{
  struct token* t = malloc(sizeof(struct token));
  t->type = type;
  (*tail)->next = t;
  *tail = t;
}

struct token* tokenize(const char* filename, const char* src)
{
  unsigned int line_counter = 0;
  struct token* head = malloc(sizeof(struct token));
  head->type = TOKEN_TYPE_HEAD;
  struct token* tail = head;

  while (*src != 0) {
    set_error_line(++line_counter);
    skip_whitespaces(&src);

    if (*src == '#') {
      skip_line(&src);
      continue;
    }
    else if (strncmp(src, "return", 6) == 0) {
      add_token(TOKEN_TYPE_RETURN, &tail);
      src += 6;
      skip_whitespaces(&src);

      if (*src < 'a' || *src > 'z') {
        error(ERROR_EXPECTED_IDENTIFIER, "var");
        return 0;
      }
      tail->value = (int)(*src);
    }
    else if (strncmp(src, "var", 3) == 0) {
      add_token(TOKEN_TYPE_VAR, &tail);
      src += 3;
      skip_whitespaces(&src);

      if (*src < 'a' || *src > 'z') {
        error(ERROR_EXPECTED_IDENTIFIER, "var");
        return 0;
      }
      tail->value = (int)(*src);
    }
    else if (*src == '\n') {
      skip_line(&src);
      continue;
    }
    else {
      if (*src < 'a' || *src > 'z') {
        error(ERROR_EXPECTED_IDENTIFIER, src);
        return 0;
      }
      add_token(TOKEN_TYPE_CALL, &tail);
      tail->value = (int)*src;
      src += 1;
      skip_whitespaces(&src);

      if (*src < '0' || *src > '9') {
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

  /* const char* keyword = "keep";
   enum state current_state = STATE_PARSING_KEYWORD;
   struct token* prev = malloc(sizeof(struct token));
   prev->type = TOKEN_TYPE_ROOT;
   prev->next = 0;

   int keyword_char_counter = 0;
   while (*src != 0) {
     const char c = *src;

     switch (current_state) {
     case STATE_PARSING_KEYWORD:
       if (c == keyword[keyword_char_counter]) {
         ++keyword_char_counter;
         if (keyword_char_counter > 4) {
           struct token* next = malloc(sizeof(struct token));
           next->type = TOKEN_TYPE_REMEMBER;
           prev->next = next;
           prev = next;
         }
       }
       else {
         current_state = STATE_PARSING_IDENTIFIER;
       }
       break;
     default:
     }
   }

   prev->next = 0;*/

   //if (c == '')


 /* unsigned int lineCounter = 0;
  const char* begin = src;


  set_error_line(0);

  while (*src != 0)
  {
    if (*src == ' ')
    {
      *src = 0;

      if (strcmp(begin, "remember") == 0) {
        begin = src + 1;
      }
      else
      {
        error(ERROR_UNKNOWN_IDENTIFIER, begin);
        return 0;
      }
    }
    else if (*src == '\n')
    {
      set_error_line(++lineCounter);
      begin = src + 1;
    }

    ++src;
  }

  return root;*/
}
