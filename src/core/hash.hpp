
#ifndef _HASH_HPP_
  #define _HASH_HPP_

  #include "./base/tools.h"
  #include "./array.hpp"
  #include "./linked_list.hpp"


  #define _HASH_OBJECT_ARRAY_LEN   37

  template <class class_type>
  class Hash: public Array<LinkedList<class_type>> {

    private:

      unsigned long int calcIndex(const char* key) {
        return hashCode(key) % _HASH_OBJECT_ARRAY_LEN;
      }

    public:

      Hash() : Array<LinkedList<class_type>>(_HASH_OBJECT_ARRAY_LEN){
        // intentionally left blank.
      }

      class_type get(const char* key) {
        unsigned long int hCode = hashCode(key);
        unsigned long int idx = calcIndex(key);

        LinkedList<class_type>* tableEntry = Array<LinkedList<class_type>>::getValAt(idx);
        LinkedListEntry<class_type>* listEntry = tableEntry->getByIdentifier(hCode);

        return listEntry->getVal();
      }

      class_type set(const char* key, class_type newVal) {
        unsigned long int hCode = hashCode(key);
        unsigned long int idx = calcIndex(key);

        LinkedList<class_type>* tableEntry = Array<LinkedList<class_type>>::getValAt(idx);
        return tableEntry->push(hCode, newVal);
      }

      inline class_type& operator[](const char* key) {
        return get( key );
      } // class_type& operator[]( const char* )

  };  // class Hash

#endif  // #ifndef _HASH_HPP_
