#ifndef _BASE_HPP_
  #define _BASE_HPP_

  #include <math.h>
  #include <time.h>
  #include <stdlib.h>

  #include "./tools.h"
//  #include "./timer.h"


  #define HAMBURGER_NUMBER    0xb00b135

  class Base {

    private:
      unsigned long int identifier;
      inline unsigned long int generateIdentifier( unsigned long int multiplier = HAMBURGER_NUMBER ){
        unsigned long int elapsed = time(NULL);
        unsigned long int salt = (rand() % 1337) + 1;

        return hashCode( int_to_str(elapsed * multiplier * salt) );
      }


    public:
      inline unsigned long int setIdentifier( unsigned long int newIdentifier ){
        return this->identifier = newIdentifier ? newIdentifier : this->generateIdentifier();
      }

      inline unsigned long int getIdentifier(){
        return this->identifier;
      }


      Base(){
        this->setIdentifier( (unsigned long int)NULL );
      }
      //~Base(){
      //}


  };

#endif  // #ifndef _BASE_HPP_
