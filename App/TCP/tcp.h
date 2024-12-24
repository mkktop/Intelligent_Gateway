//��ģ��ΪTCP�ͻ��˳���
#ifndef __TCP_H__
#define __TCP_H__

#include "eth.h"
#include "socket.h"
#include "Com_Types.h"

// �궨��
// ʹ��socket�ı��
#define SN 0
// ��ǰ�Ľ�ɫ
#define CLIENT 0
#define SERVER 1

// ����TCP�ͻ���
CommonStatus TCP_ClientStart(void);

// ��TCP��ʽ�շ�����
void TCP_SendData(uint8_t data[], uint16_t len);

#endif /* __TCP_H__ */