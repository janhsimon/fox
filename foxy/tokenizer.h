enum token_type
{
  TOKEN_TYPE_HEAD,
  TOKEN_TYPE_TAIL,
  TOKEN_TYPE_RETURN,
  TOKEN_TYPE_VAR,
  TOKEN_TYPE_CALL
};

struct token
{
  enum token_type type;
  struct token *next;
  int value, value2;
};

struct token *tokenize(const char *src);