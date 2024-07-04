#include <bits/stdc++.h>
using namespace std;
class Object {
public:
    virtual string toString()  = 0;
};
class Integer: public Object {
private:
    int _value;
public:
    Integer(int value):_value(value) {}
    string toString()  {
        return to_string(_value);
    }
    int value() {
        return _value;
    }

};
class NumberFormatInfo: public Object {
private:
    string _currencyDecimalSeparator = ".";
    string _currencySymbol = "d";

    // https://stackoverflow.com/questions/17459450/how-to-determine-currency-symbol-position-for-a-culture
    int _currencyPositive = 3;				// 0		1		2		3
    string _currencyPositiveFormat = "n $"; // "$n"		"n$"	"$ n"	"n $"
public:
    string currencyDecimalSeparator(){
        return _currencyDecimalSeparator;
    }
    string currencySymbol(){
        return _currencySymbol;
    }
    int currencyPositive(){
        return _currencyPositive;
    }
    string currencyPositiveFormat(){
        return _currencyPositiveFormat;
    }
public:
    string toString(){
        return "NumberFormatInfo";
    }

};
class IValueConverter: public Object {
    virtual string convert(Object* obj)=0;
};
class IntegerToCurrencyConverter: public IValueConverter
{
public:
    string convert(Object *obj)
    {
        auto number = dynamic_cast<Integer *>(obj);
        int value = number->value();

        stringstream builder;
        NumberFormatInfo info;
        int count = 0;

        while (value != 0)
        {
            int lastDigit = value % 10;
            builder << lastDigit;

            count++;
            value /= 10;
            if (count == info.currencyPositive())
            {
                count = 0;
                if (value != 0)
                    builder << info.currencyDecimalSeparator();
            }
        }

        string numberSeparated = builder.str();
        reverse(numberSeparated.begin(), numberSeparated.end());

        string format = info.currencyPositiveFormat();
        string symbol = info.currencySymbol();

        //using regex
        string result = regex_replace(format, regex("n"), numberSeparated);
        result = regex_replace(result, regex("\\$"), symbol);
        // not using regex
//        string result = format;
//        result.replace(result.find("n"), 1, numberSeparated);
//        result.replace(result.find("$"), 1, symbol);
        return result;
    }
    string toString() {
        return "IntegerToCurrencyConverter";
    }

};
class IProject: public Object{
public:
    virtual float getBudget() = 0;
    virtual void printInfo(ostream& os)=0;
};
class Idea:public IProject{
private:
    string name;
    int months;
    const float budget=2200;
public:
    Idea(string name, int months):name(name), months(months) {}
    float getBudget()  {
        return months * budget;
    }
    string toString()  {
        return "Idea";
    }
    void printInfo(ostream& os) {
        string s= "Phat trien: " + to_string(months) + " thang";
        os << setw(15) << name << " | "
           << setw(12) << toString() << " | "
           << setw(40) << s << " | ";
//           << setw(8) << getBudget() << " | " << endl;
    }
};
class MVP:public IProject{
private:
    string name;
    int runMonths;
    int marketingMonths;
    const float runBudget = 930;
    const float marketingBudget = 500;
public:
    MVP(string name, int runMonths, int marketingMonths):name(name), runMonths(runMonths), marketingMonths(marketingMonths) {}
    float getBudget()  {
        return runMonths * runBudget + marketingMonths * marketingBudget;
    }

    string toString()  {
        return "MVP";
    }
    void printInfo(ostream& os) {
        string s= "Van hanh: " + to_string(runMonths) + " thang. Marketing: " + to_string(marketingMonths) + " thang";
        os << setw(15) << name << " | "
           << setw(12) << toString() << " | "
           << setw(40) << s << " | ";
    }
};
class IParser: public Object{
public:
    virtual IProject* parse(const string& line) = 0;
};
class IdeaParser: public IParser{
public:
    IProject *parse(const string& s){
        string name=s.substr(0, s.find(","));
        int months=stoi(s.substr(s.find("=")+1));
        return new Idea(name, months);
    }
    string toString() {
        return "Idea";
    }
};
class MVPParser: public IParser{
public:
    IProject *parse(const string& line){
        string name=line.substr(0, line.find(","));
        int runMonths=stoi(line.substr(line.find("=")+1, line.find(",")));
        string temp=line.substr(line.find(",")+1);
        temp=temp.substr(temp.find(",")+1);
        temp=temp.substr(temp.find("=")+1);
        int marketingMonths=stoi(temp);
        return new MVP(name, runMonths, marketingMonths);
    }
    string toString() {
        return "Mvp";
    }
};
class Factory{
private:
    inline static Factory *instance = nullptr;
    map<string, IParser*> parsers;
private:
    Factory() {}
public:
    void registerWith(IParser* parser) {
        parsers[parser->toString()] = parser;
    }
    static Factory* getInstance() {
        if (instance == nullptr) {
            instance = new Factory();
        }
        return instance;
    }
    IParser* create(string type) {
        return parsers[type];
    }
};
void configuration (){
    Factory *factory = Factory::getInstance();
    factory->registerWith(new IdeaParser());
    factory->registerWith(new MVPParser());
}
int main(){
    configuration();
    ifstream file("MayProposals.txt");
    string line;
    vector<IProject*> projects;
    while(getline(file, line)){
        string type=line.substr(0, line.find(":"));
        IParser *parser = Factory::getInstance()->create(type);
        string temp=line.substr(line.find(":")+1);
        projects.push_back(parser->parse(temp));
    }
    sort(projects.begin(), projects.end(), [](IProject* a, IProject* b){
        return a->getBudget() < b->getBudget();
    });
    cout << "Ke hoach tai tro du an startup noi bo cong ty AlphaTech" << endl;
    cout << setw(4) << "STT" << " | "
         << setw(15) << "Ten du an" << " | "
         << setw(12) << "Loai du an" << " | "
         << setw(40) << "Thong tin" << " | "
         << setw(8) << "Kinh phi" << " | "
         <<endl;
    cout << string(95, '-') << endl;
    float sum=0;
    IntegerToCurrencyConverter converter;
    for(int i=0; i<projects.size(); i++){
        cout << setw(4) << (i+1) << " | ";
        projects[i]->printInfo(cout);
        cout << setw(8) << converter.convert(new Integer(projects[i]->getBudget())) << endl;
        sum+=projects[i]->getBudget();
    }
    cout << "Tong Kinh Phi Tai Tro: $" << sum;
    return 0;
}



/*
 * # A. IProject StartupSponsors

## Scenario

The company **AlphaTech** opens its monthly internal **Hackathon Challenge**. The employees of the company will form teams to participate. Each team will submit its project for getting sponsors from the company.

There are two types of project:

- **Idea**: An initial idea is all that the team has. This project needs time to do research and development. It will propose the months that are needed.
    - For example: Team A has an ideas of developing a website for renting old computers. This project needs **6** months of developing.
    - The company can support each month **2.200**$ for development.
    - As a result, the company needs to grant a sponsor of **6** * **2.200** = **13.200**$.
- **MVP**: This project has some basic development and reaches MVP state (minimal viable product). It will need money for running in production and its marketing campaigns. The team will propose the months for running the product in production together with the months they want to execute their marketing campaigns.
    - For example: Team B has developed an MVP version of the project **Flower Fast Delivery**. It wants to runs the website for **8** months and use **4** months to do some marketing campaigns.
    - The company can support each month **930$** for running the product.
    - To support the website, the company will hire a marketing team in the market with the cost of **500$** each month.
    - As a result, the company needs to grant a sponsor of **8 * 930 + 4 * 500 = 9.440$**

## Requirements

- Read all project proposals from the input file: **MayProposals.txt**
Idea: SuperTech, DevMonths=6
Mvp: FutureCar, RunMonths=6, Marketing=3
Idea: VirtualHouse, DevMonths=7
Idea: NightVision, DevMonths=4
Mvp: SmartKey, RunMonths=4, Marketing=5
 expected
Kế hoạch tài trợ dự án startup nội bộ công ty AlphaTech
Tháng: 05/2024

STT | Loại dự án  | Tên dự án   	| Thông tin 					                    | Kinh phí
-------------------------------------------------------------------------------------------------
1   | Ý tưởng     | NightVision	  | Phát triển: 6 tháng 			              | $120,000
2   | Sản phẩm    | SmartKey  	  | Vận hành: 6 tháng. Marketing: 3 tháng 	| $150,000
3   | Ý tưởng     | VirtualHouse 	| Phát triển: 7 tháng				              | $160,000
4   | Ý tưởng     | SuperTech 	  | Phát triển: 4 tháng				              | $280,000
5   | Sản phẩm    | FutureCar   	| Vận hành: 4 tháng. Marketing: 5 tháng 	| $335,000

Tổng kinh phí tài trợ: $800,000
 */