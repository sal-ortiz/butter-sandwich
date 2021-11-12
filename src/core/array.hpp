#ifndef _ARRAY_HPP_
#define _ARRAY_HPP_



  #include "./base//tools.h"
  #include "./array.h"
  #include "./base/container.hpp"


  template <class class_type>
  class Array: private ContainerBase {

    private:

    protected:

      class_type* blockPtr;

      unsigned long int numEntries;

      void initArray(unsigned long int num_entries) {
        blockPtr = (class_type*)malloc(0);
        numEntries = num_entries;
        blockPtr = (class_type*)_allocArray(blockPtr, numEntries, class_type);
      }

      void deinitArray() {
        numEntries = 0;
        _deallocArray(blockPtr);
      }

    public:

      Array(unsigned long int len = 0) {
        initArray(len);
      } // constructor()

      Array(const class_type* block) {
        initArray(_aryLen(block, class_type), sizeof(class_type));
        _aryCpy(block, 0, blockPtr, 0, _aryLen(block, class_type), class_type);
      } // constructor(const class_type*)

      ~Array() {
        deinitArray();
      } // destructor()

      //class_type& operator[](const long int index) {
      //  return *(class_type*)getValAt(index);
      //  //return *(class_type*)_arrayIndexPtr(blockPtr, index, sizeof(class_type));
      //}  // class_type operator[](const unsigned long int)

      //template<typename function_type>  operator function_type*() {   return (function_type*)blockPtr;   } // operator char*()

      operator class_type* () {
        return getVal();
      }

      class_type* operator= (class_type* ary) {
        setVal(ary);
        return ary;
      }

      inline unsigned long int length() {
        return numEntries;
      }

      inline unsigned long int size() {
        return numEntries * sizeof(class_type);
      }

      inline void fill(class_type val, unsigned long int index = 0, unsigned long int len = 0xffffffff) {

        if (len == 0xffffffff) {
          len = numEntries - index;
        }

        _fillArray(blockPtr, index, (index+len), val);
      }

      inline void setVal(class_type* val) {
        resize(_aryLen(val, class_type));
        _aryCpy(val, 0, blockPtr, 0, _aryLen(val, class_type), class_type);
      }

      inline class_type* getVal() {
        return blockPtr;
      }

      inline class_type setValAt(unsigned long int index, class_type val) {
        _setValAt(blockPtr, index, class_type, val);

        return val;
      }

      inline class_type* getValAt(unsigned long int index) {
        return _getValAt(blockPtr, index, class_type);
      }

      class_type* resize(unsigned long int newSize) {
        initArray(newSize);

        return blockPtr;
      }

      inline class_type push(class_type newEntry) {
        resize(numEntries + 1);

        return setValAt(numEntries-1, newEntry);
      }

      inline class_type* pop() {
        class_type *retval = _getValAt(blockPtr, numEntries-1, class_type);
        resize(numEntries - 1);

        return retval;
      }

  };  // class Array


#endif  // #ifndef _ARRAY_HPP_
