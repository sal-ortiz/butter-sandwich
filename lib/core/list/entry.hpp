
#ifndef _LIST_ENTRY_HPP

  #define _LIST_ENTRY_HPP

  #include <stddef.h>


  template <class class_type>
  class ListEntry {

    private:

      class_type value;

      ListEntry<class_type>* next;
      ListEntry<class_type>* prev;


    public:

      ListEntry() {
        this->next = (ListEntry<class_type>*)NULL;
        this->prev = (ListEntry<class_type>*)NULL;

        //this->value = NULL;
      }

      class_type getValue() {
        return this->value;
      }

      void setValue(class_type value) {
        this->value = value;
      }

      ListEntry<class_type>* getNext() {
        return this->next;
      }

      void setNext(ListEntry<class_type>* entry) {
        this->next = entry;
      }

      ListEntry<class_type>* getPrev() {
        return this->prev;
      }

      void setPrev(ListEntry<class_type>* entry) {
        this->prev = entry;
      }

  };

#endif


