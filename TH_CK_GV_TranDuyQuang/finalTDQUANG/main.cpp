#include <bits/stdc++.h>

using namespace std;
string shortenString(const string &str, size_t maxLength) {
    if (str.length() <= maxLength) {
        return str;
    }
    return str.substr(0, maxLength - 3) + "...";
}
class Object {
public:
    virtual string toString() = 0;
};

class Date : public Object{
private:
    int day;
    int month;
    int year;
public:
    Date() {
        // Lấy thời gian hiện tại
        auto now = std::chrono::system_clock::now();
        // Chuyển đổi thành thời gian hệ thống
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        // Sử dụng std::localtime để chuyển đổi time_t thành tm
        std::tm local_time = *std::localtime(&now_time);
        this->day = local_time.tm_mday;
        this->month = local_time.tm_mon + 1;
        this->year = local_time.tm_year + 1900;
    }

    Date(int day, int month, int year) {
        this->day = day;
        this->month = month;
        this->year = year;
    }

    Date getTimeToday() {
        return Date();
    }

    Date getDate(string date) {
        stringstream ss(date);
        string token;
        vector<string> tokens;
        while (getline(ss, token, '/')) {
            tokens.push_back(token);
        }
        return Date(stoi(tokens[0]), stoi(tokens[1]), stoi(tokens[2]));
    }
    string toString() override {
        return to_string(day) + "/" + to_string(month) + "/" + to_string(year);
    }
    static int calculateDiff(Date startDate, Date endDate) {
//        - Employee A has a start date of 01/05/2023. So his start month will be 5
//        - If today falls in 04/2024 (any day in April), is is counted as < 1 year of work
//        - If today falls in 05/2024 (any day in May), it is counted as a full 1 year of work (=1)
//        - If today falls in 06/2024 (any day in June), it is counted as > 1 year of work
        int diff = endDate.year - startDate.year;
        if(diff>=2) return 2;
        if(diff==0) return 0;
        if(diff==1) {
            if (endDate.month == startDate.month) return 1;
            if (endDate.month > startDate.month) return 2;
            return 0;
        }
    }
};

class Book : public Object {
private:
    string title;
    double price;
    string link;
public:
    Book(string title, double price, string link) {
        this->title = title;
        this->price = price;
        this->link = link;
    }
    string toString() override {
        return title + " " + to_string(price) + " " + link;
    }
    double getPrice() {
        return price;
    }
    string getTitle() {
        return title;
    }
    string getLink() {
        return link;
    }
    static Book parse(string line ){
        vector<string> v;
        stringstream ss(line);
        string token;
        while(getline(ss, token, ',')) {
            v.push_back(token);
        }
        string title = v[0].substr(v[0].find("Title=") + 6);
        double price = stod(v[1].substr(v[1].find("$") + 1));
        string link = v[2].substr(v[2].find("=") + 1);
        return Book(title, price, link);

    }
    void printInfo() {
        ostringstream os;
        os << fixed << setprecision(2) << price;
        string s=" $"+os.str();
        cout << setw(27) << shortenString(title,27) << " | "
             << setw(10) << s << " | ";
    }
};

class Employee : public Object {
protected:
    string name;
    string email;
    Date startDate;
public:
    Employee(string name, string email, Date startDate) {
        this->name = name;
        this->email = email;
        this->startDate = startDate;
    }
    virtual double getPercentSponsoring() = 0;
    virtual void printInfo()=0;
};

class Fresher : public Employee {
public:
    double getPercentSponsoring() override {
        return 0.3;
    }
    Fresher(string name, string email, Date startDate) : Employee(name, email, startDate) {}
    string toString() override {
        return "Fresher";
    }
    void printInfo() override {
        cout << setw(15) << name << " | "
             << setw(10) << "Fresher" << " | ";
    }
};

class Junior : public Employee {
public:
    Junior(string name, string email, Date startDate) : Employee(name, email, startDate) {}
    double getPercentSponsoring() override {
        return 0.5;
    }
    string toString() override {
        return "Junior";
    }
    void printInfo() override {
        cout <<setw(15)<< name<<" | "
        <<setw(10)<< "Junior"<<" | ";
    }
};

class Senior : public Employee {
public:
    Senior(string name, string email, Date startDate) : Employee(name, email, startDate) {}
    double getPercentSponsoring() override {
        return 1;
    }
    string toString() override {
        return "Senior";
    }
    void printInfo() override {
        cout <<setw(15)<< name<<" | "
        <<setw(10)<< "Senior"<<" | ";
    }
};

class IPaser: public Object {
public:
    virtual Employee* parse(string line) = 0;
};

class FresherParser: public IPaser {
public:
    Employee* parse(string line) override {
        vector<string>v;
        stringstream ss(line);
        string token;
        while(getline(ss, token, ',')){
            v.push_back(token);
        }
        string name = v[0].substr(v[0].find("=")+1);
        string email = v[1].substr(v[1].find("=")+1);
        Date startDate = Date().getDate(v[2].substr(v[2].find("=")+1));
        return new Fresher(name, email, startDate);
    }
    string toString() override {
        return "Fresher";
    }
};
class JuniorParser: public IPaser {
public:
    Employee* parse(string line) override {
        vector<string>v;
        stringstream ss(line);
        string token;
        while(getline(ss, token, ',')){
            v.push_back(token);
        }
        string name = v[0].substr(v[0].find("=")+1);
        string email = v[1].substr(v[1].find("=")+1);
        Date startDate = Date().getDate(v[2].substr(v[2].find("=")+1));
        return new Junior(name, email, startDate);
    }
    string toString() override {
        return "Junior";
    }

};
class SeniorParser: public IPaser {
public:
    Employee* parse(string line) override {
        vector<string>v;
        stringstream ss(line);
        string token;
        while(getline(ss, token, ',')){
            v.push_back(token);
        }
        string name = v[0].substr(v[0].find("=")+1);
        string email = v[1].substr(v[1].find("=")+1);
        Date startDate = Date().getDate(v[2].substr(v[2].find("=")+1));
        return new Senior(name, email, startDate);
    }
    string toString() override {
        return "Senior";
    }
};

class Factory {
private:
    inline static Factory* instance = nullptr;
    map<string, IPaser*> parsers;
private:
    Factory(){}
public:
    void registerWith(IPaser* parser) {
        parsers[parser->toString()] = parser;
    }
    static Factory* getInstance() {
        if (instance == nullptr) {
            instance = new Factory();
        }
        return instance;
    }
    IPaser* create(string type) {
        return parsers[type];
    }

};

class Proposal {
private:
    Employee *employee;
    Book *book;
public:
    Proposal(Employee *employee, Book *book) {
        this->employee = employee;
        this->book = book;
    }
    double getTotal() {
        return book->getPrice() * employee->getPercentSponsoring();
    }
    void printInfo() {
        employee->printInfo();
        book->printInfo();
        ostringstream out;
        out << fixed << setprecision(2) << getTotal();
        int percentage=(employee->getPercentSponsoring()*100);
        string Sper=to_string(percentage)+"%";
        cout << setw(10)<<Sper << " | ";
        cout << setw(10)<<out.str()<<endl;
    }

};

void config(){
    Factory *factory = Factory::getInstance();
    factory->registerWith(new FresherParser());
    factory->registerWith(new JuniorParser());
    factory->registerWith(new SeniorParser());
}

int main() {
    config();
    Date now = Date().getTimeToday();
    ifstream file("May2024Proposals.txt");
    string line;
    map<int,string> type;
    type[0]="Fresher";
    type[1]="Junior";
    type[2]="Senior";
    int i=0;
    vector<Book*>books;
    vector<Employee *> employees;
    vector<Proposal> proposals;

    while (getline(file, line)) {
        if(i==2) i=0;
        if (line[0] == 'E') {
            string date=line.substr(line.find("StartDate=")+10);
            int diff=Date::calculateDiff(Date().getDate(date), now);
            IPaser *parser = Factory::getInstance()->create(type[diff]);
            employees.push_back(parser->parse(line));
            i+=1;
        } else if (line[0] == '=') {
            books.push_back(new Book(Book::parse(line)));
            i+=1;
        }
        if(i==2) proposals.push_back(Proposal(employees.back(), books.back()));

    }
    cout << "Chuong trinh tai tro cho nhan vien cua UltraUs " << now.toString() << endl;
    cout << "Dang doc cac de nghi tu tap tin May2024Proposals.txt" << endl;
    cout << "Tim thay " << proposals.size() << " de nghi mua sach" << endl;
    cout << setw(4) << "STT" << " | "
         << setw(15) << "Nhan vien" << " | "
         << setw(10) << "Tham nien" << " | "
         << setw(27) << "Ten sach" << " | "
         << setw(10) << "Gia sach" << " | "
         << setw(10) << "Ho tro" << " | "
         << setw(10) << "Thanh tien" << endl;
    cout << string(105, '-') << endl;
    float sum = 0;
    for (int i = 0; i < proposals.size(); i++) {
        cout << setw(4) << (i + 1) << " | ";
        proposals[i].printInfo();
        sum += proposals[i].getTotal();
    }
    cout << "Tong tien tai tro: $" << fixed << setprecision(2) << sum << endl;
}

/*
 # 1. Preparation

<aside>
💡 This is a suggestion, not a must.

</aside>

- Create a solution with the name of **FinalLab**.
    - Create a project with the name of **EmployeeBookSponsor**

# 2. Scenario

The company UltraUs sponsors its employees' skill and knowledge development by providing financial assistance. Each month, employees submit proposals outlining their desired training. Employees can only submit one proposal per month.

- Employees can recommend one **book** for the company to purchase. Each recommendation should include the book's **title**, **price** in USD, and a **link** for reference

Employees with more experience may be eligible for increased sponsorship opportunities

| Years of work | Classification | Percent of sponsoring |
| --- | --- | --- |
| < 1 year | Fresher | 30% |
| 1 ≤ year < 2 | Junior | 50% |
| 2 ≤ year | Senior | 100% |
- Work experience is calculated solely based on start month and year
- Example:
    - Employee A has a start date of 01/05/2023. So his start month will be 5
- If today falls in 04/2024 (any day in April), is is counted as < 1 year of work
- If today falls in 05/2024 (any day in May), it is counted as a full 1 year of work (=1)
- If today falls in 06/2024 (any day in June), it is counted as > 1 year of work

onsidering the policy has undergone two revisions in the past, your code should be designed to accommodate future policy changes.

# 3. Requirements

1. Read all the proposals from the input file **May2024Proposals.txt (only the information that you need)**
2. Generate a table summarizing the results of all proposals.
3. Display the total amount of sponsorship funds allocated for this month.
 */

//SAMPLE INPUT
/*
Employee: Name=Do Minh Long, Email=dmlong@gmail.com, StartDate=05/07/2023
=> Book: Title=Clean architecture with .Net Core, Price=$60.69, Link=www.amazon.com?id=11512

Employee: Name=Tran Bao Tuan, Email=tbtuan@gmail.com, StartDate=12/06/2022
=> Book: Title=The Pragmatic Programmer: From Journeyman to Master, Price=$55.17, Link=www.amazon.com?id=11459

Employee: Name=Cao Hoang Thien, Email=chthien@gmail.com, StartDate=12/06/2021
=> Book: Title=Design Patterns: Elements of Reusable Object-Oriented Software, Price=$58.29, Link=www.amazon.com?id=66821
 */

//EXPECTED :Please note: This data is for presentation purposes only and does not reflect actual results
/*
Chuong trinh tai tro cho nhan vien cua UltraUs 05/2024
Dang doc cac de nghi tu tap tin May2024Proposals.txt
Tim thay 3 de nghi mua sach

STT | Nhan vien       | Tham nien | Ten sach                  | Gia sach | Ho tro | Thanh tien
---------------------------------------------------------------------------------------------
1   | Do Minh Long    | Fresher   | Clean architecture with...| $77.12   | 30%    | $21.42
2   | Tran Bao Tuan   | Junior    | The Pragmatic Programme...| $51.62   | 50%    | $25.55
3   | Cao Hoang Thien | Senior    | Design Patterns: Elemen...| $66.33   | 100%   | $66.33

Tong tien tai tro: $200.58
 */