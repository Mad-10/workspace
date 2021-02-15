#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#define LEN 10

typedef struct LargeNUmber{            		//ȷ������
	int8_t digit[LEN + 1];
}LN;

typedef struct Stack{            		//ȷ������
	int8_t data[LEN + 1];
	int8_t *top;
}Stack;

static Stack LNStack;

//��ʼ��
static void LNInit(LN *obj) {            		//ȷ������
	memset(LNStack.data, 0, sizeof(LNStack.data));//��ʼ��ջ
	LNStack.top = LNStack.data;
	memset((obj->digit), 0, sizeof(obj->digit));//��ʼ��ָ������
}

//ѹջ
static int8_t LNPush (int8_t ch) {            		//ȷ������
	*(LNStack.top) = ch - '0';
	LNStack.top++;//ջ��ָ��ָ����һ��Ҫ����Ԫ�ص�λ��
	if (LNStack.top - LNStack.data == LEN) {//���һ��λ��
		return -1;
	} else {
		return ch;
	}
}

//��ջ
static int8_t LNPop (int8_t *ch) {            		//ȷ������
	if(LNStack.top == LNStack.data) {//ֻʣһ��Ԫ��
		*ch = *(LNStack.top);//�������ƣ�ָ��ջ��
		return -1;
	} else {//��������Ԫ��
		*ch = *(LNStack.top);
		LNStack.top--;
		return *ch;
	}
}

//����
void LNScan(LN *des) {            		//ȷ������
	LNInit(des);//��ʼ��
	
	//����������ջ
	{
		int8_t ch;
		while((ch = getchar()) < '0' || ch > '9');
		if (ch >= '0' && ch <= '9') {
			LNPush(ch);
		}
		
		while(1) {
			if ((ch = getchar()) < '0' || ch > '9') {
				break;
			}
			if (LNPush(ch) == -1) {//if(LNPush(ch) != ch) {
				//printf("����λ������Ŀǰ֧�ֵ�λ��Ϊ��%d;\n������������������λ����ò�������%d\n", LEN, LEN - 1);
				break;
				//exit(1);
			}
		}
		LNStack.top--;//��֤ѹջ������ջ��ָ��ָ����ЧԪ��
	}
	
	//��ջת�Ƶ�ָ������
	{
		int8_t *p = &(des->digit[LEN - 1]);
		while(1) {
			if(LNPop(p) == -1){
				break;
			} else if (p == des->digit) {
				break;
			} else {
				p--;
			}
		}
	}
	
}

//ͳ��λ��
int LNLength(LN *src) {            		//ȷ������
	int8_t *p = &(src->digit[0]);
	//�����λ
	{
		while(1) {
			if(p - &(src->digit[0]) == LEN) {
				//p++;
				break;
			}
			if(*p == 0) {
				p++;
			} else {
				break;
			}
		}
	}
	//ƫ����֮��
	return &(src->digit[LEN - 1]) - p + 1;
}

//���
void LNPrint (LN *src) {            		//ȷ������
	int8_t *p = &(src->digit[0]);
	//�����λ
	{
		while(1) {
			if(p - &(src->digit[0]) == LEN - 1) {
				break;
			}
			if(*p == 0) {
				p++;
			} else {
				break;
			}
		}
	}
	//ѭ�����
	//�������һλ���з��ţ�
	printf("%"PRId8, *p);
	
	if(p - &(src->digit[0]) == LEN - 1) {//�����ǰ�����һλ���˳�
		return;
	} else {
		p++;
	}
	while(1){
		if(p - &(src->digit[0]) == LEN) {//�����ǰ�����һλ���˳�
			break;
		} else {
			printf("%"PRId8, abs((int)(*p)));
			p++;
		}
		
		
	}
	
}

int main(void) {
	LN a;
	memset(a.digit, 0, sizeof(a.digit));
	LNScan(&a);
	
	
	return 0;
}
