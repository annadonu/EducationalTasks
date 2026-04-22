#include "stack.h"
#include <stdexcept>

Node::Node(int32_t value, Node* previous): value(value), previous(previous) {}

Stack::Stack(): head_(nullptr), size_(0) {}

Stack::~Stack() { clear(); }

void Stack::push(int32_t value)
{
    if(empty())
    {
        head_ = new Node(value, nullptr);
    }
    else
    {
        Node* current = new Node(value, head_);
        head_ = current;
    }
    ++size_;
}

void Stack::pop()
{
    if(empty())
        throw std::out_of_range("stack is empty");
    Node* current = head_;
    head_ = head_->previous;
    delete current;
    --size_;
}

int32_t Stack::top() const
{
    if(empty())
        throw std::out_of_range("stack is empty");
    return head_->value;
}

int32_t Stack::size() const { return size_; }

bool Stack::empty() const
{
    if(size_ == 0)
        return true;
    else
        return false;
}

void Stack::clear()
{
    while(head_ != nullptr)
    {
        Node* current = head_;
        head_ = head_->previous;
        delete current;
    }
    size_ = 0;
}
