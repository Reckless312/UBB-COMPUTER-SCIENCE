--Train --> name, train_type
--TrainTypes --> name, description
--Stations --> name, unique
--Routes --> name, associated train
--RouteLinkedStations --> route, station, departure time, arival time

CREATE TABLE TrainTypes(
	name VARCHAR(50) PRIMARY KEY,
	description VARCHAR(50),
)

CREATE TABLE Train(
	name VARCHAR(50) PRIMARY KEY,
	train_type VARCHAR(50) FOREIGN KEY REFERENCES TrainTypes(name),
)

CREATE TABLE Stations(
	name VARCHAR(50) PRIMARY KEY
)

CREATE TABLE Routes(
	name VARCHAR(50) PRIMARY KEY,
	train VARCHAR(50) FOREIGN KEY REFERENCES Train(name)
)

CREATE TABLE RouteLinkedStations(
	route VARCHAR(50) FOREIGN KEY REFERENCES Routes(name),
	station VARCHAR(50) FOREIGN KEY REFERENCES Stations(name),
	departure_time TIME,
	arival_time TIME,
)

GO
CREATE PROCEDURE addStationToRoute(@route VARCHAR(50), @station VARCHAR(50), @departure_time TIME, @arival_time TIME)
AS
BEGIN
	IF EXISTS (SELECT * FROM RouteLinkedStations RS WHERE RS.route = @route AND RS.station = @station)
	BEGIN
		UPDATE RouteLinkedStations SET departure_time = @departure_time, arival_time = @arival_time WHERE route = @route AND station = @station
	END
	ELSE
	BEGIN
		INSERT INTO RouteLinkedStations(route, station, departure_time, arival_time) VALUES (@route, @station, @departure_time, @arival_time)
	END
END
GO
CREATE VIEW VIEW_1
AS
	SELECT route FROM RouteLinkedStations GROUP BY route HAVING COUNT(*) = (SELECT COUNT(*) total FROM Stations)
GO

CREATE FUNCTION printStationsWithMoreThanGivenNrOfRoutes(@R INT)
RETURNS TABLE
AS
	RETURN SELECT station FROM RouteLinkedStations GROUP BY station HAVING COUNT(*) > @R
GO

INSERT INTO TrainTypes (name, description) VALUES ('Type_1', 'Description_1')
INSERT INTO Train(name, train_type) VALUES('Train_1', 'Type_1')
INSERT INTO Stations(name) VALUES('Station_1')
INSERT INTO Stations(name) VALUES('Station_2')
INSERT INTO Stations(name) VALUES('Station_3')
INSERT INTO Routes(name, train) VALUES('Route_1', 'Train_1')
INSERT INTO Routes(name, train) VALUES('Route_2', 'Train_1')
INSERT INTO RouteLinkedStations(route, station, departure_time, arival_time) VALUES ('Route_1', 'Station_1', '15:23', '16:04')
INSERT INTO RouteLinkedStations(route, station, departure_time, arival_time) VALUES ('Route_1', 'Station_2', '13:23', '03:04')
INSERT INTO RouteLinkedStations(route, station, departure_time, arival_time) VALUES ('Route_2', 'Station_1', '11:23', '07:04')
INSERT INTO RouteLinkedStations(route, station, departure_time, arival_time) VALUES ('Route_2', 'Station_2', '09:23', '14:04')
INSERT INTO RouteLinkedStations(route, station, departure_time, arival_time) VALUES ('Route_2', 'Station_3', '18:23', '20:04')

SELECT * FROM RouteLinkedStations

EXEC addStationToRoute @route = 'Route_1', @station = 'Station_3', @departure_time = '14:23', @arival_time = '15:04'

SELECT * FROM VIEW_1

SELECT * FROM printStationsWithMoreThanGivenNrOfRoutes(1)