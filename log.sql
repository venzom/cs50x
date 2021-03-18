-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Crime took place on July 28, 2020 and took place on Chamberlin Street

-- Used to see all tables in colums in database
.schema

-- .tables to see a shorter list of just all the tables
.tables

-- See if street matches Chamberlin Street
SELECT street FROM crime_scene_reports;

-- Read descritption of crime report from Chamberlin Street on 07/28
SELECT description FROM crime_scene_reports 
WHERE street = "Chamberlin Street"
AND month = 7 AND day = 28; 
-- 3 witnesses were present and interview transcript mentions the courthouse

-- Grab ID of crime for ease of use
SELECT id FROM crime_scene_reports 
WHERE street = "Chamberlin Street"
AND month = 7 AND day = 28; 
-- id of report = 295

-- List information from interviews from July 28
SELECT * FROM interviews
WHERE month = 7 AND day = 28 and year = 2020; 
-- 161 | Ruth | Criminal got into car in Courthouse parking, check footage from 10:15 to 10:30
-- 162 | Eugene | Thief recognized, withdrew from ATM on Fifer street, before 10:15
-- 163 | Raymond | Thief on phone, less than minute, earliest flight out of Fiftyville next day.
--                 Thief asked person to purchase flight tickets

-- Check for airports in Fiftyville and for first flight next day sorted by earliest
SELECT * FROM flights
WHERE origin_airport_id = 
(SELECT id FROM airports 
WHERE city = "Fiftyville")
AND year = 2020 
AND month = 7
AND day = 29
ORDER BY hour ASC, minute;
-- Earliest flight information listed below
-- id | origin_airport_id | destination_airport_id | year | month | day | hour | minute
-- 36 |         8         |            4           | 2020 |   7   | 29  |  8   | 20

-- Find destination based on earliest flight
SELECT city FROM airports WHERE id = 4;
-- Thief escaping to London