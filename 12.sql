/* List the titles of all movies in which both Johnny Depp and Helena Bonham Carted starred */
SELECT title FROM people
JOIN movies ON movies.id = stars.movie_id
JOIN stars ON stars.person_id = people.id
WHERE name = "Johnny Depp"
INTERSECT
SELECT title FROM people
JOIN movies ON movies.id = stars.movie_id
JOIN stars ON stars.person_id = people.id
WHERE name = "Helena Bonham Carter";