/* Auto-generated by genmsg_cpp for file /home/dave/ros/clam/clam_block_manipulation/msg/InteractiveBlockManipulationFeedback.msg */
#ifndef CLAM_BLOCK_MANIPULATION_MESSAGE_INTERACTIVEBLOCKMANIPULATIONFEEDBACK_H
#define CLAM_BLOCK_MANIPULATION_MESSAGE_INTERACTIVEBLOCKMANIPULATIONFEEDBACK_H
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include "ros/serialization.h"
#include "ros/builtin_message_traits.h"
#include "ros/message_operations.h"
#include "ros/time.h"

#include "ros/macros.h"

#include "ros/assert.h"


namespace clam_block_manipulation
{
template <class ContainerAllocator>
struct InteractiveBlockManipulationFeedback_ {
  typedef InteractiveBlockManipulationFeedback_<ContainerAllocator> Type;

  InteractiveBlockManipulationFeedback_()
  {
  }

  InteractiveBlockManipulationFeedback_(const ContainerAllocator& _alloc)
  {
  }


  typedef boost::shared_ptr< ::clam_block_manipulation::InteractiveBlockManipulationFeedback_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::clam_block_manipulation::InteractiveBlockManipulationFeedback_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct InteractiveBlockManipulationFeedback
typedef  ::clam_block_manipulation::InteractiveBlockManipulationFeedback_<std::allocator<void> > InteractiveBlockManipulationFeedback;

typedef boost::shared_ptr< ::clam_block_manipulation::InteractiveBlockManipulationFeedback> InteractiveBlockManipulationFeedbackPtr;
typedef boost::shared_ptr< ::clam_block_manipulation::InteractiveBlockManipulationFeedback const> InteractiveBlockManipulationFeedbackConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::clam_block_manipulation::InteractiveBlockManipulationFeedback_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::clam_block_manipulation::InteractiveBlockManipulationFeedback_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace clam_block_manipulation

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::clam_block_manipulation::InteractiveBlockManipulationFeedback_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::clam_block_manipulation::InteractiveBlockManipulationFeedback_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::clam_block_manipulation::InteractiveBlockManipulationFeedback_<ContainerAllocator> > {
  static const char* value() 
  {
    return "d41d8cd98f00b204e9800998ecf8427e";
  }

  static const char* value(const  ::clam_block_manipulation::InteractiveBlockManipulationFeedback_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0xd41d8cd98f00b204ULL;
  static const uint64_t static_value2 = 0xe9800998ecf8427eULL;
};

template<class ContainerAllocator>
struct DataType< ::clam_block_manipulation::InteractiveBlockManipulationFeedback_<ContainerAllocator> > {
  static const char* value() 
  {
    return "clam_block_manipulation/InteractiveBlockManipulationFeedback";
  }

  static const char* value(const  ::clam_block_manipulation::InteractiveBlockManipulationFeedback_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::clam_block_manipulation::InteractiveBlockManipulationFeedback_<ContainerAllocator> > {
  static const char* value() 
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
#feedback\n\
\n\
\n\
";
  }

  static const char* value(const  ::clam_block_manipulation::InteractiveBlockManipulationFeedback_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct IsFixedSize< ::clam_block_manipulation::InteractiveBlockManipulationFeedback_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::clam_block_manipulation::InteractiveBlockManipulationFeedback_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct InteractiveBlockManipulationFeedback_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::clam_block_manipulation::InteractiveBlockManipulationFeedback_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::clam_block_manipulation::InteractiveBlockManipulationFeedback_<ContainerAllocator> & v) 
  {
  }
};


} // namespace message_operations
} // namespace ros

#endif // CLAM_BLOCK_MANIPULATION_MESSAGE_INTERACTIVEBLOCKMANIPULATIONFEEDBACK_H

