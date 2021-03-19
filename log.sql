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
-- 161 | Ruth | Criminal got into car in Courthouse parking, check footage from 10:24 to 10:30
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
min
-- Find destination based on earliest flight
SELECT city FROM airports WHERE id = 4;
-- Thief escaping to London

-- Check footage from 10:24 to 10:30 for matching license plates
SELECT * FROM courthouse_security_logs
WHERE month = 7 AND day = 28 AND hour = 10
AND activity = "exit";
/* 3 Possible vehicles
id | year | month | day | hour | minute | activity | license_plate
260 | 2020 | 7 | 28 | 10 | 16 | exit | 5P2BI95
261 | 2020 | 7 | 28 | 10 | 18 | exit | 94KL13X
262 | 2020 | 7 | 28 | 10 | 18 | exit | 6P58WS2
263 | 2020 | 7 | 28 | 10 | 19 | exit | 4328GD8
264 | 2020 | 7 | 28 | 10 | 20 | exit | G412CB7
265 | 2020 | 7 | 28 | 10 | 21 | exit | L93JTIZ
266 | 2020 | 7 | 28 | 10 | 23 | exit | 322W7JE
267 | 2020 | 7 | 28 | 10 | 23 | exit | 0NTHK55
268 | 2020 | 7 | 28 | 10 | 35 | exit | 1106N58 */

-- Check people name based on licence plate
SELECT * FROM people WHERE license_plate = "8P9NEU9";
/* 3 Possible people
id     | name      | phone_number   | passport_number | license_plate
372684 | Alexander | (801) 555-9266 |                 | 8P9NEU9
606219 | Jessica   | (786) 555-5321 | 7118667746      | ET017P4
561160 | Kathryn   | (609) 555-5876 | 6121106406      | 4ZY7I8T */

-- Check ATM transactions on Fifer Street before on day of crime
SELECT account_number, transaction_type
FROM atm_transactions
WHERE year = 2020 AND month = 7 AND day = 28
AND atm_location = "Fifer Street"
AND transaction_type = "withdraw";

-- Match ATM transactions to account numbers to people to match with license plate
SELECT name, phone_number, license_plate FROM people WHERE id IN
    (SELECT person_id FROM bank_accounts WHERE account_number IN -- Query person id
        (SELECT account_number -- Query bank acount numbers
        FROM atm_transactions
        WHERE year = 2020 AND month = 7 AND day = 28
        AND atm_location = "Fifer Street"
        AND transaction_type = "withdraw"));
/* name | phone_number | license_plate
Bobby | (826) 555-1652 | 30G67EN
Elizabeth | (829) 555-5269 | L93JTIZ
Victoria | (338) 555-6650 | 8X428L0
Madison | (286) 555-6063 | 1106N58
Roy | (122) 555-4581 | QX4YZN3
Danielle | (389) 555-5198 | 4328GD8
Russell | (770) 555-1861 | 322W7JE
Ernest | (367) 555-5533 | 94KL13X */

-- Match license plates from courthouse to ATM transations
SELECT name, phone_number FROM people WHERE id IN
    (SELECT person_id FROM bank_accounts WHERE account_number IN -- Query person id
        (SELECT account_number -- Query bank acount numbers
        FROM atm_transactions
        WHERE year = 2020 AND month = 7 AND day = 28
        AND atm_location = "Fifer Street"
        AND transaction_type = "withdraw"))
    AND license_plate IN
        (SELECT license_plate FROM courthouse_security_logs
        WHERE month = 7 AND day = 28 AND hour = 10
        AND activity = "exit");
/*name | phone_number
Elizabeth | (829) 555-5269
Madison | (286) 555-6063
Danielle | (389) 555-5198
Russell | (770) 555-1861
Ernest | (367) 555-5533*/

-- Query phone calls less than a minute
SELECT caller, receiver FROM phone_calls
WHERE year = 2020 AND month = 7
AND day = 28 AND duration < 60;

-- Query names matching ATM transactions and license plates and caller
SELECT name FROM people WHERE id IN
    (SELECT person_id FROM bank_accounts WHERE account_number IN -- Query person id
        (SELECT account_number -- Query bank acount numbers
        FROM atm_transactions
        WHERE year = 2020 AND month = 7 AND day = 28
        AND atm_location = "Fifer Street"
        AND transaction_type = "withdraw"))
    AND license_plate IN
        (SELECT license_plate FROM courthouse_security_logs
        WHERE month = 7 AND day = 28 AND hour = 10
        AND activity = "exit")
    AND phone_number IN
        (SELECT caller FROM phone_calls
        WHERE year = 2020 AND month = 7
        AND day = 28 AND duration < 60);
-- NAMES Madison, Russell, Ernest

-- Query names matching ATM transactions and license plates and receiver
SELECT name, phone_number FROM people WHERE phone_number IN
    (SELECT receiver FROM phone_calls WHERE caller IN
        (SELECT phone_number FROM people WHERE id IN
            (SELECT person_id FROM bank_accounts WHERE account_number IN -- Query person id
                (SELECT account_number -- Query bank acount numbers
                FROM atm_transactions
                WHERE year = 2020 AND month = 7 AND day = 28
                AND atm_location = "Fifer Street"
                AND transaction_type = "withdraw"))
            AND license_plate IN
                (SELECT license_plate FROM courthouse_security_logs
                WHERE month = 7 AND day = 28 AND hour = 10
                AND activity = "exit")
            AND phone_number IN
                (SELECT caller FROM phone_calls
                WHERE year = 2020 AND month = 7
                AND day = 28 AND duration < 60))
            AND year = 2020 AND month = 7
                AND day = 28 AND duration < 60);
/* caller | receiver
Ernest (367) 555-5533 | Berthold (375) 555-8161
Madison (286) 555-6063 | James (676) 555-6554 
Russell (770) 555-1861 | Philip (725) 555-3243*/

SELECT name, phone_number FROM people 
WHERE license_plate IN
(SELECT license_plate FROM courthouse_security_logs
WHERE month = 7 AND day = 28 AND hour = 10
AND activity = "exit");