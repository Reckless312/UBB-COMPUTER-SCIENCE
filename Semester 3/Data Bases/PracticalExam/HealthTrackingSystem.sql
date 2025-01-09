--Users --> name, age, gender, unique names
--Activities --> name, nr of calories burned / hour, names are unique
--Meals --> name, nr of calories per serving, names are unique
--Health Metrics --> user, date of recording, weight, blood preasure, heart rate
--User Activities Journal --> user, activity, date of recording, duration

CREATE TABLE Users(
	name VARCHAR(50) PRIMARY KEY,
	age INT,
	gender VARCHAR(25),
)

CREATE TABLE Activities(
	name VARCHAR(50) PRIMARY KEY,
	calories_burned_per_hour INT,
)

CREATE TABLE Meals(
	name VARCHAR(50) PRIMARY KEY,
	calories_per_serving INT,
)

CREATE TABLE HealthMetrics(
	user_name VARCHAR(50) FOREIGN KEY REFERENCES Users(name),
	date_of_recording DATE,
	weight REAL,
	blood_preasure INT,
	heart_rate INT,
)

CREATE TABLE UserActivitiesJournal(
	user_name VARCHAR(50) FOREIGN KEY REFERENCES Users(name),
	activity_name VARCHAR(50) FOREIGN KEY REFERENCES Activities(name),
	date_of_recording DATE,
	duration INT,
)

GO
CREATE PROCEDURE addMetrics (@user_name VARCHAR(50), @date_of_recording DATE, @weight REAL, @blood_preasure INT, @heart_rate INT)
AS
BEGIN
	IF @date_of_recording > GETDATE()
	BEGIN
		RAISERROR ('Inserted date is not valid!', 10, 1)
	END
	ELSE
	BEGIN
		INSERT INTO HealthMetrics(user_name, date_of_recording, weight, blood_preasure, heart_rate) VALUES (@user_name, @date_of_recording, @weight, @blood_preasure, @heart_rate)
	END
END
GO

CREATE VIEW VIEW_1 AS
	SELECT user_name, AVG(weight) AverageWeight, MAX(blood_preasure)MaximumBloodPreasure FROM HealthMetrics WHERE date_of_recording > '2022-12-31' AND date_of_recording < '2024-01-01' GROUP BY user_name
GO

CREATE FUNCTION AverageDuration(@user VARCHAR(50), @activity VARCHAR(50))
RETURNS INT AS
BEGIN
	DECLARE @result INT
	SELECT @result = AVG(duration) FROM UserActivitiesJournal WHERE UserActivitiesJournal.user_name = @user AND UserActivitiesJournal.activity_name = @activity
	RETURN @result
END
GO

INSERT INTO Users(name, age, gender) VALUES ('Name_1', 15, 'female')

EXEC addMetrics @user_name = 'Name_1', @date_of_recording = '2023-05-15', @weight = 54, @blood_preasure = 90, @heart_rate = 67
--misspelled pressure

SELECT * FROM HealthMetrics

INSERT INTO Users(name, age, gender) VALUES ('Name_2', 17, 'male')

EXEC addMetrics @user_name = 'Name_2', @date_of_recording = '2023-01-30', @weight = 58, @blood_preasure = 91, @heart_rate = 64
EXEC addMetrics @user_name = 'Name_2', @date_of_recording = '2024-07-28', @weight = 62, @blood_preasure = 90, @heart_rate = 63

SELECT * FROM VIEW_1

INSERT INTO Activities(name, calories_burned_per_hour) VALUES ('Running', 360)
INSERT INTO Activities(name, calories_burned_per_hour) VALUES ('Gym', 120)

INSERT INTO UserActivitiesJournal(user_name, activity_name, date_of_recording, duration) VALUES ('Name_1', 'Running', '2023-02-25', 33)
INSERT INTO UserActivitiesJournal(user_name, activity_name, date_of_recording, duration) VALUES ('Name_1', 'Running', '2023-02-26', 67)

GO
SELECT dbo.AverageDuration ('Name_1', 'Running') as AverageDuration