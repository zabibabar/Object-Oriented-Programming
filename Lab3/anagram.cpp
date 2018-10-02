#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "lettercount.h"
void anagram(LetterCount& oth, const vector<LetterCount>& obj, vector<int>& idx, vector <vector<int>>& idc);

int main ()
{
    string str;
    vector <LetterCount> dict;
    vector <int> index;
    vector <vector<int>> indices;

    ifstream in("dictionary.txt");

    while(getline(in, str))
    {
        int length = str.length();
        char* word = new char[length];

        for(int i = 0; i < length; i++)
            word[i] = str[i];

        LetterCount words(word);
        dict.push_back(words);
    }

    cout << "Type a word or phrase you want the anagrams for: ";
    getline(cin, str);

    int length = str.length();
    char* phrase = new char[length];
    for(int i = 0; i < length+1; i++)
        phrase[i] = str[i];

    LetterCount input(phrase);

    anagram(input, dict, index, indices);
    cout << "Total words in the dictionary: " << dict.size() << endl;
    cout <<  indices.size() << " anagrams found for " << str << "." << endl;

    for (unsigned int i = 0; i < indices.size(); i++)
    {
        for (unsigned int j = 0; j < indices[i].size(); j++)
        {
            string str;
            ifstream words ("dictionary.txt");
            int line = 0;
            while (getline(words, str))
            {
                if (line == indices[i][j])
                {
                    cout << str << " ";
                    break;
                }
                line++;
            }
        }
        cout << endl;
    }
    delete [] phrase;
}
void anagram(LetterCount& oth, const vector<LetterCount>& obj, vector<int>& index, vector <vector<int>>& indices)
{
    for (unsigned int i = 0; i < obj.size(); i++)
    {
        if (oth.equals(obj[i]))
        {
            index.push_back(i);
            indices.push_back(index);
            index.pop_back();
        }
        if (oth.hasAsMany(obj[i]) && !oth.equals(obj[i]))
        {
            index.push_back(i);
            oth.subtract(obj[i]);
            if (oth.totalCount() > 2)
                anagram(oth, obj, index, indices);
            else
            {
                oth.add(obj[i]);
                index.pop_back();
            }
        }
        //cout << i << " " << index.size() << " "; oth.print();
        if (i == obj.size()-1)
        {
            if (index.size() > 0)
                oth.add(obj[index.back()]);
            index.pop_back();
        }
    }
}
