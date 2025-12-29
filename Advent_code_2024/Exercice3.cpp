#include <iostream>
#include <string>
#include <cctype>
using namespace std;







int main() {
    int total =0;
    string message;
    cout << "Enter expression: ";
    getline(cin, message);

    bool enable = true;

    auto findNumber = [&](int& i){
        int x =0;
        while (x< 1000 && isdigit(message[i])){
            x = 10 * x + (message[i] - '0'); // first part is adding to a number and the second to convert to digit
            i++;
        }
        if( 1 <= x && x <= 999){
            return  x;
        }
        else
            return -1;
    };

    int n = (int) message.length();
    for(int i=0; i<n - 7;i++ ){
        if(message.substr(i,4) == "do()"){
            enable = true;
        }
        if(message.substr(i,7) == "don\'t()"){
            enable = false;
        }
        if(enable && message[i] == 'm'){
            if(message[i+1] == 'u' && message[i+2] == 'l' && message[i+3] == '(' ){
                i += 4; // jump to the number
                int x = findNumber(i);
                if(message[i] == ','){
                    i +=1;
                    int y = findNumber(i);
                    if(message[i] == ')'){
                        if( x!= -1 && y!= -1)
                            total += x*y;
                    }
                }
            }
        }
    }
    cout << "\nTotal of all multiplications: " << total << endl;
    return 0;
}