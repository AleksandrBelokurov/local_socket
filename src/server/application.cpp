#include "application.h"

Application::Application(char*& filename)
{
    logFileName_.append(filename);
    logFileName_ = logFileName_ + ".log";
    log_ = new Logging(logFileName_);
}

int Application::init()
{
    listener_ = socket(AF_UNIX, SOCK_STREAM, 0);
    if(listener_ < 0) {
        *log_ << "error socket create";
        return 1;
    }
    fcntl(listener_, F_SETFL, O_NONBLOCK);
    addr_.sun_family = AF_UNIX;
    strcpy(addr_.sun_path, sock_path_.c_str());
    unlink(addr_.sun_path);
    if(bind(listener_, (struct sockaddr *)&addr_, sizeof(addr_)) < 0) {
        *log_ << "error bind socket";
        return 2;
    }
    listen(listener_, 2);
    clients_.clear();
    for (auto sch : channelNames_) {
        channels_.insert(std::pair<string, Channel*>(sch, new Channel()));
    }
    msgcodec_ = new Messagecodec(&channels_);
    return 0;
}

int Application::run()
{
    while(1) {
        fd_set readset;
        FD_ZERO(&readset);
        FD_SET(listener_, &readset);
        for (auto id : clients_)
            FD_SET(id, &readset);
        timeval timeout;
        timeout.tv_sec = 45;
        timeout.tv_usec = 0;
        int mx = max(listener_, *max_element(clients_.begin(), clients_.end()));
        if(select(mx+1, &readset, NULL, NULL, &timeout) <= 0) {
            *log_ << "error select";
            return 3;
        }
        if(FD_ISSET(listener_, &readset)) {
            int sock = accept(listener_, NULL, NULL);
            if(sock < 0) {
                *log_ << "error accept";
                return 3;
            }
            fcntl(sock, F_SETFL, O_NONBLOCK);
            clients_.insert(sock);
            *log_ << "register client id = " +  to_string(sock);
        }
        for(auto id : clients_) {
            if(FD_ISSET(id, &readset)) {
                bytes_read_ = recv(id, buf, 1024, 0);
                if(bytes_read_ <= 0) {
                    close(id);
                    clients_.erase(id);
                    *log_ << "unregister client id = " + to_string(id);
                    break;
                }
            string reqest = string(buf , bytes_read_);
            *log_ << "client id = " + to_string(id) + ", resqest: " + reqest;
            string answer = msgcodec_->decode(reqest);
            send(id, answer.c_str(), answer.length(), 0);
            *log_ << "client id = " + to_string(id) + ", answer: " + answer;
            }
        }
    }
    *log_ << "server exit(0)";
    return 0;
}
