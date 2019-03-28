#ifndef ASSERT_HPP
#define ASSERT_HPP

#include <cassert>

#ifdef __RTL_SIMULATION__
#define RTL_SIMULATION_DEFINED 1
#else
#define RTL_SIMULATION_DEFINED 0
#endif
#ifdef __SYNTHESIS__
#define SYNTHESIS_DEFINED 1
#else
#define SYNTHESIS_DEFINED 0
#endif
#ifdef DEBUG
#include <iostream>
#define DEBUG_DEFINED 1
#else
#define DEBUG_DEFINED 0
#endif

//#if (defined __RTL_SIMULATION__ || defined DEBUG) && !defined __SYNTHESIS__
#if (RTL_SIMULATION_DEFINED || DEBUG_DEFINED) && (SYNTHESIS_DEFINED == 0)
  #define ASSERT(condition, message)\
    if (!(condition)) {\
        std::cout << "ASSERTION in " << __FILE__ << " at line " << __LINE__ << ": ";\
        std::cout << message << std::endl;\
        assert(false);\
    }

  #define ASSERT_IF(condition_when_to_check_assertion,assertion_condition,message)\
    if ((condition_when_to_check_assertion)) {\
      if (!(assertion_condition)) {\
        std::cout << "ASSERTION in " << __FILE__ << " at line " << __LINE__ << ": ";\
        std::cout << message << std::endl;\
        assert(false);\
      }\
    }

  #define UNIMPLEMENTED() \
    std::cout << "UNIMPLEMENTED FUNCTION at line " << __LINE__ << " in file " << __FILE__ << std::endl;\
    assert(false);

  #define UNIMPLEMENTED_QUIET(message) \
    std::cout << "UNIMPLEMENTED FUNCTION at line " << __LINE__ << " in file " << __FILE__ << std::endl;\
    std::cout << "\t" << message << std::endl;

  #define INFO(message) \
    std::cout << message << std::endl;
#else // DEBUG
 #if defined(__clang__)
 #define ASSERT(condition, message) \
    DO_PRAGMA(clang diagnostic ignored "-Wunused-comparison")\
    DO_PRAGMA(clang diagnostic ignored "-Wunused-value")\
    condition;
 #else 
  #if defined(__GNUC__) || defined(__GNUG__)
   #define ASSERT(condition, message) \
    condition;
  #endif
 #endif
  #define DO_PRAGMA_INNER(x) _Pragma (#x)
  #define DO_PRAGMA(x) DO_PRAGMA_INNER(x)
  #define ASSERT_IF(condition_when_to_check_assertion,assertion_condition,message) {}

  #define INFO(message) {}
  #define UNIMPLEMENTED() {}
  #define UNIMPLEMENTED_QUIET(messsage) {}
#endif // DEBUG

#endif