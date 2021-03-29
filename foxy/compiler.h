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
  struct token *next;
  enum token_type type;
  int value, value2;
};

struct token *compile(const char *src);