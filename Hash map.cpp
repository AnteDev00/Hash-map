#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <chrono>

using namespace std;

vector<string> vKeywords = {
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

const int KEYWORDS_SIZE = vKeywords.size(); //90
const int SIZE_HASHMAP = vKeywords.size() * 1.41; // 30% free 70% not free


int main()
{
    unordered_map<int, string> hashMap;
        //hashMap.resize(SIZE_HASHMAP); //if you wanna use vector, then enable this code
    
    cout << SIZE_HASHMAP << "\n";

    //Fill 
    for (unsigned int i = 0; i < KEYWORDS_SIZE; i++)
    {
        unsigned int hashindex = hash<string>{}(vKeywords[i]) % SIZE_HASHMAP;
        hashMap[hashindex] = vKeywords[i];
            cout << vKeywords[i] << " - hashindex: " << hashindex << endl;
    }
    
    //Lookup & Measuring
    auto start = chrono::high_resolution_clock::now();
    for (unsigned int i = 0; i < KEYWORDS_SIZE; i++)
    {
        unsigned int hashIndex = hash<string>{}(vKeywords[i]) % SIZE_HASHMAP;
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    
    //Collision check
    unsigned int collisions = 0;
    for (unsigned int i = 0; i < KEYWORDS_SIZE - 1; i++)
    {
        unsigned int first_index= hash<string>{}(vKeywords[i]) % SIZE_HASHMAP;
        for (unsigned int j = i + 1; j < KEYWORDS_SIZE; j++)
        {
            unsigned int second_index = hash<string>{}(vKeywords[j]) % SIZE_HASHMAP;
            if ((hash<string>{}(vKeywords[i]) % SIZE_HASHMAP) == (hash<string>{}(vKeywords[j])) % SIZE_HASHMAP)
            {
                cout << "Collision between index: " << first_index << "and " << second_index << endl;
                collisions++;
            }
        }
    }
    
    //Log
    cout << "\n\nAverage Lookup Time: " << duration.count() / KEYWORDS_SIZE << " nanoseconds" << endl; // output elapsed time in microseconds
    unsigned int nanosecInSec = 1'000'000'000;
    double MlookupPerSec = (static_cast<double>(nanosecInSec) / (duration.count() / KEYWORDS_SIZE) ) / 1'000'000;
    cout << "\nThat is " << MlookupPerSec << " Milion lookup/s \n";
    cout << "\nCollisions: " << collisions << "  \n";

    cin.get();
}




// old code
/*
    //Fill
    vector<string> vectorMap(vKeywords.size());
    for (int i = 0; i < vKeywords.size(); i++)
    {
        vectorMap[i] = vKeywords[i];
    }
    
    //Lookup 
    start = chrono::high_resolution_clock::now();
    int index2;
    string keyword2;
    for (int i = 0; i < SIZE_KEYWORDS; i++)
    {
        for (int j = 0; j < vectorMap.size(); j++)
        {
            if (vKeywords[i] == vectorMap[j]) index2 = j;
        }
        vectorMap[index2] = "";
    }
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start);

    //Log
    cout << "\n\nLookup time: " << duration.count() / vKeywords.size() << " nanoseconds" << endl; // output elapsed time in microseconds
    nanosecInSec = 1'000'000'000;
    lookupPerSec = nanosecInSec / (duration.count() / vKeywords.size());
    cout << "\n That is " << lookupPerSec << " lookup/s \n";

    return 0;

*/


