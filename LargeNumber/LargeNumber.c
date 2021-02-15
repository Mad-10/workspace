#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#define LEN 10

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
int LNLength(LN *src) {            		//确认无误
	int8_t *p = &(src->digit[0]);
	//找最高位
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
	//偏移量之差
	return &(src->digit[LEN - 1]) - p + 1;
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

int main(void) {
	LN a;
	memset(a.digit, 0, sizeof(a.digit));
	LNScan(&a);
	
	
	return 0;
}
