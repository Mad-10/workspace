#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#define LEN 20

typedef struct LargeNUmber{            		//ȷ������
	int8_t digit[LEN + 1];
}LN;

typedef struct Stack{            		//ȷ������
	int8_t data[LEN + 1];
	int8_t *top;
}Stack;

static Stack LNStack;//ȫ�ֱ�������������
LN One;
LN Zero;

static void LNInit(LN *obj);//��ʼ��
static int8_t LNPush (int8_t ch);//ѹջ
static int8_t LNPop (int8_t *ch);//��ջ
void LNScan(LN *des);//����
int LNLength(LN src);//ͳ��λ�����ο����strlen();
void LNPrint (LN *src);//���
LN LNAdd(LN a, LN b);//�ӷ���ģ��������㷽��
LN LNSubtract (const LN a, const LN b);//������ģ��������㷽��
int LNCompare(LN a, LN b);//�����Ƚϣ��ο����strcmp();
LN LNMultiply (LN a, LN b);//�˷���ģ��������㷽��
LN LNPow (LN base, int exp);//�����������㡤������
static LN LNDivide(LN dividend, LN divisor, int8_t flag);//����
LN LNQuotient(LN dividend, LN divisor);//ȡ��
LN LNRemain(LN dividend, LN divisor);//ȡ��


//��ʼ��
static void LNInit(LN *obj) {            		//ȷ������
	memset(LNStack.data, 0, sizeof(LNStack.data));//��ʼ��ջ
	LNStack.top = LNStack.data;
	memset((obj->digit), 0, sizeof(obj->digit));//��ʼ��ָ������
	memset(One.digit, 0, sizeof(One.digit));
	One.digit[LEN - 1] = 1;
	memset(Zero.digit, 0, sizeof(Zero.digit));
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
int LNLength(LN src) {            		//ȷ������
	int8_t *p = src.digit;
	//�����λ
	{
		while(1) {
			if(p - &(src.digit[0]) == LEN) {
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
	return &(src.digit[LEN - 1]) - p + 1;
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

//�����ӷ�
LN LNAdd(LN a, LN b) {            		//ȷ������
	LN result;
	memset(result.digit, 0, sizeof(result.digit));
	int alen = LNLength(a);
	int blen = LNLength(b);
	int len = (alen > blen) ? (alen) : (blen);
	int i = 0;
	int8_t temp = 0;
	for (i = LEN - 1; LEN - 1 - i <= len; i--) {
			temp = a.digit[i] + b.digit[i];
			result.digit[i] += temp % 10;
			if(temp > 9 || result.digit[i] > 9) {
				if(temp > 9) {
					result.digit[i - 1] += temp / 10;
				}
				if(result.digit[i] > 9) {
					result.digit[i - 1] += result.digit[i] / 10;
					result.digit[i] = result.digit[i] % 10;
				}
			}
	}
	return result;
}

//��������
LN LNSubtract (const LN a, const LN b) {            		//ȷ������
	LN result;
	memset(result.digit, 0, sizeof(result.digit));

	int alen = LNLength(a);
	int blen = LNLength(b);

	int len = (alen > blen) ? (alen) : (blen);

	int i = 0;
	int8_t temp = 0;
	for (i = LEN - 1 - len;i <= LEN - 1; i++) {
			temp = a.digit[i] - b.digit[i];

			if (temp * result.digit[i - 1] < 0) {
				if (temp < 0) {
					result.digit[i - 1] -= 1;
					temp += 10;
				} else {
					result.digit[i - 1] += 1;
					temp -= 10;
				}
			}
			result.digit[i] += temp;
	}
	return result;

}

//�����Ƚ�
int LNCompare(LN a, LN b) {
	int alen = LNLength(a);
	int blen = LNLength(b);
	int len = (alen > blen) ? (alen) : (blen);
	int flag = 0;
	int i = 0;
	for (i = LEN - 1 - len; i <= LEN - 1; i++) {
		flag = a.digit[i] - b.digit[i];
		if(flag != 0) {
			return flag;
		}
	}
	return flag;
}

//�����˷�
LN LNMultiply (LN a, LN b) {            		//ȷ������
	LN result;
	memset(result.digit, 0, sizeof(result.digit));
	LN sum;
	memset(sum.digit, 0, sizeof(sum.digit));
	int alen = LNLength(a);//a��λ��
	int blen = LNLength(b);//b��λ��
	if (alen + blen > LEN) {
		printf("������λ��֮��%d����%d, ��˻����ܻᳬ����Χ�����������ݴ���\n��������λ�����������С������\n", alen + blen, LEN);
		exit(1);
	}
	int i = 0;
	int j = 0;
	int k = 0;
	int8_t temp = 0;
	for (i = LEN - 1; k < blen; i--) {
		for (j = LEN - 1; LEN - 1 - j < alen; j--) {
			temp = b.digit[i] * a.digit[j];
			sum.digit[j - k] += temp % 10;
			sum.digit[j - k - 1] += temp /10;
		}
		k++;
		result = LNAdd(result, sum);
		memset(sum.digit, 0, sizeof(sum.digit));
	}
	return result;
}

LN LNPow (LN base, int exp) {            		//ȷ������
	LN result;
	memset(result.digit, 0, sizeof(result.digit));
	if (exp <= 0) {
		result.digit[LEN - 1] = 1;
		return result;
	} else if (exp & 1){
		exp--;
		return result = LNMultiply(base, LNPow(base, exp));
	} else {
		exp >>= 1;
		result = LNPow(base, exp);
		return result = LNMultiply(result, result);
	}

}

//��������
static LN LNDivide(LN dividend, LN divisor, int8_t flag) {
	LN remain;
	memset(remain.digit, 0, sizeof(remain.digit));
	remain = LNAdd(remain, dividend);

	LN quotient;
	memset(quotient.digit, 0, sizeof(quotient.digit));
	{
		for (; LNCompare(remain, divisor) >= 0; ) {
			int len1 = LNLength(dividend);
			int len2 = LNLength(divisor);
			quotient = LNAdd(quotient, One);
			remain = LNSubtract(dividend, LNMultiply(divisor, quotient));
		}
	}
	if(flag == 0) {
		return quotient;
	} else {
		return remain;
	}
}


LN LNQuotient(LN dividend, LN divisor) {
	return LNDivide(dividend, divisor, 0);
}

LN LNRemain(LN dividend, LN divisor) {
	return LNDivide(dividend, divisor, 1);
}

int main(void) {
	LNInit(&Zero);

	LN a;
	memset(a.digit, 0, sizeof(a.digit));
    LNScan(&a);
	LN b;
	memset(b.digit, 0, sizeof(b.digit));
    LNScan(&b);
//	a.digit[LEN - 2] = 9;
//	a.digit[LEN - 1] = 8;
//	b.digit[LEN - 1] = 2;
//	int i = 0;
//	for (i = 0; i < 100; i++) {
//		a = LNSubtract(a, b);
//		printf("i = ");
//		LNPrint(&a);
//		putchar('\n');
//	}

//	int exp;
//	scanf("%d", &exp);
	LN c;
	c = LNQuotient(a, b);
	LNPrint(&c);
	putchar('\n');
	c = LNRemain(a, b);
	LNPrint(&c);
	return 0;
}

/*
���Ż���
1��Ŀǰδ�������븺����
2:��ȡ�����������õ�ջ��
3:����λ�����㺯�������Ż�
4:�����㷨�д��Ż�
*/
