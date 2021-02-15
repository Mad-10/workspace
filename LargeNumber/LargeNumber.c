#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#define LEN 20

typedef struct LargeNUmber{            		//确认无误
	int8_t digit[LEN + 1];
}LN;

typedef struct Stack{            		//确认无误
	int8_t data[LEN + 1];
	int8_t *top;
}Stack;

static Stack LNStack;

//初始化
static void LNInit(LN *obj) {            		//确认无误
	memset(LNStack.data, 0, sizeof(LNStack.data));//初始化栈
	LNStack.top = LNStack.data;
	memset((obj->digit), 0, sizeof(obj->digit));//初始化指定对象
}

//压栈
static int8_t LNPush (int8_t ch) {            		//确认无误
	*(LNStack.top) = ch - '0';
	LNStack.top++;//栈顶指针指向下一个要储存元素的位置
	if (LNStack.top - LNStack.data == LEN) {//最后一个位置
		return -1;
	} else {
		return ch;
	}
}

//出栈
static int8_t LNPop (int8_t *ch) {            		//确认无误
	if(LNStack.top == LNStack.data) {//只剩一个元素
		*ch = *(LNStack.top);//不再下移，指向栈底
		return -1;
	} else {//至少两个元素
		*ch = *(LNStack.top);
		LNStack.top--;
		return *ch;
	}
}

//输入
void LNScan(LN *des) {            		//确认无误
	LNInit(des);//初始化

	//输入数据入栈
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
				//printf("数据位数过大，目前支持的位数为：%d;\n保险起见，输入的数据位数最好不超过：%d\n", LEN, LEN - 1);
				break;
				//exit(1);
			}
		}
		LNStack.top--;//保证压栈结束后栈顶指针指向有效元素
	}

	//出栈转移到指定变量
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

//统计位数
int LNLength(LN src) {            		//确认无误
	int8_t *p = src.digit;
	//找最高位
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
	//偏移量之差
	return &(src.digit[LEN - 1]) - p + 1;
}

//输出
void LNPrint (LN *src) {            		//确认无误
	int8_t *p = &(src->digit[0]);
	//找最高位
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
	//循环输出
	//先输出第一位（有符号）
	printf("%"PRId8, *p);

	if(p - &(src->digit[0]) == LEN - 1) {//如果当前是最后一位，退出
		return;
	} else {
		p++;
	}
	while(1){
		if(p - &(src->digit[0]) == LEN) {//如果当前是最后一位，退出
			break;
		} else {
			printf("%"PRId8, abs((int)(*p)));
			p++;
		}


	}

}

//大数加法
LN LNAdd(LN a, LN b) {
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

//大数减法
LN LNSubtract (const LN a, const LN b) {
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


//大数乘法
LN LNMultiply (LN a, LN b) {
	LN result;
	memset(result.digit, 0, sizeof(result.digit));
	LN sum;
	memset(sum.digit, 0, sizeof(sum.digit));
	int alen = LNLength(a);//a的位数
	int blen = LNLength(b);//b的位数
	if (alen + blen > LEN) {
		printf("因两数位数之和%d大于%d, 其乘积可能会超出范围进而导致数据错误。\n请调整最大位数，或输入较小的数。\n", alen + blen, LEN);
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

LN LNPow (LN base, int exp) {
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

//大数除法
LN LNDivide (LN a, LN b) {
//	LN quotient;
//	memset(quotient.digit, 0, quotient.digit);
//	LN remain;
//	memset(remain.digit, 0, remain.digit);
	int alen = LNLength (a);
	int blen = LNLength (b);

	int i = 0;
	int j = 0;

	for (i = LEN - 1 - alen; i <= LEN - 1; i++) {

		for (j = 0; j = blen; j++) {

		}

	}
}

int main(void) {
	LN a;
	memset(a.digit, 0, sizeof(a.digit));
    LNScan(&a);
//	LN b;
//	memset(b.digit, 0, sizeof(b.digit));
//    LNScan(&b);
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

	int exp;
	scanf("%d", &exp);
	LN c;
	c = LNPow(a, exp);
	LNPrint(&c);
	return 0;
}

/*
可优化：
1：目前未考虑输入负数；
2:获取可以利用闲置的栈；
3:利用位数计算函数；已优化
*/
