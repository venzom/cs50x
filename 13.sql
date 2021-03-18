/* List the names of all people who starred in a movie in which Kevin Bacon also starred.
   Be sure to only select the Kevin Bacon born in 1958 */

-- SELECT name FROM people
-- JOIN stars ON people.id = stars.person_id
-- JOIN movies ON movies.id = stars.movie_id AND stars.person_id = (
-- SELECT id FROM people WHERE birth = 1958)
-- WHERE name = "Kevin Bacon";

SELECT name FROM people WHERE id =
(SELECT person_id FROM stars WHERE movie_id =
(SELECT movie_id FROM stars WHERE person_id =
(SELECT id FROM people WHERE name = "Kevin Bacon" AND birth = 1958)));