#include <iostream>
#include <string>

using namespace std;
using std::cout;
using std::cin;

const int row = 13;
const int col = 6;

string seatDigitCheck = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
string seatLowerDigitCheck = "abcdefghijklmnopqrstuvwxyz";
string rowNumberCheck[13] = { "1","2","3","4","5","6","7","8","9","10","11","12","13" };

class Passenger {
private:
	string Raw;
	string Name;
	string Id;
	string Seat_num;
	string Row;
	string Col;
public:
	Passenger() {
		Row = " ";
		Col = " ";
	}
	Passenger(string data) {
		cout << "added new passenger.";
	}
	Passenger(string name, string id, string seat_num) {
		Name = name;
		Id = id;
		Seat_num = seat_num;
	}
	void showDetail() {
		cout << Name << "/" << Id << "/" << Seat_num << endl;
	}
	string getName(string name) {
		Name = name;
		return Name;
	}
	string getId(string id) {
		Id = id;
		return Id;
	}
	string getSeat(string seat_num) {
		Seat_num = seat_num;
		return seat_num;
	}
	string getRow(string seat_num) {
		int pos = seat_num.length()-1;

		string last = seat_num.substr(pos);

		size_t found = seat_num.find_last_of(last);
		string row = seat_num.substr(0, found);
		Row = row;
		//cout << Row << endl;
		return row;
	}
	string getCol(string seat_num) {
		int pos = seat_num.length();

		string last = seat_num.substr(pos - 1);
		size_t found = seat_num.find_last_of(last);

		string col = seat_num.substr(found);
		Col = col;
		//cout << Col << endl;
		return col;
	}
	string catAll() {
		string connector = "/";
		string raw;
		raw = Name + connector + Id + connector + Seat_num;
		Raw = raw;
		return raw;
	}

	void prtAtt() {
		cout << Row << Col;
	}

	int isOcup() {
		int status;
		if (Row != " " && Col != " ")
		{
			status = 0;
		}
		else
		{
			status = 1;
		}
		return status;
	}

	void reset() {
		Raw = "";
		Name = "";
		Id = "";
		Seat_num = "";
		Row = " ";
		Col = " ";
	}

	string expName() {
		return Name;
	}

	string expId() {
		return Id;
	}

	string expSeat() {
		return Row + Col;
	}

	~Passenger()
	{

	}
};

bool rowCheck(string input) {
	int string_lenght = input.length();
	int inputType = (string_lenght == 2) ? 2 : (string_lenght == 3) ? 3 : 0;
	int matchCount = 0;
	if (inputType == 0)
	{
		return false;
	}
	string rowString = (inputType == 2) ? input.substr(0, 1) : (inputType == 3) ? input.substr(0, 2) : " ";
	for (int i = 0; i < row; i++)
	{
		if (rowString == rowNumberCheck[i])
		{
			matchCount++;
		}
	}
	if (matchCount == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int idCheck(Passenger obj[row][col], string id) {
	int id_count = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++) {
			if (obj[i][j].expId() == id)
			{
				id_count++;
			}
		}
	}
	return id_count;
}

int seatRepeatedCheck(Passenger obj[row][col], string seat) {
	int seat_count = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++) {
			if (obj[i][j].expSeat() == seat)
			{
				seat_count++;
			}
		}
	}
	return seat_count;
}


int setColIndex(string indexString) {
	int index = 0;
	if (indexString == "A" )
	{
		index = 1;
	}
	else if (indexString == "B" )
	{
		index = 2;
	}
	else if (indexString == "C" )
	{
		index = 3;
	}
	else if (indexString == "D" )
	{
		index = 4;
	}
	else if (indexString == "E" )
	{
		index = 5;
	}
	else if (indexString == "F" )
	{
		index = 6;
	}
	else
	{
		index = -1;
	}
	return index;
}

int NumOfLetterCheck(string input) {
	int letter_count = 0;
	for (unsigned int i = 0; i < input.length(); i++)
	{
		for (int j = 0; j < 26; j++) {
			if (input[i] == seatDigitCheck[j] || input[i] == seatLowerDigitCheck[j])
			{
				letter_count++;
			}
		}
	}
	return letter_count;
}

int first_digit_check(string input) {
	int first_digit_stat = 0;
	for (int i = 0; i < 26; i++)
	{
		if (input[0] == seatDigitCheck[i] || input[0] == seatLowerDigitCheck[i]) {
			first_digit_stat++;
		}
	}
	return first_digit_stat;
}

int checkSpace(string input) {
	int leng = input.length();
	int blankCount = 0;
	for (int i = 0; i < leng; i++)
	{
		if (input[i] == ' ')
		{
			blankCount++;
		}
	}
	return blankCount;
}

bool checkBatchSeat(string input) {
	int len = input.length();
	int count = 0;
	for (int i = 0; i < len; i++)
	{
		if (input[i] == '/' or input[i] == '\'') {
			count++ ;
		}
	}
	if (count == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int colCheck(string input) {
	int count = 0;

	for (int i = 0; i < 6; i++)
	{
		if (input[input.length() - 1] == seatDigitCheck[i])
			count++;
	}
	return count;
}

bool batchRepeatCheck( string array[], string input) {
	int count = 0;
	for (int i = 0; i < row*col; i++)
	{
		if (input == array[i]) {
			count++;
		}
	}
	if (count == 0)
	{
		return true;
	}
	else {
		return false;
	}
}

int main()
{
	string choice;
	string name;
	string id;
	string seat_num;
	Passenger tmp_passenger;

	string batchString;
	string batchName = "*";
	string batchID = "*";
	string batchSeat = "*";
	string batchIDRecord[row * col] = {" "};
	//int IDCount = 0;
	string batchSeatRecord[row * col] = {" "};
	//int SeatCount = 0;

	int batchCount = 0;
	int errorCount = 0;
	int successCount = 0;


	Passenger fin_detail[row][col];

	int colIndex = -1;
	int rowIndex = -1;

	string indexstring;

	string exit_con;

	int Raw_row;
	do {
		cout << "welcome to the system" << endl;
		cout << "*** main menu ***" << endl;
		cout << "[1] Add an assignment" << endl;
		cout << "[2] Delete an assignment" << endl;
		cout << "[3] Add assignments in batch" << endl;
		cout << "[4] Show latest seating plan" << endl;
		cout << "[5] Show details" << endl;
		cout << "[6] Exit" << endl;
		cout << "*****************" << endl;
		cout << "Option (1-6): ";
		std::cin >> choice;

		cout << "\n\n";

		if (choice=="1") {
			cout << "enter passenger's name, id and seat code: "<< endl;
			cout << "Name: ";
			std::cin >> name;

			cout << "ID: ";
			cin >> id;

			if (checkSpace(id) != 0)
			{
				cout << "ID cannot contain any space, the progress is aborted." << endl;
				continue;
			}

			if (idCheck(fin_detail, id) != 0)
			{
				cout << "\nID already exists, the progress is aborted.\n" << endl;
				continue;
			}

			cout << "Seat number: ";
			cin >> seat_num;

			// check the length of input, only 2 - 3 digit is accepted.
			if (seat_num.length() > 3 or seat_num.length() < 2)
			{
				cout << "\nOnly 2 or 3 digit of seat code can be accepted, the progress is aborted.\n" << endl;
				continue;
			}

			if (checkSpace(seat_num) != 0)
			{
				cout << "ID cannot contain any space, the progress is aborted." << endl;
				continue;
			}

			if (first_digit_check(seat_num) != 0)
			{
				cout << "\nThe first digit of seat code should not be a letter, the progress is aborted.\n" << endl;
				continue;
			}

			if (NumOfLetterCheck(seat_num) != 1)
			{
				cout << "\nThe seat code entered contains more than one letter or no letter, which is not allowed, the progress is aborted.\n" << endl;
				continue;
			}

			if (rowCheck(seat_num) != 1)
			{
				cout << "\nYour row number in the seat code input is out of the range of 1 to 13, the progress is aborted.\n" << endl;
				continue;
			}

			// check the availability of a seat, return 0 if the desire seat is available.
			if (seatRepeatedCheck(fin_detail, seat_num) != 0)
			{
				cout << "\nSeat occupied, the progress is aborted.\n" << endl;
				continue;
			}

			Raw_row = stoi(tmp_passenger.getRow(seat_num));
			rowIndex = Raw_row - 1;

			indexstring = tmp_passenger.getCol(seat_num);

			colIndex = setColIndex(indexstring) - 1;

			if (colIndex < 0)
			{
				cout << "\nYou may entered lowercase letter or letter not among A to F, the progress is aborted.\n" << endl;
				continue;
			}

			fin_detail[rowIndex][colIndex].getId(tmp_passenger.getId(id));
			fin_detail[rowIndex][colIndex].getName(tmp_passenger.getName(name));
			fin_detail[rowIndex][colIndex].getSeat(tmp_passenger.getSeat(seat_num));

			fin_detail[rowIndex][colIndex].getCol(seat_num);
			fin_detail[rowIndex][colIndex].getRow(seat_num);


			
		}
		else if (choice == "2")
		{
			string id_del = "*";
			
			int name_del_stat = 0;
			int id_del_stat = 0;

			cout << "Data deletion sequence activated." << endl;
			cout << "Enter user's passport ID to match the record you want to delete: " << endl;
			cin >> id_del;
			string del_choice;

			cout << "\nThe following are matched data. If there are no matched record, the list shows nothing: " << endl;

			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < col; j++) {
					if (fin_detail[i][j].expId() == id_del)
					{
						cout << fin_detail[i][j].expName() << "/" << fin_detail[i][j].expId() << endl;
						name_del_stat++;
						id_del_stat++;
					}
				}
			}
			cout << id_del_stat << " record(s) found.\n" << endl;
			if (id_del_stat > 0)
			{
				cout << "Delete all records that match the search result? ([y]es or [n]o)" << endl;
				cin >> del_choice;
				if (del_choice == "y")
				{
					for (int i = 0; i < row; i++)
					{
						for (int j = 0; j < col; j++) {
							if (fin_detail[i][j].expId() == id_del)
							{
								fin_detail[i][j].reset();
								cout << "Record Deleted." << endl;
							}
						}
					}
				}
			}
			else
			{
				cout << "No records to delete." << endl;
			}
		}
		else if (choice == "3")
		{
			cout << "Enter data in the format of [name/id/seat code]: \n" ;
			string temp[500];
			string success[500];
			string failed[500];
			batchCount = 0;
			errorCount = 0;
			successCount = 0;
			
			// check the format of input
			// all incorrect format of input will be moved to failed list
			// inputs that passed the check will be moved to success list
			do
			{
				// initialize all variable for the loop
				batchName = " ";
				batchID = " ";
				batchSeat = " ";
				batchString = " ";

				string temp = " ";

				int len = 0;
				int pos = 0;

				cin >> batchString;
				if (batchString =="0")
				{
					continue;
				}

				temp = batchString;

				pos = temp.find_first_of("/");
				batchName = temp.substr(0, pos);
				len = batchName.length();

				if (pos != -1 and len > 0)
				{
					cout << "Name received" << endl;
				}
				else
				{
					cout << "No name" << endl;
					failed[errorCount] = batchString;
					errorCount++;
					batchString = " ";
					temp = " ";
					continue;
				}
				len = batchName.length();
				temp.erase(temp.find(batchName), len + 1);


				pos = temp.find_first_of("/");
				batchID = temp.substr(0, pos);

				len = batchID.length();

				if (pos != -1 and len>0)
				{
					cout << "ID received\n";
					if (idCheck(fin_detail, batchID) != 0 or batchRepeatCheck(batchIDRecord, batchID) == false)
					{
						//cout << "\nID already exists or empty, the progress is aborted.\n" << endl;
						cout << "ID invalid" << endl;
						failed[errorCount] = batchString;
						errorCount++;
						batchString = " ";
						temp = " ";
						continue;
					}
				}
				else
				{
					cout << "No id" << endl;
					failed[errorCount] = batchString;
					errorCount++;
					batchString = " ";
					temp = " ";
					continue;
				}
				batchIDRecord[batchCount] = batchID;
				temp.erase(temp.find(batchID), len + 1);

				pos = 0;
				batchSeat = temp;
				len = batchSeat.length();

				if (checkBatchSeat(batchSeat) != 0 and len>0)
				{
					cout << "No unexpected \'/\'" << endl;
					if (len > 3 or len < 2)
					{
						//cout << "\nOnly 2 or 3 digit of seat code can be accepted, the progress is aborted.\n" << endl;
						cout << "Length of seat code is not in range(2-3)." << endl;
						failed[errorCount] = batchString;
						errorCount++;
						batchString = " ";
						temp = " ";

						continue;
					}

					if (first_digit_check(batchSeat) != 0)
					{
						cout << "The first digit is not a number" << endl;
						failed[errorCount] = batchString;
						errorCount++;
						batchString = " ";
						temp = " ";
						continue;
					}

					if (rowCheck(batchSeat) == 0)
					{
						cout << "Cant pass row check" << endl;
						failed[errorCount] = batchString;
						errorCount++;
						batchString = " ";
						temp = " ";

						continue;
					}

					if (NumOfLetterCheck(batchSeat) != 1)
					{
						cout << "There are too many letter in the seat code\n";
						failed[errorCount] = batchString;
						errorCount++;
						batchString = " ";
						temp = " ";

						continue;
					}

					// check the availability of a seat, return 0 if the desire seat is available.
					if (seatRepeatedCheck(fin_detail, batchSeat) != 0 or batchRepeatCheck(batchSeatRecord, batchSeat) == false)
					{
						cout << "Seat occupied \n";
						failed[errorCount] = batchString;
						errorCount++;
						batchString = " ";
						temp = " ";
						continue;
					}

					if (colCheck(batchSeat) != 1)
					{
						cout << "The letter received is unexpected, or there is no letter\n";
						failed[errorCount] = batchString;
						errorCount++;
						batchString = " ";
						temp = " ";
						continue;
					}
				}
				else {
					cout << "Have extra \'/\' or no seat code." << endl;
					failed[errorCount] = batchString;
					errorCount++;
					batchString = " ";
					temp = " ";
					continue;
				}

				temp.erase(temp.find(batchSeat), len + 1);

				success[successCount] = batchString;
				successCount++;
				batchString = " ";
				temp = " ";
			} while (batchString != "0");
			
			cout << "\n==== The following(s) is/are request(s) that violates at least one check: ====" << endl;

			for (int i = 0; i < errorCount; i++)
			{
				cout << failed[i] << endl;
			}

			cout << "\n==== The following(s) is/are request(s) that do not violate any check: ====" << endl;

			for (int i = 0; i < successCount; i++)
			{
				cout << success[i] << endl;
			}
			string crt3_choice;

			do
			{
				cout << "\nCommit successful request(s)? (enter [y]es to commit successful request(s) or [n]o to abort) \n";
				cout << "CAUTION: You have only ONE chance to commit those successful requests. \nIf you enter \'n\' in this section, all successful requests will be LOST.\n";
				cin >> crt3_choice;
				if (crt3_choice == "y")
				{
					for (int i = 0; i < successCount; i++) {
						int pos = 0;
						int len = 0;

						pos = success[i].find_first_of("/");
						batchName = success[i].substr(0, pos);
						len = batchName.length();
						success[i].erase(success[i].find(batchName), len + 1);


						pos = success[i].find_first_of("/");
						batchID = success[i].substr(0, pos);
						len = batchID.length();
						success[i].erase(success[i].find(batchID), len + 1);

						batchSeat = success[i];

						Raw_row = stoi(tmp_passenger.getRow(batchSeat));
						rowIndex = Raw_row - 1;

						indexstring = tmp_passenger.getCol(batchSeat);

						colIndex = setColIndex(indexstring) - 1;

						fin_detail[rowIndex][colIndex].getId(tmp_passenger.getId(batchID));
						fin_detail[rowIndex][colIndex].getName(tmp_passenger.getName(batchName));
						fin_detail[rowIndex][colIndex].getSeat(tmp_passenger.getSeat(batchSeat));

						fin_detail[rowIndex][colIndex].getCol(batchSeat);
						fin_detail[rowIndex][colIndex].getRow(batchSeat);

						success[i] = "*";
					}
					successCount = 0;
					cout << "Commit successful.\n\n";
					break;
				}

				cout << "No such option, please anter again. ";
			} while (crt3_choice != "y" and crt3_choice != "n");

			if (errorCount == 0)
			{
				cout << "No failed request(s) detected.\n\n";
			}

			while (errorCount > 0)
			{
				cout << "Failed requests detected, modify?\n\n";
				cout << "Enter [y]es to modify, [n]o to leave.\n\n";
				cout << "CAUTION [1]: ALL FAILED requests can NOT be retrieved again, once you have chosen [n] as your option.\n\n";
				string correctionChoice;
				cin >> correctionChoice;
				if (correctionChoice == "n")
				{
					break;
				}
				if (correctionChoice == "y")
				{
					for (int i = 0; i < errorCount;i++ ) {
						string fixName;
						string fixID;
						string fixSeat;
						string fixString;

						cout << "Current failed request: " << failed[i] << endl;

						cout << "Please enter passenger's name: ";
						cin >> fixName;

						cout << "Please enter passenger's ID: ";
						cin >> fixID;

						cout << "Please enter passenger's seat code: ";
						cin >> fixSeat;

						fixString = fixName + '/' + fixID + '/' + fixSeat;

						if (fixName.length()<1)
						{
							failed[i] = fixString;
							continue;
						}

						if (fixID.length()<1 or checkSpace(fixID) != 0)
						{
							failed[i] = fixString;
							continue;
						}
						if (idCheck(fin_detail, fixID)!=0 or batchRepeatCheck(batchIDRecord, fixID)==false)
						{
							failed[i] = fixString;
							continue;
						}
						int len = fixSeat.length();
						if (checkBatchSeat(fixSeat) != 0 and len > 0)
						{
							cout << "No unecpected \'/\'" << endl;
							if (len > 3 or len < 2)
							{
								//cout << "\nOnly 2 or 3 digit of seat code can be accepted, the progress is aborted.\n" << endl;
								cout << "Length of seat code is not in range(2-3)." << endl;
								failed[i] = fixString;
								continue;
							}

							if (first_digit_check(fixSeat) != 0)
							{
								cout << "The first digit is not a number" << endl;
								failed[i] = fixString;
								continue;
							}

							if (rowCheck(fixSeat) == 0)
							{
								cout << "Cant pass row check" << endl;
								failed[i] = fixString;
								continue;
							}

							if (NumOfLetterCheck(fixSeat) != 1)
							{
								cout << "There are too many letter in the seat code\n";
								failed[i] = fixString;
								continue;
							}

							// check the availability of a seat, return 0 if the desire seat is available.
							if (seatRepeatedCheck(fin_detail, fixSeat) != 0 or batchRepeatCheck(batchSeatRecord, fixSeat) == false)
							{
								cout << "Seat occupied \n";
								failed[i] = fixString;
								continue;
							}

							if (colCheck(fixSeat) != 1)
							{
								cout << "The letter received is unexpected, or there is no letter\n";
								failed[i] = fixString;
								continue;
							}
						}	
						success[i] = fixString;
						successCount++;
					}
				}
				errorCount = 0;
			}

			for (int i = 0; i < successCount; i++)
			{
				batchName = " ";
				batchID = " ";
				batchSeat = " ";

				int pos = 0;
				int len = 0;

				pos = success[i].find_first_of("/");
				batchName = success[i].substr(0, pos);
				len = batchName.length();
				success[i].erase(success[i].find(batchName), len + 1);


				pos = success[i].find_first_of("/");
				batchID = success[i].substr(0, pos);
				len = batchID.length();
				success[i].erase(success[i].find(batchID), len + 1);

				batchSeat = success[i];

				Raw_row = stoi(tmp_passenger.getRow(batchSeat));
				rowIndex = Raw_row - 1;

				indexstring = tmp_passenger.getCol(batchSeat);

				colIndex = setColIndex(indexstring) - 1;

				fin_detail[rowIndex][colIndex].getId(tmp_passenger.getId(batchID));
				fin_detail[rowIndex][colIndex].getName(tmp_passenger.getName(batchName));
				fin_detail[rowIndex][colIndex].getSeat(tmp_passenger.getSeat(batchSeat));

				fin_detail[rowIndex][colIndex].getCol(batchSeat);
				fin_detail[rowIndex][colIndex].getRow(batchSeat);

				success[i] = "*";

			}

			batchCount = 0;
			errorCount = 0;
			successCount = 0;
		}
		else if (choice == "4")
		{
			for (int i = 0; i <= col; i++)
			{
				if (i == 0) {
					cout << "\t";
				}
				else
				{
					cout << seatDigitCheck[i-1] << "\t";
				}
			}
			cout << endl;
			for (int i = 0; i < row; i++)
			{
				cout << i + 1 << "\t";
				for (int j = 0; j < col; j++) {
					if (fin_detail[i][j].isOcup() == 0)
					{
						cout << "X\t";
					}
					else
					{
						cout << "*\t";
					}
				}
				cout << endl;
			}
		}
		else if (choice =="5")
		{
			do
			{
				cout << "*** Details ***" << endl;
				cout << "[1] Passenger" << endl;
				cout << "[2] Class" << endl;
				cout << "[3] Back" << endl;
				cout << "*****************" << endl;
				cout << "Option (1-3): " << endl;
				cin >> choice;
				if (choice == "1")
				{
					int search_stat = 0;
					string search_key;
					cout << "Please enter an ID to list the details of that passenger: ";
					cin >> search_key;
					for (int i = 0; i < row; i++)
					{
						for (int j = 0; j < col; j++) {
							if (fin_detail[i][j].expId() == search_key)
							{
								cout << fin_detail[i][j].expName() << "/" << fin_detail[i][j].expId() << "/" << fin_detail[i][j].expSeat() << endl;
								search_stat++;
							}
						}
					}
					cout << search_stat << " passenger found." << endl;
				}
				else if (choice == "2")
				{
					char crt5_choice;
					char classType[3] = { 'F','B','E' };
					cout << "Please enter which type of seats you would like to show: ([F]irst class, [B]usiness, [E]conomy) ";
					
					cin >> crt5_choice;
					int search_key = (crt5_choice == classType[0]) ? 1 : (crt5_choice == classType[1]) ? 2 : (crt5_choice == classType[2]) ? 3 : 0;
					switch (search_key)
					{
					case 1:
						cout << "The followings are seat status from 1A to 2F." << endl;
						for (int i = 0; i < 2; i++)
						{
							for (int j = 0; j < 6; j++)
							{
								if (fin_detail[i][j].isOcup() == 1)
								{
									cout << "vacant" << endl;
								}
								else
								{
									cout << fin_detail[i][j].expName() << "/" << fin_detail[i][j].expId() << "/" << fin_detail[i][j].expSeat() << endl;
								}
							}
						}
						break;
					case 2:
						cout << "The followings are seat status from 3A to 7F." << endl;

						for (int i = 2; i < 7; i++)
						{
							for (int j = 0; j < 6; j++)
							{
								if (fin_detail[i][j].isOcup() == 1)
								{
									cout << "vacant" << endl;
								}
								else
								{
									cout << fin_detail[i][j].expName() << "/" << fin_detail[i][j].expId() << "/" << fin_detail[i][j].expSeat() << endl;
								}
							}
						}
						break;
					case 3:
						cout << "The followings are seat status from 8A to 13F." << endl;

						for (int i = 7; i < 13; i++)
						{
							for (int j = 0; j < 6; j++)
							{
								if (fin_detail[i][j].isOcup() == 1)
								{
									cout << "vacant" << endl;
								}
								else
								{
									cout << fin_detail[i][j].expName() << "/" << fin_detail[i][j].expId() << "/" << fin_detail[i][j].expSeat() << endl;
								}
							}
						}
						break;
					default:
						cout << "No such class type, aborting" << endl;
						break;
					}
				}
				else if (choice == "3")
				{
					cout << "\nIs going back to the main menu... \n" << endl;
				}
				else
				{
					cout << "No such option, please check your input." << endl;
				}
			} while (choice != "3");
		}
		else if (choice == "6")
		{
			cout << "This operation will discard all changes and terminate the program, are you sure? (type \"y\" to confirm): " << endl;
			cin >> exit_con;
			if (exit_con == "y")
			{
				cout << "Program terminates. Good bye!" << endl;
				return 0;
			}
			else {
				// reset the choice content for next input
				choice = "*";
				continue;
			}
		}
		else
		{
			cout << "\nNo such option." << endl;
		}
	} while (choice != "6" );

	return 0;
}

