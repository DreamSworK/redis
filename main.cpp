#include <queue>
#include <chrono>
#include <iostream>
#include <hiredis.h>

#define SIZE 20000

void PipeCommand(const int items, redisContext *context) {

    redisReply *reply;

    for (int i = 0; i < items; ++i) {
        redisAppendCommand(context, "RPUSH %s %i", "list", 0);
    }

    for (int i = 0; i < items; ++i) {
        redisGetReply(context, (void **) &reply);
        freeReplyObject(reply);
    }
}

void SyncCommand(const int items, redisContext *context) {
    for (int i = 0; i < items; ++i) {
        auto *reply = (redisReply *) redisCommand(context, "RPUSH %s %i", "list", 0);
        freeReplyObject(reply);
    }
}

void clean(redisContext *context) {
    if (context != nullptr) {
        auto reply = (redisReply *) redisCommand(context, "FLUSHDB");
        freeReplyObject(reply);
        printf("Redis DB has been cleaned!\n");
    }
}

#define PERFORMANCE(func) do { \
auto start = std::chrono::steady_clock::now(); func; auto end = std::chrono::steady_clock::now(); \
auto duration = (std::chrono::duration_cast<std::chrono::milliseconds>(end - start)).count(); \
std::string file = __FILE__; printf("(%s) %s[%d]: %lli ms\n", __func__, file.substr(file.find_last_of('/') + 1).c_str(), __LINE__, duration); \
} while(0);

int main() {

    const int items = SIZE;

    struct timeval timeout = {1, 500000};
    redisContext *context = redisConnectWithTimeout("127.0.0.1", 6379, timeout);

    clean(context);

    PERFORMANCE(PipeCommand(items, context))
    PERFORMANCE(SyncCommand(items, context))

    return 0;
}