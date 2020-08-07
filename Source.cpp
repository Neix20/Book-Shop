#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<cctype>
#include<regex>
using namespace std;

struct Book {
	string title, ISBN, author, publisher;
	int quantity;
	double wholesaleCost, retailCost;
	void print(ostream& out) {
		out << endl << endl
			<< "Title: " << title << endl
			<< "ISBN: " << ISBN << endl
			<< "Author: " << author << endl
			<< "Publisher: " << publisher << endl
			<< "Quantity: " << quantity << endl
			<< fixed << setprecision(2)
			<< "Wholesale Cost: $" << wholesaleCost << endl
			<< "Retail Cost: $" << retailCost;
	}
	void export_to_table(ostream& out,int i) {
		string ind = to_string(i + 1) + ".";
		out << "<tr>" << endl
			<< "<td>" << ind << "</td>" << endl
			<< "<td>" << title << "</td>" << endl
			<< "<td>" << ISBN << "</td>" << endl
			<< "<td>" << author << "</td>" << endl
			<< "<td>" << publisher << "</td>" << endl
			<< "<td style=\"text-align: right;\">" << quantity << "</td>" << endl
			<< fixed << setprecision(2)
			<< "<td style=\"text-align: right;\">" << "$" << wholesaleCost << "</td>" << endl
			<< "<td style=\"text-align: right;\">" << "$" << retailCost << "</td>" << endl
			<< "</tr>" << endl;
	}

	void show_table(int i) {
		string ind = to_string(i + 1) + ".";
		cout << left
			<< setw(4) << ind
			<< setw(50) << title
			<< setw(20) << ISBN
			<< setw(20) << author
			<< setw(40) << publisher
			<< right
			<< setw(3) << quantity
			<< fixed << setprecision(2)
			<< " $"
			<< right
			<< setw(6) << wholesaleCost
			<< " $"
			<< right
			<< setw(6) << retailCost
			<< endl;
	}
};

struct transaction {
	Book b;
	int quantity;

	double total() {
		return quantity * b.retailCost;
	}
	void print(ostream& out) {
		out << setw(10) << " "
			<< right
			<< setw(3) << quantity
			<< setw(5) << " "
			<< left
			<< setw(20) << b.ISBN
			<< setw(40) << b.title
			<< fixed << setprecision(2)
			<< "$" << setw(14) << b.retailCost
			<< "$" << setw(14) << total();
	}
};

Book b[100];
int numberOfBooks(0);

bool date_validator(string&);
bool int_validator(string&);
bool ISBN_validator(string&);
bool string_validator(string&);
bool double_validator(string&);
bool char_validator(string&);
bool name_validator(string&);
void drawLine();
void center(string);
string lower(string);
void color(string c);
void reset();
void menu();
void book_database_menu();
bool readFile(string);
bool search(string, Book&);
void outFile(string);
bool addBook(Book&);
void searched_term(int []);
void edit(int [], Book&);
int search(string);
void cashier();
void receipt(transaction[], int, string, int);
bool readOrder(string, int&);
void export_to_html();

int main() {
	/*readFile("books.txt");
	int s_arr[7];
	Book temp;
	searched_term(s_arr);
	edit(s_arr, b[1]);*/
	//menu();
	/*string date;
	cout << endl
		<< setw(35) << " " << "Rules: " << endl
		<< setw(35) << " " << "1. The Date should not be empty" << endl
		<< setw(35) << " " << "2. The Date should only consists of numbers and slash characters" << endl
		<< setw(35) << " " << "3. The Date should have at least 6 characters till 10 characters" << endl
		<< setw(35) << " " << "4. The Date follows DD/MM/YYYY format" << endl
		<< setw(35) << " " << "5. Months must be a number between 0 and 12" << endl
		<< setw(35) << " " << "6. Day must be a number between 0 and 31" << endl
		<< setw(35) << " " << "7. Year must have at least 2 numbers" << endl
		<< setw(35) << " " << "8. Year can only be 2 or 4 digits" << endl
		<< setw(35) << " " << "9. Days can only be 31st on respective months" << endl
		<< setw(35) << " " << "10. 29th February can only happen on a leap year" << endl
		<< setw(35) << " " << "11. 30th and 31st February does not exist" << endl
		<< setw(35) << " " << "12. The date can not consists of only numbers or slashes" << endl
		<< endl;
	cout << setw(40) << ">> ";
	while (!date_validator(date)) {
		cout << setw(40) << ">> ";
	}
	center(date);*/
	/*menu();*/
	string s;
	cout << endl
		<< setw(40) << "" << "Format: XXX-X-XXX-XXXXX-X" << endl
		<< setw(40) << ">> ";
	while (!ISBN_validator(s)) {
		cout << setw(40) << ">> ";
	}
	cout << endl
		<< setw(40) << "" << s << endl;
	system("pause");
	return 0;
}

bool date_validator(string& x) {
	getline(cin, x);

	if (x.empty()) {
		cout << endl;
		center("You have not inserted anything");
		cout << endl;
		return false;
	}

	if (x[0] == ' ') {
		cout << endl;
		center("You have entered only a single space");
		cout << endl;
		return false;
	}

	if (x.find_first_not_of("/") == -1) {
		cout << endl;
		center("The string consists of only slashes");
		cout << endl;
		return false;
	}

	if (x.find_first_not_of("0123456789") == -1) {
		cout << endl;
		center("The string consists of only numbers");
		cout << endl;
		return false;
	}

	int occ[20];
	int slash_count = 0;
	for (int i = 0; i < x.length(); i++) {
		if (x[i] == '/')
			occ[slash_count++] = i;

		if (slash_count > 2) {
			cout << endl;
			center("The number of slash has exceeded the proper count");
			cout << endl;
			return false;
		}

		if (!isdigit(x[i]) && x[i] != '/') {
			cout << endl;
			center("The date does not consists of only digits and two slash");
			cout << endl;
			return false;
		}
	}

	if (x.length() < 6 || x.length() > 10) {
		cout << endl;
		center("The string does not follow the length of a normal Date");
		cout << endl;
		return false;
	}

	if (x.length() - occ[1] - 1 < 2 || x.length() - occ[1] - 1 == 3 || x.length() - occ[1] - 1 > 4) {
		cout << endl;
		center("The year can only be 2 or 4 numbers");
		cout << endl;
		return false;
	}

	int day = stoi(x.substr(0, occ[0])), month = stoi(x.substr(occ[0] + 1, occ[1] - occ[0] - 1)), year = stoi(x.substr(occ[1] + 1, x.length() - occ[1] - 1));

	if (day <= 0 || day > 31) {
		cout << endl;
		center("The day is not between 0 and 31");
		cout << endl;
		return false;
	}

	if (month <= 0 || month > 12) {
		cout << endl;
		center("The month is not between 0 and 12");
		cout << endl;
		return false;
	}

	switch (month) {
	case 2:
		if (year % 4 == 0) {
			if (day >= 30) {
				cout << endl;
				center("There's no such day for February!!");
				cout << endl;
				return false;
			}
		}
		else if (day >= 29) {
			cout << endl;
			center("There's no such day for February!!");
			cout << endl;
			return false;
		}
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		if (day == 31) {
			cout << endl;
			center("There's no 31st for that month!!");
			cout << endl;
			return false;
		}
		break;
	}
	
	return true;
}

bool name_validator(string& x) {
	getline(cin, x);

	if (x.empty()) {
		cout << endl;
		center("You have not inserted anything");
		cout << endl;
		return false;
	}

	if (x[0] == ' ') {
		cout << endl;
		center("You have entered only a single space");
		cout << endl;
		return false;
	}

	int dot_count = 0;
	for (int i = 0; i < x.length(); i++) {
		if (x[i] == '.')
			dot_count++;

		if (dot_count > 1) {
			cout << endl;
			center("The name cannot have more than one '.'");
			cout << endl;
			return false;
		}

		if (!isalpha(x[i]) && x[i] != '.' && x[i] != ' ') {
			cout << endl;
			center("The name does not consists of only alphabets (and one or none '.')");
			cout << endl;
			return false;
		}
	}

	return true;
}

bool char_validator(string& x) {
	getline(cin, x);

	if (x.empty()) {
		cout << endl;
		center("You have not inserted anything");
		cout << endl;
		return false;
	}

	if (x[0] == ' ') {
		cout << endl;
		center("You have entered only a single space");
		cout << endl;
		return false;
	}

	if (x.length() > 1) {
		cout << endl;
		center("You have exceeded the length for input");
		cout << endl;
		return false;
	}

	return true;
}

bool string_validator(string& x) {
	getline(cin, x);

	if (x.empty()) {
		cout << endl;
		center("You have not inserted anything");
		cout << endl;
		return false;
	}

	if (x[0] == ' ') {
		cout << endl;
		center("You have entered only a single space");
		cout << endl;
		return false;
	}

	return true;
}

bool double_validator(string& x) {
	getline(cin, x);

	if (x.empty()) {
		cout << endl;
		center("You have not inserted anything");
		cout << endl;
		return false;
	}

	if (x[0] == ' ') {
		cout << endl;
		center("You have entered only a single space");
		cout << endl;
		return false;
	}

	int dot_count = 0;
	for (int i = 0; i < x.length(); i++) {
		if (x[i] == '.')
			dot_count++;

		if (dot_count > 1) {
			cout << endl;
			center("The number cannot have more than one '.'");
			cout << endl;
			return false;
		}

		if (!isdigit(x[i]) && x[i] != '.') {
			cout << endl;
			center("The number does not consists of only numbers (and one or none '.')");
			cout << endl;
			return false;
		}
	}
	return true;
}

bool int_validator(string& x) {
	getline(cin, x);

	if (x.empty()) {
		cout << endl;
		center("You have not inserted anything");
		cout << endl;
		return false;
	}

	if (x[0] == ' ') {
		cout << endl;
		center("You have entered only a single space");
		cout << endl;
		return false;
	}

	for (int i = 0; i < x.length(); i++)
		if (!isdigit(x[i])) {
			cout << endl;
			center("You have not entered a digit");
			cout << endl;
			return false;
		}

	return true;
}

bool ISBN_validator(string& s) {
	getline(cin, s);
	return regex_match(s, regex("^[0-9]{3}-[0-9]-[0-9]{3}-[0-9]{5}-[0-9]$"));
	/*if (s.empty()) {
		cout << endl;
		center("You have not inserted anything");
		cout << endl;
		return false;
	}

	if (s[0] == ' ') {
		cout << endl;
		center("You have entered only a single space");
		cout << endl;
		return false;
	}


	for (int i = 0; i < s.length(); i++) {
		if (i == 3 || i == 5 || i == 9 || i == 15)
			continue;

		if (!isdigit(s[i])) {
			cout << endl;
			center("The string you input does not consists of only digit characters");
			cout << endl;
			return false;
		}
	}

	if (s.length() != 17) {
		cout << endl;
		center("The string does not fit the length of an ISBN");
		cout << endl;
		return false;
	}

	if (s[3] != '-' || s[5] != '-' || s[9] != '-'|| s[15] != '-') {
		cout << endl;
		center("The string you input does not follow the format of ISBN");
		cout << endl;
		return false;
	}


*/
}

bool readFile(string filename) {
	string trash, price;
	int i(0);
	ifstream input(filename);
	if (input) {
		while (!input.eof()) {
			Book temp;

			input >> trash;
			getline(input, temp.title);
			temp.title = temp.title.substr(1);

			input >> trash >> temp.ISBN;
			input >> trash;

			getline(input, temp.author);
			temp.author = temp.author.substr(1);

			input >> trash;
			getline(input, temp.publisher);
			temp.publisher = temp.publisher.substr(1);

			input >> trash >> temp.quantity
				>> trash >> trash >> price;
			temp.wholesaleCost = stod(price.substr(1));

			input >> trash >> trash >> price;
			temp.retailCost = stod(price.substr(1));

			b[i++] = temp;
		}
		numberOfBooks = i;
		input.close();
	}
	else
		return false;

	return true;
}

void center(string msg) {
	int l = msg.length();
	int space = 60 - (int)l / 2;
	cout << setw(space) << " " << msg << endl;
}

void drawLine() {
	cout << "========================================================================================================================" << endl;
}

string lower(string s) {
	for (int i = 0; i < s.length(); i++)
		s[i] = tolower(s[i]);
	return s;
}

void color(string c) {
	string color[8] = { "black","red","green","yellow","blue","magenta","cyan","white" };
	string clr = lower(c);
	int num = -1;
	for (int i = 0; i < 8; i++)
		if (clr == color[i])
			num = i;
	switch (num) {
	case 0:cout << "\u001b[30m"; break;
	case 1:cout << "\u001b[31m"; break;
	case 2:cout << "\u001b[32m"; break;
	case 3:cout << "\u001b[33m"; break;
	case 4:cout << "\u001b[34m"; break;
	case 5:cout << "\u001b[35m"; break;
	case 6:cout << "\u001b[36m"; break;
	case 7:cout << "\u001b[37m"; break;
	}
}

void reset() {
	cout << "\u001b[0m";
}

void menu() {
	int choice;
	string choice2, trash;

	if (readFile("books.txt")) {
		do {
			system("cls");
			cout << endl;
			center("INTI Smart Book Store");
			center("Main Menu");

			drawLine();
			cout << endl
				<< setw(40) << " " << "1. Cashier" << endl
				<< setw(40) << " " << "2. Book Database" << endl
				<< setw(40) << " " << "3. Export Book Records" << endl
				<< setw(40) << " " << "4. Exit" << endl
				<< endl;
			drawLine();

			cout << endl << setw(40) << " " << "Enter Your Choice >> ";

			while (!int_validator(choice2)) { cout << setw(50) << " " << " >> "; }
			choice = stoi(choice2);

			system("cls");
			switch (choice) {
			case 1:
				cashier();
				break;
			case 2:
				book_database_menu();
				break;
			case 3:
				export_to_html();
				getline(cin, trash);
				break;
			}
		} while (choice != 4);
		cout << endl;
		drawLine();
		cout << endl;
		center("Thank you for using our program!");
		cout << endl;
		drawLine();
		cout << endl;
	}
	else {
		cout << endl;
		drawLine();
		center("File does not exist!!");
		cout << endl;
		drawLine();
		cout << endl;
	}
}

void book_database_menu() {
	int choice, s_arr[7], index;
	string choice2, search_text, s, trash;
	Book temp, temp2;
	bool s_flag, add_flag, delete_flag;
	do {
		system("cls");
		cout << endl;
		center("Study Smart Book Store");
		center("Inventory Database");

		drawLine();
		cout << endl
			<< setw(40) << " " << "1. Search Book" << endl
			<< setw(40) << " " << "2. Add Book" << endl
			<< setw(40) << " " << "3. Edit Book" << endl
			<< setw(40) << " " << "4. Delete Book" << endl
			<< setw(40) << " " << "5. Return to the Main Menu" << endl
			<< endl;
		drawLine();

		cout << endl << setw(40) << " " << "Enter Your Choice >> ";

		while (!int_validator(choice2)) { cout << setw(50) << " " << " >> "; }
		choice = stoi(choice2);

		system("cls");
		switch (choice) {
		case 1:
			//initialize the value of the variables
			search_text = "";
			s_flag = false;
			temp = Book();

			cout << endl;
			center("Study Smart Book Store");
			center("Inventory Database");
			drawLine();

			cout << endl;
			center("SEARCH BOOK");
			cout << endl;
			center("What are you looking for?");
			center("Please specify which field you would like to search:");
			cout << endl;
			cout << setw(45) << " " << "1. Title" << endl
				<< setw(45) << " " << "2. ISBN" << endl
				<< endl
				<< setw(35) << " " << "*Please enter as followed: 1 - Title, 2 - ISBN" << endl
				<< endl
				<< setw(45) << " " << "Enter Your Choice >> ";

			do {
				while (!int_validator(choice2)) {
					cout << setw(45) << " " << " >> ";
				}
				choice = stoi(choice2);
				if (choice < 1 || choice>2) {
					cout << endl;
					center("That wasn't within the options!");
					cout << endl
						<< setw(45) << " " << " >> ";
				}
			} while (choice < 1 || choice > 2);

			cout << endl;
			drawLine();

			s = (choice == 1) ? "title" : "ISBN";

			center("Available Books");
			cout << endl;

			for (int i = 0; i < numberOfBooks; i++)
				cout << setw(35) << " " << i + 1 << ". " << b[i].title << " - " << b[i].ISBN << endl;

			cout << endl;
			center("Enter the "+s+" of the book you wish to search for");
			cout << endl
				<< setw(40) << " " << " >> ";

			if (choice == 1) 
				while (!string_validator(search_text)) {cout << setw(40) << " " << " >> ";}
			else if (choice == 2)
				while (!ISBN_validator(search_text)) { cout << setw(40) << " " << " >> "; }

			s_flag = search(search_text, temp);

			if (s_flag) {
				cout << endl;
				drawLine();
				cout << endl
					<< "RESULTS: ";
				temp.print(cout);
				cout << endl << endl;
				center("OUTPUT DISPLAYED SUCCESSFULLY");
			}
			else {
				cout << endl;
				center("SEARCH RESULT INCONCLUSIVE. THE BOOK DOES NOT EXIST");
				center("OUTPUT WAS NOT DISPLAYED");
			}

			cout << endl;
			drawLine();

			getline(cin, trash);
			system("cls");
			break;
		case 2:
			do {
				s_flag = add_flag = false;

				system("cls");
				cout << endl;
				center("Study Smart Book Store");
				center("Inventory Database");
				drawLine();

				cout << endl;
				center("ADD BOOK");
				center("Storage Available: " + to_string(100 - numberOfBooks));
				cout << endl;

				if (addBook(temp)) {
					cout << endl;
					drawLine();
					cout << endl << "Results: ";
					temp.print(cout);

					cout << endl << endl;
					center("Are you certain you want the book \u001b[31m" + temp.title + "\u001b[0m to be added [Y/N]?:");
					cout << setw(45) << " " << " >> ";

					while (!char_validator(choice2)) {
						cout << setw(45) << " " << " >> ";
					}

					choice = choice2[0];
					choice = tolower(choice);

					s_flag = true;
					add_flag = true;

					if (choice == 'y')
						break;

					add_flag = false;

					cout << endl;
					center("Do you wish to continue operations [Y/N]?:");
					cout << setw(45) << " " << " >> ";

					while (!char_validator(choice2)) {
						cout << setw(45) << " " << " >> ";
					}

					choice = choice2[0];
					choice = tolower(choice);
				}
				else
					break;
			} while (choice == 'y');

			if (add_flag)
				b[numberOfBooks++] = temp;
			
			if (!s_flag) {
				center("The library has already reached full storage capacity");
				center("ACTION WAS NOT PERFORMED SUCCESSFULLY");
				cout << endl;
				drawLine();
				getline(cin, trash);
			}

			system("cls");
			break;
		case 3:
			do {
				do {
					search_text = "";
					s_flag = add_flag = false;
					temp = Book();

					system("cls");
					cout << endl;
					center("Study Smart Book Store");
					center("Inventory Database");
					drawLine();

					cout << endl;
					center("Available Books");
					cout << endl;

					for (int i = 0; i < numberOfBooks; i++)
						cout << setw(35) << " " << i + 1 << ". " << b[i].title << endl;

					cout << endl;
					center("EDIT BOOK");
					cout << endl;
					center("Please enter the title of the book you are looking for");
					cout << setw(45) << " " << " >> ";
					while (!string_validator(search_text)) { cout << setw(45) << " " << " >> "; }

					s_flag = search(search_text, temp2);

					temp = temp2;

					if (s_flag) {
						cout << endl;
						drawLine();
						cout << endl
							<< "RESULTS: ";
						temp.print(cout);
						cout << endl << endl;

						center("Are you certain that this is the book you wish to edit [Y/N]?:");
						cout << setw(45) << " " << " >> ";
						while (!char_validator(choice2)) {
							cout << setw(45) << " " << " >> ";
						}

						choice = choice2[0];
						choice = tolower(choice);
					}
					else {
						break;
					}
				} while (choice != 'y');

				if (!s_flag) {
					cout << endl;
					center("SEARCH RESULT INCONCLUSIVE. THE BOOK DOES NOT EXIST");
					center("ACTION WAS NOT PERFORMED SUCCESSFULLY");
					cout << endl;
					drawLine();
					break;
				}

				searched_term(s_arr);
				edit(s_arr, temp);

				temp.print(cout);
				cout << endl << endl;


				drawLine();

				cout << endl;
				center("Are you certain that you want to edit the book [Y/N]?:");
				cout << setw(45) << " " << " >> ";

				while (!char_validator(choice2)) {
					cout << setw(45) << " " << " >> ";
				}

				choice = choice2[0];
				choice = tolower(choice);

				if (choice == 'y') {
					add_flag = true;
					break;
				}

				cout << endl;
				center("Do you wish to continue operations [Y/N]?:");
				 
				cout << setw(45) << " " << " >> ";
				while (!char_validator(choice2)) {
					cout << setw(45) << " " << " >> ";
				}

				choice = choice2[0];
				choice = tolower(choice);
			} while (choice == 'y');

			if (add_flag)
				for (int i = 0; i < numberOfBooks; i++)
					if (b[i].title == temp2.title)
						b[i] = temp;

			getline(cin, trash);
			system("cls");
			break;
		case 4:
			do {
				search_text = "";
				s_flag = delete_flag = false;
				temp = Book();

				system("cls");
				cout << endl;
				center("Study Smart Book Store");
				center("Inventory Database");
				drawLine();

				cout << endl;
				center("Available Books");
				cout << endl;

				for (int i = 0; i < numberOfBooks; i++)
					cout << setw(35) << " " << i + 1 << ". " << b[i].title << endl;

				cout << endl;
				center("DELETE BOOK");
				cout << endl;
				center("Please enter the title of the book you are looking for:");
				cout << setw(45) << " " << " >> ";
				while (!string_validator(search_text)) { cout << setw(45) << " " << " >> "; }

				s_flag = search(search_text, temp);

				if (s_flag) {
					cout << endl;
					drawLine();
					cout << endl
						<< "RESULTS: ";
					temp.print(cout);
					cout << endl << endl;

					center("Are you certain that this is the book you wish to delete [Y/N]?:");
					cout << setw(45) << " " << " >> ";
					while (!char_validator(choice2)) {
						cout << setw(45) << " " << " >> ";
					}

					choice = choice2[0];

					if (choice == 'y') {
						delete_flag = true;
						break;
					}

					cout << endl;
					center("Do you wish to continue operations [Y/N]?:");
					cout << setw(45) << " " << " >> ";
					while (!char_validator(choice2)) {
						cout << setw(45) << " " << " >> ";
					}

					choice = choice2[0];
					choice = tolower(choice);
				}
				else
					break;
			} while (choice == 'y');

			if (delete_flag) {
				index = search(temp.title);
				for (int i = index; i < numberOfBooks; i++) {
					if (i == numberOfBooks - 1)
						break;
					b[i] = b[i + 1];
				}
				numberOfBooks--;
			}

			if (!s_flag) {
				cout << endl;
				center("SEARCH RESULT INCONCLUSIVE. THE BOOK DOES NOT EXIST");
				center("ACTION WAS NOT PERFORMED SUCCESSFULLY");
				cout << endl;
				drawLine();
			}

			getline(cin, trash);
			system("cls");
			break;
		}
		outFile("books.txt");
	} while (choice != 5);
}

bool search(string text, Book& bk) {
	text = lower(text);
	for (int i = 0; i < numberOfBooks; i++) {
		string title = lower(b[i].title);
		if (title == text || b[i].ISBN == text) {
			bk = b[i];
			return true;
		}
	}
	return false;
}

void outFile(string filename) {
	ofstream output(filename);
	for (int i = 0; i < numberOfBooks; i++)
		b[i].print(output);
	output.close();
}

bool addBook(Book& temp) {

	char choice;
	string choice2, s, test1, test2;
	bool flag;

	if (numberOfBooks == 100) {
		return false;
	}

	center("CREATING A NEW BOOK");

	//Book Title
	do {
		cout << endl;
		drawLine();
		cout << endl;

		cout << setw(40) << " " << "Rules: " << endl
			<< setw(40) << " " << "1. Title of the book should not be empty" << endl
			<< endl;
		
		do {
			flag = false;
			center("Enter the title of the book");
			cout << setw(45) << " " << " >> ";

			while (!string_validator(temp.title)) {
				cout << setw(45) << " " << " >> ";
			}

			for (int i = 0; i < numberOfBooks; i++) {
				test1 = lower(temp.title);
				test2 = lower(b[i].title);
				if (test1 == test2)
					flag = true;
			}

			if (flag) {
				cout << endl;
				center("ERROR! The title of the book has already been used.");
				center("Please change the title of the book.");
				cout << endl;
			}
		} while (flag);

		cout << endl;
		center("Are you certain you want \u001b[31m" + temp.title + "\u001b[0m to be your book title [Y/N]?:");
		cout << setw(45) << " " << " >> ";

		while (!char_validator(choice2)) {
			cout << setw(45) << " " << " >> ";
		}

		choice = choice2[0];
		choice = tolower(choice);

	} while (choice != 'y');
	//Book ISBN
	do {
		cout << endl;
		drawLine();
		cout << endl;

		cout << setw(35) << " " << "Rules: " << endl
			<< setw(35) << " " << "1. ISBN of the book should not be empty" << endl
			<< setw(35) << " " << "2. ISBN of the book should consists of only digits and hyphen characters" << endl
			<< setw(35) << " " << "3. ISBN of the book should be 17 characters " << endl
			<< setw(35) << " " << "4. ISBN of the book should have a format of XXX-X-XXX-XXXXX-X " << endl
			<< endl;

		do {
			flag = false;
			center("Enter the ISBN of the book");
			cout << setw(45) << " " << " >> ";

			while (!ISBN_validator(temp.ISBN)) {
				cout << setw(45) << " " << " >> ";
			}

			for (int i = 0; i < numberOfBooks; i++)
				if (temp.ISBN == b[i].ISBN)
					flag = true;

			if (flag) {
				cout << endl;
				center("ERROR! The title of the book has already been used.");
				center("Please change the title of the book.");
				cout << endl;
			}
		} while (flag);

		cout << endl;
		center("Are you certain you want \u001b[31m" + temp.ISBN + "\u001b[0m to be your book ISBN [Y/N]?:");
		cout << setw(45) << " " << " >> ";

		while (!char_validator(choice2)) {
			cout << setw(45) << " " << " >> ";
		}

		choice = choice2[0];
		choice = tolower(choice);

	} while (choice != 'y');
	//Book Author
	do {
		cout << endl;
		drawLine();
		cout << endl;

		cout << setw(40) << " " << "Rules: " << endl
			<< setw(40) << " " << "1. Author of the book should not be empty" << endl
			<< setw(40) << " " <<"2. Author of the book can contain one or more '.' character"<<endl
			<< endl;

		center("Enter the Author of the book");
		cout << setw(45) << " " << " >> ";

		while (!name_validator(temp.author)) {
			cout << setw(45) << " " << " >> ";
		}

		cout << endl;
		center("Are you certain you want \u001b[31m" + temp.author + "\u001b[0m to be your book author [Y/N]?:");
		cout << setw(45) << " " << " >> ";

		while (!char_validator(choice2)) {
			cout << setw(45) << " " << " >> ";
		}

		choice = choice2[0];
		choice = tolower(choice);

	} while (choice != 'y');
	//Book Publisher
	do {
		cout << endl;
		drawLine();
		cout << endl;

		cout << setw(40) << " " << "Rules: " << endl
			<< setw(40) << " " << "1. Publisher of the book should not be empty" << endl
			<< setw(40) << " " << "2. Publisher of the book can contain one or more '.' character" << endl
			<< endl;

		center("Enter the Publisher of the book");
		cout << setw(45) << " " << " >> ";

		while (!name_validator(temp.publisher)) {
			cout << setw(45) << " " << " >> ";
		}

		cout << endl;
		center("Are you certain you want \u001b[31m" + temp.publisher + "\u001b[0m to be your book publisher [Y/N]?:");
		cout << setw(45) << " " << " >> ";

		while (!char_validator(choice2)) {
			cout << setw(45) << " " << " >> ";
		}

		choice = choice2[0];
		choice = tolower(choice);

	} while (choice != 'y');
	//Book quantity
	do {
		cout << endl;
		drawLine();
		cout << endl;

		cout << setw(40) << " " << "Rules: " << endl
			<< setw(40) << " " << "1. Quantity of the book should not be empty" << endl
			<< setw(40) << " " << "2. Quantity of the book should be a number" << endl
			<< setw(40) << " " << "3. Quantity of the book should not contain '.' character" << endl
			<< setw(40) << " " << "4. Quantity of the book cannot be 0" << endl
			<< endl;

		center("Enter the Quantity of the book");
		cout << setw(45) << " " << " >> ";

		do {
			while (!int_validator(s)) {
				cout << setw(45) << " " << " >> ";
			}

			if (stoi(s) == 0) {
				cout << endl;
				center("Quantity cannot be 0");
				cout << endl;
				cout << setw(45) << " " << " >> ";
			}
		} while (stoi(s) == 0);

		cout << endl;
		center("Are you certain you want \u001b[31m" + s + "\u001b[0m to be your book quantity [Y/N]?:");
		cout << setw(45) << " " << " >> ";

		while (!char_validator(choice2)) {
			cout << setw(45) << " " << " >> ";
		}

		choice = choice2[0];
		choice = tolower(choice);

	} while (choice != 'y');

	temp.quantity = stoi(s);

	//Book Wholesale Cost
	do {
		cout << endl;
		drawLine();
		cout << endl;

		cout << setw(35) << " " << "Rules: " << endl
			<< setw(35) << " " << "1. Wholesale Cost of the book should not be empty" << endl
			<< setw(35) << " " << "2. Wholesale Cost of the book should or should not include one '.' character" << endl
			<< setw(35) << " " << "3. Wholesale Cost of the book should only consists of digits and '.' character" << endl
			<< setw(35) << " " << "4. Wholesale Cost of the book cannot be less than 10 cents" << endl
			<< endl;

		center("Enter the Wholesale Cost of the book");
		cout << setw(45) << " " << " >> ";

		do {
			while (!double_validator(s)) {
				cout << setw(45) << " " << " >> ";
			}

			if (stod(s) < 0.1) {
				cout << endl;
				center("Wholesale Cost cannot be less than 0.1");
				cout << endl;
				cout << setw(45) << " " << " >> ";
			}
		} while (stod(s) < 0.1);

		cout << endl;
		center("Are you certain you want \u001b[31m$" + s + "\u001b[0m to be the Wholesale Cost of your book [Y/N]?:");
		cout << setw(45) << " " << " >> ";

		while (!char_validator(choice2)) {
			cout << setw(45) << " " << " >> ";
		}

		choice = choice2[0];
		choice = tolower(choice);

	} while (choice != 'y');

	temp.wholesaleCost = stod(s);

	//retail cost
	do {
		cout << endl;
		drawLine();
		cout << endl;

		cout << setw(35) << " " << "Rules: " << endl
			<< setw(35) << " " << "1. Retail Cost of the book should not be empty" << endl
			<< setw(35) << " " << "2. Retail Cost of the book should or should not include one '.' character" << endl
			<< setw(35) << " " << "3. Retail Cost of the book should only consists of digits and '.' character" << endl
			<< setw(35) << " " << "4. Retail Cost of the book cannot be less than 10 cents" << endl
			<< endl;

		center("Enter the Retail Cost of the book");
		cout << setw(45) << " " << " >> ";

		do {
			while (!double_validator(s)) {
				cout << setw(45) << " " << " >> ";
			}

			if (stod(s) < 0.1) {
				cout << endl;
				center("Retail Cost cannot be less than 0.1");
				cout << endl;
				cout << setw(45) << " " << " >> ";
			}
		} while (stod(s) < 0.1);

		cout << endl;
		center("Are you certain you want \u001b[31m$" + s + "\u001b[0m to be the Retail Cost of your book [Y/N]?:");
		cout << setw(45) << " " << " >> ";

		while (!char_validator(choice2)) {
			cout << setw(45) << " " << " >> ";
		}

		choice = choice2[0];
		choice = tolower(choice);

	} while (choice != 'y');

	temp.retailCost = stod(s);

	return true;
}

void searched_term(int s_arr[]) {
	int num_of_terms, temp_num;
	string input;
	bool i_flag;

	//initialize array
	for (int i = 0; i < 7; i++)
		s_arr[i] = 0;

	center("What would you like to edit?");
	cout << endl
		<< setw(50) << " " << "Properties of book: " << endl
		<< endl
		<< setw(40) << " " << "1. Title" << endl
		<< setw(40) << " " << "2. ISBN" << endl
		<< setw(40) << " " << "3. Author" << endl
		<< setw(40) << " " << "4. Publisher" << endl
		<< setw(40) << " " << "5. Quantity" << endl
		<< setw(40) << " " << "6. Wholesale Cost" << endl
		<< setw(40) << " " << "7. Retail Cost" << endl
		<< endl;
	center("Please enter the number of columns you would like to edit");
	cout << setw(50) << " " << "Maximum: 7" << endl;

	do {
		cout << setw(45) << " " << " >> ";

		while (!int_validator(input)) { cout << setw(45) << " " << " >> "; }

		num_of_terms = stoi(input);

		if (num_of_terms < 1 || num_of_terms>7) {
			cout << endl;
			center("Your input has exceeded the range!");
			center("Please try again!");
			cout << endl;
		}
	} while (num_of_terms < 1 || num_of_terms>7);

	cout << endl;
	center("Enter the columns you would like to edit");

	for (int i = 0; i < num_of_terms; i++) {
		cout << endl
			<< setw(45) << " " << "Currently at: " << i + 1 << " term" << endl;
		do {
			i_flag = false;

			do {
				cout << setw(45) << " " << " >> ";

				while (!int_validator(input)) { cout << setw(45) << " " << " >> "; }

				temp_num = stoi(input);

				if (temp_num < 1 || temp_num>7) {
					cout << endl;
					center("Your input has exceeded the range!");
					center("Please try again!");
					cout << endl;
				}
			} while (temp_num < 1 || temp_num>7);

			for (int j = 0; j < i; j++)
				if (input == to_string(s_arr[j])) {
					i_flag = true;
					break;
				}

			if (i_flag) {
				cout << endl;
				center("You have repeated this in your search");
				center("Please choose again!");
				cout << endl;
			}

		} while (i_flag);

		s_arr[i] = stoi(input);
	}
}

void edit(int s_arr[], Book& bk) {
	int choice;
	string choice2, test1, test2, temp;
	bool flag;

	for (int i = 0; s_arr[i] != 0; i++) {
		switch (s_arr[i]) {
		case 1:
			//Book Title
			do {
				cout << endl;
				drawLine();
				cout << endl;

				cout << setw(40) << " " << "Rules: " << endl
					<< setw(40) << " " << "1. Title of the book should not be empty" << endl
					<< endl;

				do {
					flag = false;
					center("Enter the new title of the book");
					cout << setw(45) << " " << " >> ";

					while (!string_validator(temp)) {
						cout << setw(45) << " " << " >> ";
					}

					for (int i = 0; i < numberOfBooks; i++) {
						test1 = lower(temp);
						test2 = lower(b[i].title);
						if (test1 == test2)
							flag = true;
					}

					if (flag) {
						cout << endl;
						center("ERROR! The title of the book has already been used.");
						center("Please change the title of the book.");
						cout << endl;
					}
				} while (flag);

				cout << endl;
				center("Are you certain you want \u001b[31m" + temp + "\u001b[0m to be your new book title [Y/N]?:");
				cout << setw(45) << " " << " >> ";

				while (!char_validator(choice2)) {
					cout << setw(45) << " " << " >> ";
				}

				choice = choice2[0];
				choice = tolower(choice);

			} while (choice != 'y');
			bk.title = temp;
			break;
		case 2:
			//Book ISBN
			do {
				cout << endl;
				drawLine();
				cout << endl;

				cout << setw(35) << " " << "Rules: " << endl
					<< setw(35) << " " << "1. ISBN of the book should not be empty" << endl
					<< setw(35) << " " << "2. ISBN of the book should consists of only digits and hyphen characters" << endl
					<< setw(35) << " " << "3. ISBN of the book should be 17 characters " << endl
					<< setw(35) << " " << "4. ISBN of the book should have a format of XXX-X-XXX-XXXXX-X " << endl
					<< endl;

				do {
					flag = false;
					center("Enter the new ISBN of the book");
					cout << setw(45) << " " << " >> ";

					while (!ISBN_validator(temp)) {
						cout << setw(45) << " " << " >> ";
					}

					for (int i = 0; i < numberOfBooks; i++)
						if (temp == b[i].ISBN)
							flag = true;

					if (flag) {
						cout << endl;
						center("ERROR! The title of the book has already been used.");
						center("Please change the title of the book.");
						cout << endl;
					}
				} while (flag);

				cout << endl;
				center("Are you certain you want \u001b[31m" + temp + "\u001b[0m to be your new book ISBN [Y/N]?:");
				cout << setw(45) << " " << " >> ";

				while (!char_validator(choice2)) {
					cout << setw(45) << " " << " >> ";
				}

				choice = choice2[0];
				choice = tolower(choice);

			} while (choice != 'y');
			bk.ISBN = temp;
			break;
		case 3:
			//Book Author
			do {
				cout << endl;
				drawLine();
				cout << endl;

				cout << setw(40) << " " << "Rules: " << endl
					<< setw(40) << " " << "1. Author of the book should not be empty" << endl
					<< setw(40) << " " << "2. Author of the book can contain one or more '.' character" << endl
					<< endl;

				center("Enter the new Author of the book");
				cout << setw(45) << " " << " >> ";

				while (!name_validator(temp)) {
					cout << setw(45) << " " << " >> ";
				}

				cout << endl;
				center("Are you certain you want \u001b[31m" + temp + "\u001b[0m to be your new book author [Y/N]?:");
				cout << setw(45) << " " << " >> ";

				while (!char_validator(choice2)) {
					cout << setw(45) << " " << " >> ";
				}

				choice = choice2[0];
				choice = tolower(choice);

			} while (choice != 'y');
			bk.author = temp;
			break;
		case 4:
			//Book Publisher
			do {
				cout << endl;
				drawLine();
				cout << endl;

				cout << setw(40) << " " << "Rules: " << endl
					<< setw(40) << " " << "1. Publisher of the book should not be empty" << endl
					<< setw(40) << " " << "2. Publisher of the book can contain one or more '.' character" << endl
					<< endl;

				center("Enter the new Publisher of the book");
				cout << setw(45) << " " << " >> ";

				while (!name_validator(temp)) {
					cout << setw(45) << " " << " >> ";
				}

				cout << endl;
				center("Are you certain you want \u001b[31m" + temp + "\u001b[0m to be your new book publisher [Y/N]?:");
				cout << setw(45) << " " << " >> ";

				while (!char_validator(choice2)) {
					cout << setw(45) << " " << " >> ";
				}

				choice = choice2[0];
				choice = tolower(choice);

			} while (choice != 'y');
			bk.publisher = temp;
			break;
		case 5:
			//Quantity
			do {
				cout << endl;
				drawLine();
				cout << endl;

				cout << setw(40) << " " << "Rules: " << endl
					<< setw(40) << " " << "1. Quantity of the book should not be empty" << endl
					<< setw(40) << " " << "2. Quantity of the book should be a number" << endl
					<< setw(40) << " " << "3. Quantity of the book should not contain '.' character" << endl
					<< setw(40) << " " << "4. Quantity of the book cannot be 0" << endl
					<< endl;

				center("Enter the Quantity of the book");
				cout << setw(45) << " " << " >> ";

				do {
					while (!int_validator(temp)) {
						cout << setw(45) << " " << " >> ";
					}

					if (stoi(temp) == 0) {
						cout << endl;
						center("Quantity cannot be 0");
						cout << endl;
						cout << setw(45) << " " << " >> ";
					}
				} while (stoi(temp) == 0);

				cout << endl;
				center("Are you certain you want \u001b[31m" + temp + "\u001b[0m to be your book quantity [Y/N]?:");
				cout << setw(45) << " " << " >> ";

				while (!char_validator(choice2)) {
					cout << setw(45) << " " << " >> ";
				}

				choice = choice2[0];
				choice = tolower(choice);

			} while (choice != 'y');
			bk.quantity = stoi(temp);
			break;
		case 6:
			//wholesale cost
			do {
				cout << endl;
				drawLine();
				cout << endl;

				cout << setw(35) << " " << "Rules: " << endl
					<< setw(35) << " " << "1. Wholesale Cost of the book should not be empty" << endl
					<< setw(35) << " " << "2. Wholesale Cost of the book should or should not include one '.' character" << endl
					<< setw(35) << " " << "3. Wholesale Cost of the book should only consists of digits and '.' character" << endl
					<< setw(35) << " " << "4. Wholesale Cost of the book cannot be less than 10 cents" << endl
					<< endl;

				center("Enter the Wholesale Cost of the book");
				cout << setw(45) << " " << " >> ";

				do {
					while (!double_validator(temp)) {
						cout << setw(45) << " " << " >> ";
					}

					if (stod(temp) < 0.1) {
						cout << endl;
						center("Wholesale Cost cannot be less than 0.1");
						cout << endl;
						cout << setw(45) << " " << " >> ";
					}
				} while (stod(temp) < 0.1);

				cout << endl;
				center("Are you certain you want \u001b[31m$" + temp + "\u001b[0m to be the Wholesale Cost of your book [Y/N]?:");
				cout << setw(45) << " " << " >> ";

				while (!char_validator(choice2)) {
					cout << setw(45) << " " << " >> ";
				}

				choice = choice2[0];
				choice = tolower(choice);

			} while (choice != 'y');
			bk.wholesaleCost = stod(temp);
			break;
		case 7:
			//retail cost
			do {
				cout << endl;
				drawLine();
				cout << endl;

				cout << setw(35) << " " << "Rules: " << endl
					<< setw(35) << " " << "1. Retail Cost of the book should not be empty" << endl
					<< setw(35) << " " << "2. Retail Cost of the book should or should not include one '.' character" << endl
					<< setw(35) << " " << "3. Retail Cost of the book should only consists of digits and '.' character" << endl
					<< setw(35) << " " << "4. Retail Cost of the book cannot be less than 10 cents" << endl
					<< endl;

				center("Enter the Retail Cost of the book");
				cout << setw(45) << " " << " >> ";

				do {
					while (!double_validator(temp)) {
						cout << setw(45) << " " << " >> ";
					}

					if (stod(temp) < 0.1) {
						cout << endl;
						center("Retail Cost cannot be less than 0.1");
						cout << endl;
						cout << setw(45) << " " << " >> ";
					}
				} while (stod(temp) < 0.1);

				cout << endl;
				center("Are you certain you want \u001b[31m$" + temp + "\u001b[0m to be the Retail Cost of your book [Y/N]?:");
				cout << setw(45) << " " << " >> ";

				while (!char_validator(choice2)) {
					cout << setw(45) << " " << " >> ";
				}

				choice = choice2[0];
				choice = tolower(choice);

			} while (choice != 'y');
			bk.retailCost = stod(temp);
			break;
		}
	}
}

int search(string text) {
	text = lower(text);
	for (int i = 0; i < numberOfBooks; i++) {
		string title = lower(b[i].title);
		if (title == text || b[i].ISBN == text)
			return i;
	}
	return -1;
}
//make a quit flag for edit book
// int exceed int max, double exceed double max
//Do the exceed 2000
void cashier() {

	string date = "", ISBN, title, s, choice2;
	char choice;
	bool s_flag, found, e_flag, out_of_stock_flag, c_flag(false);

	Book temp;
	int current_book(0), quantity, order_id;
	double total(0);
	transaction record[50];

	e_flag = readOrder("transaction.txt", order_id);

	do {
		do {
			system("cls");
			s = "";
			temp = Book();
			s_flag = found = out_of_stock_flag = false;
			cout << endl;
			center("Study Smart Book Store");
			center("Cashier Module");
			drawLine();

			if (current_book == 50) {
				cout << endl;
				center("Transaction Limit Reached. No books can be processed any more");
				cout << endl;
				break;
			}

			for (int i = 0; i < numberOfBooks; i++)
				if (b[i].quantity > 0)
					out_of_stock_flag = true;

			if (!out_of_stock_flag) {
				cout << endl;
				center("All books are currently out of stock!");
				cout << endl;
				break;
			}

			cout << endl;
			center("Number of Books Left for transaction: " + to_string(50 - current_book));

			cout << endl
				<< setw(50) << " " << "Total Amount: $"
				<< fixed << setprecision(2)
				<< total
				<< endl;

			cout << endl
				<< setw(40) << " " << "Order ID: " << order_id + 1 << endl
				<< endl;

			if (date == "") {
				cout << setw(40) << " " << "Date: ";
				while (!date_validator(date)) {
					cout << setw(40) << " " << " >> ";
				}
			}
			else
				cout << setw(40) << " " << "Date: " << date << endl;

			cout << endl
				<< setw(40) << " " << "Please enter which element to be searched" << endl
				<< endl
				<< setw(40) << " " << "1 - Title" << endl
				<< endl
				<< setw(40) << " " << "2 - ISBN" << endl
				<< endl;

			do {
				cout << setw(40) << " " << "Enter your choice: ";

				while (!char_validator(choice2)) {
					cout << setw(40) << " " << " >> ";
				}

				choice = choice2[0];

				if (choice != '1' && choice != '2') {
					cout << endl;
					center("That wasn't within the options!");
					cout << endl;
				}
			} while (choice != '1' && choice != '2');

			switch (choice) {
			case '1':
				cout << endl
					<< setw(40) << " " << "Title: ";
				do {
					while (!string_validator(title)) {
						cout << setw(40) << " " << " >> ";
					}

					s_flag = search(title, temp);

					if (!s_flag) {
						cout << endl;
						center("Error! This title does not exist within the database");
						center("Please Try Again");
						cout << endl
							<< setw(40) << " " << " >> ";
						continue;
					}

					if (temp.quantity == 0) {
						cout << endl;
						center("Error! This book is currently out of stock");
						center("Please Try Again");
						cout << endl
							<< setw(40) << " " << " >> ";
					}
				} while (!s_flag || temp.quantity == 0);

				cout << endl
					<< setw(40) << " " << "ISBN: " << temp.ISBN << endl;
				break;
			case '2':
				cout << endl
					<< setw(40) << " " << "ISBN: ";
				do {
					while (!ISBN_validator(ISBN)) {
						cout << setw(40) << " " << " >> ";
					}

					s_flag = search(ISBN, temp);

					if (!s_flag) {
						cout << endl;
						center("Error! This ISBN does not exist within the database");
						center("Please Try Again");
						cout << endl
							<< setw(40) << " " << " >> ";
						continue;
					}

					if (temp.quantity == 0) {
						cout << endl;
						center("Error! This book is currently out of stock");
						center("Please Try Again");
						cout << endl
							<< setw(40) << " " << " >> ";
					}
				} while (!s_flag || temp.quantity == 0);

				cout << endl
					<< setw(40) << " " << "Title: " << temp.title << endl;
				break;
			}

			cout << endl
				<< setw(40) << " " << "Quantity in stock: " << temp.quantity << endl
				<< endl
				<< setw(40) << " " << "Quantity: ";

			do {
				while (!int_validator(s)) {
					cout << setw(40) << " " << " >> ";
				}

				if (stoi(s) <= 0) {
					cout << endl;
					center("Error! Quantity cannot be 0");
					center("Please try again");
					cout << endl
						<< setw(40) << " " << " >> ";
				}

				if (stoi(s) > temp.quantity) {
					cout << endl;
					center("Error! The quantity you have entered is more than the quantity in inventory");
					center("Please try again");
					cout << endl
						<< setw(40) << " " << " >> ";
					continue;
				}

				if ((total + stoi(s) * temp.retailCost) * 1.06 > 2000) {
					cout << endl;
					center("Error! Amount limit reached");
					center("Please try again");
					cout << endl
						<< setw(40) << " " << " >> ";
				}
			} while (stoi(s) <= 0 || stoi(s) > temp.quantity || (total + stoi(s) * temp.retailCost) * 1.06 > 2000);
			quantity = stoi(s);

			for (int i = 0; i < numberOfBooks; i++)
				if (b[i].title == temp.title) {
					b[i].quantity -= quantity;
					break;
				}

			cout << endl
				<< setw(40) << " " << "Price: $ " << temp.retailCost;

			if (current_book > 0) {
				for (int i = 0; i < current_book; i++)
					if (record[i].b.title == temp.title) {
						total -= record[i].total();
						record[i].quantity += quantity;
						total += record[i].total();
						found = true;
					}
			}

			if (!found) {
				record[current_book++].b = temp;
				record[current_book - 1].quantity = quantity;
				total += record[current_book - 1].total();
			}

			c_flag = true;

			cout << endl
				<< endl
				<< setw(40) << " " << "Continue next book [Y/N]: ";

			while (!char_validator(choice2)) {
				cout << setw(40) << " " << " >> ";
			}

			choice = choice2[0];
			choice = tolower(choice);
		} while (choice != 'n');

		if (c_flag) {
			receipt(record, current_book, date, order_id + 1);

			outFile("books.txt");
		}
		else {
			center("TRANSACTION WAS NOT ABLE TO BE COMPLETE SUCCESSFULLY");
			cout << endl;
			drawLine();
			getline(cin, s);
			break;
		}

		cout << endl;
		center("Do you want to enter the next sale [Y/N]?:");
		cout << setw(45) << " " << " >> ";

		while (!char_validator(choice2)) {
			cout << setw(45) << " " << " >> ";
		}

		choice = choice2[0];
		choice = tolower(choice);
	}while (choice != 'n');
}

void receipt(transaction r[], int count,string date,int order_id) {
	string choice2;
	char choice;

	double total = 0;

	system("cls");
	cout << endl;
	center("Study Smart Book Store");
	drawLine();

	cout << endl
		<< setw(10) << " " << "Date: " << date << setw(55) << " " << "Order: " << order_id << endl
		<< endl
		<< left
		<< setw(10) << " " << setw(3) << "Qty" << setw(5) << " " << setw(20) << "ISBN" << setw(40) << "Title" << setw(15) << "Price" << setw(15) << "Total" << endl;

	for (int i = 0; i < count; i++) {
		cout << endl;
		r[i].print(cout);
		cout << endl;
		total += r[i].total();
	}

	cout << endl
		<< endl
		<< fixed << setprecision(2)
		<< setw(80) << " " << setw(10) << "Sub Total" << setw(5) << " " << left << "$" << setw(6) << right << total << endl
		<< setw(80) << " " << setw(10) << "Tax" << setw(5) << " " << left << "$" << setw(6) << right << total * 0.06 << endl
		<< setw(80) << " " << setw(10) << "Total" << setw(5) << " " << left << "$" << setw(6) << right << total * 1.06 << endl
		<< endl;
	center("Thank you for Shopping at smart study Land!");
	cout << endl;
	drawLine();

	ofstream output("transaction.txt", ofstream::app);
	output << order_id << endl
		<< "Date: " << date << endl
		<< "Number of Books Sold: " << count << endl;
	for (int i = 0; i < count; i++) {
		r[i].print(output);
		output << endl;
	}
	output << "Total: $" << total * 1.06 << endl
		<< endl;
	output.close();
}

bool readOrder(string filename,int& n) {
	string trash;
	int num;
	ifstream input(filename);
	int current_order = 0;
	if (input) {
		while (!input.eof()) {
			num = 0;
			input >> current_order;
			input.ignore();
			getline(input, trash);
			input >> trash >> trash >> trash >> trash >> num;
			input.ignore();
			for (int i = 0; i < num; i++)
				getline(input, trash);
			getline(input, trash);
		}
		input.close();
		n = current_order;
		return true;
	}
	else {
		n = 1000;
		return false;
	}
}

void export_to_html() {
	cout << endl;
	center("Study Smart Book Store");
	center("HTML Table");
	drawLine();
	cout << endl;
	center("Exporting...");
	cout << endl;
	center("Export complete!");
	cout << endl;
	center("book_records.html has been successfully created!");
	cout << endl;
	drawLine();
	cout << endl;

	ofstream output("book_records.html");
	output << "<!DOCTYPE html>" << endl
		<< "<html lang=\"en\">" << endl
		<< "<head>" << endl
		<< "<meta charset=\"UTF - 8\">" << endl
		<< "<meta name=\"viewport\" content=\"width = device-width, initial-scale = 1.0\">" << endl
		<< "<title>Book Records</title>" << endl
		<< "<style>" << endl
		<< "table, th, td{\nborder: 1px solid black;\n}" << endl
		<< "th, td{\npadding: 15px;\n}" << endl
		<< "</style>" << endl
		<< "</head>" << endl
		<< "<body>" << endl
		<< "<h1 style=\"text-align:center\">Book Records Table</h1>" << endl
		<< "<table align=\"center\" style=\"border-collapse: collapse;\">" << endl
		<< "<tr>" << endl
		<< "<th></th>" << endl
		<< "<th>Title</th>" << endl
		<< "<th>ISBN</th>" << endl
		<< "<th>Author</th>" << endl
		<< "<th>Publisher</th>" << endl
		<< "<th>Quantity</th>" << endl
		<< "<th>Wholesale Cost</th>" << endl
		<< "<th>Retail Cost</th>" << endl
		<< "</tr>" << endl;
	for (int i = 0; i < numberOfBooks; i++) {
		b[i].export_to_table(output, i);
	}
	output << "</table>" << endl
		<< "</body>" << endl
		<< "</html>" << endl;
	output.close();
}