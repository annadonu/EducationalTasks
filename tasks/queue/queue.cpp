#include "queue.h"
#include <stdexcept>

Node::Node(int32_t value, Node* next): value(value), next(next) {}

Queue::Queue(): front_(nullptr), tail_(nullptr), size_(0) {}

Queue::~Queue() { clear(); }

void Queue::push(int32_t value)
{
    Node* newNode = new Node(value, nullptr);
    if(empty())
    {
        tail_ = newNode;
        front_ = tail_;
    }
    else
    {
        tail_->next = newNode;
        tail_ = tail_->next;
    }
    size_++;
}

void Queue::pop()
{
    if(empty())
    {
        throw std::out_of_range("queue is empty");
    }
    else
    {
        Node* current = front_;
        front_ = front_->next;
        delete current;
    }
    size_--;
    if(size_ == 0)
        tail_ = nullptr;
}

int32_t Queue::front() const
{
    if(empty())
        throw std::out_of_range("queue is empty");
    return front_->value;
}

int32_t Queue::size() const { return size_; }

void Queue::clear()
{
    while(front_ != nullptr)
    {
        Node* current = front_;
        front_ = front_->next;
        delete current;
    }
    tail_ = nullptr;
    size_ = 0;
}

bool Queue::empty() const
{
    if(size_ == 0)
        return true;
    return false;
}
