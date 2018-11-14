#ifndef NODE_H
#define NODE_H

using namespace std;

template <class T>
class Node {
public:
    int x, y;
    T data;
    Node* next;
    Node* down;

    Node(int x, int y, T data ,Node* next = NULL, Node* down =  NULL)
    {
    	this->x = x;
    	this->y = y;
    	this->data = data;
    	this->next = next;
    	this->down = down;
    }
};

#endif