#ifndef CODE_H
#define CODE_H

// this file as well as  html\cgi-bin\arduino_code.data won't get updated anymore by git
// in order to not unveil the PW
// reactivate by: git update-index --no-assume-unchanged path/to/file.txt

// defines SMA_PW, nothing else. Should just be:
// #define SMA_PW <pw>
#include "html/cgi-bin/sma_pw.h"

class code {
 public:
  code() {}
  ~code(void) {}
  static const char *get() {   const static char code[]=SMA_PW; return code; }
 };

#endif /* CODE_H */

