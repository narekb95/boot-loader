#ifndef _CODE16GCC_H_
#define _CODE16GCC_H_
asm(".code16gcc\n");
#endif

/* needs to stay the first line */
asm("jmp $0, $main");

void print(char str[], int len)
{
	/*asm(
		"add $48, %%al;"
		"movb $0x0E, %%ah;"
		"int $0x10;"
	:
	:"a"(len)
	);*/
	asm("movb $0x0E, %ah;");
	for(long i = 0; i < len; i++)
	{
		asm(
			"int $0x10;"
		:
		:	"a"(str[i])
		);
	}
	asm(
		"mov $10, %al;"
		"movb $0x0E, %ah;"
		"int $0x10;"
		"mov $13, %al;"
		"movb $0x0E, %ah;"
		"int $0x10;"
	);
	return;
}


//int readPassowrd
//int 0 password read
//int 1 password empty
void readPassword()
{
	char in[8];
	int l;
	asm(
		"mov $0, %%si;"
	"read:"
		"movb $0x0, %%ah;"
		"int $0x16;"

		"cmp $13, %%al;"
		"je end;"
		"cmp $8, %%si;"
		"je read;"
		

		"mov %%ax, (%%bx, %%si);"
		"inc %%si;"
		"mov $46, %%al;"
		"movb $0x0E, %%ah;"
		"int $0x10;"
		"jmp read;"
		"int $0x10;"
		"jmp read;"
	"end:"
		//"push %%si;"
		//"push %%bx;"
		//"call %P0;" 
		
		: "=S"(l)
		: "b"(in), "r"(print)
	);
	if(l == 0)
	{
		asm("int $0x19;");
	}
	else
	{
		asm(
		"mov $10, %al;"
		"movb $0x0E, %ah;"
		"int $0x10;"
		"mov $13, %al;"
		"movb $0x0E, %ah;"
		"int $0x10;"
		);
	}
	print(in, l);
}

/* space for additional code */
void main(void)
{
	print("Hello", 5);
	while(1)
	{
		readPassword();
	}
	asm("jmp .");
	
}
