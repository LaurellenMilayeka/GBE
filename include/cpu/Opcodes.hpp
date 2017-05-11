#ifndef __OPCODES_HPP__
#define __OPCODES_HPP__

#include <stdint.h>

namespace CPU {
  class Z80;
};

typedef enum E_FLAGS_STATE {
  CLEAR, /* Clear the flag to 0 */
  SET, /* Set the flag to 1 */
  INST_SET, /* Set the flag depending on instruction result */
  UNCHANGED /* The flag remains unchanged */
} FLAGS_STATE;

typedef struct s_defineflags {

  FLAGS_STATE  	z;
  FLAGS_STATE	n;
  FLAGS_STATE	h;
  FLAGS_STATE	c;
} t_set_flag_state;

typedef struct s_opcodes {

  uint8_t		code;
  uint8_t		nbrCycles;
  //FLAGS		flagSet[6];
  t_set_flag_state	flagsState;
  void			(*fptr)(CPU::Z80*);
} t_op;

extern t_op	opcodes[];

#endif
