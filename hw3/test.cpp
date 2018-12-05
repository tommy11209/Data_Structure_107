#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

std::vector<std::string> parse(std::ifstream &input)
{
    std::vector<std::string> tokens;
    std::string line;
    // expected atleast one line
    while (std::getline(input, line))
    {
        int round = std::stoi(line);
        std::string buf = line + " ";
        for (int i = 0; i <= round; i++)
            if (std::getline(input, line))
                buf += line + " ";
        tokens.push_back(buf);
    }
    return tokens;
}

struct node{};
node * insert(node *n, int, float) { return n; }

node * create(std::string fin_string)
{
    std::stringstream fin{fin_string};
    int n , i, power1;
    float coeff1;
    node * head = nullptr;
    fin >> n;
    for (i = 1 ; i <= n ; i++)
    {
        fin >> coeff1 >> power1;
        head = insert(head, power1, coeff1);
    }
    return (head);
}

int main()
{
    std::ifstream input{"./input.txt"};
    std::vector<std::string> && c = parse(input);
    for (std::string & x : c)
    {
        std::cout << "'" << x << "'\n";
        create(x);
    }
}
