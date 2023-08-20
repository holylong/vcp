/*
 * @Author: holylong mrhlingchen@163.com
 * @Date: 2023-08-03 16:10:56
 * @LastEditors: holylong mrhlingchen@163.com
 * @LastEditTime: 2023-08-03 16:11:25
 * @FilePath: \vcp\network\reactor\Reactor.cc
 */
// Reactor.cpp
#include "Reactor.h"
#include <stdio.h>

Reactor::Reactor() {
    max_fd = -1;
    FD_ZERO(&read_set);
    FD_ZERO(&write_set);
}

Reactor::~Reactor() {
    for (auto& pair : handlers) {
        delete pair.second;
    }
}

void Reactor::register_handler(EventHandler* handler) {
    int fd = handler->get_handle();
    if (fd > max_fd) {
        max_fd = fd;
    }
    FD_SET(fd, &read_set);
    FD_SET(fd, &write_set);
    handlers[fd] = handler;
}

void Reactor::remove_handler(EventHandler* handler) {
    int fd = handler->get_handle();
    FD_CLR(fd, &read_set);
    FD_CLR(fd, &write_set);
    handlers.erase(fd);
}

void Reactor::handle_events() {
    while (true) {
        fd_set read_fds = read_set;
        fd_set write_fds = write_set;
        int n = select(max_fd + 1, &read_fds, &write_fds, NULL, NULL);
        if (n < 0) {
            perror("select error");
            break;
        }
        for (int i = 0; i <= max_fd; i++) {
            if (FD_ISSET(i, &read_fds)) {
                handlers[i]->handle_read();
            }
            if (FD_ISSET(i, &write_fds)) {
                handlers[i]->handle_write();
            }
        }
    }
}