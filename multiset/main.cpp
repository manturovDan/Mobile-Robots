#include <iostream>

//#include "multiset.h"
#include <set>

int main() {
    std::set<int> m_set;
    std::set<int>::iterator fw_iterr;

    m_set.insert(1);
    m_set.insert(2);
    m_set.insert(-50);


    std::cout << *(++m_set.end()) << std::endl;


    return 0;
}