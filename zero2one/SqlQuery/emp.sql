-- 创建数据库
CREATE DATABASE emp;

-- 使用数据库
USE emp;

-- 创建部门表 dept
CREATE TABLE dept(
    deptId INT PRIMARY KEY AUTO_INCREMENT,
    deptName VARCHAR(40) NOT NULL
);

-- 创建员工表 emp
CREATE TABLE emp(
    empNo INT PRIMARY KEY,
    empName CHAR(10) NOT NULL,
    gender CHAR(2) DEFAULT '男',
    deptId INT,
    salary DECIMAL(7, 2) DEFAULT 5000,
    CONSTRAINT dept_emp_fk FOREIGN KEY(deptId) REFERENCES dept(deptId)
);

-- 插入测试数据
INSERT INTO dept VALUES(NULL, '机械工程学院');
INSERT INTO dept VALUES(NULL, '信息科学与工程学院');
INSERT INTO dept VALUES(NULL, '经济管理学院');
INSERT INTO dept VALUES(NULL, '电气工程学院');

INSERT INTO emp VALUES(1001, '浩然', '男', 1, 9000);
INSERT INTO emp VALUES(1003, '万茜', '女', 1, 8300);
INSERT INTO emp VALUES(2001, '王晓', '女', 2, 8800);
INSERT INTO emp VALUES(3001, '宋嘉', '男', 3, 10050);
INSERT INTO emp VALUES(4001, '孙松', '男', 4, 8000);
