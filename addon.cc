#include "addon.hpp"

namespace corbanode
{
    v8::Handle<v8::Value> LoadDirectory(const v8::Arguments& args) 
    {
        v8::HandleScope scope;
        // TODO
        return scope.Close(v8::Undefined());
    }

    v8::Handle<v8::Value> CreateObject(const v8::Arguments& args) 
    {
        v8::HandleScope scope;
        // TODO
        return scope.Close(v8::Undefined());
    }

    void Init(v8::Handle<v8::Object> target) 
    {
        target->Set(v8::String::NewSymbol("loadDirectory"),
                v8::FunctionTemplate::New(LoadDirectory)->GetFunction());
        target->Set(v8::String::NewSymbol("createObject"),
                v8::FunctionTemplate::New(CreateObject)->GetFunction());
    }
    
    NODE_MODULE(corbanode, Init);
} // namespace corbanode

