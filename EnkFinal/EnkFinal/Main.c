#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <bits.h>

void Write();
void Read();
void Generator(short*, int);

int main()
{
	char input = '\0';
	printf("Press: (E) to encrypt a message\n       (D) to decrypt a message\n");
	do
	{
		input = tolower(_getch());
		if (input == 'e')
		{
			system("cls"); //
			Write();
		}
		else if (input == 'd')
		{
			system("cls"); //
			Read();
		}
		else
		{
			printf("\nInvalid entry!");
			input = 0;
		}
	} while (input == 0);

	return 0;
}

void Write()
{
	clock_t start, end;
	FILE* txtF;
	char imeDat[50] = { 0 };

	char poruka[160] = { 0 };
	int temp = 0;
	char input = '\0', input1 = '\0';

	int keyE = 0, keyN = 0;
	short rnd[1120] = { 0 };

	int asciE[1120] = { 0 };
	int tempBr1 = 0;
	int tempBr2 = 6;

	printf("Do you want to import a message from a text file ? (Y/N)");
	do
	{
		input1 = tolower(_getch());
		if (input1 == 'y')
		{
			system("cls"); //
			printf("Enter exact file location and name: ");
			scanf(" %s", &imeDat);
			txtF = fopen(imeDat, "r");
			while (fgets(poruka, 160, txtF) != NULL);
			fclose(txtF);
		}
		else if (input1 == 'n')
		{
			system("cls"); //
			printf("Enter message to encrypt:\n\n\t");
			fgets(poruka, 160, stdin);
		}
		else
		{
			printf("\nInvalid entry!");
			input1 = 0;
		}
	} while (input1 == 0);

	system("cls"); //
	printf("Press: (E) to enter an existing key\n       (G) to get a new key\n");
	do
	{
		input = tolower(_getch());
		if (input == 'e')
		{
			system("cls"); //
			printf("Please enter your numerical key: ");
			scanf(" %d", &keyE);
			system("cls"); //
			start = clock(); //
			Generator(rnd, keyE);
		}
		else if (input == 'g')
		{
			system("cls"); //
			srand(time(NULL));
			keyN = rand();
			keyN *= keyN;
			start = clock(); //
			Generator(rnd, keyN);
		}
		else
		{
			printf("\nInvalid entry!");
			input = 0;
		}
	} while (input == 0);

	for (int i = 0; i < 160; i++)
	{
		temp = poruka[i]; //Converting char to int, getting the chars ascii number
		for (int i = 1; i < 8; i++)
		{

			tempBr1 = rnd[tempBr2];
			tempBr2--;

			if (temp > 0) //Decimal to binary
			{
				asciE[tempBr1] = temp % 2;
				temp = temp / 2;
			}
			else //Rest of the spots get filled w 0
			{
				asciE[tempBr1] = 0;
			}
		}
		tempBr2 += 14;
	}
	end = clock();

	if (input1 == 'y')
	{
		input1 = '\0';
		do
		{
			printf("Would you like to convert the message from your file to the encrypted one ? (Y/N)");
			input1 = tolower(_getch());
			if (input1 == 'y')
			{
				txtF = fopen(imeDat, "w");
				for (int i = 0; i < 1120; i++)
				{
					fprintf(txtF, "%d", asciE[i]);
				}
				fclose(txtF);
			}
			else if (input1 == 'n'){}
			else
			{
				printf("\nInvalid entry!");
				input1 = 0;
			}
		} while (input1 == 0);
	}

	system("cls"); //
	if (input == 'e')
	{
		printf("Key used to encrypt [%d]\n\n", keyE);
	}
	else if (input == 'g')
	{
		printf("Your new key is [%d]\n\n", keyN);
	}

	for (int i = 0; i < 1120; i++)
	{
		printf("%d", asciE[i]);
	}

	double time_taken = (double)(end - start) / (double)(CLOCKS_PER_SEC);
	printf("\n\nEncryption was completed in [%f sec]\n\n", time_taken);
}

void Read()
{
	clock_t start, end;
	int x2 = 0;

	char poruka2[1121] = { 0 };
	short binarni[1120] = { 0 };
	short binarniSortirani[1120] = { 0 };

	int Dkey = 0;
	short reverter[1120] = { 0 };

	short brojac = 6;
	short temp2 = 1;
	short asciiBr = 0;

	printf("Enter the decryption key: ");
	scanf(" %d", &Dkey);
	Generator(reverter, Dkey);
	system("cls"); //
	printf("Enter message to decrypt:\n");
	fgets(poruka2, 1120, stdin);
	scanf("%[^\n]%*c", poruka2);


	start = clock();
	for (int i = 0; i < 1120; i++)
	{
		poruka2[i] = (int)poruka2[i];
		binarni[i] = (poruka2[i] - 48);
	}

	for (int i = 0; i < 1120; i++)
	{
		binarniSortirani[i] = binarni[reverter[i]];
	}

	system("cls");
	printf("Message:\n\n\t");

	for (int i = 0; i < 1120; i++)
	{
		if (binarniSortirani[i] == 1)
		{
			if (brojac == 0)	// x ^ 0 = 1
			{
				asciiBr += 1;
			}
			else
			{
				for (int i = 1; i <= brojac; i++)
				{
					temp2 *= 2;
				}
				asciiBr += temp2;
				temp2 = 1;
			}
		}
		if ((brojac == 0) && (asciiBr > 7))
		{
			printf("%c", asciiBr);
			asciiBr = 0;
			brojac = 7;
		}
		brojac--;
	}
	end = clock();

	printf("\n\n");
	double time_taken = (double)(end - start) / (double)(CLOCKS_PER_SEC);
	printf("Decryption was completed in [%f sec]\n\n", time_taken);
}

void Generator(short* rnd, int x) 
{
	int i = 0, j = 0;

	srand(x);

	while (i < 1120)
	{
		int r = rand() % 1120;

		for (j = 0; j < i; j++) //Checking for duplicates
		{
			if (rnd[j] == r)
			{
				break;
			}
		}
		if (j == i) //No dupes
		{
			rnd[i++] = r;
		}
	}
}
