#ifndef _CODE16GCC_H_
#define _CODE16GCC_H_
asm(".code16gcc\n");
#endif
asm("jmp $0, $main");

/////////////MAIN PROGRAM/////////////
/*
Ausgabe der Zeichenkette "Hello!"
Verdeckte Eingabe eines Strings (maximal 8 Zeichen), Ausgabe von Punkten statt Buchstaben
Ausgabe der verdeckten Eingabe nach Drücken der Enter-Taste
Neustart des Systems, wenn der Eingabe-String leer ist
Nach Ein-/Ausgabe einer nicht leeren Zeichenkette soll anschließend die nächste Zeichenkette eingelesen werde
*/

char HELLO[] = "Hello!";
char SECRET_CHAR = '*';
int MAX_PASSWORD_LENGTH = 8;
char password[] = "password";
int passwordLength = 0;

void println(char text[], int maxLength);
void printLetter(char letter);
void getPassword();
char readChar();
int playingWithPasswords();
void saveLetter(char letter);
void reboot();

void main() {
	println(HELLO, 6);
	while (playingWithPasswords()) {
		println(password, passwordLength);
	}
	reboot();
}

int playingWithPasswords() {
	getPassword();
	return passwordLength;
}

void println(char text[], int length) {
	for (int i = 0; i<length; i++) {
		printLetter(text[i]);
	}
	printLetter('\n');
	printLetter('\r');
}

void getPassword() {
	passwordLength = 0;
	
	while (1) {
		char lastChar = readChar();
		if (lastChar != '\r') {
			saveLetter(lastChar);
		} else {
			break;
		}
	}
	printLetter('\n');
	printLetter('\r');
}

void saveLetter(char letter) {
	if (passwordLength < MAX_PASSWORD_LENGTH) {
		password[passwordLength] = letter;
		printLetter(SECRET_CHAR);
		passwordLength++;
	}
}

void printLetter(char letter) {
	asm(
		"movb $0x0e, %%ah;" //INTERRUPT CODE FOR OUTPUT
		"int  $0x10"::"a"(letter));
}

char readChar() {
	printLetter((char)0x00); //SPACE
	printLetter((char)0x08); //BACKSPACE
	char lastChar;
	asm(
		"movb $0x0, %%ah;" //INTERRUPT CODE FOR READ
        "int $0x16"
		:"=al"(lastChar)
		:
	);
	
	return lastChar;
}

void reboot() {
	asm("int $0x19;");
}
