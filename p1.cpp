#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

int main(int argc, char *argv[]){

    string keyword = argv[3];

    ifstream keyFile(argv[1]);
    if (!keyFile){
        cout << "Could not access " << argv[1] << endl;
        return 0;
    }

    string fAlpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string alpha, encodeRep;

    getline(keyFile, alpha);
    getline(keyFile, encodeRep);

    keyFile.close();

    ifstream encodeFile(argv[2]);
    if (!encodeFile){
        cout << "Could not access " << argv[2] << endl;
        return 0;
    }

    string codeIn;
    bool keywordChosen = false;

    while(encodeFile >> codeIn){
        int numAlpha = 0;
        string newStr;

        for (int i = 0; i < codeIn.length(); i++){
            if(isalpha(codeIn.at(i))){
                numAlpha++;
                newStr += codeIn.at(i);
            }
        }

        if (numAlpha == keyword.length() && keywordChosen == false){
            codeIn = newStr;
            bool maybeKey = true;
            int foundCount = 0;
            
            for (int i = 0; i < codeIn.length(); i++){
                for (int j = 0; j < alpha.length(); j++){
                    if (codeIn.at(i) == encodeRep.at(j)){
                        codeIn.at(i) = alpha.at(j);
                        if (codeIn.at(i) != keyword.at(i)){
                            maybeKey = false;
                        }
                        foundCount++;
                        break;
                    }
                }
            }

            if (maybeKey == true || foundCount == 0){
                for(int j = 0; j < keyword.length(); j++){
                    if(codeIn.at(j) != keyword.at(j) && alpha.find(keyword.at(j)) == -1){
                        alpha += keyword.at(j);
                        encodeRep += codeIn.at(j);
                    }
                }
                codeIn = keyword;
                keywordChosen = true;
            }
        }
    }

    while(alpha.length() < 26){
        for (int i = 0; i < fAlpha.length(); i++){
            if (alpha.find(fAlpha.at(i)) == -1){
                alpha += fAlpha.at(i);
                break;
            }
        }
        for (int i = 0; i < fAlpha.length(); i++){
            if (encodeRep.find(fAlpha.at(i)) == -1){
                encodeRep += fAlpha.at(i);
                break;
            }
        }
    }
    encodeFile.close();

    ifstream finalFile(argv[2]);
    char ch;

    while (finalFile.get(ch)){
        if (isalpha(ch)){
            for (int i = 0; i < alpha.length(); i++){
                if (ch == encodeRep.at(i)){
                    ch = alpha.at(i);
                    break;
                }
            }
        }
        cout << ch;
    }
    finalFile.close();
}