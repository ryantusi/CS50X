-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Checking tables--
.table

--Checking Schema--
.schema

--Checking crime description of all the dates--
SELECT * FROM crime_scene_reports;

--Checking description of the day of theft--
SELECT description FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28;

--Checking everything on the day of theft--
SELECT * FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28;
-- Axmark Road - 12:04 - vandalism, Boyce Avenue - 03:01 - Shoplifting - 2 witness, Humphrey Street - 10:15 cs50 duck theft in bakery - 3 witness--
-- Widenius Street - 20:30 - money laundering, Humphrey Street - 16:36 - littering--

--Checking interviews--
.schema interviews
SELECT * FROM interviews WHERE year = 2021 AND month = 7 AND day = 28;
-- Ruth: within 10 mins theif drove from parking in bakery--
-- Eugene: saw withdrawing cash from ATM Leggett Street before going to bakery --
-- Raymond: Theif called less than a minute call, tomorrow early flight, asked to purchase ticket--

--Checking bakery--
.schema bakery_security_logs
SELECT * FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28;
-- 10:15 - Theft--
-- 10:16 - 5P2BI95 --
-- 10:18 - 94KL13X --
-- 10:18 - 6P58WS2 --
-- 10:19 - 4328GD8 --
-- 10:20 - G412CB7 --
-- 10:21 - L93JTIZ --
-- 10:23 - 322W7JE --
-- 10:23 - 0NTHK55 --

--Checking atm_transaction--
.schema atm_transactions
SELECT * FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location LIKE "LEGGETT STREET";
-- Account numbers - amount --
-- 28500762 : 48 --
-- 28296815 : 20 --
-- 76054385 : 60 --
-- 49610011 : 50 --
-- 16153065 : 80 --
-- 25506511 : 20 --
-- 81061156 : 30 --
-- 26013199 : 35 --

--Checking phone_calls--
.schema phone_calls
SELECT * FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28;
-- Calls less than a minute --
-- caller : reciever --
--(130) 555-0289 : (996) 555-8899--
--(499) 555-9472 : (892) 555-8872--
--(367) 555-5533 : (375) 555-8161--
--(499) 555-9472 : (717) 555-1342--
--(286) 555-6063 : (676) 555-6554--
--(770) 555-1861 : (725) 555-3243--
--(031) 555-6622 : (910) 555-3251--
--(826) 555-1652 : (066) 555-9701--
--(338) 555-6650 : (704) 555-2131--

--Checking FLights--
.schema flights
SELECT * FROM flights WHERE year = 2021 AND month = 7 AND day = 29;
-- Earliest Flight from origin_id: 8 --
-- flight_id - destination_id - time --
-- 18 - 6 - 16:00 --
-- 23 - 12 - 12:00 --
-- 36 - 4 - 8:20 --
-- 43 - 1 - 9:30 --
-- 53 - 9 - 15:20 --

--Checking airports--
.schema airports
SELECT * FROM airports WHERE id = 8;
-- CSF - Fiftyville Airport : 8 --

--Checking passengers--
.schema passengers

--Checking bank_accounts--
SELECT * FROM bank_accounts;

--Checking all details of the passenger who flew on 29th july 2021 from flight origin_id 8 (i.e) fiftyville airport--
SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE year = 2021 AND month = 7 AND day = 29);
/*
| 2835165196      |
| 6131360461      |
| 3231999695      |
| 3592750733      |
| 2626335085      |
| 6117294637      |
| 2996517496      |
| 3915621712      |
| 4149859587      |
| 9183348466      |
| 7378796210      |
| 7874488539      |
| 4195341387      |
| 6263461050      |
| 3231999695      |
| 7951366683      |
| 7214083635      |
| 1695452385      |
| 5773159633      |
| 1540955065      |
| 8294398571      |
| 1988161715      |
| 9878712108      |
| 8496433585      |
| 7597790505      |
| 6128131458      |
| 6264773605      |
| 3642612721      |
| 4356447308      |
| 7441135547      |
| 7894166154      |
| 6034823042      |
| 4408372428      |
| 2312901747      |
| 1151340634      |
| 8174538026      |
| 1050247273      |
| 7834357192 */

--Suspects license plate--
SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25 AND activity = "exit";

--Suspects Account numbers--
SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location LIKE "LEGGETT STREET" AND transaction_type = "withdraw";

--Suspects phone numbers--
SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60;

--Suspects Flight ID--
SELECT id FROM flights WHERE year = 2021 AND month = 7 AND day = 29;

--Suspects Bank Account--
SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location LIKE "LEGGETT STREET" AND transaction_type = "withdraw");


--Checking People--
SELECT * FROM people;

--Suspects from people--
SELECT * FROM people WHERE license_plate IN
(SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25 AND activity = "exit");
/*
+--------+---------+----------------+-----------------+---------------+
|   id   |  name   |  phone_number  | passport_number | license_plate |
+--------+---------+----------------+-----------------+---------------+
| 221103 | Vanessa | (725) 555-4692 | 2963008352      | 5P2BI95       |
| 243696 | Barry   | (301) 555-4174 | 7526138472      | 6P58WS2       |
| 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
| 398010 | Sofia   | (130) 555-0289 | 1695452385      | G412CB7       |
| 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
| 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
| 560886 | Kelsey  | (499) 555-9472 | 8294398571      | 0NTHK55       |
| 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
+--------+---------+----------------+-----------------+---------------+ */

--Final Suspects--
SELECT * FROM people WHERE license_plate IN
(SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25 AND activity = "exit")
AND phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60)
AND id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location LIKE "LEGGETT STREET" AND transaction_type = "withdraw"))
AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE year = 2021 AND month = 7 AND day = 29));
/*
+--------+-------+----------------+-----------------+---------------+
|   id   | name  |  phone_number  | passport_number | license_plate |
+--------+-------+----------------+-----------------+---------------+
| 514354 | Diana | (770) 555-1861 | 3592750733      | 322W7JE       |
| 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
+--------+-------+----------------+-----------------+---------------+ */

--Checking the suspects flights--
SELECT * FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25 AND activity = "exit") AND phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60) AND id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location LIKE "LEGGETT STREET" AND transaction_type = "withdraw")) AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE year = 2021 AND month = 7 AND day = 29));

--Checking destination_airport_id of suspects--
SELECT destination_airport_id FROM flights JOIN passengers ON flights.id = passengers.flight_id WHERE year = 2021 AND month = 7 AND day = 29 AND passport_number IN (SELECT passport_number FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25 AND activity = "exit") AND phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60) AND id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location LIKE "LEGGETT STREET" AND transaction_type = "withdraw")) AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE year = 2021 AND month = 7 AND day = 29)));
/*+------------------------+
| destination_airport_id |
+------------------------+
| 6                      |
| 4                      |
+------------------------+*/

SELECT * FROM flights JOIN passengers ON flights.id = passengers.flight_id WHERE year = 2021 AND month = 7 AND day = 29 AND passport_number IN (SELECT passport_number FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25 AND activity = "exit") AND phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60) AND id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location LIKE "LEGGETT STREET" AND transaction_type = "withdraw")) AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE year = 2021 AND month = 7 AND day = 29)));

--Final destination--
SELECT * FROM airports WHERE id IN (SELECT destination_airport_id FROM flights JOIN passengers ON flights.id = passengers.flight_id WHERE year = 2021 AND month = 7 AND day = 29 AND passport_number IN (SELECT passport_number FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25 AND activity = "exit") AND phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60) AND id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location LIKE "LEGGETT STREET" AND transaction_type = "withdraw")) AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE year = 2021 AND month = 7 AND day = 29))));
/*+----+--------------+-----------------------------+---------------+
| id | abbreviation |          full_name          |     city      |
+----+--------------+-----------------------------+---------------+
| 4  | LGA          | LaGuardia Airport           | New York City |
| 6  | BOS          | Logan International Airport | Boston        |
+----+--------------+-----------------------------+---------------+*/

--Its bruce who took the earliest flight--

--reciever number--
SELECT receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60 AND caller = (SELECT phone_number FROM people WHERE name LIKE "BRUCE");
/* +----------------+
|    receiver    |
+----------------+
| (375) 555-8161 |
+----------------+*/

--The accomplice--
SELECT name FROM people WHERE phone_number = (SELECT receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60 AND caller = (SELECT phone_number FROM people WHERE name LIKE "BRUCE"));
/*+-------+
| name  |
+-------+
| Robin |*/

