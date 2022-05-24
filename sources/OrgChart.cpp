//
// Created by rivka on 18/05/2022.
//

#include "OrgChart.hpp"

namespace ariel {
    OrgChart::OrgChart() {
        this->head = nullptr;
    }

//Adding a root if the root exists replaces the value
    OrgChart &OrgChart::add_root(const std::string &name) {
        if ((name.empty())||(name == " ")||((name == "\n"))){
            throw std::out_of_range{"Invalid value"};
        }
        if (this->head == nullptr) {
            this->head = new Node{name};
        } else {
            this->head->name = name;
        }
        return *this;
    }
    /*
     * Adding a value to a tree looks for a name1 if it does not exist throws an error.
       Passes in level order on the tree
     */
    OrgChart &OrgChart::add_sub(const std::string &name1, const std::string &name2) {
        if ((name1.empty())||(name1 == " ")||((name1 == "\n"))){
            throw std::out_of_range{"Invalid value"};
        }
        if ((name2.empty())||(name2 == " ")||((name2 == "\n"))){
            throw std::out_of_range{"Invalid value"};
        }
        if (this->head == nullptr) {
            throw std::out_of_range{"There is no root"};
        }
        for (my_iterator it = this->begin_level_order(); it != this->end_level_order(); ++it) {
            if (name1 == (*it)) {
                Node *temp = it.get_node();
                temp->next.push_back(new Node{name2});
                return *this;
            }
            if (name2 == (*it)) {
                throw std::out_of_range{"Existing value"};
            }
        }
        throw std::out_of_range{"not found"};
    }

//operator=
    OrgChart &OrgChart::operator=(const OrgChart &other) {
        OrgChart o = OrgChart(other);
        return *this;
    }

    // move assignment
    OrgChart &OrgChart::operator=(OrgChart &&other)

    noexcept {
    OrgChart &o = other;
    return *this;
}

//copy constructor
OrgChart::OrgChart(const OrgChart &other) {
    this->head = other.head;
}

//Auxiliary function for adding members to a queue in preorder
void OrgChart::my_iterator::add_preorder(Node *n) {
        for (unsigned long i = 0; i < n->next.size(); ++i) {
            this->listTree.push(n->next.at(i));
            add_preorder(n->next.at(i));
        }
}
//Auxiliary function for adding members to a queue in level order

void OrgChart::my_iterator::add_level_order(Node *n) {
    std::queue <Node*> queue;
    queue.push(n);
    while (!queue.empty()) {
        this->current = queue.front();
        queue.pop();
        this->listTree.push(this->current);
        if (this->current->next.empty()) {
            continue;
        }
        for (unsigned long i = 0; i <  this->current->next.size(); i++) {
            queue.push(this->current->next.at(i));
        }
    }
}
//Auxiliary function for adding members to a queue in reverse order
void OrgChart::my_iterator::add_reverse_order(Node *n) {
    std::queue < Node * > queue;
    std::stack < Node * > stack;
    queue.push(n);
    while (!queue.empty()) {
        this->current = queue.front();
        queue.pop();
        stack.push(this->current);
        if (this->current->next.empty()) {
            continue;
        }
        int size = this->current->next.size();
        for (int i = size - 1; i >= 0; i--) {
            queue.push(this->current->next.at((unsigned) i));

        }
    }
//    while (stack.size() > 1) {
    while (!stack.empty()){
        this->current = stack.top();
        stack.pop();
        this->listTree.push(this->current);
    }
}
/*
 * constructor
 * 0 - level order
 * 1 - reverse order
 * 2 - preorder
 */
OrgChart::my_iterator::my_iterator(Node *ptr, int flag) {
    if (flag == 0 ) {
        add_level_order(ptr);
    }
    if (flag == 1) {
        add_reverse_order(ptr);
//        this->listTree.push(ptr);
    }
    if (flag == 2) {
        this->listTree.push(ptr);
        add_preorder(ptr);
    }

    this->current = this->listTree.front();
}

/*
 * operator !=
 * If both are empty they are equal
 *If one is empty and the other is not then they are different
 * If both are not empty we will check the value
*/
bool OrgChart::my_iterator::operator!=(const my_iterator &iter) const {
    if ((!this->listTree.empty()) && (!iter.listTree.empty())) {
        return this->current != iter.current;
    }
    return !(this->listTree.empty() && iter.listTree.empty());
}

//operator ==
bool OrgChart::my_iterator::operator==(const my_iterator &iter) const {
    return !(*this != iter);

}

//operator *
std::string operator*(OrgChart::my_iterator &iter) {
    return iter.current->name;
}

//operator ->
std::string *OrgChart::my_iterator::operator->() const {
    return &this->current->name;
}

// operator ++
OrgChart::my_iterator &OrgChart::my_iterator::operator++() {
    this->listTree.pop();
    this->current = this->listTree.front();
    return *this;

}

//return the current value
Node *OrgChart::my_iterator::get_node() {
    return this->current;
}

//Returns an iterator to pass the tree in level order
OrgChart::my_iterator OrgChart::begin_level_order() const {
    if (this->head == nullptr) {
        throw std::out_of_range{"empty tree"};
    }
    my_iterator it{this->head, 0};
    return it;
}

//Returns an iterator to pass the tree in level order
OrgChart::my_iterator OrgChart::end_level_order() const {
    if (this->head == nullptr) {
        throw std::out_of_range{"empty tree"};
    }
    my_iterator it;
    return it;
}

//Returns an iterator to pass the tree in reverse order
OrgChart::my_iterator OrgChart::begin_reverse_order() const {
    if (this->head == nullptr) {
        throw std::out_of_range{"empty tree"};
    }
    my_iterator it{this->head, 1};
    return it;
}

//Returns an iterator to pass the tree in reverse order
OrgChart::my_iterator OrgChart::reverse_order() const {
    if (this->head == nullptr) {
        throw std::out_of_range{"empty tree"};
    }
    my_iterator it;
    return it;
}
//Returns an iterator to pass the tree in preorder

OrgChart::my_iterator OrgChart::begin_preorder() const {
    if (this->head == nullptr) {
        throw std::out_of_range{"empty tree"};
    }
    my_iterator it{this->head, 2};
    return it;
}

//Returns an iterator to pass the tree in preorder
OrgChart::my_iterator OrgChart::end_preorder() const {
    if (this->head == nullptr) {
        throw std::out_of_range{"empty tree"};
    }
    my_iterator it;
    return it;
}

//Returns an iterator to pass the tree in level order for the for each
OrgChart::my_iterator OrgChart::begin() const {
    if (this->head == nullptr) {
        throw std::out_of_range{"empty tree"};
    }
    return this->begin_level_order();
}

//Returns an iterator to pass the tree in level order for the for each
OrgChart::my_iterator OrgChart::end() const {
    if (this->head == nullptr) {
        throw std::out_of_range{"empty tree"};
    }
    return this->end_level_order();

}

//detractor
OrgChart::~OrgChart() {
    del(this->head);
}

//detractor the nodes from end to beginning in recursion
void OrgChart::del(Node *ptr) {
    if (ptr == nullptr) {
        return;
    }
    for (unsigned long i = 0; i < (ptr)->next.size(); ++i) {
        del(((ptr)->next.at(i)));
    }
    delete ptr;
}

//Auxiliary function for adding a tree trajectory
std::ostream &get_value(Node *n, std::ostream &os) {
    os << "->" << n->name;
    for (unsigned long i = 0; i < n->next.size(); ++i) {
        return get_value(n->next.at(i), os);
    }
    return os;
}

//operator <<
std::ostream &operator<<(std::ostream &os, const OrgChart &o) {
    for (unsigned long i = 0; i < o.head->next.size(); ++i) {
        os << o.head->name;
        get_value(o.head->next.at(i), os);
        os << std::endl;
    }
    return os;
}

}