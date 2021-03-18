/* List the names of all people who starred in a movie in which Kevin Bacon also starred.
   Be sure to only select the Kevin Bacon born in 1958 */

-- SELECT name FROM people
-- JOIN stars ON people.id = stars.person_id
-- JOIN movies ON movies.id = stars.movie_id AND stars.person_id = (
-- SELECT id FROM people WHERE birth = 1958)
-- WHERE name = "Kevin Bacon";

SELECT DISTINCT(name) FROM people
JOIN movies ON movies.id = stars.movie_id
JOIN stars ON stars.person_id =
(SELECT id FROM people WHERE name = "Kevin Bacon")
WHERE birth = 1958;