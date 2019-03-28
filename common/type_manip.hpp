#ifndef TYPE_MANIP_HPP
#define TYPE_MANIP_HPP

#include <cstdint>
#include <type_traits>
#include <ap_int.h>
#include <type_traits>

constexpr uint8_t BITS_PER_BYTE = 8;

/* ==Compile time==
 * Check to see if a number is a power of two. Input type must be
 * integral - currently ap_uint/ap_int is not supported but it can easily be added by improving
 * the static assertion based on type
 * RETURN: True if integral_value is power of two
 */
template <typename INTEGRAL_TYPE_T>
constexpr bool IsPowerOfTwo(const INTEGRAL_TYPE_T integral_value)
{
    static_assert(std::is_integral<INTEGRAL_TYPE_T>::value, "Can only check IsPowerOfTwo for integral values");
    return integral_value != 0 && ((integral_value - 1) & integral_value) == 0;
}

/* ==Compile time==
 * Calculates the minimum number of bits that are needed to store the value held in integral_value, 
 * as an unsigned integral
 * e.g. integral_value 3 requires 2 bits unsigned
 *      integral_value 4 requires 3 bits unsigned
 *      integral_value 15 requires 4 bits unsigned
 * To figure out how many bits youd need to store the number as a signed value, add 1 to the return
 * RETURN: the min num of bits needed to represent argument "integral_value" as an unsigned integral
 */
template <typename INTEGRAL_TYPE_T, INTEGRAL_TYPE_T integral_value>
inline constexpr uint8_t BitsNeededToStore()
{
    //static_assert(std::is_integral<INTEGRAL_TYPE_T>::value, "Can only check IsPowerOfTwo for integral values");
    static_assert(((uint64_t)1 << 32) > integral_value, "Maximum supported size for check of BitsNeededToStore is 32bit");
    static_assert(0 <= integral_value, "Only positive values are currently supported");
#ifndef __DISABLE_SMART_AP__
    return (static_cast<uint32_t>(integral_value) < (1 << 1)) ? 1 :\
           (static_cast<uint32_t>(integral_value) < (1 << 2)) ? 2 :\
           (static_cast<uint32_t>(integral_value) < (1 << 3)) ? 3 :\
           (static_cast<uint32_t>(integral_value) < (1 << 4)) ? 4 :\
           (static_cast<uint32_t>(integral_value) < (1 << 5)) ? 5 :\
           (static_cast<uint32_t>(integral_value) < (1 << 6)) ? 6 :\
           (static_cast<uint32_t>(integral_value) < (1 << 7)) ? 7 :\
           (static_cast<uint32_t>(integral_value) < (1 << 8)) ? 8 :\
           (static_cast<uint32_t>(integral_value) < (1 << 9)) ? 9 :\
           (static_cast<uint32_t>(integral_value) < (1 << 10)) ? 10 :\
           (static_cast<uint32_t>(integral_value) < (1 << 11)) ? 11 :\
           (static_cast<uint32_t>(integral_value) < (1 << 12)) ? 12 :\
           (static_cast<uint32_t>(integral_value) < (1 << 13)) ? 13 :\
           (static_cast<uint32_t>(integral_value) < (1 << 14)) ? 14 :\
           (static_cast<uint32_t>(integral_value) < (1 << 15)) ? 15 :\
           (static_cast<uint32_t>(integral_value) < (1 << 16)) ? 16 :\
           (static_cast<uint32_t>(integral_value) < (1 << 17)) ? 17 :\
           (static_cast<uint32_t>(integral_value) < (1 << 18)) ? 18 :\
           (static_cast<uint32_t>(integral_value) < (1 << 19)) ? 19 :\
           (static_cast<uint32_t>(integral_value) < (1 << 20)) ? 20 :\
           (static_cast<uint32_t>(integral_value) < (1 << 21)) ? 21 :\
           (static_cast<uint32_t>(integral_value) < (1 << 22)) ? 22 :\
           (static_cast<uint32_t>(integral_value) < (1 << 23)) ? 23 :\
           (static_cast<uint32_t>(integral_value) < (1 << 24)) ? 24 :\
           (static_cast<uint32_t>(integral_value) < (1 << 25)) ? 25 :\
           (static_cast<uint32_t>(integral_value) < (1 << 26)) ? 26 :\
           (static_cast<uint32_t>(integral_value) < (1 << 27)) ? 27 :\
           (static_cast<uint32_t>(integral_value) < (1 << 28)) ? 28 :\
           (static_cast<uint32_t>(integral_value) < (1 << 29)) ? 29 :\
           (static_cast<uint32_t>(integral_value) < (1 << 30)) ? 30 :\
           (static_cast<uint32_t>(integral_value) < (1 << 31)) ? 31 : 32;
#else
    return 32;//(static_cast<uint32_t>(integral_value) < (1 << 8)) ? 8 :\
           (static_cast<uint32_t>(integral_value) < (1 << 16)) ? 16 : 32;   
#endif
}

/* ==Compile time or Runtime==.
 * Calculates the minimum number of bits that are needed to store the value held in integral_value, 
 * as an unsigned integral
 * TARG1 - INTEGRAL_TYPE_T: Automatically inferred by ARG1 "integral_value"
 * ARG1 - integral_value: The value we wish to see how many bits are needed to store
 * e.g. integral_value 3 requires 2 bits unsigned
 *      integral_value 4 requires 3 bits unsigned
 *      integral_value 15 requires 4 bits unsigned
 * To figure out how many bits youd need to store the number as a signed value, add 1 to the return
 * RETURN: the min num of bits needed to represent argument "integral_value" as an unsigned integral
 */
template <typename INTEGRAL_TYPE_T>
constexpr uint8_t BitsNeededToStore(const INTEGRAL_TYPE_T integral_value)
{
#ifndef __DISABLE_SMART_AP__
    return (static_cast<uint32_t>(integral_value) < (1 << 1)) ? 1 :\
           (static_cast<uint32_t>(integral_value) < (1 << 2)) ? 2 :\
           (static_cast<uint32_t>(integral_value) < (1 << 3)) ? 3 :\
           (static_cast<uint32_t>(integral_value) < (1 << 4)) ? 4 :\
           (static_cast<uint32_t>(integral_value) < (1 << 5)) ? 5 :\
           (static_cast<uint32_t>(integral_value) < (1 << 6)) ? 6 :\
           (static_cast<uint32_t>(integral_value) < (1 << 7)) ? 7 :\
           (static_cast<uint32_t>(integral_value) < (1 << 8)) ? 8 :\
           (static_cast<uint32_t>(integral_value) < (1 << 9)) ? 9 :\
           (static_cast<uint32_t>(integral_value) < (1 << 10)) ? 10 :\
           (static_cast<uint32_t>(integral_value) < (1 << 11)) ? 11 :\
           (static_cast<uint32_t>(integral_value) < (1 << 12)) ? 12 :\
           (static_cast<uint32_t>(integral_value) < (1 << 13)) ? 13 :\
           (static_cast<uint32_t>(integral_value) < (1 << 14)) ? 14 :\
           (static_cast<uint32_t>(integral_value) < (1 << 15)) ? 15 :\
           (static_cast<uint32_t>(integral_value) < (1 << 16)) ? 16 :\
           (static_cast<uint32_t>(integral_value) < (1 << 17)) ? 17 :\
           (static_cast<uint32_t>(integral_value) < (1 << 18)) ? 18 :\
           (static_cast<uint32_t>(integral_value) < (1 << 19)) ? 19 :\
           (static_cast<uint32_t>(integral_value) < (1 << 20)) ? 20 :\
           (static_cast<uint32_t>(integral_value) < (1 << 21)) ? 21 :\
           (static_cast<uint32_t>(integral_value) < (1 << 22)) ? 22 :\
           (static_cast<uint32_t>(integral_value) < (1 << 23)) ? 23 :\
           (static_cast<uint32_t>(integral_value) < (1 << 24)) ? 24 :\
           (static_cast<uint32_t>(integral_value) < (1 << 25)) ? 25 :\
           (static_cast<uint32_t>(integral_value) < (1 << 26)) ? 26 :\
           (static_cast<uint32_t>(integral_value) < (1 << 27)) ? 27 :\
           (static_cast<uint32_t>(integral_value) < (1 << 28)) ? 28 :\
           (static_cast<uint32_t>(integral_value) < (1 << 29)) ? 29 :\
           (static_cast<uint32_t>(integral_value) < (1 << 30)) ? 30 :\
           (static_cast<uint32_t>(integral_value) < (1 << 31)) ? 31 : 32;
#else
    return 32;//(static_cast<uint32_t>(integral_value) < (1 << 8)) ? 8 :\
           (static_cast<uint32_t>(integral_value) < (1 << 16)) ? 16 : 32;   
#endif
}



/* == Runtime ==
 * returns the reversed datum (usually datum is a byte) ordering (or endianness) of the input value
 * A specialization is provided below (reverse_endianess) for reversing byte ordering with a simpler
 * interface, but note that sometimes we wish to reverse at a smaller granularity such as 4-bit 
 * groupings for some field groups on some network packet headers
 * TARG1 - BIT_GROUP_SIZE: bit grouping size (e.g. for bytes, this would be 8 since bytes are 8 bits wide)
 * TARG2 - T: Type of input, automatically inferred
 * ARG1 - input: The value we wish to reverse
 * RETURN: the reversed bit groupings of "input" stored in the same type/container as ARG1
 */
template <int BIT_GROUP_SIZE, typename T>
const T reverse_bit_groupings(const T &input) {
    constexpr int GROUP_COUNT = T::width / BIT_GROUP_SIZE;
    T reversed;
    for (uint8_t group_i = 0; group_i < GROUP_COUNT; ++group_i) {
        #pragma HLS UNROLL
        const uint8_t lo_i = group_i * BIT_GROUP_SIZE;
        const uint8_t hi_i = lo_i + BIT_GROUP_SIZE - 1;
        const uint8_t group_o = GROUP_COUNT - 1 - group_i;
        const uint8_t lo_o = group_o * BIT_GROUP_SIZE;
        const uint8_t hi_o = lo_o + BIT_GROUP_SIZE - 1;
        reversed.range(hi_o, lo_o) = input(hi_i, lo_i);
    }

    return reversed;
}


/* == Runtime ==
 * Specialization of "reverse_bit_groupings" where BIT_GROUP_SIZE is hardcoded to 8 (the width of a byte)
 * returns the reversed byte ordering (or endianness) of the input value
 */
template <typename T>
const T reverse_endianess(const T &input) {
    //static_assert(T::width % 8 == 0, "Size of type must be a multiple of 8 bits");
    return reverse_bit_groupings<8, T>(input);
}



/* Given a keep field on an AXI bus, calculate how many bits are active. Specializations are
 * provided (below) for more efficient implementations 
 * TARG1 - BIT_WIDTH: automatically inferred by the type passed in to "keep_field"
 * ARG1 - keep_field: the keep field from the axi bus to count the bits on
 * RETURN: the number of high bits
 */
template <int BIT_WIDTH>
const ap_uint<BIT_WIDTH> CountKeepBits(const ap_uint<BIT_WIDTH> keep_field)
{
    for (int i = 0; i < BIT_WIDTH; i++) {
        #pragma HLS UNROLL
        if ((keep_field >> i) == 1) {
            return i + 1;
        }
    }
    return 0;
}

/* Specialization of CountKeepBits - should be inferred as a simple LUT */
template <>
inline const ap_uint<1> CountKeepBits<1>(const ap_uint<1> keep_field)
{
    switch (keep_field) {
        case 0x0: return 0;
        case 0x1: return 1;
        default: return 0;
    };
}

/* Specialization of CountKeepBits - should be inferred as a simple LUT */
template <>
inline const ap_uint<2> CountKeepBits<2>(const ap_uint<2> keep_field)
{
    switch (keep_field) {
        case 0x0: return 0;
        case 0x1: return 1;
        case 0x3: return 2;
        default: return 0;
    };
}

/* Specialization of CountKeepBits - should be inferred as a simple LUT */
template <>
inline const ap_uint<4> CountKeepBits<4>(const ap_uint<4> keep_field)
{
    switch (keep_field) {
        case 0x0: return 0;
        case 0x1: return 1;
        case 0x3: return 2;
        case 0x7: return 3;
        case 0xf: return 4;
        default: return 0;
    };
}

/* Specialization of CountKeepBits - should be inferred as a simple LUT (or 2 LUT w/ mux) */
template <>
inline const ap_uint<8> CountKeepBits<8>(const ap_uint<8> keep_field)
{
    switch (keep_field) {
        case 0x0: return 0;
        case 0x1: return 1;
        case 0x3: return 2;
        case 0x7: return 3;
        case 0xf: return 4;
        case 0x1f: return 5;
        case 0x3f: return 6;
        case 0x7f: return 7;
        case 0xff: return 8;
        default: return 0;
    };
}

/* Specialization of CountKeepBits - should be inferred as a simple LUT (or multi-LUT w/ mux)*/
template <>
inline const ap_uint<16> CountKeepBits<16>(const ap_uint<16> keep_field)
{
    switch (keep_field) {
        case 0x0: return 0;
        case 0x1: return 1;
        case 0x3: return 2;
        case 0x7: return 3;
        case 0xf: return 4;
        case 0x1f: return 5;
        case 0x3f: return 6;
        case 0x7f: return 7;
        case 0xff: return 8;
        case 0x1ff: return 9;
        case 0x3ff: return 10;
        case 0x7ff: return 11;
        case 0xfff: return 12;
        case 0x1fff: return 13;
        case 0x3fff: return 14;
        case 0x7fff: return 15;
        case 0xffff: return 16;
        default: return 0;
    };
}


/* == Runtime == 
 * NOTE: This function should not be called directly by an user
 * A helper function for CreateNBitMask where given a number "n_bits"
 * a bit mask of type return_type_t will be returned. 
 * e.x. if return_type_t is uint8_t and n_bits = 5, then return is 8b00011111
 */
template <typename return_type_t, int RETURN_TYPE_BIT_LENGTH >
return_type_t CreateNBitMask_Inner(const int n_bits) {
    constexpr int length_plus_one = RETURN_TYPE_BIT_LENGTH + 1;
    return_type_t return_val = 0;

    // TODO: measure the estimate for different bit width and possibly add a special case for this if return_type_t::width < some_size;
    // = ((ap_uint<length_plus_one>)1 << n_bits) - 1;
    
    for (int i = 0; i < RETURN_TYPE_BIT_LENGTH; i++) {
        #pragma HLS UNROLL
        return_val[i] = (return_type_t)(((ap_uint<length_plus_one>)(i < n_bits?1:0))/* << i*/);
    }
    
    return return_val;
}

/* Helper function to compute the bit width of the return type in CreateNBitMask
 * specialization for ap_u?int_types
 * NOTE: Shouldn't be called directly by user 
 */
template <typename return_type_t, bool = std::is_integral<return_type_t>::value>
struct CreateNBitMaskHelper {
    constexpr static int BIT_LENGTH = return_type_t::width;
};
/* Helper function to compute the bit width of the return type in CreateNBitMask 
 * specialization for integral types
 * NOTE: Shouldn't be called directly by user 
 */
template <typename return_type_t>
struct CreateNBitMaskHelper<return_type_t, true> {
    constexpr static int BIT_LENGTH = sizeof(return_type_t) * 8;
};

/* == Runtime or Compile time ==
 * Returns a mask of type return_type_t where the "n_bits" least significant bits are set high
 * with the remainder set low
 * RETURN: an n-bit mask
 *   e.x. if return_type_t is uint8_t and n_bits is 5, the return is 8b00011111
 * NOTE: Called for native integral types
 */
template <typename return_type_t>
return_type_t CreateNBitMask(const int n_bits) 
{
    return CreateNBitMask_Inner<return_type_t, CreateNBitMaskHelper<return_type_t>::BIT_LENGTH>(n_bits);
}

/* Specialization of CreateNBitMask, where the return type is non-integral (e.g. ap_u?int)
 * NOTE: Called for ap_u?int types
 */
template <typename return_type_t, typename std::enable_if<!std::is_integral<return_type_t>::value, void>::type>
return_type_t CreateNBitMask(const int n_bits) 
{
    return CreateNBitMask_Inner<return_type_t, return_type_t::width>(n_bits);
}




template <int CURRENT_BYTE>
struct ByteMaskMaker {
    template <typename return_type_t>
    static constexpr auto GetByteMask() -> return_type_t {
        static_assert(CURRENT_BYTE > 1, "Can only create byte masks for > 1 or more bytes");
        return (ByteMaskMaker<CURRENT_BYTE-1>::template GetByteMask<return_type_t>() << 8) | 0xFF;
    }   
};

template <>
struct ByteMaskMaker<0> {
    template <typename return_type_t>
    static constexpr auto GetByteMask() -> return_type_t{
        return static_cast<return_type_t>(0xFF);
    }
};

/* == Runtime == (Compile time specialization provided below)
 * Similar to CreateNBitMask except n_bytes represents how many 8-bit groupings
 * to mask in with the return value. Although it may seem redundant and might
 * be better at first glance to just implement this as 
 *   return CreateNBitMask(n_bytes * 8):
 * this implementation will result in fewer resources used and better timing.
 * RETURN: the byte mask
 */
template <typename return_type_t>
inline return_type_t CreateNByteMask(const int n_bytes) {
    static_assert(sizeof(return_type_t) <= 16, "Probably too big for CreateNByteMask");
    constexpr int type_byte_count = sizeof(return_type_t);
    uint8_t bytes[sizeof(return_type_t)];
	#pragma HLS ARRAY_PARTITION VARIABLE=bytes COMPLETE

    for (int i = 0; i < type_byte_count; i++) {
		#pragma HLS UNROLL
    	int byte_num = i;
        bytes[i] = (byte_num < n_bytes) ? 0xFF : 0x00;
    }

    return *(return_type_t*)(bytes);
}

/* == Compile time ==
 * Compile time specialization of CreateNByteMask
 * RETURN: the byte mask
 * TODO: Create a common implementaton that can be shared with CreateNBitMask
 *       where ByteMaskMaker is changed to BitGroupMaskMaker and GetByteMask
 *       is changed to GetMask and another template argument is added as the mask width
 *       is added to specify the mask bit width (so it is computed at compile time with no overhead)
 *       Then change CreateNByteMask to 
 *         return BitGroupMaskMaker<(int)(n_bytes-1)>::template GetMask<return_type_t, 8>();
 *       And CreateNBitMask is changed to 
 *         return BitGroupMaskMaker<(int)(n_bytes-1)>::template GetMask<return_type_t, 1>();
 */
template <typename return_type_t, int n_bytes>
constexpr return_type_t CreateNByteMask() {
    #pragma HLS INLINE RECURSIVE
    static_assert(sizeof(return_type_t) < 16, "Probably too big for CreateNByteMask constexpr");
    return ByteMaskMaker<(int)(n_bytes-1)>::template GetByteMask<return_type_t>();
}

/* == Compile time ==
 * Given a (return) type (return_type_t), create a mask for that type
 * Return a bit mask of the same size of the type specified by return_type_t
 * ex. if return_type_t is uint8_t, then this will return an 8-bit mask
 *      if return_type_t is int32_t, then this will return a 32-bit mask
 */
template <typename return_type_t>
constexpr return_type_t CreateTypeBitMask() {
    static_assert(sizeof(return_type_t) <= 8, "CreateTypeBitMask supports max bytecount of 8");
    return static_cast<return_type_t>(CreateNByteMask<return_type_t, sizeof(return_type_t)>());
}

/* == Runtime ==
 * Given a larger word type, extract some smaller type at an offset into the larger type
 * ex. extract the second byte of an int: 
 *       ExtractSmallerTypeFromIntegralType<int32_t, uint8_t>(int_type_value, sizeof(uint8_t) * 2)
 * TODO: Create a specialized version that will automatically calculate an offset based on subfield_type_t
 *       (instead of calling the arg offset, it would be called "index") because it will be treating the
 *       larger type as an array of the subfield type
 */
template <typename bitfield_t, typename subfield_type_t>
constexpr subfield_type_t ExtractSmallerTypeFromIntegralType(const bitfield_t integral_value, const uint8_t offset) {
    static_assert(sizeof(bitfield_t) <= 8, "ExtractSmallerTypeFromIntegralType supports max bytecount of 8");
    static_assert(sizeof(bitfield_t) >= sizeof(subfield_type_t), "output size is larger than the input size");
    return static_cast<subfield_type_t>((integral_value >> offset) & CreateTypeBitMask<subfield_type_t>());
}


/* == Runtime (OPTIMIZED when BYTES_PER_WORD is known at compile time) ==
 * Given a type that describes an address (more accurately, a byte address), 
 * and a word size in bytes, retrieve the word address
 * portion of the byte address */
template <typename ADDRESS_T, int BYTES_PER_WORD>
constexpr ADDRESS_T ByteAddressableToWordAddressable(const ADDRESS_T address)
{
    //static_assert(std::is_integral<ADDRESS_T>::value, "BYTES_PER_WORD must be integral type");
    return  address >> BitsNeededToStore<ADDRESS_T>(BYTES_PER_WORD);
}

/* == Runtime, unoptimized for when BYTES_PER_WORD is only known at runtime ==
 * Given a type that describes an address, and a word size in bytes, retrieve the word address
 * portion of the byte address */
template <typename ADDRESS_T>
ADDRESS_T ByteAddressableToWordAddressable(const ADDRESS_T address, const int BYTES_PER_WORD)
{
    //static_assert(std::is_integral<ADDRESS_T>::value, "BYTES_PER_WORD must be integral type");
    return  address >> BitsNeededToStore<ADDRESS_T>(BYTES_PER_WORD);
}

/* == Runtime ==
 * A specialization for when we want to convert a byte address to a default size word address
 * The default size is based on the size of the address
 */
template <typename ADDRESS_T>
constexpr ADDRESS_T ByteAddressableToWordAddressable(const ADDRESS_T address)
{
    //static_assert(std::is_integral<ADDRESS_T>::value, "BYTES_PER_WORD must be integral type");
    return ByteAddressableToWordAddressable<ADDRESS_T, sizeof(ADDRESS_T)>(address);
}

/* == Runtime (OPTIMIZED when BYTES_PER_WORD is known at compile time) ==
 * Given a type that describes an address, and a word size in bytes, retrieve the part of the byte
 * address that will index into a word to retrieve this byte */
template <typename ADDRESS_T, int BYTES_PER_WORD>
constexpr ADDRESS_T ByteAddressableToSubWordAddressable(const ADDRESS_T address)
{
    //static_assert(std::is_integral<ADDRESS_T>::value, "BYTES_PER_WORD must be integral type");
    return  address & (CreateNBitMask<uint8_t, BitsNeededToStore<ADDRESS_T, BYTES_PER_WORD>() - 1>());
}

/* == Runtime ==
 * Specialization for when the word size is the size of an address
 */
template <typename ADDRESS_T>
constexpr ADDRESS_T ByteAddressableToSubWordAddressable(const ADDRESS_T address)
{
    //static_assert(std::is_integral<ADDRESS_T>::value, "BYTES_PER_WORD must be integral type");
    return ByteAddressableToSubWordAddressable<ADDRESS_T, sizeof(ADDRESS_T)>(address);
}

