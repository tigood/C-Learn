#include <iostream>
#include <vector>
#include <string>

class myDate {
public:
    myDate(const std::string user_input) {
        unsigned tag;
        unsigned format;
        tag = format = 0;

        // 1/1/1900
        if (user_input.find_first_of('/') != std::string::npos) {
            format = 0x01;
        }

        // January 1, 1900 or Jan 1, 1900
        if (user_input.find_first_of(',') != std::string::npos && user_input.find_first_of('/') >= 4){
            format = 0x10;
        }
        else{
            if (user_input.find_first_of(' ') != std::string::npos && user_input.find_first_of(' ') >= 3) {
                format = 0x10;
                tag = 1;
            }
        }

        switch (format)
        {
        case 0x01:
            day_ = std::stoi(user_input.substr(0, user_input.find_first_of('/')));
            month_ = std::stoi(user_input.substr(user_input.find_first_of('/'), user_input.find_last_of('/') - user_input.find_first_of('/')));
            year_ = std::stoi(user_input.substr(user_input.find_last_of('/') + 1, 4));
            break;
        case 0x10:
            if( user_input.find("Jan") < user_input.size() )  month_ = 1;
            if( user_input.find("Feb") < user_input.size() )  month_ = 2;
            if( user_input.find("Mar") < user_input.size() )  month_ = 3;
            if( user_input.find("Apr") < user_input.size() )  month_ = 4;
            if( user_input.find("May") < user_input.size() )  month_ = 5;
            if( user_input.find("Jun") < user_input.size() )  month_ = 6;
            if( user_input.find("Jul") < user_input.size() )  month_ = 7;
            if( user_input.find("Aug") < user_input.size() )  month_ = 8;
            if( user_input.find("Sep") < user_input.size() )  month_ = 9;
            if( user_input.find("Oct") < user_input.size() )  month_ =10;
            if( user_input.find("Nov") < user_input.size() )  month_ =11;
            if( user_input.find("Dec") < user_input.size() )  month_ =12;

            char ch = ',';
            if (tag = 1) {
                ch = ' ';
            }
            day_ = std::stoi(user_input.substr(user_input.find_first_of("123456789"), user_input.find_first_of(ch) - user_input.find_first_of("123456789")));

            year_ = std::stoi(user_input.substr(user_input.find_last_of(' ') + 1, 4));
            break;

        default:
            break;
        }

    }
    
    void print() {
        std::cout << "day: " << day_ << " month: " << month_ << " year: " << year_ << std::endl;
    }

private:
    unsigned day_, month_, year_;
};

int main()
{

    return 0;
}