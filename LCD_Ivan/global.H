
#ifndef _GLOBAL_H
#define _GLOBAL_H

#include <avr/pgmspace.h>
#include <stdbool.h>

#define lee_byte(address_short) pgm_read_byte_near(address_short)
#define outp(addr, data)	addr = (data)
#define	inp(addr)			(addr)
#define cbi(reg,bit)	reg &= ~(_BV(bit))
#define sbi(reg,bit)	reg |= (_BV(bit))

#define MIN(a,b)			((a<b)?(a):(b))
#define MAX(a,b)			((a>b)?(a):(b))
#define ABS(x)				((x>0)?(x):(-x))
#define MAX_U08             255

#endif
