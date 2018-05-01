#ifndef _CODE16GCC_H_
#define _CODE16GCC_H_
asm(".code16gcc\n");
#endif

/* needs to stay the first line */
asm("jmp $0, $main");

void printhello()
{
	char hello[] = "Hello\n\r";
	long len = sizeof(hello)/sizeof(char);
	asm("movb $0x0E, %ah;");
	for(long i = 0; i < len - 1; i++)
	{
		asm(
			"int $0x10;"
		:
		:	"a"(hello[i])
		);
	}
}

void readPassowd();

/* space for additional code */
void main(void)
{
	printhello();
	asm("jmp .");
	
}
