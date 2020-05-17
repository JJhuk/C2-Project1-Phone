# C 프로그래밍 2 project 1

Created: May 17, 2020 6:40 PM
Status: In Progress
Timeline: Jun 01, 2020
Type: Task 🔨

# **C 프로그래밍 2 project 1**

## 제목: 전화번호관리 프로그램 만들기

## 제출마감: 2020년 6월 1일

## **개요:**

- 전화번호를 검색, 추가, 삭제, 리스트 등을 수행하는 프로그램을 C 언어를 가지고 만든다.

## **내용:**

### 1. 파일 data.txt는 전화번호 데이터를 가지고 있으며 다음과 같이 ‘:’을 구분자 (field separator)로 사용한다.

- (구현의 난이도를 낮추기 위해 각 필드의 데이터로서의 빈칸은 허용하지 않으며, 한글쓰지 않는다.)

```
Bae:01098765432::G777

Baek:01062773268:0222875074:G516

Han:01034567800::G732

Jung:01068223248:0222870000:G612

Kim:01023450987::
```

### 2. 각 필드의 크기는 다음과 같이 한다.

```c
char name[30];

char phone1[20];

char phone2[20];

char memo[40];
```

이외에 프로그램을 구현하기 위한 데이터 구조(구조체, 포인터 등등)은 각자 디자인한다.

### 3. 최대 엔트리 수에는 제한이 없으나, 최소한 100개의 엔트리는 입력할 수 있어야 한다.

### 4. 프로그램의 이름은 tel로 하고, tel은 다음과 같이 사용한다.

```bash
**$tel [-adl] *words***
```

- 옵션은 독립적으로 작동하며 섞어 쓰지 않는다.

### 4-1. 기본작동

```bash
$tel (Enter)
```

사용법 설명

```bash
$tel 516
```

```bash
1 Baek 01062773268 0222875074 G516
match found.
```

```bash
$tel 2287
```

```bash
1 Baek 01062773268 0222875074 G516
2 Jung 01068223248 0222870000 G612

match found.
```

```bash
$tel Lee
```

```bash
no match found.
```

### 4-2. a(add) option

```bash
$tel –a JBaek 0101110000 0222871111 J500
```

```bash
JBaek 0101110000 0222871111 J500
add? [Y/N]: Y(Enter) -> 
```

- 다른키(Enter)는 프로그램을 끝냄
- 주어지는 arguments를 무조건 name, phone1, phone2, memo 의 순서로 저장한다.

### 4-3. d(delete) option

```bash
$tel –d Baek
```

```bash
1 Baek 01062773268 0222875074 G516
which one? 1(Enter) ->
```

- 삭제 / 맞는 숫자 범위가 아니면 프로그램 끝냄

```bash
$tel –d Bae
```

```bash
1 Bae 01098765432 G777
2 Baek 01062773268 0222875074 G516

which one? 2(Enter) ->
```

- 삭제 / 맞는 숫자 범위가 아니면 프로그램 끝냄

### 4-4. l(list) option

```bash
$tel –l
```

```bash
Bae 01098765432 G777

Baek 01062773268 0222875074 G516

Han 01034567800 G732

Jung 01068223248 0222870000 G612

Kim 01023450987
```

- 이름의 Alphabetic order로 전체 리스트를 출력

이상 기술한 작동 외에 필요한 사항은 각자 결정함.

## 제출물

### - 소스코드

- main()이 있는 파일의 이름은 tel.c, modular programming를 사용하는 경우에는 소스를 모두 압축하여 제출, 소스 코드에는 comment 필요.

### - 프로그램 구조 설명, 예제 수행과 수행 캡처 파일: CPL2-학생이름-Project-1.doc (또는 hwp)

- 예제 수행은 기본, add, delete, list 등 모든 기능을 다 보여 주어야 하며, 그 에 따른 data.txt의 변화도 보여 주어야 한다.