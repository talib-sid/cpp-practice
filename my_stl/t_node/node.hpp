#include <memory>
#pragma once

//
// Binary Node in C++20
// Features: 1. Constructors and Desc. 5. Member Functions
// Pending: 1. Exception Handling 2. Operator Overloading 3. Template Specialization
 

template <typename T>
class Node {
    public:
        T data;
        std::shared_ptr<Node<T>> left;    
        std::shared_ptr<Node<T>> right;

        // Default constructors
        Node(T data): data(data), left(nullptr), right(nullptr) {};
        Node(T data, std::shared_ptr<Node<T>> left): data(data), left(left), right(nullptr) {};
        // Node(T data, Node<T>* right): data(data), left(nullptr), right(right) {};
        Node(T data, std::shared_ptr<Node<T>> left, std::shared_ptr<Node<T>> right): data(data), left(left), right(right) {};

        // Copy constructor
        Node(const Node<T>& node): data(node.data), left(node.left), right(node.right) {};

        // Move constructor
        Node(Node<T>&& node): data(std::move(node.data)), left(std::move(node.left)), right(std::move(node.right)){
            // std::cout << "Move constructor called" << std::endl
            // node.left = nullptr;  // Optional
            // node.right = nullptr; // Optional
        }


        // Destructor
        ~Node(){}
        constexpr void print_data() const noexcept{
            std::cout << data << std::endl;
        }
        std::shared_ptr<Node<T>> get_left() const noexcept{
            return left;
        }

        std::shared_ptr<Node<T>> get_right() const noexcept{
            return right;
        }
        // for the specific node 
        constexpr T get_data() const noexcept{
            // Pending: Exception Handling to be done
            if(this == nullptr) return " ";
            else return data;
            // return nullptr;
        }
        constexpr bool operator=(const Node<T>& node) const noexcept{
            // assignment
            if(&this == node) return *this;
            return data=node.data;
            
        }
        constexpr bool operator==(const Node<T>& node) const noexcept{
            return data == node.data;
        }
        
};


