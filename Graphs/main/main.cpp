#include <iostream>
#include <string>
#include "graph.h"

struct Person
{
private:
    std::string names[SIZE];
    int number = 0;
public:
    std::string addPerson(std::string name);
};

std::string Person:: addPerson(std::string name)
{
    return name;
}
int main()
{
    system("chcp 1251");
    Person person;

    std::string user_1=  person.addPerson("Настя");
    std::string user_2 = person.addPerson("Никита");
    std::string user_3 = person.addPerson("Ваня");
    std::string user_4 = person.addPerson("Женя");
    std::string user_5 = person.addPerson("Олег");


    Graph graph;
    graph.addVertex(user_1);
    graph.addVertex(user_2);
    graph.addVertex(user_3);
    graph.addVertex(user_4);
    graph.addVertex(user_5);

    graph.addEdge(user_1, user_2);
    graph.addEdge(user_1, user_3);
    graph.addEdge(user_2, user_5);
    graph.addEdge(user_3, user_4);


    graph.findFriends(user_3);

}

