#pragma once

#include <memory>
#include <string>

#include "file_util.h"
#include "noncopyable.h"
#include "mutexlock.h"

// LogFile 负责文件写入

class LogFile : private NonCopyable
{
public:
    // 每被append flushEveryN次，flush一下，会往文件写，只不过，文件也是带缓冲区的
    LogFile(const std::string& basename, int flushEveryN = 1024);
    ~LogFile();

    void append(const char* logline, int len);

    void flush();

private:
    void append_unlocked(const char* logline, int len);

    const std::string basename_;
    const int flushEveryN_;

    int count_;
    std::unique_ptr<MutexLock> mutex_;
    std::unique_ptr<AppendFile> file_;

};