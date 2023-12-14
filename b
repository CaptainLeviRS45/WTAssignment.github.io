-- Create tables
CREATE TABLE Employee (
    Empid INT PRIMARY KEY,
    EmpName VARCHAR(50),
    Department VARCHAR(10),
    ContactNo VARCHAR(15),
    Emailld VARCHAR(100),
    EmpHeadId INT
);

CREATE TABLE EmpDept (
    DeptId VARCHAR(10) PRIMARY KEY,
    DeptName VARCHAR(50),
    Dept_off VARCHAR(50),
    DeptHead INT
);

CREATE TABLE EmpSalary (
    Empld INT PRIMARY KEY,
    Salary DECIMAL(10, 2),
    IsPermanent BIT
);

-- Insert sample data
INSERT INTO Employee (Empid, EmpName, Department, ContactNo, Emailld, EmpHeadId) VALUES
    (101, 'Paul', 'E-101', '1234567890', 'paul@example.com', NULL),
    (102, 'Peter', 'E-102', '9876543210', 'peter@gmail.com', 101),
    (103, 'Patrick', 'E-103', '1112223333', 'patrick@gmail.com', 101),
    (104, 'Sarah', 'E-104', '9998887777', 'sarah@example.com', 103);

INSERT INTO EmpDept (DeptId, DeptName, Dept_off, DeptHead) VALUES
    ('E-101', 'Department 101', 'Office 101', 101),
    ('E-102', 'Department 102', 'Office 102', 102),
    ('E-103', 'Department 103', 'Office 103', 103),
    ('E-104', 'Department 104', 'Office 104', 104);

INSERT INTO EmpSalary (Empld, Salary, IsPermanent) VALUES
    (101, 6000.00, 1),
    (102, 5500.00, 1),
    (103, 4800.00, 1),
    (104, 5200.00, 1);

-- Queries
-- 1. Select the detail of the employee whose name starts with P.
SELECT * FROM Employee WHERE EmpName LIKE 'P%';

-- 2. How many permanent candidates take a salary more than 5000.
SELECT COUNT(*) FROM EmpSalary WHERE IsPermanent = 1 AND Salary > 5000;

-- 3. Select the details of employees whose email IDs are in Gmail.
SELECT * FROM Employee WHERE Emailld LIKE '%@gmail.com';

-- 4. Select the details of employees who work for either department E-104 or E-102.
SELECT * FROM Employee WHERE Department IN ('E-104', 'E-102');

-- 5. What is the department name for DeptID E-102?
SELECT DeptName FROM EmpDept WHERE DeptId = 'E-102';

-- 6. What is the total salary paid to permanent employees?
SELECT SUM(Salary) FROM EmpSalary WHERE IsPermanent = 1;

-- 7. Select the department name of the company assigned to the employee whose employee ID is greater than 103.
SELECT d.DeptName 
FROM Employee e 
INNER JOIN EmpDept d ON e.Department = d.DeptId 
WHERE e.Empid > 103;

-- 8. List the count of employees in each department.
SELECT Department, COUNT(*) AS EmployeeCount 
FROM Employee 
GROUP BY Department;
