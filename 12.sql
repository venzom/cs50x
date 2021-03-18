/* List the titles of all movies in which both Johnny Depp and Helena Bonham Carted starred */
SELECT title FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON movies.id = stars.movie_id
WHERE name = "Johnny Depp" OR name = "Helena Bonham Carter";