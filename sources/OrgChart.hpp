//
// Created by rivka on 18/05/2022.
//

#ifndef ORG_B_NEW_H
#define ORG_B_NEW_H
#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

typedef struct Node{
    std::string name;
    std::vector<Node*> next;
}Node;

namespace ariel {
    class OrgChart {
    private:
        Node* head;
    public:
        class my_iterator {
        private:
            Node* current;
            std::queue<Node*> listTree;
        public:
            my_iterator(){
                current= nullptr;
            }
            my_iterator(Node* ptr, int flag);
            Node* get_node();
            bool operator!=(const my_iterator& iter) const;
            bool operator==(const my_iterator& iter) const;
            std::string* operator->() const ;
            void add_preorder(Node *n);
            void add_reverse_order(Node* n);
            void add_level_order(Node *n);
            my_iterator& operator++();
            friend std::string operator*(my_iterator& iter);
        };
        OrgChart& add_root(const std::string &name);
        OrgChart& add_sub(const std::string &name1, const std::string& name2);
        OrgChart& operator=(const OrgChart& other);
        OrgChart& operator=(OrgChart&& other) noexcept;
        OrgChart::my_iterator begin_level_order() const;
        OrgChart::my_iterator end_level_order() const;
        OrgChart::my_iterator begin_reverse_order() const;
        OrgChart::my_iterator reverse_order() const;
        OrgChart::my_iterator begin_preorder()const;
        OrgChart::my_iterator end_preorder() const;
        OrgChart::my_iterator begin() const;
        OrgChart::my_iterator end() const;
        friend std::ostream &get_value(Node* n,std::ostream &os);
        friend std::ostream &operator<<(std::ostream &os, const OrgChart &o);
        ~OrgChart();
        void del(Node* ptr);
        OrgChart();
        OrgChart(OrgChart &&) = default;
        OrgChart(const OrgChart& other);
        };
}

#endif //ORG_B_NEW_H