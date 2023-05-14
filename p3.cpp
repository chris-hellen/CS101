#include <iostream>
#include <string>

#include "p3.h"

using namespace std;

Person::Person(){
    this->height = 0;
    this->weight = 0;
    this->nextHeight = nullptr;
    this->nextWeight = nullptr;
}

Person::Person(string first, string last, int height, int weight){
    this->first = first;
    this->last = last;
    this->height = height;
    this->weight = weight;
    this->nextHeight = nullptr;
    this->nextWeight = nullptr;
}

PersonList::PersonList(){
    this->size = 0;
    this->headHeightList = nullptr;
    this->headWeightList = nullptr;
}

int PersonList::getSize(){
    int size = 0;
    for(Person *cur = this->headHeightList; cur != nullptr; cur = cur->nextHeight){
        size++;
    }
    return size;
}

void PersonList::printByHeight(ostream &os){
    for (Person *cur = this->headHeightList; cur != nullptr; cur = cur->nextHeight){
        os << cur->first << " " << cur->last << ": height=" << cur->height << ", weight=" << cur->weight << endl;
    }
}

void PersonList::printByWeight(ostream &os){
    for (Person *cur = this->headWeightList; cur != nullptr; cur = cur->nextWeight){
        os << cur->first << " " << cur->last << ": height=" << cur->height << ", weight=" << cur->weight << endl;
    }
}

bool PersonList::exists(string first, string last){
    for (Person *cur = headWeightList; cur != nullptr; cur = cur->nextWeight){
        if (cur->first == first && cur->last == last){
            return true;
        }
    }
    return false;
}

int PersonList::getHeight(string first, string last){
    for (Person *cur = headHeightList; cur != nullptr; cur = cur->nextHeight){
        if (cur->first == first && cur->last == last){
            return cur->height;
        }
    }

    return -1;
}

int PersonList::getWeight(string first, string last){
    for (Person *cur = headWeightList; cur != nullptr; cur = cur->nextWeight){
        if (cur->first == first && cur->last == last){
            return cur->weight;
        }
    }
    return -1;
}

bool PersonList::add(string first, string last, int height, int weight){
    if (exists(first, last))
    {
        return false;
    }

    Person *p = new Person(first, last, height, weight);

    if(headHeightList == nullptr){
        headHeightList = p;
    }
    else if (p->height == headHeightList->height){
        if(p->weight < headHeightList->weight){
            p->nextHeight = headHeightList;
            headHeightList = p;
        }
        else{
            Person *temp = headHeightList->nextHeight;
            headWeightList->nextWeight = p;
            p->nextWeight = temp;
        }
    }
    else if(headHeightList->height < p->height){
        p->nextHeight = headHeightList;
        headHeightList = p;
    }
    else{
        Person *prev = headHeightList;
        Person *cur = headHeightList->nextHeight;

        while(cur != nullptr){
            if (p->height > cur->height){
                break;
            }
            if(p->height == cur->height && p->weight < cur->weight){
                break;
            }
            prev = prev->nextHeight;
            cur = cur->nextHeight;
        }
        prev->nextHeight = p;
        p->nextHeight = cur;
    }

    if(headWeightList == nullptr){
        headWeightList = p;
    }
    else if (p->weight == headWeightList->weight){
        if(p->height > headWeightList->height){
            p->nextWeight = headWeightList;
            headWeightList = p;
        }
        else{
            Person *temp = headWeightList->nextWeight;
            headWeightList->nextWeight = p;
            p->nextWeight = temp;
        }
    } 
    else if(headWeightList->weight > p->weight){
        p->nextWeight = headWeightList;
        headWeightList = p;
    }
    else{
        Person *prev = headWeightList;
        Person *cur = headWeightList->nextWeight;

        while(cur != nullptr){
            if (p->weight < cur->weight){
                break;
            }
            if (p->weight == cur->weight && p->height > cur->height){
                break;
            }
            prev = prev->nextWeight;
            cur = cur->nextWeight;
        }
        prev->nextWeight = p;
        p->nextWeight = cur;
    }
	return true;
}

bool PersonList::remove(string first, string last){
    if(!exists(first, last)){
        return false;
    }

    if(headHeightList->first == first && headHeightList->last == last && headWeightList->first == first && headWeightList->last == last){
        Person *nextH = headHeightList->nextHeight;
        Person *nextW = headWeightList->nextWeight;
        delete headHeightList;
        headHeightList = nextH;
        headWeightList = nextW;
    }

    else if (headHeightList->first == first && headHeightList->last == last){
        Person *nextH = headHeightList->nextHeight;
        headHeightList = nextH;

        Person *prevW = headWeightList;
        for (Person *cur = headWeightList; cur != nullptr; cur = cur->nextWeight){
            if (cur->first == first && cur->last == last){
                prevW->nextWeight = cur->nextWeight;
                delete cur;
            }
        }
    }

    else if (headWeightList->first == first && headWeightList->last == last){
        Person *nextW = headWeightList->nextWeight;
        headWeightList = nextW;

        Person *prevH = headHeightList;
        for (Person *cur = headHeightList; cur != nullptr; cur = cur->nextHeight){
            if (cur->first == first && cur->last == last){
                prevH->nextHeight = cur->nextHeight;
                delete cur;
            }
        }
    }

    else{
        Person *prevH = headHeightList;
        for(Person *cur = headHeightList; cur != nullptr; cur = cur->nextHeight){
            if (cur->first == first && cur->last == last){
                prevH->nextHeight = cur->nextHeight;
            }
            prevH = cur;
        }

        Person *prevW = headWeightList;
        for(Person *cur = headWeightList; cur != nullptr; cur = cur->nextWeight){
            if (cur->first == first && cur->last == last){
                prevW->nextWeight = cur->nextWeight;
                delete cur;
            }
            prevW = cur;
        }
    }
    return true;
}

bool PersonList::updateName(string first, string last, string newFirst, string newLast){
    for (Person *cur = headWeightList; cur != nullptr; cur = cur->nextWeight){
        if (cur->first == first && cur->last == last){
            cur->first = newFirst;
            cur->last = newLast;
            return true;
        }
    }
    return false;
}

bool PersonList::updateHeight(string first, string last, int height){
    for (Person *cur = headHeightList; cur != nullptr; cur = cur->nextHeight){
        if (cur->first == first && cur->last == last){
            int curWeight = cur->weight;
            remove(first, last);
            add(first, last, height, curWeight);
            return true;
        }
    }
    return false;
}

bool PersonList::updateWeight(string first, string last, int weight){
    for (Person *cur = headWeightList; cur != nullptr; cur = cur->nextWeight){
        if (cur->first == first && cur->last == last){
            int curHeight = cur->height;
            remove(first, last);
            add(first, last, curHeight, weight);
            return true;
        }
    }
    return false;
}

void PersonList::deepCopy(const PersonList &src){
    for (Person *ptr = src.headHeightList; ptr != nullptr; ptr = ptr->nextHeight){
        add(ptr->first, ptr->last, ptr->height, ptr->weight);
    }
}

PersonList::~PersonList(){
    while(headHeightList != nullptr){
       Person *next = headHeightList->nextHeight;
       delete headHeightList;
       headHeightList = next;
    }
}

PersonList::PersonList(const PersonList &src){
    headHeightList = nullptr;
    deepCopy(src);
}

const PersonList &PersonList::operator=(const PersonList &src){
    if (this != &src){
        this->~PersonList();
        deepCopy(src);
    }
    return *this;
}
