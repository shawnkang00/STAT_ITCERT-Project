#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <list>
#include <algorithm>

using namespace std;

struct Booking {
    string day, start_time, end_time, name, people, table;   
};

bool operator<(const Booking &b1, const Booking &b2) {
    return (b1.name < b2.name);
}
 
list<Booking> schedule;

//copy data from input.txt into list
void file_to_list(list<Booking> &schedule) {

    ifstream ifile("input.txt");

    if (ifile.fail()) {
        cout << "Input file cannot be opened" << endl;
        exit(1);
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

//store data from list to input.txt
void list_to_file(list<Booking> schedule) {

    ofstream ofile("input.txt");

    if (ofile.fail()) {
        cout << "input.txt cannot be opened" << endl;
        exit(1);
    }

    for (list<Booking>::iterator iter = schedule.begin(); iter != schedule.end(); iter++) {

        ofile << iter->day << " " << iter->start_time << " " << iter->end_time << " " << iter->name << " " << iter->people << " " << iter->table << endl;

    }

    cout << "Saved data to input.txt" << endl;

    ofile.close();
}

//list out all bookings on a given day
void ListBooking(list<Booking> schedule) {

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
        schedule.sort();
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
void TotalBooking(list<Booking> schedule) {
    
    int count = schedule.size();
    if (count == 0) {
        cout << "There are currently no reservations on record." << endl;
    }
    else {
        cout << "There are " << count << " reservation(s) in this week." << endl;
    }

}

// Make a new booking to the schedule
void AddBooking(list<Booking> &schedule) {

    string day, s_time, e_time, n, ppl, tableNo;
    bool clash = false;
    cout << "Day of the week:" << endl;
    cin >> day;
    cout << "Start time: " << endl;
    cin >> s_time;
    if (s_time >= "2100") {
        cout << "Start time passed restaurant business hours" << endl;
        return;
    }
    cout << "End time: " << endl;
    cin >> e_time;
    if (e_time >= "2100") {
        cout << "End time passed restaurant business hours" << endl;
        return;
    }
    cout << "Name: " << endl;
    cin >> n;
    cout << "Number of people: " << endl;
    cin >> ppl;
    if (stoi(ppl) > 4) {
        cout << "Maximum occupancy for each table is 4." << endl;
        return;
    }
    cout << "Table Number: " << endl;
    cin >> tableNo;
    if (tableNo <= "00" || tableNo >= "25") {
        cout << "Table Number out of range" << endl;
        return;
    }

    for (list<Booking>::iterator iter = schedule.begin(); (iter != schedule.end() && clash != true); iter++) {

        if (day == iter->day) {
            if ((s_time >= iter->start_time && s_time <= iter->start_time)||(e_time >= iter->start_time && e_time <= iter->start_time)) {
                if (tableNo == iter->table) {
                    clash = true;
                }
            }
        }
    }

    if (clash) {
        cout << "Booking cannot be made due to reservation clashes" << endl;
        return;
    }
    else {
        Booking b1 = { day, s_time, e_time, n, ppl, tableNo };
        schedule.push_back(b1);
        cout << "Booking added to schedule" << endl;
    }
    

}

//remove a booking from the schedule
void Rm_Booking(list<Booking> &schedule) {

    string dy, s_time, e_time, n, tableNo;
    bool exist = false;
    cout << "Day of reservation: " << endl;
    cin >> dy;
    cout << "Start time of reservation: " << endl;
    cin >> s_time;
    cout << "End time of reservation: " << endl;
    cin >> e_time;
    cout << "Name of reservation: " << endl;
    cin >> n;
    cout << "Table number reserved: " << endl;
    cin >> tableNo;

    list<Booking>::iterator iter = schedule.begin();
    for (; iter != schedule.end(); iter++) {
        if (iter->day == dy) {
            if (iter->start_time == s_time) {
                if (iter->end_time == e_time) {
                    if (iter->name == n) {
                        if (iter->table == tableNo) {
                            exist = true;
                            schedule.erase(iter);
                            cout << "Booking removed from schedule" << endl;
                            return;
                        }
                    }
                }
            }
        }
    }

    cout << "Booking not found" << endl;
    return;

}

//check avaliability of table
//returns time period in which the table is occupied
void CheckTime(list<Booking> schedule) {

    string dy, tableNo;
    bool exist = false;
    cout << "Day of reservation: " << endl;
    cin >> dy;
    cout << "Table number reserved: " << endl;
    cin >> tableNo;

    list<Booking>::iterator iter = schedule.begin();
    for (; iter != schedule.end(); iter++) {
        if (iter->day == dy) {
            if (iter->table == tableNo) {
                exist = true;
                cout << "------------------------------------------\n";
                cout << iter->start_time << "~" << iter->end_time << endl;
            }
        }
    }

    if (!exist) {
        cout << "Table " << tableNo << " does not have any reservations on record on " << dy << endl;
        return;
    }
    cout << "------------------------------------------\n";


}

// print help menu for main function
void h_cmd() {

    system("cls");
    cout << "==========================================================\n";
    cout << setw(20) << "" << setw(15) << "List of Commands" << setw(20) << "" << endl;
    cout << "==========================================================\n";
    cout << setw(13) << left << "save" << setw(40) << left << "| Save current schedule to file" << endl;
    cout << "----------------------------------------------------------\n";
    cout << setw(13) << left << "list" << setw(40) << left << "| List all current schedule booking" << endl;
    cout << "----------------------------------------------------------\n";
    cout << setw(13) << left << "total" << setw(40) << left << "| View all booking for a day" << endl;
    cout << "----------------------------------------------------------\n";
    cout << setw(13) << left << "add" << setw(40) << left << "| Add a booking" << endl;
    cout << "----------------------------------------------------------\n";
    cout << setw(13) << left << "remove" << setw(40) << left << "| Remove a booking" << endl;
    cout << "----------------------------------------------------------\n";
    cout << setw(13) << left << "check" << setw(40) << left << "| Check the avaliability of a table" << endl;
    cout << "----------------------------------------------------------\n";
    cout << setw(13) << left << "exit" << setw(40) << left << "| Exit program" << endl;
    cout << "----------------------------------------------------------\n";
    system("pause");
    system("cls");

}

int main() {

    string cmd;
    file_to_list(schedule);

    while (true) {
        cout << "Command: (h for help)" << endl;
        cin >> cmd;
        
        if (cmd == "h") {
            h_cmd();
        }
        else if (cmd == "save") {
            list_to_file(schedule);
        }
        else if (cmd == "list") {
            ListBooking(schedule);
        }
        else if (cmd == "total") {
            TotalBooking(schedule);
        }
        else if (cmd == "add") {
            AddBooking(schedule);
        }
        else if (cmd == "remove") {
            Rm_Booking(schedule);
        }
        else if (cmd == "check") {
            CheckTime(schedule);
        }
        else if (cmd == "exit") {
            system("cls");
            break;
        }
        else {
            cout << "Invalid Command" << endl;
        }
    }

    cout << "Program Exited" << endl;
	
	return 0;
}
