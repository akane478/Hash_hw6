//
//  main.cpp
//  cash_pipe
//
//  Created by Allison Kane on 4/24/16.
//  Copyright © 2016 Allison Kane. All rights reserved.
//

    
#include <iostream>
#include <fstream>
#include <string>
//#include <vector>
#include <cstring>
#include <cstdlib>
#define MIN_TABLE_SIZE 100

using namespace std;

int hashbrowns(int key);
bool QP (int key, int *& hash_table, int i_val);



int hashbrowns(int key) //hash function
{
    string a, b, c, d;
    string temp2 = to_string(key);      //this extracts the 2,4, 6. and 7 index of each number and
                                        //  turns it into a string
    a = temp2[2];
    b = temp2[4];
    c = temp2[6];
    d = temp2[7];
    temp2 = a + b + c + d;
    int temp3 = stoi(temp2);
    //cout << temp3 % 65000 << endl;
    return temp3 % 65000;
}



int main()
{
    ifstream in;
    string filename = "everybodys_socials.txt"; //file that gets read in (65000 social security numbers
    in.open(filename.c_str());
    int temp;
    char comma = ',';
    int socials[65000];
    int count;
    string temp2;

    
    if(!in.is_open())           //opens file
        {
        cout<<"File not found"<<endl;
        }
    
    while(in.peek()!=EOF)       //while loop separates the numbers and puts it into a hash array
        {
            while (in >> temp)
                {
                    socials[count++] = temp;
            
                    if (in >> comma && comma != ',')
                        {
                            cerr << "expected a comma between numbers, not '" << comma << "'\n";
                            exit(1);
                        }
                }
        }
    cout << "Count: "<<count<<endl; //counts how many numbers are in array
    
    for(int i = 0; i < 65000; i++)
        {
            cout<< socials[i]<<endl; //prints out hash array of social security numbers
        }
    
    int myint;
    while(!(myint < 450000000 && myint > 0)) //the use is prompted for a number between 1 and 450,000,000 for the quadratic
                                             //probing funtion. I don't know why.
        {
            cout<<"Enter a number between 1 and 450000000"<< endl;
            cin>>myint;
        }
    in.close();
    int *rehash=new int [65000];
    for(int i = 0; i < 65000; i++)
        {
            cout << i << endl; cout.flush();

            int index = hashbrowns(socials[i]);
            
            if (rehash[index] == 0)
            {
                rehash[index] = socials[i];
            }
            else
            {
                cout << "There's been a violent collision. We can resolve it!\n";
                QP(socials[i], rehash, myint);
            }
        }
    cout << "HERE"; cout.flush();
    ofstream out;
    out.open("hashed_socials.txt");
    out << "we are writing the new hash table! " << endl;
    for(int i=0; i<64999; i++)
        out << rehash[i] << ",";
    
    out << rehash[64999];
    out.close();
}

    
bool QP(int key, int *&hash_table, int i_val) //quadratic probing function
{
    int pos = hashbrowns(key);
    int new_pos;
    int i;
    for (i=0; i<65000; i++)
        {
            new_pos = (pos + ((i_val+i) *(i_val+i))) % 65000;
            
            if (hash_table[new_pos] == 0)
            {
                hash_table[pos] = key;
                //cout << key;
                return true;
            }
        }
    return false;
}

