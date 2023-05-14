#ifndef _P3_H_
#define _P3_H_

#include <iostream>
#include <string>

class Person {
public:
    std::string first;
    std::string last;
    int height;
    int weight;
    Person *nextHeight;
    Person *nextWeight;

    Person();
    Person(std::string first, std::string last, int height, int weight);
};

class PersonList {
private:
    Person *headHeightList;
    Person *headWeightList;
    int size;
public:
    PersonList();

    int getSize();
    void printByHeight(std::ostream &os);
    void printByWeight(std::ostream &os);

    bool exists(std::string first, std::string last);
    int getHeight(std::string first, std::string last);
    int getWeight(std::string first, std::string last);

    bool add(std::string first, std::string last, int height, int weight);
    bool remove(std::string first, std::string last);

    bool updateName(std::string first, std::string last, std::string newFirst, std::string newLast);
    bool updateHeight(std::string first, std::string last, int height);
    bool updateWeight(std::string first, std::string last, int weight);

    void deepCopy(const PersonList &src);
    ~PersonList();
    PersonList(const PersonList &src);
    const PersonList &operator=(const PersonList &src);
};

#endif
