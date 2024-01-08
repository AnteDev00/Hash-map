#include <iostream>
#include <vector>
#include <chrono>

#include "List.h" // Custom linked list class for dealing with collisions

using namespace std;

vector<string> keywords = {
    "alignas", "alignof", "and", "and_eq", "asm", "auto", "bitand", "bitor", "bool", "break",
    "case", "catch", "char", "char8_t", "char16_t", "char32_t", "class", "compl", "concept", "const",
    "consteval", "constexpr", "const_cast", "continue", "co_await", "co_return", "co_yield", "decltype", "default", "delete",
    "do", "double", "dynamic_cast", "else", "enum", "explicit", "export", "extern", "false", "float",
    "for", "friend", "goto", "if", "inline", "int", "long", "mutable", "namespace", "new",
    "noexcept", "not", "not_eq", "nullptr", "operator", "or", "or_eq", "private", "protected", "public",
    "register", "reinterpret_cast", "requires", "return", "short", "signed", "sizeof", "static", "static_assert", "static_cast",
    "struct", "switch", "synchronized", "template", "this", "thread_local", "throw", "true", "try", "typedef",
    "typeid", "typename", "union", "unsigned", "using", "virtual", "void", "volatile", "wchar_t", "while"
};

const int DATASIZE = keywords.size(); // 90 elem
const int MAPSIZE = keywords.size() * 1.45; //LOAD Factor ~ 70%


int Hash(string keyword)
{
    return hash<string>{}(keyword) % MAPSIZE;
}

string FindKeyword(vector<List<string>*>& hashMap, int hashIndex, int listIndex)
{
    return hashMap[hashIndex]->nodeAt(listIndex);
}

int main() {
    vector<List<string>*> hashMap(MAPSIZE);

    // FILL
    for (int i = 0; i < DATASIZE; i++)
    {
        // Calc the hash
        int hashIndex = Hash(keywords[i]);

        // If it's first elem
        if (hashMap[hashIndex] == nullptr)
        {
            List<string>* tempList = new List<string>();
            hashMap[hashIndex] = tempList;
            hashMap[hashIndex]->addBack(keywords[i]);
        }
        else // if it's not first elem
        {
            hashMap[hashIndex]->addBack(keywords[i]);
        }
        // cout << keywords[i] << " - hashindex: " << hashIndex << endl;
    }


    //Lookup & Measuring
    auto start = chrono::high_resolution_clock::now();
    for ( int i = 0; i < DATASIZE; i++)
    {
        // Calc the hash
        int hashIndex = hash<string>{}(keywords[i]) % MAPSIZE;

        // Find the INDEX of elem
        int listIndex = hashMap[hashIndex]->findIndex(keywords[i]);

        // Access the elem
        string keyword = hashMap[hashIndex]->nodeAt(listIndex);
       
        //cout << "\nElement index: " << listIndex << " for " << keywords[i] << " in a linked list, at index:" << hashIndex;
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    

    // How many collisions happened and SOLVED
    int collisions = 0;
    for (int i = 0; i < DATASIZE; i++)
    {
        if(hashMap[i] != nullptr)
        collisions = collisions + hashMap[i]->getSize()-1;
    }


    // Loggin the data about speed and collisions
    cout << "\n\nAverage Lookup Time [ACCESS OPERATION]: " << duration.count() / DATASIZE << " nanoseconds" << endl; // output elapsed time in microseconds
    unsigned int nanosecInSec = 1'000'000'000;
    double MlookupPerSec = (static_cast<double>(nanosecInSec) / (duration.count() / DATASIZE)) / 1'000'000;
    cout << "\nThat is " << MlookupPerSec << " Milion lookup/s \n";

    cout << "\nCollisions: " << collisions << "\n";


    cout << "\n\n------------------------------------------------------------\n";


    // How much time to delete
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < DATASIZE; i++)
        if (hashMap[i] != nullptr)
        {
            int listSize = hashMap[i]->getSize();
            for(int j = 0; j < listSize; j++)
                hashMap[i]->deleteBack();
        }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start);

    // Loggin the data about speed
    cout << "\n\nAverage Lookup Time [DELETE OPRERATION]: " << duration.count() / DATASIZE << " nanoseconds" << endl; // output elapsed time in microseconds
    MlookupPerSec = (static_cast<double>(nanosecInSec) / (duration.count() / DATASIZE)) / 1'000'000;
    cout << "\nThat is " << MlookupPerSec << " Milion lookup/s \n";

    cout << "\n\n------------------------------------------------------------\n";


    // CleanUp 
    for (int i = 0; i < DATASIZE; i++)
    {
        delete hashMap[i];
    }
}
