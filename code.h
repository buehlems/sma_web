#ifndef CODE_H
#define CODE_H

class code {
 public:
  code() {}
  ~code(void) {}
  static const char *get() {   const static char code[]="test_code"; return code; }
 };

#endif /* CODE_H */

