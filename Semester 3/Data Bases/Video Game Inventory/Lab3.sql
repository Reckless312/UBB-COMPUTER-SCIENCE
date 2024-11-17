CREATE TABLE DATABASE_VERSIONS(
	id INT PRIMARY KEY,
	to_update NVARCHAR(MAX),
	to_rollback NVARCHAR(MAX)
);
GO

CREATE TABLE CURRENT_VERSION(
	id INT
);
GO

CREATE PROCEDURE MODIFY_COLUMN(@table_name NVARCHAR(128), @column_name NVARCHAR(128), @new_type NVARCHAR(128))
AS
BEGIN
	BEGIN TRY
		DECLARE @sql NVARCHAR(MAX);
		DECLARE @sql2 NVARCHAR(MAX);

		DECLARE @current_type NVARCHAR(MAX);
		DECLARE @length NVARCHAR(MAX);

		DECLARE @current_version INT;

		SELECT @current_type = DATA_TYPE FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = @table_name AND COLUMN_NAME = @column_name

		IF @length IS NULL
		BEGIN
			SET @length = N'';
		END
		ELSE
		BEGIN
			SET @length = N'(' + @length + N')';
		END

		SET @sql = N'ALTER TABLE ' + QUOTENAME(@table_name) + N' ALTER COLUMN ' + QUOTENAME(@column_name) + N' ' + @new_type;
		SET @sql2 = N'ALTER TABLE ' + QUOTENAME(@table_name) + N' ALTER COLUMN ' + QUOTENAME(@column_name) + N' ' + @current_type + @length;

		EXEC sp_executesql @sql;

		SELECT @current_version = id FROM CURRENT_VERSION;
		DELETE FROM DATABASE_VERSIONS WHERE id > @current_version;

		SET @current_version = @current_version + 1
		UPDATE CURRENT_VERSION SET id = @current_version

		INSERT INTO DATABASE_VERSIONS(id, to_update, to_rollback) VALUES (@current_version, @sql, @sql2);
	END TRY
	BEGIN CATCH
		PRINT ERROR_MESSAGE()
	END CATCH
END
GO

CREATE PROCEDURE ADD_COLUMN(@table_name NVARCHAR(128), @column_name NVARCHAR(128), @new_type NVARCHAR(128))
AS
BEGIN
	BEGIN TRY
		DECLARE @sql NVARCHAR(MAX);
		DECLARE @sql2 NVARCHAR(MAX);

		DECLARE @current_version INT;

		SET @sql = N'ALTER TABLE ' + QUOTENAME(@table_name) + N' ADD ' + QUOTENAME(@column_name) + N' ' + @new_type;
		SET @sql2 = N'ALTER TABLE ' + QUOTENAME(@table_name) + N' DROP COLUMN ' + QUOTENAME(@column_name);

		EXEC sp_executesql @sql;

		SELECT @current_version = id FROM CURRENT_VERSION;
		DELETE FROM DATABASE_VERSIONS WHERE id > @current_version;

		SET @current_version = @current_version + 1
		UPDATE CURRENT_VERSION SET id = @current_version

		INSERT INTO DATABASE_VERSIONS(id, to_update, to_rollback) VALUES (@current_version, @sql, @sql2);
	END TRY
	BEGIN CATCH
		PRINT ERROR_MESSAGE()
	END CATCH
END
GO

CREATE PROCEDURE DELETE_COLUMN(@table_name NVARCHAR(128), @column_name NVARCHAR(128))
AS
BEGIN
	BEGIN TRY
		DECLARE @sql NVARCHAR(MAX);
		DECLARE @sql2 NVARCHAR(MAX);

		DECLARE @current_type NVARCHAR(MAX);
		DECLARE @length NVARCHAR(MAX);

		DECLARE @current_version INT;

		SELECT @current_type = DATA_TYPE, @length = CAST(CHARACTER_MAXIMUM_LENGTH AS NVARCHAR) FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = @table_name AND COLUMN_NAME = @column_name

		SET @length = ISNULL(N'(' + @length + N')', N'')

		SET @sql = N'ALTER TABLE ' + QUOTENAME(@table_name) + N' DROP COLUMN ' + QUOTENAME(@column_name);
		SET @sql2 = N'ALTER TABLE ' + QUOTENAME(@table_name) + N' ADD ' + QUOTENAME(@column_name) + N' ' + @current_type + @length;

		EXEC sp_executesql @sql;

		SELECT @current_version = id FROM CURRENT_VERSION;
		DELETE FROM DATABASE_VERSIONS WHERE id > @current_version;

		SET @current_version = @current_version + 1
		UPDATE CURRENT_VERSION SET id = @current_version

		INSERT INTO DATABASE_VERSIONS(id, to_update, to_rollback) VALUES (@current_version, @sql, @sql2);
	END TRY
	BEGIN CATCH
		PRINT ERROR_MESSAGE()
	END CATCH
END
GO

CREATE PROCEDURE ADD_DEFAULT_CONSTRAINT(@table_name NVARCHAR(128), @constraint_name NVARCHAR(128), @column_name NVARCHAR(128), @default_value NVARCHAR(128))
AS
BEGIN
	BEGIN TRY
		DECLARE @sql NVARCHAR(MAX);
		DECLARE @sql2 NVARCHAR(MAX);

		DECLARE @current_version INT;

		SET @sql = N'ALTER TABLE ' + QUOTENAME(@table_name) + N' ADD CONSTRAINT ' + QUOTENAME(@constraint_name) + N' DEFAULT ' + @default_value + N' FOR ' + QUOTENAME(@column_name);
		SET @sql2 = N'ALTER TABLE ' + QUOTENAME(@table_name) + N' DROP CONSTRAINT ' + QUOTENAME(@constraint_name);

		EXEC sp_executesql @sql;

		SELECT @current_version = id FROM CURRENT_VERSION;
		DELETE FROM DATABASE_VERSIONS WHERE id > @current_version;

		SET @current_version = @current_version + 1
		UPDATE CURRENT_VERSION SET id = @current_version

		INSERT INTO DATABASE_VERSIONS(id, to_update, to_rollback) VALUES (@current_version, @sql, @sql2);
	END TRY
	BEGIN CATCH
		PRINT ERROR_MESSAGE()
	END CATCH
END
GO

CREATE PROCEDURE REMOVE_CONSTRAINT(@table_name NVARCHAR(128), @constraint_name NVARCHAR(128))
AS
BEGIN
	BEGIN TRY
		DECLARE @sql NVARCHAR(MAX);
		DECLARE @sql2 NVARCHAR(MAX);

		DECLARE @current_constraint NVARCHAR(MAX);
		DECLARE @current_column NVARCHAR(MAX);

		DECLARE @current_version INT;
		DECLARE @default_value NVARCHAR(MAX);

		SELECT @current_constraint = CONSTRAINT_TYPE FROM INFORMATION_SCHEMA.TABLE_CONSTRAINTS WHERE TABLE_NAME = @table_name AND CONSTRAINT_NAME = @constraint_name;

		IF @current_constraint IS NULL
		BEGIN
			SELECT @default_value = definition FROM sys.default_constraints WHERE NAME = @constraint_name;

			IF @default_value IS NOT NULL
			BEGIN
				SET @current_constraint = N'DEFAULT';
			END
		END

		SELECT @current_column = STRING_AGG(COLUMN_NAME, ',') FROM INFORMATION_SCHEMA.KEY_COLUMN_USAGE WHERE TABLE_NAME = @table_name AND CONSTRAINT_NAME = @constraint_name;

		SET @sql = N'ALTER TABLE ' + QUOTENAME(@table_name) + N' DROP CONSTRAINT ' + QUOTENAME(@constraint_name);

		IF @current_constraint = N'DEFAULT'
		BEGIN
			SELECT @current_column = c.name FROM sys.default_constraints AS dc INNER JOIN sys.tables AS t ON dc.parent_object_id = t.object_id INNER JOIN sys.schemas AS s ON t.schema_id = s.schema_id INNER JOIN sys.columns AS c ON c.default_object_id = dc.object_id WHERE s.name = 'dbo' AND t.name = @table_name AND dc.name = @constraint_name;

			SET @sql2 = N'ALTER TABLE ' + QUOTENAME(@table_name) + N' ADD CONSTRAINT ' + QUOTENAME(@constraint_name) + N' DEFAULT ' + @default_value + N' FOR ' + QUOTENAME(@current_column);
		END
		ELSE IF @current_constraint = N'PRIMARY KEY'
		BEGIN
			SET @sql2 = N'ALTER TABLE ' + QUOTENAME(@table_name) + N' ADD CONSTRAINT ' + QUOTENAME(@constraint_name) + N' PRIMARY KEY (' + QUOTENAME(@current_column) + N')';
		END
		ELSE IF @current_constraint = N'FOREIGN KEY'
		BEGIN
			DECLARE @other_table NVARCHAR(MAX);
			DECLARE @other_column NVARCHAR(MAX);

			CREATE TABLE #ForeignKeyInfo (
				PKTABLE_QUALIFIER NVARCHAR(128),
				PKTABLE_OWNER NVARCHAR(128),
				PKTABLE_NAME NVARCHAR(128),
				PKCOLUMN_NAME NVARCHAR(128),
				FKTABLE_QUALIFIER NVARCHAR(128),
				FKTABLE_OWNER NVARCHAR(128),
				FKTABLE_NAME NVARCHAR(128),
				FKCOLUMN_NAME NVARCHAR(128),
				KEY_SEQ SMALLINT,
				UPDATE_RULE SMALLINT,
				DELETE_RULE SMALLINT,
				FK_NAME NVARCHAR(128),
				PK_NAME NVARCHAR(128),
				DEFERRABILITY SMALLINT
			);

			INSERT INTO #ForeignKeyInfo
			EXEC sp_fkeys @fktable_name = @table_name

			SELECT @other_table = PKTABLE_NAME, @other_column = PKCOLUMN_NAME FROM #ForeignKeyInfo WHERE FK_NAME = @constraint_name

			SET @sql2 = N'ALTER TABLE ' + QUOTENAME(@table_name) + N' ADD CONSTRAINT ' + QUOTENAME(@constraint_name) + N' FOREIGN KEY (' + QUOTENAME(@current_column) + N') REFERENCES ' + QUOTENAME(@other_table) + N'(' + QUOTENAME(@other_column) + N')';
		END
		ELSE IF @current_constraint = N'UNIQUE'
		BEGIN 
			SET @sql2 = N'ALTER TABLE ' + QUOTENAME(@table_name) + N' ADD CONSTRAINT ' + QUOTENAME(@constraint_name) + N' UNIQUE (' + QUOTENAME(@current_column) + N')';
		END

		EXEC sp_executesql @sql;

		SELECT @current_version = id FROM CURRENT_VERSION;
		DELETE FROM DATABASE_VERSIONS WHERE id > @current_version;

		SET @current_version = @current_version + 1
		UPDATE CURRENT_VERSION SET id = @current_version

		INSERT INTO DATABASE_VERSIONS(id, to_update, to_rollback) VALUES (@current_version, @sql, @sql2);
	END TRY
	BEGIN CATCH
		PRINT ERROR_MESSAGE()
	END CATCH
END
GO

CREATE PROCEDURE ADD_PRIMARY_KEY(@table_name NVARCHAR(128),@constraint_name NVARCHAR(128), @column_name NVARCHAR(128))
AS
BEGIN
	BEGIN TRY
		DECLARE @sql NVARCHAR(MAX);
		DECLARE @sql2 NVARCHAR(MAX);

		DECLARE @current_version INT;

		SET @sql = N'ALTER TABLE ' + QUOTENAME(@table_name) + N' ADD CONSTRAINT ' + QUOTENAME(@constraint_name) + N' PRIMARY KEY (' + QUOTENAME(@column_name) + N')';
		SET @sql2 = N'ALTER TABLE ' + QUOTENAME(@table_name) + N' DROP CONSTRAINT ' + QUOTENAME(@constraint_name);

		EXEC sp_executesql @sql;

		SELECT @current_version = id FROM CURRENT_VERSION;
		DELETE FROM DATABASE_VERSIONS WHERE id > @current_version;

		SET @current_version = @current_version + 1
		UPDATE CURRENT_VERSION SET id = @current_version

		INSERT INTO DATABASE_VERSIONS(id, to_update, to_rollback) VALUES (@current_version, @sql, @sql2);
	END TRY
	BEGIN CATCH
		PRINT ERROR_MESSAGE()
	END CATCH
END
GO

CREATE PROCEDURE ADD_CANDIDATE_KEY(@table_name NVARCHAR(128), @column_name NVARCHAR(128), @constraint_name NVARCHAR(128))
AS
BEGIN
	BEGIN TRY
		DECLARE @sql NVARCHAR(MAX);
		DECLARE @sql2 NVARCHAR(MAX);

		DECLARE @current_version INT;

		SET @sql = N'ALTER TABLE ' + QUOTENAME(@table_name) + N' ADD CONSTRAINT ' + QUOTENAME(@constraint_name) + N' UNIQUE (' + QUOTENAME(@column_name) + N')';
		SET @sql2 = N'ALTER TABLE ' + QUOTENAME(@table_name) + N' DROP CONSTRAINT ' + QUOTENAME(@constraint_name);

		EXEC sp_executesql @sql;

		SELECT @current_version = id FROM CURRENT_VERSION;
		DELETE FROM DATABASE_VERSIONS WHERE id > @current_version;

		SET @current_version = @current_version + 1
		UPDATE CURRENT_VERSION SET id = @current_version

		INSERT INTO DATABASE_VERSIONS(id, to_update, to_rollback) VALUES (@current_version, @sql, @sql2);
	END TRY
	BEGIN CATCH
		PRINT ERROR_MESSAGE()
	END CATCH
END
GO

CREATE PROCEDURE ADD_FOREIGN_KEY(@table_name NVARCHAR(128), @constraint_name NVARCHAR(128), @column_name NVARCHAR(128), @other_table_name NVARCHAR(128), @other_column_name NVARCHAR(128))
AS
BEGIN
	BEGIN TRY
		DECLARE @sql NVARCHAR(MAX);
		DECLARE @sql2 NVARCHAR(MAX);

		DECLARE @current_version INT;

		SET @sql = N'ALTER TABLE ' + QUOTENAME(@table_name) + N' ADD CONSTRAINT ' + QUOTENAME(@constraint_name) + N' FOREIGN KEY (' + QUOTENAME(@column_name) + N') REFERENCES ' + QUOTENAME(@other_table_name) + N'(' + QUOTENAME(@other_column_name) + N')';
		SET @sql2 = N'ALTER TABLE ' + QUOTENAME(@table_name) + N' DROP CONSTRAINT ' + QUOTENAME(@constraint_name);

		EXEC sp_executesql @sql;

		SELECT @current_version = id FROM CURRENT_VERSION;
		DELETE FROM DATABASE_VERSIONS WHERE id > @current_version;

		SET @current_version = @current_version + 1
		UPDATE CURRENT_VERSION SET id = @current_version

		INSERT INTO DATABASE_VERSIONS(id, to_update, to_rollback) VALUES (@current_version, @sql, @sql2);
	END TRY
	BEGIN CATCH
		PRINT ERROR_MESSAGE()
	END CATCH
END
GO

CREATE PROCEDURE CREATE_TABLE(@table_name NVARCHAR(128), @columns_and_datatype NVARCHAR(MAX))
AS
BEGIN
	BEGIN TRY
		DECLARE @sql NVARCHAR(MAX);
		DECLARE @sql2 NVARCHAR(MAX);

		DECLARE @current_version INT;

		SET @sql = N'CREATE TABLE ' + QUOTENAME(@table_name) +  N' (' + @columns_and_datatype + N')';
		SET @sql2 = N'DROP TABLE ' + QUOTENAME(@table_name);

		EXEC sp_executesql @sql;

		SELECT @current_version = id FROM CURRENT_VERSION;
		DELETE FROM DATABASE_VERSIONS WHERE id > @current_version;

		SET @current_version = @current_version + 1
		UPDATE CURRENT_VERSION SET id = @current_version

		INSERT INTO DATABASE_VERSIONS(id, to_update, to_rollback) VALUES (@current_version, @sql, @sql2);
	END TRY
	BEGIN CATCH
		PRINT ERROR_MESSAGE()
	END CATCH
END
GO

CREATE PROCEDURE DROP_TABLE(@table_name NVARCHAR(128))
AS
BEGIN
	BEGIN TRY
		DECLARE @sql NVARCHAR(MAX);
		DECLARE @sql2 NVARCHAR(MAX);

		DECLARE @columns_and_datatype NVARCHAR(MAX);

		DECLARE @current_version INT;

		SELECT @columns_and_datatype = STRING_AGG(COLUMN_NAME + ' ' + DATA_TYPE + ISNULL(N'(' + CAST(CHARACTER_MAXIMUM_LENGTH AS NVARCHAR) + N')', N'') , ', ') FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = @table_name

		SET @sql = N'DROP TABLE ' + QUOTENAME(@table_name);
		SET @sql2 = N'CREATE TABLE ' + QUOTENAME(@table_name) +  N' (' + @columns_and_datatype + N')';

		EXEC sp_executesql @sql;

		SELECT @current_version = id FROM CURRENT_VERSION;
		DELETE FROM DATABASE_VERSIONS WHERE id > @current_version;

		SET @current_version = @current_version + 1
		UPDATE CURRENT_VERSION SET id = @current_version

		INSERT INTO DATABASE_VERSIONS(id, to_update, to_rollback) VALUES (@current_version, @sql, @sql2);
	END TRY
	BEGIN CATCH
		PRINT ERROR_MESSAGE()
	END CATCH
END
GO

CREATE PROCEDURE REVERTBACK(@version INT)
AS
BEGIN
	DECLARE @current_version INT;

	SELECT @current_version = id FROM CURRENT_VERSION;

	WHILE @current_version < @version AND @current_version < (SELECT MAX(id) FROM DATABASE_VERSIONS)
	BEGIN
		DECLARE @to_update NVARCHAR(MAX);

		SET @current_version = @current_version + 1

		SELECT @to_update = to_update FROM DATABASE_VERSIONS WHERE id = @current_version

		EXEC sp_executesql @to_update;

		UPDATE CURRENT_VERSION SET id = @current_version;
	END

	WHILE @current_version > @version AND @current_version > 0
	BEGIN
		DECLARE @to_rollback NVARCHAR(MAX);

		SELECT @to_rollback = to_rollback FROM DATABASE_VERSIONS WHERE id = @current_version

		SET @current_version = @current_version - 1

		EXEC sp_executesql @to_rollback;

		UPDATE CURRENT_VERSION SET id = @current_version;
	END
END
GO

DROP PROCEDURE CREATE_TABLE;
DROP PROCEDURE REVERTBACK;
DROP PROCEDURE ADD_CANDIDATE_KEY;
DROP PROCEDURE ADD_COLUMN;
DROP PROCEDURE ADD_DEFAULT_CONSTRAINT;
DROP PROCEDURE ADD_FOREIGN_KEY;
DROP PROCEDURE ADD_PRIMARY_KEY;
DROP PROCEDURE REMOVE_CONSTRAINT;
DROP PROCEDURE DROP_TABLE;
DROP PROCEDURE DELETE_COLUMN;
DROP PROCEDURE MODIFY_COLUMN;
DROP TABLE DATABASE_VERSIONS;
DROP TABLE CURRENT_VERSION
INSERT CURRENT_VERSION(id) VALUES(0)
SELECT * FROM DATABASE_VERSIONS;
SELECT * FROM CURRENT_VERSION;
GO

EXEC REVERTBACK @version = 1;
GO

EXEC CREATE_TABLE @table_name = N'test', @columns_and_datatype = N'column1 INT, column2 VARCHAR(50)'; 
GO

EXEC DROP_TABLE @table_name = N'test'; 
GO

EXEC MODIFY_COLUMN @table_name = N'test', @column_name = N'column1', @new_type = N'VARCHAR(50)'
GO

EXEC ADD_COLUMN @table_name = N'test', @column_name = N'column3', @new_type = N'NVARCHAR(50)'
GO

EXEC DELETE_COLUMN @table_name = N'test', @column_name = N'column3'
GO

EXEC ADD_DEFAULT_CONSTRAINT @table_name = N'test', @constraint_name = N'default1', @column_name = N'column1', @default_value = N'0'
GO

SELECT object_definition(default_object_id) AS definition
FROM   sys.columns
WHERE  name      ='column1'
AND    object_id = object_id('test')

ALTER TABLE test ALTER COLUMN column1 int not null

EXEC ADD_PRIMARY_KEY @table_name = N'test', @constraint_name = N'primary2', @column_name = N'column1'
GO

EXEC ADD_CANDIDATE_KEY @table_name = N'test', @column_name = N'column2', @constraint_name = N'candidate1'
GO

EXEC CREATE_TABLE @table_name = N'test2', @columns_and_datatype = N'column1 INT, column2 VARCHAR(50), column3 NVARCHAR(50)'; 
GO

ALTER TABLE test2 ALTER COLUMN column3 int not null

EXEC ADD_PRIMARY_KEY @table_name = N'test2', @constraint_name = N'primary1', @column_name = N'column3'
GO

EXEC ADD_FOREIGN_KEY @table_name = N'test', @column_name = N'column3', @constraint_name = N'foreign1', @other_table_name = N'test2', @other_column_name = N'column3';
GO

EXEC REMOVE_CONSTRAINT @table_name = N'test', @constraint_name = N'foreign1'
GO

EXEC sp_fkeys @fktable_name = N'test'
GO

EXEC REMOVE_CONSTRAINT @table_name = N'test', @constraint_name = N'default1'
GO

EXEC REMOVE_CONSTRAINT @table_name = N'test', @constraint_name = N'candidate1'
GO

EXEC REMOVE_CONSTRAINT @table_name = N'test', @constraint_name = N'primary2'
GO
