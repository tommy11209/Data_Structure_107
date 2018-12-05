#include <iomanip>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <fstream>
#include <chrono>


using namespace std;

struct treeNode
{
    int data;
    treeNode *left;
    treeNode *right;
};

treeNode* FindMax(treeNode *node)
{
    if(node==NULL)
    {

        return NULL;
    }
    if(node->right)
        return(FindMax(node->right));
    else
        return node;
}

treeNode *Insert(treeNode *node,int data)
{
    int a,b;
    if(node==NULL)
    {
        treeNode *temp;
        temp=new treeNode;

        temp -> data = data;
        temp -> left = temp -> right = NULL;
        return temp;
    }
    if(data >(node->data))
    {
        node->right = Insert(node->right,data);
    }
    else if(data < (node->data))
    {
        node->left = Insert(node->left,data);
    }
    else if (data == (node->data))
    {
        a=b;
    }

    return node;
}

treeNode * Delet(treeNode *node, int data)
{
    treeNode *temp;
    if(node==NULL)
    {

    }
    else if(data < node->data)
    {
        node->left = Delet(node->left, data);
    }
    else if(data > node->data)
    {
        node->right = Delet(node->right, data);
    }
    else
    {

        if(node->right && node->left)
        {
            temp = FindMax(node->left);
            node -> data = temp->data;

            node -> left = Delet(node->left,temp->data);
        }
        else
        {
            temp = node;
            if(node->left == NULL)
                node = node->right;
            else if(node->right == NULL)
                node = node->left;
            free(temp);
        }
    }
    return node;
}

treeNode * Find(treeNode *node, int data)
{
    if(node==NULL)
    {

        return NULL;
    }
    if(data > node->data)
    {

        return Find(node->right,data);
    }
    else if(data < node->data)
    {

        return Find(node->left,data);
    }
    else
    {

        return node;
    }
}

int getLevelUtil(treeNode *node, int data, int level)
{
    if (node == NULL)
        return 0;

    if (node->data == data)
        return level;

    int downlevel = getLevelUtil(node->left, data, level+1);
    if (downlevel != 0)
        return downlevel;

    downlevel = getLevelUtil(node->right, data, level+1);
    return downlevel;
}

/* Returns level of given data value */
int getLevel(treeNode *node, int data)
{
    return getLevelUtil(node,data,1);
}


int main(int argc, char** argv)
{
    treeNode *root = NULL,*temp;
    int value;
    int level;


    char* input, *output;
    input = argv[1];
    output = argv[2];
    std::fstream f(input , std::ios::in);
    std::fstream  out(output , std::ios::out);
    int choice;

    while(f >> choice)
    {

        f >> value;
        if(choice == 1)
        {
            root = Insert(root, value);
        }

        else if(choice == 2)
        {
            root = Delet(root,value);
        }

        else if(choice == 3)
        {
            temp = Find(root,value);

            if(temp==NULL)
            {
                out << "-1" << endl;
            }
            else
            {
                out<< getLevel(root,temp->data) - 1 << endl;
            }
        }

    }
    return 0;
}
