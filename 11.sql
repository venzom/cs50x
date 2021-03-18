/* List the titles of the five highest rated movies (in order) that Chadwick Boseman starred in, */
/* starting with the highest rated */
SELECT title FROM people
JOIN stars on people.id = stars.person_id
JOIN movies on movies.id = stars.movie_id
JOIN ratings on ratings.movie_id = movies.id
WHERE name = "Chadwick Boseman"
ORDER BY rating DESC
LIMIT 5;
;