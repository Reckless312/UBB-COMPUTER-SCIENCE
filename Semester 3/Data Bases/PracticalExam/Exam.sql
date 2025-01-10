CREATE TABLE Country(
	name VARCHAR(50) PRIMARY KEY,
)

CREATE TABLE Athletes(
	name VARCHAR(50) PRIMARY KEY,
	country VARCHAR(50) FOREIGN KEY REFERENCES Country(name),
	date_of_birth DATE
)

CREATE TABLE Sports(
	name VARCHAR(50) PRIMARY KEY,
)

CREATE TABLE SportEvent(
	id INT PRIMARY KEY,
	sport_name VARCHAR(50) FOREIGN KEY REFERENCES Sports(name),
	description VARCHAR(50),
)

CREATE TABLE Results(
	athlete_name VARCHAR(50) FOREIGN KEY REFERENCES Athletes(name),
	sport_event_id INT FOREIGN KEY REFERENCES SportEvent(id),
	date DATE,
	final_rank INT,
	description VARCHAR(4) CHECK (description = 'PB' OR description = 'WR' OR description = 'N/A')
)

GO
CREATE PROCEDURE addResult(@athlete_name VARCHAR(50), @sport_event_id INT, @date DATE, @final_rank INT, @description VARCHAR(4))
AS
BEGIN
	IF EXISTS (SELECT * FROM Results WHERE athlete_name = @athlete_name AND sport_event_id = @sport_event_id)
	BEGIN
		UPDATE Results SET date = @date, final_rank = @final_rank, description = @description WHERE athlete_name = @athlete_name AND sport_event_id = @sport_event_id 
	END
	ELSE
	BEGIN
		INSERT INTO Results(athlete_name, sport_event_id, date, final_rank, description) VALUES (@athlete_name, @sport_event_id, @date, @final_rank, @description)
	END
END
GO

CREATE VIEW VIEW_1
AS
	SELECT country gold FROM Athletes INNER JOIN Results ON Results.athlete_name = Athletes.name WHERE final_rank = 1 GROUP BY country ORDER BY COUNT(*)
	UNION ALL
	SELECT country silver FROM Athletes INNER JOIN Results ON Results.athlete_name = Athletes.name WHERE final_rank = 2 GROUP BY country ORDER BY COUNT(*)
GO

CREATE FUNCTION athletesParticipated(@R INT)
RETURNS INT AS
BEGIN
	DECLARE @result INT
	SELECT @result = COUNT(*) FROM (SELECT athlete_name FROM Results GROUP BY athlete_name HAVING COUNT(*) > @R) AS R
	RETURN @result
END