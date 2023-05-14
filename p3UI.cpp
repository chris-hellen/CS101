#include <iostream>
#include <string>

#include "p3.h"

using namespace std;

int main(int argc, char *argv[]) {
    bool printPrompts = true;
    if (argc == 2 && string(argv[1]) == "no") {
        printPrompts = false;
    }

    PersonList *list = new PersonList();

    string cmd, first, last, newFirst, newLast;
    int h, w;
    while (1) {
        if (printPrompts) cout << "Enter a command or \"help\" to get a command list: ";
        cin >> cmd;
        if (cmd == "quit") {
            break;
        }
        else if (cmd == "add") {
            if (printPrompts) cout << "\tEnter first name: ";
            cin >> first;
            if (printPrompts) cout << "\tEnter last name: ";
            cin >> last;
            if (printPrompts) cout << "\tEnter height: ";
            cin >> h;
            if (printPrompts) cout << "\tEnter weight: ";
            cin >> w;
            if (!list->add(first, last, h, w))
            {
                cout << "Error: " << first << " " << last << " already exists in the list" << endl;
            }
        }
        else if (cmd == "size") {
            cout << "\nThere are " << list->getSize() << " persons in the list" << endl;
        }
        else if (cmd == "printByHeight") {
            list->printByHeight(cout);
            cout << endl;
        }
        else if (cmd == "printByWeight") {
            list->printByWeight(cout);
            cout << endl;
        }
        else if (cmd == "search") {
            if (printPrompts) cout << "\tEnter first name: ";
            cin >> first;
            if (printPrompts) cout << "\tEnter last name: ";
            cin >> last;
            if (!list->exists(first, last)) {
                cout << first << " " << last << " does not exist in the list" << endl;
            }
            else {
                cout << first << " " << last << ": height=" << list->getHeight(first, last);
                cout << ", weight=" << list->getWeight(first, last) << endl;
            }
        }
        else if (cmd == "updateName") {
            if (printPrompts) cout << "\tEnter first name: ";
            cin >> first;
            if (printPrompts) cout << "\tEnter last name: ";
            cin >> last;
            if (printPrompts) cout << "\tEnter new first name: ";
            cin >> newFirst;
            if (printPrompts) cout << "\tEnter new last name: ";
            cin >> newLast;
            if (!list->updateName(first, last, newFirst, newLast))
            {
                cout << "Error: " << first << " " << last << " does not exist in the list" << endl;
            }
        }
        else if (cmd == "remove") {
            if (printPrompts) cout << "\tEnter first name: ";
            cin >> first;
            if (printPrompts) cout << "\tEnter last name: ";
            cin >> last;
            if (!list->remove(first, last))
            {
                cout << "Error: " << first << " " << last << " does not exist in the list" << endl;
            }
        }
        else if (cmd == "updateHeight") {
            if (printPrompts) cout << "\tEnter first name: ";
            cin >> first;
            if (printPrompts) cout << "\tEnter last name: ";
            cin >> last;
            if (printPrompts) cout << "\tEnter new height: ";
            cin >> h;
            if (!list->updateHeight(first, last, h))
            {
                cout << "Error: " << first << " " << last << " does not exist in the list" << endl;
            }
        }
        else if (cmd == "updateWeight") {
            if (printPrompts) cout << "\tEnter first name: ";
            cin >> first;
            if (printPrompts) cout << "\tEnter last name: ";
            cin >> last;
            if (printPrompts) cout << "\tEnter new weight: ";
            cin >> w;
            if (!list->updateWeight(first, last, w))
            {
                cout << "Error: " << first << " " << last << " does not exist in the list" << endl;
            }
        }
        else if (cmd == "destroy") {
            delete list;
            list = new PersonList();
        }
        else if (cmd == "copycon" || cmd == "copy=") {
            PersonList *list2;
            if (cmd == "copycon")
            {
                list2 = new PersonList(*list);
            }
            else
            {
                list2 = new PersonList();
                *list2 = *list;
            }

            cout << "Original list by height:" << endl;
            list->printByHeight(cout);
            cout << endl << "Original list by weight:" << endl;
            list->printByWeight(cout);
            cout << endl;

            cout << "Copied list by height:" << endl;
            list2->printByHeight(cout);
            cout << endl << "Copied list by weight:" << endl;
            list2->printByWeight(cout);
            cout << endl;

            if (printPrompts) cout << "\tAdd person to copied list:" << endl;
            if (printPrompts) cout << "\tEnter first name: ";
            cin >> first;
            if (printPrompts) cout << "\tEnter last name: ";
            cin >> last;
            if (printPrompts) cout << "\tEnter height: ";
            cin >> h;
            if (printPrompts) cout << "\tEnter weight: ";
            cin >> w;
            if (!list2->add(first, last, h, w))
            {
                cout << "Error: " << first << " " << last << " already exists in the list" << endl;
            }

            cout << endl << "Original list by height:" << endl;
            list->printByHeight(cout);
            cout << endl << "Original list by weight:" << endl;
            list->printByWeight(cout);
            cout << endl;

            cout << "Copied list by height:" << endl;
            list2->printByHeight(cout);
            cout << endl << "Copied list by weight:" << endl;
            list2->printByWeight(cout);
            cout << endl;

            delete list2;
        }
        else if (cmd == "help") {
            cout << "Valid commands:" << endl;
            cout << "***** add" << endl;
            cout << "***** size" << endl;
            cout << "***** printByHeight" << endl;
            cout << "***** printByWeight" << endl;
            cout << "***** search" << endl;
            cout << "***** remove" << endl;
            cout << "***** updateName" << endl;
            cout << "***** updateHeight" << endl;
            cout << "***** updateWeight" << endl;
            cout << "***** destroy" << endl;
            cout << "***** copycon" << endl;
            cout << "***** copy=" << endl;
            cout << "***** help" << endl;
            cout << "***** quit" << endl;
        }
        else {
            if (printPrompts) cout << "Invalid command specified - " << cmd << endl;
        }
        if (printPrompts) cout << endl;
    }
    return 0;
}
