#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <queue>
#include <stdlib.h>
#include <sstream>
#include <math.h>

using namespace std;

int extraction_method (int key);                                        //declares the function written below
int quadratic_probe (int *& Hashtable, int key, int Max, int input);        //declares the function written below
void write_out_table(int *& Hashtable, int Max);                        //declares the function written below

int main()
{
    ifstream in;                                //initiates an inputfile stream
    in.open ("everybodys_socials.txt");         //sets the input file as "everybodys_socials.txt", and opens the file
    
    if (!in.is_open()) {                        //checks to make sure the file exists/is in the right place, if not:
        cout << "The file could not be found!" << endl;     //notifies the user, and
        return 0;                                           //terminates the program
    }
    
    string line;    //sets an empty string variable to temporarily store SSNs from the input file
    
    vector <int> socialsVector;      //initializes an int vector to hold the read SSNs
    
    while (!in.eof ()) {                //checks to make sure its not the end of the file, if not:
        getline (in,line, ',');             //read a SSN and store it as a string in the variable "line"
        socialsVector.push_back(stoi(line));     //change the SSN to an int value and add it to the vector
    }
    
    in.clear();         //clear the input file buffer
    in.close();         //close the input file

    int input = 0;
    int index;              //sets an integer variable to store the new index value that will be extracted using a function
    int M = socialsVector.size();      //sets a maximum hash table value (same as the number of SSN in the file)
    
    while (input < 1 || input > 450000000) {        //checks to see that the max value is between 1 and 450 million, if not:
        cout << "Enter a number between 1 and 450 Million: ";       //prompts the user to enter a value for M
        cin >> input;                                                   //sets the user input to be the new value of M
    }
    
    int *hash_table = new int [M];       //creates a new hash table with M elements
    
    for(int i=0;i<M;i++) {   //sets all of the initial values in the hash table to 0
        hash_table[i]=0;
    }
    
    for(int i=0;i<M;i++) {   //hash the elements in socialsVector into the hash_table
        
        index = extraction_method (socialsVector[i]);     //sets the index of the new SSN in the hash table to the extracted value
        
        if(hash_table[index]==0) {                  //if the index that was extracted is empty within the hash table:
            hash_table[index] = socialsVector [i];       //add the SSN from the vector to the indexed location in the hash table
        }
        
        else {                                    //if the extracted index is not empty:
            quadratic_probe (hash_table , socialsVector [i], M, input); //implement the quadratic_probe() funtion to find a new index
        }
    }
    
    write_out_table(hash_table, M);         //call the function to write out the hash table to a new file

    delete hash_table;            //delete the hash table
}

int extraction_method(int key)
{
    string text = to_string (key);          //convert int key into a string
    string first, second, third, fourth;    //declare variables that will store the 3rd, 5th, 7th, and 8th digits of the SSN
    int result;             //declare a variable that will contain the combined digits taken as an int
    
    first = text [2];       //store the 3rd digit
    second = text [4];      //store the 5th digit
    third = text [6];       //store the 7th digit
    fourth = text [7];      //store the 8th digit
    
    text = first + second + third + fourth;     //combine the extracted and newly stored digits
    
    result = stoi(text);        //convert the new number combination to an int value
    
    return result;      //return the integer
}

int quadratic_probe (int *& Hashtable, int key, int Max, int input)
{
    unsigned int pos;        //Declare an int variable to store the new position of the element being placed

    for (int i = 1 ; i<Max; i++)      //go through the hash table
    {
        pos = (extraction_method(key) + ((input+i)*(input+i))) % Max;  //assign the position using the extraction_method() function and the user input
        
        if (Hashtable[pos]  == 0)       //if the new position in the table is empty:
        {
            Hashtable [pos] = key;      //place the SSN value there
            return pos;                 //return the position
        }
    } //table overflow
    return -1;
}

void write_out_table(int *& Hashtable, int Max)
{
    ofstream out;                       //declares a new output file to put the results in
    out.open("hashed_socials.txt");     //opens the output file under the file name "hashed_socials.txt"
    
    for (int k = 0 ; k< Max; k++) {         //write out the hashtable
    
        cout<<Hashtable[k]<<endl;           //write each element on its own line on the console
        
        if (k<(Max-1)) {                      //Check to see if the element is the last one in the table, if not:
            out<<Hashtable[k]<<",";        //print out the element into the output file and follow with a comma
        } else {                            //If it is the last element:
            out<<Hashtable[k];             //Print it out to the console and do not follow with a comma
        }
    }
    
    out.clear ();       //clear the output file buffer
    out.close ();       //close the output file
}
