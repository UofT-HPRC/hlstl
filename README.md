# hlstl
High Level Synthesis Template Library

# Directory Structure
**common/**
<br>**common/type_manip.hpp** - Convenience helpers to manipulate, extract, and modify types

Functions:
- IsPowerOfTwo
  *Returns true if # is power of 2*

- BitsNeededToStore
  *Calculates the minimum number of bits that are needed to*
  *store the value held in integral_value*

- reverse_bit_groupings
  *Given a bit group size, reverse a word by bit groupings*
  *Similar to reversing endianess, but bit groupings not*
  *restricted to 8 bits*

- reverse_endianess
  *Reverses the endianess of a word
  *Specialization of reverse_bit_groupings where a bit group*
  *is 8 bits.*

- CountKeepBits
  *Returns the number of high bits in a keep field*

- CreateNBitMask
  *Create a mask with N bits set high (container type can*
  *be specified)*

- CreateNByteMask
  *Creates a mask of bytes, N bytes wide (return container*
  *type can be specified)*

- CreateTypeBitMask
  *Create a bit mask of the same size as the specified type*

- ExtractSmallerTypeFromIntegralType
  *Given a larger word, extract some smaller type from that*
  *word at a given offset*

- ByteAddressableToWordAddressable
  *Given a byte address, convert it to a word address,*
  *where the word size is caller specified*

- ByteAddressableToSubWordAddressable
  *Given a byte address, extract that part of the address*
  *that is used to index into subwords of a larger type*
  *e.g. if given a byte address, and the memory bus is for*
         *8 byte words, then the sub-word address is to address*
         *the 8 bytes of that word (i.e. the first 3 bits of the addr)*
         
         
<br>**common/hls_types.hpp** - Convenience helpers to define, types, derive types, inspect, and deduce types

Functions/Types:
- using hls_bool_t = ap_uint<1>;
- using hls_int_t = ap_int<32>;
- using hls_uint_t = ap_uint<32>;

- ReadVarIntoApInt
  *Given a base type with a value, store that value in an*
  *ap_u?int container*
  *(not a type cast!)*

- ReadApIntToVar
  *Given an ap_u?int container with some value encoded as*
  *a base type, return that value in that base type*
  *(not a type cast!)*

- hls_stream_flit_t
  *Given an hls stream type, derive a type that is the same*
  *type as the flit of that stream*

- hls_stream_data_t
  *Given an hls stream type, derive a type that is the same*
  *type as the data field of that stream*

- TYPE_WIDTH_IN_BITS
  *Given a type, return its width in bits*

- ComputeFieldLengthInBytes
  *Given a type, return its width in bits*

- HLS_STREAM_DATA_WIDTH
  *Given an hls stream type, return it's data field size in bits*

- FIELD_BUFFER_FITS_IN_STREAM
  *Given an hls stream type and another type, T, check to*
  *see if T can fit inside of the data field of the hls stream*
  *type*

For now this library contains the source headers of a handful of helper functions/types.
