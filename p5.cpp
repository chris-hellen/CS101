#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <cctype>
using namespace std;

class Node{
    public:
    int data;
    Node *leftChild, *rightChild;
};

class HuffmanTree{
    public:
    Node root;
    vector <char> message;
    vector <int> inOrder;
    vector <int> levelOrder;
    HuffmanTree();
    void setRoot();
    void buildTree(Node &root, vector <int> inOrder, vector <int> levelOrder);
    void decode();
};

HuffmanTree::HuffmanTree(){
}

void HuffmanTree::buildTree(Node &root, vector <int> inOrder, vector <int> levelOrder){
    int inLen = inOrder.size(), levLen = levelOrder.size();
    HuffmanTree *rightSub = new HuffmanTree;
    HuffmanTree *leftSub = new HuffmanTree;
    Node *rightRoot = new Node;
    Node *leftRoot = new Node;

    int rootIdx;
    for (int i = 0; i < inLen; i++){
        if (inOrder[i] == root.data){
            rootIdx = i;
        }
    }
    for(int i = 0; i < rootIdx; i++){
        leftSub->inOrder.push_back(inOrder[i]);
    }
    for(int i = rootIdx + 1; i < inLen; i++){
        rightSub->inOrder.push_back(inOrder[i]);
    }
    for(int i = 0; i < levLen; i++){
        for(int j = 0; j < leftSub->inOrder.size(); j++){
            if (leftSub->inOrder[j] == levelOrder[i]){
                leftSub->levelOrder.push_back(levelOrder[i]);
            }
        }
    }
    for(int i = 0; i < levLen; i++){
        for(int j = 0; j < rightSub->inOrder.size(); j++){
            if (rightSub->inOrder[j] == levelOrder[i]){
                rightSub->levelOrder.push_back(levelOrder[i]);
            }
        }
    }
    rightRoot->data = rightSub->levelOrder[0];
    leftRoot->data = leftSub->levelOrder[0];

    root.rightChild = rightRoot;
    root.leftChild = leftRoot;

    if (leftSub->inOrder.size() > 1 && rightSub->inOrder.size() > 1){
        buildTree(*leftRoot, leftSub->inOrder, leftSub->levelOrder);
        buildTree(*rightRoot, rightSub->inOrder, rightSub->levelOrder);
    }
    else if (leftSub->inOrder.size() > 1){
        buildTree(*leftRoot, leftSub->inOrder, leftSub->levelOrder);
    }
    else if (rightSub->inOrder.size() > 1){
        buildTree(*rightRoot, rightSub->inOrder, rightSub->levelOrder);
    }
    else{
        return;
    }
}

void HuffmanTree::decode(){
    Node curNode = root;
    int digCount = 0;

    while(digCount < message.size()){
        if (message[digCount] == '0'){
        curNode = *curNode.leftChild;
        }
        else if (message[digCount] == '1'){
        curNode = *curNode.rightChild;
        }

        if (curNode.data < 128){
            cout << char(curNode.data);
            curNode = root;
        }
        digCount++;
    }
}

//Start of Main


int main(int argc, char **argv){
    ifstream inFile(argv[1]);
    ifstream levFile(argv[2]);
    ifstream msgFile(argv[3]);

    HuffmanTree tree;
    int curNum;
    char curDig;

    while(inFile >> curNum){
        tree.inOrder.push_back(curNum);
    }
    while(levFile >> curNum){
        tree.levelOrder.push_back(curNum);
    }
    while(msgFile.get(curDig)){
        tree.message.push_back(curDig);
    }
    tree.root.data = tree.levelOrder[0];

    tree.buildTree(tree.root, tree.inOrder, tree.levelOrder);
    tree.decode();

    return 0;
}