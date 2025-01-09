--Museum -> name, opening year, a city, a country
--Exhibition -> name, description, belongs to a museum
--Tour -> name, a date, a name for the tour guide, ticket price, belongs to a museum
--Tourist -> name, surname, gender, age, (possible: number of ticket bought, rating given to the museum)

CREATE TABLE Museum (
	name VARCHAR(50) PRIMARY KEY,
	opening_year INT CHECK(opening_year >= 0),
	city VARCHAR(50),
	country VARCHAR(50)
)

CREATE TABLE Exhibition (
	name VARCHAR(50) PRIMARY KEY,
	description VARCHAR(200),
	museum_name VARCHAR(50) FOREIGN KEY REFERENCES Museum(name)
)

CREATE TABLE Tour(
	name VARCHAR(50) PRIMARY KEY,
	date DATE,
	tour_guide VARCHAR(50),
	ticket_price REAL,
	museum_name VARCHAR(50) FOREIGN KEY REFERENCES Museum(name)
)

CREATE TABLE Tourist(
	name VARCHAR(50),
	surname VARCHAR(50),
	gender VARCHAR(50),
	age INT
	CONSTRAINT PK_Tourist PRIMARY KEY(name, surname)
)

CREATE TABLE TouristAttended(
	tourist_name VARCHAR(50),
	tourist_surname VARCHAR(50),
	tour_name VARCHAR(50) FOREIGN KEY REFERENCES Tour(name),
	CONSTRAINT FK_TouristTour FOREIGN KEY (tourist_name, tourist_surname) REFERENCES Tourist(name, surname),
	tickets_bought INT,
	rating_given VARCHAR(25)
)


--  ADDS A TOURIST IF IT DIDN'T EXIST BEFORE, ELSE UPDATE THE TOURISTATTENDED TABLE
GO
CREATE PROCEDURE Attend(@tour_name VARCHAR(50), @tourist_name VARCHAR(50), @tourist_surname VARCHAR(50), @tickets_bought INT, @rating_given VARCHAR(50))
AS
BEGIN
	IF EXISTS (SELECT * FROM TouristAttended T WHERE T.tourist_name = @tourist_name AND T.tourist_surname = @tourist_surname AND T.tour_name = @tour_name)
	BEGIN
		UPDATE TouristAttended SET tickets_bought = tickets_bought + @tickets_bought, rating_given = @rating_given WHERE tourist_name = @tourist_name AND tourist_surname = @tourist_surname AND tour_name = @tour_name
	END
	ELSE
	BEGIN
		INSERT INTO TouristAttended(tourist_name, tourist_surname, tour_name, tickets_bought, rating_given) VALUES (@tourist_name, @tourist_surname, @tour_name, @tickets_bought, @rating_given)
	END
END

GO
CREATE VIEW VIEW_1 AS
	SELECT * FROM Exhibition WHERE museum_name = 'National Museum of Art and Science'
GO

CREATE FUNCTION list_tourists(@m INT)
RETURNS TABLE
AS
	RETURN
		SELECT tourist_name, SUM(tickets_bought) as total_tickets FROM TouristAttended GROUP BY tourist_name HAVING SUM(tickets_bought) > @m
GO


INSERT INTO Museum(name, opening_year, city, country) VALUES ('Museum_name_1', 2004, 'City_1', 'Country_1')
INSERT INTO Tour(name, date, tour_guide, ticket_price, museum_name) VALUES ('Tour_1', '2004-01-30','Guide_1', 3.5, 'Museum_name_1')
INSERT INTO Tourist(name, surname, age, gender) VALUES ('Name_1', 'Surname_1', 20, 'male') 
SELECT * FROM TouristAttended
--throws errors if the tour is not added or no tourist found 
EXEC Attend @tour_name = 'Tour_1', @tourist_name = 'Name_1', @tourist_surname = 'Surname_1', @tickets_bought = 2, @rating_given = 'very gooddd'


INSERT INTO Exhibition (name, description, museum_name) VALUES ('Exhibition_1', 'Description_1', 'Museum_name_1')
INSERT INTO Exhibition (name, description, museum_name) VALUES ('Exhibition_2', 'Description_1', 'National Museum of Art and Science')
INSERT INTO Museum(name, opening_year, city, country) VALUES ('National Museum of Art and Science', 2004, 'City_1', 'Country_1')
SELECT * FROM VIEW_1

SELECT * FROM list_tourists(6)