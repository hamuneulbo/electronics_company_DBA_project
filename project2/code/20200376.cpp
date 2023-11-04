#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "mysql.h"

#pragma comment(lib, "libmysql.lib")

const char* host = "localhost";
const char* user = "root";
const char* pw = "rlagksmf5609@";
const char* db = "himart";

int main(void) {

	MYSQL* connection = NULL;
	MYSQL conn;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;

	if (mysql_init(&conn) == NULL)
		printf("mysql_init() error!");

	connection = mysql_real_connect(&conn, host, user, pw, db, 3306, (const char*)NULL, 0);
	if (connection == NULL)
	{
		printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
		return 1;
	}

	else
	{
		printf("Connection Succeed\n\n");

		if (mysql_select_db(&conn, db))
		{
			printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
			return 1;
		}

		const int max = 5000;
		char ltmp[max];
		char line[max];
		char* pLine;
		char query[1000];
		char del[7] = "delete";
		int state, k = 0;
		int flag = 0;
		FILE* in = fopen("20200376.txt", "r");

		for (int i = 0; i < max; i++) {
			line[i] = '\0';
		}

		while (!feof(in)) {
			//fscanf(in, "%s", ltmp);
			pLine = fgets(ltmp, max, in);
			if (!pLine) break;

			for (int i = 0; i < strlen(pLine); i++) {
				//printf("%c", *(pLine + i));
				if (*(pLine + i) == ';') {
					//printf("%s\n", line);
					if (strncmp(pLine, del, 6) == 0) {
						flag = 1;
						break;
					}
					state = mysql_query(connection, line);
					if (state == 0)
					{
						//printf("\n create table!\n");
					}
					for (int j = 0; j < max; j++) {
						line[j] = '\0';
					}
					k = 0;
					break;
				}
				line[k++] = *(pLine + i);

			}
			if (flag == 1) break;

		}
		fclose(in);

		int input, input2;

		while (1) {

			printf("\n\n---------- SELECT QUERY TYPES ----------\n\n");
			printf("\t1. TYPE 1\n");
			printf("\t2. TYPE 2\n");
			printf("\t3. TYPE 3\n");
			printf("\t4. TYPE 4\n");
			printf("\t5. TYPE 5\n");
			printf("\t6. TYPE 6\n");
			printf("\t7. TYPE 7\n");
			printf("\t0. QUIT\n");

			scanf("%d", &input);
			if (input == 0) break;

			else if (input == 1) {
				char temp[100];
				char temp2[20][100];
				char track[17] = "0000000000000000";
				int tmp, tmp2, tmp3, i = 0;
				int ux;
				int div, mod;
				printf("------- TYPE 1 -------\n\n");
				printf("** The package shipped by USPS with tracking number X is destroyed in an accident **\n");
				printf("** Find the contact information for the customer **\n\n");
				//printf("** Asuume X = 4 **\n\n");
				printf("Which X?: ");
				scanf("%d", &ux);

				tmp3 = ux;
				i = 0;
				while (tmp3) {
					div = tmp3 / 10;
					mod = tmp3 % 10;
					track[15 - i] = mod + '0';
					tmp3 = tmp3 / 10;
					i++;
				}
				//printf("%s\n", track);
				//scanf("%d", &ux);
				sprintf(query, "select * from customer as c, sale as s where c.c_id = s.c_id and s.sale_number in (select sale_number from delivery where tracking_number='%s' and d_company_name = 'USPS')", track);
				state = mysql_query(connection, query);
				if (state == 0)
				{
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("Customer_id : %s\n\nName : %s\n\nPhone_number : %s\n\n\n", sql_row[0], sql_row[1], sql_row[3]);
						strcpy(temp, sql_row[5]);
						tmp = atoi(temp);
						tmp2 = tmp;
					}

					mysql_free_result(sql_result);
				}

				printf("---------- Subtype in TYPE 1 ----------\n");
				printf("          1. TYPE 1-1\n\n\n");
				scanf("%d", &input2);
				if (input2 == 0)break;
				else if (input2 == 1) {
					printf("---------- TYPE 1-1 ----------\n\n");
					printf("** The contents of that shipment **\n\n");

					sprintf_s(query, "select p.pkg_name, pi.p_name, amount from sale as s, package as p, package_item as pi where pi.pkg_id=p.pkg_id and s.pkg_id = p.pkg_id and s.sale_number in (select sale_number from delivery where tracking_number='%s' and d_company_name = 'USPS')", track);
					i = 0;
					state = mysql_query(connection, query);
					if (state == 0)
					{
						sql_result = mysql_store_result(connection);
						sql_row = mysql_fetch_row(sql_result);
						printf(" Package name : %s\n\n Package_item\n -> %s\n", sql_row[0], sql_row[1]);
						strcpy(temp, sql_row[2]);
						tmp = atoi(temp);

						strcpy(temp2[i++], sql_row[1]);
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
						{
							printf(" -> % s\n", sql_row[1]);
							strcpy(temp2[i++], sql_row[1]);
						}

						for (int j = 0; j < i; j++) {
							sprintf(query, "update inventory set wh_cnt = wh_cnt - %d where p_name='%s'", tmp, temp2[j]);
							state = mysql_query(connection, query);
							if (state == 0) {
								printf("\n %s's Inventory Count is reduced by amount '%d'", temp2[j], tmp);
							}
						}

						sprintf(query, "insert into delivery values ('USPS', '0000000000000007', %d, curdate(), adddate(curdate(), 7), null)", tmp2);
						state = mysql_query(connection, query);
						if (state == 0) {
							printf("\n\nA new shipment with replacement_items is created!!!\n");
						}

						mysql_free_result(sql_result);
					}
				}

			}

			else if (input == 2) {
				char temp[100];
				int tmp;
				printf("------- TYPE 2 -------\n\n");
				printf("** Customer who has bought the most (in price) in the past year **\n\n");

				sprintf(query, "create view p_price as with p_price(c_id, p_name, amount, price, final_price) as (select c_id, p_name, amount, p.price, amount * p.price from sale, product as p where p.name = sale.p_name and sale_date like '2021%%' order by c_id) select c_id, sum(final_price) as final_price from p_price group by c_id order by c_id");
				//printf("%s", query);
				state = mysql_query(connection, query);
				if (state == 0) {
					printf("View about sale & product_price is created!!\n");
				}

				sprintf(query, "create view pkg_price as with pkg_list(pkg_id, p_name, price, discount_rate) as (select p.pkg_id, pi.p_name, pd.price, p.discount_rate from package as p, package_item as pi, product as pd where pd.name=pi.p_name and p.pkg_id=pi.pkg_id) select pkg_id, sum(price) as price, discount_rate, sum(price)*(100-discount_rate)*0.01 as final_price from pkg_list as pl group by pl.pkg_id");
				state = mysql_query(connection, query);
				if (state == 0) {
					printf("View about package_price is created!!\n");
				}

				sprintf(query, "create view pk_price as with pk_price(c_id, pkg_id, amount, price, final_price) as (select c_id, pk.pkg_id, amount, pk.final_price, amount*pk.final_price from sale, pkg_price as pk where pk.pkg_id=sale.pkg_id and sale_date like '2021%%' order by c_id) select c_id, sum(final_price) as final_price from pk_price group by c_id order by c_id");
				state = mysql_query(connection, query);
				if (state == 0) {
					printf("View about sale & package_price is created!!\n");
				}

				sprintf(query, "create view type2 as select * from p_price union select * from pk_price");
				state = mysql_query(connection, query);
				if (state == 0) {
					printf("Two Views are unioned!!\n\n");
				}

				sprintf(query, "with type2_max(c_id, max_price) as (select c_id, sum(final_price) from type2 group by c_id order by c_id) select c_id, max_price from type2_max where max_price >= (select max(max_price) from type2_max)");
				state = mysql_query(connection, query);
				if (state == 0)
				{
					sql_result = mysql_store_result(connection);
					if ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("Customer_id : %s\n\npayment : %s\n\n\n", sql_row[0], sql_row[1]);
						strcpy(temp, sql_row[0]);
						tmp = atoi(temp);
					}

					mysql_free_result(sql_result);
				}

				printf("---------- Subtype in TYPE 2 ----------\n");
				printf("          1. TYPE 2-1\n\n\n");
				scanf("%d", &input2);
				if (input2 == 0)break;
				else if (input2 == 1) {
					printf("---------- TYPE 2-1 ----------\n\n");
					printf("** The product that the customer bought the most **\n\n");

					sprintf(query, "create view type2_1 as select p_name, amount from sale where sale_date like '2021%%' and c_id=%d and p_name is not null union select p.p_name, s.amount from sale as s, package_item as p where s.pkg_id=p.pkg_id and sale_date like '2021%%' and c_id=%d and s.pkg_id is not null", tmp, tmp);
					state = mysql_query(connection, query);
					if (state == 0) {
						printf("View about Customer %d's purchase list is created!!\n\n\n", tmp);
					}

					//sprintf(query, "create view p_price as with p_price(c_id, p_name, amount, price, final_price) as (select c_id, p_name, amount, p.price, amount * p.price from sale, product as p where p.name = sale.p_name and sale_date like '2021%%' order by c_id) select c_id, sum(final_price) as final_price from p_price group by c_id order by c_id");
					sprintf(query, "select p_name, amount from type2_1 group by p_name having amount >= max(amount) order by amount DESC");
					state = mysql_query(connection, query);
					if (state == 0)
					{
						sql_result = mysql_store_result(connection);
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
						{
							printf("product_name : %s  ->  amount : %s\n\n", sql_row[0], sql_row[1]);
						}
						mysql_free_result(sql_result);
					}
				}

			}

			else if (input == 3) {
				printf("------- TYPE 3 -------\n\n");
				printf("** Find all products sold in the past year **\n\n");

				sprintf(query, "create view t3_1 as with t3_1(p_name, amount, price) as (select p_name, amount, price from sale, product as p where sale.p_name=p.name and sale_date like '2021%%' and p_name is not null) select p_name, amount, amount*price as price from t3_1");
				state = mysql_query(connection, query);
				if (state == 0) {
					printf("View about products sold last year is created!!\n");
				}

				sprintf(query, "create view t3_4 as select p_name, sum(amount) as amount, sum(price) as price from t3_1 group by p_name");
				state = mysql_query(connection, query);
				if (state == 0) {
					printf("View about ordered products sold last year is created!!\n");
				}

				sprintf(query, "create view t3_2 as with t3_2(p_name, amount, price) as (select p.p_name, s.amount, price from sale as s, package_item as p, product as pd where p.p_name=pd.name and s.pkg_id=p.pkg_id and sale_date like '2021%%' and s.pkg_id is not null) select p_name, amount, amount*price as price from t3_2");
				state = mysql_query(connection, query);
				if (state == 0) {
					printf("View about packages sold last year is created!!\n");
				}

				sprintf(query, "create view t3_5 as select p_name, sum(amount) as amount, sum(price) as price from t3_2 group by p_name");
				state = mysql_query(connection, query);
				if (state == 0) {
					printf("View about ordered packages sold last year is created!!\n");
				}

				sprintf(query, "create view t3_3 as select * from t3_4 union select * from t3_5");
				state = mysql_query(connection, query);
				if (state == 0) {
					printf("Two Views are unioned!!\n\n\n");
				}

				int count = 0;
				sprintf(query, "select p_name, sum(amount) as amount, sum(price) as price from t3_3 group by p_name order by price desc");
				state = mysql_query(connection, query);
				if (state == 0)
				{
					printf("[ product_name ]\n\n");
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("%s\n", sql_row[0]);
						count++;
					}
					mysql_free_result(sql_result);
				}

				int uk;
				int cnt = 0;

				printf("\n---------- Subtype in TYPE 3 ----------\n");
				printf("          1. TYPE 3-1\n");
				printf("          2. TYPE 3-2\n\n\n");
				scanf("%d", &input2);
				if (input2 == 0)break;
				else if (input2 == 1) {
					printf("---------- TYPE 3-1 ----------\n\n");
					printf("** Find the top k products by dollar-amount-sold **\n");
					printf(" Which K?: ");
					scanf("%d", &uk);
					sprintf(query, "select p_name, sum(amount) as amount, sum(price) as price from t3_3 group by p_name order by price desc");
					state = mysql_query(connection, query);
					if (state == 0)
					{
						printf("\n[ product_name ]\n\n");
						sql_result = mysql_store_result(connection);
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
						{
							if (cnt == uk) break;
							printf("%s\n", sql_row[0]);
							cnt++;
						}
						mysql_free_result(sql_result);

					}
				}
				else if (input2 == 2) {
					printf("\n---------- TYPE 3-2 ----------\n\n");
					printf("** Find the top 10%% products by dollar-amount-sold **\n");
					//printf("%d", count);
					int top10 = count * 0.1;
					//printf("%d", top10);
					cnt = 0;
					sprintf(query, "select p_name, sum(amount) as amount, sum(price) as price from t3_3 group by p_name order by price desc");
					state = mysql_query(connection, query);
					if (state == 0)
					{
						printf("\n[ product_name ]\n\n");
						sql_result = mysql_store_result(connection);
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
						{
							if (cnt == top10) break;
							printf("%s\n", sql_row[0]);
							cnt++;
						}
						mysql_free_result(sql_result);
					}
				}

			}

			else if (input == 4) {
				int count = 0;
				printf("------- TYPE 4 -------\n\n");
				printf("** Find all products by unit sales in the past year **\n\n");

				sprintf(query, "select p_name, sum(amount) as amount, sum(price) as price from t3_3 group by p_name order by amount desc");
				state = mysql_query(connection, query);
				if (state == 0)
				{
					printf("[ amount & product_name ]\n\n");
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("%s\t%s\n", sql_row[1], sql_row[0]);
						count++;
					}
					mysql_free_result(sql_result);
				}

				int uk;
				int cnt = 0;
				printf("\n\n---------- Subtype in TYPE 4 ----------\n");
				printf("          1. TYPE 4-1\n");
				printf("          2. TYPE 4-2\n\n\n");
				scanf("%d", &input2);
				if (input2 == 0)break;
				else if (input2 == 1) {
					printf("---------- TYPE 4-1 ----------\n\n");
					printf("** Find the top k products by unit sales **\n");
					printf(" Which K?: ");
					scanf("%d", &uk);

					sprintf(query, "select p_name, sum(amount) as amount, sum(price) as price from t3_3 group by p_name order by amount desc");
					state = mysql_query(connection, query);
					if (state == 0)
					{
						printf("\n[ product_name ]\n\n");
						sql_result = mysql_store_result(connection);
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
						{
							if (cnt == uk) break;
							printf("%s\n", sql_row[0]);
							cnt++;
						}
						mysql_free_result(sql_result);

					}
				}
				else if (input2 == 2) {
					printf("\n---------- TYPE 4-2 ----------\n\n");
					printf("** Find the top 10%% products by unit sales **\n");
					//printf("%d", count);
					int top10 = count * 0.1;
					//printf("%d", top10);
					cnt = 0;
					sprintf(query, "select p_name, sum(amount) as amount, sum(price) as price from t3_3 group by p_name order by amount desc");
					state = mysql_query(connection, query);
					if (state == 0)
					{
						printf("\n[ product_name ]\n\n");
						sql_result = mysql_store_result(connection);
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
						{
							if (cnt == top10) break;
							printf("%s\n", sql_row[0]);
							cnt++;
						}
						mysql_free_result(sql_result);
					}
				}

			}

			else if (input == 5) {
				printf("------- TYPE 5 -------\n\n");
				printf("** Find those products that are out-of-stock at every store in California **\n\n");

				sprintf(query, "create view type5 as select p_name, count(p_name) as count from store as s, store_inventory as si where store_cnt=0 and s.s_id=si.s_id and region='California' group by p_name");
				state = mysql_query(connection, query);
				if (state == 0) {
					printf("View about those products is created!!\n\n\n");
				}

				sprintf(query, "select * from type5 where count = (select count(s_id) from store where region='California')");
				//printf("%s\n", query);
				state = mysql_query(connection, query);
				if (state == 0)
				{
					printf("[ product_name ]\n\n");
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("%s\n", sql_row[0]);
					}
					mysql_free_result(sql_result);
				}


			}

			else if (input == 6) {
				printf("------- TYPE 6 -------\n\n");
				printf("** Find packages that were not delivered within the promised time **\n\n");

				sprintf(query, "select p.pkg_id, p.pkg_name, s.amount from sale as s, package as p where p.pkg_id = s.pkg_id and s.pkg_id is not null and s.sale_number in (select sale_number from delivery where promise_date < arrival_date or (promise_date<curdate() and arrival_date is null))");
				state = mysql_query(connection, query);
				if (state == 0) {
					sql_result = mysql_store_result(connection);
					printf("--------------------------------------------------\n");
					printf("| package_id | package_name         | amount     |\n");
					printf("--------------------------------------------------\n");
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("| %10s | %20s | %10s |\n", sql_row[0], sql_row[1], sql_row[2]);
					}
					printf("--------------------------------------------------\n");
					mysql_free_result(sql_result);
				}
			}

			else if (input == 7) {
				printf("------- TYPE 7 -------\n\n");
				printf("** Generate the bill for each customer for the past month **\n\n");

				sprintf(query, "create view type7 as with type7_1(c_id, pkg_id, amount, price) as (select c_id, s.pkg_id, amount, final_price from sale as s, pkg_price as p where s.pkg_id=p.pkg_id and sale_date like '2022-05%%' and c_id in (select c_id from customer where contractor_number is not null)) select c_id, pkg_id as product_pkg, amount, amount*price as price from type7_1");
				state = mysql_query(connection, query);
				if (state == 0) {
					printf("View about product bill is created!!\n");
				}

				sprintf(query, "create view t7 as with t7_1(c_id, p_name, amount, price) as (select c_id, p_name, amount, price from sale as s, product as p where p.name=s.p_name and sale_date like '2022-05%%' and c_id in (select c_id from customer where contractor_number is not null)) select c_id, p_name as product_pkg, amount, amount*price as price from t7_1");
				state = mysql_query(connection, query);
				if (state == 0) {
					printf("View about package bill is created!!\n");
				}

				sprintf(query, "create view type7_2 as select * from t7 union select * from type7");
				state = mysql_query(connection, query);
				if (state == 0) {
					printf("Two Views are unioned!!\n\n\n");
				}

				sprintf(query, "select c_id, sum(price) as total_price from type7_2 group by c_id");
				state = mysql_query(connection, query);
				if (state == 0)
				{
					printf("\n--- TOTAL PRICE ---\n\n");
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("customer_id : %s\ttotal_price: %s\n\n", sql_row[0], sql_row[1]);
					}
					mysql_free_result(sql_result);
				}

				sprintf(query, "select * from type7_2");
				state = mysql_query(connection, query);
				if (state == 0)
				{
					printf("\n--- Specification ---\n\n");
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("customer_id : %s\tproduct/pkg : %s\tamount : %s\tprice : %s\n\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3]);
					}
					mysql_free_result(sql_result);
				}

			}


		}

		FILE* finish = fopen("20200376.txt", "r");

		for (int i = 0; i < max; i++) {
			line[i] = '\0';
		}
		flag = 0;
		while (!feof(finish)) {
			//fscanf(in, "%s", ltmp);
			pLine = fgets(ltmp, max, finish);
			if (!pLine) break;

			for (int i = 0; i < strlen(pLine); i++) {
				//printf("%c", *(pLine + i));
				if (*(pLine + i) == ';') {
					//printf("%s\n", line);
					if (strncmp(pLine, del, 6) == 0) {
						flag = 1;
					}
					if (flag == 1) {
						state = mysql_query(connection, line);
						if (state == 0)
						{
							//printf("\n delete table!\n");
						}
					}
					
					for (int j = 0; j < max; j++) {
						line[j] = '\0';
					}
					k = 0;
					break;
				}
				line[k++] = *(pLine + i);

			}

		}
		fclose(finish);

		mysql_close(connection);

	}

	return 0;
}