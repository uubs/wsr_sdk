#ifndef _SERVER_H_
#define _SERVER_H_

#include <boost/lockfree/spsc_queue.hpp> // ring buffer
#include <boost/interprocess/managed_shared_memory.hpp>
#include <string>
#include "../command/command.h"

// reference https://gist.github.com/19317362/29288bbbf6a7f031b2bbd5873267c919#file-consumer-cpp-L21

// TODO: no mutex, no atomic

typedef boost::lockfree::spsc_queue<RequestCommand,boost::lockfree::capacity<sizeof(RequestCommand)>> RingBufferReq;
typedef boost::lockfree::spsc_queue<ResponseCommand, boost::lockfree::capacity<sizeof(ResponseCommand)>> RingBufferRsp;
class Server {
public:
    // Server(std::string start_shm_name, std::string fini_shm_name, size_t shm_size);
    Server(size_t shm_size);
    ~Server();

    void Start();
    void Stop();
    void StartIOTask();
    void FinishIOTask(uint32_t cid, Status status);
private:
    RingBufferReq *_start_io_task_queue;
    RingBufferRsp *_fini_io_task_queue;
    bool _stop;
};

#endif