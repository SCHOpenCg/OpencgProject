
// 필요한 헤더파일을 선언한다
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 필요한 정의를 한다
#define MAX_STR_SIZE 1000

// 오류 방지 구문을 선언한다
#pragma warning(disable : 4996)

// 학생 구조체를 선언한다
typedef struct student
{
	char name[30]; // 학생 이름
	int num; // 학생 학번
	int hour; // 시간
	int minute; // 분
	int second; // 초
}Student;

// 메인 함수
int main(void)
{
	FILE *fp; // 파일 포인터 선언
	Student std[10]; // 학생 구조체 배열 선언

	// 임시 저장 변수를 선언한다
	char tmp[100];
	char tmp2[100];
	char *ptr; // ptr 포인터를 선언한다

	// 필요한 변수를 선언한다
	int i = 0;
	int j = 0;
	int total, std_total;
	int time_hour, time_minute, time_second;

	// 파일을 읽는다
	fp = fopen("Sheet1.txt", "r");

	// 파일 오픈 실패시 종료한다
	if (fp == NULL)
	{
		return 0;
	}

	// 파일 끝까지 반복하면서 한줄을 읽는데 널값이면 종료한다
	while (!feof(fp) && fgets(tmp, 1000, fp) != '\0')
	{
		// tmp가 널이면 종료
		if (strcmp(tmp, "\0") == 0)
			break;
		// ":" 문자를 기준으로 문자열을 자른다, 포인터 반환
		ptr = strtok(tmp, ",");
		while (ptr != NULL)// 자른 문자열이 나오지 않을 때까지 반복
		{
			// 만약 j가 3일경우
			if (j == 3)
			{
				// 만약 미참여일경우 
				if (strcmp(ptr, "미참여") == 0)
				{
					// 시간을 모두 0으로 만든다
					std[i].hour = 0;
					std[i].minute = 0;
					std[i].second = 0;
					// 반복문을 빠져 나간다
					break;
				}
			}
			// 이름을 입력받는다
			if (j == 0)
			{
				std[i].num = atoi(ptr);
			}
			// 학번을 입력받는다
			if (j == 1)
			{
				strcpy(std[i].name, ptr);
			}
			// 출석 시간을 토큰으로 분리해 값을 삽입한다
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
			ptr = strtok(NULL, ",");      // 다음 문자열을 잘라서 포인터를 반환
			j++;
		}
		// 학생의 정보를 출력한다
		printf("%d %s %d:%d:%d\n", std[i].num, std[i].name, std[i].hour, std[i].minute, std[i].second);
		j = 0;
		i++;
	}

	// 수업 시간을 입력 받는다
	printf("기준 시간(시, 분, 초)을 입력하시오:  ");
	scanf("%d %d %d", &time_hour, &time_minute, &time_second);

	// 수업시간을 계산한다
	total = time_hour * 3600 + time_minute * 60 + time_second;

	// 학생 수 만큼 반복한다
	for (i = 0; i < 6; i++)
	{
		printf("%d %s %d:%d:%d ", std[i].num, std[i].name, std[i].hour, std[i].minute, std[i].second);
		// 학생의 출석시간을 계산한다
		std_total = std[i].hour * 3600 + std[i].minute * 60 + std[i].second;

		// 만약 수업 시간의 5분 이내까지 강의를 들었을 경우 출석 성공 아닐경우 실패이다
		if ((total - 300) > std_total)
			printf("출석 실패\n");
		else
			printf("출석 성공\n");

	}

	// 파일을 닫고 종료한다
	fclose(fp);
	return 0;
}