#include <iostream>
#include <fstream>
#include <cstring>
#include <list>
#include <vector>
#include <cctype>
using namespace std;

unsigned long djb2(string str) {
   const char *ptr = str.c_str();
   unsigned long hash = 5381;
   int c;
   while ((c = *ptr++)) {
      hash = ((hash << 5) + hash) + c;
   }
   return hash;
}
class HashTable{
   private:
   vector<pair<string, vector<int>>> table;
   int collisions;

   public:
   HashTable();
   void resize(int size);
   int h1(string key);
   void hashInsert(string key, int value, string strat, int hashVal);
   void print();
   void statPrinter(int totWords);
   void querySearch(string key, string searchStrat, int hashVal);
};
HashTable::HashTable(){
   collisions = 0;
}
void HashTable::resize(int size){
   table.resize(size);
}
int HashTable::h1(string key){
   int index = djb2(key) % table.size();
   return index;
}
void HashTable::hashInsert(string key, int value, string strat, int hashVal){
   int size = table.size(), index = h1(key), j = 0;
   if(table[index].first.empty()){
      table[index].first = key;
      table[index].second.push_back(value);
      return;
   }
   else if (strat == "lp"){
      for (j = 0; j < size; j++){
         index = (h1(key) + j) % size;
         if (table[index].first.empty() || table[index].first == key){
            table[index].first = key;
            table[index].second.push_back(value);
            return;
         }
         else{
            collisions++;
         }
      }
   }
   else if (strat == "qp"){
      for (j = 0; j < size; j++){
         index = (h1(key) + j*j) % size;
         if (table[index].first.empty() || table[index].first == key){
            table[index].first = key;
            table[index].second.push_back(value);
            return;
         }
         else{
            collisions++;
         }
      }
   }
   else if (strat == "dh"){
       for (j = 0; j < size; j++){
         index = (h1(key) + j * (hashVal - (djb2(key) % hashVal))) % size;
         if (table[index].first.empty() || table[index].first == key){
            table[index].first = key;
            table[index].second.push_back(value);
            return;
         }
         else{
            collisions++;
         }
      }
   }
}
void HashTable::print(){
   for(int i = 0; i < table.size(); i++){
      cout << i << ": " << table[i].first << endl;
   }
}
void HashTable::statPrinter(int totWords){
   int uniqueWords = 0;
   for (int i = 0; i < table.size(); i++){
      if (!table[i].first.empty()){
         uniqueWords++;
      }
   }

   cout << "The number of words found in the file was " << totWords << endl;
   cout << "The number of unique words found in the file was " << uniqueWords << endl;
   cout << "The number of collisions was " << collisions << endl << endl;
}
void HashTable::querySearch(string key, string searchStrat, int hashVal){
   int collNum = 0, size = table.size(), index = djb2(key) % size;
   if (key == table[index].first || table[index].first.empty()){
      cout << key << " appears on lines " << "[";
      for (int i = 0; i < table[index].second.size(); i++){
         cout << table[index].second[i];
         if (i != table[index].second.size() - 1){
            cout << ",";
         }
      }
      cout << "]" << endl;
      cout << "The search had " << collNum << " collisions" << endl;
      return;
   }
   if (searchStrat == "lp"){
      while(1){
         collNum++;
         index = (djb2(key) + collNum) % size;
         if (key == table[index].first || table[index].first.empty()){
            cout << key << " appears on lines " << "[";
            for (int i = 0; i < table[index].second.size(); i++){
               cout << table[index].second[i];
               if (i != table[index].second.size() - 1){
                  cout << ",";
               }
            }
            cout << "]" << endl;
            cout << "The search had " << collNum << " collisions" << endl;
            return;
         }
      }
   }
   if (searchStrat == "qp"){
      while(1){
         collNum++;
         index = (djb2(key) + collNum * collNum) % size;
         if (key == table[index].first || table[index].first.empty()){
            cout << key << " appears on lines " << "[";
            for (int i = 0; i < table[index].second.size(); i++){
               cout << table[index].second[i];
               if (i != table[index].second.size() - 1){
                  cout << ",";
               }
            }
            cout << "]" << endl;
            cout << "The search had " << collNum << " collisions" << endl;
            return;
         }
      }
   }
   if (searchStrat == "dh"){
      while(1){
         collNum++;
         index = (djb2(key) + collNum * (hashVal - (djb2(key) % hashVal))) % size;
         if (key == table[index].first || table[index].first.empty()){
            cout << key << " appears on lines " << "[";
            for (int i = 0; i < table[index].second.size(); i++){
               cout << table[index].second[i];
               if (i != table[index].second.size() - 1){
                  cout << ",";
               }
            }
            cout << "]" << endl;
            cout << "The search had " << collNum << " collisions" << endl;
            return;
         }
      }
   }
}
//End of HashTable Class

int main(int argc, char **argv) {
   ifstream inFile(argv[1]);
   ifstream queryFile(argv[2]);
   int hashSize = stoi(argv[3]);
   string collStrat = argv[4];
   int dhValue;
   if (collStrat == "dh"){
      dhValue = stoi(argv[5]);
   }


   HashTable table;
   table.resize(hashSize);

   int lineCount = 1, wordCount = 0;
   string curWord, curLine;

   while(getline(inFile, curLine)){
      int lineLen = curLine.length();
      for (char c : curLine){
         if (isalpha(c)){
            curWord += tolower(c);
         }
         else if (curWord != ""){
            wordCount++;
            table.hashInsert(curWord, lineCount, collStrat, dhValue);
            curWord = "";
         }
      }
      if (curWord != ""){
         wordCount++;
         table.hashInsert(curWord, lineCount, collStrat, dhValue);
         curWord = "";
      }
      lineCount++;
   }

   //table.print();

   table.statPrinter(wordCount);

   string queryWord;
   vector<string> words;
   while(queryFile >> queryWord){
      words.push_back(queryWord);
   }

   for (int i = 0; i < words.size(); i++){
      table.querySearch(words[i], collStrat, dhValue);
      if (i < words.size() - 1){
         cout << endl;
      }
   }
   
   return 0;
}
