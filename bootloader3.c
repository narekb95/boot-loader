#ifndef _CODE16GCC_H_
#define _CODE16GCC_H_
asm(".code16gcc\n");
#endif
asm("jmp $0, $main");

/////////////MAIN PROGRAM/////////////
/*Ausgabe der Zeichenkette "Hello!"
Verdeckte Eingabe eines Strings (maximal 8 Zeichen), Ausgabe von Punkten statt Buchstaben
Ausgabe der verdeckten Eingabe nach Drücken der Enter-Taste
Neustart des Systems, wenn der Eingabe-String leer ist
Nach Ein-/Ausgabe einer nicht leeren Zeichenkette soll anschließend die nächste Zeichenkette eingelesen werde
*/

//char HELLO[] = "Hello!";
//short HELLO_LENGTH = 6;
//char SECRET_CHAR = '.';
//char ENTER = '\r';
char password[8];
//short MAX_PASSWORD_LENGTH = 8;
short passwordLength = 0;

void println(char text[], short maxLength);
void printLetter(char letter);
short getPassword();
void saveChar(char letter);
char readChar();
void reboot();

void main() {
	println("Hello!", 6);
	while (1) {
		getPassword();
		if (passwordLength == 0) reboot();
		println("", 0); 
		println(password, passwordLength);
	}
}

inline void println(char text[], short length) {
	for (short i = 0; i<length; i++) printLetter(text[i]);
	printLetter('\n');
	printLetter('\r');
}

short getPassword() {
	passwordLength = 0;
	while (1) {
		char lastChar = readChar();
		if (lastChar == '\r') break;
		saveChar(lastChar);
	}
	return passwordLength;
}

void saveChar(char letter) {
	if (passwordLength < 8) {
		password[passwordLength] = letter;
		passwordLength++;
		printLetter('.');
	}
}

void printLetter(char letter) {
	asm volatile(
		"movb $0x0e, %%ah;" 	//INT FCODE FOR VIDEO - TELETYPE OUTPUT
		"int  $0x10;"
		::"al"(letter)
	);
}

char readChar() {	
	char lastChar;
	asm volatile (
		"int $0x16"
		: "=a"(lastChar)
		: "a"((short) 0)
	);
	return lastChar;
}

void reboot() {
	println("Reboot!", 7);
	asm("int $0x19;");			//INT FCODE FOR SYSTEM - BOOTSTRAP LOADER
}
