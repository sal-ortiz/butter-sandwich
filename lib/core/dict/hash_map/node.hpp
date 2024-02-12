
#ifndef _HASHMAP_NODE_HPP

  #define _HASHMAP_NODE_HPP

  #include <string.h>


  template <class class_type>
  class HashMapNode {

    private:

      const char* key;
      class_type value;


    public:

      HashMapNode() {
        this->key = (const char*)NULL;
        this->value = (class_type)NULL;
      }

      HashMapNode(const char* key, class_type value) {
        this->setKey(key);
        this->setValue(value);
      }

      ~HashMapNode() {
        delete this->key;
      }

      const char* getKey() {
        return this->key;
      }

      void setKey(const char* key) {
        uint32_t keyLen = strlen(key);
        char* newKey = new char[keyLen + 1];

        strcpy(newKey, key);

        this->key = newKey;
      }

      class_type getValue() {
        return this->value;
      }

      void setValue(class_type newValue) {
        this->value = newValue;
      }

  };

#endif
