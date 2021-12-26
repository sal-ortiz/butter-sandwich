

#ifndef _LIST_ENTRY_HPP

  #define _LIST_ENTRY_HPP

  template <class class_type>
  class ListEntry {

    private:

      class_type value;

      ListEntry<class_type>* next;
      ListEntry<class_type>* prev;


    public:

      ListEntry() {
        this->next = NULL;
        this->prev = NULL;

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


#ifndef _LIST_HPP

  #define _LIST_HPP

  template <class class_type>
  class List {

    private:

      ListEntry<class_type>* root;

      ListEntry<class_type>* getEntry(unsigned long int targIndex) {
        ListEntry<class_type>* node = this->root;

        for (unsigned long int idx = 0; idx < targIndex + 1; idx++) {

          if (node->getNext() != NULL) {
            node = node->getNext();
          } else {
            break;
          }

        }

        return node;
      }

      void setEntry(unsigned long int targIndex, class_type value) {
        ListEntry<class_type>* node = this->root;

        for (unsigned long int idx = 0; idx <= targIndex; idx++) {

          if (node->getNext() == NULL) {
            ListEntry<class_type>* newEntry = new ListEntry<class_type>();

            newEntry->setPrev(node);
            node->setNext(newEntry);

          }

          node = node->getNext();
        }

        node->setValue(value);
      }


    public:

      List() {
        this->root = new ListEntry<class_type>();
      }

      ListEntry<class_type>* getRoot() {
        return this->root;
      }

      unsigned long int getLength() {
        unsigned long int length = 0;

        ListEntry<class_type>* node = this->root;

        while (node->getNext() != NULL) {
          length++;

          node = node->getNext();
        }

        return length;
      }

      class_type get(unsigned long int targIndex) {

        if (targIndex > (this->getLength() - 1)) {
          throw;
        }

        ListEntry<class_type>* node = this->getEntry(targIndex);

        return node->getValue();
      }

      void set(unsigned long int targIndex, class_type value) {
        this->setEntry(targIndex, value);
      }

      void push(class_type value) {
        unsigned long int length = this->getLength();

        ListEntry<class_type>* newEntry = new ListEntry<class_type>();
        ListEntry<class_type>* node = this->getEntry(length - 1);

        newEntry->setValue(value);

        node->setNext(newEntry);
      }

      void unshift(class_type value) {
        ListEntry<class_type>* newEntry = new ListEntry<class_type>();
        ListEntry<class_type>* root = this->getRoot();
        ListEntry<class_type>* next = root->getNext();

        newEntry->setValue(value);

        root->setNext(newEntry);

        newEntry->setPrev(root);

        if (next != NULL) {
          newEntry->setNext(next);

          next->setPrev(newEntry);
        }

      }

      class_type pop() {
        unsigned long int length = this->getLength();

        ListEntry<class_type>* newEntry = new ListEntry<class_type>();

        ListEntry<class_type>* node = this->getEntry(length - 1);
        ListEntry<class_type>* prev = this->getEntry(length - 2);

        prev->setNext(NULL);

        node->setNext(NULL);
        node->setPrev(NULL);

        class_type outpValue = node->getValue();

        delete node;

        return outpValue;
      }

      class_type shift() {
        ListEntry<class_type>* root = this->getRoot();
        ListEntry<class_type>* next = root->getNext();

        if (next != NULL) {
          ListEntry<class_type>* further = next->getNext();


          if (further) {
            root->setNext(further);
            further->setPrev(root);
          }

          next->setPrev(NULL);
          next->setNext(NULL);
        }

        class_type outpValue = next->getValue();

        delete next;

        return outpValue;
      }

  };

#endif


