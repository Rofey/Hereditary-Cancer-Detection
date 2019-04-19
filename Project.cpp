#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define MAXHCHAR 256

class Cancer {
	private:
		string data, pattern;

	public:
		Cancer();
		Cancer(string data, string pattern);
		void search();
		bool BoyerMoore(string txt, string pat);
		int max(int a, int b);
		void LettersUsed(string str, int size, int badchar[256]);
		void display();


};

Cancer::Cancer(string data, string pattern) {
	this->data = data;
	this->pattern = pattern;
}

int Cancer::max(int a, int b) {
    return (a > b) ? a : b;
}
 
void Cancer::LettersUsed(string str, int size, int badchar[MAXHCHAR]) {
    int i;
 
    // takay garbage value na aye
    // Can put 0 too over here
    for (i = 0; i < MAXHCHAR; i++)
        badchar[i] = -1;
 
    for (i = 0; i < size; i++)
        badchar[(int) str[i]] = i;
}

bool Cancer::BoyerMoore(string txt, string pat) {

    int m = pat.size();
    int n = txt.size();
    int check = 0;
    int badchar[MAXHCHAR];
 
    LettersUsed(pat, m, badchar);
 
    int s = 0; 
    while (s <= (n - m))
    {
        int j = m - 1;
 
        while (j >= 0 && pat[j] == txt[s + j])
            j--;
 
        if (j < 0)
        {
            cout << "Pattern can be found on: " << s << endl;
 			check = 1;
            s += (s + m < n) ? m - badchar[txt[s + m]] : 1;
 
        }
 
        else
            s += max(1, j - badchar[txt[s + j]]);
    }
    return check;
}

void Cancer::search() {
	int dataLen = data.size();
	int patternLen = pattern.size();
	int charIndex, pattHash = 0, strHash = 0, h = 1;
	int prime = 101;
	int index = -1;
	int array[dataLen];
	bool check = 0;

	for(int i = 0; i<patternLen-1; i++) {
		h = (h*MAXHCHAR) % prime;
	}

	for(int i=0; i<patternLen; i++) {
		pattHash = (MAXHCHAR * pattHash + pattern[i]) % prime;
		strHash = (MAXHCHAR * strHash + data[i]) % prime;
	}

	for(int i=0; i<=(dataLen-patternLen); i++) {
		if(pattHash == strHash) {
			for(charIndex = 0; charIndex < patternLen; charIndex++) {
				if(data[i+charIndex] != pattern[charIndex])
					break;
			}

			if(charIndex == patternLen) {
				(index)++;
				array[(index)] = i;
				check = 1;

			} else check = 0;
		}

		if(i < (dataLen-patternLen)) {
			strHash = (MAXHCHAR*(strHash - data[i]*h) + data[i+patternLen]) % prime;
			if(strHash < 0) 
				strHash += prime;
		}
	}

	for(int i=0 ; i<index; i++) {
		cout << array[i] << endl;
	}
}




void Cancer::display() {
	cout << data;
}

int main() {
	ifstream patternFile;
	ifstream geneFile;
	ifstream pancreaticFile;
	ifstream uterineFile;
	ifstream breastFile;
	ifstream prostateFile;
 
	string prostate = "ATGAGTCTAGTACTTAATGATCTGCTTATCTGCTGCCGTCAACTAGAACATGATAGAGCTACAGAACGAAAGAAAGAAGTTGAGAAATTTAAGCGCCTGATTCGAGATCCTGAAACAATTAAACATCTAGATCGGCATTCAGATTCCAAACAAGGAAAATATTTGAATTGGGATGCTGTTTTTAGATTTTTACAGAAATATATTCAGAAAGAAACAGAATGTCTGAGAATAGCAAAACCAAATGTATCAGCCTCAACACAAGCCTCCAGGCAGAAAAAGATGCAGGAAATCAGTAGTTTGGTCAAATACTTCATCAAATGTGCAAACAGAAGAGCACCTAGGCTAAAATGTCAAGAACTCTTAAATTATATCATGGATACAGTGAAAGATTCATCTAATGGTGCTATTTACGGAGCTGATTGTAGCAACATACTACTCAAAGACATTCTTTCTGTGAGAAAATACTGGTGTGAAATATCTCAGCAACAGTGGTTAGAATTGTTCTCTGTGTACTTCAGGCTCTATCTGAAACCTTCACAAGATGTTCATAGAGTTTTAGTGGCTAGAATAATTCATGCTGTTACCAAAGGATGCTGTTCTCAGACTGACGGATTAAATTCCAAATTTTTGGACTTTTTTTCCAAGGCTATTCAGTGTGCGAGACAAGAAAAGAGCTCTTCAGGTCTAAATCATATCTTAGCAGCTCTTACTATCTTCCTCAAGACTTTGGCTGTCAACTTTCGAATTCGAGTGTGTGAATTAGGAGATGAAATTCTTCCCACTTTGCTTTATATTTGGACTCAACATAGGCTTAATGATTCTTTAAAAGAAGTCATTATTGAATTATTTCAACTGCAAATTTATATCCATCATCCGAAAGGAGCCAAAACCCAAGAAAAAGGTGCTTATGAATCAACAAAATGGAGAAGTATTTTATACAACTTATATGATCTGCTAGTGAATGAGATAAGTCATATAGGAAGTAGAGGAAAGTATTCTTCAGGATTTCGTAATATTGCCGTCAAAGAAAATTTGATTGAATTGATGGCAGATATCTGTCACCAGGTTTTTAATGAAGATACCAGATCCTTGGAGATTTCTCAATCTTACACTACTACACAAAGAGAATCTAGTGATTACAGTGTCCCTTGCAAAAGGAAGAAAATAGAACTAGGCTGGGAAGTAATAAAAGATCACCTTCAGAAGTCACAGAATGATTTTGATCTTGTGCCTTGGCTACAGATTGCAACCCAATTAATATCAAAGTATCCTGCAAGTTTACCTAACTGTGAGCTGTCTCCATTACTGATGATACTATCTCAGCTTCTACCCCAACAGCGACATGGGGAACGTACACCATATGTGTTACGATGCCTTACGGAAGTTGCATTGTGTCAAGACAAGAGGTCAAACCTAGAAAGCTCACAAAAGTCAGATTTATTAAAACTCTGGAATAAAATTTGGTGTATTACCTTTCGTGGTATAAGTTCTGAGCAAATACAAGCTGAAAACTTTGGCTTACTTGGAGCCATAATTCAGGGTAGTTTAGTTGAGGTTGACAGAGAATTCTGGAAGTTATTTACTGGGTCAGCCTGCAGACCTTCATGTCCTGCAGTATGCTGTTTGACTTTGGCACTGACCACCAGTATAGTTCCAGGAACGGTAAAAATGGGAATAGAGCAAAATATGTGTGAAGTAAATAGAAGCTTTTCTTTAAAGGAATCAATAATGAAATGGCTCTTATTCTATCAGTTAGAGGGTGACTTAGAAAATAGCACAGAAGTGCCTCCAATTCTTCACAGTAATTTTCCTCATCTTGTACTGGAGAAAATTCTTGTGAGTCTCACTATGAAAAACTGTAAAGCTGCAATGAATTTTTTCCAAAGCGTGCCAGAATGTGAACACCACCAAAAAGATAAAGAAGAACTTTCATTCTCAGAAGTAGAAGAACTATTTCTTCAGACAACTTTTGACAAGATGGACTTTTTAACCATTGTGAGAGAATGTGGTATAGAAAAGCACCAGTCCAGTATTGGCTTCTCTGTCCACCAGAATCTCAAGGAATCACTGGATCGCTGTCTTCTGGGATTATCAGAACAGCTTCTGAATAATTACTCATCTGAGATTACAAATTCAGAAACTCTTGTCCGGTGTTCACGTCTTTTGGTGGGTGTCCTTGGCTGCTACTGTTACATGGGTGTAATAGCTGAAGAGGAAGCATATAAGTCAGAATTATTCCAGAAAGCCAAGTCTCTAATGCAATGTGCAGGAGAAAGTATCACTCTGTTTAAAAATAAGACAAATGAGGAATTCAGAATTGGTTCCTTGAGAAATATGATGCAGCTATGTACACGTTGCTTGAGCAACTGTACCAAGAAGAGTCCAAATAAGATTGCATCTGGCTTTTTCCTGCGATTGTTAACATCAAAGCTAATGAATGACATTGCAGATATTTGTAAAAGTTTAGCATCCTTCATCAAAAAGCCATTTGACCGTGGAGAAGTAGAATCAATGGAAGATGATACTAATGGAAATCTAATGGAGGTGGAGGATCAGTCATCCATGAATCTATTTAACGATTACCCTGATAGTAGTGTTAGTGATGCAAACGAACCTGGAGAGAGCCAAAGTACCATAGGTGCCATTAATCCTTTAGCTGAAGAATATCTGTCAAAGCAAGATCTACTTTTCTTAGACATGCTCAAGTTCTTGTGTTTGTGTGTAACTACTGCTCAGACCAATACTGTGTCCTTTAGGGCAGCTGATATTCGGAGGAAATTGTTAATGTTAATTGATTCTAGCACGCTAGAACCTACCAAATCCCTCCACCTGCATATGTATCTAATGCTTTTAAAGGAGCTTCCTGGAGAAGAGTACCCCTTGCCAATGGAAGATGTTCTTGAACTTCTGAAACCACTATCCAATGTGTGTTCTTTGTATCGTCGTGACCAAGATGTTTGTAAAACTATTTTAAACCATGTCCTTCATGTAGTGAAAAACCTAGGTCAAAGCAATATGGACTCTGAGAACACAAGGGATGCTCAAGGACAGTTTCTTACAGTAATTGGAGCATTTTGGCATCTAACAAAGGAGAGGAAATATATATTCTCTGTAAGAATGGCCCTAGTAAATTGCCTTAAAACTTTGCTTGAGGCTGATCCTTATTCAAAATGGGCCATTCTTAATGTAATGGGAAAAGACTTTCCTGTAAATGAAGTATTTACACAATTTCTTGCTGACAATCATCACCAAGTTCGCATGTTGGCTGCAGAGTCAATCAATAGATTGTTCCAGGACACGAAGGGAGATTCTTCCAGGTTACTGAAAGCACTTCCTTTGAAGCTTCAGCAAACAGCTTTTGAAAATGCATACTTGAAAGCTCAGGAAGGAATGAGAGAAATGTCCCATAGTGCTGAGAACCCTGAAACTTTGGATGAAATTTATAATAGAAAATCTGTTTTACTGACGTTGATAGCTGTGGTTTTATCCTGTAGCCCTATCTGCGAAAAACAGGCTTTGTTTGCCCTGTGTAAATCTGTGAAAGAGAATGGATTAGAACCTCACCTTGTGAAAAAGGTTTTAGAGAAAGTTTCTGAAACTTTTGGATATAGACGTTTAGAAGACTTTATGGCATCTCATTTAGATTATCTGGTTTTGGAATGGCTAAATCTTCAAGATACTGAATACAACTTATCTTCTTTTCCTTTTATTTTATTAAACTACACAAATATTGAGGATTTCTATAGATCTTGTTATAAGGTTTTGATTCCACATCTGGTGATTAGAAGTCATTTTGATGAGGTGAAGTCCATTGCTAATCAGATTCAAGAGGACTGGAAAAGTCTTCTAACAGACTGCTTTCCAAAGATTCTTGTAAATATTCTTCCTTATTTTGCCTATGAGGGTACCAGAGACAGTGGGATGGCACAGCAAAGAGAGACTGCTACCAAGGTCTATGATATGCTTAAAAGTGAAAACTTATTGGGAAAACAGATTGATCACTTATTCATTAGTAATTTACCAGAGATTGTGGTGGAGTTATTGATGACGTTACATGAGCCAGCAAATTCTAGTGCCAGTCAGAGCACTGACCTCTGTGACTTTTCAGGGGATTTGGATCCTGCTCCTAATCCACCTCATTTTCCATCGCATGTGATTAAAGCAACATTTGCCTATATCAGCAATTGTCATAAAACCAAGTTAAAAAGCATTTTAGAAATTCTTTCCAAAAGCCCTGATTCCTATCAGAAAATTCTTCTTGCCATATGTGAGCAAGCAGCTGAAACAAATAATGTTTATAAGAAGCACAGAATTCTTAAAATATATCACCTGTTTGTTAGTTTATTACTGAAAGATATAAAAAGTGGCTTAGGAGGAGCTTGGGCCTTTGTTCTTCGAGACGTTATTTATACTTTGATTCACTATATCAACCAAAGGCCTTCTTGTATCATGGATGTGTCATTACGTAGCTTCTCCCTTTGTTGTGACTTATTAAGTCAGGTTTGCCAGACAGCCGTGACTTACTGTAAGGATGCTCTAGAAAACCATCTTCATGTTATTGTTGGTACACTTATACCCCTTGTGTATGAGCAGGTGGAGGTTCAGAAACAGGTATTGGACTTGTTGAAATACTTAGTGATAGATAACAAGGATAATGAAAACCTCTATATCACGATTAAGCTTTTAGATCCTTTTCCTGACCATGTTGTTTTTAAGGATTTGCGTATTACTCAGCAAAAAATCAAATACAGTAGAGGACCCTTTTCACTCTTGGAGGAAATTAACCATTTTCTCTCAGTAAGTGTTTATGATGCACTTCCATTGACAAGACTTGAAGGACTAAAGGATCTTCGAAGACAACTGGAACTACATAAAGATCAGATGGTGGACATTATGAGAGCTTCTCAGGATAATCCGCAAGATGGGATTATGGTGAAACTAGTTGTCAATTTGTTGCAGTTATCCAAGATGGCAATAAACCACACTGGTGAAAAAGAAGTTCTAGAGGCTGTTGGAAGCTGCTTGGGAGAAGTGGGTCCTATAGATTTCTCTACCATAGCTATACAACATAGTAAAGATGCATCTTATACCAAGGCCCTTAAGTTATTTGAAGATAAAGAACTTCAGTGGACCTTCATAATGCTGACCTACCTGAATAACACACTGGTAGAAGATTGTGTCAAAGTTCGATCAGCAGCTGTTACCTGTTTGAAAAACATTTTAGCCACAAAGACTGGACATAGTTTCTGGGAGATTTATAAGATGACAACAGATCCAATGCTGGCCTATCTACAGCCTTTTAGAACATCAAGAAAAAAGTTTTTAGAAGTACCCAGATTTGACAAAGAAAACCCTTTTGAAGGCCTGGATGATATAAATCTGTGGATTCCTCTAAGTGAAAATCATGACATTTGGATAAAGACACTGACTTGTGCTTTTTTGGACAGTGGAGGCACAAAATGTGAAATTCTTCAATTATTAAAGCCAATGTGTGAAGTGAAAACTGACTTTTGTCAGACTGTACTTCCATACTTGATTCATGATATTTTACTCCAAGATACAAATGAATCATGGAGAAATCTGCTTTCTACACATGTTCAGGGATTTTTCACCAGCTGTCTTCGACACTTCTCGCAAACGAGCCGATCCACAACCCCTGCAAACTTGGATTCAGAGTCAGAGCACTTTTTCCGATGCTGTTTGGATAAAAAATCACAAAGAACAATGCTTGCTGTTGTGGACTACATGAGAAGACAAAAGAGACCTTCTTCAGGAACAATTTTTAATGATGCTTTCTGGCTGGATTTAAATTATCTAGAAGTTGCCAAGGTAGCTCAGTCTTGTGCTGCTCACTTTACAGCTTTACTCTATGCAGAAATCTATGCAGATAAGAAAAGTATGGATGATCAAGAGAAAAGAAGTCTTGCATTTGAAGAAGGAAGCCAGAATACAACTATTTCTAGCTTGAGTGAAAAAAGTAAAGAAGAAACTGGAATAAGTTTACAGGATCTTCTCTTAGAAATCTACAGAAGTATAGGGGAGCCAGATAGTTTGTATGGCTGTGGTGGAGGGAAGATGTTACAACCCATTACTAGACTACGAACATATGAACACGAAGCAATGTGGGGCAAAGCCCTAGTAACATATGACCTCGAAACAGCAATCCCCTCATCAACACGCCAGGCAGGAATCATTCAGGCCTTGCAGAATTTGGGACTCTGCCATATTCTTTCCGTCTATTTAAAAGGATTGGATTATGAAAATAAAGACTGGTGTCCTGAACTAGAAGAACTTCATTACCAAGCAGCATGGAGGAATATGCAGTGGGACCATTGCACTTCCGTCAGCAAAGAAGTAGAAGGAACCAGTTACCATGAATCATTGTACAATGCTCTACAATCTCTAAGAGACAGAGAATTCTCTACATTTTATGAAAGTCTCAAATATGCCAGAGTAAAAGAAGTGGAAGAGATGTGTAAGCGCAGCCTTGAGTCTGTGTATTCGCTCTATCCCACACTTAGCAGGTTGCAGGCCATTGGAGAGCTGGAAAGCATTGGGGAGCTTTTCTCAAGATCAGTCACACATAGACAACTCTCTGAAGTATATATTAAGTGGCAGAAACACTCCCAGCTTCTCAAGGACAGTGATTTTAGTTTTCAGGAGCCTATCATGGCTCTACGCACAGTCATTTTGGAGATCCTGATGGAAAAGGAAATGGACAACTCACAAAGAGAATGTATTAAGGACATTCTCACCAAACACCTTGTAGAACTCTCTATACTGGCCAGAACTTTCAAGAACACTCAGCTCCCTGAAAGGGCAATATTTCAAATTAAACAGTACAATTCAGTTAGCTGTGGAGTCTCTGAGTGGCAGCTGGAAGAAGCACAAGTATTCTGGGCAAAAAAGGAGCAGAGTCTTGCCCTGAGTATTCTCAAGCAAATGATCAAGAAGTTGGATGCCAGCTGTGCAGCGAACAATCCCAGCCTAAAACTTACATACACAGAATGTCTGAGGGTTTGTGGCAACTGGTTAGCAGAAACGTGCTTAGAAAATCCTGCGGTCATCATGCAGACCTATCTAGAAAAGGCAGTAGAAGTTGCTGGAAATTATGATGGAGAAAGTAGTGATGAGCTAAGAAATGGAAAAATGAAGGCATTTCTCTCATTAGCCCGGTTTTCAGATACTCAATACCAAAGAATTGAAAACTACATGAAATCATCGGAATTTGAAAACAAGCAAGCTCTCCTGAAAAGAGCCAAAGAGGAAGTAGGTCTCCTTAGGGAACATAAAATTCAGACAAACAGATACACAGTAAAGGTTCAGCGAGAGCTGGAGTTGGATGAATTAGCCCTGCGTGCACTGAAAGAGGATCGTAAACGCTTCTTATGTAAAGCAGTTGAAAATTATATCAACTGCTTATTAAGTGGAGAAGAACATGATATGTGGGTATTCCGACTTTGTTCCCTCTGGCTTGAAAATTCTGGAGTTTCTGAAGTCAATGGCATGATGAAGAGAGACGGAATGAAGATTCCAACATATAAATTTTTGCCTCTTATGTACCAATTGGCTGCTAGAATGGGGACCAAGATGATGGGAGGCCTAGGATTTCATGAAGTCCTCAATAATCTAATCTCTAGAATTTCAATGGATCACCCCCATCACACTTTGTTTATTATACTGGCCTTAGCAAATGCAAACAGAGATGAATTTCTGACTAAACCAGAGGTAGCCAGAAGAAGCAGAATAACTAAAAATGTGCCTAAACAAAGCTCTCAGCTTGATGAGGATCGAACAGAGGCTGCAAATAGAATAATATGTACTATCAGAAGTAGGAGACCTCAGATGGTCAGAAGTGTTGAGGCACTTTGTGATGCTTATATTATATTAGCAAACTTAGATGCCACTCAGTGGAAGACTCAGAGAAAAGGCATAAATATTCCAGCAGACCAGCCAATTACTAAACTTAAGAATTTAGAAGATGTTGTTGTCCCTACTATGGAAATTAAGGTGGACCACACAGGAGAATATGGAAATCTGGTGACTATACAGTCATTTAAAGCAGAATTTCGCTTAGCAGGAGGTGTAAATTTACCAAAAATAATAGATTGTGTAGGTTCCGATGGCAAGGAGAGGAGACAGCTTGTTAAGGGCCGTGATGACCTGAGACAAGATGCTGTCATGCAACAGGTCTTCCAGATGTGTAATACATTACTGCAGAGAAACACGGAAACTAGGAAGAGGAAATTAACTATCTGTACTTATAAGGTGGTTCCCCTCTCTCAGCGAAGTGGTGTTCTTGAATGGTGCACAGGAACTGTCCCCATTGGTGAATTTCTTGTTAACAATGAAGATGGTGCTCATAAAAGATACAGGCCAAATGATTTCAGTGCCTTTCAGTGCCAAAAGAAAATGATGGAGGTGCAAAAAAAGTCTTTTGAAGAGAAATATGAAGTCTTCATGGATGTTTGCCAAAATTTTCAACCAGTTTTCCGTTACTTCTGCATGGAAAAATTCTTGGATCCAGCTATTTGGTTTGAGAAGCGATTGGCTTATACGCGCAGTGTAGCTACTTCTTCTATTGTTGGTTACATACTTGGACTTGGTGATAGACATGTACAGAATATCTTGATAAATGAGCAGTCAGCAGAACTTGTACATATAGATCTAGGTGTTGCTTTTGAACAGGGCAAAATCCTTCCTACTCCTGAGACAGTTCCTTTTAGACTCACCAGAGATATTGTGGATGGCATGGGCATTACGGGTGTTGAAGGTGTCTTCAGAAGATGCTGTGAGAAAACCATGGAAGTGATGAGAAACTCTCAGGAAACTCTGTTAACCATTGTAGAGGTCCTTCTATATGATCCACTCTTTGACTGGACCATGAATCCTTTGAAAGCTTTGTATTTACAGCAGAGGCCGGAAGATGAAACTGAGCTTCACCCTACTCTGAATGCAGATGACCAAGAATGCAAACGAAATCTCAGTGATATTGACCAGAGTTTCAACAAAGTAGCTGAACGTGTCTTAATGAGACTACAAGAGAAACTGAAAGGAGTGGAAGAAGGCACTGTGCTCAGTGTTGGTGGACAAGTGAATTTGCTCATACAGCAGGCCATAGACCCCAAAAATCTCAGCCGACTTTTCCCAGGATGGAAAGCTTGGGTGTGAatgtctcgggagtcggatgttgaggctcagcagtctcatggcagcagtgcctgttcacagccccatggcagcgttacccagtcccaaggctcctcctcacagtcccagggcatatccagctcctctaccagcacgatgccaaactccagccagtcctctcactccagctctgggacactgagctccttagagacagtgtccactcaggaactctattctattcctgaggaccaagaacctgaggaccaagaacctgaggagcctacccctgccccctgggctcgattatgggcccttcaggatggatttgccaatcttgaatgtgtgaatgacaactactggtttgggagggacaaaagctgtgaatattgctttgatgaaccactgctgaaaagaacagataaataccgaacatacagcaagaaacactttcggattttcagggaagtgggtcctaaaaactcttacattgcatacatagaagatcacagtggcaatggaacctttgtaaatacagagcttgtagggaaaggaaaacgccgtcctttgaataacaattctgaaattgcactgtcactaagcagaaataaagtttttgtcttttttgatctgactgtagatgatcagtcagtttatcctaaggcattaagagatgaatacatcatgtcaaaaactcttggaagtggtgcctgtggagaggtaaagctggctttcgagaggaaaacatgtaagaaagtagccataaagatcatcagcaaaaggaagtttgctattggttcagcaagagaggcagacccagctctcaatgttgaaacagaaatagaaattttgaaaaagctaaatcatccttgcatcatcaagattaaaaacttttttgatgcagaagattattatattgttttggaattgatggaagggggagagctgtttgacaaagtggtggggaataaacgcctgaaagaagctacctgcaagctctatttttaccagatgctcttggctgtgcagtaccttcatgaaaacggtattatacaccgtgacttaaagccagagaatgttttactgtcatctcaagaagaggactgtcttataaagattactgattttgggcactccaagattttgggagagacctctctcatgagaaccttatgtggaacccccacctacttggcgcctgaagttcttgtttctgttgggactgctgggtataaccgtgctgtggactgctggagtttaggagttattctttttatctgccttagtgggtatccacctttctctgagcataggactcaagtgtcactgaaggatcagatcaccagtggaaaatacaacttcattcctgaagtctgggcagaagtctcagagaaagctctggaccttgtcaagaagttgttggtagtggatccaaaggcacgttttacgacagaagaagccttaagacacccgtggcttcaggatgaagacatgaagagaaagtttcaagatcttctgtctgaggaaaatgaatccacagctctaccccaggttctagcccagccttctactagtcgaaagcggccccgtgaaggggaagccgagggtgccgagaccacaaagcgcccagctgtgtgtgctgctgtgttgtga";
	string colon = "atgacagccatcatcaaagagatcgttagcagaaacaaaaggagatatcaagaggatggattcgacttagacttgacctatatttatccaaacattattgctatgggatttcctgcagaaagacttgaaggcgtatacaggaacaatattgatgatgtagtaaggtttttggattcaaagcataaaaaccattacaagatatacaatctttgtgctgaaagacattatgacaccgccaaatttaattgcagagttgcacaatatccttttgaagaccataacccaccacagctagaacttatcaaacccttttgtgaagatcttgaccaatggctaagtgaagatgacaatcatgttgcagcaattcactgtaaagctggaaagggacgaactggtgtaatgatatgtgcatatttattacatcggggcaaatttttaaaggcacaagaggccctagatttctatggggaagtaaggaccagagacaaaaagggagtaactattcccagtcagaggcgctatgtgtattattatagctacctgttaaagaatcatctggattatagaccagtggcactgttgtttcacaagatgatgtttgaaactattccaatgttcagtggcggaacttgcaatcctcagtttgtggtctgccagctaaaggtgaagatatattcctccaattcaggacccacacgacgggaagacaagttcatgtactttgagttccctcagccgttacctgtgtgtggtgatatcaaagtagagttcttccacaaacagaacaagatgctaaaaaaggacaaaatgtttcacttttgggtaaatacattcttcataccaggaccagaggaaacctcagaaaaagtagaaaatggaagtctatgtgatcaagaaatcgatagcatttgcagtatagagcgtgcagataatgacaaggaatatctagtacttactttaacaaaaaatgatcttgacaaagcaaataaagacaaagccaaccgatacttttctccaaattttaaggtgaagctgtacttcacaaaaacagtagaggagccgtcaaatccagaggctagcagttcaacttctgtaacaccagatgttagtgacaatgaacctgatcattatagatattctgacaccactgactctgatccagagaatgaaccttttgatgaagatcagcatacacaaattacaaaagtctgaatggaggtggtggacccgcagcagctgggcatgttcacggagggcgagctgatgtcggtgggtatggacacgttcatccaccgcatcgactccaccgaggtcatctaccagccgcgccgcaagcgggccaagctcatcggcaagtacctgatgggggacctgctgggggaaggctcttacggcaaggtgaaggaggtgctggactcggagacgctgtgcaggagggccgtcaagatcctcaagaagaagaagttgcgaaggatccccaacggggaggccaacgtgaagaaggaaattcaactactgaggaggttacggcacaaaaatgtcatccagctggtggatgtgttatacaacgaagagaagcagaaaatgtatatggtgatggagtactgcgtgtgtggcatgcaggaaatgctggacagcgtgccggagaagcgtttcccagtgtgccaggcccacgggtacttctgtcagctgattgacggcctggagtacctgcatagccagggcattgtgcacaaggacatcaagccggggaacctgctgctcaccaccggtggcaccctcaaaatctccgacctgggcgtggccgaggcactgcacccgttcgcggcggacgacacctgccggaccagccagggctccccggctttccagccgcccgagattgccaacggcctggacaccttctccggcttcaaggtggacatctggtcggctggggtcaccctctacaacatcaccacgggtctgtaccccttcgaaggggacaacatctacaagttgtttgagaacatcgggaaggggagctacgccatcccgggcgactgtggccccccgctctctgacctgctgaaagggatgcttgagtacgaaccggccaagaggttctccatccggcagatccggcagcacagctggttccggaagaaacatcctccggctgaagcaccagtgcccatcccaccgagcccagacaccaaggaccggtggcgcagcatgactgtggtgccgtacttggaggacctgcacggcgcggacgaggacgaggacctcttcgacatcgaggatgacatcatctacactcaggacttcacggtgcccggacaggtcccagaagaggaggccagtcacaatggacagcgccggggcctccccaaggccgtgtgtatgaacggcacagaggcggcgcagctgagcaccaaatccagggcggagggccgggcccccaaccctgcccgcaaggcctgctccgccagcagcaagatccgccggctgtcggcctgcaagcagcagtgaagcagcaagatccgccggctgtcggcctgcaagcagcagtga";

	patternFile.open("colon.txt");
	geneFile.open("Homo_sapiens.GRCh38.dna.chromosome.9.txt");
	string patternData;
	string geneData;

	pancreaticFile.open("pancreatic.txt");
	string p;
	getline(pancreaticFile, p);

	uterineFile.open("uterine.txt");
	string u;
	getline(uterineFile, u);

	breastFile.open("breast.txt");
	string br;
	getline(breastFile, br);

	prostateFile.open("prostate.txt");
	string pr;
	getline(prostateFile, pr);




//	patternFile.sync();
//	patternFile >> patternData;
	

	string a;
	while(getline(geneFile, geneData)) {
		a += geneData; 

	}

	string b;
	while(getline(patternFile, patternData)) {
		b += patternData; 
	}

	Cancer cancer(a, colon);

	if(cancer.BoyerMoore(a, b)) {
		cout << "\nThis gene contains Colon Cancer\n\n";
	}
	else cout << "\nDoesn't contain Colon Cancer";

	if(cancer.BoyerMoore(a,p))
		cout << "\nContains Pancreatic Cancer\n\n";
	else cout << "\nDoesn't contain Pancreatic Cancer\n\n";

	if(cancer.BoyerMoore(a,u))
		cout << "\nContains Uterine Cancer\n\n";
	else cout << "\nDoesn't contain Uterine Cancer";

	if(cancer.BoyerMoore(a, br))
		cout << "\nContains Breast Cancer too\n\n";
	else cout << "\nDoesn't contain Breast Cancer";

	if(cancer.BoyerMoore(a, pr))
		cout << "\nContains prostate Cancer too\n\n";
	else cout << "\nDoesn't contain prostate Cancer";

}