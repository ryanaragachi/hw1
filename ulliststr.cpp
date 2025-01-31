#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE

void ULListStr::push_back(const std::string&val) {
  if (!tail_ || tail_->last == ARRSIZE) 
  {
    Item* new_item = new Item();
    if (tail_) {
      tail_->next = new_item;
      new_item->prev = tail_;
    }

    else
    { 
      head_ = new_item;
    }

    tail_ = new_item;
  }

  tail_->val[tail_->last++] = val;
  size_++;
}

void ULListStr::pop_back()
{
  if (empty()) return;

  tail_->last--;
  size_--;

  if (tail_->first == tail_->last)
  {
    Item* temporary = tail_;
    tail_ = tail_->prev;

    if (tail_) tail_->next = nullptr;
    else head_ = nullptr;

    delete temporary;
  }
}

void ULListStr::push_front(const std:: string&val) 
{
  if (!head_ || head_->first == 0)
  {
    Item* new_item = new Item();
    new_item->first = new_item->last = ARRSIZE;

    if (head_) 
    {
      head_->prev = new_item;
      new_item->next = head_;
    }

    else 
    {
      tail_ = new_item;
    }

    head_ = new_item;
  }

  head_->val[--head_->first] = val;
  size_++;
}

void ULListStr::pop_front()
{
  if (empty()) return;

  head_->first++;
  size_--;

  if (head_->first == head_->last) 
  {
    Item* temporary = head_;
    head_ = head_->next;

    if (head_) head_->prev = nullptr;
    else tail_ = nullptr;

    delete temporary;
  }
}

std::string const& ULListStr::back() const 
{
  if (empty())
  {
    throw std::underflow_error("NOTHING IN LIST");
  }

  return tail_->val[tail_->last - 1]; 
}

std::string const& ULListStr::front() const
{
  if (empty())
  {
    throw std::underflow_error("NOTHING IN LIST");
  }

  return head_->val[head_->first];
}


void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}

std::string* ULListStr::getValAtLoc(size_t loc) const
{
  if (loc>= size_) return nullptr;

  Item* current = head_;

  while (current)
  {
    size_t numElements = current->last - current->first;
    if (loc < numElements)
    {
      return &current->val[current->first + loc];
    }

    loc = loc - numElements;
    current = current->next;
  }

  return nullptr;
}