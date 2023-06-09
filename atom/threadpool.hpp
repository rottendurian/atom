#pragma once

#ifndef _ATOM_POOL_HPP
#define _ATOM_POOL_HPP

namespace atom {

class pool {
public:
    pool();
    pool(uint32_t thread_count);
    ~pool();

    void add_task(std::function<void()> task);
    void wait_for_tasks();
    int get_threads_working();
    bool has_tasks();
    void empty();

private:
    void spawn_threads(uint32_t count);
    void join_threads();
    void wait_for_task();

    bool _stop_requested = false;
    std::atomic<int> threads_working;
    std::mutex queue_mutex;
    std::condition_variable queue_cond;
    std::queue<std::function<void()>> queue;
    std::vector<std::thread> threads;
};


} // namespace stp

#endif // __STP_POOL_HPP


