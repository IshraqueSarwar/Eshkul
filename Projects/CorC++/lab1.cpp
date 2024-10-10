#include <iostream>
#include <string>
using namespace	std;
int main()
{
    string name;
    int age = 0;
    int choice;
    int action = 0;
    
    // getting the dog's name

    cout << "What is your dog's name?" << endl;
    getline(cin, name);

    // getting the dog's age with valiation
    while (true)
    {
        cout << "what is your dog's age" << endl;
        cin >> age;

        if (age >= 0 && age  25)
        {
            break;
        }
        cout << "Please enter a valid age between 0 and 25" << endl;
        
    }
    
    // looping for the menu option
    while (action < 3)
    {
        cout<< "What would you like to do?" << endl;
        cout << "1. Play fetch with " << name << endl;
        cout << "2. Feed " << name << endl;
        cout << "3. Pet " << name << endl;
        cin >> choice;

        if ( choice == 1){
            cout << name << " gets the stick and returns to you" << endl;
            action++;
        }   
        else if ( choice == 2){
            cout << name << " hungrily eats their food." << endl;
            action++;
        }
        else if ( choice == 3){
            cout << "You happily pet "<< name << "." << endl;
            action++;
        }
    }
        


    cout << "You are a great pet owner! Good-bye" << endl;

  return 0;
}
