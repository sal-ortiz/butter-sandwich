#ifndef _BASE_HPP_ 
  #define _BASE_HPP_

  #include <math.h>

  #include "./tools.h"
  #include "./timer.h"

  #define HAMBURGER_NUMBER    0xb00b135

  class Base {

    private:
      unsigned long int identifier;
      inline unsigned long int generateIdentifier( unsigned long int multiplier = HAMBURGER_NUMBER ){
        return hashCode( int_to_str((unsigned long int)(get_elapsed_runtime() * multiplier)) );
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
