
#ifndef _STRING_HPP_
  #define _STRING_HPP

  #include "./array.hpp"


  class String: public Array<char> {

    public:

      String(const char* str){
        setVal(str);
      }

      const char* operator= (const char* str){
        setVal(str);

        return str;
      }

      //operator const char* (){
      //  printf("sdfasdadsfasdF\n");
      //  return (const char*)getVal();
      //}

  };

#endif  // #ifndef _STRING_HPP_
