#ifndef ADDON_HPP
#define ADDON_HPP

#include <node.h>
#include <unistd.h>

#include <corbasim/core/reflective_fwd.hpp>
#include <corbasim/core/caller_fwd.hpp>

namespace corbanode 
{

// Some useful typedefs
typedef ::corbasim::core::interface_caller_ptr Caller_ptr;
typedef ::corbasim::core::interface_reflective_base const * InterfaceDescriptor_ptr;
typedef ::corbasim::core::operation_reflective_base const * OperationDescriptor_ptr;
typedef ::corbasim::event::request_ptr Request_ptr;
typedef ::corbasim::event::event_ptr Event_ptr;

class Objref : public node::ObjectWrap 
{
public:
    static void Init(v8::Handle<v8::Object> target);

private:
    Objref();
    ~Objref();

    static v8::Handle<v8::Value> Call(const v8::Arguments &args);

    InterfaceDescriptor_ptr m_interface;
    Caller_ptr m_caller;
};

struct AsyncRequest
{
    Caller_ptr caller_;
    OperationDescriptor_ptr operation_;
    Request_ptr request_;
    v8::Persistent<v8::Function> callback_;
    Event_ptr result_;
};

} // namespace corbanode

#endif /* ADDON_HPP */
