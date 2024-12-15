#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

// Validate Function
bool ValidateInput(string input, int lim, bool& isFraction, const char KEY[], vector<int>& whole, vector<int>& fraction) {

    // Variable to confirm character is found in array list
    bool found;

    // Iterate through the user's string input
    for(int i = 0; i < input.size(); i++) {

        // If the character is a decimal and a decimal has not already been found, set isFraction to true and move to the next character
        if (input[i] == '.' && isFraction == false) {
            isFraction = true;
            i++;
        }

        // Iterate through the array list of valid characters with a limit that's been defined by the source base
        for (int j = 0; j <= lim; j++) {
            // Set the found variable to false
            found = false;
            // If the character is found in the array, set found to true
            if (input[i] == KEY[j]) {
                found = true;
                // Add the integer index value to the appropriate vector list by checking the variable isFraction and end the search
                if (isFraction == false) {
                    whole.push_back(j);
                    break;
                }
                else {
                    fraction.push_back(j);
                    break;
                }
            }
        }
        // If the character was not found or multiple decimal points were entered, clear both vector lists and return false.
        if (found == false) {
            whole.clear();
            fraction.clear();
            return false;
        }
    }
    // Otherwise return true
    return true;
}

// Conversion Function
int convert_number(int source_base, int target_base, bool& isFraction, const char KEY[], vector<int>& whole, vector<int>& fraction) {
    // Variables to be used for conversions
    int remainder = 0;
    int temp = 0;
    string answer = "";
    int count = 0;
    int number = 0;
    double decimal = 0;

    // Convert Decimal to Binary
    if(source_base==10 && target_base==2){
        // Iterate through the vector list for the whole number section of the user's input from right to left
        for (int i = (whole.size()-1); i>=0; i--) {
            // Multiply each number (0-9) by 10 to the power of the position of the number starting from right to left and add the sum to a variable
            number += whole[i]*(int(pow(10.0, double(count))));
            count++;
        }
        // Divide the number by 2 and add the remainder to a string variable until the number reaches 0
        do {
            remainder = number % 2;
            number = (number - remainder)/2;
            answer.append(to_string(remainder));
        } while(number != 0 );
        // Reverse the string to display the binary code in the correct order
        reverse(answer.begin(), answer.end());
        // If the answer is less than 4 digits, add the correct amount of 0's to display a 4 digit binary number
        if(answer.length() < 4){
            temp = 4 - answer.length();
            answer.insert(0,temp, '0');
        }
        // If the user entered a fractional decimal
        if (isFraction) {
            // Start the count variable at -1 and add a decimal point to the answer string
            count = -1;
            answer += '.';
            // Iterate through the vector list for the fractional section of the user's input from left to right
            for (int i = 0; i <=(fraction.size()-1); i++) {
                // Multiply each number (0-9) by 10 to the power of the position of the number starting from left to right and add the sum to a variable
                decimal += (fraction[i])*(pow(10.0, double(count)));
                count--;
            }
            // Set the count variable to 0
            count = 0;
            // Multiply the decimal portion by 2 and add 0 or 1 to the answer string until the decimal is equal to 0 or total of 10 decimal places
            do {
                count++;
                decimal = decimal * 2;
                if (decimal >= 1.0) {
                    answer += '1';
                    decimal -= 1.0;
                }
                else {
                    answer += '0';
                }
            } while ((decimal != 0) && (count < 10));
        }
        // Print the answer
        cout << "\nBinary output: " << answer << endl;
    }


    // Convert Decimal to Hexadecimal
    else if(source_base == 10 && target_base == 16){
        // Iterate through the vector list for the whole number section of the user's input from right to left
        for (int i = (whole.size()-1); i>=0; i--) {
            // Multiply each number (0-9) by 10 to the power of the position of the number starting from right to left and add the sum to a variable
            number += whole[i]*(int(pow(10.0, double(count))));
            count++;
        }
        // Divide the number by 16 and add the remainder to a string variable until the number reaches 0
        do{
            remainder = number % 16;
            answer += (KEY[remainder]);
            number = (number - remainder) / 16;
        }while(number != 0);
        // Reverse the string to display the binary code in the correct order
        reverse(answer.begin(), answer.end());
        // If the user entered a fractional decimal
        if (isFraction) {
            // Start the count variable at -1 and add a decimal point to the answer string
            count = -1;
            answer += '.';
            // Iterate through the vector list for the fractional section of the user's input from left to right
            for (int i = 0; i <=(fraction.size()-1); i++) {
                // Multiply each number (0-9) by 10 to the power of the position of the number starting from left to right and add the sum to a variable
                decimal += (fraction[i])*(pow(10.0, double(count)));
                count--;
            }
            // Set the count variable to 0
            count = 0;
            // Multiply the decimal portion by 16 and add 0 or 1 to the answer string until the decimal is equal to 0 or total of 10 decimal places
            do {
                count++;
                decimal *= 16;
                if (decimal >= 1.0) {
                    answer += KEY[int(decimal)];
                    decimal -= int(decimal);
                }
                else {
                    answer += '0';
                }
            } while ((decimal != 0) && (count <= 10));
        }
        // Print the answer
        cout << "\nHexadecimal output: " <<answer << endl;
    }
    // Convert Binary to Decimal
    else if(source_base == 2 && target_base == 10){
        // Iterate through the vector list for the whole number section of the user's input from right to left
        for(int i = (whole.size()-1); i>=0; i--){
            // If the number is 1
            if(whole[i] == 1){
                // Add 2 to the power of the position of the number to a variable
                number += int(pow(2.0, double(count)));
            }
            count++;
        }
        // If the user entered a fractional binary
        if (isFraction) {
            // Start the count variable at -1
            count = -1;
            // Iterate through the vector list for the fractional section of the user's input from left to right
            for (int i = 0; i <=(fraction.size()-1); i++) {
                // Multiply each number (0 or 1) by 2 to the power of the position of the number starting from left to right and add the sum to a variable
                decimal += (fraction[i])*(pow(2.0, double(count)));
                count--;
            }
        }
        // Add the whole number portion of the conversion to the decimal portion
        decimal += number;
        // Print the answer
        cout << "\nDecimal output: " <<decimal << endl;
    }
    // Convert Binary to Hexadecimal
    else if(source_base == 2 && target_base == 16){

        // First convert Binary to Decimal
        for(int i = (whole.size()-1); i>=0; i--){
            if(whole[i] == 1){
                number += int(pow(2.0, double(count)));
            }
            count++;
        }
        // Then convert the Decimal to Hexadecimal
        do{
            remainder = number % 16;
            answer += (KEY[remainder]);
            number = (number - remainder) / 16;
        }while(number != 0);
        // Reverse the string to display the Hexadecimal code in the correct order
        reverse(answer.begin(), answer.end()); 
        // If the user entered a fractional Binary
        if (isFraction) {
            // Start the count variable at -1 and add a decimal point to the answer string
            answer += '.';
            count = -1;
            // Iterate through the vector list for the fractional section of the user's input from left to right
            for (int i = 0; i <=(fraction.size()-1); i++) {
                // Multiply each number (0 or 1) by 2 to the power of the position of the number starting from left to right and add the sum to a variable
                decimal += (fraction[i])*(pow(2.0, double(count)));
                count--;
            }
            // Set the count variable to 0
            count = 0;
            // Multiply the decimal portion by 16 and add a number (0-15) to the answer string until the decimal is equal to 0 or total of 10 decimal places
            do {
                count++;
                decimal *= 16;
                if (decimal >= 1.0) {
                    answer += KEY[int(decimal)];
                    decimal -= int(decimal);
                }
                else {
                    answer += '0';
                }
            } while ((decimal != 0) && (count <= 10));
        }
        // Print the answer
        cout << "\nHexadecimal output: " <<answer << endl;
    } 
    // Convert Hexadecimal to Decimal
    else if(source_base == 16  && target_base == 10){
        // Iterate through the vector list for the whole number section of the user's input from right to left
        for(int i = (whole.size() - 1); i>=0; i--){
            // Multiply each number (0-15) by 16 to the power of the position of the number starting from right to left and add the sum to a variable
            number += whole[i]*(int(pow(16.0, double(count))));
            count++;
        }
        // If the user entered a fractional Hexadecimal
        if (isFraction) {
            // Start the count variable at -1
            count = -1;
            // Iterate through the vector list for the fractional section of the user's input from left to right
            for (int i = 0; i <=(fraction.size()-1); i++) {
                // Multiply each number (0-15) by 16 to the power of the position of the number starting from left to right and add the sum to a variable
                decimal += (fraction[i])*(pow(16.0, double(count)));
                count--;
            }
        }
        // Add the whole number portion of the conversion to the decimal portion
        decimal += number;
        // Print the answer
        cout << "\nDecimal output: " <<decimal << endl;
    }
    // Convert Hexadecimal to Binary
    else if(source_base ==16 && target_base == 2){
        
        // First convert Hexadecimal to Decimal
        for(int i = (whole.size() - 1); i>=0; i--){
            number += whole[i]*(int(pow(16.0, double(count))));
            count++;
        }

        // Then convert Decimal to Binary
        do {
            remainder = number % 2;
            number = (number - remainder)/2;
            answer.append(to_string(remainder));
        } while(number != 0 );
        // Reverse the string to display the Binary code in the correct order
        reverse(answer.begin(), answer.end());

        // If the answer is less than 4 digits, add the correct amount of 0's to display a 4 digit binary number
        if(answer.length() < 4){
            temp = 4 - answer.length();
            answer.insert(0,temp, '0');
        }

        // If the user entered a fractional Binary
        if (isFraction) {
            // Start the count variable at -1 and add a decimal point to the answer string
            answer += '.';
            count = -1;
            // Iterate through the vector list for the fractional section of the user's input from left to right
            for (int i = 0; i <=(fraction.size()-1); i++) {
                // Multiply each number (0-15) by 16 to the power of the position of the number starting from left to right and add the sum to a variable
                decimal += (fraction[i])*(pow(16.0, double(count)));
                count--;
            }
            // Multiply the decimal portion by 2 and add 0 or 1 to the answer string until the decimal is equal to 0 or total of 10 decimal places
            do {
                count++;
                decimal = decimal * 2;
                if (decimal >= 1.0) {
                    answer += '1';
                    decimal -= 1.0;
                }
                else {
                    answer += '0';
                }
            } while ((decimal != 0) && (count <= 10));
        }
        
        
        // Print the answer
        cout <<"\nBinary output: " << answer << endl;
    }
    // Return 0
    return 0;
}
// Main Method
int main() {
    // Constant character array with all possible valid inputs for number inputs
    const char KEY[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    // Lists to store the integer values of the user's input
    vector<int> whole;
    vector<int> fraction;
    // Variable to determine if the user would like to repeat the program
    string repeat = "";

    do {
        // Variable to take in number input
        string input = "";
        // Variable to determine if the user enters a valid value and if user input is a fractional value
        bool invalid = false;
        bool isFraction = false;
        // Variables for source base, target base, and limit
        int source_base = 0, target_base = 0, lim = 0;

        cout << "Please enter the following inputs:" << endl;
        // Ask the user to enter the source base by entering 2, 10, or 16 and validate until they enter a valid input
        do {
            // If the user's input was invalid then display an error message and set the invalid variable to false
            if (invalid) {
                cout << "The number you entered is invalid!\n" << endl;
                invalid = false;
            }
            cout << "The source base:\n2\tBinary\n10\tDecimal\n16\tHexadecimal" << endl;
            cin >> source_base;
            // If a mismatch exception occurs or a invalid number is entered
            if (cin.fail() || ((source_base != 2) && (source_base != 10) && (source_base != 16))) {
                // Clear the cin, ignore all characters and set invalid variable to true
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                invalid = true;
            }
        } while(invalid);

        //invalid = false;
        // Print an empty line
        cout << endl;
        // Ask the user to enter the source base by entering 2, 10, or 16 and validate until they enter a valid input
        do {
            // If the user's input was invalid then display an error message and set the invalid variable to false
            if (invalid) {
                cout << "The number you entered is either invalid or the same base!\n" << endl;
                invalid = false;
            }
            cout << "The target base:\n2\tBinary\n10\tDecimal\n16\tHexadecimal" << endl;
            cin >> target_base;
            // If a mismatch exception occurs, an invalid number is entered, or the source base and target base are the same
            if (cin.fail() || ((target_base != 2) && (target_base != 10) && (target_base != 16)) || (source_base == target_base)) {
                // Clear the cin, ignore all characters and set invalid variable to true
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                invalid = true;
            }
        } while(invalid);
        // Print an empty line
        cout << endl;
        // Determine the limit to be used when searching through the KEY using the given source base
        switch(source_base) {
            // If Binary only allow searching through the first 2 indices (0 and 1)
            case 2:
                lim = 1;
                break;
            // If Decimal only allow searching through the first 10 indices (0-10)
            case 10:
                lim = 9;
                break;
            // If Hexadecimal only allow searching through the first 15 indices (0-15, all indices)
            case 16:
                lim = 15;
                break;
        }
        // Asked the user to enter the number to convert and validate
        do {
            // If the user's input was invalid then display an error message and set the invalid variable to false
            if (invalid) {
                cout << "The number you entered is not recognized in the given source base!\n" << endl;
                invalid = false;
            }
            cout << "The number to convert:" << endl;
            cin >> input;
            // If the source base was 16, allow lower case letters by converting all characters to upper case
            if (source_base == 16) {
                for(int i = 0; i < input.length(); i++){
                    input[i] = toupper(input[i]);
                }
            }
            // Pass the user's input, limit, isFraction variable, KEY, whole list and fraction list to validate the input
            if ((ValidateInput(input, lim, isFraction, KEY, whole, fraction)) == false) {
                invalid = true;
            }
        } while(invalid);
        // Pass the source base, target base, isFraction variable, KEY, whole list and fraction list to convert the user's input
        convert_number(source_base, target_base, isFraction, KEY, whole, fraction);
        // Once converted, clear the whole list and fraction list
        whole.clear();
        fraction.clear();
        // Ask the user if they would like to continue by entering Y or N (lower case accepted)
        do {
            cout << "Would you like to convert another number? Y/N" << endl;
            cin >> repeat;
            for(int i = 0; i < repeat.length(); i++){
                repeat[i] = toupper(repeat[i]);
            }
            
            if ((repeat != "N") && (repeat != "Y")) {
                cout << "Please enter either Y or N!" << endl << endl;
            }
        } while ((repeat != "N") && (repeat != "Y"));
    } while (repeat == "Y"); // Repeat the program if the user enters y or Y
    // Return 0
    return 0;
}