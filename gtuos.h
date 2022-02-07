#ifndef H_GTUOS
#define H_GTUOS

#include "8080emuCPP.h"
#include <fstream>
#include <iostream>

enum SYS_CALL{
  PRINT_B = 0x04,
  PRINT_MEM = 0x03,
  READ_B = 0x07,
  READ_MEM = 0x02,
  PRINT_STR = 0x01,
  READ_STR = 0x08
};

using namespace std;

class GTUOS{  
 public:
  /*
   * Constructor and destructor are written
   * for file open,close processing
   */
  GTUOS();
  ~GTUOS();
  uint64_t handleCall(const CPU8080 & cpu);

  uint64_t sysPrintB(const CPU8080 & cpu);
  uint64_t sysPrintMem(const CPU8080 & cpu);
  uint64_t sysReadB(const CPU8080 & cpu);
  uint64_t sysReadMem(const CPU8080 & cpu);
  uint64_t sysPrintStr(const CPU8080 & cpu);
  uint64_t sysReadStr(const CPU8080 & cpu);

 private:
  /*These are used for file processing*/
  ifstream in;
  ofstream out;
};

#endif
