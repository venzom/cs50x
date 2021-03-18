/* Query to list the titles and release years of all Harry Potter Movies, in chronological order */
SELECT title, year FROM movies WHERE title LIKE "Harry Potter%" ORDER BY year;