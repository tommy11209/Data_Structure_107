#include <cstdio>
#include <cmath>
#include <fstream>
#include <iostream>

#include <sstream>
#include <vector>

using namespace std;

typedef struct  node
{
    int power;
    int coeff;
    struct node *next;
}node;

node *  insert(node *head,int power1,int coeff1);
node *  insert_sub(node *head,int power1,int coeff1);
node *  create();
node *  addition(node *p1,node *p2);
node *  sub(node *p1,node *p2);
node *  multiply(node *p1,node *p2);
void print(node *head);

std::vector<std::string> parse(std::ifstream &input)
{
    std::vector<std::string> tokens;
    std::string line, buf = "+ ";
    // expected atleast one line
    while (std::getline(input, line))
    {
        int round = std::stoi(line);
        buf += line + " ";
        for (int i = 0; i < round; i++)
            if (std::getline(input, line))
                buf += line + " ";
        tokens.push_back(buf);
        if (std::getline(input, line))
            buf = line + " ";
    }
    return tokens;
}


node *insert(node *head, int power1, int coeff1)
{
    node *p,*q;

    p=(node*) malloc(sizeof(node));
    p->power = power1;
    p->coeff = coeff1;
    p->next = NULL;
    if(head == NULL)
    {
        head = p;
        head->next = head;
        return(head);
    }
    if(power1 > head->power)
    {
        p->next = head->next;
        head->next = p;
        head = p;
        return(head);
    }
    if(power1 == head->power)
    {
        head->coeff = head->coeff + coeff1;
        return(head);
    }

    q = head;
    while(q->next != head && power1 >= q->next->power)
        q = q->next;
    if(p->power == q->power)
        q->coeff = q->coeff + coeff1;
    else
    {
        p->next = q->next;
        q->next = p;
    }
    return(head);
}

node *insert_sub(node *head, int power1, int coeff1)
{
    node *p,*q;

    p = (node*) malloc(sizeof(node));
    p->power = power1;
    p->coeff = (-coeff1);
    p->next = NULL;
    if(head == NULL)
    {
        head = p;
        head->next = head;
        return(head);
    }
    if(power1 > head->power)
    {
        p->next = head->next;
        head->next = p;
        head=p;
        return(head);
    }
    if(power1 == head->power)
    {
        head->coeff = head->coeff-coeff1;
        return(head);
    }

    q = head;
    while(q->next != head && power1 >= q->next->power)
        q = q->next;
    if(p->power == q->power)
        q->coeff = q->coeff-coeff1;
    else
    {
        p->next = q->next;
        q->next = p;
    }
    return(head);
}


node * addition(node *p1, node *p2)
{
    node *p;
    node *head = NULL;
    int power;
    int coeff;
    p = p1->next;
    do
    {
        head = insert(head, p->power, p->coeff);
        p = p->next;
    }while(p != p1->next);

    p = p2->next;
    do
    {
        head = insert(head, p->power, p->coeff);
        p = p->next;
    }while(p != p2->next);

    return(head);
}

node * sub(node *p1, node *p2)
{
    node *p;
    node *head = NULL;
    int power;
    int coeff;
    p = p1->next;
    do
    {
        head = insert(head, p->power, p->coeff);
        p = p->next;
    }while(p != p1->next);

    p = p2->next;

    do
    {
        head = insert_sub(head, p->power, p->coeff);
        p = p->next;
    }while(p != p2->next);

    return(head);
}

node *multiply(node *p1,node *p2)
{
    node *head1, *head2;
    node *head = NULL;
    head2 = p2->next;
    do
    {
        head1 = p1->next;
        do
        {
            head = insert(head, head1->power + head2->power, head1->coeff * head2->coeff);
            head1 = head1->next;
        }while(head1 != p1->next);
    head2 = head2->next;
    }while(head2 != p2->next);

    return(head);
}


node * create(std::string fin_string)
{
    std::stringstream fin{fin_string};
    int n , i, power1;
    int coeff1;
    node * head = nullptr;
    fin >> n;
    for (i = 1 ; i <= n ; i++)
    {
        fin >> coeff1 >> power1;
        head = insert(head, power1, coeff1);
    }
    return (head);
}

/*void print(node *head)
{
    node *p;
    node *temp;
    int *ouptut_arr1, *ouptut_arr2;

    int count = 0;
    int i = 0;
    int j = 0;
    p = head->next;
    temp = head->next;
    do
    {
        temp = temp->next;
        if(temp->coeff != 0)
            count ++;
    }while(temp != head->next);
    out << count << endl;

    ouptut_arr1 = new int[count+1000];

    ouptut_arr2 = new int[count+1000];

    do
    {
        //if(p->coeff != 0)
        //{

        ouptut_arr1[i] = p->coeff;

        ouptut_arr2[i] = p->power;
        //}
            //cout << p->coeff << " " << p->power << endl;
        p = p->next;
        i++;
    }while(p != head->next);
    for(int i = count; i >= 0; i--)
    {
        if(ouptut_arr1[i] != 0)
            out << ouptut_arr1[i] << " " << ouptut_arr2[i] << endl;
    }
}*/


int main(int argc, char** argv)
{
    char* read_file, *output;
    read_file = argv[1];
    output = argv[2];
    //std::fstream f(input , std::ios::in);
    std::fstream  out(output , std::ios::out);

    //////////////////////////////
    node *p;
    node *temp;
    int *ouptut_arr1, *ouptut_arr2;

    int count = 0;
    int i = 0;
    int j = 0;
    //////////////////////////////
    node *head;
    head = NULL;
    std::ifstream input{read_file};
    head = create("1 0 0");
    std::vector<std::string> && c = parse(input);
    for (std::string & x : c)
    {
        if(x[0] == '+')
        {
            head = addition(head, create(x.substr(2)));
        }
        if(x[0] == '*')
        {
            head = multiply(head, create(x.substr(2)));
        }
        if(x[0] == '-')
        {
            head = sub(head, create(x.substr(2)));
        }
    }
    //print(p);
    p = head->next;
    temp = head->next;
    do
    {
        temp = temp->next;
        if(temp->coeff != 0)
            count ++;
    }while(temp != head->next);
    if(count == 0)
    {
        //out << "1" << endl;
        out << "zero polynomial" << endl;
    }
    else
        out << count << endl;

    ouptut_arr1 = new int[count+9999];

    ouptut_arr2 = new int[count+9999];

    do
    {
        //if(p->coeff != 0)
        //{

        ouptut_arr1[i] = p->coeff;

        ouptut_arr2[i] = p->power;
        //}
            //cout << p->coeff << " " << p->power << endl;
        p = p->next;
        i++;
    }while(p != head->next);
    for(int i = count; i >= 0; i--)
    {
        if(ouptut_arr1[i] != 0)
            out << ouptut_arr1[i] << " " << ouptut_arr2[i] << endl;
    }
}
