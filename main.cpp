#include <stdio.h>
#include <iostream>
#include <regex>

enum {
    welcome_message = 0,
    input_key = 1,
    validate_key = 2,
};

char state;

int checksum_calc(const std::string& key);
bool validate_format(const std::string& key);

int main() {
    std::string user_key;
    state = welcome_message;

    while(true) {
        switch(state) {
            case welcome_message: 
                printf("#############################################\n");
                printf("#           Crackme by smalltownboy         #\n");
                printf("#   Purpose: to generate a key for program  #\n");
                printf("#          registration. Good Luck!         #\n");
                printf("#############################################\n");
                state = input_key;
            break;

            case input_key:
                std::cout << "Enter your key for verification: ";
                std::cin >> user_key;

                if(validate_format(user_key)) {
                    state = validate_key;
                } else {
                    printf("#############################################\n");
                    printf("#        The key must have the format       #\n");
                    printf("#        XXXXX-XXXXX-XXXXX. Try Again.      #\n");
                    printf("#############################################\n");
                    state = input_key;
                }
            break;

            case validate_key:
                int checksum = checksum_calc(user_key);
                if(checksum == 27) {
                    printf("#############################################\n");
                    printf("#        Great job, you have done well!     #\n");
                    printf("#############################################\n");
                    return 0;
                } else {
                    printf("#############################################\n");
                    printf("#         Nice try, but no. Try Again.      #\n");
                    printf("#############################################\n");
                    state = input_key;
                }
            break;
        }
    }
}

int checksum_calc(const std::string &key) {
    int symbol_sum;

    for(char c : key) {
        symbol_sum += static_cast<int>(c);
    }

    return symbol_sum % 256;
}

bool validate_format(const std::string &key) {
    std::regex pattern("^[A-Z0-9]{5}-[A-Z0-9]{5}-[A-Z0-9]{5}$");

    return std::regex_match(key, pattern);
}
