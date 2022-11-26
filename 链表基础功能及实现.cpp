#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

struct cell {
	ElementType val;
	struct cell* next;
};

//新建链表
struct cell* Build() {
	struct cell* head, * p, * tail;
	head = p = tail = NULL;
	int n = 0;	//计录当前节点数
	while (true) {
		if (!n) {	//若n节点数为0，则添加一个头节点
			head = (struct cell*)malloc(sizeof(struct cell));	//为头节点申请一个新空间
			scanf("%d", &head->val);	//输入头节点
			tail = head;	//此时头节点也是尾节点
			tail->next = NULL;
			n = 1;
		}
		else {
			p = (struct cell*)malloc(sizeof(struct cell));	//为新节点申请一个新空间
			scanf("%d", &p->val);
			if (p->val == 0) {	//若输入为0，则释放此时p节点的内存并跳出循环
				free(p);
				break;
			}
			tail->next = p;	//tail指向p，实现节点连接
			tail = p;	//tail移动到p，实现tail移动到尾节点位置
			tail->next = NULL;
		}
	}
	return head;
}

//新增节点
struct cell* Add(struct cell* head, int n) {
	if (head == NULL || n <= 0) {	//若为空链表或n不合法，则返回NULL
		return NULL;
	}
	struct cell* p, * p0;
	p0 = head;
	p = (struct cell*)malloc(sizeof(struct cell));	//为新增节点p申请一个新空间
	scanf("%d", &p->val);
	if (n == 1) {	//当新增节点位置为头节点处时
		p->next = head;
		return p;
	}
	else {
		for (int i = 1; i < n - 1; i++) {
			p0 = p0->next;	//p0记录新增节点位置的前一个节点
			if (p0 == NULL) {	//若n超过链表长度，则返回原头节点head
				return head;
			}
		}
		p->next = p0->next;		//***标注A***
		p0->next = p;
	}
	return head;
}

//删除节点
struct cell* Del(struct cell* head, int n) {
	if (head == NULL || n <= 0) {	//若为空链表或n不合法，则返回NULL
		return NULL;
	}
	struct cell* p, * p0;
	p = p0 = head;
	if (n == 1) {	//当删除节点为头节点时
		head = head->next;
		free(p);	//***标注B***
	}
	else {
		for (int i = 1; i < n - 1; i++) {
			p0 = p0->next;	//p0记录删除节点位置的前一个节点
			if (p0 == NULL) {	//若n超过链表长度，则返回原头节点head
				return head;
			}
		}
		p = p0->next;
		if (p) {	//检测p是否为NULL，即p0是否为位节点
			p0->next = p->next;
			free(p);	//***标注B***
		}
	}
	return head;
}

//通过节点查找元素
ElementType FindElement(struct cell* head, int n) {
	if (head == NULL || n <= 0) {	//若为空链表或n不合法，则返回0
		return 0;
	}
	for (int i = 1; i < n; i++) {
		head = head->next;
		if (head == NULL) {	//若n超过链表长度，则返回0
			return 0;
		}
	}
	return head->val;
}

//通过元素查找节点
bool FindSite(struct cell* head, ElementType n) {
	int x = 1;	//记录节点位置
	bool TorN = false;
	while (head) {
		if (head->val == n) {
			printf("%d ", x);
			TorN = true;	//若找到则标记true
		}
		head = head->next;
		x++;
	}
	if (x) {
		return true;
	}
	printf("NULL");
	return false;	//未找到返回0并打印NULL
}

//打印链表
void Print(struct cell* head) {
	while (head) {
		printf("%d ", head->val);
		head = head->next;
	}
}

//释放链表内存
void Release(struct cell* head) {
	struct cell* p;
	while (head) {
		p = head->next;
		free(p);
		head = p;
	}
}

int main() {
	struct cell* head;
	head = Build();
	head = Add(head, 3);
	Print(head);
	putchar('\n');
	head = Del(head, 5);
	Print(head);
	putchar('\n');
	printf("%d", FindElement(head, 2));
	Print(head);
	putchar('\n');
	FindSite(head, 5);
	Release(head);
	return 0;
}