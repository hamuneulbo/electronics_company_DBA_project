## ➡️프로젝트 설명

`전자 제품 판매 업체의 DBA` 가 된 상황을 가정해서 사용자의 요구사항으로부터 데이터베이스를 구축하고,  
쿼리문을 작성한 프로젝트 입니다.  
**요구사항 추출**부터 **E-R schema diagram** 작성 내용이 `project1` 에 담겨있습니다.  
E-R schema 에서 보완을 거쳐 **Logical schema(BCNF)** 로 도출해내는 과정과 **Physical schema diagram**을 구축하는 과정, 코드가 `project2` 에 담겨있습니다.  

## 🧬프로젝트 구조
```
├── project1
│   ├── 20200376.erwin 관계 스키마 다이어그램
│   ├── [project1]20200376.pdf 보고서
│   └── er_20200376.jpg ERD
├── project2
│   ├── code 애플리케이션 프로그램
│   │      ├── 20200376.sln
│   │      ├── 20200376.cpp C++ 코드
│   │      ├── 20200376.txt 데이터베이스의 테이블 생성 및 삭제와 데이터를 추가하는 CRUD 파일
│   │      ├── 20200376.vcxproj
│   │      ├── 20200376.vcxproj.filters
│   │      ├── 20200376.vcxproj.user
│   │      ├── libmysql.dll
│   │      └── READEME.txt 애플리케이션 프로그램 README
│   ├── 20200376.erwin 물리 스키마 다이어그램
│   ├── 20200376.png 정규화된 관계 스키마 다이어그램
│   └── [project2]20200376.pdf 보고서 
└── README.md
```

## ❇️스택
- Language : `C`
- Database : `MySQL`
