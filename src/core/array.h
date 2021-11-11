#ifndef _ARRAY_H_
  #define _ARRAY_H_

  #include <string.h>


  #define _allocArray( blockPtr, arraySize, elementType )    \
    realloc( blockPtr, (arraySize * sizeof(elementType)) )


  #define _deallocArray( blockPtr )   \
    free( blockPtr )


  #define _arrayIndexPtr( blockPtr, arrayIndex, elementSize )    \
    (void*)( (unsigned long int)blockPtr + (arrayIndex * elementSize) )


  #define _getValAt( blockPtr, arrayIndex, elementType )   \
    (elementType*)_arrayIndexPtr( blockPtr, arrayIndex, sizeof(elementType) )


  #define _aryCpy( srcAry, srcIndex, destAry, destIndex, len, elementType ) \
    memcpy( _arrayIndexPtr( destAry, destIndex, sizeof(elementType) ),      \
            _arrayIndexPtr( srcAry, srcIndex, sizeof(elementType) ),        \
            ( len * sizeof(elementType) ) )


  #define _setValAt( blockPtr, arrayIndex, elementType, newVal )    \
    *(elementType*) memset( _arrayIndexPtr( blockPtr, arrayIndex, sizeof(newVal) ), \
                            newVal, sizeof(elementType) )

  #define _fillArray( blockPtr, startIndex, endIndex, newVal )   \
    memset( _arrayIndexPtr( blockPtr, startIndex, sizeof(newVal) ),      \
            newVal, ( endIndex-startIndex ) )

  #define _aryLen( blockPtr, elementType )   \
    _getAryLen( blockPtr, sizeof(elementType) )

  inline unsigned long int _getAryLen( void* aryPtr, unsigned long int elementSize ){
    unsigned long int aryLen;
    for( aryLen = 0;
         *(unsigned char*)_arrayIndexPtr( aryPtr, aryLen, elementSize ) != 0x00;
         aryLen++
      );

    return aryLen;
  }


#endif // ifndef _ARRAY_H_
