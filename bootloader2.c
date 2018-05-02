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

char HELLO[] = "Hello!";
int HELLO_LENGTH = 6;
char SECRET_CHAR = '.';
char ENTER = '\r';
char password[8];
int MAX_PASSWORD_LENGTH = 8;
int passwordLength = 0;

void println(char text[], int maxLength);
void printLetter(char letter);
int getPassword();
void saveChar(char letter);
char readChar();
void reboot();

void main() {
	println(HELLO, HELLO_LENGTH);
	while (getPassword()) {
		println(password, passwordLength);
	}
	reboot();
}

void println(char text[], int length) {
	for (int i = 0; i<length; i++) {
		printLetter(text[i]);
	}
	printLetter('\n');
	printLetter('\r');
}

int getPassword() {
	passwordLength = 0;
	while (1) {
		char lastChar = readChar();
		if (lastChar == ENTER) break;
		saveChar(lastChar);
	}
	println("", 0);
	return passwordLength;
}

void saveChar(char letter) {
	if (passwordLength < MAX_PASSWORD_LENGTH) {
		password[passwordLength] = letter;
		passwordLength++;
		printLetter(SECRET_CHAR);
	}
}

void printLetter(char letter) {
	asm(
		"movb $0x0e, %%ah;" 	//INT FCODE FOR VIDEO - TELETYPE OUTPUT
		"int  $0x10;"
		:
		:"al"(letter)
	);
}

char readChar() {
	printLetter((char)0x00); //SPACE
	printLetter((char)0x08); //BACKSPACE
	char lastChar;
	asm(
		"movb $0x0, %%ah;"		//INT FCODE FOR KEYBOARD - GET KEYSTROKE
        "int $0x16"
		:"=al"(lastChar)
		:
	);
	return lastChar;
}

void reboot() {
	asm("int $0x19;");			//INT FCODE FOR SYSTEM - BOOTSTRAP LOADER
}
