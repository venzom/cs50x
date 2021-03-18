/* List the names of songs that are by post malone */
SELECT name FROM songs WHERE id IN (SELECT id FROM artists WHERE name = "Post Malone");