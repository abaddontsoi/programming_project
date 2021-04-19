// JetAssign.cpp
// Author: Samuel Tam
// Date: 2021-03-22

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <vector>
#include <algorithm>

#define ROW_MAX 13
#define COL_MAX 6
#define ROW_C1 2
#define ROW_C2 7

using std::string;
using std::vector;
using std::cout;
using std::cin;

template<typename T>
T input()
{
    T t;
    cin >> t;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Try again: ";
        cin >> t;
    }
    return t;
}

template<typename T>
T input(T min, T max)
{
    T t;
    cin >> t;
    while (cin.fail() || t < min || t > max)
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Try again: ";
        cin >> t;
    }
    return t;
}

template<typename T, size_t N>
T input(T (&opts)[N])
{
    T t;
    cin >> t;
    auto r = std::find(std::begin(opts), std::end(opts), t);
    while (cin.fail() || r == std::end(opts))
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Try again: ";
        cin >> t;
        r = std::find(std::begin(opts), std::end(opts), t);
    }
    return t;
}

class Seat
{
private:
    string _name;
    string _id;
    int _row;
    int _col;
public:
    Seat(string name, string id, int row, int col)
        : _name(std::move(name)), _id(std::move(id)), _row(row), _col(col) {};
    string get_name() const { return _name; };
    string get_id() const { return _id; };
    int get_row() const { return _row; };
    int get_col() const { return _col; };
    void print() const;
};

class Plane
{
private:
    bool index[ROW_MAX][COL_MAX] = { 0 };
    vector<Seat> seats;
public:
    int add_seat(string name, string id, string seat);
    int remove_seat(string name, string id);
    vector<Seat>::iterator search_seat(string name, string id);
    vector<Seat>::iterator search_seat(string id);
    vector<Seat>::iterator search_seat(int row, int col);
    vector<Seat>::iterator get_seats_end();
    bool query_seat(int row, int col) const;
    void print() const;
};

void Seat::print() const
{
    cout << std::left << std::setw(20)
         << "Name: " << _name << '\n'
         << std::left << std::setw(20)
         << "Passport ID: " << _id << '\n';
    string rank = (_row < ROW_C1) ? "First"
                : (_row < ROW_C2) ? "Business"
                : "Economy";
    cout << std::left << std::setw(20)
         << "Class type: " << rank << '\n';
    int row = _row + 1;
    char col = _col + 'A';
    cout << std::left << std::setw(20)
         << "Seat location: " << row << col << '\n';
}

int Plane::add_seat(string name, string id, string seat)
{
    // code 0: success
    // code 1: invaild column
    // code 2: invaild row
    // code 3: unavailable seat
    int col = seat.back() - 'A';
    if (col < 0 || col >= COL_MAX)
        return 1;
    int row = (seat.size() == 3) ? seat.at(0) * 10 + seat.at(1) - '0' * 11 - 1
            : (seat.size() == 2) ? seat.at(0) - '0' - 1
            : -1;
    if (row < 0 || row >= ROW_MAX)
        return 2;
    if (query_seat(row, col))
        return 3;
    seats.emplace_back(name, id, row, col);
    index[row][col] = 1;
    return 0;
}

int Plane::remove_seat(string name, string id)
{
    // code 0: success
    // code 1: unable to find seat
    auto result = search_seat(name, id);
    if (result != seats.end())
    {
        seats.erase(result);
        auto seat = &*result;
        index[seat->get_row()][seat->get_col()] = 0;
        return 0;
    }
    return 1;
}

vector<Seat>::iterator Plane::search_seat(string name, string id)
{
    return std::find_if(seats.begin(), seats.end(),
        [&] (Seat const& p) { return (p.get_name() == name) && (p.get_id() == id); });
}

vector<Seat>::iterator Plane::search_seat(string id)
{
    return std::find_if(seats.begin(), seats.end(),
        [&] (Seat const& p) { return (p.get_id() == id); });
}

vector<Seat>::iterator Plane::search_seat(int row, int col)
{
    return std::find_if(seats.begin(), seats.end(),
        [&] (Seat const& p) { return (p.get_row() == row) && (p.get_col() == col); });
}

vector<Seat>::iterator Plane::get_seats_end()
{
    return seats.end();
}

bool Plane::query_seat(int row, int col) const
{
    return index[row][col];
}

void Plane::print() const
{
    cout << '\n' << std::left << std::setw(6) << ' ';
    for (char c = 'A'; c - 'A' < COL_MAX; c++)
        cout << std::left << std::setw(4) << c;
    cout << '\n';
    for (int row = 0; row < ROW_MAX; row++)
    {
        cout << std::left << std::setw(6) << row + 1;
        for (int col = 0; col < COL_MAX; col++)
        {
            char symbol = index[row][col] ? 'X' : '*';
            cout << std::left << std::setw(4) << symbol;
        }
        cout << '\n';
    }
}

int main()
{
    Plane plane;

    while (true)
    {
        std::cout << '\n'
                  << "*** main menu ***" << '\n'
                  << "[1] Add an assignment" << '\n'
                  << "[2] Delete an assignment" << '\n'
                  << "[3] Add assignments in batch" << '\n'
                  << "[4] Show latest seating plan" << '\n'
                  << "[5] Show details" << '\n'
                  << "[6] Exit" << '\n'
                  << "*****************" << '\n'
                  << "Option (1-6): ";
        int n = input(1, 6);

        switch (n)
        {
            case 1:
                {
                    string name, id, seat;
                    cout << "Enter name: ";
                    cin >> name;
                    cout << "Enter passport ID: ";
                    cin >> id;
                    cout << "Enter desired seat location: ";
                    cin >> seat;
                    cout << '\n' << "* Result *" << '\n';
                    switch (plane.add_seat(name, id, seat))
                    {
                        case 0:
                            cout << "Success" << '\n';
                            break;
                        case 1:
                            cout << "Invaild seat column" << '\n';
                            break;
                        case 2:
                            cout << "Invaild seat row" << '\n';
                            break;
                        case 3:
                            cout << "Seat already taken" << '\n';
                            break;
                    }
                }
                break;
            case 2:
                {
                    bool cont = 0;
                    do
                    {
                        string name, id;
                        cout << "Enter name: ";
                        cin >> name;
                        cout << "Enter passport ID: ";
                        cin >> id;
                        switch (plane.remove_seat(name, id))
                        {
                            case 0:
                                cout << "Success" << '\n';
                                cont = 0;
                                break;
                            case 1:
                                cout << "Failed to find entry." << '\n'
                                     << "Try again? [y/n] ";
                                char opts[] = { 'y', 'n' };
                                cont = (input(opts) == 'y');
                                break;
                        }
                    }
                    while (cont);
                }
                break;
            case 3:
                {
                    cout << "Enter in the format of \"Name/PassportID/Seat\";" << '\n'
                         << "Use \"0\" to terminate sequence:" << '\n';

                    string line;
                    vector<string> lines;
                    vector<int> lines_code;

                    while (true)
                    {
                        cin >> line;
                        if (line == "0") break;
                        lines.push_back(line);
                    }

                    cout << "Adding " << lines.size() << " assignment(s) in batch." << '\n'
                         << "Are you sure? [y/n] ";
                    char opts[] = { 'y', 'n' };
                    if (input(opts) != 'y') break;

                    for (auto &line : lines)
                    {
                        std::stringstream line_ss;
                        line_ss << line;
                        vector<string> line_args;
                        string line_arg;
                        while (std::getline(line_ss, line_arg, '/'))
                            line_args.push_back(line_arg);
                        int code = -1;
                        if (line_args.size() == 3)
                            code = plane.add_seat(line_args.at(0), line_args.at(1), line_args.at(2));
                        lines_code.push_back(code);
                    }

                    cout << '\n' << "* Results *" << '\n';
                    for (auto i = 0; i < lines.size(); i++)
                    {
                        cout << std::left << std::setw(20);
                        switch (lines_code.at(i))
                        {
                            case 0:
                                cout << "Success: " << lines.at(i) << '\n';
                                break;
                            case 1:
                                cout << "Invaild column: " << lines.at(i) << '\n';
                                break;
                            case 2:
                                cout << "Invaild row: " << lines.at(i) << '\n';
                                break;
                            case 3:
                                cout << "Seat is taken: " << lines.at(i) << '\n';
                                break;
                            default:
                                cout << "Invaild line: " << lines.at(i) << '\n';
                                break;
                        }
                    }
                }
                break;
            case 4:
                plane.print();
                break;
            case 5:
                {
                    cout << '\n'
                         << "*** Details ***" << '\n'
                         << "[1] Passenger" << '\n'
                         << "[2] Class" << '\n'
                         << "[3] Back" << '\n'
                         << "*****************" << '\n'
                         << "Option (1-3): ";
                    int n = input(1, 3);
                    switch (n)
                    {
                        case 1:
                            {
                                cout << "Enter passport ID: ";
                                string id;
                                cin >> id;
                                auto result = plane.search_seat(id);
                                if (result != plane.get_seats_end())
                                {
                                    cout << '\n' << "* Result *" << '\n';
                                    (&*result)->print();
                                }
                                else
                                    cout << "Failed to find entry." << '\n';
                            }
                            break;
                        case 2:
                            {
                                cout << "Enter class: [F/B/E] ";
                                char opts[] = { 'F', 'B', 'E' };
                                char c = input(opts);

                                int rank = (c == 'F') ? 0
                                         : (c == 'B') ? 1
                                         : (c == 'E') ? 2
                                         : 0;
                                int rank_rows[4] = { 0, ROW_C1, ROW_C2, ROW_MAX };
                                int rank_min = rank_rows[rank];
                                int rank_max = rank_rows[rank + 1];

                                for (int row = rank_min; row < rank_max; row++)
                                {
                                    for (int col = 0; col < COL_MAX; col++)
                                    {
                                        int row_d = row + 1;
                                        char col_d = col + 'A';
                                        cout << '\n'
                                             << "Seat " << row_d << col_d << '\n';
                                        if (plane.query_seat(row, col))
                                            (&*plane.search_seat(row, col))->print();
                                        else
                                            cout << "Vacant" << '\n';
                                    }
                                }
                            }
                            break;
                        default:
                            break;
                    }
                }
                break;
            case 6:
                {
                    cout << "The data ought to be uploaded to central database before shutdown." << '\n'
                         << "Confirm that all process are done; and" << '\n'
                         << "Continue to shut down? [y/n] ";
                    char opts[] = { 'y', 'n' };
                    if (input(opts) == 'y') return 0;
                }
                break;
        }
    }
}
