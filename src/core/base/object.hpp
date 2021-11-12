
#ifndef _BASE_HPP_
  #define _BASE_HPP_

  #include <time.h>

  #include "./tools.h"


  #define HAMBURGER_NUMBER    0xb00b135
  #define SALT_MODIFIER       1337

  class Base {

    private:

      unsigned long int identifier;

      inline unsigned long int generateIdentifier(unsigned long int multiplier = HAMBURGER_NUMBER) {
        unsigned long int elapsed = time(NULL);
        unsigned long int salt = (rand() % SALT_MODIFIER) + 1;

        const char* inpStr = int_to_str(elapsed * multiplier * salt);

        return hashCode(inpStr);
      }

    public:

      inline unsigned long int setIdentifier(unsigned long int newIdentifier) {

        if (newIdentifier) {
          this->identifier = newIdentifier;
        } else {
          this->identifier = this->generateIdentifier();
        }

        return this->identifier;
      }

      inline unsigned long int getIdentifier() {
        return this->identifier;
      }


      Base(){
        this->setIdentifier(NULL);
      }
      //~Base(){
      //}

  };

#endif  // #ifndef _BASE_HPP_
