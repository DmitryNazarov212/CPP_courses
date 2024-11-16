#include <iostream>
#include <string>
using namespace std;
void computeLPS(string pat, int *lps) {
    int j = 0;
    lps[0] = 0;
    int i = 1;
    while(i < pat.length()) {
        if(pat[j] == pat[i]) {
            j++;
            lps[i] = j;
            i++;
        }
        else {
            if(j != 0) {
                j = lps[j - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}
void IsKPeriodic(const string &pat, const string &txt) {
    auto *lps = new int[pat.size()];
    computeLPS(pat,  lps);
    int i = 0;
    int j = 0;
    int counter = 0;
    while(i < txt.size()) {
        if(pat[j] == txt[i]){
            j++;
            i++;
        }
        if(j == pat.size()) {
            j = lps[j-1];
            counter++;
        }
        else if (i < txt.size() && pat[j] != txt[i]) {
            if(j != 0) {
                j = lps[j - 1];
            }
            else {
                i = i+1;
            }
        }
    }
    cout << "K equals " << counter << endl;
    delete[]lps;
}

int main() {
    const string str = "abcabcabcabcabc";
    const string pat = "abc";
    IsKPeriodic(pat, str);
    return 0;
}
