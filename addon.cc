#include "addon.hpp"

namespace corbanode
{
    void Objref::Init(v8::Handle<v8::Object> target)
    {
        // Nothing to do yet
    }
      
    void DoCallTask (uv_work_t *req) 
    {
        AsyncRequest * k = static_cast<AsyncRequest *> (req->data);
        k->result_ = Event_ptr (k->caller_->do_call(k->request_.get()));
    }

    void FinishCallTask (uv_work_t *req) 
    {
        v8::HandleScope scope;

        AsyncRequest * a = static_cast<AsyncRequest *> (req->data);

        v8::Handle<v8::Value> argv[2];
        // TODO fill arguments argv[0] = v8::Integer::New (a->res_);

        v8::TryCatch try_catch;
        a->callback_->Call(v8::Context::GetCurrent()->Global(), 1, argv);

        // cleanup
        a->callback_.Dispose();
        delete a;
        delete req;

        if (try_catch.HasCaught())
            node::FatalException(try_catch);
    }

    v8::Handle<v8::Value> Objref::Call(const v8::Arguments &args)
    {
        using namespace v8;
        HandleScope scope;

        if (args.Length() < 1) 
            return ThrowException(Exception::TypeError(
                        String::New("First argument must be the operation name")));

        Objref * this_ = node::ObjectWrap::Unwrap<Objref>(args.This());

        Local<String> str = args[0]->ToString();
        const v8::String::AsciiValue opName(str);

        std::auto_ptr<AsyncRequest> data(new AsyncRequest());

        // We can do this because we won't be able to change 
        // the caller's reference or we will do it creating a
        // new caller instance.
        data->caller_ = this_->m_caller;

        // Search the operation descriptor by the operation name
        data->operation_ = 
            this_->m_interface->get_reflective_by_name(*opName);

        if (!data->operation_)
            return ThrowException(Exception::TypeError(
                        String::New("Invalid operation name")));

        data->request_ = data->operation_->create_request();

        // Second argument must be an object with the request value
        if (args.Length() > 1)
        {
            // TODO fill 'request' with 'args[1]'
        }
        
        // Thrid argumente must be a callback
        if (args.Length() > 2)
        {
            data->callback_ = 
                v8::Persistent<v8::Function>::New(
                        v8::Local<v8::Function>::Cast(args[2]));
        }

        // asynchronous call
        uv_work_t *req = new uv_work_t;
        req->data = data.release();
        uv_queue_work(uv_default_loop(), req, DoCallTask, FinishCallTask);

        return scope.Close(Undefined());
    }

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

        Objref::Init(target);
    }
    
    NODE_MODULE(corbanode, Init);
} // namespace corbanode

