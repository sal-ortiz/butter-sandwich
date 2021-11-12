// sone toolish tools


#ifndef _TOOLS_H_
  #define _TOOLS_H_

  #include <math.h>
  #include <string.h>
  #include <stdarg.h>
  #include <stdio.h> 
  #include <stdlib.h> 

  #ifndef NULL
    #define NULL  0x00
  #endif

  #ifndef NOOP
    #define NOOP ((void)0x0000)
  #endif

  // The PP_NARG macro returns the number of arguments that have been passed in */
  // posted to https://groups.google.com/forum/?fromgroups=#!topic/comp.std.c/d-6Mj5Lko_s in January 2006.
  #define PP_NARG(...) \
           PP_NARG_(__VA_ARGS__,PP_RSEQ_N())
  #define PP_NARG_(...) \
           PP_ARG_N(__VA_ARGS__)
  #define PP_ARG_N( \
            _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
           _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
           _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
           _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
           _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
           _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
           _61,_62,_63,N,...) N
  #define PP_RSEQ_N() \
           63,62,61,60,                   \
           59,58,57,56,55,54,53,52,51,50, \
           49,48,47,46,45,44,43,42,41,40, \
           39,38,37,36,35,34,33,32,31,30, \
           29,28,27,26,25,24,23,22,21,20, \
           19,18,17,16,15,14,13,12,11,10, \
           9,8,7,6,5,4,3,2,1,0








  // ===========================================================================
  //  We're redefining strlen( ... ), just to have it defined locally.
  //
  //  strlen( object )
  //    returns a 32 bit value, the length of the given object.
  //
  //      object
  //        a null-terminated string.
  //
  // ===========================================================================
  template<typename ptr_type> unsigned long int strlen( ptr_type str ){
    unsigned long int index;
    for( index=0; *(unsigned char*)(ptr_type*)( str+index ) != 0x00; index++ );
    return index;
  }



//  extern "C" void* memcpy( void*, const void*, unsigned long int );    // defined in tools.asm
//  #define memcpy( dest, src, len )  (void*)_memcpy( (void*)dest, (void*)src, (unsigned long int)len )





  // ===========================================================================
  //  Some memory management to allow for safe, indefinate persistence of memory objects.
  //  NOTE: Careless use of this functionality can lead to 'memory leaks'
  //
  //  _persist_string( object )
  //    allocates a globally persistent memory block for the given object.
  //
  //      object
  //        an object of any type (prefers primitive types and pointers, for efficiency).
  //
  //    Returns a globally accessible pointer to object.
  //
  //
  //    _purge_mem_alloc_pointers()
  //      frees each of the memory blocks allocated by _persist_string().
  //
  //    Returns no values.
  //
  // ===========================================================================
  void** mem_alloc_pointers_list = NULL;
  unsigned long int mem_alloc_pointers_list_len = 0;
  void _purge_mem_alloc_pointers(){
    for( unsigned long int index=0; index < mem_alloc_pointers_list_len; free( mem_alloc_pointers_list[index++] ) );
  }

  template<typename ptr_type> void* _persist_string( ptr_type ptr ){
    unsigned long int index = mem_alloc_pointers_list_len;
    for( index; ( (index>0) && ((unsigned long int)mem_alloc_pointers_list[index-1]!=(unsigned long int)ptr) ); index-- );

    if( index > 0 )
      return (void*)ptr;
    else {
      if( !(mem_alloc_pointers_list_len % 10) )
        mem_alloc_pointers_list = (void**)realloc( mem_alloc_pointers_list, ( (mem_alloc_pointers_list_len+10)*sizeof(void*) ) );
      mem_alloc_pointers_list[mem_alloc_pointers_list_len++] = (void*)malloc( strlen(ptr) );
      memcpy( (void*)mem_alloc_pointers_list[mem_alloc_pointers_list_len-1], (const void*)ptr, strlen((const char*)ptr)+1 );
      return (void*)mem_alloc_pointers_list[mem_alloc_pointers_list_len-1];
    }
    return (void*)ptr;
  }




  // ===========================================================================
  //
  //  unsigned char peek( unsigned char* )
  //  unsigned short int peek( unsigned short int* )
  //  unsigned long int peek( unsigned long int* )
  //
  //  unsigned char poke( unsigned char*, unsigned char )
  //  unsigned short int poke( unsigned short int*, unsigned short int )
  //  unsigned long int poke( unsigned long int*, unsigned long int )
  //
  //
  #define peek( ptr )   *ptr
  //extern "C" unsigned char _peekb( unsigned char* );      // defined in tools.asm
  //extern "C" unsigned short int _peekw( unsigned short int* ); // defined in tools.asm
  //extern "C" unsigned long int _peekd( unsigned long int* );  // defined in tools.asm

  #define poke( ptr, val )    \
    switch( sizeof(val) ){    \
      case 1:   pokeb( ptr, val );  break;      \
      case 2:   pokew( ptr, val );  break;      \
      case:3:   /* intentionally left blank. */ \
      case 4:   poked( ptr, val );  break;    }
  extern "C" unsigned char _pokeb( unsigned char*, unsigned char );                 // defined in tools.asm
  extern "C" unsigned short int _pokew( unsigned short int*, unsigned short int );  // defined in tools.asm
  extern "C" unsigned long int _poked( unsigned long int*, unsigned long int );     // defined in tools.asm




  #define abs( val )    _abs( val )
  unsigned long int _abs( unsigned long int val ){
    // hacky!!!
    unsigned long int const mask = val >> (sizeof(unsigned long int) * 8 /* bits per byte */ - 1);
    return (val + mask) ^ mask;
  }

  // ===========================================================================
  //
  //  unsigned long int call( void* method_ptr, ... )
  //
  //    void* method_ptr
  //      a pointer to the method to be called.
  //
  //    ...
  //      arguments to be passed to the method called.
  //
  //    Returns whatever was returned by the call to *method_ptr.
  //
  //#define call( method_ptr, ... )    call_c_method( (void*)method_ptr, VA_NARG(__VA_ARGS__), __VA_ARGS__ )
  //#define call( A, B, C )   call_c_method( A, B, C )

  #define call_method( method, ... )  _call_c_method( (void*)method, PP_NARG(__VA_ARGS__), array(__VA_ARGS__) )
  extern "C" unsigned long int _call_c_method( void*, unsigned long int, void* );  // defined in tools.asm

  // ===========================================================================
  //
  //  const char * int_to_hex( unsigned long int val )
  //
  //    unsigned long int val
  //      a numerical value to be converted into hexadecimal
  //
  //    Returns a string containing a hexadecimal representation of val.
  //
  const char* int_to_hex( unsigned int val ){
    char ret_str[8];
    sprintf( ret_str, "%.8x", val );  // TODO: sprintf() is a heavy call, find a better way to do this.
    return (const char*)_persist_string( ret_str );
  } // const char* int_to_hex( unsigned long int )


  // ===========================================================================
  //
  //  char* int_to_str( unsigned long int val )
  //
  //    unsigned long int val
  //        an integer to be converted.
  //
  //    Returns a string representation of val.
  //
  inline const char* int_to_str( unsigned long int val ){
    char ret_str[12];
    sprintf( ret_str, "%lu", val );  // TODO: sprintf() is a heavy call, find a better way to do this.
    return (const char*)_persist_string( ret_str );
  } // -------------------------------------------------------------------------


  // ===========================================================================
  //
  //  char* float_to_str( float val )
  //
  //    float val
  //        a float to be converted.
  //
  //    Returns a string representation of val.
  //
  inline const char* float_to_str( float val ){
    char ret_str[12];
    sprintf( ret_str, "%.3f", val );  // TODO: sprintf() is a heavy call, find a better way to do this.
    return (const char*)_persist_string( (char*)ret_str );
  } // -------------------------------------------------------------------------


  // ===========================================================================
  //
  //  char* memset( void* dest, unsigned char val, unsigned long int len )
  //
  //
  //    Returns a char* , concatenated, representation of the arguments.
  //
  //    TODO: Optimize this!
  //
//  inline const char* memset( void* dest, unsigned char val, unsigned long int len ){
//    for( unsigned long int index=len; --index<len; *(char*)((unsigned long int)dest+index) = (unsigned char)val );
//  } // -------------------------------------------------------------------------

  // ===========================================================================
  //
  //  char* strcat( char*, const char* )
  //
  //
  //    Returns a char* , concatenated, representation of the arguments.
  //
  //    TODO: Optimize this!
  //
//  inline const char* strcat( char* destStr, const char* srcStr ){
//    sprintf( destStr, "%s%s", srcStr );   // TODO: sprintf() is a heavy call, find a better way to do this.
//    return destStr;
//  } // -------------------------------------------------------------------------

  // ===========================================================================
  //
  //  char* str_join( char* &, ... )
  //
  //    ...
  //        strings to be concatenated.
  //
  //    Returns a char* , concatenated, representation of the arguments.
  //
  #define str_join( ... )   _str_join( PP_NARG(__VA_ARGS__), __VA_ARGS__ )
  inline const char* _str_join( unsigned char num_params, ... ){
    va_list args;
    unsigned char params_index;
    
    char ret_str[256];  memset( ret_str, 0x00, 256 );

    va_start( args, num_params );
    for( params_index = 0; params_index < num_params; params_index++ )
      strcat( ret_str, va_arg( args, const char* ) );
    va_end( args );

    return (const char*)_persist_string( (char*)ret_str );
  } // -------------------------------------------------------------------------




  // ===========================================================================
  //
  //  char* str_match( const char*, const char* )
  //
  //    const char*
  //        a string.
  //
  //    const char*
  //        a string.
  //
  //    Returns true if strings matchd.
  //
  bool str_match( const char* strOne, const char* strTwo, unsigned int startIndex=0 ){
    if( (!strOne || !strTwo) && strOne==strTwo )    return true;  // avoid segfaults.

    unsigned int index;
    for(  index = startIndex;
          (strOne[index] && strTwo[index]) && (strOne[index] == strTwo[index]);
          index++ );

    return(!strOne[index] && !strTwo[index]);
  } // -------------------------------------------------------------------------

  inline const void* _create_persistent_array( unsigned long int num_params, ... ){
    va_list args;
    unsigned char params_index = 0;
    unsigned long int *params = new unsigned long int[ num_params ];

    va_start( args, num_params );
      for( params_index = 0; params_index < num_params; params[params_index++]=va_arg( args, unsigned long int ) )
    va_end( args );

    return params;
  }
  #define array( ... )    (void*)_create_persistent_array( PP_NARG(__VA_ARGS__), __VA_ARGS__ )





  // ===========================================================================
  //
  //  unsigned long int hashCode( const char* )
  //
  //    const char*
  //        a string.
  //
  //    Returns a 32bit value unique to the string input.
  //    TODO: test.
  //
  unsigned long int hashCode( const char* str ){
    // TODO: optimize this!
    unsigned long int hamburger_number = 0xb000b135;
    for(  unsigned long int index = 0;
          (unsigned char)str[ index ];
          index++ )
      hamburger_number ^= (unsigned long int)pow( str[index], index+1 );

    return hamburger_number;
  }

#endif  // #ifndef _TOOLS_H_
