DROP TABLE config;
DROP TABLE video;
DROP TABLE tutor;
DROP TABLE series;

CREATE TABLE config(
param INT,
idx    INT,
intval    INT,
charval   CHAR(256),
desc     CHAR(256)
);
INSERT INTO config VALUES(0, 1, 0, 'http://www.boobooke.com/qv.php', 'video query url');
INSERT INTO config VALUES(1, 1, 0, 'videos', 'video directory');

CREATE TABLE tutor (
tid	CHAR(10),
ename	CHAR(128)
);
INSERT INTO tutor VALUES('TID0000000', 'С��');
INSERT INTO tutor VALUES('TID0000001', '�ڹ�');
INSERT INTO tutor VALUES('TID0000002', '����');
INSERT INTO tutor VALUES('TID0000003', 'С��');

CREATE TABLE series (
sid	INTEGER PRIMARY KEY,
tutor	CHAR(32),
total	INTEGER,
title	CHAR(256),
summary CHAR(2048)
);
INSERT INTO series VALUES(0, '', 0, '����ϵ�е���Ƶ', ''); 
INSERT INTO series VALUES(1, 'С��', 76, 'Oracle 9i Fundamentals Iϵ����ѵ��Ƶ', 'Oracle 9i��ѵר��'); 
INSERT INTO series VALUES(2, 'С��', 40, 'MySQL��������ϵ����ѵ��Ƶ', 'MySQL���ż��õ���ѵ��Ƶ'); 

CREATE TABLE video (
vid 	CHAR(13) PRIMARY KEY,
tutor	CHAR(32),
sid	INTEGER,
idx	INTEGER,
title	CHAR(256),
summary	CHAR(2048),
tag	CHAR(128),
size	CHAR(1),
FOREIGN KEY(sid) REFERENCES series(sid)
);
INSERT INTO video VALUES('bbk1109', 'С��', 1, 1, 'Oracle��Linuxƽ̨�µİ�װ', NULL, 'Oracle|���ݿ�', 'S');
INSERT INTO video VALUES('bbk1110', 'С��', 1, 2, 'Oracle��ϵ�ṹ����', NULL, 'Oracle|���ݿ�', 'S');
INSERT INTO video VALUES('bbk4791', 'С��', 2, 1, 'MySQL��Linuxƽ̨�µİ�װ', NULL, 'MySQL|���ݿ�|Linux', 'S');
INSERT INTO video VALUES('bbk4798', 'С��', 2, 2, 'MySQL��ϵ�ṹ����', NULL, 'MySQL|���ݿ�|Linux', 'S');

