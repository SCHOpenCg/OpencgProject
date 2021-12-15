
// �ʿ��� ��������� �����Ѵ�
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// �ʿ��� ���Ǹ� �Ѵ�
#define MAX_STR_SIZE 1000

// ���� ���� ������ �����Ѵ�
#pragma warning(disable : 4996)

// �л� ����ü�� �����Ѵ�
typedef struct student
{
	char name[30]; // �л� �̸�
	int num; // �л� �й�
	int hour; // �ð�
	int minute; // ��
	int second; // ��
}Student;

// ���� �Լ�
int main(void)
{
	FILE *fp; // ���� ������ ����
	Student std[10]; // �л� ����ü �迭 ����

	// �ӽ� ���� ������ �����Ѵ�
	char tmp[100];
	char tmp2[100];
	char *ptr; // ptr �����͸� �����Ѵ�

	// �ʿ��� ������ �����Ѵ�
	int i = 0;
	int j = 0;
	int total, std_total;
	int time_hour, time_minute, time_second;

	// ������ �д´�
	fp = fopen("Sheet1.txt", "r");

	// ���� ���� ���н� �����Ѵ�
	if (fp == NULL)
	{
		return 0;
	}

	// ���� ������ �ݺ��ϸ鼭 ������ �дµ� �ΰ��̸� �����Ѵ�
	while (!feof(fp) && fgets(tmp, 1000, fp) != '\0')
	{
		// tmp�� ���̸� ����
		if (strcmp(tmp, "\0") == 0)
			break;
		// ":" ���ڸ� �������� ���ڿ��� �ڸ���, ������ ��ȯ
		ptr = strtok(tmp, ",");
		while (ptr != NULL)// �ڸ� ���ڿ��� ������ ���� ������ �ݺ�
		{
			// ���� j�� 3�ϰ��
			if (j == 3)
			{
				// ���� �������ϰ�� 
				if (strcmp(ptr, "������") == 0)
				{
					// �ð��� ��� 0���� �����
					std[i].hour = 0;
					std[i].minute = 0;
					std[i].second = 0;
					// �ݺ����� ���� ������
					break;
				}
			}
			// �̸��� �Է¹޴´�
			if (j == 0)
			{
				std[i].num = atoi(ptr);
			}
			// �й��� �Է¹޴´�
			if (j == 1)
			{
				strcpy(std[i].name, ptr);
			}
			// �⼮ �ð��� ��ū���� �и��� ���� �����Ѵ�
			if (j == 5)
			{
				strcpy(tmp2, ptr);
				ptr = strtok(tmp2, ":");
				std[i].hour = atoi(ptr);
				ptr = strtok(NULL, " :");
				std[i].minute = atoi(ptr);
				ptr = strtok(NULL, " :");
				std[i].second = atoi(ptr);
			}
			ptr = strtok(NULL, ",");      // ���� ���ڿ��� �߶� �����͸� ��ȯ
			j++;
		}
		// �л��� ������ ����Ѵ�
		printf("%d %s %d:%d:%d\n", std[i].num, std[i].name, std[i].hour, std[i].minute, std[i].second);
		j = 0;
		i++;
	}

	// ���� �ð��� �Է� �޴´�
	printf("���� �ð�(��, ��, ��)�� �Է��Ͻÿ�:  ");
	scanf("%d %d %d", &time_hour, &time_minute, &time_second);

	// �����ð��� ����Ѵ�
	total = time_hour * 3600 + time_minute * 60 + time_second;

	// �л� �� ��ŭ �ݺ��Ѵ�
	for (i = 0; i < 6; i++)
	{
		printf("%d %s %d:%d:%d ", std[i].num, std[i].name, std[i].hour, std[i].minute, std[i].second);
		// �л��� �⼮�ð��� ����Ѵ�
		std_total = std[i].hour * 3600 + std[i].minute * 60 + std[i].second;

		// ���� ���� �ð��� 5�� �̳����� ���Ǹ� ����� ��� �⼮ ���� �ƴҰ�� �����̴�
		if ((total - 300) > std_total)
			printf("�⼮ ����\n");
		else
			printf("�⼮ ����\n");

	}

	// ������ �ݰ� �����Ѵ�
	fclose(fp);
	return 0;
}