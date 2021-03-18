/* List the names of all people who starred in a movie in which Kevin Bacon also starred.
   Be sure to only select the Kevin Bacon born in 1958 */

SELECT name FROM people WHERE id IN
(SELECT person_id FROM stars
WHERE movie_id IN
(SELECT movie_id FROM stars
WHERE person_id IN
(SELECT id FROM people
WHERE name = "Kevin Bacon" AND birth = 1958)))
AND NOT name = "Kevin Bacon"
GROUP BY people.id;


-- SELECT name FROM movies
-- JOIN people ON people.id = stars.person_id AND stars.person_id =
-- (SELECT id FROM people WHERE name = "Kevin Bacon" AND birth = 1958)
-- JOIN stars ON movies.id = stars.movie_id

-- INTERSECT
-- SELECT stars FROM movies
-- SELECT name FROM movies
-- JOIN stars ON people.id = stars.person_id
-- JOIN movies ON movies.id = stars.movie_id
-- WHERE movie_id = (SELECT movie_id FROM stars WHERE person_id =
-- (SELECT id FROM people WHERE name = "Kevin Bacon" AND birth = 1958));

-- SELECT name FROM people WHERE id =
-- (SELECT person_id FROM stars WHERE movie_id =
-- (SELECT movie_id FROM stars WHERE person_id =
-- (SELECT id FROM people WHERE name = "Kevin Bacon" AND birth = 1958)));