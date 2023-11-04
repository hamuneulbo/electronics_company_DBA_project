## 프로젝트 설명

전자제품판매업체의 DBA 가 된 상황을 가정해서 사용자의 요구사항으로부터 데이터베이스를 구축하고, 쿼리문을 작성한 프로젝트 입니다.  
요구사항 추출부터 E-R schema diagram 작성 내용이 project1 에 담겨있습니다.  
E-R schema 에서 보완을 거쳐 Logical schema(BCNF) 로 도출해내는 과정과 Physical schema diagram 구축 과정 및 코드가 project2 에 담겨있습니다.  

## 프로젝트 구조
```
├── DB
│   ├── CreatingTable 생성한 테이블 
│   │      ├── Bicycle
│   │      ├── Broken
│   │      ├── Employee
│   │      ├── History
│   │      ├── Locations
│   │      ├── Station
│   │      ├── Users_before
│   │      └── Users_final
│   ├── data 사용한 따릉이 데이터 
│   │      ├── Bicycle.csv
│   │      ├── Bicycle_final.csv
│   │      ├── Bicycle_management.csv
│   │      ├── Broken.csv
│   │      ├── Employee.csv
│   │      ├── History_random.csv
│   │      ├── Locations.csv
│   │      ├── Station.csv
│   │      ├── Station_temp.csv
│   │      ├── Users_before.csv
│   │      └── Users_final.csv
│   ├── Graphical Visualization 쿼리문 처리 시각화 자료
│   │      ├── 1st join_bicycle management department
│   │      ├── 2nd join_final bicycle table
│   │      ├── Query_1-1
│   │      ├── Query_1-2
│   │      ├── Query_2
│   │      ├── Query_3
│   │      ├── Query_4
│   │      ├── Query_5
│   │      ├── Query_6
│   │      └── Query_7
│   ├── Query_adv 인덱싱 쿼리
│   ├── Query0 질의 쿼리 0~7
│   ├── Query1
│   ├── Query2
│   ├── Query3
│   ├── Query4
│   ├── Query5
│   ├── Query6
│   ├── Query7
│   └── fromdb.csv 
├── Final_Presentation 프로젝트 발표 ppt
├── Final_report 보고서 
└── README.md
```

## 스택
- Language : `C`
- Database : `MySQL`
