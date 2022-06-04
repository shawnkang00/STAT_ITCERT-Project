#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <list>
using namespace std;

struct Booking {
    string day, start_time, end_time, name, people, table;
};
 
list<Booking>schedule;

//copy data from input.txt into list
void file_to_list(list<Booking>& schedule) {

    ifstream ifile("input.txt");

    if (ifile.fail()) {
        cout << "Input file cannot be opened" << endl;
    }
    string line;
    while (getline(ifile, line)) {
        Booking b;
        string word = "";
        int counter = 0;

        //iterate through each character in line
        //which contains 4 space characters
        for (char c : line) {
            if (!isspace(c)) {
                word = word + c;
                if (c == line[line.length() - 1] && counter == 5) {
                    b.table = word;
                    counter = 0;
                }
            }
            //c is a space character
            else {
                switch (counter) {
                case 0:
                    b.day = word;
                    break;
                case 1:
                    b.start_time = word;
                    break;
                case 2:
                    b.end_time = word;
                    break;
                case 3:
                    b.name = word;
                    break;
                case 4:
                    b.people = word;
                    break;
                }
                word = "";
                counter++;
            }
        }
        schedule.push_back(b);
    }
    ifile.close();
}

//list out all bookings on a given day
void ListBooking(list<Booking>schedule) {

    string d;
retry:
    cout << "Day in schedule? (h for help)" << endl;
    cin >> d;

    if (d == "h") {
        cout << " Mon - Monday\n Tue - Tuesday\n Wed - Wednesday\n Thu - Thursday\n Fri - Friday\n Sat - Saturday\n Sun - Sunday\n";
        system("pause");
        system("cls");
        goto retry;
    }
    else {
        int counter = 0;
        list<Booking>::iterator iter = schedule.begin();

        //count the number of bookings on d
        for (; iter != schedule.end(); iter++) {
            if ((*iter).day == d) {
                counter++;
            }
        }

        //list out all bookings on d
        iter = schedule.begin();
        cout << "There are " << counter << " reservation(s) on " << d <<":"<< endl;
        cout << "==========================================================\n";
        cout << "== From/To == | == Name == | == People == | == TableNo. ==" << endl;
        cout << "==========================================================\n";
        for (; iter != schedule.end(); iter++) {
            if ((*iter).day == d) {
                cout << setw(8)<<left<<(*iter).start_time << "~" << (*iter).end_time << " | " << setw(10)<<left<<(*iter).name << " | " << setw(12)<<left<<(*iter).people << " | " <<setw(14)<<left<< (*iter).table << endl;
                cout << "----------------------------------------------------------\n";
            }
        }

    }
    system("pause");
    system("cls");
}

//prints the total number of bookings in a week
void TotalBooking(list<Booking>schedule) {
    
    int count = schedule.size();
    if (count == 0) {
        cout << "There are currently no reservations on record." << endl;
    }
    else {
        cout << "There are " << count << " reservation(s) in this week." << endl;
    }

}

int main() {

	file_to_list(schedule);
    
    ListBooking(schedule);

    TotalBooking(schedule);

	return 0;
}