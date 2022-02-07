#include <iostream>
#include "8080emuCPP.h"
#include "gtuos.h"
#include <string.h>
#include <fstream> 

using namespace std;

#define CYCLE 10

GTUOS::GTUOS(){
  /*
   * The files named below must be in the same directory
   * as source code
   */
  string inputFile = "input.txt";
  string outputFile = "output.txt";  

  /*open files*/
  in.open(inputFile.c_str());
  out.open(outputFile.c_str());  
}

GTUOS::~GTUOS(){
  /*close files*/
  in.close();
  out.close();  
}

/*
  Handle the operating system calls
*/
uint64_t GTUOS::handleCall(const CPU8080 & cpu){
  uint16_t cycles;
  if(in && out){
    switch(cpu.state->a){
    case PRINT_B:
      cycles = sysPrintB(cpu);
      break;
    case PRINT_MEM:
      cycles = sysPrintMem(cpu);    
      break;
    case READ_B:
      cycles = sysReadB(cpu);
      break;
    case READ_MEM:
      cycles = sysReadMem(cpu);
      break;
    case PRINT_STR:
      cycles = sysPrintStr(cpu);
      break;
    case READ_STR:
      cycles = sysReadStr(cpu);
      break;
    default:
      break;
    }
  }else{
    cout << "Files not found" << endl;
  }
  return cycles;
}

/*
  Print the contents of register B
*/
uint64_t GTUOS::sysPrintB(const CPU8080& cpu){
  out << (int)cpu.state->b;
  //printf("%d",(int)cpu.state->b);
  return CYCLE;
}
/*
  Print the content of memory pointed by B and C
  Calculate start address first then get the block
*/
uint64_t GTUOS::sysPrintMem(const CPU8080& cpu){
  uint16_t startAddr;
  startAddr = ((uint16_t)cpu.state->b << 8) | cpu.state->c;
  out << (int)cpu.memory->at(startAddr);
  //printf("%02x\n",(int)cpu.memory->at(startAddr));
  return CYCLE;
}

/*
  Read an integer and put it to B
*/
uint64_t GTUOS::sysReadB(const CPU8080& cpu){
  uint16_t num;
  in >> num;
  cpu.state->b = num;

  return CYCLE;
}

/*
  Read an integer and put it to memory address pointed
  by B and C
*/
uint64_t GTUOS::sysReadMem(const CPU8080& cpu){
    int readVal;
    uint16_t realValue;

    in >> readVal;
    realValue = (uint16_t) readVal;

    if (readVal < 0 || readVal > 65535){
      out << "Error! Bigger than 16 bits not accepted" << endl;
    }else{
      uint8_t leastSign = (uint8_t) realValue;
      uint8_t mostSign = (uint8_t) (realValue >> 8);
      cpu.state->c = leastSign;
      cpu.state->b = mostSign;
    }
    return CYCLE;
}

/*
  Print the null terminated string
  whose start address is stored in B and C
*/
uint64_t GTUOS::sysPrintStr(const CPU8080& cpu){
  uint16_t startAddr;
  startAddr = ((uint16_t)cpu.state->b << 8) | cpu.state->c;
    
  while(cpu.memory->at(startAddr) != (uint8_t) 0){
    out << cpu.memory->at(startAddr);
    startAddr++;
  }
  return CYCLE;
}
/*
  Read string and put it to memory address
  pointed by B and C
*/
uint64_t GTUOS::sysReadStr(const CPU8080& cpu){
  uint16_t startAddr;
  string str;
  in >> str;
  startAddr = (((uint16_t)cpu.state->b) << 8) | cpu.state->c;
  for(int i = 0 ; i < (signed) str.length() ; ++i){
    cpu.memory->at(startAddr) = str[i];
    startAddr++;
  }
  cpu.memory->at(startAddr) = (uint8_t)'\0'; 
  return CYCLE;
}
