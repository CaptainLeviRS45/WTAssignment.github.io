-- Create tables
CREATE TABLE Book (
    accnum INT PRIMARY KEY,
    author VARCHAR(50),
    title VARCHAR(100),
    price DECIMAL(10, 2),
    pages INT
);

CREATE TABLE Bookorder (
    vendorno INT,
    accnum INT,
    orderno INT,
    copies INT,
    orderdate DATE,
    FOREIGN KEY (accnum) REFERENCES Book(accnum)
);

CREATE TABLE Vendor (
    vendorno INT PRIMARY KEY,
    vendorname VARCHAR(50)
);

CREATE TABLE Member (
    borrowno INT PRIMARY KEY,
    name VARCHAR(50),
    address VARCHAR(100)
);

CREATE TABLE Bookissue (
    accnum INT,
    borrowno INT,
    issuedate DATE,
    FOREIGN KEY (accnum) REFERENCES Book(accnum),
    FOREIGN KEY (borrowno) REFERENCES Member(borrowno)
);

CREATE TABLE Bookreturn (
    accnum INT,
    borrowno INT,
    returndate DATE,
    FOREIGN KEY (accnum) REFERENCES Book(accnum),
    FOREIGN KEY (borrowno) REFERENCES Member(borrowno)
);

-- Insert data
INSERT INTO Book (accnum, author, title, price, pages)
VALUES (1, 'Author1', 'Book1', 150.00, 250),
       (2, 'Author2', 'Book2', 250.00, 350),
       (3, 'Author3', 'Book3', 180.00, 280);

INSERT INTO Bookorder (vendorno, accnum, orderno, copies, orderdate)
VALUES (1, 1, 101, 50, '2023-01-10'),
       (2, 2, 102, 30, '2023-02-15'),
       (1, 3, 103, 40, '2023-03-20');

INSERT INTO Vendor (vendorno, vendorname)
VALUES (1, 'Vendor1'),
       (2, 'Vendor2');

INSERT INTO Member (borrowno, name, address)
VALUES (1001, 'Member1', 'Address1'),
       (1002, 'Member2', 'Address2');

INSERT INTO Bookissue (accnum, borrowno, issuedate)
VALUES (1, 1001, '2023-01-20'),
       (2, 1002, '2023-02-25'),
       (3, 1001, '2023-03-30');

INSERT INTO Bookreturn (accnum, borrowno, returndate)
VALUES (1, 1001, '2023-02-10'),
       (2, 1002, '2023-03-05');

-- Queries

-- 1. Display all vendor names in descending order of number of copies.
SELECT v.vendorname
FROM Vendor v
JOIN Bookorder bo ON v.vendorno = bo.vendorno
GROUP BY v.vendorname
ORDER BY SUM(bo.copies) DESC;

-- 2. Display book names ordered by their price.
SELECT title
FROM Book
ORDER BY price;

-- 3. Display member names of members who have both borrowed and issued a book.
SELECT m.name
FROM Member m
JOIN Bookissue bi ON m.borrowno = bi.borrowno
JOIN Bookreturn br ON bi.borrowno = br.borrowno
GROUP BY m.name
HAVING COUNT(DISTINCT bi.accnum) > 0 AND COUNT(DISTINCT br.accnum) > 0;

-- 4. Display book names ordered by issue date.
SELECT b.title
FROM Book b
JOIN Bookissue bi ON b.accnum = bi.accnum
ORDER BY bi.issuedate;

-- 5. Display names of books whose price is greater than 200.
SELECT title
FROM Book
WHERE price > 200;

-- 6. Display book names having a substring and at least 4 characters.
SELECT title
FROM Book
WHERE title LIKE '%...%' AND LENGTH(title) >= 4;

-- 7. Set price to 300 when pages are more than 300.
UPDATE Book
SET price = 300
WHERE pages > 300;

-- 8. Find the number of books.
SELECT COUNT(*) AS book_count
FROM Book;

-- 9. Create a view of book names by their issue date.
CREATE VIEW Book_Issue_Date AS
SELECT b.title, bi.issuedate
FROM Book b
JOIN Bookissue bi ON b.accnum = bi.accnum;

-- 10. Find all account numbers with books issued but not returned.
SELECT bi.accnum
FROM Bookissue bi
LEFT JOIN Bookreturn br ON bi.borrowno = br.borrowno
WHERE br.borrowno IS NULL;

-- 11. Create a trigger to keep records in a new summary table when a book is issued from Bookissue.
CREATE TRIGGER Book_issued_trigger
AFTER INSERT ON Bookissue
FOR EACH ROW
BEGIN
    INSERT INTO Book_Issued_Summary (accnum, borrowno, issuedate)
    VALUES (NEW.accnum, NEW.borrowno, NEW.issuedate);
END;
