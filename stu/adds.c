#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"

int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");

	char sno[32] = "\0";
	char cno[6] = "\0";
	char grade[6] = "\0";
	int status = 0;

	status = cgiFormString("sno",  sno, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get sno error!\n");
		return 1;
	}

	status = cgiFormString("cno",  cno, 6);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get cno error!\n");
		return 1;
	}

	status = cgiFormString("grade",  grade, 6);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get grade error!\n");
		return 1;
	}

	//fprintf(cgiOut, "sname = %s, sage = %s, sno = %s\n", sname, sage, sno,dept);

	int ret;
	char sql[128] = "\0";
	MYSQL *db;

	//初始化
	db = mysql_init(NULL);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_init fail:%s\n", mysql_error(db));
		return -1;
	}

	//连接数据库
	db = mysql_real_connect(db, "127.0.0.1", "root", "123456", "stu",  3306, NULL, 0);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_real_connect fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}



	/*strcpy(sql, "create table stu(id int not null primary key, name varchar(20) not null, age int not null, sex char(4) not null, dept char(10) not null)");
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		if (ret != 1)
		{
			fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
			mysql_close(db);
			return ;
		}
	}*/



	sprintf(sql, "insert into score values(%d, '%s', '%s')", atoi(sno), cno, grade);
	if (mysql_real_query(db, sql, strlen(sql) + 1) != 0)
	{
		fprintf(cgiOut, "%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}

	fprintf(cgiOut, "add score ok!\n");
	mysql_close(db);
	return 0;
}