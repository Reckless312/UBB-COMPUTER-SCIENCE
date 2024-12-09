CREATE TABLE PET(
	id INT,
	name VARCHAR(50),
	PRIMARY KEY(id, name)
	)

INSERT INTO Tables(name) VALUES (N'ARMOR_SET')
INSERT INTO Tables(name) VALUES (N'ARMOR_ENHANCEMENT')
INSERT INTO Tables(name) VALUES (N'PET')

SELECT * FROM Tables

INSERT INTO Tests(Name) VALUES(N'test1')
INSERT INTO Tests(Name) VALUES(N'test2')
INSERT INTO Tests(Name) VALUES(N'test3')

SELECT * FROM Tests

INSERT INTO TestTables(TestID, TableID, NoOfRows, Position) VALUES (1, 1, 100, 1)
INSERT INTO TestTables(TestID, TableID, NoOfRows, Position) VALUES (2, 1, 100, 1)
INSERT INTO TestTables(TestID, TableID, NoOfRows, Position) VALUES (2, 2, 100, 2)
INSERT INTO TestTables(TestID, TableID, NoOfRows, Position) VALUES (3, 1, 100, 1)
INSERT INTO TestTables(TestID, TableID, NoOfRows, Position) VALUES (3, 2, 100, 2)
INSERT INTO TestTables(TestID, TableID, NoOfRows, Position) VALUES (3, 3, 100, 3)

SELECT * FROM TestTables

GO
CREATE VIEW View_1 AS
	SELECT id, name FROM PET
GO

CREATE VIEW View_2 AS
	SELECT ARMOR_SET.defense, ARMOR_ENHANCEMENT.id FROM ARMOR_SET INNER JOIN
	ARMOR_ENHANCEMENT ON ARMOR_SET.id = ARMOR_ENHANCEMENT.armor_id
GO

CREATE VIEW View_3 AS
	SELECT ARMOR_SET.name, ARMOR_ENHANCEMENT.extra_defense FROM ARMOR_SET INNER JOIN
	ARMOR_ENHANCEMENT ON ARMOR_SET.id = ARMOR_ENHANCEMENT.armor_id
	WHERE ARMOR_SET.defense IN (SELECT TOP 5 defense FROM ARMOR_SET GROUP BY defense)
GO

SELECT * FROM VIEW_1
SELECT * FROM VIEW_2
SELECT * FROM VIEW_3

INSERT INTO Views(Name) VALUES(N'View_1')
INSERT INTO Views(Name) VALUES(N'View_2')
INSERT INTO Views(Name) VALUES(N'View_3')

SELECT * FROM Views

INSERT INTO TestViews(TestID, ViewID) VALUES (1, 1)
INSERT INTO TestViews(TestID, ViewID) VALUES (2, 1)
INSERT INTO TestViews(TestID, ViewID) VALUES (2, 2)
INSERT INTO TestViews(TestID, ViewID) VALUES (3, 1)
INSERT INTO TestViews(TestID, ViewID) VALUES (3, 2)
INSERT INTO TestViews(TestID, ViewID) VALUES (3, 3)

SELECT * FROM TestViews

GO
CREATE PROCEDURE RUN_TEST(@testid INT)
AS
BEGIN
	DECLARE @ds DATETIME
	DECLARE @de DATETIME

	DECLARE table_cursor CURSOR FOR
	SELECT TableID, NoOfRows FROM TestTables WHERE TestTables.TestID = @testid ORDER BY Position

	DECLARE view_cursor CURSOR FOR
	SELECT Views.Name, Views.ViewID FROM Views
	INNER JOIN TestViews ON Views.ViewID = TestViews.ViewID WHERE TestID = @testid

	DECLARE @TableID INT
	DECLARE @ViewID INT
	DECLARE @ViewName NVARCHAR(50)
	DECLARE @NoOfRows INT

	OPEN table_cursor

	SET @ds = GETDATE()

	FETCH NEXT FROM table_cursor INTO @TableID, @NoOfRows
	WHILE @@FETCH_STATUS = 0
	BEGIN
		EXEC DELETE_DATA @TableID = @TableID, @NoOfRows = @NoOfRows
	
		FETCH NEXT FROM table_cursor INTO @TableID, @NoOfRows
	END

	CLOSE table_cursor

	DECLARE table_cursor_reverse CURSOR FOR
	SELECT TableID, NoOfRows FROM TestTables WHERE TestTables.TestID = @testid ORDER BY Position DESC

	OPEN table_cursor_reverse

	FETCH NEXT FROM table_cursor_reverse INTO @TableID, @NoOfRows
	WHILE @@FETCH_STATUS = 0
	BEGIN
		EXEC ADD_DATA @TableID = @TableID, @NoOfRows = @NoOfRows

		FETCH NEXT FROM table_cursor_reverse INTO @TableID, @NoOfRows
	END

	CLOSE table_cursor_reverse

	DEALLOCATE table_cursor_reverse

	OPEN view_cursor

	FETCH NEXT FROM view_cursor INTO @ViewName, @ViewID
	WHILE @@FETCH_STATUS = 0
	BEGIN
		EXEC('SELECT * FROM ' + @ViewName)
		FETCH NEXT FROM view_cursor INTO @ViewName, @ViewID
	END 

	CLOSE view_cursor

	SET @de = GETDATE()
	INSERT INTO TestRuns(Description, StartAt, EndAt) Values (N'Test ' + CONVERT(VARCHAR(5), @testid) + N' Finished', @ds, @de)

	DECLARE @TestRunID INT

	SELECT @TestRunID = MAX(TestRuns.TestRunID) FROM TestRuns

	OPEN table_cursor

	FETCH NEXT FROM table_cursor INTO @TableID, @NoOfRows
	WHILE @@FETCH_STATUS = 0
	BEGIN
		INSERT INTO TestRunTables(TestRunID, TableID, StartAt, EndAt) Values (@TestRunID, @TableID, @ds, @de)
	
		FETCH NEXT FROM table_cursor INTO @TableID, @NoOfRows
	END

	CLOSE table_cursor

	DEALLOCATE table_cursor

	OPEN view_cursor

	FETCH NEXT FROM view_cursor INTO @ViewName, @ViewID
	WHILE @@FETCH_STATUS = 0
	BEGIN
		INSERT INTO TestRunViews(TestRunID, ViewID, StartAt, EndAt) Values (@TestRunID, @ViewID, @ds, @de)
		FETCH NEXT FROM view_cursor INTO @ViewName, @ViewID
	END 

	CLOSE view_cursor

	DEALLOCATE view_cursor
END

GO
CREATE PROCEDURE ADD_DATA(@TableID INT, @NoOfRows INT)
AS
BEGIN
	DECLARE @count INT
	DECLARE @fk INT
	DECLARE @new_id INT
	SET @count = 0
	IF @TableID = 1
	BEGIN
		SET @new_id = ISNULL((SELECT MAX(id) + 1 FROM ARMOR_SET), 0)
		WHILE @count < @NoOfRows
		BEGIN
			INSERT INTO ARMOR_SET(id, name, type, defense) VALUES (@new_id, CONVERT (VARCHAR(5), @new_id), CONVERT(VARCHAR(5), @new_id + 1), @new_id + 1)
			SET @count = @count + 1
			SET @new_id = @new_id + 1
		END
	END
	ELSE IF @TableID = 2
	BEGIN
		SET @new_id = ISNULL((SELECT MAX(id) + 1 FROM ARMOR_ENHANCEMENT), 0)
		WHILE @count < @NoOfRows
		BEGIN
			SELECT TOP 1 @fk = id FROM ARMOR_SET ORDER BY NEWID()
			INSERT INTO ARMOR_ENHANCEMENT(id, name, extra_defense, armor_id) VALUES (@new_id, CONVERT (VARCHAR(5), @new_id), @new_id + 1, @fk)
			SET @count = @count + 1
			SET @new_id = @new_id + 1
		END
	END
	ELSE IF @TableID = 3
	BEGIN
		SET @new_id = ISNULL((SELECT MAX(id) + 1 FROM PET), 0)
		WHILE @count < @NoOfRows
		BEGIN
			INSERT INTO PET(id, name) VALUES (@new_id, CONVERT (VARCHAR(5), @new_id))
			SET @count = @count + 1
			SET @new_id = @new_id + 1
		END
	END
END
GO

CREATE PROCEDURE DELETE_DATA(@TableID INT, @NoOfRows INT)
AS
BEGIN
	DECLARE @count INT
	DECLARE @id INT
	SET @count = 0
	IF @TableID = 1
	BEGIN
		SET @id = ISNULL((SELECT MAX(id) FROM ARMOR_SET), -1)
		WHILE @count < @NoOfRows AND @id >= 0
		BEGIN
			DELETE FROM ARMOR_SET WHERE id = @id
			SET @count = @count + 1
			SET @id = @id - 1
		END
	END
	ELSE IF @TableID = 2
	BEGIN
		SET @id = ISNULL((SELECT MAX(id) FROM ARMOR_ENHANCEMENT), -1)
		WHILE @count < @NoOfRows AND @id >= 0
		BEGIN
			DELETE FROM ARMOR_ENHANCEMENT WHERE id = @id
			SET @count = @count + 1
			SET @id = @id - 1
		END
	END
	ELSE IF @TableID = 3
	BEGIN
		SET @id = ISNULL((SELECT MAX(id) FROM PET), -1)
		WHILE @count < @NoOfRows AND @id >= 0
		BEGIN
			DELETE FROM PET WHERE id = @id
			SET @count = @count + 1
			SET @id = @id - 1
		END
	END
END

DROP PROCEDURE RUN_TEST
DROP PROCEDURE DELETE_DATA
DROP PROCEDURE ADD_DATA

DELETE FROM ARMOR_ENHANCEMENT
DELETE FROM ARMOR_SET
DELETE FROM PET

EXEC ADD_DATA @TableID = 1, @NoOfRows = 100
EXEC DELETE_DATA @TableID = 1, @NoOfRows = 100
EXEC ADD_DATA @TableID = 2, @NoOfRows = 100
EXEC DELETE_DATA @TableID = 2, @NoOfRows = 100
EXEC ADD_DATA @TableID = 3, @NoOfRows = 100
EXEC DELETE_DATA @TableID = 3, @NoOfRows = 100

SELECT * FROM ARMOR_SET
SELECT * FROM ARMOR_ENHANCEMENT
SELECT * FROM PET

SELECT * FROM TestRuns
SELECT * FROM TestRunTables
SELECT * FROM TestRunViews

DELETE FROM TestRuns
DELETE FROM TestRunTables
DELETE FROM TestRunViews

EXEC RUN_TEST @testid = 3
