/* List the titles of all movies in which both Johnny Depp and Helena Bonham Carted starred */
SELECT title FROM people
JOIN movies ON movies.id = stars.movie_id
JOIN stars ON people.id = stars.person_id
WHERE name IN ("Johnny Depp", "Helena Bonham Carter");