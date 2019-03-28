#ifndef HLS_TYPES_HPP
#define HLS_TYPES_HPP

#include <ap_int.h>
#include <type_traits>
#include <iostream>
#include "common/bitmanip.hpp"


using hls_bool_t = ap_uint<1>;
using hls_int_t = ap_int<32>; // Vivado adds 1 bit on top of this for the sign for some stupid reason instead including the sign in the #bits specified
using hls_uint_t = ap_uint<32>;

/*
template<bool Condition, typename T = void >
using enable_if_t = typename std::enable_if<Condition, T>::type;

template <typename type_t>
using enable_if_floating_point = enable_if_t<std::is_floating_point<type_t>::value, type_t>;
template <typename type_t>
using enable_if_not_integral_or_fp = enable_if_t<!std::is_floating_point<type_t>::value && !std::is_integral<type_t>::value, type_t>;
template <typename type_t>
using enable_if_bool = enable_if_t<std::is_same<bool,type_t>::value, type_t>;
template <typename type_t>
using enable_if_integral = enable_if_t<std::is_integral<type_t>::value, type_t>;
*/


/* == Compile time ==
 * Given an base type (float in this case), copy it into an ap_u?int container
 * NOTE: THIS IS NOT A TYPE CAST
 */
template <typename return_t, typename T>
typename std::enable_if<std::is_floating_point<T>::value, return_t>::type 
ReadVarIntoApInt(T var) {
	return_t buffer = 0;
	memcpy(&buffer, &var, sizeof(var));
	return buffer;
}

/* == Compile time ==
 * Given an base type (integral in this case), copy it into an ap_u?int container
 * NOTE: THIS IS NOT A TYPE CAST
 */
template <typename return_t, typename T>
typename std::enable_if<std::is_integral<T>::value, return_t>::type 
ReadVarIntoApInt(T var) {
    constexpr int sizeof_var = sizeof(var);
    static_assert(sizeof_var * 8 <= return_t::width, "Result container too small to hold input");
    return var;
}

/* == Compile time ==
 * Given an base type (bool in this case), copy it into an ap_u?int container
 * NOTE: THIS IS NOT A TYPE CAST
template <typename return_t, typename T>
typename std::enable_if<std::is_same<bool,T>::value || std::is_same<const bool,T>::value, return_t>::type ReadVarIntoApInt(
    T &bool_var)
{
    return_t bitfield = 0;
    bitfield[0] = bool_var;
    return bitfield;
}
*/

/* == Compile time ==
 * Given an base type (aggregate/struct in this case), copy it into an ap_u?int container.
 * NOTE: THIS IS NOT A TYPE CAST
 * NOTE: that in newer versions of C++ there is an is_aggregate type trait check that can be used
 *       *AFTER* vivado_hls supports c++ versions higher than c++11. However, at the moment,
 *       vivado_hls only supports up to C++11, so we can't use that type trait
 */
template <typename return_t, typename T>
typename std::enable_if<!std::is_floating_point<T>::value && !std::is_integral<T>::value && !std::is_same<bool,T>::value && !std::is_same<const bool,T>::value, return_t>::type 
ReadVarIntoApInt (
    T &aggregate) // After C++17 support added - change to std::is_aggregate
{
    static_assert(return_t::width <= sizeof(T) * 8, "Result container too small to hold input");
    return aggregate.BitCopy();
}


/* == Compile time ==
 * Given an ap_u?int container type, return that value as a base type (floating point in this case)
 * NOTE: THIS IS NOT A TYPE CAST
 */
template <typename return_t, typename AP_INT_T>
typename std::enable_if<std::is_floating_point<return_t>::value, return_t>::type 
ReadApIntToVar (
    AP_INT_T &copy_back_bitfield
) {
    //ASSERT(copy_back_bitfield & ~CreateNByteMask<sizeof(return_t)>() == 0, "Result container too small to hold input");
    return *(return_t*)&copy_back_bitfield;
}

/* == Compile time ==
 * Given an ap_u?int container type, return that value as a base type (bool point in this case)
 * NOTE: THIS IS NOT A TYPE CAST
template <typename return_t, typename AP_INT_T>
typename std::enable_if<std::is_same<bool,return_t>::value || std::is_same<const bool,return_t>::value, return_t>::type ReadApIntToVar(
    AP_INT_T &copy_back_bitfield)
{
    return copy_back_bitfield;
}*/


/* == Compile time ==
 * Given an ap_u?int container type, return that value as a base type (integral in this case)
 * NOTE: THIS IS NOT A TYPE CAST
 */
template <typename return_t, typename AP_INT_T>
typename std::enable_if<std::is_integral<return_t>::value, return_t>::type
ReadApIntToVar (
    AP_INT_T &copy_back_bitfield
) {
    //ASSERT(copy_back_bitfield & ~(CreateNByteMask<int, sizeof(return_t)>()) == 0, "Result container too small to hold input");
    return copy_back_bitfield;
}

/* == Compile time ==
 * Given an ap_u?int container type, return that value as a base type (aggregate/struct in this case)
 * NOTE: THIS IS NOT A TYPE CAST
 * NOTE: that in newer versions of C++ there is an is_aggregate type trait check that can be used
 *       *AFTER* vivado_hls supports c++ versions higher than c++11. However, at the moment,
 *       vivado_hls only supports up to C++11, so we can't use that type trait
 */
template <typename return_t, typename AP_INT_T>
typename std::enable_if<!std::is_floating_point<return_t>::value && !std::is_integral<return_t>::value && !std::is_same<bool,return_t>::value && !std::is_same<const bool,return_t>::value, return_t>::type 
ReadApIntToVar (
    AP_INT_T &copy_back_bitfield
) {
    //ASSERT(copy_back_bitfield & ~(CreateNByteMask<int, sizeof(return_t)>()) == 0, "Result container too small to hold input");
    return return_t::FromBitfield(copy_back_bitfield);
}

/* == Compile time ==
 * A type deduction where given a stream type, we determine the word type of the 
 * flit/axi written to/read from that stream
 * e.g. the flit type of hls::stream<int> is int. 
 *      the flit type of hls::stream<ap_axiu<32,1,1,1>> is ap_axiu<32,1,1,1>
 * Can be used as a regular type - is useful when the type of the stream
 * is derived from other parameters or it's hidden as another type (makes code more portable)
 * Usage example:
 * using stream_t = hls_stream<some_type>;
 * void func (stream_t &stream_out)
 * hls_stream_flit_t<stream_t> flit = ... ; // << HERE IS ONE USAGE
 *     OR
 * hls_stream_flit_t<decltype(stream_out)> flit_to_stream_out; // << HERE IS ANOTHER USAGE
 */
template <typename HLS_STREAM_T>
using hls_stream_flit_t = decltype(std::declval<HLS_STREAM_T>().read());

/* == Compile time ==
 * Similar to hls_stream_flit_t (above) but will extract the type of the data field from an axi stream flit
 * Where the flit is of type ap_axi/ap_axiu
 * e.x. for ap_axiu<32, 1, 1, 1>, hls_stream_data_t<ap_axiu<32, 1, 1, 1>> will return ap_uint<32>
 * Usage:
 * using flit_t = ap_axiu<32, 1, 1, 1>;
 * ...
 * using stream_t = hls::stream<flit_t>;
 * ...
 * hls_stream_data_t<stream_t> flit_data = ...;  // << HERE IS THE USAGE
 * static_assert(std::is_same<decltype(flit_data), ap_axiu<32, 1, 1, 1>>::value, "Mismatch in data type"); // Will not fail
 * */
template <typename HLS_STREAM_T>
using hls_stream_data_t = decltype(std::declval<HLS_STREAM_T>().read().data);


/* == Compile time ==
 * Given a type, T, get it's size in *bits*
 * Specializations provided for each type below
 */
template <typename T>
struct TYPE_WIDTH_IN_BITS {
    static constexpr int value = T::width;
};
template <> struct TYPE_WIDTH_IN_BITS<uint8_t> { static constexpr int value = sizeof(uint8_t) * 8; };
template <> struct TYPE_WIDTH_IN_BITS<int8_t> { static constexpr int value = sizeof(int8_t) * 8; };
template <> struct TYPE_WIDTH_IN_BITS<uint16_t> { static constexpr int value = sizeof(uint16_t) * 8; };
template <> struct TYPE_WIDTH_IN_BITS<int16_t> { static constexpr int value = sizeof(int16_t) * 8; };
template <> struct TYPE_WIDTH_IN_BITS<uint32_t> { static constexpr int value = sizeof(uint32_t) * 8; };
template <> struct TYPE_WIDTH_IN_BITS<int32_t> { static constexpr int value = sizeof(int32_t) * 8; };
template <> struct TYPE_WIDTH_IN_BITS<uint64_t> { static constexpr int value = sizeof(uint64_t) * 8; };
template <> struct TYPE_WIDTH_IN_BITS<int64_t> { static constexpr int value = sizeof(int64_t) * 8; };
template <> struct TYPE_WIDTH_IN_BITS<float> { static constexpr int value = sizeof(float) * 8; };
template <> struct TYPE_WIDTH_IN_BITS<double> { static constexpr int value = sizeof(double) * 8; };
template <> struct TYPE_WIDTH_IN_BITS<bool> { static constexpr int value = sizeof(bool) * 8; };


/* == Compile time ==
 * Given a type, T, compute its size in *bytes*
 * Specializations provided for each type below
 */
template <typename T>
inline hls_int_t ComputeFieldLengthInBytes (T field) {
    return (T::width / 8);
};
template <> inline hls_int_t ComputeFieldLengthInBytes<uint8_t> (uint8_t field) { return sizeof(uint8_t); };
template <> inline hls_int_t ComputeFieldLengthInBytes<int8_t> (int8_t field) { return sizeof(int8_t); };
template <> inline hls_int_t ComputeFieldLengthInBytes<uint16_t> (uint16_t field) { return sizeof(uint16_t); };
template <> inline hls_int_t ComputeFieldLengthInBytes<int16_t> (int16_t field) { return sizeof(int16_t); };
template <> inline hls_int_t ComputeFieldLengthInBytes<uint32_t> (uint32_t field) { return sizeof(uint32_t); };
template <> inline hls_int_t ComputeFieldLengthInBytes<int32_t> (int32_t field) { return sizeof(int32_t); };
template <> inline hls_int_t ComputeFieldLengthInBytes<uint64_t> (uint64_t field) { return sizeof(uint64_t); };
template <> inline hls_int_t ComputeFieldLengthInBytes<int64_t> (int64_t field) { return sizeof(int64_t); };
template <> inline hls_int_t ComputeFieldLengthInBytes<float> (float field) { return sizeof(float); };
template <> inline hls_int_t ComputeFieldLengthInBytes<double> (double field) { return sizeof(double); };
template <> inline hls_int_t ComputeFieldLengthInBytes<bool> (bool field) { return sizeof(bool); };
//template <> hls_int_t ComputeFieldLengthInBytes<(field_data);


/* Given a stream type, HLS_STREAM_T, get the bit width of the data field
 * Usage example:
 * using stream_t = hls::stream<  ___  >;
 * constexpr int STREAM_DATA_WIDTH = HLS_STREAM_DATA_WIDTH<stream_t>::value; // << HERE IS THE USAGE
 * ap_uint<STREAM_DATA_WIDTH> some_var;
 */
template <typename HLS_STREAM_T>
struct HLS_STREAM_DATA_WIDTH {
    static constexpr int value = decltype(std::declval<HLS_STREAM_T>().read().data)::width;
};

/* Given a type, T, of a word, compute if it will fit within the data field of an hls stream
 * flit.
 * This can be a helpful helper function to build specialized paths for common logic that 
 * may be instantiated across different bus widths
 *  OR
 * This can be a helpful helper function to build specialized paths to make an IP scalable 
 * with bus width without requiring rewrites
 */
template <typename T, typename HLS_STREAM_T>
struct FIELD_BUFFER_FITS_IN_STREAM {
    static constexpr bool value = (T::width <= HLS_STREAM_DATA_WIDTH<HLS_STREAM_T>::value);
};

#endif
