#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool ends_with(string word, string ending) {
    size_t found = word.rfind(ending);
    return (found != string::npos && (found == (word.size() - ending.size()))); 
}

bool match_ending(string word, vector<string> endings) {
    for(unsigned i = 0; i < endings.size(); i++) {
        if (ends_with(word, endings[i])) {
            return true;
        }
    }
    return false;
}

vector<string> endings[20];
string buffer;
string ending_line;
int main(){
    int e,start;
    int pos;

    string common_word;
    getline(cin, common_word);

    getline(cin, buffer);
    e = std::stoi(buffer);

    // Get all of the endings.
    for(int i=0; i < e; i++) {
        start = 0;
        pos = 0;
        getline(cin, ending_line);

        while(pos < ending_line.size() && pos != -1) {
            pos = ending_line.find(' ', start);
            if ( pos > -1) {
                endings[i].push_back(string(ending_line.substr(start, pos - start)));
                start = pos + 1;
            } else {
                endings[i].push_back(ending_line.substr(start, ending_line.size() - start));
            }
        }
    }

    // Find the ending lists that actually matter.
    vector<vector<string>> matching_endings;
    for(int i = 0; i < e; i++) {
        if (match_ending(common_word, endings[i])) {
            matching_endings.push_back(endings[i]);
        }
    }

    getline(cin, buffer);
    int p = std::stoi(buffer);

    bool rhymes;
    for(int i = 0; i < p; i++) {
        getline(cin, ending_line);
        rhymes = false;
        for(int j = 0; j < matching_endings.size(); j++) {
            if (match_ending(ending_line, matching_endings[j])) {
                rhymes = true;
                continue;
            }
        }
        cout << (rhymes ? "YES" : "NO") << '\n';
    }
};
