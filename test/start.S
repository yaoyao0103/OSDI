.section = ".text"

._global = _start

_start:
	ldr x0, = bss_begin // load bss_begin address to x0
	ldr x1, = bss_end // load bss_end address to x1
	subs x1, x1, x0 // set x1 = bss_end - bss_begin, and set Condition Code Flags(N,Z,C,V)
	b.ls 2f // branch to 2, if bss_end < bss_begin(lower or same, unsigned)

memzero: // clear the bss
	str xzr, [x0], #8 // write xzr(zero regier) to x0(bss_begin), set x0 to new address R1+8(x0 = x0 + 8)
	subs x1, x1, #8 // x1 = bss_end - 8, and set Condition Code Flags(N,Z,C,V)
	b.gt memzero // (greater than, signed) (judge from pervios *s instruction), (when bss_size > 0, branch)
	

2:
	ldr x0, = _start // load _start address to x0
	mov sp, x0 // set stack
	bl main // junp to main.c

1:	
	wfe
	b 1b // branch to 1 back
