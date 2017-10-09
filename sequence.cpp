// Provided by:   ____________Carter Beebe__________
// Lab:           ____________Ott 182________
// Course number: ____________CIS-221________
// All of the code has been typed by myself and none was copied.
// FILE: sequence.h
// CLASS PROVIDED: sequence (part of the namespace main_savitch_4)
//
// VALUE SEMANTICS for the sequence class:
//    Assignments and the copy constructor may be used with sequence objects.
//
// DYNAMIC MEMORY USAGE by the List
//   If there is insufficient dynamic memory, then the following functions
//   throw a BAD_ALLOC exception: The constructors, insert, attach. 

#include "sequence.h"
namespace main_savitch_4
{
    // CONSTRUCTOR
    // Postcondition: The sequence has been initialized as an empty sequence.
    // The insert/attach functions will work efficiently (without allocating
    // new memory) until this capacity is reached.
    sequence::sequence (size_type initial_capacity)
    {
      data_ = new value_type [DEFAULT_CAPACITY];
      used_ = 0;
      current_index_ = 0;
      capacity_ = DEFAULT_CAPACITY;
    }

    // COPY CONSTRUCTOR
    // Postcondition: The sequence has been initialized to the sequence
    //   passed in.
    // The insert/attach functions will work efficiently (without allocating
    // new memory) until the source's capacity is reached.
   sequence::sequence(const sequence& source)
    {
     if (this == &source)
       return;
     data_ = new value_type[DEFAULT_CAPACITY];
     capacity_ = source.capacity_;
     used_ = source.used_;
     copy(source.data_, source.data_ + used_, data_);
    }

    // DESTRUCTOR
    // Postcondition: The memory allocated for the object has been released.
    sequence::~sequence()
    {
      if (data_) {
        delete [] data_;
        data_ = NULL;
      }
    }

    // MODIFICATION MEMBER FUNCTIONS

    // Postcondition: The sequence's current capacity is changed to the 
    //   new_capacity (but not less that the number of items already on the
    //   list). The insert/attach functions will work efficiently (without
    //   allocating new memory) until this new capacity is reached.
    void sequence::resize(size_type new_capacity)
    {
      value_type *larger_data_;
      if (new_capacity == capacity_) {
       return;
      }
      if (new_capacity < used_) {
        new_capacity = used_;
      }
      larger_data_ = new value_type[new_capacity];
      copy(data_, data_ + used_, larger_data_);
      delete[] data_;
      data_ = larger_data_;
      capacity_ = new_capacity;
    }

    // Postcondition: The first item on the sequence becomes the current item
    //   (but if the sequence is empty, then there is no current item).
    void sequence::start( )
    {
      if (used_ < 1)
      return;
      current_index_ = 0;
    }

    // Precondition: is_item returns true.
    // Postcondition: If the current item was already the last item in the
    //   sequence, then there is no longer any current item. Otherwise, the new
    //   current item is the item immediately after the original current item.
    void sequence::advance( )
    {
      assert (is_item());
      if (current_index_ == used_) {
        current_index_ = -1;
      }
      else {
        current_index_++;
      }
    }

    // Postcondition: A new copy of entry has been inserted in the sequence
    //   before the current item. If there was no current item, then the new
    //   entry has been inserted at the front of the sequence. In either case,
    //   the newly inserted item is now the current item of the sequence.
    void sequence::insert(const value_type& entry)
    {
      assert (size() < capacity_);
      if (used_ == capacity_) {
        resize(used_+1);
      }
      if (used_ == 0){
      data_[used_] = entry;
      ++used_;
      current_index_ = used_ -1;
      }
      else if (!is_item()) {
        value_type prev_entry;
        value_type next_entry = entry;
        for(size_type j=0; j<used_+1; j++){
          prev_entry = data_[j];
          data_[j] = next_entry;
          next_entry = prev_entry;
        }
      ++used_;
      current_index_ = 0;
      }
      else {
        value_type prev_entry;
        value_type next_entry;
        for (size_type j=current_index_; j<used_+1; j++) {
          prev_entry = data_ [j];
          data_ [j] = next_entry;
          next_entry = prev_entry;
        }
      ++used_;
      }
    }

    // Postcondition: A new copy of entry has been inserted in the sequence
    //   after the current item. If there was no current item, then the new
    //   entry has been attached to the end of the sequence. In either case,
    //   the newly inserted item is now the current item of the sequence.
    void sequence::attach(const value_type& entry)
    {
      if (used_ == capacity_)
      resize(used_+1);
      if(!is_item()) {
        data_[used_] = entry;
        ++used_;
        current_index_ = used_-1;
      }
      else {
        value_type prev_entry;
        value_type next_entry = entry;
        ++current_index_;
        for (size_type j=current_index_; j<used_+1; j++) {
          prev_entry = data_[j];
          data_[j] = next_entry;
          next_entry = prev_entry;
        }
      ++used_;
      } 
    }

    // Precondition: is_item returns true.
    // Postcondition: The current item has been removed from the sequence,
    //   and the item after this (if there is one) is now the new current item.
    void sequence::remove_current( )
    {
      assert (is_item());
      if (current_index_ == used_-1) {
        used_ --;
        current_index_ = -1;
      }
      else {
        for (size_type j=current_index_; j<used_-1; j++) {
          data_[j] = data_[j+1];
          used_--;
        }
      }
    }

    // Postcondition: The current object is equivalent to the object passed
    //   in.
    void sequence::operator =(const sequence& source)
    {
      value_type* new_data;
      if (this == &source)
      return;
      if (capacity_ !=source.capacity_) {
        new_data = new value_type[source.capacity_];
        data_ = new_data;
        capacity_ = source.capacity_;
      }
      current_index_ = source.current_index_;
      used_ = source.used_;
      copy(source.data_, source.data_+used_, data_);
    }

    // Postcondition: The return value is the number of items in the sequence.
    sequence::size_type sequence::size ( ) const
    {
      return used_;
    }

    // Postcondition: A true return value indicates that there is a valid
    //   "current" item that may be retrieved by activating the current
    //   member function (listed below). A false return value indicates that
    //   there is no valid current item.
    bool sequence::is_item( ) const
    {
      if (current_index_ < used_) {
        return true;
      }
      else {
        return false;
      }
    }

    //  Precondition: is_item( ) returns true.
    //  Postcondition: The item returned is the current item in the sequence.
    sequence::value_type sequence::current( ) const
    {
      if (is_item()) {
        return current_index_;
      }
    }

    //  Postcondition: The return value is true if both sequences contain no
    //    data items. Also, if the length is greater than zero, then the
    //    sequences must contain the same number of items and the items at the
    //    same location must be equal.
    bool sequence::operator ==(const sequence& other)
    {
      value_type* equal1ptr_;
      value_type* equal2ptr_;
      equal1ptr_ = data_.current_index_;
      equal2ptr_ = other.current_index_;
       if ((data_.size() == 0) && (other.size() == 0)) {
         return true;
       }
       if ((data_.size() == 0) || (other.size() == 0)) {
         return false;
       }
       if ((data_.size() > 0) && (other.size() > 0) {
        if (data_.current_index_ = other.current_index_) {
          if (equal1ptr_ = equal2ptr_) {
            data_.advance();
            other.advance();
          }
          return true;
          else { 
            if (equal1ptr_ != equal2ptr_) {
              return false;
            }
          }
        }
      else {
        if (data_.current_index_ != other.current_index_) {
          data_.current_index_ = 0;
          other.current_index_ = 0;
          if (data_.current_index_ = other.current_index_) {
            if (equal1ptr_ = equal2ptr_) {
            data_.advance();
            other.advance();
          }
          return true;
          else { 
            if (equal1ptr_ != equal2ptr_) {
              return false;
            }
          }
          }
        }
      }
      }
    }

    //  Postcondition: The return value is false if both sequences contain no
    //    data items. Also, if the length is greater than zero, then the
    //    sequences must not contain the same number of items or the items at
    //    the same location must not be equal.
    bool sequece::operator !=(const sequence& other)
    {
     value_type* equal1ptr_;
      value_type* equal2ptr_;
      equal1ptr_ = data_.current_index_;
      equal2ptr_ = other.current_index_;
       if ((data_.size() == 0) && (other.size() == 0)) {
         return false;
       }
       if ((data_.size() == 0) || (other.size() == 0)) {
         return true;
       }
       if ((data_.size() > 0) && (other.size() > 0) {
        if (data_.current_index_ = other.current_index_) {
          if (equal1ptr_ = equal2ptr_) {
            data_.advance();
            other.advance();
          }
          return true;
          else { 
            if (equal1ptr_ != equal2ptr_) {
              return false;
            }
          }
        }
      else {
        if (data_.current_index_ != other.current_index_) {
          data_.current_index_ = 0;
          other.current_index_ = 0;
          if (data_.current_index_ = other.current_index_) {
            if (equal1ptr_ = equal2ptr_) {
            data_.advance();
            other.advance();
          }
          return true;
          else { 
            if (equal1ptr_ != equal2ptr_) {
              return false;
            }
          }
          }
        }
      }
      }
    }
    // HELPER (PRIVATE) FUNCTIONS

    // Precondition: The capacity is (at least one) bigger than the number of
    //   items stored.
    // Postcondition: All data items from index to the number of items stored
    //   will be moved down one space.
    void sequence::move_down(size_type index)
    {
      assert (capacity_ > used_);
      if
    }

    // Precondition: There is at least one item stored.
    // Postcondition: All data items from index to the number of items stored
    //   will be moved up one space.
    void sequence::move_up(size_type index)
    {
      
    }
}