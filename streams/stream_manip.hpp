#ifndef STREAM_MANIP_HPP
#define STREAM_MANIP_HPP

#include <tuple>
#include <cstdint>

/* THERE ARE TWO IMPLEMENTATIONS AND SUPPORTED USES FOR THIS METHOD
 * This is intended for use within HLS dataflow designs, not as a standalone IP 
 * Broadcasts the input stream data to all output streams concurrently
 * Really only useful when  called in a design with 
 * #pragma HLS DATAFLOW
 *       or
 * #pragma HLS DATAFLOW DISABLE_START_PROPAGATION
 * Just call this similar to one of the examples below, STREAM_T and N are automatically inferred
 * ____ THIS IMPLEMENTATION _____
 * using flit_t = ...;
 * using stream_t = hls::stream<flit_t>;
 * stream_t s_axis;
 * stream_t m_axis[5];
 * axis_broadcaster(s_axis, m_axis); // << THIS USE, STREAM_T and N are inferred
 * 
 * ___ NEXT IMPLEMENTATION
 * using flit_t = ...;
 * using stream_t = hls::stream<flit_t>;
 * stream_t s_axis;
 * stream_t m_axis1;
 * stream_t m_axis2;
 * axis_broadcaster(s_axis, m_axis1, m_axis2); // << THIS USE, STREAM_T and N are inferred.
 */
template <int N, typename STREAM_T>
void axis_broadcaster (STREAM_T &s_axis, STREAM_T (&m_axis)[N]) 
{
    #pragma HLS INTERFACE ap_ctrl_none PORT=return 
    #pragma HLS PIPELINE II=1
    #pragma HLS INLINE OFF
    #pragma HLS ARRAY_PARTITION VARIABLE=m_axis
    
    auto flit_in = s_axis.read();
    for (int i = 0; i < N; i++) {
        #pragma HLS UNROLL
        m_axis[i].write(flit_in);
    }
}


/* Variadic template helper for axis_broadcaster below
 */
template <typename T, typename FIRST_STREAM_T>
void broadcast_flit_over_axis (const T &flit, FIRST_STREAM_T &this_stream)
{
    this_stream.write(flit);
}

/* Variadic template helper for axis_broadcaster below
 */
template <typename T, typename FIRST_STREAM_T, typename ... REST_STREAM_T>
void broadcast_flit_over_axis (const T &flit, FIRST_STREAM_T &this_stream, REST_STREAM_T &...other_streams)
{
    #pragma HLS INLINE RECURSIVE
    this_stream.write(flit);
    broadcast_flit_over_axis(flit, other_streams...);
}

/* This is one of two implementations (there are two supported calling conventions)
 * This is intended for use within HLS dataflow designs, not as a standalone IP 
 * Broadcasts the input stream data to all output streams concurrently
 * Really only useful when  called in a design with 
 * #pragma HLS DATAFLOW
 *       or
 * #pragma HLS DATAFLOW DISABLE_START_PROPAGATION
 * Just call this similar to one of the examples below, I_STREAM_T and O_STREAM_T are automatically inferred
 * using flit_t = ...;
 * using stream_t = hls::stream<flit_t>;
 * stream_t s_axis;
 * stream_t m_axis1;
 * stream_t m_axis2;
 * axis_broadcaster(s_axis, m_axis1, m_axis2); // << THIS USE, STREAM_T and N are inferred.
 */
template <typename I_STREAM_T, typename ... O_STREAM_T>
void axis_broadcaster (I_STREAM_T &s_axis, O_STREAM_T &...output_streams) 
{
    #pragma HLS INTERFACE ap_ctrl_none PORT=return 
    #pragma HLS PIPELINE II=1
    #pragma HLS INLINE OFF
    #pragma HLS INLINE RECURSIVE
    
    auto flit_in = s_axis.read();
    broadcast_flit_over_axis (flit_in, output_streams...);
}

#endif