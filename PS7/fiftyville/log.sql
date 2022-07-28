-- Keep a log of any SQL queries you execute as you solve the mystery.
--SELECT description FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28 AND street = "Humphrey Street";
--| Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. |
--| Littering took place at 16:36. No known witnesses.
SELECT * FROM interviews WHERE year = 2021 AND month = 7 AND day = 28;
--Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from
--  the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
--I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on
--  Leggett Street and saw the thief there withdrawing some money.
--As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were
--  planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.
        --People who exited the bakery
SELECT name, phone_number, passport_number FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15  AND minute < 25);
--+---------+----------------+-----------------+
--|  name   |  phone_number  | passport_number |
--+---------+----------------+-----------------+
--| Vanessa | (725) 555-4692 | 2963008352      |
--| Barry   | (301) 555-4174 | 7526138472      |
--| Iman    | (829) 555-5269 | 7049073643      |
--| Sofia   | (130) 555-0289 | 1695452385      |
--| Luca    | (389) 555-5198 | 8496433585      |
--| Diana   | (770) 555-1861 | 3592750733      |
--| Kelsey  | (499) 555-9472 | 8294398571      |
--| Bruce   | (367) 555-5533 | 5773159633      |
--+---------+----------------+-----------------+
        -- People who used the ATM
SELECT name FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE atm_location = "Leggett Street" AND year = 2021 AND month = 7 AND day = 28)) ;
--+---------+
--|  name   |
--+---------+
--| Kenny   |
--| Iman    |
--| Benista |
--| Taylor  |
--| Brooke  |
--| Luca    |
--| Diana   |
--| Bruce   |
--| Kaelyn  |
--+---------+
        --Suspects who did exited bakery and where at the ATM and withdrew money
SELECT name FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE atm_location = "Leggett Street" AND year = 2021 AND month = 7 AND day = 28 AND transaction_type = "withdraw"))
    AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15  AND minute < 25) ;
--+-------+
--| name  |
--+-------+
--| Iman  |
--| Luca  |
--| Diana |
--| Bruce |
--+-------+
        --Suspects that made calls that day
SELECT name FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND caller IN (SELECT phone_number FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE atm_location = "Leggett Street" AND year = 2021 AND month = 7 AND day = 28))
    AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15  AND minute < 25)) );
--+-------+
--| name  |
--+-------+
--| Diana |
--| Bruce |
--+-------+
        --Earliest flight on 29th where a suspect flew
SELECT * FROM flights WHERE day = 29 AND id IN (SELECT flight_id FROM PASSENGERS WHERE passport_number IN (SELECT passport_number FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND caller IN (SELECT phone_number FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE atm_location = "Leggett Street" AND year = 2021 AND month = 7 AND day = 28))
    AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15  AND minute < 25)) ))) ORDER BY hour ASC LIMIT (1);

        --Earliest flight destination
SELECT full_name FROM airports WHERE id =(SELECT destination_airport_id FROM flights WHERE day = 29 AND id IN (SELECT flight_id FROM PASSENGERS WHERE passport_number IN (SELECT passport_number FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND caller IN (SELECT phone_number FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE atm_location = "Leggett Street" AND year = 2021 AND month = 7 AND day = 28))
    AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15  AND minute < 25)) ))) ORDER BY hour ASC LIMIT (1));
--+-------------------+
--|     full_name     |
--+-------------------+
--| LaGuardia Airport |
--+-------------------+
        --Guilty!
SELECT name FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = (SELECT id FROM flights WHERE day = 29
    AND id IN (SELECT flight_id FROM PASSENGERS WHERE passport_number IN (SELECT passport_number FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28
    AND caller IN (SELECT phone_number FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE atm_location = "Leggett Street" AND year = 2021 AND month = 7 AND day = 28))
    AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15  AND minute < 25)) ))) ORDER BY hour ASC LIMIT (1)))
    AND name IN (SELECT name FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND caller IN (SELECT phone_number FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE atm_location = "Leggett Street" AND year = 2021 AND month = 7 AND day = 28))
    AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15  AND minute < 25)) ));
--+-------+
--| name  |
--+-------+
--| Bruce |
--+-------+
        --Accomplice
SELECT name FROM people WHERE phone_number = (SELECT receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND caller = (SELECT phone_number FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = (SELECT id FROM flights WHERE day = 29
    AND id IN (SELECT flight_id FROM PASSENGERS WHERE passport_number IN (SELECT passport_number FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28
    AND caller IN (SELECT phone_number FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE atm_location = "Leggett Street" AND year = 2021 AND month = 7 AND day = 28))
    AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15  AND minute < 25)) ))) ORDER BY hour ASC LIMIT (1)))
    AND name IN (SELECT name FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND caller IN (SELECT phone_number FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE atm_location = "Leggett Street" AND year = 2021 AND month = 7 AND day = 28))
    AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15  AND minute < 25))))));
--+-------+
--| name  |
--+-------+
--| Robin |
--+-------+