#ifndef _LIST_BASE_HPP

  #define _LIST_BASE_HPP

  #include "./node/list_node.hpp"


  template <class class_type>
  class List {

    private:

      uint32_t length;


    protected:

      virtual ListNode<class_type>* getEntry(uint32_t targIndex) {
        return NULL;
      }

      virtual void setEntry(uint32_t targIndex, class_type value) {
        /* intentionally left blank */
      }

      virtual void insertEntry(uint32_t targIndex, class_type value) {
        /* intentionally left blank */
      }

      virtual void deleteEntry(uint32_t targIndex) {
        /* intentionally left blank */
      }


    public:

      uint32_t getLength() {
        return this->length;
      }

      class_type get(uint32_t targIndex) {
        ListNode<class_type>* node = this->getEntry(targIndex);

        if (node == NULL) {
          return (class_type)NULL;
        }

        return node->value;
      }

      void set(uint32_t targIndex, class_type value) {
        this->setEntry(targIndex, value);
      }

      void remove(uint32_t targIndex) {
        this->deleteEntry(targIndex);
      }

      void push(class_type value) {
        uint32_t index = this->length;

        this->setEntry(index, value);
      }

      void unshift(class_type value) {
        uint32_t index = 0;

        this->insertEntry(index, value);
      }

      class_type pop() {
        uint32_t index = this->length - 1;

        ListNode<class_type>* node = this->getEntry(index);

        if (node == NULL) {
          return NULL;
        }

        class_type outpValue = node->value;

        this->deleteEntry(index);

        return outpValue;
      }

      class_type shift() {
        uint32_t index = 0;

        ListNode<class_type>* node = this->getEntry(index);

        if (node == NULL) {
          return NULL;
        }

        class_type outpValue = node->value;

        this->deleteEntry(index);

        return outpValue;
      }

  };

#endif
