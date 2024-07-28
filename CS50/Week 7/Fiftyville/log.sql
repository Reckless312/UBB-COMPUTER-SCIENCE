-- Keep a log of any SQL queries you execute as you solve the mystery.
--Inspect crime Database
SELECT * FROM crime_scene_reports;
--Inspect crime on the day of the theft
SELECT * FROM crime_scene_reports WHERE day = 28 AND month = 7 AND year = 2023;
--Id of the crime: 295, TIME: 10:15 AM, LOCATION: Humphrey Street bakery, witnesses: 3, All witnesses point towards the bakery

--Checking the interviews from that day
SELECT * FROM interviews WHERE year = 2023 AND month = 7 AND day = 28;
--TO INSPECT: The thief left less 10 minutes after the theft into a car in the parking lot of the bakery
--TO INSPECT: Thief spotted the same day in the morning at ATM on Leggett Street, did a withdrawal, the bakery is Emma's
--TO INSPECT: Thief is planning to leave tomorrow, at the earliest flight, suspect has a helper which will buy the ticket, the phone lasted less than 1 minute, happened while leaving the bakery

--CHECKING ATM
SELECT * FROM atm_transactions WHERE year = 2023 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';
--FOUND 8 possible accounts

--CHECKING PHONE CALLS
SELECT * FROM phone_calls where year = 2023 AND month = 7 AND day = 28 AND duration <= 60;
--FOUND 10 possible calls

--CHECKING FLIGHTS
--AIRPORT OF Fiftyville: ID: 8, CSF
SELECT * FROM flights WHERE origin_airport_id = 8 AND year = 2023 AND month = 7 AND day = 29;
--FOUND: The thief will leave Fiftyville at 8:20 in the morning towards to LaGuardia Airport, NYC, id of flight = 36

--CHECKING BAKERY
SELECT * FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 AND 25; 
--FOUND: 8 vehicles left between that time

--Finding possible thiefs:
SELECT * FROM people WHERE phone_number IN (SELECT caller FROM phone_calls where year = 2023 AND month = 7 AND day = 28 AND duration <= 60);

--Finding possible license plates of those people:
SELECT * FROM bakery_security_logs WHERE license_plate IN(SELECT license_plate FROM people WHERE phone_number IN (SELECT caller FROM phone_calls where year = 2023 AND month = 7 AND day = 28 AND duration <= 60)) AND year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 AND 25;

--Found: 94KL13X, G412CB7, 322W7JE, 0NTHK55
--The thief is one of those 4 suspects Sofia, Diana, Kelsey, Bruce

--From the withdrawal:
SELECT * FROM bank_accounts WHERE person_id IN (SELECT id FROM people WHERE license_plate = '94KL13X' OR license_plate = 'G412CB7' OR license_plate = '322W7JE' OR license_plate = '0NTHK55');
--The possible thiefs are Bruce, Diana
--From the atm_transactions, both are found, with Bruce being the one earlier than Diana
--Creation Bruce: 2010, Diana: 2012

--From the possible helpers:
SELECT * FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls where year = 2023 AND month = 7 AND day = 28 AND duration <= 60);

--Check flight 36:
SELECT * FROM passengers WHERE flight_id = 36;

--Check if Bruce is on board:
SELECT * FROM people WHERE id = 686048
--BRUCE IS THE THIEF

--Knowing Bruce Information we can go back to the calls and plug in the number of the receiver:
SELECT * FROM people WHERE phone_number = '(375) 555-8161';
--ROBIN IS THE HELPING HAND

