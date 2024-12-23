#include "tcp.h"

// 定义全局变量，表示当前的角色
uint8_t role;

// 定义好要连接的服务器IP和端口号
uint8_t serverIP[]  = {192, 168, 34, 36};
uint16_t serverPort = 8888;

// 启动TCP客户端，放到主循环里执行，只有建立连接成功才返回OK
CommonStatus TCP_ClientStart(void)
{
    //当前为客户端
    role = CLIENT;

    // 1. 获取当前socket的状态
    uint8_t status = getSn_SR(SN);

    // 2. 根据状态决定要执行的命令
    if (status == SOCK_CLOSED) {
        // 打开socket，定义好协议TCP，端口9999，根据返回值是否是socket号判断是否成功
        uint8_t n = socket(SN, Sn_MR_TCP, 8888, SF_TCP_NODELAY);

        if (n == SN) {
            printf("socket %d 打开成功！\n", SN);
        } else {
            printf("socket %d 打开失败！\n", SN);
        }
    } else if (status == SOCK_INIT) {
        // 对于客户端，执行connect命令，连接服务器
        uint8_t res = connect(SN, serverIP, serverPort);
        if (res == SOCK_OK) {
            printf("客户端连接服务器成功！\n");
        } else {
            printf("客户端连接服务器失败！\n");
        }
    } else if (status == SOCK_CLOSE_WAIT) {
        printf("失去与服务端的连接,即将重新打开socket...\n");
        // 客户端断开连接，直接关闭（之后再重新打开）
        close(SN);
    } else if (status == SOCK_ESTABLISHED) {
        printf("客户端保持连接\n");
        return COMMON_OK;
    }

    return COMMON_ERROR;
}

void TCP_SendData(uint8_t data[], uint16_t len)
{
    if (len == 0) {
        return;
    }

    // 用循环不停调用 ClientStart，直到建立连接
    while (TCP_ClientStart() == COMMON_ERROR) {
        HAL_Delay(100);
    }

    // 1. 获取当前socket的状态
    uint8_t status = getSn_SR(SN);

    // 2. 必须是连接状态才可以发送数据
    if (status == SOCK_ESTABLISHED) {
        // 调用send函数发送数据
        send(SN, data, len);
    }
}
