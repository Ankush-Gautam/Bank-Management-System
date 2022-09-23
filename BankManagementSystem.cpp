/******************************************************************************************************************
 *  TITLE       :   Bank Management System                                                                        *
 *  DESCRIPTION :   This program helps to manage bank transactions and activity in a bank.                        *
 *  DEVELOPER   :   Ankush Gautam                                                                                 *
 ******************************************************************************************************************/

#include "Colors.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <conio.h>
using namespace std;

/****  USER-DEFINED FUNCS  ****/
void HEADER(const char*);
void line(char);
void pause();
int numOfRecords();
char* maskPassword(char*);

inline void dangerMessage(const char*);
inline void successMessage(const char*);

/**** VALIDATORS ****/
bool isValidName(char*);
bool isValidAccountNo(int);
bool isValidAmount(double);
bool isValidPhoneNo(char*);
bool isValidCitizenship(char*);

/****  REGISTRATION FUNCS  ****/
void setupPage();
void validateUser();
void login(char*, char*);

/****  MENU ITEMS  ****/
void menu();
void createAccount();
void checkAccount();
void withdraw();
void deposit();
void transfer();
void closeAccount();
void listAccounts();
void sortAccounts();
void about();

/****  CLASS DECLARATION  ****/
class Bank
{
private:
	int accountNo;
	char firstName[16];
	char lastName[16];
	char phone[11];
	char birthdate[11];
	char email[33];
	char address[33];
	char citizenshipNo[24];
	long double balance;

public:
	// CONSTRUCTOR
	Bank()
	{
		accountNo = 0;
		strcpy_s(firstName, "N/A");
		strcpy_s(lastName, "N/A");
		strcpy_s(phone, "N/A");
		strcpy_s(birthdate, "N/A");
		strcpy_s(email, "N/A");
		strcpy_s(address, "N/A");
		strcpy_s(citizenshipNo, "N/A");
		balance = 0.0;
	}

	//	GETTERS
	int getAccountNo()
	{
		return accountNo;
	}

	char* getCitizenshipNo()
	{
		return citizenshipNo;
	}

	long double getBalance()
	{
		return balance;
	}

	// METHODS
	void displayHeadings();
	void displayRecord();
	void addDeposit(double amt);
	void addWithdraw(double amt);
	void inputDetails();

	// friend funcs
	friend void checkAccount();
	friend void sortAccounts();
};

/****  ---------- BANK METHODS ---------------  ****/
void Bank::displayHeadings()
{
	char ch = char(254);

	line(ch);
	black();
	cout << '\t' << left << setw(13) << "A/C NO." << setw(20) << "LASTNAME" << setw(20) << "FIRSTNAME" << setw(19) << "BIRTHDATE"
	     << setw(25) << "CITIZENSHIP NO." << setw(12) << "PHONE NO." << right << setw(20) << "BALANCE (Rs)";
	line(ch);
}

void Bank::displayRecord()
{
	cout << '\t' << left << setw(13) << accountNo << setw(20) << strupr(lastName) << setw(20) << strupr(firstName) << setw(19) << birthdate
	     << setw(25) << citizenshipNo << setw(12) << phone << right << setw(20) << fixed << setprecision(2) << balance << endl; // fixed for no scientific.
}

// deposited money
void Bank::addDeposit(double amt)
{
	balance += amt;
}

void Bank::addWithdraw(double amt)
{
	balance -= amt;
}

void Bank::inputDetails()
{
	successMessage("\tENTER CORRECT DETAILS BELOW CAREFULLY!\n");

	do
	{
		cout << "\n\tACCOUNT NO. : ";
		cin.clear();
		cin >> accountNo;
	}
	while(!isValidAccountNo(accountNo));


	cout << "\n\tFIRST NAME : ";
	cin.clear();
	cin >> firstName;

	cout << "\n\t(FAMILY)LAST NAME : ";
	cin.clear();
	cin >> lastName;

	cout << "\n\tBIRTH DATE(YYYY-MM-DD) : ";
	cin.ignore();
	cin.clear();
	cin.getline(birthdate, sizeof(birthdate));

	do
	{
		cout << "\n\tCITIZENSHIP NO. : ";
		cin.clear();
		cin.getline(citizenshipNo, sizeof(citizenshipNo));
	}
	while(!isValidCitizenship(citizenshipNo));


	do
	{
		cout << "\n\tPHONE NO. : +977 ";
		cin.clear();
		cin.getline(phone, sizeof(phone));
	}
	while (!isValidPhoneNo(phone));

	cout << "\n\tEMAIL ADDRESS : ";
	cin.clear();
	cin.getline(email, sizeof(email));

	cout << "\n\tPERMANENT ADDRESS : ";
	cin.clear();
	cin.getline(address, sizeof(address));

	do
	{
		cout << "\n\tINITIAL DEPOSIT : Rs.";
		cin.clear();
		cin >> balance;
	}
	while (!isValidAmount(balance));
}

/**** ----------- Registration class -------------- ****/
class Registration
{
private:
	char bankname[32];
	char bankaddress[32];
	char telephone[10];
	char username[10];
	char password[10];

public:
	char* getUsername()
	{
		return username;
	}

	char* getPassword()
	{
		return password;
	}

	void setup()
	{
		char confirmpw[10];

		cout << "\tBANK NAME : ";
		cin.getline(bankname, sizeof(bankname));

		cout << "\n\tBANK ADDRESS : ";
		cin.getline(bankaddress, sizeof(bankaddress));

		cout << "\n\tTELEPHONE NO. : ";
		cin.getline(telephone, sizeof(telephone));

		successMessage("\n\n\tCREATE A LOGIN ACCOUNT\n");

		cout << "\n\tCREATE A USERNAME : ";
		cin.getline(username, sizeof(username));

pw_again:
		cout << "\n\tCREATE A PASSWORD : ";
		strcpy_s(password, maskPassword(password));

		cout << "\n\n\tCONFIRM THE PASSWORD : ";
		strcpy_s(confirmpw, maskPassword(confirmpw));

		if (!(strcmp(password, confirmpw) == 0))
		{
			dangerMessage("\n\t[SORRY! PASSWORD DOESN'T MATCH.]\n");
			goto pw_again;
		}
	}
};

/****  GLOBAL DECLARATIONS  ****/
const char* filename = "bankdata.dat";
fstream file;
Bank bank;

/* ========================================
				MAIN DRIVER
	 ======================================== */
int main()
{
	system("title BANK MANAGEMENT SYSTEM");
	system("color f8");

	validateUser();

	return 0;
}

void setupPage()
{
	HEADER("SETUP PAGE");

	Registration reg;
	fstream setupfile;
	setupfile.open("setupfile.dat", ios::out | ios::binary);

	successMessage("\tPLEASE TAKE A MOMENT TO SETUP. YOU ONLY HAVE TO DO THIS ONCE.\n\n");

	reg.setup();
	setupfile.write((char*)&reg, sizeof(reg));
	setupfile.close();

	successMessage("\n\n\n\tSETUP SUCCESSFULL! HAVE A GREAT DAY.");
	pause();

	return menu();
}

void login(char* username, char* password)
{
	HEADER("LOGIN PAGE");

	char user[10], pw[10];

	cout << "\n\tENTER USERNAME : ";
	cin.getline(user, sizeof(user));

	cout << "\n\tENTER PASSWORD : ";
	strcpy_s(pw, maskPassword(pw));

	if (strcmp(user, username) == 0 && strcmp(pw, password) == 0)
	{
		return menu();
	}
	else
	{
		dangerMessage("\n\n\tINVALID USERNAME OR PASSWORD! PLEASE TRY AGAIN.");
		pause();
		return login(username, password);
	}
}

void validateUser()
{
	fstream setupfile;
	setupfile.open("setupfile.dat", ios::in | ios::binary);

	setupfile.seekg(0, ios::end);
	int filesize = setupfile.tellg(); //finding the size of file to see if the file has data

	if (!setupfile.is_open() || filesize <= 0)
	{
		return setupPage();
	}

	Registration reg;

	setupfile.seekg(0, ios::beg);
	setupfile.read((char*)&reg, sizeof(reg));
	setupfile.close();

	return login(reg.getUsername(), reg.getPassword());
}

/* ========================================
				MENU ITEMS
	 ======================================== */
void menu()
{
	int choice;

	do
	{
		HEADER("BANK MANAGEMENT SYSTEM");

		cout << "\tWELCOME TO THE MAIN MENU\n";

		cout << "\n\n\t1. CREATE NEW ACCOUNT";
		cout << "\n\n\t2. CHECK ACCOUNT BALANCE";
		cout << "\n\n\t3. DEPOSIT MONEY";
		cout << "\n\n\t4. WITHDRAW MONEY";
		cout << "\n\n\t5. TRANSFER MONEY";
		cout << "\n\n\t6. CLOSE AN ACCOUNT";
		cout << "\n\n\t7. LIST ALL ACCOUNTS";
		cout << "\n\n\t8. SORT ACCOUNTS";
		cout << "\n\n\t9. ABOUT";
		cout << "\n\n\t0. EXIT";

		green();
		cout << "\n\n\n\tENTER YOUR CHOICE :\n\t>> ";
		gray();
		cin.clear();
		cin >> choice;

		switch (choice)
		{
			case 1:
				createAccount();
				break;

			case 2:
				checkAccount();
				break;

			case 3:
				deposit();
				break;

			case 4:
				withdraw();
				break;

			case 5:
				transfer();
				break;

			case 6:
				closeAccount();
				break;

			case 7:
				listAccounts();
				break;

			case 8:
				sortAccounts();
				break;

			case 9:
				about();
				break;

			case 0:
				system("cls");
				successMessage("\n\n\n\n\tTHANK YOU FOR YOUR VISIT.\n");
				pause();
				break;
		}
	}
	while (choice != 0);
}

/* -------- 1. CREATE NEW ACCOUNT ------------------------------------------------------- */
void createAccount()
{

	HEADER("CREATING A NEW ACCOUNT");

	file.open(filename, ios::app | ios::binary);
	// if file cannot be opened
	if (!file)
	{
		red();
		cout << "\n\tERROR: FILE CANNOT BE OPENED!" << endl;
		gray();
		pause();
		return;
	}

	bank.inputDetails();
	file.write((char*)&bank, sizeof(bank));
	file.close();

	successMessage("\n\tNEW ACCOUNT SUCCESSFULLY CREATED.");

	// asking if user want to create another a/c
	line('.');
	char yesno;
	cout << "\tDo You Want To CREATE Another Account?(Press 'y' for Yes)\n\t>> ";
	cin >> yesno;

	if (yesno == 'y' || yesno == 'Y')
		return createAccount();
}

/* -------- 2. CHECK ACCOUNT ------------------------------------------------------- */
void checkAccount()
{
	HEADER("CHECKING AN ACCOUNT");

	file.open(filename, ios::in | ios::binary);

	if (!file || (numOfRecords() <= 0))
	{
		dangerMessage("\tNO DATA FOUND! ADD ACCOUNTS FIRST.");
		pause();
		file.close();
		return;
	}

	int accountNum;
	int found = 0;

	cout << "\tENTER THE A/C NO. YOU WANT TO CHECK : ";
	cin >> accountNum;

	while (file.read((char*)&bank, sizeof(bank)))
	{
		if (accountNum == bank.getAccountNo())
		{
			found = 1;

			HEADER("CHECKING ACCOUNT");

			black();
			cout << "\n\tACCOUNT NO. \t\t: \t";
			green();
			cout << bank.accountNo;

            black();
			cout << "\n\n\tFIRST NAME \t\t: \t";
			green();
			cout << strupr(bank.firstName);


			black();
			cout << "\n\n\tLAST NAME \t\t: \t";
			green();
			cout << strupr(bank.lastName);

			black();
			cout << "\n\n\tBIRTHDATE (YYYY-MM-DD) \t: \t";
			green();
			cout << bank.birthdate;

			black();
			cout << "\n\n\tCITIZENSHIP NO. \t: \t";
			green();
			cout << bank.citizenshipNo;

			black();
			cout << "\n\n\tPHONE NO. \t\t: \t";
			green();
			cout << bank.phone;

			black();
			cout << "\n\n\tEMAIL ADDRESS \t\t: \t";
			green();
			cout << strlwr(bank.email);

			black();
			cout << "\n\n\tPERMANENT ADDRESS \t: \t";
			green();
			cout << strupr(bank.address);

			black();
			cout << "\n\n\tBANK BALANCE \t\t: \t";
			green();
			cout << "Rs."<< fixed << setprecision(2) << bank.balance;

			black();
			// just printing some funny advice for users
			cout << "\n\n\n\tLook At That Bank Balance...";

			if(bank.balance <= 999999) // if less than 10lakhs
			{
				cout << "\n\tThe safest way to double your money is to fold it over and put it in your pocket.\n";
			}
			else if(bank.balance <= 9999999) //if less than 1crore
			{
				cout << "\n\tMake sure to save for the future and keep making money! \n";
			}
			else //if more than a crore
			{
				cout << "\n\tWanna host who wants to be a Millionaire?\n";
			}

			break;
		}
	}

	if (!found)
	{
		dangerMessage("\tNO MATCH FOUND!");
	}

	file.close();

	// if user wants to search again
	line('.');
	char yesno;
	cout << "\tDo You Want To Check Again?(Press 'y' for Yes)\n\t>> ";
	cin >> yesno;

	if (yesno == 'y' || yesno == 'Y')
		return checkAccount();
}

/* -------- 3. DEPOSIT MONEY ------------------------------------------------------- */
void deposit()
{
	HEADER("DEPOSIT MONEY INTO AN ACCOUNT");

	file.open(filename, ios::binary | ios::in | ios::out);

	if (!file || (numOfRecords() <= 0))
	{
		dangerMessage("\tNO DATA FOUND! ADD ACCOUNTS FIRST.");
		pause();
		file.close();
		return;
	}

	bool found = false;
	int accNo;
	double depositAmt;

	// asking the account no to add amount
	cout << "\tENTER THE A/C NO. YOU WANT TO DEPOSIT IN : ";
	cin >> accNo;

	// searching for the records and copying the data in newfile
	while (file.read((char*)&bank, sizeof(bank)))
	{
		if (accNo == bank.getAccountNo())
		{
			found = true;

			// displaying the detailed info of entered accountNO
			cout << endl;
			bank.displayHeadings();
			bank.displayRecord();

			do
			{
				green();
				cout << "\n\n\tENTER THE AMOUNT YOU WANT TO DEPOSIT : Rs.";
				gray();
				cin >> depositAmt;
			}
			while (!isValidAmount(depositAmt));

			bank.addDeposit(depositAmt);

			// updating the money in the file
			int pos = (-1) * static_cast<int>(sizeof(bank));
			file.seekp(pos, ios::cur);
			file.write((char*)&bank, sizeof(bank));
			break;
		}
	}

	file.close();

	if (found)
		successMessage("\n\tAMOUNT SUCCESSFULLY DEPOSITED.\n");
	else
		dangerMessage("\tNO MATCH FOUND!");

	line('.');
	char yesno;
	cout << "\tDo You Want To Deposit Again?(Press 'y' for Yes)\n\t>> ";
	cin >> yesno;

	if (yesno == 'y' || yesno == 'Y')
		return deposit();
}

/* -------- 4. WITHDRAW MONEY ------------------------------------------------------- */
void withdraw()
{
	HEADER("WITHDRAW MONEY FROM AN ACCOUNT");

	file.open(filename, ios::binary | ios::in | ios::out);

	if (!file || (numOfRecords() <= 0))
	{
		dangerMessage("\tNO DATA FOUND! ADD ACCOUNTS FIRST.");
		pause();
		file.close();
		return;
	}

	bool found = false;
	int accNo;
	double withdrawAmt;

	// asking the account no to add amount
	cout << "\tENTER THE A/C NO. YOU WANT TO WITHDRAW FROM : ";
	cin >> accNo;

	// searching for the records and copying the data in newfile
	while (file.read((char*)&bank, sizeof(bank)))
	{
		if (accNo == bank.getAccountNo())
		{
			found = true;

			// displaying the detailed info of entered accountNO
			cout << endl;
			bank.displayHeadings();
			bank.displayRecord();

			do
			{
				green();
				cout << "\n\n\tENTER THE AMOUNT YOU WANT TO WITHDRAW : Rs.";
				gray();
				cin >> withdrawAmt;
			}
			while (!isValidAmount(withdrawAmt));

			if (bank.getBalance() < withdrawAmt)
			{
				dangerMessage("\n\tOOPS! INSUFFICIENT BALANCE.");
				pause();
				file.close();
				return;
			}
			else
			{
				bank.addWithdraw(withdrawAmt);
			}

			// updating the money in the file
			int pos = (-1) * static_cast<int>(sizeof(bank));
			file.seekp(pos, ios::cur);
			file.write((char*)&bank, sizeof(bank));
			break;
		}
	}

	file.close();

	if (found)
		successMessage("\n\tAMOUNT SUCCESSFULLY WITHDRAWN.\n");
	else
		dangerMessage("\tNO MATCH FOUND!");

	line('.');
	char yesno;
	cout << "\tDo You Want To Withdraw Again?(Press 'y' for Yes)\n\t>> ";
	cin >> yesno;

	if (yesno == 'y' || yesno == 'Y')
		return withdraw();
}

/* -------- 5. TRANSFER MONEY ------------------------------------------------------- */
void transfer()
{
	HEADER("TRANSFER MONEY BETWEEN ACCOUNTS");

	file.open(filename, ios::binary | ios::in | ios::out);

	if (!file || (numOfRecords() <= 0))
	{
		dangerMessage("\tNO DATA FOUND! ADD ACCOUNTS FIRST.");
		pause();
		file.close();
		return;
	}

	int sender, receiver;
	double transferAmt;

	bool transferred = false;
	bool receiverExists = false;
	bool senderExists = false;

	// asking the account no to add amount
	cout << "\n\tENTER THE SENDER A/C NO. : ";
	cin >> sender;

	// checking if the sender a/c exists
	while (file.read((char*)&bank, sizeof(bank)))
	{
		if (sender == bank.getAccountNo())
		{
			senderExists = true;
			break;
		}
	}

	cout << "\n\tENTER THE RECEIVER A/C NO. : ";
	cin >> receiver;

	// checking if reciever a/c exists
	file.seekg(0, ios::beg);
	while (file.read((char*)&bank, sizeof(bank)))
	{
		if (receiver == bank.getAccountNo())
		{
			receiverExists = true;
			break;
		}
	}

	// if one of the a/c doesn't exist
	if (!(receiverExists || senderExists))
	{
		dangerMessage("\n\tSORRY! CANNOT FIND REQUIRED ACCOUNT(s).\n");
		pause();
		file.close();
		return;
	}

	do
	{
		green();
		cout << "\n\n\tENTER THE AMOUNT YOU WANT TO WITHDRAW : Rs.";
		gray();
		cin >> transferAmt;
	}
	while (!isValidAmount(transferAmt));

	// deducting money from sender's a/c
	file.seekg(0, ios::beg);
	while (file.read((char*)&bank, sizeof(bank)))
	{
		if (sender == bank.getAccountNo())
		{
			bank.addWithdraw(transferAmt);

			if (bank.getBalance() < transferAmt)
			{
				dangerMessage("\n\tOOPS! INSUFFICIENT BALANCE.");
				pause();
				file.close();
				return;
			}
			else
			{
				bank.addWithdraw(transferAmt);
			}

			// updating the money in the file
			int pos = (-1) * static_cast<int>(sizeof(bank));
			file.seekp(pos, ios::cur);
			file.write((char*)&bank, sizeof(bank));
			break;
		}
	}

	// adding money in receiver's a/c
	file.seekg(0, ios::beg);
	while (file.read((char*)&bank, sizeof(bank)))
	{
		if (receiver == bank.getAccountNo())
		{
			transferred = true;

			bank.addDeposit(transferAmt);

			// updating the money in the file
			int pos = (-1) * static_cast<int>(sizeof(bank));
			file.seekp(pos, ios::cur);
			file.write((char*)&bank, sizeof(bank));
			break;
		}
	}

	file.close();

	// if amount transferred, display success msg
	if (transferred)
		successMessage("\n\tAMOUNT SUCCESFULLY TRANSFERRED.\n");
	else
		dangerMessage("\tERROR OCCURED WHILE TRANSFERRING!\n");

	line('.');
	char yesno;
	cout << "\tDo You Want To Transfer Again?(Press 'y' for Yes)\n\t>> ";
	cin >> yesno;

	if (yesno == 'y' || yesno == 'Y')
		return transfer();
}

/* -------- 6. CLOSE ACCOUNT ------------------------------------------------------- */
void closeAccount()
{
	HEADER("CLOSING AN ACCOUNT");

	file.open(filename, ios::in | ios::binary);

	if (!file || (numOfRecords() <= 0))
	{
		dangerMessage("\tNO DATA FOUND! ADD ACCOUNTS FIRST.");
		pause();
		file.close();
		return;
	}

	fstream newfile;
	newfile.open("newfile.dat", ios::out | ios::binary);

	int accountNum;
	int found = 0;

	lightred();
	cout << "\tENTER THE A/C NO. YOU WANT TO CLOSE: ";
	gray();
	cin >> accountNum;

	// searching for the a/c to delete
	while (file.read((char*)&bank, sizeof(bank)))
	{
		if (accountNum == bank.getAccountNo())
		{
			found = 1;

			cout << endl;
			bank.displayHeadings();
			bank.displayRecord();
		}
		else
		{
			newfile.write((char*)&bank, sizeof(bank));
		}
	}

	// closing the files to perform remove & rename
	file.close();
	newfile.close();

	// if the record is found and updated , Now renaming the newfile
	if (found)
	{
		remove(filename);
		(void)rename("newfile.dat", filename);
		successMessage("\n\tACCOUNT SUCCESSFULLY CLOSED.\n");
	}
	else
		dangerMessage("\tNO MATCH FOUND!");

	// if user wants to close another a/c
	line('.');
	char yesno;
	cout << "\tDo You Want To Delete Another?(Press 'y' for Yes)\n\t>> ";
	cin >> yesno;

	if (yesno == 'y' || yesno == 'Y')
		return closeAccount();
}

/* -------- 7. LIST ALL ACCOUNTS ------------------------------------------------------- */
void listAccounts()
{
	HEADER("LISTING ALL EXISTING ACCOUNTS");

	file.open(filename, ios::binary | ios::in);

	// if no a/c found
	if (!file || numOfRecords() <= 0)
	{
		dangerMessage("\tNO DATA FOUND! ADD ACCOUNTS FIRST.");
		pause();
		file.close();
		return;
	}

	cout << "\tTOTAL ACCOUNTS = " << numOfRecords() << '\n';

	bank.displayHeadings();
	while (file.read((char*)&bank, sizeof(bank)))
	{
		bank.displayRecord();
	}

	file.close();
	pause();
}

/* -------- 8. SORT ACCOUNTS ------------------------------------------------------- */
void sortAccounts()
{
	HEADER("SORTING SUB-MENU");

	file.open(filename, ios::in);
	int n = numOfRecords();

	// if the file exists or atleast has a record
	if (!file || (n <= 0))
	{
		dangerMessage("\tNO DATA FOUND! ADD ACCOUNTS FIRST.");
		pause();
		file.close();
		return;
	}

	int sortChoice;
	Bank* obj, temp;

	// dynamically making object array
	obj = new Bank[n];

	// copying file data in the object array
	for (int i = 0; i < n; i++)
	{
		file.read((char*)&obj[i], sizeof(obj[i]));
	}

	do
	{
		HEADER("SORTING SUB-MENU");

		/*----------------- Sub-Menu to Choose which type of sorting -------------------*/
		cout << "\t1. SORT BY ACCOUNT NUMBER";
		cout << "\n\n\t2. SORT BY CUSTOMER'S NAME";
		cout << "\n\n\t3. SORT BY BANK BALANCE";
		cout << "\n\n\t0. BACK TO THE MENU";

		green();
		cout << "\n\n\n\tENTER YOUR CHOICE :\n\t>> ";
		gray();
		cin >> sortChoice;
		cin.ignore();

		switch (sortChoice)
		{
			case 1:
				// sorting by team ID
				HEADER("SORTING BY ACCOUNT NUMBER");
				for (int i = 0; i < n; i++)
				{
					for (int j = i + 1; j < n; j++)
					{
						if (obj[i].accountNo > obj[j].accountNo)
						{
							temp = obj[i];
							obj[i] = obj[j];
							obj[j] = temp;
						}
					}
				}
				break;
			case 2:
				// sorting by Customer Name
				HEADER("SORTING BY CUSTOMER'S NAME");

				for (int i = 0; i < n; i++)
				{
					for (int j = i + 1; j < n; j++)
					{
						if (strcmp(obj[i].firstName, obj[j].firstName) > 0)
						{
							temp = obj[i];
							obj[i] = obj[j];
							obj[j] = temp;
						}
					}
				}
				break;
			case 3:
				// sorting by bank balance
				HEADER("SORTING BY BANK BALANCE");
				for (int i = 0; i < n; i++)
				{
					for (int j = i + 1; j < n; j++)
					{
						if (obj[i].balance < obj[j].balance)
						{
							temp = obj[i];
							obj[i] = obj[j];
							obj[j] = temp;
						}
					}
				}
				break;
		}

		/*----------------- Displaying the accounts after sorting -------------------*/
		if (sortChoice >= 1 && sortChoice <= 3)
		{
			cout << "\tTOTAL ACCOUNTS = " << numOfRecords() << '\n';

			bank.displayHeadings();
			for (int i = 0; i < n; i++)
			{
				obj[i].displayRecord();
			}

			pause();
		}
	}
	while (sortChoice != 0);

	// deleting objects after job done
	delete [] obj;
	file.close();
}

/* -------- 9. ABOUT ------------------------------------------------------- */
void about()
{
	HEADER("ABOUT THE DEVELOPERS");

	ifstream aboutfile;
	aboutfile.open("about.dat", ios::in);
	if (!aboutfile)
	{
		dangerMessage("\n\tSORRY! CANNOT FIND DESCRIPTION FILE\n");
		pause();
		return;
	}

	char ch;
	while (aboutfile.get(ch))
	{
		cout << ch;
	}

	aboutfile.close();

	cout << endl;
	pause();
}

/* ========================================
				HELPING FUNCS
	 ======================================== */
void line(char ch)
{
	cout << "\n\t";
	lightblue();
	for (int i = 0; i < 129; i++)
	{
		cout << char(ch);
	}
	gray();
	cout << '\n';
}

/* -------- HEADER ------------------------------------------------------- */
void HEADER(const char* title)
{
	system("cls");
	lightblue();
	cout << "\n\t" << title << "\n\n";

	for (int i = 0; i < 146; i++)
	{
		cout << char(219);
	}
	gray();
	cout << "\n\n";
}

/* -------- SCREEN PAUSE ------------------------------------------------------- */
void pause()
{
	lightpurple();
	cout << "\n\tPRESS ANY KEY TO CONTINUE...";
	gray();
	(void)_getch();
}

/* -------- FOR DRY PURPOSE ------------------------------------------------------- */

// colorize the msg for the aesthetic purpose
inline void dangerMessage(const char* msg)
{
	lightred();
	cout << msg;
	gray();
}

inline void successMessage(const char* msg)
{
	green();
	cout << msg;
	gray();
}

/* -------- TOTAL ACCOUNTS COUNTER ------------------------------------------------------- */
int numOfRecords()
{
	ifstream fp;
	fp.open(filename, ios::in | ios::binary);

	// if fp is empty
	if (!fp.is_open())
	{
		return 0;
	}

	fp.seekg(0, ios::end);						 // moving cursor to the end of the fp
	int n = fp.tellg() / sizeof(bank); // gives total bytes of the fp
	fp.close();

	return n; // returns total number of recors as totalsize/size_per_one_obj
}

/* -------- HIDES PASSWORD ------------------------------------------------------- */
char* maskPassword(char* pw)
{
	int i = 0;
	char ch;

	while ((ch = _getch()) != 13)
	{
		if (ch == 8)
		{
			--i;
			cout << "\b \b";
		}
		else
		{
			pw[i] = ch;
			cout << "*";
			++i;
		}
	}
	pw[i] = '\0';

	return pw;
}

/* -------- CHECKS FOR VALID NAME ------------------------------------------------------- */
bool isValidName(char* name)
{
	int i = 0;
	while (name[i] != '\0')
	{
		// if the character is not alpha or space
		if ((!isalpha(name[i])) && (name[i] != ' '))
		{
			dangerMessage("\t[PLEASE USE ALPHABETS ONLY!]\n");
			return false;
		}
		i++;
	}
	return true;
}

/* -------- CHECKS ACCOUNT NO ------------------------------------------------------- */
bool isValidAccountNo(int accNo)
{
	// finding length of the number
	int i = 0;
	int n = accNo;
	int length = 0;

	while (n != 0)
	{
		n = n / 10;
		++length;
	}

	// checking if number is valid 5 digit number
	if (accNo <= 0 || length != 5)
	{
		dangerMessage("\t[INVALID A/C NO! PLEASE USE 5 DIGITS.]\n");
		return false;
	}

	// checking if a/c no already exist in the file
	ifstream fp;
	Bank b;

	fp.open(filename, ios::in | ios::binary);
	if (!fp.is_open())
	{
		return false;
	}

	while (fp.read((char*)&b, sizeof(b)))
	{
		if (accNo == b.getAccountNo())
		{
			dangerMessage("\t[THIS A/C NO. ALREADY EXISTS!]\n");
			fp.close();
			return false;
		}
	}

	fp.close();
	return true;
}

/* -------- CHECKS FOR VALID AMOUNT ------------------------------------------------------- */
bool isValidAmount(double amt)
{
	if (amt < 0)
	{
		dangerMessage("\t[PLEASE! DON'T BE NEGATIVE.]\n");
		return false;
	}
	else if (amt == 0)
	{
		cout << "\t[FUN FACT: 0 WAS INVENTED BY ARYA BHATT.]\n";
		return true;
	}
	else
		return true;
}

bool isValidPhoneNo(char* num)
{
	if (strlen(num) != 10)
	{
		dangerMessage("\t[PLEASE USE 10 DIGITS!]\n");
		return false;
	}
	else
		return true;
}

bool isValidCitizenship(char* citizenNo)
{
	// checking if a/c no already exist in the file
	ifstream fp;
	Bank b;

	fp.open(filename, ios::in | ios::binary);
	if (!fp.is_open())
	{
		return false;
	}

	while (fp.read((char*)&b, sizeof(b)))
	{
		if (strcmp(citizenNo, b.getCitizenshipNo()) == 0)
		{
			dangerMessage("\t[AN ACCOUNT WITH THIS CITIZENSHIP NO. ALREADY EXISTS!]\n");
			fp.close();
			return false;
		}
	}

	fp.close();
	return true;
}
