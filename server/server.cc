#include "server.h"

Server::Server(size_t shm_size) {
    boost::interprocess::managed_shared_memory
     start_segment(boost::interprocess::open_or_create, "StartTaskQueue", 25536);
     _start_io_task_queue = start_segment.find_or_construct<RingBufferReq>("start_io_task_queue")();

    boost::interprocess::managed_shared_memory
     fini_segment(boost::interprocess::open_or_create, "FiniTaskQueue", 25536);
     _fini_io_task_queue = start_segment.find_or_construct<RingBufferRsp>("fini_io_task_queue")();

}

/*
Server::Server(std::string start_shm_name, std::string fini_shm_name, size_t shm_size) {
    boost::interprocess::managed_shared_memory
     start_segment(boost::interprocess::open_or_create, start_shm_name, shm_size);
     _start_io_task_queue = start_segment.find_or_construct<RingBufferReq>("start_io_task_queue")();

    boost::interprocess::managed_shared_memory
     fini_segment(boost::interprocess::open_or_create, fini_shm_name, shm_size);
     _fini_io_task_queue = start_segment.find_or_construct<RingBufferRsp>("fini_io_task_queue")();

}
*/

Server::~Server() {
    // how to destroy

}

void Server::Start() {
    _stop = false;
    StartIOTask();
}

void Server::Stop() {
    _stop = true;
}

// TODO: boost bind core api
void Server::StartIOTask() {
    RequestCommand req;
    while (!_stop) {
        if (_start_io_task_queue->pop(req)) {
            // TODO

        }
    }
}

void Server::FinishIOTask(uint32_t cid, Status status) {
    ResponseCommand rsp;
    rsp.cid  = cid;
    rsp.status = status;
    _fini_io_task_queue->push(rsp);
}


