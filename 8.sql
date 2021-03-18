/* Query that lists the names of the songs that fature other artists. */
SELECT name FROM songs WHERE name LIKE "%feat%";