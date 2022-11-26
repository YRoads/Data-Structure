#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

struct cell {
	ElementType val;
	struct cell* next;
};

//�½�����
struct cell* Build() {
	struct cell* head, * p, * tail;
	head = p = tail = NULL;
	int n = 0;	//��¼��ǰ�ڵ���
	while (true) {
		if (!n) {	//��n�ڵ���Ϊ0�������һ��ͷ�ڵ�
			head = (struct cell*)malloc(sizeof(struct cell));	//Ϊͷ�ڵ�����һ���¿ռ�
			scanf("%d", &head->val);	//����ͷ�ڵ�
			tail = head;	//��ʱͷ�ڵ�Ҳ��β�ڵ�
			tail->next = NULL;
			n = 1;
		}
		else {
			p = (struct cell*)malloc(sizeof(struct cell));	//Ϊ�½ڵ�����һ���¿ռ�
			scanf("%d", &p->val);
			if (p->val == 0) {	//������Ϊ0�����ͷŴ�ʱp�ڵ���ڴ沢����ѭ��
				free(p);
				break;
			}
			tail->next = p;	//tailָ��p��ʵ�ֽڵ�����
			tail = p;	//tail�ƶ���p��ʵ��tail�ƶ���β�ڵ�λ��
			tail->next = NULL;
		}
	}
	return head;
}

//�����ڵ�
struct cell* Add(struct cell* head, int n) {
	if (head == NULL || n <= 0) {	//��Ϊ�������n���Ϸ����򷵻�NULL
		return NULL;
	}
	struct cell* p, * p0;
	p0 = head;
	p = (struct cell*)malloc(sizeof(struct cell));	//Ϊ�����ڵ�p����һ���¿ռ�
	scanf("%d", &p->val);
	if (n == 1) {	//�������ڵ�λ��Ϊͷ�ڵ㴦ʱ
		p->next = head;
		return p;
	}
	else {
		for (int i = 1; i < n - 1; i++) {
			p0 = p0->next;	//p0��¼�����ڵ�λ�õ�ǰһ���ڵ�
			if (p0 == NULL) {	//��n���������ȣ��򷵻�ԭͷ�ڵ�head
				return head;
			}
		}
		p->next = p0->next;		//***��עA***
		p0->next = p;
	}
	return head;
}

//ɾ���ڵ�
struct cell* Del(struct cell* head, int n) {
	if (head == NULL || n <= 0) {	//��Ϊ�������n���Ϸ����򷵻�NULL
		return NULL;
	}
	struct cell* p, * p0;
	p = p0 = head;
	if (n == 1) {	//��ɾ���ڵ�Ϊͷ�ڵ�ʱ
		head = head->next;
		free(p);	//***��עB***
	}
	else {
		for (int i = 1; i < n - 1; i++) {
			p0 = p0->next;	//p0��¼ɾ���ڵ�λ�õ�ǰһ���ڵ�
			if (p0 == NULL) {	//��n���������ȣ��򷵻�ԭͷ�ڵ�head
				return head;
			}
		}
		p = p0->next;
		if (p) {	//���p�Ƿ�ΪNULL����p0�Ƿ�Ϊλ�ڵ�
			p0->next = p->next;
			free(p);	//***��עB***
		}
	}
	return head;
}

//ͨ���ڵ����Ԫ��
ElementType FindElement(struct cell* head, int n) {
	if (head == NULL || n <= 0) {	//��Ϊ�������n���Ϸ����򷵻�0
		return 0;
	}
	for (int i = 1; i < n; i++) {
		head = head->next;
		if (head == NULL) {	//��n���������ȣ��򷵻�0
			return 0;
		}
	}
	return head->val;
}

//ͨ��Ԫ�ز��ҽڵ�
bool FindSite(struct cell* head, ElementType n) {
	int x = 1;	//��¼�ڵ�λ��
	bool TorN = false;
	while (head) {
		if (head->val == n) {
			printf("%d ", x);
			TorN = true;	//���ҵ�����true
		}
		head = head->next;
		x++;
	}
	if (x) {
		return true;
	}
	printf("NULL");
	return false;	//δ�ҵ�����0����ӡNULL
}

//��ӡ����
void Print(struct cell* head) {
	while (head) {
		printf("%d ", head->val);
		head = head->next;
	}
}

//�ͷ������ڴ�
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