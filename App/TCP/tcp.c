#include "tcp.h"

// ����ȫ�ֱ�������ʾ��ǰ�Ľ�ɫ
uint8_t role;

// �����Ҫ���ӵķ�����IP�Ͷ˿ں�
uint8_t serverIP[]  = {192, 168, 34, 36};
uint16_t serverPort = 8888;

// ����TCP�ͻ��ˣ��ŵ���ѭ����ִ�У�ֻ�н������ӳɹ��ŷ���OK
CommonStatus TCP_ClientStart(void)
{
    //��ǰΪ�ͻ���
    role = CLIENT;

    // 1. ��ȡ��ǰsocket��״̬
    uint8_t status = getSn_SR(SN);

    // 2. ����״̬����Ҫִ�е�����
    if (status == SOCK_CLOSED) {
        // ��socket�������Э��TCP���˿�9999�����ݷ���ֵ�Ƿ���socket���ж��Ƿ�ɹ�
        uint8_t n = socket(SN, Sn_MR_TCP, 8888, SF_TCP_NODELAY);

        if (n == SN) {
            printf("socket %d �򿪳ɹ���\n", SN);
        } else {
            printf("socket %d ��ʧ�ܣ�\n", SN);
        }
    } else if (status == SOCK_INIT) {
        // ���ڿͻ��ˣ�ִ��connect������ӷ�����
        uint8_t res = connect(SN, serverIP, serverPort);
        if (res == SOCK_OK) {
            printf("�ͻ������ӷ������ɹ���\n");
        } else {
            printf("�ͻ������ӷ�����ʧ�ܣ�\n");
        }
    } else if (status == SOCK_CLOSE_WAIT) {
        printf("ʧȥ�����˵�����,�������´�socket...\n");
        // �ͻ��˶Ͽ����ӣ�ֱ�ӹرգ�֮�������´򿪣�
        close(SN);
    } else if (status == SOCK_ESTABLISHED) {
        printf("�ͻ��˱�������\n");
        return COMMON_OK;
    }

    return COMMON_ERROR;
}

void TCP_SendData(uint8_t data[], uint16_t len)
{
    if (len == 0) {
        return;
    }

    // ��ѭ����ͣ���� ClientStart��ֱ����������
    while (TCP_ClientStart() == COMMON_ERROR) {
        HAL_Delay(100);
    }

    // 1. ��ȡ��ǰsocket��״̬
    uint8_t status = getSn_SR(SN);

    // 2. ����������״̬�ſ��Է�������
    if (status == SOCK_ESTABLISHED) {
        // ����send������������
        send(SN, data, len);
    }
}
